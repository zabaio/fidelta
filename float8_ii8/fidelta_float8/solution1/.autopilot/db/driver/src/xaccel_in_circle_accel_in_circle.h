// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.2 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_H
#define XACCEL_IN_CIRCLE_ACCEL_IN_CIRCLE_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xaccel_in_circle_accel_in_circle_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
#else
typedef struct {
    u16 DeviceId;
    u32 Control_BaseAddress;
} XAccel_in_circle_accel_in_circle_Config;
#endif

typedef struct {
    u32 Control_BaseAddress;
    u32 IsReady;
} XAccel_in_circle_accel_in_circle;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XAccel_in_circle_accel_in_circle_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XAccel_in_circle_accel_in_circle_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XAccel_in_circle_accel_in_circle_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XAccel_in_circle_accel_in_circle_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XAccel_in_circle_accel_in_circle_Initialize(XAccel_in_circle_accel_in_circle *InstancePtr, u16 DeviceId);
XAccel_in_circle_accel_in_circle_Config* XAccel_in_circle_accel_in_circle_LookupConfig(u16 DeviceId);
int XAccel_in_circle_accel_in_circle_CfgInitialize(XAccel_in_circle_accel_in_circle *InstancePtr, XAccel_in_circle_accel_in_circle_Config *ConfigPtr);
#else
int XAccel_in_circle_accel_in_circle_Initialize(XAccel_in_circle_accel_in_circle *InstancePtr, const char* InstanceName);
int XAccel_in_circle_accel_in_circle_Release(XAccel_in_circle_accel_in_circle *InstancePtr);
#endif

void XAccel_in_circle_accel_in_circle_Start(XAccel_in_circle_accel_in_circle *InstancePtr);
u32 XAccel_in_circle_accel_in_circle_IsDone(XAccel_in_circle_accel_in_circle *InstancePtr);
u32 XAccel_in_circle_accel_in_circle_IsIdle(XAccel_in_circle_accel_in_circle *InstancePtr);
u32 XAccel_in_circle_accel_in_circle_IsReady(XAccel_in_circle_accel_in_circle *InstancePtr);
void XAccel_in_circle_accel_in_circle_EnableAutoRestart(XAccel_in_circle_accel_in_circle *InstancePtr);
void XAccel_in_circle_accel_in_circle_DisableAutoRestart(XAccel_in_circle_accel_in_circle *InstancePtr);

void XAccel_in_circle_accel_in_circle_Set_indata_f0(XAccel_in_circle_accel_in_circle *InstancePtr, u64 Data);
u64 XAccel_in_circle_accel_in_circle_Get_indata_f0(XAccel_in_circle_accel_in_circle *InstancePtr);
void XAccel_in_circle_accel_in_circle_Set_indata_f1(XAccel_in_circle_accel_in_circle *InstancePtr, u64 Data);
u64 XAccel_in_circle_accel_in_circle_Get_indata_f1(XAccel_in_circle_accel_in_circle *InstancePtr);
void XAccel_in_circle_accel_in_circle_Set_indata_f2(XAccel_in_circle_accel_in_circle *InstancePtr, u64 Data);
u64 XAccel_in_circle_accel_in_circle_Get_indata_f2(XAccel_in_circle_accel_in_circle *InstancePtr);
void XAccel_in_circle_accel_in_circle_Set_indata_f3(XAccel_in_circle_accel_in_circle *InstancePtr, u64 Data);
u64 XAccel_in_circle_accel_in_circle_Get_indata_f3(XAccel_in_circle_accel_in_circle *InstancePtr);
void XAccel_in_circle_accel_in_circle_Set_indata_f4(XAccel_in_circle_accel_in_circle *InstancePtr, u64 Data);
u64 XAccel_in_circle_accel_in_circle_Get_indata_f4(XAccel_in_circle_accel_in_circle *InstancePtr);
void XAccel_in_circle_accel_in_circle_Set_indata_f5(XAccel_in_circle_accel_in_circle *InstancePtr, u64 Data);
u64 XAccel_in_circle_accel_in_circle_Get_indata_f5(XAccel_in_circle_accel_in_circle *InstancePtr);
void XAccel_in_circle_accel_in_circle_Set_indata_f6(XAccel_in_circle_accel_in_circle *InstancePtr, u64 Data);
u64 XAccel_in_circle_accel_in_circle_Get_indata_f6(XAccel_in_circle_accel_in_circle *InstancePtr);
void XAccel_in_circle_accel_in_circle_Set_indata_f7(XAccel_in_circle_accel_in_circle *InstancePtr, u64 Data);
u64 XAccel_in_circle_accel_in_circle_Get_indata_f7(XAccel_in_circle_accel_in_circle *InstancePtr);
void XAccel_in_circle_accel_in_circle_Set_instate(XAccel_in_circle_accel_in_circle *InstancePtr, u64 Data);
u64 XAccel_in_circle_accel_in_circle_Get_instate(XAccel_in_circle_accel_in_circle *InstancePtr);

void XAccel_in_circle_accel_in_circle_InterruptGlobalEnable(XAccel_in_circle_accel_in_circle *InstancePtr);
void XAccel_in_circle_accel_in_circle_InterruptGlobalDisable(XAccel_in_circle_accel_in_circle *InstancePtr);
void XAccel_in_circle_accel_in_circle_InterruptEnable(XAccel_in_circle_accel_in_circle *InstancePtr, u32 Mask);
void XAccel_in_circle_accel_in_circle_InterruptDisable(XAccel_in_circle_accel_in_circle *InstancePtr, u32 Mask);
void XAccel_in_circle_accel_in_circle_InterruptClear(XAccel_in_circle_accel_in_circle *InstancePtr, u32 Mask);
u32 XAccel_in_circle_accel_in_circle_InterruptGetEnabled(XAccel_in_circle_accel_in_circle *InstancePtr);
u32 XAccel_in_circle_accel_in_circle_InterruptGetStatus(XAccel_in_circle_accel_in_circle *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
