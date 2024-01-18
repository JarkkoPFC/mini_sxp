//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// OpenCL functions
//============================================================================
#ifndef PFC_OCL_FUNC
#error define PFC_OCL_FUNC before including this file
#endif
//----------------------------------------------------------------------------

// platform & device access
PFC_OCL_FUNC(cl_int, clGetPlatformIDs, (cl_uint num_entries_, cl_platform_id *platforms_, cl_uint *num_platforms_), (num_entries_, platforms_, num_platforms_));
PFC_OCL_FUNC(cl_int, clGetPlatformInfo, (cl_platform_id plat_id_, cl_platform_info param_id_, size_t param_val_size_, void *param_val_, size_t *param_val_ret_size_), (plat_id_, param_id_, param_val_size_, param_val_, param_val_ret_size_));
PFC_OCL_FUNC(cl_int, clGetDeviceIDs, (cl_platform_id platform_, cl_device_type dev_type_, cl_uint num_entries_, cl_device_id *devs_, cl_uint *num_devs_), (platform_, dev_type_, num_entries_, devs_, num_devs_))
PFC_OCL_FUNC(cl_int, clGetDeviceInfo, (cl_device_id device_id_, cl_device_info param_id_, size_t param_val_size_, void *param_val_, size_t *param_val_ret_size_), (device_id_, param_id_, param_val_size_, param_val_, param_val_ret_size_));
// context & command queue resource management
PFC_OCL_FUNC(cl_context, clCreateContext, (const cl_context_properties *props_, cl_uint num_devices_, const cl_device_id *devices_, void (CL_CALLBACK *pfn_notify_)(const char*, const void*, size_t, void*), void *user_data_, cl_int *ret_val_), (props_, num_devices_, devices_, pfn_notify_, user_data_, ret_val_));
PFC_OCL_FUNC(cl_int, clReleaseContext, (cl_context ctx_), (ctx_));
PFC_OCL_FUNC(cl_int, clGetContextInfo, (cl_context ctx_, cl_context_info param_id_, size_t param_val_size_, void *param_val_, size_t *param_val_ret_size_), (ctx_, param_id_, param_val_size_, param_val_, param_val_ret_size_));
PFC_OCL_FUNC(cl_command_queue, clCreateCommandQueue, (cl_context ctx_, cl_device_id device_, const cl_command_queue_properties props_, cl_int *ret_val_), (ctx_, device_, props_, ret_val_));
PFC_OCL_FUNC(cl_command_queue, clCreateCommandQueueWithProperties, (cl_context ctx_, cl_device_id device_, const cl_queue_properties *props_, cl_int *ret_val_), (ctx_, device_, props_, ret_val_));
PFC_OCL_FUNC(cl_int, clReleaseCommandQueue, (cl_command_queue queue_), (queue_));
PFC_OCL_FUNC(cl_int, clGetCommandQueueInfo, (cl_command_queue queue_, cl_command_queue_info param_id_, size_t param_val_size_, void *param_val_, size_t *param_val_ret_size_), (queue_, param_id_, param_val_size_, param_val_, param_val_ret_size_));
// command queueing
PFC_OCL_FUNC(cl_int, clEnqueueNDRangeKernel, (cl_command_queue queue_, cl_kernel kernel_, cl_uint work_dim_, const size_t *global_work_offset_, const size_t *global_work_size_, const size_t *local_work_size_, cl_uint num_wait_events_, const cl_event *wait_events_, cl_event *event_), (queue_, kernel_, work_dim_, global_work_offset_, global_work_size_, local_work_size_, num_wait_events_, wait_events_, event_));
PFC_OCL_FUNC(cl_int, clEnqueueReadBuffer, (cl_command_queue queue_, cl_mem buffer_, cl_bool is_blocking_, size_t offset_, size_t size_, void *ptr_, cl_uint num_wait_events_, const cl_event *wait_events_, cl_event *event_), (queue_, buffer_, is_blocking_, offset_, size_, ptr_, num_wait_events_, wait_events_, event_));
PFC_OCL_FUNC(cl_int, clEnqueueReadImage, (cl_command_queue queue_, cl_mem img_, cl_bool is_blocking_, const size_t *origin_, const size_t *region_, size_t row_pitch_, size_t slice_pitch_, void *ptr_, cl_uint num_wait_events_, const cl_event *wait_events_, cl_event *event_), (queue_, img_, is_blocking_, origin_, region_, row_pitch_, slice_pitch_, ptr_, num_wait_events_, wait_events_, event_));
PFC_OCL_FUNC(cl_int, clEnqueueWriteBuffer, (cl_command_queue queue_, cl_mem buffer_, cl_bool is_blocking_, size_t offset_, size_t size_, const void *ptr_, cl_uint num_wait_events_, const cl_event *wait_events_, cl_event *event_), (queue_, buffer_, is_blocking_, offset_, size_, ptr_, num_wait_events_, wait_events_, event_));
PFC_OCL_FUNC(cl_int, clEnqueueFillBuffer, (cl_command_queue queue_, cl_mem buffer_, const void *pattern_, size_t pattern_size_, size_t offset_, size_t size_, cl_uint num_wait_events_, const cl_event *wait_events_, cl_event *event_), (queue_, buffer_, pattern_, pattern_size_, offset_, size_, num_wait_events_, wait_events_, event_));
PFC_OCL_FUNC(cl_int, clEnqueueWriteImage, (cl_command_queue queue_, cl_mem img_, cl_bool is_blocking_, const size_t *origin_, const size_t *region_, size_t row_pitch_, size_t slice_pitch_, const void *ptr_, cl_uint num_wait_events_, const cl_event *wait_events_, cl_event *event_), (queue_, img_, is_blocking_, origin_, region_, row_pitch_, slice_pitch_, ptr_, num_wait_events_, wait_events_, event_));
// command queue synchronization
PFC_OCL_FUNC(cl_int, clWaitForEvents, (cl_uint num_events_, const cl_event *events_), (num_events_, events_));
PFC_OCL_FUNC(cl_int, clGetEventInfo, (cl_event event_, cl_event_info param_name_, size_t param_val_size_, void *param_val_, size_t *param_val_size_ret_), (event_, param_name_, param_val_size_, param_val_, param_val_size_ret_));
PFC_OCL_FUNC(cl_int, clFinish, (cl_command_queue queue_), (queue_));
PFC_OCL_FUNC(cl_int, clReleaseEvent, (cl_event event_), (event_));
// program management
PFC_OCL_FUNC(cl_program, clCreateProgramWithSource, (cl_context ctx_, cl_uint num_strings_, const char **strings_, const size_t *string_lengths_, cl_int *ret_val_), (ctx_, num_strings_, strings_, string_lengths_, ret_val_));
PFC_OCL_FUNC(cl_program, clCreateProgramWithBinary, (cl_context ctx_, cl_uint num_devices_, const cl_device_id *devices_, const size_t *binary_sizes_, const unsigned char **binaries_, cl_int *binary_status_, cl_int *ret_val_), (ctx_, num_devices_, devices_, binary_sizes_, binaries_, binary_status_, ret_val_));
PFC_OCL_FUNC(cl_program, clCreateProgramWithBuiltInKernels, (cl_context ctx_, cl_uint num_devices_, const cl_device_id *devices_, const char *kernel_names_, cl_int *ret_val_), (ctx_, num_devices_, devices_, kernel_names_, ret_val_));
PFC_OCL_FUNC(cl_program, clCreateProgramWithIL, (cl_context ctx_, const void *il_binary_, size_t bin_size_, cl_int *ret_val_), (ctx_, il_binary_, bin_size_, ret_val_));
PFC_OCL_FUNC(cl_int, clReleaseProgram, (cl_program program_), (program_));
PFC_OCL_FUNC(cl_int, clGetProgramInfo, (cl_program program_, cl_program_info param_id_, size_t param_val_size_, void *param_val_, size_t *param_val_ret_size_), (program_, param_id_, param_val_size_, param_val_, param_val_ret_size_));
PFC_OCL_FUNC(cl_int, clCompileProgram, (cl_program program_, cl_uint num_devices_, const cl_device_id *devices_, const char *options_, cl_uint num_input_headers_, const cl_program *input_headers_, const char **header_include_names_, void (CL_CALLBACK *pfn_notify_)(cl_program, void*), void *user_data_), (program_, num_devices_, devices_, options_, num_input_headers_, input_headers_, header_include_names_, pfn_notify_, user_data_));
PFC_OCL_FUNC(cl_program, clLinkProgram, (cl_context ctx_, cl_uint num_devices_, const cl_device_id *devices_, const char *options_, cl_uint num_programs_, const cl_program *programs_, void (CL_CALLBACK *pfn_notify_)(cl_program, void*), void *user_data_, cl_int *ret_val_), (ctx_, num_devices_, devices_, options_, num_programs_, programs_, pfn_notify_, user_data_, ret_val_));
PFC_OCL_FUNC(cl_int, clBuildProgram, (cl_program program_, cl_uint num_devices_, const cl_device_id *devices_, const char *options_, void(CL_CALLBACK *pnf_notify_)(cl_program, void *user_data_), void *user_data_), (program_, num_devices_, devices_, options_, pnf_notify_, user_data_));
PFC_OCL_FUNC(cl_int, clGetProgramBuildInfo, (cl_program program_, cl_device_id device_, cl_program_build_info param_id_, size_t param_val_size_, void *param_val_, size_t *param_val_ret_size_), (program_, device_, param_id_, param_val_size_, param_val_, param_val_ret_size_));
// kernel management
PFC_OCL_FUNC(cl_kernel, clCreateKernel, (cl_program program_, const char *kernel_name_, cl_int *ret_val_), (program_, kernel_name_, ret_val_));
PFC_OCL_FUNC(cl_int, clReleaseKernel, (cl_kernel kernel_), (kernel_));
PFC_OCL_FUNC(cl_int, clGetKernelWorkGroupInfo, (cl_kernel kernel_, cl_device_id device_, cl_kernel_work_group_info param_id_, size_t param_val_size_, void *param_val_, size_t *param_val_ret_size_), (kernel_, device_, param_id_, param_val_size_, param_val_, param_val_ret_size_));
PFC_OCL_FUNC(cl_int, clSetKernelArg, (cl_kernel kernel_, cl_uint arg_idx_, size_t arg_size_, const void *arg_val_), (kernel_, arg_idx_, arg_size_, arg_val_));
// memory resource management
PFC_OCL_FUNC(cl_mem, clCreateBuffer, (cl_context ctx_, cl_mem_flags flags_, size_t size_, void *host_ptr_, cl_int *ret_val_), (ctx_, flags_, size_, host_ptr_, ret_val_));
PFC_OCL_FUNC(cl_mem, clCreateImage, (cl_context ctx_, cl_mem_flags flags_, const cl_image_format *img_fmt_, const cl_image_desc *img_desc_, void *data_, cl_int *ret_val_), (ctx_, flags_, img_fmt_, img_desc_, data_, ret_val_));
PFC_OCL_FUNC(cl_int, clReleaseMemObject, (cl_mem mem_), (mem_));
//----------------------------------------------------------------------------

#undef PFC_OCL_FUNC
//----------------------------------------------------------------------------
