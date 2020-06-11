# This script segment is generated automatically by AutoPilot

set axilite_register_dict [dict create]
set port_control {
ap_start { }
ap_done { }
ap_ready { }
ap_idle { }
indata_V { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 16
	offset_end 27
}
instate_V { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 28
	offset_end 39
}
infather_V { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 40
	offset_end 51
}
inmaxquery { 
	dir I
	width 32
	depth 1
	mode ap_none
	offset 52
	offset_end 59
}
}
dict set axilite_register_dict control $port_control


