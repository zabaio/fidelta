create_project prj -part xcu200-fsgd2104-2-e -force
set_property target_language verilog [current_project]
set vivado_ver [version -short]
set COE_DIR "../../syn/verilog"
source "/home/users/alberto.giusti/Desktop/backup/ap_uint_ii1/fidelta_apint/solution1/syn/verilog/accel_in_circle_accel_in_circle_ap_fsub_1_full_dsp_32_ip.tcl"
if {[regexp -nocase {2015\.3.*} $vivado_ver match] || [regexp -nocase {2016\.1.*} $vivado_ver match]} {
    extract_files -base_dir "./prjsrcs/sources_1/ip" [get_files -all -of [get_ips accel_in_circle_accel_in_circle_ap_fsub_1_full_dsp_32]]
}
source "/home/users/alberto.giusti/Desktop/backup/ap_uint_ii1/fidelta_apint/solution1/syn/verilog/accel_in_circle_accel_in_circle_ap_fadd_1_full_dsp_32_ip.tcl"
if {[regexp -nocase {2015\.3.*} $vivado_ver match] || [regexp -nocase {2016\.1.*} $vivado_ver match]} {
    extract_files -base_dir "./prjsrcs/sources_1/ip" [get_files -all -of [get_ips accel_in_circle_accel_in_circle_ap_fadd_1_full_dsp_32]]
}
source "/home/users/alberto.giusti/Desktop/backup/ap_uint_ii1/fidelta_apint/solution1/syn/verilog/accel_in_circle_accel_in_circle_ap_fmul_0_max_dsp_32_ip.tcl"
if {[regexp -nocase {2015\.3.*} $vivado_ver match] || [regexp -nocase {2016\.1.*} $vivado_ver match]} {
    extract_files -base_dir "./prjsrcs/sources_1/ip" [get_files -all -of [get_ips accel_in_circle_accel_in_circle_ap_fmul_0_max_dsp_32]]
}
source "/home/users/alberto.giusti/Desktop/backup/ap_uint_ii1/fidelta_apint/solution1/syn/verilog/accel_in_circle_accel_in_circle_ap_fcmp_0_no_dsp_32_ip.tcl"
if {[regexp -nocase {2015\.3.*} $vivado_ver match] || [regexp -nocase {2016\.1.*} $vivado_ver match]} {
    extract_files -base_dir "./prjsrcs/sources_1/ip" [get_files -all -of [get_ips accel_in_circle_accel_in_circle_ap_fcmp_0_no_dsp_32]]
}
