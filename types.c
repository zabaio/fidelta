#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

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
void push_t(t_node **ref, point p1, point p2, point p3){
    t_node *new = (t_node*)malloc(sizeof(t_node));
    set_t(&(new->t), p1, p2, p3);
    new->fenc = NULL;
    new->lenc = NULL;
    new->next = *ref;
    new->prev = NULL;
    if(*ref!=NULL) (*ref)->prev = new;
    *ref = new;
    return;
}

// add point to the back of the list, returns the end of the list
void push_ptint(t_node *ref, point pt){
    if(ref == NULL){
        printf("Error in push_ptint");
        exit(EXIT_FAILURE);
    }
    pt_node *new = (pt_node*)malloc(sizeof(pt_node));
    set_pt(&(new->pt), pt.x, pt.y, pt.id);
    new->next = NULL;
    new->prev = ref->lenc;
    if(ref->lenc == NULL){
        ref->fenc = new;
        ref->lenc = new;
        return;
    }
    ref->lenc->next = new;
    ref->lenc = new;
    return;
}

// delete triangle from list. TODO check. Maybe not needed
/* void pop_t(t_node **ref, t_node *del){
    if(*ref == NULL || del== NULL)
        return;

    pt_node *tmp;
    while(del->fenc != NULL){
        tmp = del->fenc;
        del->fenc = del->fenc->next;
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
} */

// delete point from list TODO wrong. Maybe not needed
/* void pop_ptint(t_node *ref, pt_node *del){
    if(ref == NULL || del== NULL)
        return;
    if(*ref == del)
        *ref=del->next;
    if((*ref)->prev != NULL)
        (*ref)->prev->next=(*ref)->next;
    if((*ref)->next != NULL)
        (*ref)->next->prev=(*ref)->prev;
    free(del);
    return;
} */

// add a new halfsegment gets added to segs
void segs_add(record_segs **head, point p1, point p2, t_node *tknown){
    record_segs *record;
    segment *seg;
    set_seg (seg, p1, p2);
    HASH_FIND(hh, *head, seg, sizeof(segment), record);
    
    if (record == NULL){
        record = (record_segs *)malloc(sizeof(record_segs));
        set_seg(&(record->key),p1,p2);
        record->tfirst = tknown;
        record->tsecond = NULL;
        HASH_ADD(hh, *head, key, sizeof(segment), record);
    }
    else{
        assert (record->tfirst != NULL && record->tsecond == NULL);
        record->tsecond = tknown;
    }
    return;
}

// deletes record in segs hash table
void segs_delete(record_segs *head, record_segs *del){
    HASH_DELETE(hh, head, del);
    free(del);
    return;
}

// pushes a new active segment in acts
void push_act(act_node **acts, record_segs *segs, point p1, point p2, t_node *father){
    act_node *new = (act_node *)malloc(sizeof(act_node));
    segment *activeseg = (segment *)malloc(sizeof(segment));
    set_seg (activeseg, p1, p2);
    HASH_FIND (hh, segs, activeseg, sizeof (segment), new->act);
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