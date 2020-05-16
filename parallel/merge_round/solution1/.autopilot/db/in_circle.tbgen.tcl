set moduleName in_circle
set isTopModule 1
set isTaskLevelControl 1
set isCombinational 0
set isDatapathOnly 0
set isFreeRunPipelineModule 0
set isPipelined 0
set pipeline_type none
set FunctionProtocol ap_ctrl_hs
set isOneStateSeq 0
set ProfileFlag 0
set StallSigGenFlag 0
set isEnableWaveformDebug 1
set C_modelName {in_circle}
set C_modelType { int 32 }
set C_modelArgList {
	{ t_p1_id int 32 unused {pointer 0}  }
	{ t_p1_x float 32 regular {pointer 0}  }
	{ t_p1_y float 32 regular {pointer 0}  }
	{ t_p2_id int 32 unused {pointer 0}  }
	{ t_p2_x float 32 regular {pointer 0}  }
	{ t_p2_y float 32 regular {pointer 0}  }
	{ t_p3_id int 32 unused {pointer 0}  }
	{ t_p3_x float 32 regular {pointer 0}  }
	{ t_p3_y float 32 regular {pointer 0}  }
	{ d_id int 32 unused {pointer 0}  }
	{ d_x float 32 regular {pointer 0}  }
	{ d_y float 32 regular {pointer 0}  }
}
set C_modelArgMapList {[ 
	{ "Name" : "t_p1_id", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "t.p1.id","cData": "int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}]} , 
 	{ "Name" : "t_p1_x", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "t.p1.x","cData": "float","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}]} , 
 	{ "Name" : "t_p1_y", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "t.p1.y","cData": "float","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}]} , 
 	{ "Name" : "t_p2_id", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "t.p2.id","cData": "int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}]} , 
 	{ "Name" : "t_p2_x", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "t.p2.x","cData": "float","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}]} , 
 	{ "Name" : "t_p2_y", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "t.p2.y","cData": "float","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}]} , 
 	{ "Name" : "t_p3_id", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "t.p3.id","cData": "int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}]} , 
 	{ "Name" : "t_p3_x", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "t.p3.x","cData": "float","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}]} , 
 	{ "Name" : "t_p3_y", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "t.p3.y","cData": "float","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}]} , 
 	{ "Name" : "d_id", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "d.id","cData": "int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}]} , 
 	{ "Name" : "d_x", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "d.x","cData": "float","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}]} , 
 	{ "Name" : "d_y", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "d.y","cData": "float","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}]} , 
 	{ "Name" : "ap_return", "interface" : "wire", "bitwidth" : 32,"bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "return","cData": "int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 1,"step" : 0}]}]}]} ]}
# RTL Port declarations: 
set portNum 19
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ t_p1_id sc_in sc_lv 32 signal 0 } 
	{ t_p1_x sc_in sc_lv 32 signal 1 } 
	{ t_p1_y sc_in sc_lv 32 signal 2 } 
	{ t_p2_id sc_in sc_lv 32 signal 3 } 
	{ t_p2_x sc_in sc_lv 32 signal 4 } 
	{ t_p2_y sc_in sc_lv 32 signal 5 } 
	{ t_p3_id sc_in sc_lv 32 signal 6 } 
	{ t_p3_x sc_in sc_lv 32 signal 7 } 
	{ t_p3_y sc_in sc_lv 32 signal 8 } 
	{ d_id sc_in sc_lv 32 signal 9 } 
	{ d_x sc_in sc_lv 32 signal 10 } 
	{ d_y sc_in sc_lv 32 signal 11 } 
	{ ap_return sc_out sc_lv 32 signal -1 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "t_p1_id", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "t_p1_id", "role": "default" }} , 
 	{ "name": "t_p1_x", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "t_p1_x", "role": "default" }} , 
 	{ "name": "t_p1_y", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "t_p1_y", "role": "default" }} , 
 	{ "name": "t_p2_id", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "t_p2_id", "role": "default" }} , 
 	{ "name": "t_p2_x", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "t_p2_x", "role": "default" }} , 
 	{ "name": "t_p2_y", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "t_p2_y", "role": "default" }} , 
 	{ "name": "t_p3_id", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "t_p3_id", "role": "default" }} , 
 	{ "name": "t_p3_x", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "t_p3_x", "role": "default" }} , 
 	{ "name": "t_p3_y", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "t_p3_y", "role": "default" }} , 
 	{ "name": "d_id", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "d_id", "role": "default" }} , 
 	{ "name": "d_x", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "d_x", "role": "default" }} , 
 	{ "name": "d_y", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "d_y", "role": "default" }} , 
 	{ "name": "ap_return", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return", "role": "default" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19"],
		"CDFG" : "in_circle",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "12", "EstimateLatencyMax" : "12",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "t_p1_id", "Type" : "None", "Direction" : "I"},
			{"Name" : "t_p1_x", "Type" : "None", "Direction" : "I"},
			{"Name" : "t_p1_y", "Type" : "None", "Direction" : "I"},
			{"Name" : "t_p2_id", "Type" : "None", "Direction" : "I"},
			{"Name" : "t_p2_x", "Type" : "None", "Direction" : "I"},
			{"Name" : "t_p2_y", "Type" : "None", "Direction" : "I"},
			{"Name" : "t_p3_id", "Type" : "None", "Direction" : "I"},
			{"Name" : "t_p3_x", "Type" : "None", "Direction" : "I"},
			{"Name" : "t_p3_y", "Type" : "None", "Direction" : "I"},
			{"Name" : "d_id", "Type" : "None", "Direction" : "I"},
			{"Name" : "d_x", "Type" : "None", "Direction" : "I"},
			{"Name" : "d_y", "Type" : "None", "Direction" : "I"}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.in_circle_faddfsub_32ns_32ns_32_2_full_dsp_1_U1", "Parent" : "0"},
	{"ID" : "2", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.in_circle_faddfsub_32ns_32ns_32_2_full_dsp_1_U2", "Parent" : "0"},
	{"ID" : "3", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.in_circle_faddfsub_32ns_32ns_32_2_full_dsp_1_U3", "Parent" : "0"},
	{"ID" : "4", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.in_circle_fsub_32ns_32ns_32_2_full_dsp_1_U4", "Parent" : "0"},
	{"ID" : "5", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.in_circle_fsub_32ns_32ns_32_2_full_dsp_1_U5", "Parent" : "0"},
	{"ID" : "6", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.in_circle_fsub_32ns_32ns_32_2_full_dsp_1_U6", "Parent" : "0"},
	{"ID" : "7", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.in_circle_fmul_32ns_32ns_32_2_max_dsp_1_U7", "Parent" : "0"},
	{"ID" : "8", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.in_circle_fmul_32ns_32ns_32_2_max_dsp_1_U8", "Parent" : "0"},
	{"ID" : "9", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.in_circle_fmul_32ns_32ns_32_2_max_dsp_1_U9", "Parent" : "0"},
	{"ID" : "10", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.in_circle_fmul_32ns_32ns_32_2_max_dsp_1_U10", "Parent" : "0"},
	{"ID" : "11", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.in_circle_fmul_32ns_32ns_32_2_max_dsp_1_U11", "Parent" : "0"},
	{"ID" : "12", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.in_circle_fmul_32ns_32ns_32_2_max_dsp_1_U12", "Parent" : "0"},
	{"ID" : "13", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.in_circle_fmul_32ns_32ns_32_2_max_dsp_1_U13", "Parent" : "0"},
	{"ID" : "14", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.in_circle_fmul_32ns_32ns_32_2_max_dsp_1_U14", "Parent" : "0"},
	{"ID" : "15", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.in_circle_fmul_32ns_32ns_32_2_max_dsp_1_U15", "Parent" : "0"},
	{"ID" : "16", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.in_circle_fmul_32ns_32ns_32_2_max_dsp_1_U16", "Parent" : "0"},
	{"ID" : "17", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.in_circle_fmul_32ns_32ns_32_2_max_dsp_1_U17", "Parent" : "0"},
	{"ID" : "18", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.in_circle_fmul_32ns_32ns_32_2_max_dsp_1_U18", "Parent" : "0"},
	{"ID" : "19", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.in_circle_fcmp_32ns_32ns_1_1_1_U19", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	in_circle {
		t_p1_id {Type I LastRead -1 FirstWrite -1}
		t_p1_x {Type I LastRead 0 FirstWrite -1}
		t_p1_y {Type I LastRead 0 FirstWrite -1}
		t_p2_id {Type I LastRead -1 FirstWrite -1}
		t_p2_x {Type I LastRead 0 FirstWrite -1}
		t_p2_y {Type I LastRead 0 FirstWrite -1}
		t_p3_id {Type I LastRead -1 FirstWrite -1}
		t_p3_x {Type I LastRead 0 FirstWrite -1}
		t_p3_y {Type I LastRead 0 FirstWrite -1}
		d_id {Type I LastRead -1 FirstWrite -1}
		d_x {Type I LastRead 0 FirstWrite -1}
		d_y {Type I LastRead 0 FirstWrite -1}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "12", "Max" : "12"}
	, {"Name" : "Interval", "Min" : "13", "Max" : "13"}
]}

set PipelineEnableSignalInfo {[
]}

set Spec2ImplPortList { 
	t_p1_id { ap_none {  { t_p1_id in_data 0 32 } } }
	t_p1_x { ap_none {  { t_p1_x in_data 0 32 } } }
	t_p1_y { ap_none {  { t_p1_y in_data 0 32 } } }
	t_p2_id { ap_none {  { t_p2_id in_data 0 32 } } }
	t_p2_x { ap_none {  { t_p2_x in_data 0 32 } } }
	t_p2_y { ap_none {  { t_p2_y in_data 0 32 } } }
	t_p3_id { ap_none {  { t_p3_id in_data 0 32 } } }
	t_p3_x { ap_none {  { t_p3_x in_data 0 32 } } }
	t_p3_y { ap_none {  { t_p3_y in_data 0 32 } } }
	d_id { ap_none {  { d_id in_data 0 32 } } }
	d_x { ap_none {  { d_x in_data 0 32 } } }
	d_y { ap_none {  { d_y in_data 0 32 } } }
}

set busDeadlockParameterList { 
}

# RTL port scheduling information:
set fifoSchedulingInfoList { 
}

# RTL bus port read request latency information:
set busReadReqLatencyList { 
}

# RTL bus port write response latency information:
set busWriteResLatencyList { 
}

# RTL array port load latency information:
set memoryLoadLatencyList { 
}
