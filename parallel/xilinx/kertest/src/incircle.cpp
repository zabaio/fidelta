#include <cstring>

#define MAXQUERY 30
#define PTSLIM 300000

int in_circle(float *data){

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

void accel_in_circle(float *indata, int *instate){

    #pragma HLS INTERFACE m_axi port=instate offset=slave bundle=gmem0
	#pragma HLS INTERFACE m_axi port=indata offset=slave bundle=gmem0

	#pragma HLS INTERFACE s_axilite port=instate bundle=control
	#pragma HLS INTERFACE s_axilite port=indata bundle=control
	#pragma HLS INTERFACE s_axilite port=return bundle=control

	float data[MAXQUERY][8];
	int state[MAXQUERY];

	#pragma HLS array_partition variable=data complete
	#pragma HLS array_partition variable=state complete

	memcpy(data, indata, 8*MAXQUERY*sizeof(float));
	memcpy(state, instate, MAXQUERY*sizeof(int));

	int i;
	mainloop: for (i = 0; i < MAXQUERY; i++){
		#pragma HLS UNROLL

		int res = in_circle(data[i]);
		if(state[i] != -1 && res == 0){
			state[i] = -1;
		}

	}

	memcpy(instate, state, MAXQUERY*sizeof(int));

	return;
}

