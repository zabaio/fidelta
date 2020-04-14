#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>

#include "types.h"
#include "display.h"

#ifdef DEBUG
    int is_general_position(point *pts,int n_pts);
#endif



#define N_PTS 100000
#define MAX_COR 1

// checks if point d is inside the circumcircle of t
int in_circle (triangle *t, point *d);
void merge (t_node *father, t_node *son, t_node *uncle);
void fill_sol (record_segs *segs, t_node **tail, t_node *cur);

int cont=0,cont2=0;

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
        pts[i].id = i;
        #ifdef LOG
            print_pt_id(pts[i]);
            print_pt(pts[i]);
        #endif
    }

    /*
    pts[0].x = 1.2;
    pts[0].y = -1.2;
    pts[0].id = 0;
    pts[1].x = -9.1;
    pts[1].y = -3.4;
    pts[1].id = 1;
    pts[2].x = -2.5;
    pts[2].y = 8.8;
    pts[2].id = 2;
    pts[3].x = 9.5;
    pts[3].y = -6;
    pts[3].id = 3;
    */

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

    #ifdef LOG 
        print_tris(tris);
    #endif

    // Initialization of the hash table
    // segs_add wants: segs address, pt 1, pt 2, make_value(tri 1 address, tri 2 address)
    // segs_find wants: segs, pt 1, pt2
    // segs_delete wants:

    record_segs *segs = NULL;
    
    segs_add (&segs, tris->t.p1, tris->t.p2, tris);
    segs_add (&segs, tris->t.p2, tris->t.p3, tris);
    segs_add (&segs, tris->t.p3, tris->t.p1, tris);

    #ifdef LOG
        print_segs_id(segs);
    #endif

    // Initialization of the active segments list
    act_node *acts = NULL;
    act_node *nextround = NULL;

    push_act (&acts, segs, tris->t.p1, tris->t.p2, tris);
    push_act (&acts, segs, tris->t.p2, tris->t.p3, tris);
    push_act (&acts, segs, tris->t.p3, tris->t.p1, tris);

    while(acts != NULL || nextround != NULL){
        // load next round
        if (acts == NULL){

            #ifdef LOG
                printf("Fine round;\n");
                print_tris_id(tris);
            #endif
            
            acts = nextround;
            nextround = NULL;
        }

        #ifdef LOG
            printf("\nAttivo: %d %d\n", acts->act->seg.a.id, acts->act->seg.b.id);
        #endif
        
        t_node *encroached = NULL;

        // the son gets added to tris
        push_t (&tris, acts->act->seg.a, acts->act->seg.b, acts->father->fenc->pt);
        
        // son is populated by its encroaching points
        merge (acts->father, tris, acts->uncle);
        
        // we add a-pt to segs
        // encroached gets the triangle encroached in the relation across a-pt and we add it to the next round
        encroached = segs_add (&segs, acts->act->seg.a, acts->father->fenc->pt, tris);
        
        #ifdef LOG
            print_segs_id(segs);
        #endif

        if (encroached != NULL){
            push_act (&nextround, segs, acts->act->seg.a, acts->father->fenc->pt, encroached);
        }

        // same as before with b-pt
        encroached = segs_add (&segs, acts->act->seg.b, acts->father->fenc->pt, tris);
        
        #ifdef LOG
            print_segs_id(segs);
        #endif
        if (encroached != NULL){
            push_act (&nextround, segs, acts->act->seg.b, acts->father->fenc->pt, encroached);
        }
        
        // if uncle is null we're on the border. ab has only tfirst filled, we update it and if there are still enc pts we add it so nextround
        assert (acts->act->tfirst == acts->father || acts->act->tsecond == acts->father);
        if(acts->uncle == NULL){
            acts->act->tfirst = tris;
            if (tris->fenc != NULL){
                push_act (&nextround, segs, acts->act->seg.a, acts->act->seg.b, tris);
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

            if (acts->act->tfirst->fenc != NULL && 
               (acts->act->tsecond->fenc == NULL || acts->act->tfirst->fenc->pt.id  <  acts->act->tsecond->fenc->pt.id)){
                
                push_act (&nextround, segs, acts->act->seg.a, acts->act->seg.b, acts->act->tfirst);
            
            }

            else if (acts->act->tsecond->fenc != NULL && 
                    (acts->act->tfirst->fenc == NULL || acts->act->tsecond->fenc->pt.id  <  acts->act->tfirst->fenc->pt.id)){

                push_act (&nextround, segs, acts->act->seg.a, acts->act->seg.b, acts->act->tsecond);
            
            }
        }

        pop_act (&acts);

    }
    
    #ifdef LOG
        print_tris_id(tris);
    #endif

    t_node *sol = NULL;
    t_node *tail = NULL;
    
    tris->vis = 1;
    sol = tris;
    tail = tris;
    printf("\n");
    while(tail != NULL){
        if(tail->fenc == NULL) cont++;
        cont2++;
        tail = tail->next;
    }
    tail = tris;
    // fill_sol(segs, &tail, tail);
    printf("\n");
    tail->next = NULL;
    printf("Triangoli generati in tris: %d\n", cont);
    printf("Triangoli della triangolazione: %d\n", cont2);
    return 0;
}

int in_circle(triangle *t, point *d){
    
    double xda = t->p1.x - d->x;
    double xdb = t->p2.x - d->x;
    double xdc = t->p3.x - d->x;
    double yda = t->p1.y - d->y;
    double ydb = t->p2.y - d->y;
    double ydc = t->p3.y - d->y;
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
    pt_node *fprobe = father->fenc->next;
    if (uncle == NULL){
        while (fprobe != NULL){
            if (in_circle (&son->t, &fprobe->pt))
                push_ptint (son, fprobe->pt);
            fprobe = fprobe->next;
        }
    }
    else{
        pt_node *uprobe = uncle->fenc;
        while (fprobe != NULL || uprobe != NULL){
            
            if (uprobe == NULL || (fprobe != NULL && fprobe->pt.id < uprobe->pt.id)){
                if (in_circle (&son->t, &fprobe->pt)){
                    push_ptint (son, fprobe->pt);
                }
                fprobe = fprobe->next;
            }
            
            else if (fprobe == NULL || (uprobe != NULL && uprobe->pt.id < fprobe->pt.id)){
                if (in_circle (&son->t, &uprobe->pt)){
                    push_ptint (son, uprobe->pt);
                }
                uprobe = uprobe->next;
            }

            else if (fprobe != NULL && uprobe != NULL && fprobe->pt.id == uprobe->pt.id){
                if (in_circle (&son->t, &fprobe->pt)){  //TODO necessary?
                    push_ptint (son, fprobe->pt);
                }
                uprobe = uprobe->next;
                fprobe = fprobe->next;
            }
        }
    }
    return;
}


void fill_sol (record_segs *segs, t_node **tail, t_node *cur){
    t_node *opp;
    #ifdef LOG
        printf ("Visito %2d %2d %2d\n", cur->t.p1.id, cur->t.p2.id, cur->t.p3.id);
    #endif
    opp = find_opp (segs, cur->t.p1, cur->t.p2, cur);
    if (opp != NULL && !opp->vis){
        cont++;
        opp->vis = 1;
        (*tail)->next = opp;
        (*tail) = (*tail)->next;
        fill_sol (segs, tail, opp);
    }

    opp = find_opp (segs, cur->t.p2, cur->t.p3, cur);
    if (opp != NULL && !opp->vis){
        cont++;
        opp->vis = 1;
        (*tail)->next = opp;
        (*tail) = (*tail)->next;
        fill_sol (segs, tail, opp);
    }

    opp = find_opp (segs, cur->t.p3, cur->t.p1, cur);
    if (opp != NULL && !opp->vis){
        cont++;
        opp->vis = 1;
        (*tail)->next = opp;
        (*tail) = (*tail)->next;
        fill_sol (segs, tail, opp);
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