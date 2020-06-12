// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.2 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xaccel_in_circle_accel_in_circle.h"

extern XAccel_in_circle_accel_in_circle_Config XAccel_in_circle_accel_in_circle_ConfigTable[];

XAccel_in_circle_accel_in_circle_Config *XAccel_in_circle_accel_in_circle_LookupConfig(u16 DeviceId) {
	XAccel_in_circle_accel_in_circle_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_NUM_INSTANCES; Index++) {
		if (XAccel_in_circle_accel_in_circle_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XAccel_in_circle_accel_in_circle_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XAccel_in_circle_accel_in_circle_Initialize(XAccel_in_circle_accel_in_circle *InstancePtr, u16 DeviceId) {
	XAccel_in_circle_accel_in_circle_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XAccel_in_circle_accel_in_circle_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XAccel_in_circle_accel_in_circle_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

