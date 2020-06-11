set moduleName accel_in_circle
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
set C_modelName {accel_in_circle}
set C_modelType { void 0 }
set C_modelArgList {
	{ gmem1 int 512 regular {axi_master 0}  }
	{ gmem0 int 256 regular {axi_master 2}  }
	{ gmem2 int 256 regular {axi_master 0}  }
	{ indata_V int 64 regular {axi_slave 0}  }
	{ instate_V int 64 regular {axi_slave 0}  }
	{ infather_V int 64 regular {axi_slave 0}  }
	{ inmaxquery int 32 regular {axi_slave 0}  }
}
set C_modelArgMapList {[ 
	{ "Name" : "gmem1", "interface" : "axi_master", "bitwidth" : 512, "direction" : "READONLY", "bitSlice":[{"low":0,"up":511,"cElement": [{"cName": "indata.V","cData": "uint512","bit_use": { "low": 0,"up": 511},"offset": { "type": "dynamic","port_name": "indata_V","bundle": "control"},"direction": "READONLY","cArray": [{"low" : 0,"up" : 3,"step" : 1}]}]}]} , 
 	{ "Name" : "gmem0", "interface" : "axi_master", "bitwidth" : 256, "direction" : "READWRITE", "bitSlice":[{"low":0,"up":255,"cElement": [{"cName": "instate.V","cData": "uint256","bit_use": { "low": 0,"up": 255},"offset": { "type": "dynamic","port_name": "instate_V","bundle": "control"},"direction": "READWRITE","cArray": [{"low" : 0,"up" : 3,"step" : 1}]}]}]} , 
 	{ "Name" : "gmem2", "interface" : "axi_master", "bitwidth" : 256, "direction" : "READONLY", "bitSlice":[{"low":0,"up":255,"cElement": [{"cName": "infather.V","cData": "uint256","bit_use": { "low": 0,"up": 255},"offset": { "type": "dynamic","port_name": "infather_V","bundle": "AXILiteS"},"direction": "READONLY","cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}]} , 
 	{ "Name" : "indata_V", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":16}, "offset_end" : {"in":27}} , 
 	{ "Name" : "instate_V", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":28}, "offset_end" : {"in":39}} , 
 	{ "Name" : "infather_V", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":40}, "offset_end" : {"in":51}} , 
 	{ "Name" : "inmaxquery", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "inmaxquery","cData": "int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}], "offset" : {"in":52}, "offset_end" : {"in":59}} ]}
# RTL Port declarations: 
set portNum 155
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst_n sc_in sc_logic 1 reset -1 active_low_sync } 
	{ m_axi_gmem1_AWVALID sc_out sc_logic 1 signal 0 } 
	{ m_axi_gmem1_AWREADY sc_in sc_logic 1 signal 0 } 
	{ m_axi_gmem1_AWADDR sc_out sc_lv 64 signal 0 } 
	{ m_axi_gmem1_AWID sc_out sc_lv 1 signal 0 } 
	{ m_axi_gmem1_AWLEN sc_out sc_lv 8 signal 0 } 
	{ m_axi_gmem1_AWSIZE sc_out sc_lv 3 signal 0 } 
	{ m_axi_gmem1_AWBURST sc_out sc_lv 2 signal 0 } 
	{ m_axi_gmem1_AWLOCK sc_out sc_lv 2 signal 0 } 
	{ m_axi_gmem1_AWCACHE sc_out sc_lv 4 signal 0 } 
	{ m_axi_gmem1_AWPROT sc_out sc_lv 3 signal 0 } 
	{ m_axi_gmem1_AWQOS sc_out sc_lv 4 signal 0 } 
	{ m_axi_gmem1_AWREGION sc_out sc_lv 4 signal 0 } 
	{ m_axi_gmem1_AWUSER sc_out sc_lv 1 signal 0 } 
	{ m_axi_gmem1_WVALID sc_out sc_logic 1 signal 0 } 
	{ m_axi_gmem1_WREADY sc_in sc_logic 1 signal 0 } 
	{ m_axi_gmem1_WDATA sc_out sc_lv 512 signal 0 } 
	{ m_axi_gmem1_WSTRB sc_out sc_lv 64 signal 0 } 
	{ m_axi_gmem1_WLAST sc_out sc_logic 1 signal 0 } 
	{ m_axi_gmem1_WID sc_out sc_lv 1 signal 0 } 
	{ m_axi_gmem1_WUSER sc_out sc_lv 1 signal 0 } 
	{ m_axi_gmem1_ARVALID sc_out sc_logic 1 signal 0 } 
	{ m_axi_gmem1_ARREADY sc_in sc_logic 1 signal 0 } 
	{ m_axi_gmem1_ARADDR sc_out sc_lv 64 signal 0 } 
	{ m_axi_gmem1_ARID sc_out sc_lv 1 signal 0 } 
	{ m_axi_gmem1_ARLEN sc_out sc_lv 8 signal 0 } 
	{ m_axi_gmem1_ARSIZE sc_out sc_lv 3 signal 0 } 
	{ m_axi_gmem1_ARBURST sc_out sc_lv 2 signal 0 } 
	{ m_axi_gmem1_ARLOCK sc_out sc_lv 2 signal 0 } 
	{ m_axi_gmem1_ARCACHE sc_out sc_lv 4 signal 0 } 
	{ m_axi_gmem1_ARPROT sc_out sc_lv 3 signal 0 } 
	{ m_axi_gmem1_ARQOS sc_out sc_lv 4 signal 0 } 
	{ m_axi_gmem1_ARREGION sc_out sc_lv 4 signal 0 } 
	{ m_axi_gmem1_ARUSER sc_out sc_lv 1 signal 0 } 
	{ m_axi_gmem1_RVALID sc_in sc_logic 1 signal 0 } 
	{ m_axi_gmem1_RREADY sc_out sc_logic 1 signal 0 } 
	{ m_axi_gmem1_RDATA sc_in sc_lv 512 signal 0 } 
	{ m_axi_gmem1_RLAST sc_in sc_logic 1 signal 0 } 
	{ m_axi_gmem1_RID sc_in sc_lv 1 signal 0 } 
	{ m_axi_gmem1_RUSER sc_in sc_lv 1 signal 0 } 
	{ m_axi_gmem1_RRESP sc_in sc_lv 2 signal 0 } 
	{ m_axi_gmem1_BVALID sc_in sc_logic 1 signal 0 } 
	{ m_axi_gmem1_BREADY sc_out sc_logic 1 signal 0 } 
	{ m_axi_gmem1_BRESP sc_in sc_lv 2 signal 0 } 
	{ m_axi_gmem1_BID sc_in sc_lv 1 signal 0 } 
	{ m_axi_gmem1_BUSER sc_in sc_lv 1 signal 0 } 
	{ m_axi_gmem0_AWVALID sc_out sc_logic 1 signal 1 } 
	{ m_axi_gmem0_AWREADY sc_in sc_logic 1 signal 1 } 
	{ m_axi_gmem0_AWADDR sc_out sc_lv 64 signal 1 } 
	{ m_axi_gmem0_AWID sc_out sc_lv 1 signal 1 } 
	{ m_axi_gmem0_AWLEN sc_out sc_lv 8 signal 1 } 
	{ m_axi_gmem0_AWSIZE sc_out sc_lv 3 signal 1 } 
	{ m_axi_gmem0_AWBURST sc_out sc_lv 2 signal 1 } 
	{ m_axi_gmem0_AWLOCK sc_out sc_lv 2 signal 1 } 
	{ m_axi_gmem0_AWCACHE sc_out sc_lv 4 signal 1 } 
	{ m_axi_gmem0_AWPROT sc_out sc_lv 3 signal 1 } 
	{ m_axi_gmem0_AWQOS sc_out sc_lv 4 signal 1 } 
	{ m_axi_gmem0_AWREGION sc_out sc_lv 4 signal 1 } 
	{ m_axi_gmem0_AWUSER sc_out sc_lv 1 signal 1 } 
	{ m_axi_gmem0_WVALID sc_out sc_logic 1 signal 1 } 
	{ m_axi_gmem0_WREADY sc_in sc_logic 1 signal 1 } 
	{ m_axi_gmem0_WDATA sc_out sc_lv 256 signal 1 } 
	{ m_axi_gmem0_WSTRB sc_out sc_lv 32 signal 1 } 
	{ m_axi_gmem0_WLAST sc_out sc_logic 1 signal 1 } 
	{ m_axi_gmem0_WID sc_out sc_lv 1 signal 1 } 
	{ m_axi_gmem0_WUSER sc_out sc_lv 1 signal 1 } 
	{ m_axi_gmem0_ARVALID sc_out sc_logic 1 signal 1 } 
	{ m_axi_gmem0_ARREADY sc_in sc_logic 1 signal 1 } 
	{ m_axi_gmem0_ARADDR sc_out sc_lv 64 signal 1 } 
	{ m_axi_gmem0_ARID sc_out sc_lv 1 signal 1 } 
	{ m_axi_gmem0_ARLEN sc_out sc_lv 8 signal 1 } 
	{ m_axi_gmem0_ARSIZE sc_out sc_lv 3 signal 1 } 
	{ m_axi_gmem0_ARBURST sc_out sc_lv 2 signal 1 } 
	{ m_axi_gmem0_ARLOCK sc_out sc_lv 2 signal 1 } 
	{ m_axi_gmem0_ARCACHE sc_out sc_lv 4 signal 1 } 
	{ m_axi_gmem0_ARPROT sc_out sc_lv 3 signal 1 } 
	{ m_axi_gmem0_ARQOS sc_out sc_lv 4 signal 1 } 
	{ m_axi_gmem0_ARREGION sc_out sc_lv 4 signal 1 } 
	{ m_axi_gmem0_ARUSER sc_out sc_lv 1 signal 1 } 
	{ m_axi_gmem0_RVALID sc_in sc_logic 1 signal 1 } 
	{ m_axi_gmem0_RREADY sc_out sc_logic 1 signal 1 } 
	{ m_axi_gmem0_RDATA sc_in sc_lv 256 signal 1 } 
	{ m_axi_gmem0_RLAST sc_in sc_logic 1 signal 1 } 
	{ m_axi_gmem0_RID sc_in sc_lv 1 signal 1 } 
	{ m_axi_gmem0_RUSER sc_in sc_lv 1 signal 1 } 
	{ m_axi_gmem0_RRESP sc_in sc_lv 2 signal 1 } 
	{ m_axi_gmem0_BVALID sc_in sc_logic 1 signal 1 } 
	{ m_axi_gmem0_BREADY sc_out sc_logic 1 signal 1 } 
	{ m_axi_gmem0_BRESP sc_in sc_lv 2 signal 1 } 
	{ m_axi_gmem0_BID sc_in sc_lv 1 signal 1 } 
	{ m_axi_gmem0_BUSER sc_in sc_lv 1 signal 1 } 
	{ m_axi_gmem2_AWVALID sc_out sc_logic 1 signal 2 } 
	{ m_axi_gmem2_AWREADY sc_in sc_logic 1 signal 2 } 
	{ m_axi_gmem2_AWADDR sc_out sc_lv 64 signal 2 } 
	{ m_axi_gmem2_AWID sc_out sc_lv 1 signal 2 } 
	{ m_axi_gmem2_AWLEN sc_out sc_lv 8 signal 2 } 
	{ m_axi_gmem2_AWSIZE sc_out sc_lv 3 signal 2 } 
	{ m_axi_gmem2_AWBURST sc_out sc_lv 2 signal 2 } 
	{ m_axi_gmem2_AWLOCK sc_out sc_lv 2 signal 2 } 
	{ m_axi_gmem2_AWCACHE sc_out sc_lv 4 signal 2 } 
	{ m_axi_gmem2_AWPROT sc_out sc_lv 3 signal 2 } 
	{ m_axi_gmem2_AWQOS sc_out sc_lv 4 signal 2 } 
	{ m_axi_gmem2_AWREGION sc_out sc_lv 4 signal 2 } 
	{ m_axi_gmem2_AWUSER sc_out sc_lv 1 signal 2 } 
	{ m_axi_gmem2_WVALID sc_out sc_logic 1 signal 2 } 
	{ m_axi_gmem2_WREADY sc_in sc_logic 1 signal 2 } 
	{ m_axi_gmem2_WDATA sc_out sc_lv 256 signal 2 } 
	{ m_axi_gmem2_WSTRB sc_out sc_lv 32 signal 2 } 
	{ m_axi_gmem2_WLAST sc_out sc_logic 1 signal 2 } 
	{ m_axi_gmem2_WID sc_out sc_lv 1 signal 2 } 
	{ m_axi_gmem2_WUSER sc_out sc_lv 1 signal 2 } 
	{ m_axi_gmem2_ARVALID sc_out sc_logic 1 signal 2 } 
	{ m_axi_gmem2_ARREADY sc_in sc_logic 1 signal 2 } 
	{ m_axi_gmem2_ARADDR sc_out sc_lv 64 signal 2 } 
	{ m_axi_gmem2_ARID sc_out sc_lv 1 signal 2 } 
	{ m_axi_gmem2_ARLEN sc_out sc_lv 8 signal 2 } 
	{ m_axi_gmem2_ARSIZE sc_out sc_lv 3 signal 2 } 
	{ m_axi_gmem2_ARBURST sc_out sc_lv 2 signal 2 } 
	{ m_axi_gmem2_ARLOCK sc_out sc_lv 2 signal 2 } 
	{ m_axi_gmem2_ARCACHE sc_out sc_lv 4 signal 2 } 
	{ m_axi_gmem2_ARPROT sc_out sc_lv 3 signal 2 } 
	{ m_axi_gmem2_ARQOS sc_out sc_lv 4 signal 2 } 
	{ m_axi_gmem2_ARREGION sc_out sc_lv 4 signal 2 } 
	{ m_axi_gmem2_ARUSER sc_out sc_lv 1 signal 2 } 
	{ m_axi_gmem2_RVALID sc_in sc_logic 1 signal 2 } 
	{ m_axi_gmem2_RREADY sc_out sc_logic 1 signal 2 } 
	{ m_axi_gmem2_RDATA sc_in sc_lv 256 signal 2 } 
	{ m_axi_gmem2_RLAST sc_in sc_logic 1 signal 2 } 
	{ m_axi_gmem2_RID sc_in sc_lv 1 signal 2 } 
	{ m_axi_gmem2_RUSER sc_in sc_lv 1 signal 2 } 
	{ m_axi_gmem2_RRESP sc_in sc_lv 2 signal 2 } 
	{ m_axi_gmem2_BVALID sc_in sc_logic 1 signal 2 } 
	{ m_axi_gmem2_BREADY sc_out sc_logic 1 signal 2 } 
	{ m_axi_gmem2_BRESP sc_in sc_lv 2 signal 2 } 
	{ m_axi_gmem2_BID sc_in sc_lv 1 signal 2 } 
	{ m_axi_gmem2_BUSER sc_in sc_lv 1 signal 2 } 
	{ s_axi_control_AWVALID sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_AWREADY sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_AWADDR sc_in sc_lv 6 signal -1 } 
	{ s_axi_control_WVALID sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_WREADY sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_WDATA sc_in sc_lv 32 signal -1 } 
	{ s_axi_control_WSTRB sc_in sc_lv 4 signal -1 } 
	{ s_axi_control_ARVALID sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_ARREADY sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_ARADDR sc_in sc_lv 6 signal -1 } 
	{ s_axi_control_RVALID sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_RREADY sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_RDATA sc_out sc_lv 32 signal -1 } 
	{ s_axi_control_RRESP sc_out sc_lv 2 signal -1 } 
	{ s_axi_control_BVALID sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_BREADY sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_BRESP sc_out sc_lv 2 signal -1 } 
	{ interrupt sc_out sc_logic 1 signal -1 } 
}
set NewPortList {[ 
	{ "name": "s_axi_control_AWADDR", "direction": "in", "datatype": "sc_lv", "bitwidth":6, "type": "signal", "bundle":{"name": "control", "role": "AWADDR" },"address":[{"name":"accel_in_circle","role":"start","value":"0","valid_bit":"0"},{"name":"accel_in_circle","role":"continue","value":"0","valid_bit":"4"},{"name":"accel_in_circle","role":"auto_start","value":"0","valid_bit":"7"},{"name":"indata_V","role":"data","value":"16"},{"name":"instate_V","role":"data","value":"28"},{"name":"infather_V","role":"data","value":"40"},{"name":"inmaxquery","role":"data","value":"52"}] },
	{ "name": "s_axi_control_AWVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "AWVALID" } },
	{ "name": "s_axi_control_AWREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "AWREADY" } },
	{ "name": "s_axi_control_WVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "WVALID" } },
	{ "name": "s_axi_control_WREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "WREADY" } },
	{ "name": "s_axi_control_WDATA", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "control", "role": "WDATA" } },
	{ "name": "s_axi_control_WSTRB", "direction": "in", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "control", "role": "WSTRB" } },
	{ "name": "s_axi_control_ARADDR", "direction": "in", "datatype": "sc_lv", "bitwidth":6, "type": "signal", "bundle":{"name": "control", "role": "ARADDR" },"address":[{"name":"accel_in_circle","role":"start","value":"0","valid_bit":"0"},{"name":"accel_in_circle","role":"done","value":"0","valid_bit":"1"},{"name":"accel_in_circle","role":"idle","value":"0","valid_bit":"2"},{"name":"accel_in_circle","role":"ready","value":"0","valid_bit":"3"},{"name":"accel_in_circle","role":"auto_start","value":"0","valid_bit":"7"}] },
	{ "name": "s_axi_control_ARVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "ARVALID" } },
	{ "name": "s_axi_control_ARREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "ARREADY" } },
	{ "name": "s_axi_control_RVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "RVALID" } },
	{ "name": "s_axi_control_RREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "RREADY" } },
	{ "name": "s_axi_control_RDATA", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "control", "role": "RDATA" } },
	{ "name": "s_axi_control_RRESP", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "control", "role": "RRESP" } },
	{ "name": "s_axi_control_BVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "BVALID" } },
	{ "name": "s_axi_control_BREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "BREADY" } },
	{ "name": "s_axi_control_BRESP", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "control", "role": "BRESP" } },
	{ "name": "interrupt", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "interrupt" } }, 
 	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst_n", "role": "default" }} , 
 	{ "name": "m_axi_gmem1_AWVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "AWVALID" }} , 
 	{ "name": "m_axi_gmem1_AWREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "AWREADY" }} , 
 	{ "name": "m_axi_gmem1_AWADDR", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "gmem1", "role": "AWADDR" }} , 
 	{ "name": "m_axi_gmem1_AWID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "AWID" }} , 
 	{ "name": "m_axi_gmem1_AWLEN", "direction": "out", "datatype": "sc_lv", "bitwidth":8, "type": "signal", "bundle":{"name": "gmem1", "role": "AWLEN" }} , 
 	{ "name": "m_axi_gmem1_AWSIZE", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "gmem1", "role": "AWSIZE" }} , 
 	{ "name": "m_axi_gmem1_AWBURST", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem1", "role": "AWBURST" }} , 
 	{ "name": "m_axi_gmem1_AWLOCK", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem1", "role": "AWLOCK" }} , 
 	{ "name": "m_axi_gmem1_AWCACHE", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem1", "role": "AWCACHE" }} , 
 	{ "name": "m_axi_gmem1_AWPROT", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "gmem1", "role": "AWPROT" }} , 
 	{ "name": "m_axi_gmem1_AWQOS", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem1", "role": "AWQOS" }} , 
 	{ "name": "m_axi_gmem1_AWREGION", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem1", "role": "AWREGION" }} , 
 	{ "name": "m_axi_gmem1_AWUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "AWUSER" }} , 
 	{ "name": "m_axi_gmem1_WVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "WVALID" }} , 
 	{ "name": "m_axi_gmem1_WREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "WREADY" }} , 
 	{ "name": "m_axi_gmem1_WDATA", "direction": "out", "datatype": "sc_lv", "bitwidth":512, "type": "signal", "bundle":{"name": "gmem1", "role": "WDATA" }} , 
 	{ "name": "m_axi_gmem1_WSTRB", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "gmem1", "role": "WSTRB" }} , 
 	{ "name": "m_axi_gmem1_WLAST", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "WLAST" }} , 
 	{ "name": "m_axi_gmem1_WID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "WID" }} , 
 	{ "name": "m_axi_gmem1_WUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "WUSER" }} , 
 	{ "name": "m_axi_gmem1_ARVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "ARVALID" }} , 
 	{ "name": "m_axi_gmem1_ARREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "ARREADY" }} , 
 	{ "name": "m_axi_gmem1_ARADDR", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "gmem1", "role": "ARADDR" }} , 
 	{ "name": "m_axi_gmem1_ARID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "ARID" }} , 
 	{ "name": "m_axi_gmem1_ARLEN", "direction": "out", "datatype": "sc_lv", "bitwidth":8, "type": "signal", "bundle":{"name": "gmem1", "role": "ARLEN" }} , 
 	{ "name": "m_axi_gmem1_ARSIZE", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "gmem1", "role": "ARSIZE" }} , 
 	{ "name": "m_axi_gmem1_ARBURST", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem1", "role": "ARBURST" }} , 
 	{ "name": "m_axi_gmem1_ARLOCK", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem1", "role": "ARLOCK" }} , 
 	{ "name": "m_axi_gmem1_ARCACHE", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem1", "role": "ARCACHE" }} , 
 	{ "name": "m_axi_gmem1_ARPROT", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "gmem1", "role": "ARPROT" }} , 
 	{ "name": "m_axi_gmem1_ARQOS", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem1", "role": "ARQOS" }} , 
 	{ "name": "m_axi_gmem1_ARREGION", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem1", "role": "ARREGION" }} , 
 	{ "name": "m_axi_gmem1_ARUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "ARUSER" }} , 
 	{ "name": "m_axi_gmem1_RVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "RVALID" }} , 
 	{ "name": "m_axi_gmem1_RREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "RREADY" }} , 
 	{ "name": "m_axi_gmem1_RDATA", "direction": "in", "datatype": "sc_lv", "bitwidth":512, "type": "signal", "bundle":{"name": "gmem1", "role": "RDATA" }} , 
 	{ "name": "m_axi_gmem1_RLAST", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "RLAST" }} , 
 	{ "name": "m_axi_gmem1_RID", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "RID" }} , 
 	{ "name": "m_axi_gmem1_RUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "RUSER" }} , 
 	{ "name": "m_axi_gmem1_RRESP", "direction": "in", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem1", "role": "RRESP" }} , 
 	{ "name": "m_axi_gmem1_BVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "BVALID" }} , 
 	{ "name": "m_axi_gmem1_BREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "BREADY" }} , 
 	{ "name": "m_axi_gmem1_BRESP", "direction": "in", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem1", "role": "BRESP" }} , 
 	{ "name": "m_axi_gmem1_BID", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "BID" }} , 
 	{ "name": "m_axi_gmem1_BUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "BUSER" }} , 
 	{ "name": "m_axi_gmem0_AWVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "AWVALID" }} , 
 	{ "name": "m_axi_gmem0_AWREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "AWREADY" }} , 
 	{ "name": "m_axi_gmem0_AWADDR", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "gmem0", "role": "AWADDR" }} , 
 	{ "name": "m_axi_gmem0_AWID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "AWID" }} , 
 	{ "name": "m_axi_gmem0_AWLEN", "direction": "out", "datatype": "sc_lv", "bitwidth":8, "type": "signal", "bundle":{"name": "gmem0", "role": "AWLEN" }} , 
 	{ "name": "m_axi_gmem0_AWSIZE", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "gmem0", "role": "AWSIZE" }} , 
 	{ "name": "m_axi_gmem0_AWBURST", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem0", "role": "AWBURST" }} , 
 	{ "name": "m_axi_gmem0_AWLOCK", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem0", "role": "AWLOCK" }} , 
 	{ "name": "m_axi_gmem0_AWCACHE", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem0", "role": "AWCACHE" }} , 
 	{ "name": "m_axi_gmem0_AWPROT", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "gmem0", "role": "AWPROT" }} , 
 	{ "name": "m_axi_gmem0_AWQOS", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem0", "role": "AWQOS" }} , 
 	{ "name": "m_axi_gmem0_AWREGION", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem0", "role": "AWREGION" }} , 
 	{ "name": "m_axi_gmem0_AWUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "AWUSER" }} , 
 	{ "name": "m_axi_gmem0_WVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "WVALID" }} , 
 	{ "name": "m_axi_gmem0_WREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "WREADY" }} , 
 	{ "name": "m_axi_gmem0_WDATA", "direction": "out", "datatype": "sc_lv", "bitwidth":256, "type": "signal", "bundle":{"name": "gmem0", "role": "WDATA" }} , 
 	{ "name": "m_axi_gmem0_WSTRB", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "gmem0", "role": "WSTRB" }} , 
 	{ "name": "m_axi_gmem0_WLAST", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "WLAST" }} , 
 	{ "name": "m_axi_gmem0_WID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "WID" }} , 
 	{ "name": "m_axi_gmem0_WUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "WUSER" }} , 
 	{ "name": "m_axi_gmem0_ARVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "ARVALID" }} , 
 	{ "name": "m_axi_gmem0_ARREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "ARREADY" }} , 
 	{ "name": "m_axi_gmem0_ARADDR", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "gmem0", "role": "ARADDR" }} , 
 	{ "name": "m_axi_gmem0_ARID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "ARID" }} , 
 	{ "name": "m_axi_gmem0_ARLEN", "direction": "out", "datatype": "sc_lv", "bitwidth":8, "type": "signal", "bundle":{"name": "gmem0", "role": "ARLEN" }} , 
 	{ "name": "m_axi_gmem0_ARSIZE", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "gmem0", "role": "ARSIZE" }} , 
 	{ "name": "m_axi_gmem0_ARBURST", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem0", "role": "ARBURST" }} , 
 	{ "name": "m_axi_gmem0_ARLOCK", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem0", "role": "ARLOCK" }} , 
 	{ "name": "m_axi_gmem0_ARCACHE", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem0", "role": "ARCACHE" }} , 
 	{ "name": "m_axi_gmem0_ARPROT", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "gmem0", "role": "ARPROT" }} , 
 	{ "name": "m_axi_gmem0_ARQOS", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem0", "role": "ARQOS" }} , 
 	{ "name": "m_axi_gmem0_ARREGION", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem0", "role": "ARREGION" }} , 
 	{ "name": "m_axi_gmem0_ARUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "ARUSER" }} , 
 	{ "name": "m_axi_gmem0_RVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "RVALID" }} , 
 	{ "name": "m_axi_gmem0_RREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "RREADY" }} , 
 	{ "name": "m_axi_gmem0_RDATA", "direction": "in", "datatype": "sc_lv", "bitwidth":256, "type": "signal", "bundle":{"name": "gmem0", "role": "RDATA" }} , 
 	{ "name": "m_axi_gmem0_RLAST", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "RLAST" }} , 
 	{ "name": "m_axi_gmem0_RID", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "RID" }} , 
 	{ "name": "m_axi_gmem0_RUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "RUSER" }} , 
 	{ "name": "m_axi_gmem0_RRESP", "direction": "in", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem0", "role": "RRESP" }} , 
 	{ "name": "m_axi_gmem0_BVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "BVALID" }} , 
 	{ "name": "m_axi_gmem0_BREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "BREADY" }} , 
 	{ "name": "m_axi_gmem0_BRESP", "direction": "in", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem0", "role": "BRESP" }} , 
 	{ "name": "m_axi_gmem0_BID", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "BID" }} , 
 	{ "name": "m_axi_gmem0_BUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "BUSER" }} , 
 	{ "name": "m_axi_gmem2_AWVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem2", "role": "AWVALID" }} , 
 	{ "name": "m_axi_gmem2_AWREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem2", "role": "AWREADY" }} , 
 	{ "name": "m_axi_gmem2_AWADDR", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "gmem2", "role": "AWADDR" }} , 
 	{ "name": "m_axi_gmem2_AWID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem2", "role": "AWID" }} , 
 	{ "name": "m_axi_gmem2_AWLEN", "direction": "out", "datatype": "sc_lv", "bitwidth":8, "type": "signal", "bundle":{"name": "gmem2", "role": "AWLEN" }} , 
 	{ "name": "m_axi_gmem2_AWSIZE", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "gmem2", "role": "AWSIZE" }} , 
 	{ "name": "m_axi_gmem2_AWBURST", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem2", "role": "AWBURST" }} , 
 	{ "name": "m_axi_gmem2_AWLOCK", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem2", "role": "AWLOCK" }} , 
 	{ "name": "m_axi_gmem2_AWCACHE", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem2", "role": "AWCACHE" }} , 
 	{ "name": "m_axi_gmem2_AWPROT", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "gmem2", "role": "AWPROT" }} , 
 	{ "name": "m_axi_gmem2_AWQOS", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem2", "role": "AWQOS" }} , 
 	{ "name": "m_axi_gmem2_AWREGION", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem2", "role": "AWREGION" }} , 
 	{ "name": "m_axi_gmem2_AWUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem2", "role": "AWUSER" }} , 
 	{ "name": "m_axi_gmem2_WVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem2", "role": "WVALID" }} , 
 	{ "name": "m_axi_gmem2_WREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem2", "role": "WREADY" }} , 
 	{ "name": "m_axi_gmem2_WDATA", "direction": "out", "datatype": "sc_lv", "bitwidth":256, "type": "signal", "bundle":{"name": "gmem2", "role": "WDATA" }} , 
 	{ "name": "m_axi_gmem2_WSTRB", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "gmem2", "role": "WSTRB" }} , 
 	{ "name": "m_axi_gmem2_WLAST", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem2", "role": "WLAST" }} , 
 	{ "name": "m_axi_gmem2_WID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem2", "role": "WID" }} , 
 	{ "name": "m_axi_gmem2_WUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem2", "role": "WUSER" }} , 
 	{ "name": "m_axi_gmem2_ARVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem2", "role": "ARVALID" }} , 
 	{ "name": "m_axi_gmem2_ARREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem2", "role": "ARREADY" }} , 
 	{ "name": "m_axi_gmem2_ARADDR", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "gmem2", "role": "ARADDR" }} , 
 	{ "name": "m_axi_gmem2_ARID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem2", "role": "ARID" }} , 
 	{ "name": "m_axi_gmem2_ARLEN", "direction": "out", "datatype": "sc_lv", "bitwidth":8, "type": "signal", "bundle":{"name": "gmem2", "role": "ARLEN" }} , 
 	{ "name": "m_axi_gmem2_ARSIZE", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "gmem2", "role": "ARSIZE" }} , 
 	{ "name": "m_axi_gmem2_ARBURST", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem2", "role": "ARBURST" }} , 
 	{ "name": "m_axi_gmem2_ARLOCK", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem2", "role": "ARLOCK" }} , 
 	{ "name": "m_axi_gmem2_ARCACHE", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem2", "role": "ARCACHE" }} , 
 	{ "name": "m_axi_gmem2_ARPROT", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "gmem2", "role": "ARPROT" }} , 
 	{ "name": "m_axi_gmem2_ARQOS", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem2", "role": "ARQOS" }} , 
 	{ "name": "m_axi_gmem2_ARREGION", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem2", "role": "ARREGION" }} , 
 	{ "name": "m_axi_gmem2_ARUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem2", "role": "ARUSER" }} , 
 	{ "name": "m_axi_gmem2_RVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem2", "role": "RVALID" }} , 
 	{ "name": "m_axi_gmem2_RREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem2", "role": "RREADY" }} , 
 	{ "name": "m_axi_gmem2_RDATA", "direction": "in", "datatype": "sc_lv", "bitwidth":256, "type": "signal", "bundle":{"name": "gmem2", "role": "RDATA" }} , 
 	{ "name": "m_axi_gmem2_RLAST", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem2", "role": "RLAST" }} , 
 	{ "name": "m_axi_gmem2_RID", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem2", "role": "RID" }} , 
 	{ "name": "m_axi_gmem2_RUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem2", "role": "RUSER" }} , 
 	{ "name": "m_axi_gmem2_RRESP", "direction": "in", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem2", "role": "RRESP" }} , 
 	{ "name": "m_axi_gmem2_BVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem2", "role": "BVALID" }} , 
 	{ "name": "m_axi_gmem2_BREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem2", "role": "BREADY" }} , 
 	{ "name": "m_axi_gmem2_BRESP", "direction": "in", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem2", "role": "BRESP" }} , 
 	{ "name": "m_axi_gmem2_BID", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem2", "role": "BID" }} , 
 	{ "name": "m_axi_gmem2_BUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem2", "role": "BUSER" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1", "2", "3", "4", "5", "36", "67", "98", "129", "160", "191", "222"],
		"CDFG" : "accel_in_circle",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "-1", "EstimateLatencyMax" : "-1",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "gmem1", "Type" : "MAXI", "Direction" : "I",
				"BlockSignal" : [
					{"Name" : "gmem1_blk_n_AR", "Type" : "RtlSignal"},
					{"Name" : "gmem1_blk_n_R", "Type" : "RtlSignal"}]},
			{"Name" : "gmem0", "Type" : "MAXI", "Direction" : "IO",
				"BlockSignal" : [
					{"Name" : "gmem0_blk_n_AR", "Type" : "RtlSignal"},
					{"Name" : "gmem0_blk_n_AW", "Type" : "RtlSignal"},
					{"Name" : "gmem0_blk_n_R", "Type" : "RtlSignal"},
					{"Name" : "gmem0_blk_n_W", "Type" : "RtlSignal"},
					{"Name" : "gmem0_blk_n_B", "Type" : "RtlSignal"}]},
			{"Name" : "gmem2", "Type" : "MAXI", "Direction" : "I",
				"BlockSignal" : [
					{"Name" : "gmem2_blk_n_AR", "Type" : "RtlSignal"},
					{"Name" : "gmem2_blk_n_R", "Type" : "RtlSignal"}]},
			{"Name" : "indata_V", "Type" : "None", "Direction" : "I"},
			{"Name" : "instate_V", "Type" : "None", "Direction" : "I"},
			{"Name" : "infather_V", "Type" : "None", "Direction" : "I"},
			{"Name" : "inmaxquery", "Type" : "None", "Direction" : "I"}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.accel_in_circle_control_s_axi_U", "Parent" : "0"},
	{"ID" : "2", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.accel_in_circle_gmem1_m_axi_U", "Parent" : "0"},
	{"ID" : "3", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.accel_in_circle_gmem0_m_axi_U", "Parent" : "0"},
	{"ID" : "4", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.accel_in_circle_gmem2_m_axi_U", "Parent" : "0"},
	{"ID" : "5", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_386", "Parent" : "0", "Child" : ["6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35"],
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
	{"ID" : "6", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_386.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U1", "Parent" : "5"},
	{"ID" : "7", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_386.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U2", "Parent" : "5"},
	{"ID" : "8", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_386.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U3", "Parent" : "5"},
	{"ID" : "9", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_386.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U4", "Parent" : "5"},
	{"ID" : "10", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_386.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U5", "Parent" : "5"},
	{"ID" : "11", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_386.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U6", "Parent" : "5"},
	{"ID" : "12", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_386.accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0_U7", "Parent" : "5"},
	{"ID" : "13", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_386.accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0_U8", "Parent" : "5"},
	{"ID" : "14", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_386.accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0_U9", "Parent" : "5"},
	{"ID" : "15", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_386.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U10", "Parent" : "5"},
	{"ID" : "16", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_386.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U11", "Parent" : "5"},
	{"ID" : "17", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_386.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U12", "Parent" : "5"},
	{"ID" : "18", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_386.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U13", "Parent" : "5"},
	{"ID" : "19", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_386.accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0_U14", "Parent" : "5"},
	{"ID" : "20", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_386.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U15", "Parent" : "5"},
	{"ID" : "21", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_386.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U16", "Parent" : "5"},
	{"ID" : "22", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_386.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U17", "Parent" : "5"},
	{"ID" : "23", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_386.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U18", "Parent" : "5"},
	{"ID" : "24", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_386.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U19", "Parent" : "5"},
	{"ID" : "25", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_386.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U20", "Parent" : "5"},
	{"ID" : "26", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_386.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U21", "Parent" : "5"},
	{"ID" : "27", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_386.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U22", "Parent" : "5"},
	{"ID" : "28", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_386.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U23", "Parent" : "5"},
	{"ID" : "29", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_386.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U24", "Parent" : "5"},
	{"ID" : "30", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_386.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U25", "Parent" : "5"},
	{"ID" : "31", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_386.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U26", "Parent" : "5"},
	{"ID" : "32", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_386.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U27", "Parent" : "5"},
	{"ID" : "33", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_386.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U28", "Parent" : "5"},
	{"ID" : "34", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_386.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U29", "Parent" : "5"},
	{"ID" : "35", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_386.accel_in_circle_fcmp_32ns_32ns_1_1_0_U30", "Parent" : "5"},
	{"ID" : "36", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_398", "Parent" : "0", "Child" : ["37", "38", "39", "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "60", "61", "62", "63", "64", "65", "66"],
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
	{"ID" : "37", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_398.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U1", "Parent" : "36"},
	{"ID" : "38", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_398.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U2", "Parent" : "36"},
	{"ID" : "39", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_398.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U3", "Parent" : "36"},
	{"ID" : "40", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_398.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U4", "Parent" : "36"},
	{"ID" : "41", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_398.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U5", "Parent" : "36"},
	{"ID" : "42", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_398.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U6", "Parent" : "36"},
	{"ID" : "43", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_398.accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0_U7", "Parent" : "36"},
	{"ID" : "44", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_398.accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0_U8", "Parent" : "36"},
	{"ID" : "45", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_398.accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0_U9", "Parent" : "36"},
	{"ID" : "46", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_398.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U10", "Parent" : "36"},
	{"ID" : "47", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_398.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U11", "Parent" : "36"},
	{"ID" : "48", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_398.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U12", "Parent" : "36"},
	{"ID" : "49", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_398.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U13", "Parent" : "36"},
	{"ID" : "50", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_398.accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0_U14", "Parent" : "36"},
	{"ID" : "51", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_398.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U15", "Parent" : "36"},
	{"ID" : "52", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_398.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U16", "Parent" : "36"},
	{"ID" : "53", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_398.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U17", "Parent" : "36"},
	{"ID" : "54", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_398.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U18", "Parent" : "36"},
	{"ID" : "55", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_398.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U19", "Parent" : "36"},
	{"ID" : "56", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_398.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U20", "Parent" : "36"},
	{"ID" : "57", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_398.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U21", "Parent" : "36"},
	{"ID" : "58", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_398.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U22", "Parent" : "36"},
	{"ID" : "59", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_398.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U23", "Parent" : "36"},
	{"ID" : "60", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_398.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U24", "Parent" : "36"},
	{"ID" : "61", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_398.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U25", "Parent" : "36"},
	{"ID" : "62", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_398.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U26", "Parent" : "36"},
	{"ID" : "63", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_398.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U27", "Parent" : "36"},
	{"ID" : "64", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_398.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U28", "Parent" : "36"},
	{"ID" : "65", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_398.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U29", "Parent" : "36"},
	{"ID" : "66", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_398.accel_in_circle_fcmp_32ns_32ns_1_1_0_U30", "Parent" : "36"},
	{"ID" : "67", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_410", "Parent" : "0", "Child" : ["68", "69", "70", "71", "72", "73", "74", "75", "76", "77", "78", "79", "80", "81", "82", "83", "84", "85", "86", "87", "88", "89", "90", "91", "92", "93", "94", "95", "96", "97"],
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
	{"ID" : "68", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_410.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U1", "Parent" : "67"},
	{"ID" : "69", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_410.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U2", "Parent" : "67"},
	{"ID" : "70", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_410.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U3", "Parent" : "67"},
	{"ID" : "71", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_410.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U4", "Parent" : "67"},
	{"ID" : "72", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_410.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U5", "Parent" : "67"},
	{"ID" : "73", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_410.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U6", "Parent" : "67"},
	{"ID" : "74", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_410.accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0_U7", "Parent" : "67"},
	{"ID" : "75", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_410.accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0_U8", "Parent" : "67"},
	{"ID" : "76", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_410.accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0_U9", "Parent" : "67"},
	{"ID" : "77", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_410.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U10", "Parent" : "67"},
	{"ID" : "78", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_410.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U11", "Parent" : "67"},
	{"ID" : "79", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_410.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U12", "Parent" : "67"},
	{"ID" : "80", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_410.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U13", "Parent" : "67"},
	{"ID" : "81", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_410.accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0_U14", "Parent" : "67"},
	{"ID" : "82", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_410.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U15", "Parent" : "67"},
	{"ID" : "83", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_410.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U16", "Parent" : "67"},
	{"ID" : "84", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_410.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U17", "Parent" : "67"},
	{"ID" : "85", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_410.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U18", "Parent" : "67"},
	{"ID" : "86", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_410.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U19", "Parent" : "67"},
	{"ID" : "87", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_410.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U20", "Parent" : "67"},
	{"ID" : "88", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_410.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U21", "Parent" : "67"},
	{"ID" : "89", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_410.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U22", "Parent" : "67"},
	{"ID" : "90", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_410.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U23", "Parent" : "67"},
	{"ID" : "91", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_410.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U24", "Parent" : "67"},
	{"ID" : "92", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_410.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U25", "Parent" : "67"},
	{"ID" : "93", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_410.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U26", "Parent" : "67"},
	{"ID" : "94", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_410.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U27", "Parent" : "67"},
	{"ID" : "95", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_410.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U28", "Parent" : "67"},
	{"ID" : "96", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_410.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U29", "Parent" : "67"},
	{"ID" : "97", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_410.accel_in_circle_fcmp_32ns_32ns_1_1_0_U30", "Parent" : "67"},
	{"ID" : "98", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_422", "Parent" : "0", "Child" : ["99", "100", "101", "102", "103", "104", "105", "106", "107", "108", "109", "110", "111", "112", "113", "114", "115", "116", "117", "118", "119", "120", "121", "122", "123", "124", "125", "126", "127", "128"],
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
	{"ID" : "99", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_422.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U1", "Parent" : "98"},
	{"ID" : "100", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_422.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U2", "Parent" : "98"},
	{"ID" : "101", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_422.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U3", "Parent" : "98"},
	{"ID" : "102", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_422.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U4", "Parent" : "98"},
	{"ID" : "103", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_422.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U5", "Parent" : "98"},
	{"ID" : "104", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_422.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U6", "Parent" : "98"},
	{"ID" : "105", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_422.accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0_U7", "Parent" : "98"},
	{"ID" : "106", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_422.accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0_U8", "Parent" : "98"},
	{"ID" : "107", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_422.accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0_U9", "Parent" : "98"},
	{"ID" : "108", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_422.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U10", "Parent" : "98"},
	{"ID" : "109", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_422.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U11", "Parent" : "98"},
	{"ID" : "110", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_422.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U12", "Parent" : "98"},
	{"ID" : "111", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_422.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U13", "Parent" : "98"},
	{"ID" : "112", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_422.accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0_U14", "Parent" : "98"},
	{"ID" : "113", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_422.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U15", "Parent" : "98"},
	{"ID" : "114", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_422.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U16", "Parent" : "98"},
	{"ID" : "115", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_422.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U17", "Parent" : "98"},
	{"ID" : "116", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_422.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U18", "Parent" : "98"},
	{"ID" : "117", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_422.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U19", "Parent" : "98"},
	{"ID" : "118", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_422.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U20", "Parent" : "98"},
	{"ID" : "119", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_422.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U21", "Parent" : "98"},
	{"ID" : "120", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_422.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U22", "Parent" : "98"},
	{"ID" : "121", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_422.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U23", "Parent" : "98"},
	{"ID" : "122", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_422.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U24", "Parent" : "98"},
	{"ID" : "123", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_422.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U25", "Parent" : "98"},
	{"ID" : "124", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_422.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U26", "Parent" : "98"},
	{"ID" : "125", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_422.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U27", "Parent" : "98"},
	{"ID" : "126", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_422.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U28", "Parent" : "98"},
	{"ID" : "127", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_422.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U29", "Parent" : "98"},
	{"ID" : "128", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_422.accel_in_circle_fcmp_32ns_32ns_1_1_0_U30", "Parent" : "98"},
	{"ID" : "129", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_434", "Parent" : "0", "Child" : ["130", "131", "132", "133", "134", "135", "136", "137", "138", "139", "140", "141", "142", "143", "144", "145", "146", "147", "148", "149", "150", "151", "152", "153", "154", "155", "156", "157", "158", "159"],
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
	{"ID" : "130", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_434.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U1", "Parent" : "129"},
	{"ID" : "131", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_434.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U2", "Parent" : "129"},
	{"ID" : "132", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_434.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U3", "Parent" : "129"},
	{"ID" : "133", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_434.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U4", "Parent" : "129"},
	{"ID" : "134", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_434.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U5", "Parent" : "129"},
	{"ID" : "135", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_434.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U6", "Parent" : "129"},
	{"ID" : "136", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_434.accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0_U7", "Parent" : "129"},
	{"ID" : "137", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_434.accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0_U8", "Parent" : "129"},
	{"ID" : "138", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_434.accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0_U9", "Parent" : "129"},
	{"ID" : "139", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_434.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U10", "Parent" : "129"},
	{"ID" : "140", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_434.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U11", "Parent" : "129"},
	{"ID" : "141", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_434.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U12", "Parent" : "129"},
	{"ID" : "142", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_434.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U13", "Parent" : "129"},
	{"ID" : "143", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_434.accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0_U14", "Parent" : "129"},
	{"ID" : "144", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_434.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U15", "Parent" : "129"},
	{"ID" : "145", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_434.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U16", "Parent" : "129"},
	{"ID" : "146", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_434.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U17", "Parent" : "129"},
	{"ID" : "147", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_434.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U18", "Parent" : "129"},
	{"ID" : "148", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_434.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U19", "Parent" : "129"},
	{"ID" : "149", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_434.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U20", "Parent" : "129"},
	{"ID" : "150", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_434.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U21", "Parent" : "129"},
	{"ID" : "151", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_434.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U22", "Parent" : "129"},
	{"ID" : "152", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_434.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U23", "Parent" : "129"},
	{"ID" : "153", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_434.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U24", "Parent" : "129"},
	{"ID" : "154", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_434.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U25", "Parent" : "129"},
	{"ID" : "155", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_434.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U26", "Parent" : "129"},
	{"ID" : "156", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_434.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U27", "Parent" : "129"},
	{"ID" : "157", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_434.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U28", "Parent" : "129"},
	{"ID" : "158", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_434.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U29", "Parent" : "129"},
	{"ID" : "159", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_434.accel_in_circle_fcmp_32ns_32ns_1_1_0_U30", "Parent" : "129"},
	{"ID" : "160", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_446", "Parent" : "0", "Child" : ["161", "162", "163", "164", "165", "166", "167", "168", "169", "170", "171", "172", "173", "174", "175", "176", "177", "178", "179", "180", "181", "182", "183", "184", "185", "186", "187", "188", "189", "190"],
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
	{"ID" : "161", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_446.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U1", "Parent" : "160"},
	{"ID" : "162", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_446.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U2", "Parent" : "160"},
	{"ID" : "163", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_446.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U3", "Parent" : "160"},
	{"ID" : "164", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_446.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U4", "Parent" : "160"},
	{"ID" : "165", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_446.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U5", "Parent" : "160"},
	{"ID" : "166", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_446.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U6", "Parent" : "160"},
	{"ID" : "167", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_446.accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0_U7", "Parent" : "160"},
	{"ID" : "168", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_446.accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0_U8", "Parent" : "160"},
	{"ID" : "169", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_446.accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0_U9", "Parent" : "160"},
	{"ID" : "170", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_446.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U10", "Parent" : "160"},
	{"ID" : "171", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_446.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U11", "Parent" : "160"},
	{"ID" : "172", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_446.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U12", "Parent" : "160"},
	{"ID" : "173", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_446.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U13", "Parent" : "160"},
	{"ID" : "174", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_446.accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0_U14", "Parent" : "160"},
	{"ID" : "175", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_446.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U15", "Parent" : "160"},
	{"ID" : "176", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_446.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U16", "Parent" : "160"},
	{"ID" : "177", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_446.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U17", "Parent" : "160"},
	{"ID" : "178", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_446.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U18", "Parent" : "160"},
	{"ID" : "179", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_446.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U19", "Parent" : "160"},
	{"ID" : "180", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_446.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U20", "Parent" : "160"},
	{"ID" : "181", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_446.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U21", "Parent" : "160"},
	{"ID" : "182", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_446.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U22", "Parent" : "160"},
	{"ID" : "183", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_446.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U23", "Parent" : "160"},
	{"ID" : "184", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_446.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U24", "Parent" : "160"},
	{"ID" : "185", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_446.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U25", "Parent" : "160"},
	{"ID" : "186", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_446.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U26", "Parent" : "160"},
	{"ID" : "187", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_446.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U27", "Parent" : "160"},
	{"ID" : "188", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_446.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U28", "Parent" : "160"},
	{"ID" : "189", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_446.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U29", "Parent" : "160"},
	{"ID" : "190", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_446.accel_in_circle_fcmp_32ns_32ns_1_1_0_U30", "Parent" : "160"},
	{"ID" : "191", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_458", "Parent" : "0", "Child" : ["192", "193", "194", "195", "196", "197", "198", "199", "200", "201", "202", "203", "204", "205", "206", "207", "208", "209", "210", "211", "212", "213", "214", "215", "216", "217", "218", "219", "220", "221"],
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
	{"ID" : "192", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_458.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U1", "Parent" : "191"},
	{"ID" : "193", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_458.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U2", "Parent" : "191"},
	{"ID" : "194", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_458.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U3", "Parent" : "191"},
	{"ID" : "195", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_458.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U4", "Parent" : "191"},
	{"ID" : "196", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_458.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U5", "Parent" : "191"},
	{"ID" : "197", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_458.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U6", "Parent" : "191"},
	{"ID" : "198", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_458.accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0_U7", "Parent" : "191"},
	{"ID" : "199", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_458.accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0_U8", "Parent" : "191"},
	{"ID" : "200", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_458.accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0_U9", "Parent" : "191"},
	{"ID" : "201", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_458.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U10", "Parent" : "191"},
	{"ID" : "202", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_458.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U11", "Parent" : "191"},
	{"ID" : "203", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_458.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U12", "Parent" : "191"},
	{"ID" : "204", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_458.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U13", "Parent" : "191"},
	{"ID" : "205", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_458.accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0_U14", "Parent" : "191"},
	{"ID" : "206", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_458.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U15", "Parent" : "191"},
	{"ID" : "207", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_458.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U16", "Parent" : "191"},
	{"ID" : "208", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_458.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U17", "Parent" : "191"},
	{"ID" : "209", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_458.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U18", "Parent" : "191"},
	{"ID" : "210", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_458.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U19", "Parent" : "191"},
	{"ID" : "211", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_458.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U20", "Parent" : "191"},
	{"ID" : "212", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_458.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U21", "Parent" : "191"},
	{"ID" : "213", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_458.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U22", "Parent" : "191"},
	{"ID" : "214", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_458.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U23", "Parent" : "191"},
	{"ID" : "215", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_458.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U24", "Parent" : "191"},
	{"ID" : "216", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_458.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U25", "Parent" : "191"},
	{"ID" : "217", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_458.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U26", "Parent" : "191"},
	{"ID" : "218", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_458.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U27", "Parent" : "191"},
	{"ID" : "219", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_458.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U28", "Parent" : "191"},
	{"ID" : "220", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_458.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U29", "Parent" : "191"},
	{"ID" : "221", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_458.accel_in_circle_fcmp_32ns_32ns_1_1_0_U30", "Parent" : "191"},
	{"ID" : "222", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_470", "Parent" : "0", "Child" : ["223", "224", "225", "226", "227", "228", "229", "230", "231", "232", "233", "234", "235", "236", "237", "238", "239", "240", "241", "242", "243", "244", "245", "246", "247", "248", "249", "250", "251", "252"],
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
	{"ID" : "223", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_470.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U1", "Parent" : "222"},
	{"ID" : "224", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_470.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U2", "Parent" : "222"},
	{"ID" : "225", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_470.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U3", "Parent" : "222"},
	{"ID" : "226", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_470.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U4", "Parent" : "222"},
	{"ID" : "227", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_470.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U5", "Parent" : "222"},
	{"ID" : "228", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_470.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U6", "Parent" : "222"},
	{"ID" : "229", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_470.accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0_U7", "Parent" : "222"},
	{"ID" : "230", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_470.accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0_U8", "Parent" : "222"},
	{"ID" : "231", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_470.accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0_U9", "Parent" : "222"},
	{"ID" : "232", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_470.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U10", "Parent" : "222"},
	{"ID" : "233", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_470.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U11", "Parent" : "222"},
	{"ID" : "234", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_470.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U12", "Parent" : "222"},
	{"ID" : "235", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_470.accel_in_circle_fsub_32ns_32ns_32_3_full_dsp_0_U13", "Parent" : "222"},
	{"ID" : "236", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_470.accel_in_circle_fadd_32ns_32ns_32_3_full_dsp_0_U14", "Parent" : "222"},
	{"ID" : "237", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_470.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U15", "Parent" : "222"},
	{"ID" : "238", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_470.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U16", "Parent" : "222"},
	{"ID" : "239", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_470.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U17", "Parent" : "222"},
	{"ID" : "240", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_470.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U18", "Parent" : "222"},
	{"ID" : "241", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_470.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U19", "Parent" : "222"},
	{"ID" : "242", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_470.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U20", "Parent" : "222"},
	{"ID" : "243", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_470.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U21", "Parent" : "222"},
	{"ID" : "244", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_470.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U22", "Parent" : "222"},
	{"ID" : "245", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_470.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U23", "Parent" : "222"},
	{"ID" : "246", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_470.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U24", "Parent" : "222"},
	{"ID" : "247", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_470.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U25", "Parent" : "222"},
	{"ID" : "248", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_470.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U26", "Parent" : "222"},
	{"ID" : "249", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_470.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U27", "Parent" : "222"},
	{"ID" : "250", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_470.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U28", "Parent" : "222"},
	{"ID" : "251", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_470.accel_in_circle_fmul_32ns_32ns_32_2_max_dsp_0_U29", "Parent" : "222"},
	{"ID" : "252", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_in_circle_fu_470.accel_in_circle_fcmp_32ns_32ns_1_1_0_U30", "Parent" : "222"}]}


set ArgLastReadFirstWriteLatency {
	accel_in_circle {
		gmem1 {Type I LastRead 19 FirstWrite -1}
		gmem0 {Type IO LastRead 20 FirstWrite 39}
		gmem2 {Type I LastRead 8 FirstWrite -1}
		indata_V {Type I LastRead 0 FirstWrite -1}
		instate_V {Type I LastRead 0 FirstWrite -1}
		infather_V {Type I LastRead 0 FirstWrite -1}
		inmaxquery {Type I LastRead 0 FirstWrite -1}}
	in_circle {
		innerdata_0_read {Type I LastRead 0 FirstWrite -1}
		innerdata_1_read {Type I LastRead 0 FirstWrite -1}
		father_0_read {Type I LastRead 0 FirstWrite -1}
		father_1_read {Type I LastRead 0 FirstWrite -1}
		father_2_read {Type I LastRead 0 FirstWrite -1}
		father_3_read {Type I LastRead 0 FirstWrite -1}
		father_4_read {Type I LastRead 0 FirstWrite -1}
		father_5_read {Type I LastRead 0 FirstWrite -1}}
	in_circle {
		innerdata_0_read {Type I LastRead 0 FirstWrite -1}
		innerdata_1_read {Type I LastRead 0 FirstWrite -1}
		father_0_read {Type I LastRead 0 FirstWrite -1}
		father_1_read {Type I LastRead 0 FirstWrite -1}
		father_2_read {Type I LastRead 0 FirstWrite -1}
		father_3_read {Type I LastRead 0 FirstWrite -1}
		father_4_read {Type I LastRead 0 FirstWrite -1}
		father_5_read {Type I LastRead 0 FirstWrite -1}}
	in_circle {
		innerdata_0_read {Type I LastRead 0 FirstWrite -1}
		innerdata_1_read {Type I LastRead 0 FirstWrite -1}
		father_0_read {Type I LastRead 0 FirstWrite -1}
		father_1_read {Type I LastRead 0 FirstWrite -1}
		father_2_read {Type I LastRead 0 FirstWrite -1}
		father_3_read {Type I LastRead 0 FirstWrite -1}
		father_4_read {Type I LastRead 0 FirstWrite -1}
		father_5_read {Type I LastRead 0 FirstWrite -1}}
	in_circle {
		innerdata_0_read {Type I LastRead 0 FirstWrite -1}
		innerdata_1_read {Type I LastRead 0 FirstWrite -1}
		father_0_read {Type I LastRead 0 FirstWrite -1}
		father_1_read {Type I LastRead 0 FirstWrite -1}
		father_2_read {Type I LastRead 0 FirstWrite -1}
		father_3_read {Type I LastRead 0 FirstWrite -1}
		father_4_read {Type I LastRead 0 FirstWrite -1}
		father_5_read {Type I LastRead 0 FirstWrite -1}}
	in_circle {
		innerdata_0_read {Type I LastRead 0 FirstWrite -1}
		innerdata_1_read {Type I LastRead 0 FirstWrite -1}
		father_0_read {Type I LastRead 0 FirstWrite -1}
		father_1_read {Type I LastRead 0 FirstWrite -1}
		father_2_read {Type I LastRead 0 FirstWrite -1}
		father_3_read {Type I LastRead 0 FirstWrite -1}
		father_4_read {Type I LastRead 0 FirstWrite -1}
		father_5_read {Type I LastRead 0 FirstWrite -1}}
	in_circle {
		innerdata_0_read {Type I LastRead 0 FirstWrite -1}
		innerdata_1_read {Type I LastRead 0 FirstWrite -1}
		father_0_read {Type I LastRead 0 FirstWrite -1}
		father_1_read {Type I LastRead 0 FirstWrite -1}
		father_2_read {Type I LastRead 0 FirstWrite -1}
		father_3_read {Type I LastRead 0 FirstWrite -1}
		father_4_read {Type I LastRead 0 FirstWrite -1}
		father_5_read {Type I LastRead 0 FirstWrite -1}}
	in_circle {
		innerdata_0_read {Type I LastRead 0 FirstWrite -1}
		innerdata_1_read {Type I LastRead 0 FirstWrite -1}
		father_0_read {Type I LastRead 0 FirstWrite -1}
		father_1_read {Type I LastRead 0 FirstWrite -1}
		father_2_read {Type I LastRead 0 FirstWrite -1}
		father_3_read {Type I LastRead 0 FirstWrite -1}
		father_4_read {Type I LastRead 0 FirstWrite -1}
		father_5_read {Type I LastRead 0 FirstWrite -1}}
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
	{"Name" : "Latency", "Min" : "-1", "Max" : "-1"}
	, {"Name" : "Interval", "Min" : "0", "Max" : "0"}
]}

set PipelineEnableSignalInfo {[
	{"Pipeline" : "1", "EnableSignal" : "ap_enable_pp1"}
]}

set Spec2ImplPortList { 
	gmem1 { m_axi {  { m_axi_gmem1_AWVALID VALID 1 1 }  { m_axi_gmem1_AWREADY READY 0 1 }  { m_axi_gmem1_AWADDR ADDR 1 64 }  { m_axi_gmem1_AWID ID 1 1 }  { m_axi_gmem1_AWLEN LEN 1 8 }  { m_axi_gmem1_AWSIZE SIZE 1 3 }  { m_axi_gmem1_AWBURST BURST 1 2 }  { m_axi_gmem1_AWLOCK LOCK 1 2 }  { m_axi_gmem1_AWCACHE CACHE 1 4 }  { m_axi_gmem1_AWPROT PROT 1 3 }  { m_axi_gmem1_AWQOS QOS 1 4 }  { m_axi_gmem1_AWREGION REGION 1 4 }  { m_axi_gmem1_AWUSER USER 1 1 }  { m_axi_gmem1_WVALID VALID 1 1 }  { m_axi_gmem1_WREADY READY 0 1 }  { m_axi_gmem1_WDATA DATA 1 512 }  { m_axi_gmem1_WSTRB STRB 1 64 }  { m_axi_gmem1_WLAST LAST 1 1 }  { m_axi_gmem1_WID ID 1 1 }  { m_axi_gmem1_WUSER USER 1 1 }  { m_axi_gmem1_ARVALID VALID 1 1 }  { m_axi_gmem1_ARREADY READY 0 1 }  { m_axi_gmem1_ARADDR ADDR 1 64 }  { m_axi_gmem1_ARID ID 1 1 }  { m_axi_gmem1_ARLEN LEN 1 8 }  { m_axi_gmem1_ARSIZE SIZE 1 3 }  { m_axi_gmem1_ARBURST BURST 1 2 }  { m_axi_gmem1_ARLOCK LOCK 1 2 }  { m_axi_gmem1_ARCACHE CACHE 1 4 }  { m_axi_gmem1_ARPROT PROT 1 3 }  { m_axi_gmem1_ARQOS QOS 1 4 }  { m_axi_gmem1_ARREGION REGION 1 4 }  { m_axi_gmem1_ARUSER USER 1 1 }  { m_axi_gmem1_RVALID VALID 0 1 }  { m_axi_gmem1_RREADY READY 1 1 }  { m_axi_gmem1_RDATA DATA 0 512 }  { m_axi_gmem1_RLAST LAST 0 1 }  { m_axi_gmem1_RID ID 0 1 }  { m_axi_gmem1_RUSER USER 0 1 }  { m_axi_gmem1_RRESP RESP 0 2 }  { m_axi_gmem1_BVALID VALID 0 1 }  { m_axi_gmem1_BREADY READY 1 1 }  { m_axi_gmem1_BRESP RESP 0 2 }  { m_axi_gmem1_BID ID 0 1 }  { m_axi_gmem1_BUSER USER 0 1 } } }
	gmem0 { m_axi {  { m_axi_gmem0_AWVALID VALID 1 1 }  { m_axi_gmem0_AWREADY READY 0 1 }  { m_axi_gmem0_AWADDR ADDR 1 64 }  { m_axi_gmem0_AWID ID 1 1 }  { m_axi_gmem0_AWLEN LEN 1 8 }  { m_axi_gmem0_AWSIZE SIZE 1 3 }  { m_axi_gmem0_AWBURST BURST 1 2 }  { m_axi_gmem0_AWLOCK LOCK 1 2 }  { m_axi_gmem0_AWCACHE CACHE 1 4 }  { m_axi_gmem0_AWPROT PROT 1 3 }  { m_axi_gmem0_AWQOS QOS 1 4 }  { m_axi_gmem0_AWREGION REGION 1 4 }  { m_axi_gmem0_AWUSER USER 1 1 }  { m_axi_gmem0_WVALID VALID 1 1 }  { m_axi_gmem0_WREADY READY 0 1 }  { m_axi_gmem0_WDATA DATA 1 256 }  { m_axi_gmem0_WSTRB STRB 1 32 }  { m_axi_gmem0_WLAST LAST 1 1 }  { m_axi_gmem0_WID ID 1 1 }  { m_axi_gmem0_WUSER USER 1 1 }  { m_axi_gmem0_ARVALID VALID 1 1 }  { m_axi_gmem0_ARREADY READY 0 1 }  { m_axi_gmem0_ARADDR ADDR 1 64 }  { m_axi_gmem0_ARID ID 1 1 }  { m_axi_gmem0_ARLEN LEN 1 8 }  { m_axi_gmem0_ARSIZE SIZE 1 3 }  { m_axi_gmem0_ARBURST BURST 1 2 }  { m_axi_gmem0_ARLOCK LOCK 1 2 }  { m_axi_gmem0_ARCACHE CACHE 1 4 }  { m_axi_gmem0_ARPROT PROT 1 3 }  { m_axi_gmem0_ARQOS QOS 1 4 }  { m_axi_gmem0_ARREGION REGION 1 4 }  { m_axi_gmem0_ARUSER USER 1 1 }  { m_axi_gmem0_RVALID VALID 0 1 }  { m_axi_gmem0_RREADY READY 1 1 }  { m_axi_gmem0_RDATA DATA 0 256 }  { m_axi_gmem0_RLAST LAST 0 1 }  { m_axi_gmem0_RID ID 0 1 }  { m_axi_gmem0_RUSER USER 0 1 }  { m_axi_gmem0_RRESP RESP 0 2 }  { m_axi_gmem0_BVALID VALID 0 1 }  { m_axi_gmem0_BREADY READY 1 1 }  { m_axi_gmem0_BRESP RESP 0 2 }  { m_axi_gmem0_BID ID 0 1 }  { m_axi_gmem0_BUSER USER 0 1 } } }
	gmem2 { m_axi {  { m_axi_gmem2_AWVALID VALID 1 1 }  { m_axi_gmem2_AWREADY READY 0 1 }  { m_axi_gmem2_AWADDR ADDR 1 64 }  { m_axi_gmem2_AWID ID 1 1 }  { m_axi_gmem2_AWLEN LEN 1 8 }  { m_axi_gmem2_AWSIZE SIZE 1 3 }  { m_axi_gmem2_AWBURST BURST 1 2 }  { m_axi_gmem2_AWLOCK LOCK 1 2 }  { m_axi_gmem2_AWCACHE CACHE 1 4 }  { m_axi_gmem2_AWPROT PROT 1 3 }  { m_axi_gmem2_AWQOS QOS 1 4 }  { m_axi_gmem2_AWREGION REGION 1 4 }  { m_axi_gmem2_AWUSER USER 1 1 }  { m_axi_gmem2_WVALID VALID 1 1 }  { m_axi_gmem2_WREADY READY 0 1 }  { m_axi_gmem2_WDATA DATA 1 256 }  { m_axi_gmem2_WSTRB STRB 1 32 }  { m_axi_gmem2_WLAST LAST 1 1 }  { m_axi_gmem2_WID ID 1 1 }  { m_axi_gmem2_WUSER USER 1 1 }  { m_axi_gmem2_ARVALID VALID 1 1 }  { m_axi_gmem2_ARREADY READY 0 1 }  { m_axi_gmem2_ARADDR ADDR 1 64 }  { m_axi_gmem2_ARID ID 1 1 }  { m_axi_gmem2_ARLEN LEN 1 8 }  { m_axi_gmem2_ARSIZE SIZE 1 3 }  { m_axi_gmem2_ARBURST BURST 1 2 }  { m_axi_gmem2_ARLOCK LOCK 1 2 }  { m_axi_gmem2_ARCACHE CACHE 1 4 }  { m_axi_gmem2_ARPROT PROT 1 3 }  { m_axi_gmem2_ARQOS QOS 1 4 }  { m_axi_gmem2_ARREGION REGION 1 4 }  { m_axi_gmem2_ARUSER USER 1 1 }  { m_axi_gmem2_RVALID VALID 0 1 }  { m_axi_gmem2_RREADY READY 1 1 }  { m_axi_gmem2_RDATA DATA 0 256 }  { m_axi_gmem2_RLAST LAST 0 1 }  { m_axi_gmem2_RID ID 0 1 }  { m_axi_gmem2_RUSER USER 0 1 }  { m_axi_gmem2_RRESP RESP 0 2 }  { m_axi_gmem2_BVALID VALID 0 1 }  { m_axi_gmem2_BREADY READY 1 1 }  { m_axi_gmem2_BRESP RESP 0 2 }  { m_axi_gmem2_BID ID 0 1 }  { m_axi_gmem2_BUSER USER 0 1 } } }
}

set busDeadlockParameterList { 
	{ gmem1 { NUM_READ_OUTSTANDING 16 NUM_WRITE_OUTSTANDING 16 MAX_READ_BURST_LENGTH 16 MAX_WRITE_BURST_LENGTH 16 } } \
	{ gmem0 { NUM_READ_OUTSTANDING 16 NUM_WRITE_OUTSTANDING 16 MAX_READ_BURST_LENGTH 16 MAX_WRITE_BURST_LENGTH 16 } } \
	{ gmem2 { NUM_READ_OUTSTANDING 16 NUM_WRITE_OUTSTANDING 16 MAX_READ_BURST_LENGTH 16 MAX_WRITE_BURST_LENGTH 16 } } \
}

# RTL port scheduling information:
set fifoSchedulingInfoList { 
}

# RTL bus port read request latency information:
set busReadReqLatencyList { 
	{ gmem1 1 }
	{ gmem0 1 }
	{ gmem2 1 }
}

# RTL bus port write response latency information:
set busWriteResLatencyList { 
	{ gmem1 1 }
	{ gmem0 1 }
	{ gmem2 1 }
}

# RTL array port load latency information:
set memoryLoadLatencyList { 
}
