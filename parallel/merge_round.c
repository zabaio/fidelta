#include <stdio.h>
#include "types.h"

int in_circle(triangle *t, point *d){

    float xda = t->p1.x - d->x;
    float xdb = t->p2.x - d->x;
    float xdc = t->p3.x - d->x;
    float yda = t->p1.y - d->y;
    float ydb = t->p2.y - d->y;
    float ydc = t->p3.y - d->y;
    float da2da2 = xda*xda + yda*yda;
    float db2db2 = xdb*xdb + ydb*ydb;
    float dc2dc2 = xdc*xdc + ydc*ydc;

    // calcolo i minimi complementari
    float min1 = xdb*ydc - xdc*ydb;
    float min2 = xda*ydc - xdc*yda;
    float min3 = xda*ydb - xdb*yda;

    float det = da2da2*min1 - db2db2*min2 + dc2dc2*min3;
    return (det>0);
}
