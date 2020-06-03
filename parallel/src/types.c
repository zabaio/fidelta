#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "types.h"

// defines general ordering criterion
#define PTS_IN_ORDER(a, b) \
    (a->x < b->x || (a->x == b->x && a->y <= b->y))

// swap two points
void swap_pts(point *a,point *b){
    point temp=*a;
    *a=*b;
    *b=temp;
}

// sorting 2 points in order of id
void order_two_pts(point *a,point *b){    
    if(a->id > b->id)
        swap_pts(a,b);
    return;
}

// sorting 3 points: the first according to PTS_IN_ORDER (TODO necessary?), 
// the others so that they are counterclockwise
void order_three_pts(point *a,point *b,point *c){
    if(!PTS_IN_ORDER(a,b)) swap_pts(a,b);
    if(!PTS_IN_ORDER(a,c)) swap_pts(a,c);
    
    float xca = a->x - c->x;
    float xcb = b->x - c->x;
    float yca = a->y - c->y;
    float ycb = b->y - c->y;
    float det = xca*ycb - xcb*yca;

    if (det<0){
        swap_pts(b,c);
    }

    return;
}

// fill point
void set_pt(point *pt,float x,float y,float id){
    pt->id=id;
    pt->x=x;
    pt->y=y;
    return;
}

// fill segment
void set_seg(segment *seg,point a,point b){
    order_two_pts(&a,&b);
    seg->a=a;
    seg->b=b;
    return;
}

// fill triangle
void set_t(triangle *t,point a,point b,point c){
    order_three_pts(&a,&b,&c);
    t->p1=a;
    t->p2=b;
    t->p3=c;
    return;
}
