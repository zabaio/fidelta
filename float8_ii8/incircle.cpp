#include <string.h>
#include <ap_int.h>
//#include <stdio.h>

#define MAXQUERY 30
#define DCOL 8
#define DROW 2
#define FBIT 32

typedef struct{
	float f0, f1, f2, f3, f4, f5, f6, f7;
} float8;

int in_circle(float *localdata){

	//for(int y = 0; y<8; y++)
		//printf("%.2f ", localdata[y]);

    float xda = localdata[2] - localdata[0];
    float xdb = localdata[4] - localdata[0];
    float xdc = localdata[6] - localdata[0];
    float yda = localdata[3] - localdata[1];
    float ydb = localdata[5] - localdata[1];
    float ydc = localdata[7] - localdata[1];
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

void accel_in_circle(float8 *indata, int *instate){

    #pragma HLS INTERFACE m_axi port=instate offset=slave bundle=gmem0
	#pragma HLS INTERFACE m_axi port=indata offset=slave bundle=gmem1

	#pragma HLS INTERFACE s_axilite port=instate bundle=control
	#pragma HLS INTERFACE s_axilite port=indata bundle=control
	#pragma HLS INTERFACE s_axilite port=return bundle=control

	float8 temp_data[MAXQUERY];
	float data[MAXQUERY][DCOL];
	int state[MAXQUERY];

	#pragma HLS DATA_PACK variable temp_data

	#pragma HLS ARRAY_PARTITION variable=data complete
	#pragma HLS ARRAY_PARTITION variable=state complete
	#pragma HLS ARRAY_PARTITION variable=temp_data complete

	int i;
	mainloop: for (i = 0; i < MAXQUERY; i++){

		#pragma HLS PIPELINE
		int j,k;

		temp_data[i] = indata[i];
		state[i] = instate[i];

		data[i][0] = temp_data[i].f0;
		data[i][1] = temp_data[i].f1;
		data[i][2] = temp_data[i].f2;
		data[i][3] = temp_data[i].f3;
		data[i][4] = temp_data[i].f4;
		data[i][5] = temp_data[i].f5;
		data[i][6] = temp_data[i].f6;
		data[i][7] = temp_data[i].f7;

		if (state[i] != -1 && !in_circle(data[i])){
			state[i] = -1;
		}
		//printf(" -> %d\n", (int)state[j]);

		memcpy(instate + i, state + i, sizeof(int));
	}

	return;
}
