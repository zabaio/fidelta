#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

#include <valgrind/callgrind.h>

#include "types.h"
#include "display.h"

#ifndef PTSLIM
    #define PTSLIM 300000
#endif

// c-sim of accelerated functions
int in_circle(float *innerdata, float *son);
void accel_in_circle(float *indata, int *instate, float *inson, int *inmaxquery);

// Creates and adds the list of points encroaching triangle "son":
// a point p is added if it's encroaching "father" or "uncle" AND if in_circle (son, p) is true
int merge (t_node *father, t_node *uncle, float accel_data[][2], int accel_state[]);

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

    int *accel_state = (int *) malloc((PTSLIM + 10) * sizeof(int));
    float (*accel_data)[2] = (float (*)[2]) malloc((PTSLIM + 10) * sizeof(*accel_data));
    float accel_son[6];

    // end init timing, start delaunay construction timing
    a = clock() - a; 
    clock_t t = clock();
    CALLGRIND_START_INSTRUMENTATION;

    // Initialization is over, we start timing the construction

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

                int maxquery = merge (aprobe->father, aprobe->uncle, accel_data, accel_state);                

                for(i = maxquery; i < maxquery + 7; i ++){
                    accel_state[i] = -1;
                }

                accel_son[0] = tprobe->t.p1.x;
                accel_son[1] = tprobe->t.p1.y;
                accel_son[2] = tprobe->t.p2.x;
                accel_son[3] = tprobe->t.p2.y;
                accel_son[4] = tprobe->t.p3.x;
                accel_son[5] = tprobe->t.p3.y;

                #ifdef DEBUG
                    printf("\n\n%d %d %d\n ", tprobe->t.p1.id, tprobe->t.p2.id, tprobe->t.p3.id);
                    for (i = 0; i<maxquery; i++){
                        printf("%2d ",accel_state[i]);
                    }
                    printf("\nv\n ");
                #endif                

                accel_in_circle (accel_data[0], accel_state, accel_son, &maxquery);
                

                #ifdef DEBUG
                    for (i = 0; i<maxquery; i++){
                        printf("%2d ",accel_state[i]);
                    }
                    printf("\n");

                    printf("\nPrima:");
                    print_tris_id(tprobe);
                #endif

                for (i = 0; i < maxquery; i++){
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

    // End of triangulation, starting output

    CALLGRIND_STOP_INSTRUMENTATION;
    CALLGRIND_DUMP_STATS;
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

int merge (t_node *father, t_node *uncle, float accel_data[][2], int accel_state[]){

    // We discard the fist point of father since is a vertex of son.
    // If there's no uncle we just test the father's vertices and add them to son
    point *fenc = father->enc;
    int fid = 1;
    int uid = 0;
    int sid = 0;

    if (uncle == NULL){
        for(; fid < father->dim; fid++){
            accel_state[sid] = fenc[fid].id;
            accel_data[sid][0] = fenc[fid].x;
            accel_data[sid][1] = fenc[fid].y;
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
                accel_data[sid][0] = fenc[fid].x;
                accel_data[sid][1] = fenc[fid].y;
                sid ++;
                fid ++;
            }
            
            else if (fid == father->dim || (uid < uncle->dim && uenc[uid].id < fenc[fid].id)){
                accel_state[sid] = uenc[uid].id;
                accel_data[sid][0] = uenc[uid].x;
                accel_data[sid][1] = uenc[uid].y;
                sid ++;
                uid ++;
            }

            else if (fid < father->dim && uid < uncle->dim && fenc[fid].id == uenc[uid].id){
                accel_state[sid] = fenc[fid].id;
                accel_data[sid][0] = fenc[fid].x;
                accel_data[sid][1] = fenc[fid].y;
                sid ++;
                uid ++;
                fid ++;
            }
        }
    }

    return sid;
}

int in_circle(float *innerdata, float *son){

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

void accel_in_circle(float *indata, int *instate, float *inson, int *inmaxquery){

	float data[2];
	int state;
	float son[6];
	int maxquery = *inmaxquery;
	int i;

	memcpy(son, inson, 6*sizeof(float));

	for (i = 0; i < maxquery; i++){

		memcpy(data, indata + 2*i, 2*sizeof(float));
		memcpy(&state, instate + i, sizeof(int));

        if (state != -1 && !in_circle(data, son))
            state = -1;
        
		memcpy(instate + i, &state, sizeof(int));
	}

	return;
}