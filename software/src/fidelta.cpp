#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <cstring>

#ifdef VALDEB
	#include <valgrind/callgrind.h>
#endif

#include "types.h"
#include "display.h"

#ifndef PTSLIM
    #define PTSLIM 300000
#endif

// c-sim of accelerated functions
int in_circle(float *innerdata, float *son);
void accel_in_circle(float *indata, int *instate, float *inson, int *inmaxquery);

// Merges the enc arrays of father and uncle, copying the resulting IDs in accel_state and their coordinates in accel_data
int merge (t_node *father, t_node *uncle, float accel_data[][2], int accel_state[]);

int main(int argc, char *argv[])
{
    int rmode, n_pts, i;
    float max_cor;

    //node: file where we store generated points/a copy of those in input
    //extnode: eventual input point file
    FILE *node, *extnode; 

    //start init time
    clock_t a = clock();

    // reads command line arguments, returns selected mode (random or from file), starts initializing node file
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

    t_node *tris = nullptr;

    // Simple array of points which we then fill with those in the node file
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
    // and their (up to two) adjacent triangles
    // We start by adding the three artificial bounding segments

    segment *segs = nullptr;
    push_seg(&segs, tris->p1, tris->p2, tris);
    push_seg(&segs, tris->p2, tris->p3, tris);
    push_seg(&segs, tris->p3, tris->p1, tris);

    // Initialization of the active segments list acts.
    // Each element of acts represents a future triangle generation.
    // The triangle it will generate is made by linking the segment acts->act
    // to the first encroached point (in order of id) of acts->father.
    // Acts is filled in rounds. Within each round all elements are independent, 
    // so all merge and inCircle calls could be processed simultaneously
    // When a round ends nextround is loaded in acts.

    act_node *acts = nullptr;
    act_node *nextround = nullptr;

    // The first three active segments are added, their father being the bounding triangle

    push_act (&nextround, segs, tris->p1, tris->p2, tris);
    push_act (&nextround, segs, tris->p2, tris->p3, tris);
    push_act (&nextround, segs, tris->p3, tris->p1, tris);

    #ifdef LOG
        int roundcount = 0, roundwidth = 0;
    #endif
        int deleted_t = 0;

    int *accel_state = (int *) malloc((PTSLIM + 10) * sizeof(int));
    float (*accel_data)[2] = (float (*)[2]) malloc((PTSLIM + 10) * sizeof(*accel_data));
    float accel_son[6];

    // end init timing, start delaunay construction timing
    a = clock() - a; 
    clock_t t = clock();

	#ifdef VALDEB
    	CALLGRIND_START_INSTRUMENTATION;
	#endif

    // Initialization is over, we start timing the construction
	// The algorithm continues until there are no more active segments

    while(acts != nullptr || nextround != nullptr){

        // loads next round
        if (acts == nullptr){
            #ifdef LOG
                printf("FINISHED ROUND %d [witdh=%d]\n\n", roundcount, roundwidth);
                roundcount++;
                printf("LOADING ROUND %d\n", roundcount);
                roundwidth = 0;
            #endif

            acts = nextround;
            nextround = nullptr;

            act_node *aprobe = acts;
            t_node *tprobe = tris;

            while (aprobe != nullptr){

                // Generate new triangle
                push_t (&tprobe, aprobe->seg->a, aprobe->seg->b, aprobe->father->enc[0]);

                // Allocate its enc array.
                // It can't be bigger then the sum of its parent's arrays, so we use that as an upper bound
                int alldim = 0;
                if(aprobe->seg->tfirst != nullptr)
                    alldim += aprobe->seg->tfirst->dim;
                if(aprobe->seg->tsecond != nullptr)
                    alldim += aprobe->seg->tsecond->dim;
                tprobe->enc = (point *) malloc(alldim*sizeof(point));

                int maxquery = merge (aprobe->father, aprobe->uncle, accel_data, accel_state);

                for(i = maxquery; i < maxquery + 7; i ++){
                    accel_state[i] = -1;
                }

                accel_son[0] = tprobe->p1.x;
                accel_son[1] = tprobe->p1.y;
                accel_son[2] = tprobe->p2.x;
                accel_son[3] = tprobe->p2.y;
                accel_son[4] = tprobe->p3.x;
                accel_son[5] = tprobe->p3.y;

                /*#ifdef DEBUG
                    printf("\n\nNew triangle: %d %d %d\n ", tprobe->p1.id, tprobe->p2.id, tprobe->p3.id);
                    for (i = 0; i<maxquery; i++){
                        printf("%2d ",accel_state[i]);
                    }
                    printf("\nv\n ");
                #endif*/

                accel_in_circle (accel_data[0], accel_state, accel_son, &maxquery);

                #ifdef DEBUG
                    printf("New triangle: (%d %d %d) -> ", tprobe->p1.id, tprobe->p2.id, tprobe->p3.id);
                    for (i = 0; i < maxquery; i++){
                        if (accel_state[i] >= 0)
                            printf("%2d ",accel_state[i]);
                    }
                    printf("\n");
                #endif

                for (i = 0; i < maxquery; i++){
                    if (accel_state[i] != -1){
                        tprobe->enc[tprobe->dim] = pts[accel_state[i]];
                        tprobe->dim ++;
                    }
                }

                aprobe = aprobe->next;
            }

            #ifdef DEBUG
                print_tris_id(tprobe);
                printf("\nSTART ROUND %d\n", roundcount);
            #endif
        }

        #ifdef LOG
            roundwidth++;
        #endif
        #ifdef DEBUG
            printf("\nActs:\n");
            print_acts_id(acts);
            printf("\nActive: (%d %d)\n", acts->seg->a.id, acts->seg->b.id);
        #endif
        
        // All new triangles of the round are in tris.
        // Now the rest of the process consists in going through each of them,
        // updating the segs hash table and finding the next active segments.
        // We take the next one:

        tris = tris->prev;

        #ifdef DEBUG
            printf ("\nTris:\n");
            print_tris_id(tris);
        #endif
        
        // We add one of its segment to segs.
        // If the segment already existed, on its other side there's already a triangle.
        // In that case we find which one, beteween the new neighboring triangles, has the lowest-id point.
        // That triangle will be deleted in the next round, so we add it to nextround along with the segment.
        // Else, if their lowest-id point is the same, no triangle will be deleted, we do nothing.

        segment *active = acts->seg;
        t_node *father = acts->father;
        t_node *uncle = acts->uncle;
        assert (active->tfirst == father || active->tsecond == father);

        t_node *encroached;
        encroached = push_seg (&segs, active->a, father->enc[0], tris);
        
        if (encroached != nullptr)
            push_act (&nextround, segs, active->a, father->enc[0], encroached);

        // Same as before, but considering the second new segment
        encroached = push_seg (&segs, active->b, father->enc[0], tris);
        
        if (encroached != nullptr)
            push_act (&nextround, segs, active->b, father->enc[0], encroached);
        
        #ifdef DEBUG
            printf("\n Elements in segs:\n");
            print_segs_id(segs);
        #endif

        // Now we check if act is still active even after having replaced it's father with son.
		// If uncle is null we're on the border.
        // We update its only adjacent triangle, and if the new one has still enc pts we add it to nextround.

        if(uncle == nullptr){
            active->tfirst = tris;
            if (tris->dim != 0){
                push_act (&nextround, segs, active->a, active->b, tris);
            }
        }

        // If uncle isn't null we find which triangle of the two adjecent is the father and replace it,
        // then we check if the common segment is active, on both sides
        else{

            // Checking who's the father and replacing it with the son
            if (active->tfirst == father){
                active->tfirst = tris;
            }
            else{
                active->tsecond = tris;
            }

            // Checking if the first adjecent triangle added in segs must die in the next round.
            if (active->tfirst->dim != 0 &&
               (active->tsecond->dim == 0 || active->tfirst->enc[0].id  <  active->tsecond->enc[0].id)){
                
                push_act (&nextround, segs, active->a, active->b, active->tfirst);
            }

            // Same thing but with the second triangle
            else if (active->tsecond->dim != 0 &&
                    (active->tfirst->dim == 0 || active->tsecond->enc[0].id  <  active->tfirst->enc[0].id)){

                push_act (&nextround, segs, active->a, active->b, active->tsecond);
            }
        }

        #ifdef DEBUG
            printf("\nNextround:\n");
            print_acts_id(nextround);
        #endif

        segment *left_s, *right_s;

        int f_opp_id = father->opposite(active->a, active->b).id;
        idxkey left_idx(active->a.id, f_opp_id);
        idxkey right_idx(active->b.id, f_opp_id);
        HASH_FIND(hh, segs, &left_idx, sizeof(idxkey), left_s);
        HASH_FIND(hh, segs, &right_idx, sizeof(idxkey), right_s);

        t_node *left_t, *right_t;
        left_t = left_s->opposite(father);
        right_t = right_s->opposite(father);

        //We update how many times the father has been replaced
        father->lives--;
        if (left_t != nullptr && left_t->enc[0].id == father->enc[0].id) {
            father->lives--;
        }
        else
            left_t = nullptr;
        if (right_t != nullptr && right_t->enc[0].id == father->enc[0].id)
            father->lives--;
        else
            right_t = nullptr;

        //If all three sides replaced it it is deleted;
        if (father->lives <= 0) {
            if (left_t != nullptr) {
                left_t->lives--;
                left_s->remove(&segs, father);
            }
            if (right_t != nullptr) {
                right_t->lives--;
                right_s->remove(&segs, father);
            }
            pop_t(father, &tris);
            deleted_t ++;
        }

		// We pass to the next active segment
        pop_act (&acts);
    }

    #ifdef DEBUG
        print_tris_id(tris);
    #endif

    // End of triangulation, starting output

	#ifdef VALDEB
	    CALLGRIND_STOP_INSTRUMENTATION;
   	 	CALLGRIND_DUMP_STATS;
	#endif
    
	t += clock() - t;
    clock_t o = clock();

    // Prints on result.ele file all the triangles generated, minus those connected to the start bounding triangle,
    // since it wasn't part of the original triangulation
    print_result (tris, n_pts);

    o = clock() - o;
    
    float del_time = 1000*((float)t)/CLOCKS_PER_SEC;
    float ini_time = 1000*((float)a)/CLOCKS_PER_SEC;
    float out_time = 1000*((float)o)/CLOCKS_PER_SEC;

	// Print time results
    printf("Init time: %d ms\n", (int)ini_time);
    printf("Delaunay time: %d ms\n", (int)del_time);
    printf("Writing output: %d ms\n", (int)out_time);

    #ifdef LOG
        printf ("Number of rounds: %d\n", roundcount);
    #endif
    printf ("Deleted triangles: %d\n", deleted_t);

    return 0;
}

int merge (t_node *father, t_node *uncle, float accel_data[][2], int accel_state[]){

    // We discard the fist point of father since is a vertex of son.
    // If there's no uncle we just test the father's vertices and add them to son
    point *fenc = father->enc;
    int fid = 1;
    int uid = 0;
    int sid = 0;

    if (uncle == nullptr){
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
