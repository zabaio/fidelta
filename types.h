#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include "uthash.h"

typedef struct{
    double x,y;
} point;

typedef struct{
    point a,b;
} segment;

typedef struct{
    point p1,p2,p3;
} triangle;

typedef struct pt_node{
    point pt;
    struct pt_node *prev,*next;
} pt_node;

typedef struct t_node{
    triangle t;
    struct pt_node *enc;
    struct t_node *prev,*next;
} t_node;                     //triangle&double-linked-list

typedef struct {
    triangle *t1, *t2;
} adj_tri;

typedef struct {
    segment key;
    adj_tri value;
    UT_hash_handle hh;
} record_t;

void set_pt(point *pt,double x,double y);
void set_seg(segment *seg,point a,point b);
void set_t(triangle *t,point a,point b,point c);
void push_t_front(t_node **ref, triangle t);
void push_pt_front(pt_node **ref, point pt);
void pull_t(t_node **ref, t_node *del);
void pull_pt(pt_node **ref, pt_node *del);

adj_tri make_value(triangle *t1, triangle *t2);
void hash_add(record_t **head, point *p1, point *p2, adj_tri value);
record_t *hash_find(record_t *head, point *p1, point *p2);
void hash_delete(record_t *head, record_t *item);

#endif // TYPES_H_INCLUDED
