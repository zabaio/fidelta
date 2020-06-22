#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include "xcl2.hpp"

#define CL_HPP_CL_1_2_DEFAULT_BUILD
#define CL_HPP_TARGET_OPENCL_VERSION 120
#define CL_HPP_MINIMUM_OPENCL_VERSION 120
#define CL_HPP_ENABLE_PROGRAM_CONSTRUCTION_FROM_ARRAY_COMPATIBILITY 1
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS

int main(int argc, char *argv[])
{

    cl_int err;

    float *accel_data;
	int *accel_state;
	float *accel_son;

    OCL_CHECK (err, err = posix_memalign((void **) &accel_data, 4096, 3 * sizeof(float)));
	OCL_CHECK (err, err = posix_memalign((void **) &accel_state, 4096, 3 * sizeof(int)));
	OCL_CHECK (err, err = posix_memalign((void **) &accel_son, 4096, 6*sizeof(float)));

	std::string binaryName = argv[1];
	auto fileBuf = xcl::read_binary_file(binaryName);
	cl::Program::Binaries bins{{fileBuf.data(), fileBuf.size()}};

    auto devices = xcl::get_xil_devices();
    auto device = devices[0];

    std::cout << "Device Name: " << device.getInfo<CL_DEVICE_NAME>() << std::endl;

    cl::Context context;
    OCL_CHECK (err, context = cl::Context (device, NULL, NULL, NULL, &err));

    cl::CommandQueue q;
    OCL_CHECK (err, q = cl::CommandQueue (context, device,
    					CL_QUEUE_PROFILING_ENABLE | CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE, &err));

    OCL_CHECK (err, cl::Program program(context, {device}, bins, NULL, &err));

    cl::Kernel krnl_prova;
    OCL_CHECK (err, krnl_prova = cl::Kernel(program, "accel_prova", &err));

    int maxquery = 2;

    OCL_CHECK (err, cl::Buffer data_buf(
						context, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR,
						3*sizeof(float), (void *) accel_data, &err));

	OCL_CHECK (err, cl::Buffer state_buf(
						context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR,
						3*sizeof (int), (void *) accel_state, &err));

	OCL_CHECK (err, cl::Buffer son_buf(
						context, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR,
						6 * sizeof(float), (void *) accel_son, &err));

	OCL_CHECK (err, err = krnl_prova.setArg(0, maxquery));
	OCL_CHECK (err, err = krnl_prova.setArg(1, data_buf));
	OCL_CHECK (err, err = krnl_prova.setArg(2, state_buf));
	OCL_CHECK (err, err = krnl_prova.setArg(3, son_buf));

	// ----- End OpenCL initialization ---- //


	// --- Start reading input data set --- //

    cl::Event evts[3];

    OCL_CHECK (err, err = q.enqueueMigrateMemObjects({data_buf}, 0, NULL, evts));
    OCL_CHECK (err, err = q.enqueueMigrateMemObjects({state_buf}, 0, NULL, (evts + 1)));
    OCL_CHECK (err, err = q.enqueueMigrateMemObjects({son_buf}, 0, NULL, (evts + 2)));

	OCL_CHECK (err, err = q.enqueueTask(krnl_prova));

	OCL_CHECK (err, err = q.finish());


    return 0;
}
