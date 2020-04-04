#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include "uthash.h"

typedef struct{
    int id;
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

// node of a dll of triangles with dll of points
typedef struct t_node{
    triangle t;
    struct pt_node *enc;
    struct t_node *prev,*next;
} t_node;                     

typedef struct {
    t_node *t1, *t2;
} adj_tri;

typedef struct {
    t_node *t;
    tn_node *next;
} tn_node;

typedef struct {
    segment key;
    adj_tri value;
    UT_hash_handle hh;
} record_segs;

typedef struct {
    segment key;
    t_node *father;
    UT_hash_handle hh;
} record_acts;

void set_pt(point *pt,int x,int y,int id);
void set_seg(segment *seg,point a,point b);
void set_t(triangle *t,point a,point b,point c);

void push_t(t_node **ref, triangle t);
void pop_t(t_node **ref, t_node *del);

void push_pt(pt_node **ref, point pt);
void pop_pt(pt_node **ref, pt_node *del);

adj_tri make_value(triangle *t1, triangle *t2);
void segs_add(record_segs **head, point p1, point p2, adj_tri value);
adj_tri segs_neighbors(record_segs *head, point p1, point p2);
void segs_delete(record_segs *head, record_segs *del);

void acts_add(record_acts **head, segment s, t_node *father);
int is_active(record_acts *head, segment *seg);
void acts_delete(record_acts *head, record_acts *del);

void push_tn (tn_node **ref, t_node *node);
void pop_tn (tn_node **ref);

#endif // TYPES_H_INCLUDED
