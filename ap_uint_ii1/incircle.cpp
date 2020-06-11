#include <string.h>
#include <ap_int.h>

#define MAXQUERY 30
#define DCOL 8
#define DROW 2
#define FBIT 32

int in_circle(float *localdata){

	//for(int y = 0; y<8; y++)
	//	printf("%.2f ", (float)localdata[y]);

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

void accel_in_circle(ap_uint<512> *indata, ap_uint<64> *instate){

    #pragma HLS INTERFACE m_axi port=instate offset=slave bundle=gmem0
	#pragma HLS INTERFACE m_axi port=indata offset=slave bundle=gmem1

	#pragma HLS INTERFACE s_axilite port=instate bundle=control
	#pragma HLS INTERFACE s_axilite port=indata bundle=control
	#pragma HLS INTERFACE s_axilite port=return bundle=control

	ap_uint<512> temp_data[1];
	ap_uint<64> temp_state[1];

	float data[DROW][DCOL];
	ap_int<32> state[DROW];

	#pragma HLS ARRAY_PARTITION variable=data complete
	#pragma HLS ARRAY_PARTITION variable=state complete

	int i;
	mainloop: for (i = 0; i < MAXQUERY/2; i++){

		#pragma HLS PIPELINE

		memcpy(temp_data, indata + i, sizeof(ap_uint<512>));
		memcpy(temp_state, instate + i, sizeof(ap_uint<64>));

		int j,k;
		for(j=0; j<DROW; j++){
			for(k=0; k<DCOL; k++){
				int lo = FBIT*j*DCOL + FBIT*k;
				int hi = lo + FBIT - 1;
				data[j][k] = temp_data[0].range(hi, lo);
			}
		}

		for(j=0; j<DROW; j++){
			int lo = j*FBIT;
			int hi = lo + FBIT - 1;
			state[j] = temp_state[0].range(hi, lo);
		}

		for(j=0; j<DROW; j++){

			#pragma HLS UNROLL
			if (state[j] != -1 && !in_circle(data[j])){
				state[j] = -1;
			}
			//printf(" -> %d\n", state[i]);
		}

		temp_state[0] = state[1].concat(state[0]);
		memcpy(instate + i, temp_state, sizeof(ap_int<64>));
	}

	return;
}
