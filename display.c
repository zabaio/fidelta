#include <stdio.h>
#include <stdlib.h>
#include "types.h"

#define PT_FRMT "( %4d , %4d )"       // format of the displayed point

void print_pt(point pt){
    printf(PT_FRMT "\n", pt.x, pt.y);
    return;
}

void print_seg(segment seg){
    printf(PT_FRMT "-" PT_FRMT "\n", seg.a.x, seg.a.y, seg.b.x, seg.b.y);
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

void print_record(record_t rec){
    print_seg(rec.key);
    if(rec.value.t1) print_t(*rec.value.t1); else printf("nil\n");
    if(rec.value.t2) print_t(*rec.value.t2); else printf("nil\n"); 
    return;
}

void fout_pts(point* pts, int num_pts){
    FILE *out;
    int i;
    out = fopen("./files/random.node","w");
    if(out == NULL){
        printf("Cannot open output file");
        return;
    }
    fprintf (out,"%d 2 0 0\n",num_pts);
    for(i=0; i<num_pts; i++){
        fprintf(out,"%d %d %d\n",i, pts[i].x, pts[i].y);
    }
    return;
}