#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include <cassert>
#include "uthash.h"

struct point{
    int id;
    float x,y;
    point() {}
    point(int id, float x, float y) : id(id), x(x), y(y) {}
};

void swap_pts(point *a,point *b);
void order_two_pts(point *a,point *b);
void order_three_pts(point *a,point *b,point *c);

struct idxkey{
    int id1;
    int id2;

    idxkey() {}

    idxkey(int id1, int id2){
        if (id1 <= id2) {
            this->id1 = id1;
            this->id2 = id2;
        } else {
            this->id1 = id2;
            this->id2 = id1;
        }
    }
};

// node of a dll of triangles with dll of points
// fenc is the first encroached point. lenc the last (in order of id)
struct t_node{

    point p1;
    point p2;
    point p3;
    t_node *next;
    t_node *prev;
    point *enc;
    char lives;
    int dim;

    t_node(point p1, point p2, point p3) : p1(p1), p2(p2), p3(p3), lives(3), dim(0) {
        order_three_pts(&this->p1, &this->p2, &this->p3);
    }

    point opposite(point a, point b){
        if (p1.id != a.id && p1.id != b.id)
            return p1;
        if (p2.id != a.id && p2.id != b.id)
            return p2;
        if (p3.id != a.id && p3.id != b.id)
            return p3;
        assert(0);
    }
};

struct segment{
    point a,b;
    idxkey key;
    t_node *tfirst;
    t_node *tsecond;
    UT_hash_handle hh;

    segment(point a, point b) : a(a), b(b){
        order_two_pts(&this->a, &this->b);
        key.id1 = a.id;
        key.id2 = b.id;
    }
    t_node *opposite(t_node *tknown){
        if (tfirst == tknown)
            return tsecond;
        if (tsecond == tknown)
            return tfirst;
        return nullptr;
    }
    void remove (segment **head, t_node *tknown){
        if (tfirst == tknown){
            tfirst = nullptr;
        }
        else if (tsecond == tknown){
            tsecond = nullptr;
        }
    }
};

// element of the stack of active nodes. v is the encroaching point. act is the address of the active segment. father the encroached triangle
struct act_node{
    segment *seg;
    t_node *father;
    t_node *uncle;
    act_node *next;

    act_node(segment *seg, t_node *father) : seg(seg) {
        if (father == seg->tfirst){
            this->father = seg->tfirst;
            this->uncle = seg->tsecond;
        } else{
            this->father = seg->tsecond;
            this->uncle = seg->tfirst;
        }
    }
};

// add triangle to the front of the list
void push_t(t_node **ref, point p1, point p2, point p3);

// delete triangle from t_node list
void pop_t(t_node *del, t_node **head);

// add a new triangle to the (maybe new) segment p1p2. Then, if one of the neighbors is encroached, returns its address.
t_node *push_seg(segment **head, point p1, point p2, t_node *tknown);

// pushes a new active segment in acts
void push_act(act_node **acts, segment *segs, point p1, point p2, t_node *father);

// deletes element in acts
void pop_act(act_node **acts);

#endif // TYPES_H_INCLUDED
