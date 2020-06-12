#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ap_int.h>

#define MAXQUERY 30
#define DCOL 8
#define DROW 2
#define FBIT 32
#define PTSLIM 300000

void accel_in_circle(ap_uint<512> *indata, ap_uint<64> *instate);

int test_in_circle(float *data){

    float xda = data[2] - data[0];
    float xdb = data[4] - data[0];
    float xdc = data[6] - data[0];
    float yda = data[3] - data[1];
    float ydb = data[5] - data[1];
    float ydc = data[7] - data[1];
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

	srand(5);
	float data[MAXQUERY][DCOL];
	int state[MAXQUERY];
	int state_acc[MAXQUERY];
	int i,j;

	for (i=0; i<MAXQUERY; i++){
		state[i] = i;
		state_acc[i] = state[i];

		for (j=0;j<DCOL;j++){
			data[i][j] = (float)(rand() % 1000)/100;
			printf("%.2f ",data[i][j]);
		}
		printf("\n");
	}

	for (i=0; i<MAXQUERY; i++){
		for(int y = 0; y<8; y++)
			printf("%.2f ", data[i][y]);
		if (state[i]!= -1 && !test_in_circle(data[i]))
			state[i] = -1;
		printf(" -> %d\n", state[i]);
	}

	accel_in_circle((ap_uint<512> *)data[0], (ap_uint<64> *)state_acc);

	for (i=0; i<MAXQUERY; i++){
		printf("%2d %2d\n",state[i], state_acc[i]);
	}
	return 0;
}