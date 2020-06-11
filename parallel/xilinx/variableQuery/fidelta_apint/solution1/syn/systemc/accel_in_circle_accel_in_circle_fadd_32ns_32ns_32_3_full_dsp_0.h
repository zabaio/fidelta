// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.2 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __accel_in_circle_accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0__HH__
#define __accel_in_circle_accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0__HH__
#include "ACMP_fadd.h"
#include <systemc>

template<
    int ID,
    int NUM_STAGE,
    int din0_WIDTH,
    int din1_WIDTH,
    int dout_WIDTH>
SC_MODULE(accel_in_circle_accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0) {
    sc_core::sc_in_clk clk;
    sc_core::sc_in<sc_dt::sc_logic> reset;
    sc_core::sc_in<sc_dt::sc_logic> ce;
    sc_core::sc_in< sc_dt::sc_lv<din0_WIDTH> >   din0;
    sc_core::sc_in< sc_dt::sc_lv<din1_WIDTH> >   din1;
    sc_core::sc_out< sc_dt::sc_lv<dout_WIDTH> >   dout;



    ACMP_fadd<ID, 3, din0_WIDTH, din1_WIDTH, dout_WIDTH> ACMP_fadd_U;

    SC_CTOR(accel_in_circle_accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0):  ACMP_fadd_U ("ACMP_fadd_U") {
        ACMP_fadd_U.clk(clk);
        ACMP_fadd_U.reset(reset);
        ACMP_fadd_U.ce(ce);
        ACMP_fadd_U.din0(din0);
        ACMP_fadd_U.din1(din1);
        ACMP_fadd_U.dout(dout);

    }

};

#endif //
