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

    srand(time(NULL));
    for(i = 0; i<N_PTS; i++){
        pts[i].x = rand()%(MAX_COR*2+1)-MAX_COR;
        pts[i].y = rand()%(MAX_COR*2+1)-MAX_COR;
        print_pt(pts[i]);
    }

    #ifdef DEBUG
        if(!is_general_position(pts,N_PTS)) {printf("Init error - Non general position point set\n"); return 0;}
    #endif

    // Initialization of the triangle list
    // Insertion of the starting triangle
    t_node *t_list = NULL;
    triangle t_start;
    set_t(&t_start, pts[-1], pts[-2], pts[-3]);
    push_t_front(&t_list, t_start);

    for(i=0; i<N_PTS; i++){
        push_pt_front(&t_list[0].enc,pts[i]);
    }

    // Initialization of the hash table
    // hash_add wants: segs address, pt 1, pt 2, make_value(tri 1 address, tri 2 address)
    // hash_find wants: segs, pt 1, pt2
    // hash_delete wants:

    record_t *segs = NULL;
    
    hash_add(&segs, t_list->t.p1, t_list->t.p2, make_value(&t_list->t, NULL));
    hash_add(&segs, t_list->t.p2, t_list->t.p3, make_value(&t_list->t, NULL));
    hash_add(&segs, t_list->t.p3, t_list->t.p1, make_value(&t_list->t, NULL));

    record_t *probe = segs;
    while(probe != NULL){
        print_record(*probe);
        probe = probe->hh.next;
    }

    fout_pts(pts-3,N_PTS+3);
    return 0;
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