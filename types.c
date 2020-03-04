#include <stdlib.h>
#include <stdio.h>

#include "types.h"

// defines general ordering criterion
#define PTS_IN_ORDER(a, b) \
    (a->x < b->x || (a->x == b->x && a->y <= b->y))

void swap_pts(point *a,point *b){
    point temp=*a;
    *a=*b;
    *b=temp;
}

// sorting 2 points
void order_two_pts(point *a,point *b){
    if(!PTS_IN_ORDER(a,b))
        swap_pts(a,b);
    return;
}

// sorting 3 points
void order_three_pts(point *a,point *b,point *c){
    if(!PTS_IN_ORDER(a,b)) swap_pts(a,b);
    if(!PTS_IN_ORDER(a,c)) swap_pts(a,c);
    if(!PTS_IN_ORDER(b,c)) swap_pts(b,c);
    return;
}

// init point
void set_pt(point *pt,double x,double y){
    pt->x=x;
    pt->y=y;
    return;
}

// init segment
void set_seg(segment *seg,point a,point b){
    order_two_pts(&a,&b);
    seg->a=a;
    seg->b=b;
    return;
}

// init triangle
void set_t(triangle *t,point a,point b,point c){
    order_three_pts(&a,&b,&c);
    t->p1=a;
    t->p2=b;
    t->p3=c;
    return;
}

// add triangle to the front of the list
void push_t_front(t_node **ref, triangle t){
    t_node *new_node = (t_node*)malloc(sizeof(t_node));
    new_node->t = t;
    new_node->enc = NULL;
    new_node->next = *ref;
    new_node->prev = NULL;
    if(*ref!=NULL) (*ref)->prev = new_node;
    *ref = new_node;
    return;
}

// add point to the front of the list
void push_pt_front(pt_node **ref, point pt){
    pt_node *new_node = (pt_node*)malloc(sizeof(t_node));
    new_node->pt = pt;
    new_node->next = *ref;
    new_node->prev = NULL;
    if(*ref!=NULL)
        (*ref)->prev = new_node;
    *ref = new_node;
    return;
}

// delete triangle from list
void pull_t(t_node **ref, t_node *del){
    if(*ref == NULL || del== NULL)
        return;
    if(*ref == del)
        *ref=del->next;
    if((*ref)->prev != NULL)
        (*ref)->prev->next=(*ref)->next;
    if((*ref)->next != NULL)
        (*ref)->next->prev=(*ref)->prev;
    free(del);
    return;
}

// delete point from list
void pull_pt(pt_node **ref, pt_node *del){
    if(*ref == NULL || del== NULL)
        return;
    if(*ref == del)
        *ref=del->next;
    if((*ref)->prev != NULL)
        (*ref)->prev->next=(*ref)->next;
    if((*ref)->next != NULL)
        (*ref)->next->prev=(*ref)->prev;
    free(del);
    return;
}
