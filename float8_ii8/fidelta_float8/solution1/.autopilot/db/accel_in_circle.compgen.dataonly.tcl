# This script segment is generated automatically by AutoPilot

set axilite_register_dict [dict create]
set port_control {
ap_start { }
ap_done { }
ap_ready { }
ap_idle { }
indata_f0 { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 16
	offset_end 27
}
indata_f1 { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 28
	offset_end 39
}
indata_f2 { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 40
	offset_end 51
}
indata_f3 { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 52
	offset_end 63
}
indata_f4 { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 64
	offset_end 75
}
indata_f5 { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 76
	offset_end 87
}
indata_f6 { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 88
	offset_end 99
}
indata_f7 { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 100
	offset_end 111
}
instate { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 112
	offset_end 123
}
}
dict set axilite_register_dict control $port_control


