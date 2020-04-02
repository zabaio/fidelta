#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "types.h"
#include "display.h"

#define DEBUG
#ifdef DEBUG
    int is_general_position(point *pts,int n_pts);
#endif

#define N_PTS 10
#define MAX_COR 100

// checks if point d is inside the circumcircle of t
int in_circle(triangle *t, point *d);

int main()
{
    // Initialization of the input point set.
    // Negative-index points represent the starting big triangle
    int i;
    point pts_unwr[N_PTS+3];
    point *const pts = &pts_unwr[3];

    set_pt(pts-1, MAX_COR*3, 0);
    set_pt(pts-2, 0, MAX_COR*3);
    set_pt(pts-3, -MAX_COR*3, -MAX_COR*3);

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
    triangle t_start;
    set_t(&t_start, pts[-1], pts[-2], pts[-3]);
    push_t(&tris, t_start);

    for(i=0; i<N_PTS; i++){
        push_pt(&tris[0].enc,pts[i]);
    }

    print_tris(tris);

    // Initialization of the hash table
    // hash_add wants: segs address, pt 1, pt 2, make_value(tri 1 address, tri 2 address)
    // hash_find wants: segs, pt 1, pt2
    // hash_delete wants:

    record_t *segs = NULL;
    
    hash_add(&segs, tris->t.p1, tris->t.p2, make_value(&tris->t, NULL));
    hash_add(&segs, tris->t.p2, tris->t.p3, make_value(&tris->t, NULL));
    hash_add(&segs, tris->t.p3, tris->t.p1, make_value(&tris->t, NULL));

    print_hash(segs);

    // Initialization of the active segments list
    s_node *acts = NULL;
    push_s (&acts, (segment){tris->t.p1, tris->t.p2});
    push_s (&acts, (segment){tris->t.p2, tris->t.p3});
    push_s (&acts, (segment){tris->t.p3, tris->t.p1});
    
    print_acts(acts);
    return 0;
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