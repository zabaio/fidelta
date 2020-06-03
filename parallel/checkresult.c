#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
	triangle t[3];
	point pts[DIM];

	int i;
	for(i = 0; i<DIM; i++){
		pts[i].x = (float)rand()/(float)(RAND_MAX)*(M_COR*2)-M_COR;
		pts[i].y = (float)rand()/(float)(RAND_MAX)*(M_COR*2)-M_COR;
		pts[i].id = i;
	}

	int r_1, r_2, r_3;
	for (i=0; i<3; i++){
		do {
		r_1 = rand()%DIM;
		r_2 = rand()%DIM;
		r_3 = rand()%DIM;
		} while (r_1 != r_2 && r_1 != r_3 && r_2 != r_3);
		set_t(&t[i], pts[r_1], pts[r_2], pts[r_3]);
	}

	int data[4][MAX_QUERY];
	for (i = 0; i<MAX_QUERY; i++){
		r_1 = rand() % DIM;
		r_2 = rand() % 3;
		data[0][i] = pts[r_1].id;
		data[1][i] = t[r_2].p1.id;
		data[2][i] = t[r_2].p2.id;
		data[3][i] = t[r_2].p3.id;
	}

	int init = 1;
	accel (&init, pts, NULL, NULL);
	init = 0;

	int result[MAX_QUERY], inresult[MAX_QUERY];
	for (i = 0; i<MAX_QUERY; i++){
		triangle dummy;
		set_t(&dummy, pts[data[1][i]], pts[data[2][i]], pts[data[3][i]]);
		if (in_circle_seq(&dummy, &pts[i])){
			result[i] = pts[i].id;
		}
		else result[i] = -1;

	}

	accel (&init, NULL, data[0], inresult);

	/*
	for (i = 0; i < MAX_QUERY; i++){
		if (inresult[i] != result[i]){
			printf ("ERROR\n");
			return 0;
		}
	}
	printf ("CORRECT\n");
	*/

	return 0;
}
