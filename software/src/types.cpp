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
}

// sorting 3 points counterclockwise
void order_three_pts(point *a,point *b,point *c){
    
    float xca = a->x - c->x;
    float xcb = b->x - c->x;
    float yca = a->y - c->y;
    float ycb = b->y - c->y;
    float det = xca*ycb - xcb*yca;

    if (det<0){
        swap_pts(b,c);
    }
}

// add triangle to the front of the list
void push_t (t_node **ref, point p1, point p2, point p3){
    t_node *newnode = new t_node(p1, p2, p3);
    if(*ref != NULL){
        (*ref)->prev = newnode;
    }
    newnode->next = *ref;
    newnode->prev = nullptr;
    *ref = newnode;
}

// delete triangle from t_node list
void pop_t(t_node *del, t_node **head){

    if (del->prev != NULL)
        del->prev->next = del->next;
    else
        *head = del->next;
    
    if (del->next != NULL)
        del->next->prev = del->prev;

    free(del->enc);
    delete del;
}

// add a new triangle to the (maybe new) segs record p1p2. Then, if one of the neighbors is encroached, returns its address.
t_node *push_seg(segment **head, point p1, point p2, t_node *tknown){

    segment *record;
    order_two_pts(&p1, &p2);

    idxkey idx(p1.id, p2.id);
    HASH_FIND(hh, *head, &idx, sizeof(idxkey), record);
    
    if (record == nullptr){
        record = new segment(p1, p2);
        record->tfirst = tknown;
        record->tsecond = nullptr;
        HASH_ADD(hh, *head, key, sizeof(idxkey), record);
    }
    else{
        assert (record->tfirst != nullptr && record->tsecond == nullptr);
        record->tsecond = tknown;
        if (record->tfirst->dim > 0 && (record->tsecond->dim == 0 || record->tfirst->enc[0].id < record->tsecond->enc[0].id)){
            return record->tfirst;
        }
        if (record->tsecond->dim > 0 && (record->tfirst->dim == 0 || record->tsecond->enc[0].id < record->tfirst->enc[0].id)){
            return record->tsecond;
        }
    }
    return nullptr;
}

// pushes a new active segment in acts
void push_act(act_node **acts, segment *segs, point p1, point p2, t_node *father){

    segment *active_seg;
    idxkey idx(p1.id, p2.id);
    HASH_FIND(hh, segs, &idx, sizeof(idxkey), active_seg);
    act_node *newnode = new act_node(active_seg, father);
    newnode->next = *acts;
    *acts = newnode;
}

// deletes element in acts
void pop_act(act_node **acts){
    assert (*acts != NULL);
    act_node *tmp = *acts;
    free(tmp);
    *acts = (*acts)->next;
}