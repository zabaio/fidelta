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

// sorting 3 points: the first according to PTS_IN_ORDER (TODO necessary?), 
// the others so that they are counterclockwise
void order_three_pts(point *a,point *b,point *c){
    if(!PTS_IN_ORDER(a,b)) swap_pts(a,b);
    if(!PTS_IN_ORDER(a,c)) swap_pts(a,c);
    
    double xca = a->x - c->x;
    double xcb = b->x - c->x;
    double yca = a->y - c->y;
    double ycb = b->y - c->y;
    double det = xca*ycb - xcb*yca;

    if (det<0){
        swap_pts(b,c);
    }

    return;
}

// init point
void set_pt(point *pt,int x,int y,int id){
    pt->id=id;
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
void push_t(t_node **ref, triangle t){
    t_node *new_node = (t_node*)malloc(sizeof(t_node));
    new_node->t = t;
    new_node->enc = NULL;
    new_node->next = *ref;
    new_node->prev = NULL;
    if(*ref!=NULL) (*ref)->prev = new_node;
    *ref = new_node;
    return;
}

void push_tn (tn_node **ref, t_node *node){
    tn_node *new_node = (tn_node*)malloc(sizeof(tn_node));
    new_node->t = node;
    new_node->next = *ref;
    *ref = new_node;
    return;
}

void pop_tn (tn_node **ref){
    tn_node *tmp;
    tmp = *ref;
    *ref = (*ref)->next;
    free(tmp);
    return;
}

// add point to the front of the list, returns the end of the list
void push_pt(pt_node **ref, point pt){
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
void pop_t(t_node **ref, t_node *del){
    if(*ref == NULL || del== NULL)
        return;

    pt_node *tmp;
    while(del->enc != NULL){
        tmp = del->enc;
        del->enc = del->enc->next;
        free(tmp);
    }

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
void pop_pt(pt_node **ref, pt_node *del){
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

// add record to segs hash table
void segs_add(record_segs **head, point p1, point p2, adj_tri value){
    record_segs *new =(record_segs *)malloc(sizeof(record_segs));
    set_seg(&(new->key),p1,p2);
    new->value = value;
    HASH_ADD(hh, *head, key, sizeof(segment), new);
    return;
}

// finds record in segs hash table given 2 points
adj_tri segs_neighbors(record_segs *head, point p1, point p2){
    record_segs *r;
    segment *seg = (segment *)malloc(sizeof(segment));
    set_seg(seg,p1,p2);
    HASH_FIND(hh, head, seg, sizeof(segment), r);
    return r->value;
}

// deletes record in segs hash table
void segs_delete(record_segs *head, record_segs *del){
    HASH_DELETE(hh, head, del);
    free(del);
    return;
}

// creates a couple of triangles
adj_tri make_value(triangle *t1, triangle *t2){
    adj_tri v;
    v.t1=t1;
    v.t2=t2;
    return v;
}

// add record to acts hash table
void acts_add(record_acts **head, segment s, t_node *father){
    record_acts *new =(record_acts *)malloc(sizeof(record_acts));
    new->father = father;
    HASH_ADD(hh, *head, key, sizeof(segment), new);
    return;
}

//  chechs if segment seg is inside acts
int is_active(record_acts *head, segment *seg){
    record_acts *r;
    HASH_FIND(hh, head, seg, sizeof(segment), r);
    return (r != NULL);
}

// deletes record in acts hash table
void acts_delete(record_acts *head, record_acts *del){
    HASH_DELETE(hh, head, del);
    free(del);
    return;
}