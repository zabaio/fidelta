#include "hls_design_meta.h"
const Port_Property HLS_Design_Meta::port_props[]={
	Port_Property("ap_clk", 1, hls_in, -1, "", "", 1),
	Port_Property("ap_rst", 1, hls_in, -1, "", "", 1),
	Port_Property("ap_start", 1, hls_in, -1, "", "", 1),
	Port_Property("ap_done", 1, hls_out, -1, "", "", 1),
	Port_Property("ap_idle", 1, hls_out, -1, "", "", 1),
	Port_Property("ap_ready", 1, hls_out, -1, "", "", 1),
	Port_Property("t_p1_id", 32, hls_in, 0, "ap_none", "in_data", 1),
	Port_Property("t_p1_x", 32, hls_in, 1, "ap_none", "in_data", 1),
	Port_Property("t_p1_y", 32, hls_in, 2, "ap_none", "in_data", 1),
	Port_Property("t_p2_id", 32, hls_in, 3, "ap_none", "in_data", 1),
	Port_Property("t_p2_x", 32, hls_in, 4, "ap_none", "in_data", 1),
	Port_Property("t_p2_y", 32, hls_in, 5, "ap_none", "in_data", 1),
	Port_Property("t_p3_id", 32, hls_in, 6, "ap_none", "in_data", 1),
	Port_Property("t_p3_x", 32, hls_in, 7, "ap_none", "in_data", 1),
	Port_Property("t_p3_y", 32, hls_in, 8, "ap_none", "in_data", 1),
	Port_Property("d_id", 32, hls_in, 9, "ap_none", "in_data", 1),
	Port_Property("d_x", 32, hls_in, 10, "ap_none", "in_data", 1),
	Port_Property("d_y", 32, hls_in, 11, "ap_none", "in_data", 1),
	Port_Property("ap_return", 32, hls_out, -1, "", "", 1),
};
const char* HLS_Design_Meta::dut_name = "in_circle";
