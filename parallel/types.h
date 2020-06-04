#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#define DIM 300
#define MAXQUERY 100

typedef struct{
    int id;
    float x,y;
} point;

typedef struct{
    point a,b;
} segment;

typedef struct{
    point p1,p2,p3;
} triangle;

// node of a dll of triangles with pointer to encroached points
typedef struct t_node{
    triangle t;
    struct t_node *next;
    int dim;
    point *enc;
} t_node;                     

// fill point
void set_pt(point *pt,float x,float y,float id);

// fill segment
void set_seg(segment *seg,point a,point b);

// fill triangle
void set_t(triangle *t,point a,point b,point c);

#endif // TYPES_H_INCLUDED
