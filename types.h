#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include "uthash.h"

//TODO Evaluate if various prev are needed

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
// fenc is the first encroached point. lenc the last (in order of id)
typedef struct t_node{
    triangle t;
    struct pt_node *fenc, *lenc;
    struct t_node *prev, *next;
    int vis;
} t_node;                     

// element of the hash table. tfirst is the first triangle to be added to the record
typedef struct {
    segment key;
    t_node *tfirst;
    t_node *tsecond;
    UT_hash_handle hh;
} record_segs;

// element of the stack of active nodes. v is the encroaching point. act is the address of the active segment. father the encroached triangle
typedef struct act_node{
    record_segs *act;
    t_node *father;
    t_node *uncle;
    struct act_node *next;
} act_node;

void set_pt(point *pt,double x,double y,double id);
void set_seg(segment *seg,point a,point b);
void set_t(triangle *t,point a,point b,point c);

void push_t(t_node **ref, point p1, point p2, point p3);
// void pop_t(t_node **ref, t_node *del);

void push_ptint(t_node *ref, point pt);
// void pop_ptint(t_node *ref, pt_node *del);

// add a new triangle to the (maybe new) segs record p1p2. Then, if one of the neighbors is encroached, returns its address.
t_node *segs_add(record_segs **head, point p1, point p2, t_node *tknown);
void segs_delete(record_segs *head, record_segs *del);
t_node *find_opp(record_segs *head, point p1, point p2, t_node *tknown);

void push_act(act_node **acts, record_segs *segs, point p1, point p2, t_node *father);
void pop_act(act_node **acts);

#endif // TYPES_H_INCLUDED
