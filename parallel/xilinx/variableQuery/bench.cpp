#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ap_int.h>

#define MAXQUERY 16
#define DCOL 2
#define DROW 8
#define FBIT 32

void accel_in_circle(ap_uint<512> *indata, ap_uint<256> *instate, ap_uint<256> *infather, int *inmaxquery);

int test_in_circle(float *data, float *father){

	//for(int y = 0; y<8; y++)
	//	printf("%.2f ", (float)localdata[y]);

    float xda = father[0] - data[0];
    float xdb = father[2] - data[0];
    float xdc = father[4] - data[0];
    float yda = father[1] - data[1];
    float ydb = father[3] - data[1];
    float ydc = father[5] - data[1];
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

	int maxquery = MAXQUERY;
	srand(7);
	float data[MAXQUERY][DCOL];
	int state[MAXQUERY];
	int state_acc[MAXQUERY];
	float father[6];
	int i,j;

	for(i=0; i<6; i++){
		father[i] = (float)(rand() % 1000)/100 - 5;
		printf("%.2f ",father[i]);
	}
	printf("\n");

	for (i=0; i<maxquery; i++){
		state[i] = i;
		state_acc[i] = state[i];

		for (j=0; j<DCOL; j++){
			data[i][j] = (float)(rand() % 1000)/100 - 5;
			printf("%.2f ",data[i][j]);
		}
		printf("\n");
	}

	for (i=0; i<maxquery; i++){
		for(j = 0; j<DCOL; j++)
			printf("%.2f ", data[i][j]);
		if (state[i]!= -1 && !test_in_circle(data[i], father))
			state[i] = -1;
		printf(" -> %d\n", state[i]);
	}

	accel_in_circle((ap_uint<512> *)data[0], (ap_uint<256> *)state_acc, (ap_uint<256> *)father, &maxquery);

	for (i=0; i<maxquery; i++){
		printf("%2d %2d\n",state[i], state_acc[i]);
	}
	return 0;
}
