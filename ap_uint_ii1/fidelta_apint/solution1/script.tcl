############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
open_project fidelta_apint
set_top accel_in_circle
add_files incircle.cpp
add_files -tb bench.cpp
open_solution "solution1"
set_part {xcu200-fsgd2104-2-e}
create_clock -period 10 -name default
config_sdx -optimization_level none -target xocc
config_export -vivado_optimization_level 0 -vivado_phys_opt none
config_compile -name_max_length 80 -pipeline_loops 64
config_schedule -enable_dsp_full_reg
config_rtl -module_auto_prefix -register_reset_num 3
config_interface -m_axi_addr64
#source "./fidelta_apint/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
