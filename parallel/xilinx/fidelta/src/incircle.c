#include <string.h>

#include "types.h"

#define MAXQUERY 3
#define PTSLIM 300000

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

void accel_in_circle(int init, point *inpts, int *indata){

    #pragma HLS INTERFACE m_axi port=inpts offset=slave bundle=gmem0
	#pragma HLS INTERFACE m_axi port=indata offset=slave bundle=gmem0

	#pragma HLS INTERFACE s_axilite port=init bundle=control
	#pragma HLS INTERFACE s_axilite port=inpts bundle=control
	#pragma HLS INTERFACE s_axilite port=indata bundle=control
	#pragma HLS INTERFACE s_axilite port=return bundle=control

	static point pts[PTSLIM + 3];
	#pragma HLS array_partition variable=pts block factor=30

	if (init == 1){

		memcpy(&pts[0], inpts, (PTSLIM + 3)*sizeof(point));

	}
	else{
		int data[4][MAXQUERY];

		memcpy(&data[0][0], indata, 4*MAXQUERY*sizeof(int));

		int i;
		mainloop: for (i = 0; i < MAXQUERY; i++){

			#pragma HLS unroll

			if (data[0][i] != -1 && in_circle(&pts[data[1][i]], &pts[data[2][i]], &pts[data[3][i]], &pts[data[0][i]]))
				data[0][i] = pts[data[0][i]].id;
			else
				data[0][i] = -1;

		}
		memcpy(indata, data, MAXQUERY*sizeof(int));
	}
	return;
}
