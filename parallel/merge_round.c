#include <stdio.h>
#include <string.h>
#include "types.h"

int in_circle(const point *p1,const point *p2,const point *p3 ,const point *d){

    float xda = p1->x - d->x;
    float xdb = p2->x - d->x;
    float xdc = p3->x - d->x;
    float yda = p1->y - d->y;
    float ydb = p2->y - d->y;
    float ydc = p3->y - d->y;
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

void accel(int *init, point *inpts, int *indata, int *outresult){

    #pragma HLS INTERFACE m_axi port=inpts offset=slave bundle=gmem0
	#pragma HLS INTERFACE m_axi port=indata offset=slave bundle=gmem0
    #pragma HLS INTERFACE m_axi port=outresult offset=slave bundle=gmem0

	#pragma HLS INTERFACE s_axilite port=init bundle=control
	#pragma HLS INTERFACE s_axilite port=inpts bundle=control
	#pragma HLS INTERFACE s_axilite port=indata bundle=control
	#pragma HLS INTERFACE s_axilite port=outresult bundle=control
	#pragma HLS INTERFACE s_axilite port=return bundle=control

	static const point pts[DIM];
	#pragma HLS array_partition variable=points complete dim=1

	if (*init == 1){

		memcpy(&pts[0], inpts, DIM*sizeof(point));

	}
	else{
		int data[4][MAX_QUERY];
		int result[MAX_QUERY];

		memcpy(&data[0][0], indata, 4*MAX_QUERY*sizeof(int));

		int i;
		for (i = 0; i < MAX_QUERY; i++){
			if (in_circle(&pts[data[1][i]], &pts[data[2][i]], &pts[data[3][i]], &pts[data[0][i]]))
				result[i] = pts[data[0][i]].id;
			else
				result[i] = -1;
		}
		memcpy(outresult, result, MAX_QUERY*sizeof(int));
	}
	return;
}
