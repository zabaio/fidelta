#include <string.h>
#include <ap_int.h>
//#include <stdio.h>

#define DCOL 2
#define DROW 8
#define FBIT 32

extern "C" {

int in_circle(float *innerdata, float *son){

	//for(int y = 0; y < DCOL; y++)
	//	printf("%.2f ", innerdata[y]);

    float xda = son[0] - innerdata[0];
    float xdb = son[2] - innerdata[0];
    float xdc = son[4] - innerdata[0];
    float yda = son[1] - innerdata[1];
    float ydb = son[3] - innerdata[1];
    float ydc = son[5] - innerdata[1];
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

void accel_in_circle(ap_uint<256> *instate, ap_uint<512> *indata, ap_uint<256> *inson, int maxquery){

    #pragma HLS INTERFACE m_axi port=instate offset=slave bundle=gmem0
	#pragma HLS INTERFACE m_axi port=indata offset=slave bundle=gmem1
	#pragma HLS INTERFACE m_axi port=inson offset=slave bundle=gmem2

	#pragma HLS INTERFACE s_axilite port=instate bundle=control
	#pragma HLS INTERFACE s_axilite port=indata bundle=control
	#pragma HLS INTERFACE s_axilite port=inson bundle=control
	#pragma HLS INTERFACE s_axilite port=maxquery bundle=control
	#pragma HLS INTERFACE s_axilite port=return bundle=control

	//printf("%d\n", maxquery);

	ap_uint<512> temp_data[1];
	ap_uint<256> temp_state[1];
	ap_uint<256> temp_son[1];

	float data[DROW][DCOL];
	ap_int<32> state[DROW];
	float son[6];
	int i;

	#pragma HLS ARRAY_PARTITION variable=data complete
	#pragma HLS ARRAY_PARTITION variable=state complete
	#pragma HLS ARRAY_PARTITION variable=son complete

	memcpy(temp_son, inson, sizeof(ap_uint<256>));

	initson: for(i = 0; i < 6; i++){
		#pragma HLS PIPELINE

		ap_uint<32> temp;
		int lo = FBIT*i;
		int hi = lo + FBIT - 1;
		temp = temp_son[0].range(hi, lo);

		son[i] = *((float *)&temp);
	}

	mainloop: for (i = 0; i < maxquery/DROW; i++){

		#pragma HLS PIPELINE

		memcpy(temp_data, indata + i, sizeof(ap_uint<512>));
		memcpy(temp_state, instate + i, sizeof(ap_uint<256>));

		int j,k;
		//printf("Data in kernel:\n");
		for(j=0; j<DROW; j++){
			#pragma HLS PIPELINE
			for(k=0; k<DCOL; k++){

				ap_uint<32> temp;
				int lo = FBIT*j*DCOL + FBIT*k;
				int hi = lo + FBIT - 1;
				temp = temp_data[0].range(hi, lo);

				data[j][k] = *((float *)&temp);
				//printf("%f ",(float)data[j][k]);
			}
			//printf("\n");
		}
		//printf("\nState in kernel: ");

		for(j=0; j<DROW; j++){
			#pragma HLS PIPELINE

			int lo = j*FBIT;
			int hi = lo + FBIT - 1;
			state[j] = temp_state[0].range(hi, lo);
			//printf("%d ",state[j].to_int());
		}//printf("\nState out kernel:");

		for(j=0; j<DROW; j++){

			#pragma HLS UNROLL
			if (state[j] != -1 && !in_circle(data[j], son)){
				state[j] = -1;
			}
			//printf("%d ", state[j].to_int());
		}//printf("\n");

		for(j=0; j<DROW; j++){
			#pragma HLS PIPELINE

			int lo = j*FBIT;
			int hi = lo + FBIT - 1;
			*(((ap_uint<32> *)&temp_state)+j) = state[j];
		}
		memcpy(instate + i, temp_state, sizeof(ap_int<256>));
	}

	return;
}

}
