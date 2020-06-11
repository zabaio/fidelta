// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.2 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// control
// 0x00 : Control signals
//        bit 0  - ap_start (Read/Write/COH)
//        bit 1  - ap_done (Read/COR)
//        bit 2  - ap_idle (Read)
//        bit 3  - ap_ready (Read)
//        bit 7  - auto_restart (Read/Write)
//        others - reserved
// 0x04 : Global Interrupt Enable Register
//        bit 0  - Global Interrupt Enable (Read/Write)
//        others - reserved
// 0x08 : IP Interrupt Enable Register (Read/Write)
//        bit 0  - Channel 0 (ap_done)
//        bit 1  - Channel 1 (ap_ready)
//        others - reserved
// 0x0c : IP Interrupt Status Register (Read/TOW)
//        bit 0  - Channel 0 (ap_done)
//        bit 1  - Channel 1 (ap_ready)
//        others - reserved
// 0x10 : Data signal of indata_f0
//        bit 31~0 - indata_f0[31:0] (Read/Write)
// 0x14 : Data signal of indata_f0
//        bit 31~0 - indata_f0[63:32] (Read/Write)
// 0x18 : reserved
// 0x1c : Data signal of indata_f1
//        bit 31~0 - indata_f1[31:0] (Read/Write)
// 0x20 : Data signal of indata_f1
//        bit 31~0 - indata_f1[63:32] (Read/Write)
// 0x24 : reserved
// 0x28 : Data signal of indata_f2
//        bit 31~0 - indata_f2[31:0] (Read/Write)
// 0x2c : Data signal of indata_f2
//        bit 31~0 - indata_f2[63:32] (Read/Write)
// 0x30 : reserved
// 0x34 : Data signal of indata_f3
//        bit 31~0 - indata_f3[31:0] (Read/Write)
// 0x38 : Data signal of indata_f3
//        bit 31~0 - indata_f3[63:32] (Read/Write)
// 0x3c : reserved
// 0x40 : Data signal of indata_f4
//        bit 31~0 - indata_f4[31:0] (Read/Write)
// 0x44 : Data signal of indata_f4
//        bit 31~0 - indata_f4[63:32] (Read/Write)
// 0x48 : reserved
// 0x4c : Data signal of indata_f5
//        bit 31~0 - indata_f5[31:0] (Read/Write)
// 0x50 : Data signal of indata_f5
//        bit 31~0 - indata_f5[63:32] (Read/Write)
// 0x54 : reserved
// 0x58 : Data signal of indata_f6
//        bit 31~0 - indata_f6[31:0] (Read/Write)
// 0x5c : Data signal of indata_f6
//        bit 31~0 - indata_f6[63:32] (Read/Write)
// 0x60 : reserved
// 0x64 : Data signal of indata_f7
//        bit 31~0 - indata_f7[31:0] (Read/Write)
// 0x68 : Data signal of indata_f7
//        bit 31~0 - indata_f7[63:32] (Read/Write)
// 0x6c : reserved
// 0x70 : Data signal of instate
//        bit 31~0 - instate[31:0] (Read/Write)
// 0x74 : Data signal of instate
//        bit 31~0 - instate[63:32] (Read/Write)
// 0x78 : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_AP_CTRL        0x00
#define XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_GIE            0x04
#define XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_IER            0x08
#define XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_ISR            0x0c
#define XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F0_DATA 0x10
#define XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_BITS_INDATA_F0_DATA 64
#define XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F1_DATA 0x1c
#define XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_BITS_INDATA_F1_DATA 64
#define XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F2_DATA 0x28
#define XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_BITS_INDATA_F2_DATA 64
#define XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F3_DATA 0x34
#define XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_BITS_INDATA_F3_DATA 64
#define XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F4_DATA 0x40
#define XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_BITS_INDATA_F4_DATA 64
#define XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F5_DATA 0x4c
#define XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_BITS_INDATA_F5_DATA 64
#define XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F6_DATA 0x58
#define XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_BITS_INDATA_F6_DATA 64
#define XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F7_DATA 0x64
#define XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_BITS_INDATA_F7_DATA 64
#define XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INSTATE_DATA   0x70
#define XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_BITS_INSTATE_DATA   64

