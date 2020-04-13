#include <stdio.h>
#include <stdlib.h>
#include "types.h"

#define PT_FRMT "( %.2f , %.2f )"       // format of the displayed point

void print_pt_id(point pt){
    printf("%2d ", pt.id);
    return;
}

void print_pt(point pt){
    printf( PT_FRMT "\n", pt.x, pt.y);
    return;
}

void print_seg(segment seg){
    printf(PT_FRMT "-" PT_FRMT, seg.a.x, seg.a.y, seg.b.x, seg.b.y);
    return;
}

void print_t(triangle t){
    printf(PT_FRMT "-" PT_FRMT "-" PT_FRMT "\n", t.p1.x, t.p1.y, t.p2.x, t.p2.y, t.p3.x, t.p3.y);
    return;
}

void print_t_exp(triangle t){
    printf("Tri:\n\t" PT_FRMT "-" PT_FRMT "\n\t" PT_FRMT "-" PT_FRMT "\n\t" PT_FRMT "-" PT_FRMT "\n",
           t.p1.x, t.p1.y, t.p2.x, t.p2.y,
           t.p2.x, t.p2.y, t.p3.x, t.p3.y,
           t.p1.x, t.p1.y, t.p3.x, t.p3.y);
    return;
}

void print_tris(t_node *tris){
    printf("\nTriangoli in tris:\n");
    while(tris != NULL){
        print_t(tris->t);
        pt_node *probe = tris->fenc;
        while(probe != NULL){
            printf("\t" PT_FRMT "\n", probe->pt.x, probe->pt.y);
            probe = probe->next;
        }
        tris = tris->next;
    }
}

void print_tris_id(t_node *tris){
    printf("\nTriangoli in tris:\n");
    while(tris != NULL){
        printf("%2d %2d %2d  -->",tris->t.p1.id, tris->t.p2.id, tris->t.p3.id);
        pt_node *probe = tris->fenc;
        while(probe != NULL){
            printf(" %d", probe->pt.id);
            probe = probe->next;
        }
        printf ("\n");
        tris = tris->next;
    }
    return;
}

void print_segs(record_segs *elem){
    printf("\n Elements in segs:\n");
    while(elem != NULL){
        print_seg(elem->key);
        if(elem->tfirst){
            printf("\t");
            print_t(elem->tfirst->t);
        } 
        else printf("\tnil\n");
        
        if(elem->tsecond) {
            printf("\t");
            print_t(elem->tsecond->t); 
        }    
        else printf("\tnil\n");
        
        elem = elem->hh.next;
    }
    return;
}

void print_segs_id(record_segs *elem){
    printf("\n Elements in segs:\n");
    while(elem != NULL){
        print_pt_id(elem->key.a);
        print_pt_id(elem->key.b);
        printf(" --> (");
        if(elem->tfirst){
            print_pt_id(elem->tfirst->t.p1);
            print_pt_id(elem->tfirst->t.p2);
            print_pt_id(elem->tfirst->t.p3);
        } 
        else printf(" --> (nil");
        
        if(elem->tsecond) {
            printf(") (");
            print_pt_id(elem->tsecond->t.p1);
            print_pt_id(elem->tsecond->t.p2);
            print_pt_id(elem->tsecond->t.p3);
            printf(")"); 
        }    
        else printf(") (nil)");
        printf("\n");
        elem = elem->hh.next;
    }
    return;
}

void fprint_pts(point* pts, int num_pts){
    FILE *out;
    int i;
    out = fopen("./files/random.node","w");
    if(out == NULL){
        printf("Cannot open output file");
        return;
    }
    fprintf (out,"%d 2 0 0\n",num_pts);
    for(i=0; i<num_pts; i++){
        fprintf(out,"%d %f %f\n",i, pts[i].x, pts[i].y);
    }
    return;
}

void print_sol(t_node *sol){
    while (sol != NULL){
        printf("%2d %2d %2d\n", sol->t.p1.id, sol->t.p2.id, sol->t.p3.id);
        sol = sol->next;
    }
    return;
}

void fprint_sol(t_node *sol){
    FILE *out;
    out = fopen("/files/sol.ele", "w");
    while (sol != NULL){
        fprintf(out, "%2d %2d %2d\n", sol->t.p1.id, sol->t.p2.id, sol->t.p3.id);
        sol = sol->next;
    }
    return;
}