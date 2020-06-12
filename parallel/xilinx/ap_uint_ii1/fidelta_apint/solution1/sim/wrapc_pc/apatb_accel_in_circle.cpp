// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.2 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================

#define AP_INT_MAX_W 32678

#include <systemc>
#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <stdint.h>
#include "SysCFileHandler.h"
#include "ap_int.h"
#include "ap_fixed.h"
#include <complex>
#include <stdbool.h>
#include "autopilot_cbe.h"
#include "hls_stream.h"
#include "hls_half.h"
#include "hls_signal_handler.h"

using namespace std;
using namespace sc_core;
using namespace sc_dt;


// [dump_struct_tree [build_nameSpaceTree] dumpedStructList] ---------->


// [dump_enumeration [get_enumeration_list]] ---------->


// wrapc file define: "gmem1"
#define AUTOTB_TVIN_gmem1  "../tv/cdatafile/c.accel_in_circle_accel_in_circle.autotvin_gmem1.dat"
// wrapc file define: "gmem0"
#define AUTOTB_TVIN_gmem0  "../tv/cdatafile/c.accel_in_circle_accel_in_circle.autotvin_gmem0.dat"
#define AUTOTB_TVOUT_gmem0  "../tv/cdatafile/c.accel_in_circle_accel_in_circle.autotvout_gmem0.dat"
// wrapc file define: "indata_V"
#define AUTOTB_TVIN_indata_V  "../tv/cdatafile/c.accel_in_circle_accel_in_circle.autotvin_indata_V.dat"
// wrapc file define: "instate_V"
#define AUTOTB_TVIN_instate_V  "../tv/cdatafile/c.accel_in_circle_accel_in_circle.autotvin_instate_V.dat"

#define INTER_TCL  "../tv/cdatafile/ref.tcl"

// tvout file define: "gmem0"
#define AUTOTB_TVOUT_PC_gmem0  "../tv/rtldatafile/rtl.accel_in_circle_accel_in_circle.autotvout_gmem0.dat"

class INTER_TCL_FILE {
	public:
		INTER_TCL_FILE(const char* name) {
			mName = name;
			gmem1_depth = 0;
			gmem0_depth = 0;
			indata_V_depth = 0;
			instate_V_depth = 0;
			trans_num =0;
		}

		~INTER_TCL_FILE() {
			mFile.open(mName);
			if (!mFile.good()) {
				cout << "Failed to open file ref.tcl" << endl;
				exit (1);
			}
			string total_list = get_depth_list();
			mFile << "set depth_list {\n";
			mFile << total_list;
			mFile << "}\n";
			mFile << "set trans_num "<<trans_num<<endl;
			mFile.close();
		}

		string get_depth_list () {
			stringstream total_list;
			total_list << "{gmem1 " << gmem1_depth << "}\n";
			total_list << "{gmem0 " << gmem0_depth << "}\n";
			total_list << "{indata_V " << indata_V_depth << "}\n";
			total_list << "{instate_V " << instate_V_depth << "}\n";
			return total_list.str();
		}

		void set_num (int num , int* class_num) {
			(*class_num) = (*class_num) > num ? (*class_num) : num;
		}
	public:
		int gmem1_depth;
		int gmem0_depth;
		int indata_V_depth;
		int instate_V_depth;
		int trans_num;

	private:
		ofstream mFile;
		const char* mName;
};

extern void accel_in_circle (
ap_uint<512>* indata,
ap_uint<64>* instate);

void AESL_WRAP_accel_in_circle (
ap_uint<512>* indata,
ap_uint<64>* instate)
{
	refine_signal_handler();
	fstream wrapc_switch_file_token;
	wrapc_switch_file_token.open(".hls_cosim_wrapc_switch.log");
	int AESL_i;
	if (wrapc_switch_file_token.good())
	{
		CodeState = ENTER_WRAPC_PC;
		static unsigned AESL_transaction_pc = 0;
		string AESL_token;
		string AESL_num;
		static AESL_FILE_HANDLER aesl_fh;


		// output port post check: "gmem0"
		aesl_fh.read(AUTOTB_TVOUT_PC_gmem0, AESL_token); // [[transaction]]
		if (AESL_token != "[[transaction]]")
		{
			exit(1);
		}
		aesl_fh.read(AUTOTB_TVOUT_PC_gmem0, AESL_num); // transaction number

		if (atoi(AESL_num.c_str()) == AESL_transaction_pc)
		{
			aesl_fh.read(AUTOTB_TVOUT_PC_gmem0, AESL_token); // data

			sc_bv<64> *gmem0_pc_buffer = new sc_bv<64>[15];
			int i = 0;

			while (AESL_token != "[[/transaction]]")
			{
				bool no_x = false;
				bool err = false;

				// search and replace 'X' with "0" from the 1st char of token
				while (!no_x)
				{
					size_t x_found = AESL_token.find('X');
					if (x_found != string::npos)
					{
						if (!err)
						{
							cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'X' on port 'gmem0', possible cause: There are uninitialized variables in the C design." << endl;
							err = true;
						}
						AESL_token.replace(x_found, 1, "0");
					}
					else
					{
						no_x = true;
					}
				}

				no_x = false;

				// search and replace 'x' with "0" from the 3rd char of token
				while (!no_x)
				{
					size_t x_found = AESL_token.find('x', 2);

					if (x_found != string::npos)
					{
						if (!err)
						{
							cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'X' on port 'gmem0', possible cause: There are uninitialized variables in the C design." << endl;
							err = true;
						}
						AESL_token.replace(x_found, 1, "0");
					}
					else
					{
						no_x = true;
					}
				}

				// push token into output port buffer
				if (AESL_token != "")
				{
					gmem0_pc_buffer[i] = AESL_token.c_str();
					i++;
				}

				aesl_fh.read(AUTOTB_TVOUT_PC_gmem0, AESL_token); // data or [[/transaction]]

				if (AESL_token == "[[[/runtime]]]" || aesl_fh.eof(AUTOTB_TVOUT_PC_gmem0))
				{
					exit(1);
				}
			}

			// ***********************************
			if (i > 0)
			{
				// RTL Name: gmem0
				{
					// bitslice(63, 0)
					// {
						// celement: instate.V(63, 0)
						// {
							sc_lv<64>* instate_V_lv0_0_14_1 = new sc_lv<64>[15];
						// }
					// }

					// bitslice(63, 0)
					{
						int hls_map_index = 0;
						// celement: instate.V(63, 0)
						{
							// carray: (0) => (14) @ (1)
							for (int i_0 = 0; i_0 <= 14; i_0 += 1)
							{
								if (&(instate[0]) != NULL) // check the null address if the c port is array or others
								{
									instate_V_lv0_0_14_1[hls_map_index].range(63, 0) = sc_bv<64>(gmem0_pc_buffer[hls_map_index].range(63, 0));
									hls_map_index++;
								}
							}
						}
					}

					// bitslice(63, 0)
					{
						int hls_map_index = 0;
						// celement: instate.V(63, 0)
						{
							// carray: (0) => (14) @ (1)
							for (int i_0 = 0; i_0 <= 14; i_0 += 1)
							{
								// sub                    : i_0
								// ori_name               : instate[i_0]
								// sub_1st_elem           : 0
								// ori_name_1st_elem      : instate[0]
								// output_left_conversion : instate[i_0]
								// output_type_conversion : (instate_V_lv0_0_14_1[hls_map_index]).to_string(SC_BIN).c_str()
								if (&(instate[0]) != NULL) // check the null address if the c port is array or others
								{
									instate[i_0] = (instate_V_lv0_0_14_1[hls_map_index]).to_string(SC_BIN).c_str();
									hls_map_index++;
								}
							}
						}
					}
				}
			}

			// release memory allocation
			delete [] gmem0_pc_buffer;
		}

		AESL_transaction_pc++;
	}
	else
	{
		CodeState = ENTER_WRAPC;
		static unsigned AESL_transaction;

		static AESL_FILE_HANDLER aesl_fh;

		// "gmem1"
		char* tvin_gmem1 = new char[133];
		aesl_fh.touch(AUTOTB_TVIN_gmem1);

		// "gmem0"
		char* tvin_gmem0 = new char[50];
		aesl_fh.touch(AUTOTB_TVIN_gmem0);
		char* tvout_gmem0 = new char[50];
		aesl_fh.touch(AUTOTB_TVOUT_gmem0);

		// "indata_V"
		char* tvin_indata_V = new char[50];
		aesl_fh.touch(AUTOTB_TVIN_indata_V);

		// "instate_V"
		char* tvin_instate_V = new char[50];
		aesl_fh.touch(AUTOTB_TVIN_instate_V);

		CodeState = DUMP_INPUTS;
		static INTER_TCL_FILE tcl_file(INTER_TCL);
		int leading_zero;

		// [[transaction]]
		sprintf(tvin_gmem1, "[[transaction]] %d\n", AESL_transaction);
		aesl_fh.write(AUTOTB_TVIN_gmem1, tvin_gmem1);

		sc_bv<512>* gmem1_tvin_wrapc_buffer = new sc_bv<512>[15];

		// RTL Name: gmem1
		{
			// bitslice(511, 0)
			{
				int hls_map_index = 0;
				// celement: indata.V(511, 0)
				{
					// carray: (0) => (14) @ (1)
					for (int i_0 = 0; i_0 <= 14; i_0 += 1)
					{
						// sub                   : i_0
						// ori_name              : indata[i_0]
						// sub_1st_elem          : 0
						// ori_name_1st_elem     : indata[0]
						// regulate_c_name       : indata_V
						// input_type_conversion : (indata[i_0]).to_string(2).c_str()
						if (&(indata[0]) != NULL) // check the null address if the c port is array or others
						{
							sc_lv<512> indata_V_tmp_mem;
							indata_V_tmp_mem = (indata[i_0]).to_string(2).c_str();
							gmem1_tvin_wrapc_buffer[hls_map_index].range(511, 0) = indata_V_tmp_mem.range(511, 0);
                                 	       hls_map_index++;
						}
					}
				}
			}
		}

		// dump tv to file
		for (int i = 0; i < 15; i++)
		{
			sprintf(tvin_gmem1, "%s\n", (gmem1_tvin_wrapc_buffer[i]).to_string(SC_HEX).c_str());
			aesl_fh.write(AUTOTB_TVIN_gmem1, tvin_gmem1);
		}

		tcl_file.set_num(15, &tcl_file.gmem1_depth);
		sprintf(tvin_gmem1, "[[/transaction]] \n");
		aesl_fh.write(AUTOTB_TVIN_gmem1, tvin_gmem1);

		// release memory allocation
		delete [] gmem1_tvin_wrapc_buffer;

		// [[transaction]]
		sprintf(tvin_gmem0, "[[transaction]] %d\n", AESL_transaction);
		aesl_fh.write(AUTOTB_TVIN_gmem0, tvin_gmem0);

		sc_bv<64>* gmem0_tvin_wrapc_buffer = new sc_bv<64>[15];

		// RTL Name: gmem0
		{
			// bitslice(63, 0)
			{
				int hls_map_index = 0;
				// celement: instate.V(63, 0)
				{
					// carray: (0) => (14) @ (1)
					for (int i_0 = 0; i_0 <= 14; i_0 += 1)
					{
						// sub                   : i_0
						// ori_name              : instate[i_0]
						// sub_1st_elem          : 0
						// ori_name_1st_elem     : instate[0]
						// regulate_c_name       : instate_V
						// input_type_conversion : (instate[i_0]).to_string(2).c_str()
						if (&(instate[0]) != NULL) // check the null address if the c port is array or others
						{
							sc_lv<64> instate_V_tmp_mem;
							instate_V_tmp_mem = (instate[i_0]).to_string(2).c_str();
							gmem0_tvin_wrapc_buffer[hls_map_index].range(63, 0) = instate_V_tmp_mem.range(63, 0);
                                 	       hls_map_index++;
						}
					}
				}
			}
		}

		// dump tv to file
		for (int i = 0; i < 15; i++)
		{
			sprintf(tvin_gmem0, "%s\n", (gmem0_tvin_wrapc_buffer[i]).to_string(SC_HEX).c_str());
			aesl_fh.write(AUTOTB_TVIN_gmem0, tvin_gmem0);
		}

		tcl_file.set_num(15, &tcl_file.gmem0_depth);
		sprintf(tvin_gmem0, "[[/transaction]] \n");
		aesl_fh.write(AUTOTB_TVIN_gmem0, tvin_gmem0);

		// release memory allocation
		delete [] gmem0_tvin_wrapc_buffer;

		// [[transaction]]
		sprintf(tvin_indata_V, "[[transaction]] %d\n", AESL_transaction);
		aesl_fh.write(AUTOTB_TVIN_indata_V, tvin_indata_V);

		sc_bv<64> indata_V_tvin_wrapc_buffer;

		// RTL Name: indata_V
		{
		}

		// dump tv to file
		for (int i = 0; i < 1; i++)
		{
			sprintf(tvin_indata_V, "%s\n", (indata_V_tvin_wrapc_buffer).to_string(SC_HEX).c_str());
			aesl_fh.write(AUTOTB_TVIN_indata_V, tvin_indata_V);
		}

		tcl_file.set_num(1, &tcl_file.indata_V_depth);
		sprintf(tvin_indata_V, "[[/transaction]] \n");
		aesl_fh.write(AUTOTB_TVIN_indata_V, tvin_indata_V);

		// [[transaction]]
		sprintf(tvin_instate_V, "[[transaction]] %d\n", AESL_transaction);
		aesl_fh.write(AUTOTB_TVIN_instate_V, tvin_instate_V);

		sc_bv<64> instate_V_tvin_wrapc_buffer;

		// RTL Name: instate_V
		{
		}

		// dump tv to file
		for (int i = 0; i < 1; i++)
		{
			sprintf(tvin_instate_V, "%s\n", (instate_V_tvin_wrapc_buffer).to_string(SC_HEX).c_str());
			aesl_fh.write(AUTOTB_TVIN_instate_V, tvin_instate_V);
		}

		tcl_file.set_num(1, &tcl_file.instate_V_depth);
		sprintf(tvin_instate_V, "[[/transaction]] \n");
		aesl_fh.write(AUTOTB_TVIN_instate_V, tvin_instate_V);

// [call_c_dut] ---------->

		CodeState = CALL_C_DUT;
		accel_in_circle(indata, instate);

		CodeState = DUMP_OUTPUTS;

		// [[transaction]]
		sprintf(tvout_gmem0, "[[transaction]] %d\n", AESL_transaction);
		aesl_fh.write(AUTOTB_TVOUT_gmem0, tvout_gmem0);

		sc_bv<64>* gmem0_tvout_wrapc_buffer = new sc_bv<64>[15];

		// RTL Name: gmem0
		{
			// bitslice(63, 0)
			{
				int hls_map_index = 0;
				// celement: instate.V(63, 0)
				{
					// carray: (0) => (14) @ (1)
					for (int i_0 = 0; i_0 <= 14; i_0 += 1)
					{
						// sub                   : i_0
						// ori_name              : instate[i_0]
						// sub_1st_elem          : 0
						// ori_name_1st_elem     : instate[0]
						// regulate_c_name       : instate_V
						// input_type_conversion : (instate[i_0]).to_string(2).c_str()
						if (&(instate[0]) != NULL) // check the null address if the c port is array or others
						{
							sc_lv<64> instate_V_tmp_mem;
							instate_V_tmp_mem = (instate[i_0]).to_string(2).c_str();
							gmem0_tvout_wrapc_buffer[hls_map_index].range(63, 0) = instate_V_tmp_mem.range(63, 0);
                                 	       hls_map_index++;
						}
					}
				}
			}
		}

		// dump tv to file
		for (int i = 0; i < 15; i++)
		{
			sprintf(tvout_gmem0, "%s\n", (gmem0_tvout_wrapc_buffer[i]).to_string(SC_HEX).c_str());
			aesl_fh.write(AUTOTB_TVOUT_gmem0, tvout_gmem0);
		}

		tcl_file.set_num(15, &tcl_file.gmem0_depth);
		sprintf(tvout_gmem0, "[[/transaction]] \n");
		aesl_fh.write(AUTOTB_TVOUT_gmem0, tvout_gmem0);

		// release memory allocation
		delete [] gmem0_tvout_wrapc_buffer;

		CodeState = DELETE_CHAR_BUFFERS;
		// release memory allocation: "gmem1"
		delete [] tvin_gmem1;
		// release memory allocation: "gmem0"
		delete [] tvin_gmem0;
		delete [] tvout_gmem0;
		// release memory allocation: "indata_V"
		delete [] tvin_indata_V;
		// release memory allocation: "instate_V"
		delete [] tvin_instate_V;

		AESL_transaction++;

		tcl_file.set_num(AESL_transaction , &tcl_file.trans_num);
	}
}

