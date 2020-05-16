############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
open_project merge_round
set_top in_circle
add_files merge_round.c
add_files -tb checkresult.c
add_files -tb ../serial/src/types.c
add_files -tb ../serial/src/types.h
open_solution "solution1"
set_part {xcu200-fsgd2104-2-e}
create_clock -period 10 -name default
config_export -vivado_optimization_level 0 -vivado_phys_opt none -vivado_report_level 0
config_schedule -effort medium -enable_dsp_full_reg -relax_ii_for_timing -verbose=0
config_compile -name_max_length 80 -no_signed_zeros=0 -pipeline_loops 64 -unsafe_math_optimizations=0
config_interface   -m_axi_addr64 -m_axi_offset off -register_io off -trim_dangling_port=0
config_rtl -encoding onehot -kernel_profile=0 -module_auto_prefix -mult_keep_attribute=0 -reset control -reset_async=0 -reset_level high -verbose=0
#source "./merge_round/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -rtl verilog -format ip_catalog -xo /home/users/alberto.giusti/FIDELTA/parallel/in_circle.xo
