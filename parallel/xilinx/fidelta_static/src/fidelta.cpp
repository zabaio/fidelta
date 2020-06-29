#include <stdio.h>
#include <stdlib.h>
#include <chrono>
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

#ifndef MAXQUERY
    #define MAXQUERY 1000000
#endif
#ifndef PTSLIM
    #define PTSLIM 5000000
#endif

// c-sim of accelerated functions
int sym_in_circle(float *innerdata, float *son);
void sym_accel_in_circle(float *indata, int *instate, int *outstate);

// Creates and adds the list of points encroaching triangle "son":
// a point p is added if it's encroaching "father" or "uncle" AND if in_circle (son, p) is true
void merge (t_node *father, int *fid, t_node *uncle, int *uid, float accel_data[], int accel_state[], int *bookmark);

int main(int argc, char *argv[])
{

    int rmode = 0, n_pts, i, opt_time = 0;
    float max_cor;

    //constructed point file, eventual input point file
    FILE *node, *extnode; 

    //start init time
    auto time_start = std::chrono::steady_clock::now();

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
    int *accel_result;
    int *sym_accel_result;
    int bookmark;
    cl_mem data_buf;
    cl_mem state_buf;
    cl_mem result_buf;

    OCL_CHECK (err, err = posix_memalign((void **) &accel_data, 4096, 8*MAXQUERY * sizeof(float)));
    OCL_CHECK (err, err = posix_memalign((void **) &accel_state, 4096, MAXQUERY * sizeof(int)));
    OCL_CHECK (err, err = posix_memalign((void **) &accel_result, 4096, MAXQUERY * sizeof(int)));
    OCL_CHECK (err, err = posix_memalign((void **) &sym_accel_result, 4096, MAXQUERY * sizeof(int)));

	OCL_CHECK (err, data_buf = clCreateBuffer(context, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR,
			                   8*MAXQUERY*sizeof(float), accel_data, NULL));

	OCL_CHECK (err, state_buf = clCreateBuffer(context, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR,
    				            MAXQUERY * sizeof (int), accel_state, NULL));

	OCL_CHECK (err, result_buf = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR,
    				            MAXQUERY * sizeof (int), accel_result, NULL));

	OCL_CHECK (err, err = clSetKernelArg(krnl_incircle, 0, sizeof(cl_mem), &data_buf));
	OCL_CHECK (err, err = clSetKernelArg(krnl_incircle, 1, sizeof(cl_mem), &state_buf));
	OCL_CHECK (err, err = clSetKernelArg(krnl_incircle, 2, sizeof(cl_mem), &result_buf));

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
        //print_pt (pts[i+3]);
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

    auto time_end = std::chrono::steady_clock::now();
    int init_time = std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start).count();

    // ------- End of data set input ------ //

    bookmark = 0;
    OCL_CHECK (err, err = clSetKernelArg(krnl_incircle, 3, sizeof(int), &bookmark));
    OCL_CHECK (err, err = clEnqueueTask(q, krnl_incircle, 0, NULL, NULL));
    OCL_CHECK (err, err = clFinish(q));

    // --- Start Delaunay Triangulation --- //

    time_start = std::chrono::steady_clock::now();

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

            push_t (&tprobe, aprobe->act->seg.a, aprobe->act->seg.b, aprobe->father->enc[0]); 
            
            int alldim = 0;
            if(aprobe->act->tfirst != NULL)
                alldim += aprobe->act->tfirst->dim;
            if(aprobe->act->tsecond != NULL)
                alldim += aprobe->act->tsecond->dim;
            tprobe->enc = (point *)malloc(alldim*sizeof(point));

            t_node *data_ref[MAXQUERY];
            int fid = 1, uid = 0;


            while (aprobe != NULL){
                
                int ndone;
                int complete;
                bookmark = 0;

                while (bookmark < MAXQUERY && aprobe != NULL){

                    ndone = bookmark;
                    merge (aprobe->father, &fid, aprobe->uncle, &uid, accel_data, accel_state, &bookmark);
                    ndone = bookmark - ndone;

                    if (fid + uid < alldim)
                        complete = 0;
                    else{
                        complete = 1;
                        fid = 1;
                        uid = 0;
                    }

                    //auto opt_start = std::chrono::steady_clock::now();

                    /*tricord accel_data_filler;
                    accel_data_filler.x1 = tprobe->t.p1.x;
                    accel_data_filler.y1 = tprobe->t.p1.y;
                    accel_data_filler.x2 = tprobe->t.p2.x;
                    accel_data_filler.y2 = tprobe->t.p2.y;
                    accel_data_filler.x3 = tprobe->t.p3.x;
                    accel_data_filler.y3 = tprobe->t.p3.y;*/

                    for (i = 1; i <= ndone; i++){
						data_ref[bookmark - i] = tprobe;
						accel_data[(bookmark - i)*8 + 2] = tprobe->t.p1.x;
						accel_data[(bookmark - i)*8 + 3] = tprobe->t.p1.y;
						accel_data[(bookmark - i)*8 + 4] = tprobe->t.p2.x;
						accel_data[(bookmark - i)*8 + 5] = tprobe->t.p2.y;
						accel_data[(bookmark - i)*8 + 6] = tprobe->t.p3.x;
						accel_data[(bookmark - i)*8 + 7] = tprobe->t.p3.y;
                    }

                    //auto opt_end = std::chrono::steady_clock::now();
					//opt_time += std::chrono::duration_cast<std::chrono::nanoseconds>(opt_end - opt_start).count();


                    if (complete){
                        aprobe = aprobe->next;
                        if (aprobe != NULL){

                        	push_t (&tprobe, aprobe->act->seg.a, aprobe->act->seg.b, aprobe->father->enc[0]);

                            alldim = 0;
                            if(aprobe->act->tfirst != NULL)
                                alldim += aprobe->act->tfirst->dim;
                            if(aprobe->act->tsecond != NULL)
                                alldim += aprobe->act->tsecond->dim;
                            tprobe->enc = (point *)malloc(alldim*sizeof(point));
                        }
                    }
                }

                if (bookmark == 0)
                	continue;

                if (bookmark % 2 == 1){
                    accel_state[bookmark] = -1;
                	bookmark ++;
                }

                /*printf("\n");
                for (i = 0; i<bookmark; i++){
                    printf("%2d ",accel_state[i]);
                }
                printf("\n");*/

                cl_event evts[5];

            	OCL_CHECK (err, err = clSetKernelArg(krnl_incircle, 3, sizeof(int), &bookmark));

            	OCL_CHECK (err, err = clEnqueueWriteBuffer(q, data_buf, CL_FALSE, 0, 8*bookmark*sizeof(float), accel_data, 0, NULL, evts));
				OCL_CHECK (err, err = clEnqueueWriteBuffer(q, state_buf, CL_FALSE, 0, bookmark*sizeof(int), accel_state, 0, NULL, evts+1));
				OCL_CHECK (err, err = clFinish(q));

				//sym_accel_in_circle(accel_data, accel_state, sym_accel_result);
				OCL_CHECK (err, err = clEnqueueTask(q, krnl_incircle, 0, NULL, (evts + 2)));
				OCL_CHECK (err, err = clFinish(q));

				OCL_CHECK (err, err = clEnqueueReadBuffer(q, result_buf, CL_FALSE, 0, bookmark*sizeof(int), accel_result, 0, NULL, (evts + 3)));
				OCL_CHECK (err, err = clFinish(q));

				/*printf("\nBookmark: %d\n", bookmark);
				for (i = 0; i<bookmark; i++){
					print_t_id(data_ref[i]->t);
					printf("% 2d\n",accel_result[i]);
				}*/

                /*for (i = 0; i<bookmark; i++){
                    printf("%2d ",sym_accel_result[i]);
                }
                printf("\n");*/

                #ifdef DEBUG
                    printf("Prima\n");
                    print_tris_id(tprobe);
                #endif

                for (int i = 0; i < bookmark; i++){
                	if(accel_result[i] != -1){
                		data_ref[i]->enc[data_ref[i]->dim] = pts[accel_result[i]];
                		data_ref[i]->dim ++;
                	}
                }

                //print_tris_id(tprobe);

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
    clReleaseMemObject(result_buf);

	#ifdef VALDEB
	    CALLGRIND_STOP_INSTRUMENTATION;
   	 	CALLGRIND_DUMP_STATS;
	#endif
    
	time_end = std::chrono::steady_clock::now();
	int delaunay_time = std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start).count();

    time_start = std::chrono::steady_clock::now();

    print_result (tris, n_pts);

    time_end = std::chrono::steady_clock::now();
	int output_time = std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start).count();

    // printf("Init time: %d ms\n", init_time);
    printf("Delaunay time: %d ms\n", delaunay_time);
    // printf("Writing output: %d ms\n\n", output_time);

    //printf("Opt time: %d ms\n", opt_time/1000000);

    #ifdef LOG
        printf ("Number of rounds: %d\n", roundcount);
    #endif

    return 0;
}

void merge (t_node *father, int *infid, t_node *uncle, int *inuid, float accel_data[], int accel_state[], int *inbookmark){

    // We discard the fist point of father since is a vertex of son.
    // If there's no uncle we just test the father's vertices and add them to son
    point *fenc = father->enc;
    int fid = *infid;
    int uid = *inuid;
    int bookmark = *inbookmark;
    
    if (uncle == NULL){
        for(; fid < father->dim && bookmark < MAXQUERY; fid++){
            accel_state[bookmark] = fenc[fid].id;
            accel_data[bookmark*8] = fenc[fid].x;
            accel_data[bookmark*8 + 1] = fenc[fid].y;
            (bookmark) ++;
        }
    }
    else{

        // If uncle exists we merge its and father's encroaching point lists
        // and add it to son, while maintaining the order of the ids
        point *uenc = uncle->enc;
        while ((fid < father->dim || uid < uncle->dim) && bookmark < MAXQUERY){
            
            if (uid == uncle->dim || (fid < father->dim && fenc[fid].id < uenc[uid].id)){
                accel_state[bookmark] = fenc[fid].id;
                accel_data[bookmark*8] = fenc[fid].x;
                accel_data[bookmark*8 + 1] = fenc[fid].y;
                bookmark ++;
                fid ++;
            }
            
            else if (fid == father->dim || (uid < uncle->dim && uenc[uid].id < fenc[fid].id)){
                accel_state[bookmark] = uenc[uid].id;
                accel_data[bookmark*8] = uenc[uid].x;
                accel_data[bookmark*8 + 1] = uenc[uid].y;
                bookmark ++;
                uid ++;
            }

            else if (fid < father->dim && uid < uncle->dim && fenc[fid].id == uenc[uid].id){
                accel_state[bookmark] = fenc[fid].id;
                accel_data[bookmark*8] = fenc[fid].x;
                accel_data[bookmark*8 + 1] = fenc[fid].y;
                (bookmark) ++;
                (uid) ++;
                (fid) ++;
            }
        }
    }

    *infid = fid;
    *inuid = uid;
    *inbookmark = bookmark;
    return;
}


int sym_in_circle(float *data){

    float xda = data[2] - data[0];
    float xdb = data[4] - data[0];
    float xdc = data[6] - data[0];
    float yda = data[3] - data[1];
    float ydb = data[5] - data[1];
    float ydc = data[7] - data[1];
    float da2da2 = xda*xda + yda*yda;
    float db2db2 = xdb*xdb + ydb*ydb;
    float dc2dc2 = xdc*xdc + ydc*ydc;

    // calcolo i minimi complementari
    float min1 = xdb*ydc - xdc*ydb;
    float min2 = xda*ydc - xdc*yda;
    float min3 = xda*ydb - xdb*yda;

    float det = da2da2*min1 - db2db2*min2 + dc2dc2*min3;
    return (det>0);
}

void sym_accel_in_circle(float *indata, int *instate, int *outstate){

    float data[MAXQUERY][8];
    int state[MAXQUERY];

    memcpy(data[0], indata, 8*MAXQUERY*sizeof(float));
    memcpy(state, instate, MAXQUERY*sizeof(int));

    int i;

    for (i = 0; i < MAXQUERY; i++){
        if (state[i] != -1 && !sym_in_circle(data[i]))
            state[i] = -1;
    }
    
    memcpy(outstate, state, MAXQUERY*sizeof(int));
    
	return;
}
