#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>

#include "types.h"
#include "display.h"

#define DEBUG
#ifdef DEBUG
    int is_general_position(point *pts,int n_pts);
#endif

#define N_PTS 10
#define MAX_COR 100

// checks if point d is inside the circumcircle of t
int same_triangle (triangle *t1, triangle *t2);
int in_circle (triangle *t, point *d);
void merge (t_node *father, t_node *son, t_node *uncle);

int main()
{
    // Initialization of the input point set.
    // Negative-index points represent the starting big triangle
    int i;
    point pts[N_PTS];
    point bounding[3];

    set_pt(&bounding[2], MAX_COR*3, 0,-1);
    set_pt(&bounding[1], 0, MAX_COR*3,-2);
    set_pt(&bounding[0], -MAX_COR*3, -MAX_COR*3,-3);

    printf("Generated Points:\n");
    srand(time(NULL));
    for(i = 0; i<N_PTS; i++){
        pts[i].x = (double)rand()/(double)(RAND_MAX/(MAX_COR*2))-MAX_COR;
        pts[i].y = (double)rand()/(double)(RAND_MAX/(MAX_COR*2))-MAX_COR;
        print_pt(pts[i]);
    }

    #ifdef DEBUG
        if(!is_general_position(pts,N_PTS)) {printf("Init error - Non general position point set\n"); return 0;}
    #endif

    // Initialization of the triangle list
    // Insertion of the starting triangle
    t_node *tris = NULL;
    push_t(&tris, bounding[0], bounding[1], bounding[2]);

    for(i=0; i<N_PTS; i++){
        push_ptint(tris, pts[i]);
    }

    print_tris(tris);

    // Initialization of the hash table
    // segs_add wants: segs address, pt 1, pt 2, make_value(tri 1 address, tri 2 address)
    // segs_find wants: segs, pt 1, pt2
    // segs_delete wants:

    record_segs *segs = NULL;
    
    segs_add (&segs, tris->t.p1, tris->t.p2, tris);
    segs_add (&segs, tris->t.p2, tris->t.p3, tris);
    segs_add (&segs, tris->t.p3, tris->t.p1, tris);

    print_hash(segs);

    // Initialization of the active segments list
    act_node *acts = NULL;
    act_node *nextround = NULL;

    push_act (&acts, segs, tris->t.p1, tris->t.p2, tris);
    push_act (&acts, segs, tris->t.p2, tris->t.p3, tris);
    push_act (&acts, segs, tris->t.p3, tris->t.p1, tris);

    while(acts != NULL || nextround != NULL){
        // load next round
        if (acts == NULL){
            acts = nextround;
            nextround = NULL;
        }

        t_node *encroached = NULL;

        // the son gets added to tris
        push_t (&tris, acts->act->key.a, acts->act->key.b, acts->father->fenc->pt);
        
        // son is populated by its encroaching points
        merge (acts->father, tris, acts->uncle);
        
        // we add a-pt to segs
        // encroached gets the triangle encroached in the relation across a-pt and we add it to the next round
        encroached = segs_add (&segs, acts->act->key.a, acts->father->fenc->pt, tris);
        if (encroached != NULL){
            push_act (&nextround, segs, acts->act->key.a, acts->father->fenc->pt, encroached);
        }

        // same as before with b-pt
        encroached = segs_add (&segs, acts->act->key.b, acts->father->fenc->pt, tris);
        if (encroached != NULL){
            push_act (&nextround, segs, acts->act->key.b, acts->father->fenc->pt, encroached);
        }
        
        // if uncle is null we're on the border. ab has only tfirst filled, we update it and if there are still enc pts we add it so nextround
        assert (acts->act->tfirst == acts->father || acts->act->tsecond == acts->father);
        if(acts->uncle == NULL){
            acts->act->tfirst = tris;
            if (tris->fenc != NULL){
                push_act (&nextround, segs, acts->act->key.a, acts->act->key.b, tris);
            }
        }
        // if uncle isn't null we find which triangle is father in segs, then we check if ab is active, both sides
        else{
            if (acts->act->tfirst == acts->father){
                acts->act->tfirst = tris;
            }
            else if (acts->act->tsecond == acts->father){ // if the assertion is true this check is superfluous
                acts->act->tsecond = tris;
            }

            if ((acts->act->tfirst->fenc == NULL && acts->act->tsecond->fenc != NULL) ||
                acts->act->tfirst->fenc->pt.id  <  acts->act->tsecond->fenc->pt.id){
                
                push_act (&nextround, segs, acts->act->key.a, acts->act->key.b, acts->act->tfirst);
            
            }

            else if ((acts->act->tsecond->fenc == NULL && acts->act->tfirst->fenc != NULL) ||
                      acts->act->tsecond->fenc->pt.id  <  acts->act->tfirst->fenc->pt.id){

                push_act (&nextround, segs, acts->act->key.a, acts->act->key.b, acts->act->tsecond);
            
            }
        }

        pop_act (&acts);

    }
    return 0;
}

int same_triangle(triangle *t1, triangle *t2){
    if (t1->p1.x != t2->p1.x) return 0;
    if (t1->p1.y != t2->p1.y) return 0;
    if (t1->p2.x != t2->p2.x) return 0;
    if (t1->p2.x != t2->p2.y) return 0;
    if (t1->p3.x != t2->p3.x) return 0;
    if (t1->p3.x != t2->p3.y) return 0;
    return 1;
}

int in_circle(triangle *t, point *d){
    
    double xda = t->p1.x - d->x;
    double xdb = t->p2.x - d->x;
    double xdc = t->p2.x - d->x;
    double yda = t->p1.y - d->y;
    double ydb = t->p2.y - d->y;
    double ydc = t->p2.y - d->y;
    double da2da2 = xda*xda + yda*yda;
    double db2db2 = xdb*xdb + ydb*ydb;
    double dc2dc2 = xdc*xdc + ydc*ydc;

    // calcolo i minimi complementari
    double min1 = xdb*ydc - xdc*ydb;
    double min2 = xda*ydc - xdc*yda;
    double min3 = xda*ydb - xdb*yda;

    double det = da2da2*min1 - db2db2*min2 + dc2dc2*min3;
    return (det>0);
}

void merge (t_node *father, t_node *son, t_node *uncle){
    assert (father != NULL);
    pt_node *fprobe = father->fenc;
    if (uncle == NULL){
        while (fprobe != NULL){
            if (in_circle (&father->t, &fprobe->pt))
                push_ptint (son, fprobe->pt);
            fprobe = fprobe->next;
        }
    }
    else{
        pt_node *uprobe = uncle->fenc;
        
    }
    return;
}

#ifdef DEBUG
    int is_general_position(point *pts,int n_pts){
        int i,j,k,l,cyc=0;
        double d,ux,uy,r;
        for(i=0;i<n_pts;i++){
            for(j=i+1;j<n_pts;j++){
                for(k=j+1;k<n_pts;k++){
                    d=2*(pts[i].x*(pts[j].y-pts[k].y)
                        +pts[j].x*(pts[k].y-pts[i].y)
                        +pts[k].x*(pts[i].y-pts[j].y));
                    ux=((double)1/d)*((pts[i].x*pts[i].x+pts[i].y*pts[i].y)*(pts[j].y-pts[k].y)
                                    +(pts[j].x*pts[j].x+pts[j].y*pts[j].y)*(pts[k].y-pts[i].y)
                                    +(pts[k].x*pts[k].x+pts[k].y*pts[k].y)*(pts[i].y-pts[j].y));
                    uy=((double)1/d)*((pts[i].x*pts[i].x+pts[i].y*pts[i].y)*(pts[k].x-pts[j].x)
                                    +(pts[j].x*pts[j].x+pts[j].y*pts[j].y)*(pts[i].x-pts[k].x)
                                    +(pts[k].x*pts[k].x+pts[k].y*pts[k].y)*(pts[j].x-pts[i].x));
                    r=sqrt(pow(pts[i].x-ux,2)+pow(pts[i].y-uy,2));
                    for(l=k+1;l<n_pts;l++){
                        if(pow(pts[l].x-ux,2)+pow(pts[l].y-uy,2)-pow(r,2)==0){
                            cyc++;
                            // printf("\n");
                            // print_pt(pts[i]);
                            // print_pt(pts[j]);
                            // print_pt(pts[k]);
                            // print_pt(pts[l]);
                            // printf("\n");
                        }
                    }
                }
            }
        }
        // printf("%d cerchi\n",cyc);
        return !cyc;
    }
#endif