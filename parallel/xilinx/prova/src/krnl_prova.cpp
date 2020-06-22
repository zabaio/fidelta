#include <string.h>
#include <ap_int.h>
#include <stdio.h>

extern "C" {

void accel_prova(int maxquery, ap_uint<512> *indata, ap_uint<256> *instate, ap_uint<256> *inson){

    #pragma HLS INTERFACE s_axilite port=maxquery bundle=control
	#pragma HLS INTERFACE s_axilite port=return bundle=control

	printf("%d \n", maxquery);

	return;
}

}
