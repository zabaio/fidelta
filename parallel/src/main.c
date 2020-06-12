#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

#include "types.h"
#include "display.h"

#ifndef MAXQUERY
    #define MAXQUERY 30
#endif
#ifndef PTSLIM
    #define PTSLIM 300000
#endif


int in_circle(float *data){

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

void accel_in_circle(float *indata, int *instate){

    float data[MAXQUERY][8];
    int state[MAXQUERY];

    memcpy(data[0], indata, 8*MAXQUERY*sizeof(float));
    memcpy(state, instate, MAXQUERY*sizeof(int));

    int i;

    for (i = 0; i < MAXQUERY; i++){
        if (state[i] != -1 && !in_circle(data[i]))
            state[i] = -1;
    }
    
    memcpy(indata, data[0], 8*MAXQUERY*sizeof(float));
    memcpy(instate, state, MAXQUERY*sizeof(int));
    
	return;
}

// Creates and adds the list of points encroaching triangle "son":
// a point p is added if it's encroaching "father" or "uncle" AND if in_circle (son, p) is true
void merge (t_node *father, int *fid, t_node *uncle, int *uid, float accel_data[MAXQUERY][8], int accel_state[MAXQUERY], int *bookmark);

int main(int argc, char *argv[])
{
    int rmode = 0, n_pts, i;
    float max_cor = 0;
    FILE *node, *ele, *extnode;
    rmode = init (argc, argv, &node, &ele, &extnode, &n_pts, &max_cor);
    
    clock_t a = clock();
    point prov;

    if(rmode){

        // In random mode we generate a random square cloud of points 
        // whose max coordinate has absolute value max_cor.
        // We then write in result.node three points that wrap the cloud
        // and then all the other points

        fprintf (node, "%d 2 0 0\n", n_pts+3);
        srand(time(NULL));

        set_pt(&prov, -max_cor*3, -max_cor*3, 0);
        fprint_pt (node, &prov);
        set_pt(&prov, 0, max_cor*3, 1);
        fprint_pt (node, &prov);
        set_pt(&prov, max_cor*3, 0, 2);
        fprint_pt (node, &prov);        
        #ifdef LOG
            printf("Mock point 0 = "PT_FRMT"\n", (float)-max_cor*3, (float)-max_cor*3);
            printf("Mock point 1 = "PT_FRMT"\n", (float)0, (float)max_cor*3);
            printf("Mock point 2 = "PT_FRMT"\n", (float)max_cor*3, (float)0);
        #endif

        for(i = 3; i < n_pts+3; i++){
            prov.x = (float)rand()/(float)(RAND_MAX/(max_cor*2))-max_cor;
            prov.y = (float)rand()/(float)(RAND_MAX/(max_cor*2))-max_cor;
            prov.id = i;
            fprint_pt (node, &prov);
            #ifdef LOG
                printf("Point");
                print_pt_id(prov);
                printf("= ");
                print_pt(prov);
            #endif
        }
    }
    else{

        // From file mode first scans the given .node file, checking for formatting errors
        // and finding the max coordinate of the points listed.
        // After that we write in result.node the three points wrapping all input points,
        // which we then copy as well

        if(fscanf (extnode, "%d %*[^\n]\n", &n_pts) == EOF){
            printf("ERROR: Input file is empty\n");
            man(0);
            exit(EXIT_FAILURE);
        }

        for (i = 0; i < n_pts; i++){
            if (fscanf (extnode, "%d %f %f \n", &prov.id, &prov.x, &prov.y) != 3 || prov.id != i){
                printf("ERROR: Error in input file format at line %d\n", i+2);
                man(1);
                exit(EXIT_FAILURE);
            }
            if (prov.x > max_cor) max_cor = prov.x;
            if (-prov.x > max_cor) max_cor = -prov.x;
            if (prov.y > max_cor) max_cor = prov.y;
            if (-prov.y > max_cor) max_cor = -prov.y;
        }
        
        fprintf (node, "%d 2 0 0\n", n_pts+3);
        set_pt(&prov, -max_cor*3, -max_cor*3, 0);
        fprint_pt (node, &prov);
        set_pt(&prov, 0, max_cor*3, 1);
        fprint_pt (node, &prov);
        set_pt(&prov, max_cor*3, 0, 2);
        fprint_pt (node, &prov);
    
        fseek (extnode, 0, SEEK_SET);
        fscanf (extnode, "%*[^\n]\n");
        for (i = 0; i < n_pts; i++){
            fscanf (extnode, "%d %f %f \n", &prov.id, &prov.x, &prov.y);
            prov.id += 3;
            fprint_pt (node, &prov);
        }

        fclose (extnode);
    }
    
    // Now "node" stores all the points needed.
    // We create tris, the core structure of the algorithm.
    // It is a list of triangles, each one with the list of points that encroach on it, 
    // meaning that they are inside the triangle's circumcircle
    // The first three points in result.node form a triangle bounding all other points, which we add to tris.
    // Then, with push_ptint, we add every point to the list of points encroaching on it.

    point pts[PTSLIM + 3];
    t_node *tris = NULL;
    
    fseek(node, 0, SEEK_SET);
    fscanf (node, "%*[^\n]\n");
    for (i = 0; i < 3; i++){
        fscanf (node, "%d %f %f \n", &pts[i].id, &pts[i].x, &pts[i].y);       
    }
    push_t(&tris, pts[0], pts[1], pts[2]);
    tris->dim = n_pts;
    tris->enc = malloc(tris->dim*sizeof(point));
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
    
    // Initialization is over, we start timing the construction


    #ifdef LOG
        int roundcount = 0, roundwidth = 0;
    #endif
    a = clock() - a;
    clock_t t = clock();
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
            tprobe->enc = malloc(alldim*sizeof(point));
            
            int fid = 1, uid = 0;
            while (aprobe != NULL){
                
                float accel_data[MAXQUERY][8];
                int accel_state[MAXQUERY];
                int bookmark = 0;
                int ndone;
                int complete;
                t_node *data_ref[MAXQUERY];

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

                    for (i = 1; i <= ndone; i++){
                        data_ref[bookmark - i] = tprobe;
                        accel_data[bookmark - i][2] = tprobe->t.p1.x;
                        accel_data[bookmark - i][3] = tprobe->t.p1.y;
                        accel_data[bookmark - i][4] = tprobe->t.p2.x;
                        accel_data[bookmark - i][5] = tprobe->t.p2.y;
                        accel_data[bookmark - i][6] = tprobe->t.p3.x;
                        accel_data[bookmark - i][7] = tprobe->t.p3.y;
                    }

                    if (complete){
                        aprobe = aprobe->next;
                        if (aprobe != NULL){
                            push_t (&tprobe, aprobe->act->seg.a, aprobe->act->seg.b, aprobe->father->enc[0]);
                        
                            alldim = 0;
                            if(aprobe->act->tfirst != NULL)
                                alldim += aprobe->act->tfirst->dim;
                            if(aprobe->act->tsecond != NULL)
                                alldim += aprobe->act->tsecond->dim;
                            tprobe->enc = malloc(alldim*sizeof(point));
                        }
                    }

                }

                for(; bookmark < MAXQUERY; bookmark ++){
                    accel_state[bookmark] = -1;
                }

                #ifdef DEBUG
                    for (i = 0; i<MAXQUERY; i++){
                        printf("%2d -> ",accel_state[i]);
                        int p;
                        for (p = 0; p < 8; p ++){
                            printf("%6.2f ",accel_data[i][p]);
                        }
                        printf("\n");
                    }
                    printf("v\n");
                #endif

                accel_in_circle (accel_data[0], accel_state);
    
                #ifdef DEBUG                
                    for (i = 0; i<MAXQUERY; i++){
                        printf("%2d -> ",accel_state[i]);
                        int p;
                        for (p = 0; p < 8; p ++){
                            printf("%6.2f ",accel_data[i][p]);
                        }
                        printf("\n");
                    }
                    printf("\n");

                    printf("Prima\n");
                    print_tris_id(tprobe);
                #endif

                for (i = 0; i < MAXQUERY; i++){
                    if (accel_state[i] != -1){
                        data_ref[i]->enc[data_ref[i]->dim] = pts[accel_state[i]];
                        data_ref[i]->dim ++;
                    }
                }

                #ifdef DEBUG
                    printf("Dopo\n");
                    print_tris_id(tprobe);
                #endif
            
                
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

    // Output section
    // soldim is the dimention of the triangulation, tridim of the structure tris
    // We scan through tris, every triangle who hasn't encroaching points
    // is part of the triangulation and we print it

    int soldim=0, tridim=0;
    t_node *tail = tris;
    
    fprintf (ele, "%d 3 0\n", 2*(n_pts + 3) - 5);
    while(tail != NULL){
        if(tail->dim == 0){
            fprintf (ele, "%d ", soldim);
            fprint_t (ele, &tail->t);
            soldim++;
        } 
        tridim++;
        tail = tail->next;
    }
  
    fclose (ele);

    t += clock() - t;
    float time_taken = 1000*((float)t)/CLOCKS_PER_SEC;
    float ini_time = 1000*((float)a)/CLOCKS_PER_SEC;

    #ifdef DEBUG
        print_tris_id(tris);
        printf("Total number of generated triangles: %zu B x %d\n",sizeof(t_node), tridim);
    #endif
    #ifdef LOG
        printf ("Number of rounds: %d\n", roundcount);
    #endif
    
    printf("Init time: %d ms\n", (int)ini_time);
    printf("Delaunay time: %d ms\n", (int)time_taken);

    // From the theory we know that a correct triangulation must have 2*(points)-5 triangles.
    // Note that we added the three bounding points
    if (soldim == 2*(n_pts +3 ) - 5)    
        printf ("Generated %d triangles: Correct\n", soldim);
    else
        printf ("Generated %d triangles: Incorrect\n", soldim);


    int b =MAXQUERY;
    printf ("%d\n", b);
    return 0;
}

void merge (t_node *father, int *infid, t_node *uncle, int *inuid, float accel_data[MAXQUERY][8], int accel_state[MAXQUERY], int *inbookmark){

    // We discard the fist point of father since is a vertex of son.
    // If there's no uncle we just test the father's vertices and add them to son
    point *fenc = father->enc;
    int fid = *infid;
    int uid = *inuid;
    int bookmark = *inbookmark;
    
    if (uncle == NULL){
        for(; fid < father->dim && bookmark < MAXQUERY; fid++){
            accel_state[bookmark] = fenc[fid].id;
            accel_data[bookmark][0] = fenc[fid].x;
            accel_data[bookmark][1] = fenc[fid].y;
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
                accel_data[bookmark][0] = fenc[fid].x;
                accel_data[bookmark][1] = fenc[fid].y;
                bookmark ++;
                fid ++;
            }
            
            else if (fid == father->dim || (uid < uncle->dim && uenc[uid].id < fenc[fid].id)){
                accel_state[bookmark] = uenc[uid].id;
                accel_data[bookmark][0] = uenc[uid].x;
                accel_data[bookmark][1] = uenc[uid].y;
                bookmark ++;
                uid ++;
            }

            else if (fid < father->dim && uid < uncle->dim && fenc[fid].id == uenc[uid].id){
                accel_state[bookmark] = fenc[fid].id;
                accel_data[bookmark][0] = fenc[fid].x;
                accel_data[bookmark][1] = fenc[fid].y;
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