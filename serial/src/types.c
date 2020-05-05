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

// add triangle to the front of the list
void push_t(t_node **ref, point p1, point p2, point p3){
    t_node *new = (t_node*)malloc(sizeof(t_node));
    set_t(&(new->t), p1, p2, p3);
    new->dim = 0;
    new->next = *ref;
    *ref = new;
    return;
}

// add a new triangle to the (maybe new) segs record p1p2. Then, if one of the neighbors is encroached, returns its address.
t_node *segs_add(record_segs **head, point p1, point p2, t_node *tknown){
    record_segs *record;
    order_two_pts (&p1, &p2);
    idxkey idx;
    idx.id1 = p1.id;
    idx.id2 = p2.id;
    HASH_FIND(hh, *head, &idx, sizeof(idxkey), record);
    
    if (record == NULL){
        record = (record_segs *)malloc(sizeof(record_segs));
        record->key.id1 = idx.id1;
        record->key.id2 = idx.id2;
        set_seg(&(record->seg),p1,p2);
        record->tfirst = tknown;
        record->tsecond = NULL;
        HASH_ADD(hh, *head, key, sizeof(idxkey), record);
    }
    else{
        assert (record->tfirst != NULL && record->tsecond == NULL);
        record->tsecond = tknown;
        if (record->tfirst->dim > 0 && (record->tsecond->dim == 0 || record->tfirst->enc[0].id < record->tsecond->enc[0].id)){
            return record->tfirst;
        }
        if (record->tsecond->dim > 0 && (record->tfirst->dim == 0 || record->tsecond->enc[0].id < record->tfirst->enc[0].id)){
            return record->tsecond;
        }
    }
    return NULL;
}

// pushes a new active segment in acts
void push_act(act_node **acts, record_segs *segs, point p1, point p2, t_node *father){
    act_node *new = (act_node *)malloc(sizeof(act_node));
    
    order_two_pts (&p1, &p2);
    idxkey idx;
    idx.id1 = p1.id;
    idx.id2 = p2.id;
    HASH_FIND(hh, segs, &idx, sizeof(idxkey), new->act);
    
    new->father = father;
    if (new->act->tfirst == father){
        new->uncle = new->act->tsecond;
    }
    else if (new->act->tsecond == father){
        new->uncle = new->act->tfirst;
    }
    else{
        assert(0);
    }
    new->next = *acts;
    *acts = new;
    return;
}

// deletes element in acts
void pop_act(act_node **acts){
    assert (*acts != NULL);
    act_node *tmp = *acts;
    free(tmp);
    *acts = (*acts)->next;
    return;
}