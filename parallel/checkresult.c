#include <stdio.h>
#include <stdlib.h>
#include "types.h"

#define M_COR 100

int in_circle_seq(triangle *t, point *d){

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

int main(){
	srand((unsigned)time(NULL));
	triangle t;
	point abc[3];

	int i;
	for(i = 0; i<3; i++){
		abc[i].x = (float)rand()/(float)(RAND_MAX)*(M_COR*2)-M_COR;
		abc[i].y = (float)rand()/(float)(RAND_MAX)*(M_COR*2)-M_COR;
	}

	set_t(&t, abc[0], abc[1], abc[2]);

	point v;
	v.x = (float)rand()/(float)(RAND_MAX)*(M_COR*2)-M_COR;
	v.y = (float)rand()/(float)(RAND_MAX)*(M_COR*2)-M_COR;

	int det_ker = in_circle(&t,&v);
	int det_seq = in_circle_seq(&t,&v);

	if(det_ker == det_seq)
		printf("Result is correct\n");
	else
		printf("Result is incorrect\n");

	return 0;
}
