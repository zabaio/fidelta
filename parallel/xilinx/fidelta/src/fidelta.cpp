#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

#ifdef VALDEB
	#include <valgrind/callgrind.h>
#endif

#define CL_HPP_CL_1_2_DEFAULT_BUILD
#define CL_HPP_TARGET_OPENCL_VERSION 120
#define CL_HPP_MINIMUM_OPENCL_VERSION 120
#define CL_HPP_ENABLE_PROGRAM_CONSTRUCTION_FROM_ARRAY_COMPATIBILITY 1
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS

#include <CL/opencl.h>
#include <CL/cl_ext.h>

#define OCL_CHECK(error,call)                                       \
    call;                                                           \
    if (error != CL_SUCCESS) {                                      \
      printf("%s:%d Error calling " #call ", error code is: %d\n",  \
              __FILE__,__LINE__, error);                            \
      exit(EXIT_FAILURE);                                           \
    }

#include "types.h"
#include "display.h"

#ifndef PTSLIM
    #define PTSLIM 300000
#endif

// c-sim of accelerated functions
int sym_in_circle(float *innerdata, float *son);
void sym_accel_in_circle(float *indata, int *instate, float *inson, int *inmaxquery);

// Creates and adds the list of points encroaching triangle "son":
// a point p is added if it's encroaching "father" or "uncle" AND if in_circle (son, p) is true
int merge (t_node *father, t_node *uncle, float accel_data[], int accel_state[]);

int main(int argc, char *argv[])
{
    int rmode = 0, n_pts, i;
    float max_cor;

    //constructed point file, eventual input point file
    FILE *node, *extnode; 

    //start init time
    clock_t a = clock();

    // read mode and eventual input file from cmd, then proceed initializing node file
    rmode = init_cmd (argc, argv, &node, &extnode, &n_pts, &max_cor);


    // --- Start OpenCL initialization --- //

    cl_int err;

    // Platform
    char cl_platform_vendor[1001];
    char cl_platform_name[1001];
    cl_uint platform_count;
	cl_platform_id platform_id;
	cl_platform_id platforms[16];

	OCL_CHECK (err, err = clGetPlatformIDs(16, platforms, &platform_count));
	for (cl_uint count = 0; count < platform_count; count++){
		OCL_CHECK (err, err = clGetPlatformInfo(platforms[count], CL_PLATFORM_VENDOR,
						      1000, (void *)cl_platform_vendor, NULL));
		if (strcmp(cl_platform_vendor, "Xilinx") == 0){
			printf("Found platform vendor: %s\n", cl_platform_vendor);
			platform_id = platforms[count];
			break;
		}
	}
	OCL_CHECK (err, err = clGetPlatformInfo(platform_id, CL_PLATFORM_NAME,
						  1000, (void *)cl_platform_name, NULL));
	printf("Found platform name: %s\n", cl_platform_vendor);

	// Device
	cl_device_id device_id;
	char cl_device_name[1001];

	OCL_CHECK (err, err = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ACCELERATOR,
			              1, &device_id, NULL));
	OCL_CHECK (err, err = clGetDeviceInfo(device_id, CL_DEVICE_NAME,
			              1000, (void *)cl_device_name, NULL));
    printf("Found device name: %s\n", cl_device_name);

    // Context and queue
    cl_context context;
    cl_command_queue q;

    OCL_CHECK (err, context = clCreateContext (NULL, 1, &device_id, NULL, NULL, &err));
    OCL_CHECK (err, q = clCreateCommandQueue (context, device_id,
    					CL_QUEUE_PROFILING_ENABLE, &err));

    // Program and kernel
    char *xclbin_name = argv[1];
    char *kernelbinary;
    cl_program program;
    cl_kernel krnl_incircle;

    size_t size = load_xclbin(xclbin_name, &kernelbinary);
    OCL_CHECK (err, program = clCreateProgramWithBinary(context, 1, &device_id, &size,
    			              (const unsigned char **) &kernelbinary, NULL, &err));
    OCL_CHECK (err, krnl_incircle = clCreateKernel(program, "accel_in_circle", &err));

    // Buffers and arguments
    float *accel_data;
    int *accel_state;
    int *sym_accel_state;
    float *accel_son;
    cl_int maxquery;
    cl_mem data_buf;
    cl_mem state_buf;
    cl_mem son_buf;

    OCL_CHECK (err, err = posix_memalign((void **) &accel_data, 4096, 2*(PTSLIM + 10) * sizeof(float)));
    OCL_CHECK (err, err = posix_memalign((void **) &accel_state, 4096, (PTSLIM + 10) * sizeof(int)));
    OCL_CHECK (err, err = posix_memalign((void **) &sym_accel_state, 4096, (PTSLIM + 10) * sizeof(int)));
    OCL_CHECK (err, err = posix_memalign((void **) &accel_son, 4096, 6*sizeof(float)));

	OCL_CHECK (err, data_buf = clCreateBuffer(context, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR,
			                   2*(PTSLIM + 10) * sizeof(float), accel_data, NULL));

	OCL_CHECK (err, state_buf = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR,
    				            (PTSLIM + 10) * sizeof (int), accel_state, NULL));

	OCL_CHECK (err, son_buf = clCreateBuffer(context, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR,
							  6 * sizeof(float), accel_son, NULL));

	OCL_CHECK (err, err = clSetKernelArg(krnl_incircle, 0, sizeof(cl_mem), &state_buf));
	OCL_CHECK (err, err = clSetKernelArg(krnl_incircle, 1, sizeof(cl_mem), &data_buf));
	OCL_CHECK (err, err = clSetKernelArg(krnl_incircle, 2, sizeof(cl_mem), &son_buf));
	OCL_CHECK (err, err = clSetKernelArg(krnl_incircle, 3, sizeof(cl_int), &maxquery));


	// ----- End OpenCL initialization ---- //


	// --- Start reading input data set --- //

    if (rmode)
        init_random(&node, n_pts, max_cor);
    else
        init_from_file(&extnode, &node, &n_pts);

    // Now "node" stores all the points needed.
    // We create tris, the core structure of the algorithm.
    // It is a list of triangles, each one with the array of points that encroach on it, 
    // meaning that they are inside the triangle's circumcircle
    // The first three points in result.node form a triangle bounding all other points, which we add to tris.
    // Then we add every point to its encroaching points array.

    t_node *tris = NULL;
    point *pts = (point *) malloc((PTSLIM + 3) * sizeof(point));    

    fseek(node, 0, SEEK_SET);
    fscanf (node, "%*[^\n]\n");
    for (i = 0; i < 3; i++){
        fscanf (node, "%d %f %f \n", &pts[i].id, &pts[i].x, &pts[i].y);       
    }
    push_t(&tris, pts[0], pts[1], pts[2]);
    tris->dim = n_pts;
    tris->enc = (point *) malloc(tris->dim*sizeof(point));
    for (i = 0; i < n_pts; i++){
        fscanf (node, "%d %f %f \n", &(tris->enc[i].id), &(tris->enc[i].x), &(tris->enc[i].y));
        pts[i+3] = tris->enc[i];
        print_pt (pts[i+3]);
    }

    fclose (node);

    // Initialization of the hash table segs
    // It stores every segment generated, hashed on the points ids,
    // and their (up to two) adjacent triangle
    // We start by adding the three bounding segments

    record_segs *segs = NULL;
    segs_add (&segs, tris->t.p1, tris->t.p2, tris);
    segs_add (&segs, tris->t.p2, tris->t.p3, tris);
    segs_add (&segs, tris->t.p3, tris->t.p1, tris);

    // Initialization of the active segments list acts.
    // Each segment in acts is the face of a triangle (acts->father)
    // that we can delete and replace by linking the vertices of the segment to the first 
    // encroaching point (in order of id) of the triangle.
    // Acts is filled in rounds. Within each round all elements are independent, 
    // so all merge calls could be processed simultaneously

    act_node *acts = NULL;
    act_node *nextround = NULL;

    push_act (&nextround, segs, tris->t.p1, tris->t.p2, tris);
    push_act (&nextround, segs, tris->t.p2, tris->t.p3, tris);
    push_act (&nextround, segs, tris->t.p3, tris->t.p1, tris);
    
    #ifdef LOG
        int roundcount = 0, roundwidth = 0;
    #endif

    // ------- End of data set input ------ //

        OCL_CHECK (err, err = clEnqueueWriteBuffer(q, data_buf, CL_FALSE, 0,
         					  8*sizeof(float), (void *)accel_data, 0, NULL, NULL));
        OCL_CHECK (err, err =clFinish(q));
        OCL_CHECK (err, err = clEnqueueTask(q, krnl_incircle, 0, NULL, NULL));
        OCL_CHECK (err, err =clFinish(q));



    // --- Start Delaunay Triangulation --- //

    a = clock() - a; 
    clock_t t = clock();

	#ifdef VALDEB
    	CALLGRIND_START_INSTRUMENTATION;
	#endif

    while(acts != NULL || nextround != NULL){
        
        // loads next round
        if (acts == NULL){
            #ifdef LOG
                printf ("Round width: %d\n", roundwidth);
                roundwidth = 0;
                roundcount++;
            #endif
            #ifdef DEBUG
                printf("Fine round;\n");
                print_tris_id(tris);
            #endif
            
            acts = nextround;
            nextround = NULL;

            act_node *aprobe = acts;
            t_node *tprobe = tris;

            while (aprobe != NULL){
                
                push_t (&tprobe, aprobe->act->seg.a, aprobe->act->seg.b, aprobe->father->enc[0]); 
                
                int alldim = 0;
                if(aprobe->act->tfirst != NULL)
                    alldim += aprobe->act->tfirst->dim;
                if(aprobe->act->tsecond != NULL)
                    alldim += aprobe->act->tsecond->dim;
                tprobe->enc = (point *) malloc(alldim*sizeof(point));

                accel_son[0] = tprobe->t.p1.x;
                accel_son[1] = tprobe->t.p1.y;
                accel_son[2] = tprobe->t.p2.x;
                accel_son[3] = tprobe->t.p2.y;
                accel_son[4] = tprobe->t.p3.x;
                accel_son[5] = tprobe->t.p3.y;

                int dimquery = merge (aprobe->father, aprobe->uncle, accel_data, accel_state);

                maxquery = (dimquery + 7) & ~0x07;

                //printf("dimquery = %d, maxquery = %d\n", dimquery, maxquery);
				if (dimquery == 0){
					aprobe = aprobe->next;
					continue;
				}
				/*
					for(i = 0; i<dimquery; i++){
						sym_accel_state[i] = accel_state[i];
					}
				*/
				for(i = dimquery; i < maxquery; i ++){
                    accel_state[i] = -1;
                    //sym_accel_state[i] = accel_state[i];
                }

				#ifdef DEBUG
					printf("\n\n%d %d %d\nState out host: ", tprobe->t.p1.id, tprobe->t.p2.id, tprobe->t.p3.id);
					for (i = 0; i<maxquery; i++){
						printf("%2d ",accel_state[i]);
					}
					printf("\nv\n Data out host\n");

					for(i =0; i<8; i++){
						printf("%f %f\n", accel_data[i*2], accel_data[i*2+1]);
					}
				#endif

				cl_event evts[5];

                OCL_CHECK (err, err = clEnqueueWriteBuffer(q, state_buf, CL_FALSE, 0,
                					  maxquery*sizeof(int), (void *)accel_state, 0, NULL, (evts)));
                OCL_CHECK (err, err = clEnqueueWriteBuffer(q, son_buf, CL_FALSE, 0,
                					  6*sizeof(float), (void *)accel_son, 0, NULL, (evts + 1)));
                OCL_CHECK (err, err = clEnqueueWriteBuffer(q, data_buf, CL_FALSE, 0,
                					  2*maxquery*sizeof(float), (void *)accel_data, 0, NULL, (evts+2)));

            	OCL_CHECK (err, err = clSetKernelArg(krnl_incircle, 3, sizeof(cl_int), &maxquery));

                OCL_CHECK (err, err = clEnqueueWaitForEvents(q, 3, evts));

                //sym_accel_in_circle(accel_data, sym_accel_state, accel_son, &maxquery);
                OCL_CHECK (err, err = clEnqueueTask(q, krnl_incircle, 0, NULL, (evts + 3)));

                OCL_CHECK (err, err = clEnqueueReadBuffer(q, state_buf, CL_FALSE, 0,
                				      dimquery*sizeof(int), (void *)accel_state, 1, (evts + 3), (evts + 4)));

                OCL_CHECK (err, err =clFinish(q));

				#ifdef DEBUG

					printf("State sym host: ");
					for (i = 0; i<maxquery; i++){
						printf("%2d ",sym_accel_state[i]);
					}
					printf("\nState in host: ");
					for (i = 0; i<maxquery; i++){
						printf("%2d ",accel_state[i]);
					}
					printf("\n");

                    printf("\nPrima:");
                    print_tris_id(tprobe);
                #endif

                for (i = 0; i < dimquery; i++){
                    if (accel_state[i] != -1){
                        tprobe->enc[tprobe->dim] = pts[accel_state[i]];
                        tprobe->dim ++;
                    }
                }

                #ifdef DEBUG
                    printf("\nDopo:");
                    print_tris_id(tprobe);
                #endif
            
                aprobe = aprobe->next;
            }

            #ifdef DEBUG
                print_tris_id(tprobe);
            #endif

        }

        #ifdef LOG
            roundwidth++;
        #endif
        #ifdef DEBUG
            print_acts_id(acts);
            printf("\nAttivo: %d %d\n", acts->act->seg.a.id, acts->act->seg.b.id);
        #endif
        
        tris = tris->prev;
        t_node *encroached = NULL;

        #ifdef DEBUG
            print_tris_id(tris);
        #endif
        
        // We now have a new triangle. We add the segment a-pt to segs.
        // If the segment already existed on it's other side there's already a triangle:
        // in that case encroached receives the address of the triangle we'll delete in the next round,
        // which is the one with the lowest encroaching point id, and a-pt is added to active segments.
        // If there's no triangle on the other side or the lowest encroaching point ids are the same,
        // encroached is set to NULL and a-pt is not active
        encroached = segs_add (&segs, acts->act->seg.a, acts->father->enc[0], tris);
        
        if (encroached != NULL){
            push_act (&nextround, segs, acts->act->seg.a, acts->father->enc[0], encroached);
        }

        // Same as before, but considering the other new segment, b-pt
        encroached = segs_add (&segs, acts->act->seg.b, acts->father->enc[0], tris);
        
        if (encroached != NULL){
            push_act (&nextround, segs, acts->act->seg.b, acts->father->enc[0], encroached);
        }
        
        #ifdef DEBUG
            print_segs_id(segs);
        #endif

        // Now we check if act is still active even after having replaced it's father with son. 
        // If uncle is null we're on the border: a-b has only tfirst filled, 
        // we update it and if there are still enc pts we add it so nextround
        assert (acts->act->tfirst == acts->father || acts->act->tsecond == acts->father);
        if(acts->uncle == NULL){
            acts->act->tfirst = tris;
            if (tris->dim != 0){
                push_act (&nextround, segs, acts->act->seg.a, acts->act->seg.b, tris);
            }
        }

        // If uncle isn't null we find which triangle is father in segs, 
        // then we check if a-b is active, on both sides
        else{
            
            // Checking who's the father and replacing it with the son
            if (acts->act->tfirst == acts->father){
                acts->act->tfirst = tris;
            }
            else{ 
                acts->act->tsecond = tris;
            }

            // Checking if the first adjecent triangle added in segs is going to die in next round.
            // If so we add a-b to acts and the triagle is its father
            if (acts->act->tfirst->dim != 0 && 
               (acts->act->tsecond->dim == 0 || acts->act->tfirst->enc[0].id  <  acts->act->tsecond->enc[0].id)){
                
                push_act (&nextround, segs, acts->act->seg.a, acts->act->seg.b, acts->act->tfirst);
            
            }

            // Same thing but with the second triangle
            else if (acts->act->tsecond->dim != 0 && 
                    (acts->act->tfirst->dim == 0 || acts->act->tsecond->enc[0].id  <  acts->act->tfirst->enc[0].id)){

                push_act (&nextround, segs, acts->act->seg.a, acts->act->seg.b, acts->act->tsecond);
            
            }
        }

        #ifdef DEBUG
            print_acts_id(nextround);
        #endif

        pop_act (&acts);

    }

    // ---- End Delaunay Triangulation ----- //


    // --- Cleanup, output and profiling --- //

    clReleaseCommandQueue(q);
    clReleaseContext(context);
    clReleaseDevice(device_id);
    clReleaseKernel(krnl_incircle);
    clReleaseProgram(program);
    clReleaseMemObject(data_buf);
    clReleaseMemObject(state_buf);
    clReleaseMemObject(son_buf);

	#ifdef VALDEB
	    CALLGRIND_STOP_INSTRUMENTATION;
   	 	CALLGRIND_DUMP_STATS;
	#endif
    
	t += clock() - t;
    clock_t o = clock();

    print_result (tris, n_pts);

    o = clock() - o;
    
    float del_time = 1000*((float)t)/CLOCKS_PER_SEC;
    float ini_time = 1000*((float)a)/CLOCKS_PER_SEC;
    float out_time = 1000*((float)o)/CLOCKS_PER_SEC;

    printf("Init time: %d ms\n", (int)ini_time);
    printf("Delaunay time: %d ms\n", (int)del_time);
    printf("Writing output: %d ms\n", (int)out_time);

    #ifdef LOG
        printf ("Number of rounds: %d\n", roundcount);
    #endif

    return 0;
}

int merge (t_node *father, t_node *uncle, float accel_data[], int accel_state[]){

    // We discard the fist point of father since is a vertex of son.
    // If there's no uncle we just test the father's vertices and add them to son
    point *fenc = father->enc;
    int fid = 1;
    int uid = 0;
    int sid = 0;

    if (uncle == NULL){
        for(; fid < father->dim; fid++){
            accel_state[sid] = fenc[fid].id;
            accel_data[2*sid] = fenc[fid].x;
            accel_data[2*sid + 1] = fenc[fid].y;
            sid ++;
        }
    }
    else{

        // If uncle exists we merge its and father's encroaching point lists
        // and add it to son, while maintaining the order of the ids
        point *uenc = uncle->enc;
        while ((fid < father->dim || uid < uncle->dim)){
            
            if (uid == uncle->dim || (fid < father->dim && fenc[fid].id < uenc[uid].id)){
                accel_state[sid] = fenc[fid].id;
                accel_data[2*sid] = fenc[fid].x;
                accel_data[2*sid + 1] = fenc[fid].y;
                sid ++;
                fid ++;
            }
            
            else if (fid == father->dim || (uid < uncle->dim && uenc[uid].id < fenc[fid].id)){
                accel_state[sid] = uenc[uid].id;
                accel_data[2*sid] = uenc[uid].x;
                accel_data[2*sid + 1] = uenc[uid].y;
                sid ++;
                uid ++;
            }

            else if (fid < father->dim && uid < uncle->dim && fenc[fid].id == uenc[uid].id){
                accel_state[sid] = fenc[fid].id;
                accel_data[2*sid] = fenc[fid].x;
                accel_data[2*sid + 1] = fenc[fid].y;
                sid ++;
                uid ++;
                fid ++;
            }
        }
    }

    return sid;
}


int sym_in_circle(float *innerdata, float *son){

    float xda = son[0] - innerdata[0];
    float xdb = son[2] - innerdata[0];
    float xdc = son[4] - innerdata[0];
    float yda = son[1] - innerdata[1];
    float ydb = son[3] - innerdata[1];
    float ydc = son[5] - innerdata[1];
    float da2da2 = xda*xda + yda*yda;
    float db2db2 = xdb*xdb + ydb*ydb;
    float dc2dc2 = xdc*xdc + ydc*ydc;

    float min1 = xdb*ydc - xdc*ydb;
    float min2 = xda*ydc - xdc*yda;
    float min3 = xda*ydb - xdb*yda;

    float det = da2da2*min1 - db2db2*min2 + dc2dc2*min3;
    return (det>0);
}

void sym_accel_in_circle(float *indata, int *instate, float *inson, int *inmaxquery){

	float data[2];
	int state;
	float son[6];
	int maxquery = *inmaxquery;
	int i;

	memcpy(son, inson, 6*sizeof(float));

	for (i = 0; i < maxquery; i++){

		memcpy(data, indata + 2*i, 2*sizeof(float));
		memcpy(&state, instate + i, sizeof(int));

        if (state != -1 && !sym_in_circle(data, son))
            state = -1;
        
		memcpy(instate + i, &state, sizeof(int));
	}

	return;
}
