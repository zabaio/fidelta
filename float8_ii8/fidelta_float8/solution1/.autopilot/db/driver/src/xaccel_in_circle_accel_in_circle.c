// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.2 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xaccel_in_circle_accel_in_circle.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XAccel_in_circle_accel_in_circle_CfgInitialize(XAccel_in_circle_accel_in_circle *InstancePtr, XAccel_in_circle_accel_in_circle_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XAccel_in_circle_accel_in_circle_Start(XAccel_in_circle_accel_in_circle *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAccel_in_circle_accel_in_circle_ReadReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_AP_CTRL) & 0x80;
    XAccel_in_circle_accel_in_circle_WriteReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XAccel_in_circle_accel_in_circle_IsDone(XAccel_in_circle_accel_in_circle *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAccel_in_circle_accel_in_circle_ReadReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XAccel_in_circle_accel_in_circle_IsIdle(XAccel_in_circle_accel_in_circle *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAccel_in_circle_accel_in_circle_ReadReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XAccel_in_circle_accel_in_circle_IsReady(XAccel_in_circle_accel_in_circle *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAccel_in_circle_accel_in_circle_ReadReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XAccel_in_circle_accel_in_circle_EnableAutoRestart(XAccel_in_circle_accel_in_circle *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAccel_in_circle_accel_in_circle_WriteReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XAccel_in_circle_accel_in_circle_DisableAutoRestart(XAccel_in_circle_accel_in_circle *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAccel_in_circle_accel_in_circle_WriteReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_AP_CTRL, 0);
}

void XAccel_in_circle_accel_in_circle_Set_indata_f0(XAccel_in_circle_accel_in_circle *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAccel_in_circle_accel_in_circle_WriteReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F0_DATA, (u32)(Data));
    XAccel_in_circle_accel_in_circle_WriteReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F0_DATA + 4, (u32)(Data >> 32));
}

u64 XAccel_in_circle_accel_in_circle_Get_indata_f0(XAccel_in_circle_accel_in_circle *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAccel_in_circle_accel_in_circle_ReadReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F0_DATA);
    Data += (u64)XAccel_in_circle_accel_in_circle_ReadReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F0_DATA + 4) << 32;
    return Data;
}

void XAccel_in_circle_accel_in_circle_Set_indata_f1(XAccel_in_circle_accel_in_circle *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAccel_in_circle_accel_in_circle_WriteReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F1_DATA, (u32)(Data));
    XAccel_in_circle_accel_in_circle_WriteReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F1_DATA + 4, (u32)(Data >> 32));
}

u64 XAccel_in_circle_accel_in_circle_Get_indata_f1(XAccel_in_circle_accel_in_circle *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAccel_in_circle_accel_in_circle_ReadReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F1_DATA);
    Data += (u64)XAccel_in_circle_accel_in_circle_ReadReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F1_DATA + 4) << 32;
    return Data;
}

void XAccel_in_circle_accel_in_circle_Set_indata_f2(XAccel_in_circle_accel_in_circle *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAccel_in_circle_accel_in_circle_WriteReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F2_DATA, (u32)(Data));
    XAccel_in_circle_accel_in_circle_WriteReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F2_DATA + 4, (u32)(Data >> 32));
}

u64 XAccel_in_circle_accel_in_circle_Get_indata_f2(XAccel_in_circle_accel_in_circle *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAccel_in_circle_accel_in_circle_ReadReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F2_DATA);
    Data += (u64)XAccel_in_circle_accel_in_circle_ReadReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F2_DATA + 4) << 32;
    return Data;
}

void XAccel_in_circle_accel_in_circle_Set_indata_f3(XAccel_in_circle_accel_in_circle *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAccel_in_circle_accel_in_circle_WriteReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F3_DATA, (u32)(Data));
    XAccel_in_circle_accel_in_circle_WriteReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F3_DATA + 4, (u32)(Data >> 32));
}

u64 XAccel_in_circle_accel_in_circle_Get_indata_f3(XAccel_in_circle_accel_in_circle *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAccel_in_circle_accel_in_circle_ReadReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F3_DATA);
    Data += (u64)XAccel_in_circle_accel_in_circle_ReadReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F3_DATA + 4) << 32;
    return Data;
}

void XAccel_in_circle_accel_in_circle_Set_indata_f4(XAccel_in_circle_accel_in_circle *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAccel_in_circle_accel_in_circle_WriteReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F4_DATA, (u32)(Data));
    XAccel_in_circle_accel_in_circle_WriteReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F4_DATA + 4, (u32)(Data >> 32));
}

u64 XAccel_in_circle_accel_in_circle_Get_indata_f4(XAccel_in_circle_accel_in_circle *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAccel_in_circle_accel_in_circle_ReadReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F4_DATA);
    Data += (u64)XAccel_in_circle_accel_in_circle_ReadReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F4_DATA + 4) << 32;
    return Data;
}

void XAccel_in_circle_accel_in_circle_Set_indata_f5(XAccel_in_circle_accel_in_circle *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAccel_in_circle_accel_in_circle_WriteReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F5_DATA, (u32)(Data));
    XAccel_in_circle_accel_in_circle_WriteReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F5_DATA + 4, (u32)(Data >> 32));
}

u64 XAccel_in_circle_accel_in_circle_Get_indata_f5(XAccel_in_circle_accel_in_circle *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAccel_in_circle_accel_in_circle_ReadReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F5_DATA);
    Data += (u64)XAccel_in_circle_accel_in_circle_ReadReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F5_DATA + 4) << 32;
    return Data;
}

void XAccel_in_circle_accel_in_circle_Set_indata_f6(XAccel_in_circle_accel_in_circle *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAccel_in_circle_accel_in_circle_WriteReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F6_DATA, (u32)(Data));
    XAccel_in_circle_accel_in_circle_WriteReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F6_DATA + 4, (u32)(Data >> 32));
}

u64 XAccel_in_circle_accel_in_circle_Get_indata_f6(XAccel_in_circle_accel_in_circle *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAccel_in_circle_accel_in_circle_ReadReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F6_DATA);
    Data += (u64)XAccel_in_circle_accel_in_circle_ReadReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F6_DATA + 4) << 32;
    return Data;
}

void XAccel_in_circle_accel_in_circle_Set_indata_f7(XAccel_in_circle_accel_in_circle *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAccel_in_circle_accel_in_circle_WriteReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F7_DATA, (u32)(Data));
    XAccel_in_circle_accel_in_circle_WriteReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F7_DATA + 4, (u32)(Data >> 32));
}

u64 XAccel_in_circle_accel_in_circle_Get_indata_f7(XAccel_in_circle_accel_in_circle *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAccel_in_circle_accel_in_circle_ReadReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F7_DATA);
    Data += (u64)XAccel_in_circle_accel_in_circle_ReadReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INDATA_F7_DATA + 4) << 32;
    return Data;
}

void XAccel_in_circle_accel_in_circle_Set_instate(XAccel_in_circle_accel_in_circle *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAccel_in_circle_accel_in_circle_WriteReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INSTATE_DATA, (u32)(Data));
    XAccel_in_circle_accel_in_circle_WriteReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INSTATE_DATA + 4, (u32)(Data >> 32));
}

u64 XAccel_in_circle_accel_in_circle_Get_instate(XAccel_in_circle_accel_in_circle *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAccel_in_circle_accel_in_circle_ReadReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INSTATE_DATA);
    Data += (u64)XAccel_in_circle_accel_in_circle_ReadReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_INSTATE_DATA + 4) << 32;
    return Data;
}

void XAccel_in_circle_accel_in_circle_InterruptGlobalEnable(XAccel_in_circle_accel_in_circle *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAccel_in_circle_accel_in_circle_WriteReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_GIE, 1);
}

void XAccel_in_circle_accel_in_circle_InterruptGlobalDisable(XAccel_in_circle_accel_in_circle *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAccel_in_circle_accel_in_circle_WriteReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_GIE, 0);
}

void XAccel_in_circle_accel_in_circle_InterruptEnable(XAccel_in_circle_accel_in_circle *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XAccel_in_circle_accel_in_circle_ReadReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_IER);
    XAccel_in_circle_accel_in_circle_WriteReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_IER, Register | Mask);
}

void XAccel_in_circle_accel_in_circle_InterruptDisable(XAccel_in_circle_accel_in_circle *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XAccel_in_circle_accel_in_circle_ReadReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_IER);
    XAccel_in_circle_accel_in_circle_WriteReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_IER, Register & (~Mask));
}

void XAccel_in_circle_accel_in_circle_InterruptClear(XAccel_in_circle_accel_in_circle *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAccel_in_circle_accel_in_circle_WriteReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_ISR, Mask);
}

u32 XAccel_in_circle_accel_in_circle_InterruptGetEnabled(XAccel_in_circle_accel_in_circle *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XAccel_in_circle_accel_in_circle_ReadReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_IER);
}

u32 XAccel_in_circle_accel_in_circle_InterruptGetStatus(XAccel_in_circle_accel_in_circle *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XAccel_in_circle_accel_in_circle_ReadReg(InstancePtr->Control_BaseAddress, XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_CONTROL_ADDR_ISR);
}

