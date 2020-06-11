set moduleName in_circle
set isTopModule 0
set isTaskLevelControl 1
set isCombinational 0
set isDatapathOnly 1
set isFreeRunPipelineModule 0
set isPipelined 1
set pipeline_type function
set FunctionProtocol ap_ctrl_hs
set isOneStateSeq 0
set ProfileFlag 0
set StallSigGenFlag 0
set isEnableWaveformDebug 1
set C_modelName {in_circle}
set C_modelType { int 1 }
set C_modelArgList {
	{ innerdata_0_read float 32 regular  }
	{ innerdata_1_read float 32 regular  }
	{ father_0_read float 32 regular  }
	{ father_1_read float 32 regular  }
	{ father_2_read float 32 regular  }
	{ father_3_read float 32 regular  }
	{ father_4_read float 32 regular  }
	{ father_5_read float 32 regular  }
}
set C_modelArgMapList {[ 
	{ "Name" : "innerdata_0_read", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "innerdata_1_read", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "father_0_read", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "father_1_read", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "father_2_read", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "father_3_read", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "father_4_read", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "father_5_read", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "ap_return", "interface" : "wire", "bitwidth" : 1} ]}
# RTL Port declarations: 
set portNum 12
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ innerdata_0_read sc_in sc_lv 32 signal 0 } 
	{ innerdata_1_read sc_in sc_lv 32 signal 1 } 
	{ father_0_read sc_in sc_lv 32 signal 2 } 
	{ father_1_read sc_in sc_lv 32 signal 3 } 
	{ father_2_read sc_in sc_lv 32 signal 4 } 
	{ father_3_read sc_in sc_lv 32 signal 5 } 
	{ father_4_read sc_in sc_lv 32 signal 6 } 
	{ father_5_read sc_in sc_lv 32 signal 7 } 
	{ ap_return sc_out sc_lv 1 signal -1 } 
	{ ap_ce sc_in sc_logic 1 ce -1 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "innerdata_0_read", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "innerdata_0_read", "role": "default" }} , 
 	{ "name": "innerdata_1_read", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "innerdata_1_read", "role": "default" }} , 
 	{ "name": "father_0_read", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "father_0_read", "role": "default" }} , 
 	{ "name": "father_1_read", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "father_1_read", "role": "default" }} , 
 	{ "name": "father_2_read", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "father_2_read", "role": "default" }} , 
 	{ "name": "father_3_read", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "father_3_read", "role": "default" }} , 
 	{ "name": "father_4_read", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "father_4_read", "role": "default" }} , 
 	{ "name": "father_5_read", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "father_5_read", "role": "default" }} , 
 	{ "name": "ap_return", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "ap_return", "role": "default" }} , 
 	{ "name": "ap_ce", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "ce", "bundle":{"name": "ap_ce", "role": "default" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30"],
		"CDFG" : "in_circle",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "0", "ap_start" : "0", "ap_ready" : "0", "ap_done" : "0", "ap_continue" : "0", "ap_idle" : "0",
		"Pipeline" : "Aligned", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "1",
		"VariableLatency" : "0", "ExactLatency" : "16", "EstimateLatencyMin" : "16", "EstimateLatencyMax" : "16",
		"Combinational" : "0",
		"Datapath" : "1",
		"ClockEnable" : "1",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "innerdata_0_read", "Type" : "None", "Direction" : "I"},
			{"Name" : "innerdata_1_read", "Type" : "None", "Direction" : "I"},
			{"Name" : "father_0_read", "Type" : "None", "Direction" : "I"},
			{"Name" : "father_1_read", "Type" : "None", "Direction" : "I"},
			{"Name" : "father_2_read", "Type" : "None", "Direction" : "I"},
			{"Name" : "father_3_read", "Type" : "None", "Direction" : "I"},
			{"Name" : "father_4_read", "Type" : "None", "Direction" : "I"},
			{"Name" : "father_5_read", "Type" : "None", "Direction" : "I"}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U1", "Parent" : "0"},
	{"ID" : "2", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U2", "Parent" : "0"},
	{"ID" : "3", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U3", "Parent" : "0"},
	{"ID" : "4", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U4", "Parent" : "0"},
	{"ID" : "5", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U5", "Parent" : "0"},
	{"ID" : "6", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U6", "Parent" : "0"},
	{"ID" : "7", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0_U7", "Parent" : "0"},
	{"ID" : "8", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0_U8", "Parent" : "0"},
	{"ID" : "9", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0_U9", "Parent" : "0"},
	{"ID" : "10", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U10", "Parent" : "0"},
	{"ID" : "11", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U11", "Parent" : "0"},
	{"ID" : "12", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U12", "Parent" : "0"},
	{"ID" : "13", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U13", "Parent" : "0"},
	{"ID" : "14", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0_U14", "Parent" : "0"},
	{"ID" : "15", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U15", "Parent" : "0"},
	{"ID" : "16", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U16", "Parent" : "0"},
	{"ID" : "17", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U17", "Parent" : "0"},
	{"ID" : "18", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U18", "Parent" : "0"},
	{"ID" : "19", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U19", "Parent" : "0"},
	{"ID" : "20", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U20", "Parent" : "0"},
	{"ID" : "21", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U21", "Parent" : "0"},
	{"ID" : "22", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U22", "Parent" : "0"},
	{"ID" : "23", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U23", "Parent" : "0"},
	{"ID" : "24", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U24", "Parent" : "0"},
	{"ID" : "25", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U25", "Parent" : "0"},
	{"ID" : "26", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U26", "Parent" : "0"},
	{"ID" : "27", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U27", "Parent" : "0"},
	{"ID" : "28", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U28", "Parent" : "0"},
	{"ID" : "29", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U29", "Parent" : "0"},
	{"ID" : "30", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.accel_in_circle_fcmp_32ns_32ns_1_1_0_U30", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	in_circle {
		innerdata_0_read {Type I LastRead 0 FirstWrite -1}
		innerdata_1_read {Type I LastRead 0 FirstWrite -1}
		father_0_read {Type I LastRead 0 FirstWrite -1}
		father_1_read {Type I LastRead 0 FirstWrite -1}
		father_2_read {Type I LastRead 0 FirstWrite -1}
		father_3_read {Type I LastRead 0 FirstWrite -1}
		father_4_read {Type I LastRead 0 FirstWrite -1}
		father_5_read {Type I LastRead 0 FirstWrite -1}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "16", "Max" : "16"}
	, {"Name" : "Interval", "Min" : "1", "Max" : "1"}
]}

set PipelineEnableSignalInfo {[
]}

set Spec2ImplPortList { 
	innerdata_0_read { ap_none {  { innerdata_0_read in_data 0 32 } } }
	innerdata_1_read { ap_none {  { innerdata_1_read in_data 0 32 } } }
	father_0_read { ap_none {  { father_0_read in_data 0 32 } } }
	father_1_read { ap_none {  { father_1_read in_data 0 32 } } }
	father_2_read { ap_none {  { father_2_read in_data 0 32 } } }
	father_3_read { ap_none {  { father_3_read in_data 0 32 } } }
	father_4_read { ap_none {  { father_4_read in_data 0 32 } } }
	father_5_read { ap_none {  { father_5_read in_data 0 32 } } }
}
