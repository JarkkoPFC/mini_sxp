//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "ocl_device.h"
#include "sxp_src/core/sort.h"
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// helper functions
//============================================================================
namespace
{
  //==========================================================================
  // ocl_map_fp_config_enum
  //==========================================================================
  e_ocl_float_config ocl_map_fp_config_enum(cl_device_fp_config cfg_)
  {
    // map to OpenCL floating point feature flags
    uint32_t cfg=0;
    cfg|=cfg_&CL_FP_DENORM?oclfloatcfg_denorm:0;
    cfg|=cfg_&CL_FP_INF_NAN?oclfloatcfg_inf_nan:0;
    cfg|=cfg_&CL_FP_ROUND_TO_NEAREST?oclfloatcfg_round_to_nearest:0;
    cfg|=cfg_&CL_FP_ROUND_TO_ZERO?oclfloatcfg_round_to_zero:0;
    cfg|=cfg_&CL_FP_ROUND_TO_INF?oclfloatcfg_round_to_inf:0;
    cfg|=cfg_&CL_FP_FMA?oclfloatcfg_fma:0;
    cfg|=cfg_&CL_FP_CORRECTLY_ROUNDED_DIVIDE_SQRT?oclfloatcfg_correct_div_sqrt:0;
    cfg|=cfg_&CL_FP_SOFT_FLOAT?oclfloatcfg_soft_float:0;
    return e_ocl_float_config(cfg);
  }
  //--------------------------------------------------------------------------


  //==========================================================================
  // ocl_mem_flags
  //==========================================================================
  cl_mem_flags ocl_mem_flags(e_ocl_mem_type type_, bool has_data_)
  {
    // check memory type prerequisites
    bool is_alloc_device=!!(type_&oclmemtype_alloc_device), is_alloc_host=!!(type_&oclmemtype_alloc_host);
    PFC_ASSERT_MSG(!is_alloc_device || !is_alloc_host, ("OpenCL: Memory can't be allocated both from device and host memory.\r\n"));
    bool is_alloc_buf=is_alloc_device || is_alloc_host;
    PFC_ASSERT_MSG(is_alloc_buf || has_data_, ("OpenCL: Memory must be allocated from either device or host memory, or data buffer must be provided for storage.\r\n"));
    bool is_kernel_read=!!(type_&oclmemtype_kernel_read), is_kernel_write=!!(type_&oclmemtype_kernel_write);
    bool is_host_read=!!(type_&oclmemtype_host_read), is_host_write=!!(type_&oclmemtype_host_write);
    PFC_ASSERT_MSG(is_kernel_read || is_kernel_write, ("OpenCL: Memory must be either readable or writable by kernel.\r\n"));
    PFC_ASSERT_MSG(!is_alloc_buf || is_kernel_write || is_host_write || has_data_, ("OpenCL: Kernel read-only memory that's not host-writable must define input data.\r\n"));
    PFC_ASSERT_MSG(!is_alloc_buf || is_kernel_read || is_host_read, ("OpenCL: Kernel write-only memory that's not kernel/host readable is useless.\r\n"));

    // setup OpenCL memory flags
    cl_mem_flags flags=!is_alloc_buf?CL_MEM_USE_HOST_PTR:(has_data_?CL_MEM_COPY_HOST_PTR:0)|(is_alloc_host?CL_MEM_ALLOC_HOST_PTR:0);
    flags|=is_kernel_read && is_kernel_write?CL_MEM_READ_WRITE:is_kernel_read?CL_MEM_READ_ONLY:is_kernel_write?CL_MEM_WRITE_ONLY:0;
    flags|=is_host_read && is_host_write?0:is_host_read?CL_MEM_HOST_READ_ONLY:is_host_write?CL_MEM_HOST_WRITE_ONLY:CL_MEM_HOST_NO_ACCESS;
    return flags;
  }
  //--------------------------------------------------------------------------


  //==========================================================================
  // ocl_image_format
  //==========================================================================
  cl_image_format ocl_image_format(e_ocl_image_format fmt_)
  {
    // map to OpenCL texture format
    cl_image_format fmt={0, 0};
    switch(fmt_)
    {
      // R-channel
      case oclimgfmt_r8u:   fmt.image_channel_order=CL_R; fmt.image_channel_data_type=CL_UNSIGNED_INT8; break;
      case oclimgfmt_r8s:   fmt.image_channel_order=CL_R; fmt.image_channel_data_type=CL_SIGNED_INT8; break;
      case oclimgfmt_r8un:  fmt.image_channel_order=CL_R; fmt.image_channel_data_type=CL_UNORM_INT8; break;
      case oclimgfmt_r8sn:  fmt.image_channel_order=CL_R; fmt.image_channel_data_type=CL_SNORM_INT8; break;
      case oclimgfmt_r16u:  fmt.image_channel_order=CL_R; fmt.image_channel_data_type=CL_UNSIGNED_INT16; break;
      case oclimgfmt_r16s:  fmt.image_channel_order=CL_R; fmt.image_channel_data_type=CL_SIGNED_INT16; break;
      case oclimgfmt_r16un: fmt.image_channel_order=CL_R; fmt.image_channel_data_type=CL_UNORM_INT16; break;
      case oclimgfmt_r16sn: fmt.image_channel_order=CL_R; fmt.image_channel_data_type=CL_SNORM_INT16; break;
      case oclimgfmt_r16f:  fmt.image_channel_order=CL_R; fmt.image_channel_data_type=CL_HALF_FLOAT; break;
      case oclimgfmt_r32u:  fmt.image_channel_order=CL_R; fmt.image_channel_data_type=CL_UNSIGNED_INT32; break;
      case oclimgfmt_r32s:  fmt.image_channel_order=CL_R; fmt.image_channel_data_type=CL_SIGNED_INT32; break;
      case oclimgfmt_r32f:  fmt.image_channel_order=CL_R; fmt.image_channel_data_type=CL_FLOAT; break;
      // Depth-channel
      case oclimgfmt_d16un: fmt.image_channel_order=CL_DEPTH; fmt.image_channel_data_type=CL_UNORM_INT16; break;
      case oclimgfmt_d32f:  fmt.image_channel_order=CL_DEPTH; fmt.image_channel_data_type=CL_FLOAT; break;
      // RG-channels
      case oclimgfmt_r8g8u:    fmt.image_channel_order=CL_RG; fmt.image_channel_data_type=CL_UNSIGNED_INT8; break;
      case oclimgfmt_r8g8s:    fmt.image_channel_order=CL_RG; fmt.image_channel_data_type=CL_SIGNED_INT8; break;
      case oclimgfmt_r8g8un:   fmt.image_channel_order=CL_RG; fmt.image_channel_data_type=CL_UNORM_INT8; break;
      case oclimgfmt_r8g8sn:   fmt.image_channel_order=CL_RG; fmt.image_channel_data_type=CL_SNORM_INT8; break;
      case oclimgfmt_r16g16u:  fmt.image_channel_order=CL_RG; fmt.image_channel_data_type=CL_UNSIGNED_INT16; break;
      case oclimgfmt_r16g16s:  fmt.image_channel_order=CL_RG; fmt.image_channel_data_type=CL_SIGNED_INT16; break;
      case oclimgfmt_r16g16un: fmt.image_channel_order=CL_RG; fmt.image_channel_data_type=CL_UNORM_INT16; break;
      case oclimgfmt_r16g16sn: fmt.image_channel_order=CL_RG; fmt.image_channel_data_type=CL_SNORM_INT16; break;
      case oclimgfmt_r16g16f:  fmt.image_channel_order=CL_RG; fmt.image_channel_data_type=CL_HALF_FLOAT; break;
      case oclimgfmt_r32g32u:  fmt.image_channel_order=CL_RG; fmt.image_channel_data_type=CL_UNSIGNED_INT32; break;
      case oclimgfmt_r32g32s:  fmt.image_channel_order=CL_RG; fmt.image_channel_data_type=CL_SIGNED_INT32; break;
      case oclimgfmt_r32g32f:  fmt.image_channel_order=CL_RG; fmt.image_channel_data_type=CL_FLOAT; break;
      // RGBA-channels
      case oclimgfmt_r8g8b8a8u:      fmt.image_channel_order=CL_RGBA; fmt.image_channel_data_type=CL_UNSIGNED_INT8; break;
      case oclimgfmt_r8g8b8a8s:      fmt.image_channel_order=CL_RGBA; fmt.image_channel_data_type=CL_SIGNED_INT8; break;
      case oclimgfmt_r8g8b8a8un:     fmt.image_channel_order=CL_RGBA; fmt.image_channel_data_type=CL_UNORM_INT8; break;
      case oclimgfmt_r8g8b8a8sn:     fmt.image_channel_order=CL_RGBA; fmt.image_channel_data_type=CL_SNORM_INT8; break;
      case oclimgfmt_r16g16b16a16u:  fmt.image_channel_order=CL_RGBA; fmt.image_channel_data_type=CL_UNSIGNED_INT16; break;
      case oclimgfmt_r16g16b16a16s:  fmt.image_channel_order=CL_RGBA; fmt.image_channel_data_type=CL_SIGNED_INT16; break;
      case oclimgfmt_r16g16b16a16un: fmt.image_channel_order=CL_RGBA; fmt.image_channel_data_type=CL_UNORM_INT16; break;
      case oclimgfmt_r16g16b16a16sn: fmt.image_channel_order=CL_RGBA; fmt.image_channel_data_type=CL_SNORM_INT16; break;
      case oclimgfmt_r16g16b16a16f:  fmt.image_channel_order=CL_RGBA; fmt.image_channel_data_type=CL_HALF_FLOAT; break;
      case oclimgfmt_r32g32b32a32u:  fmt.image_channel_order=CL_RGBA; fmt.image_channel_data_type=CL_UNSIGNED_INT32; break;
      case oclimgfmt_r32g32b32a32s:  fmt.image_channel_order=CL_RGBA; fmt.image_channel_data_type=CL_SIGNED_INT32; break;
      case oclimgfmt_r32g32b32a32f:  fmt.image_channel_order=CL_RGBA; fmt.image_channel_data_type=CL_FLOAT; break;
      // BGRA-channels
      case oclimgfmt_b8g8r8a8un: fmt.image_channel_order=CL_BGRA; fmt.image_channel_data_type=CL_UNORM_INT8; break;
      // sRGBA-channels
      case oclimgfmt_sr8g8b8a8un: fmt.image_channel_order=CL_sRGBA; fmt.image_channel_data_type=CL_UNORM_INT8; break;
      default: PFC_ERROR(("OpenCL: Unsupported texture format \"%s\".\r\n", enum_string(fmt_)));
    }
    return fmt;
  }
  //--------------------------------------------------------------------------
} // namespace <anonymous>
//----------------------------------------------------------------------------

//============================================================================
// e_ocl_platform_profile
//============================================================================
#define PFC_ENUM_NAMESPACE pfc
#define PFC_ENUM_TYPE e_ocl_platform_profile
#define PFC_ENUM_PREFIX oclplatprof_
#define PFC_ENUM_VALS PFC_ENUM_VAL(unknown) \
                      PFC_ENUM_VAL(full) \
                      PFC_ENUM_VAL(embedded)
#include "sxp_src/core/enum.inc"
//----------------------------------------------------------------------------


//============================================================================
// e_ocl_device_type
//============================================================================
#define PFC_ENUM_NAMESPACE pfc
#define PFC_ENUM_TYPE e_ocl_device_type
#define PFC_ENUM_PREFIX ocldevtype_
#define PFC_ENUM_VALS PFC_ENUM_VAL_N(cpu, "CPU") \
                      PFC_ENUM_VAL_N(gpu, "GPU") \
                      PFC_ENUM_VAL_N(accelerator, "Accelerator") \
                      PFC_ENUM_VAL_N(custom, "Custom")
#include "sxp_src/core/enum.inc"
//----------------------------------------------------------------------------


//============================================================================
// e_ocl_float_config
//============================================================================
#define PFC_ENUM_NAMESPACE pfc
#define PFC_ENUM_TYPE e_ocl_float_config
#define PFC_ENUM_PREFIX oclfloatcfg_
#define PFC_ENUM_VALS PFC_ENUM_VAL(denorm) \
                      PFC_ENUM_VAL(inf_nan) \
                      PFC_ENUM_VAL(round_to_nearest) \
                      PFC_ENUM_VAL(round_to_zero) \
                      PFC_ENUM_VAL(round_to_inf) \
                      PFC_ENUM_VAL(fma) \
                      PFC_ENUM_VAL(correct_div_sqrt) \
                      PFC_ENUM_VAL(soft_float)
#include "sxp_src/core/enum.inc"
//----------------------------------------------------------------------------


//============================================================================
// e_ocl_data_type
//============================================================================
#define PFC_ENUM_NAMESPACE pfc
#define PFC_ENUM_TYPE e_ocl_data_type
#define PFC_ENUM_PREFIX ocldatatype_
#define PFC_ENUM_VALS PFC_ENUM_VAL(bool) \
                      PFC_ENUM_VAL(char)   PFC_ENUM_VAL(char2)   PFC_ENUM_VAL(char3)   PFC_ENUM_VAL(char4)   PFC_ENUM_VAL(char8)   PFC_ENUM_VAL(char16) \
                      PFC_ENUM_VAL(uchar)  PFC_ENUM_VAL(uchar2)  PFC_ENUM_VAL(uchar3)  PFC_ENUM_VAL(uchar4)  PFC_ENUM_VAL(uchar8)  PFC_ENUM_VAL(uchar16) \
                      PFC_ENUM_VAL(short)  PFC_ENUM_VAL(short2)  PFC_ENUM_VAL(short3)  PFC_ENUM_VAL(short4)  PFC_ENUM_VAL(short8)  PFC_ENUM_VAL(short16) \
                      PFC_ENUM_VAL(ushort) PFC_ENUM_VAL(ushort2) PFC_ENUM_VAL(ushort3) PFC_ENUM_VAL(ushort4) PFC_ENUM_VAL(ushort8) PFC_ENUM_VAL(ushort16) \
                      PFC_ENUM_VAL(int)    PFC_ENUM_VAL(int2)    PFC_ENUM_VAL(int3)    PFC_ENUM_VAL(int4)    PFC_ENUM_VAL(int8)    PFC_ENUM_VAL(int16) \
                      PFC_ENUM_VAL(uint)   PFC_ENUM_VAL(uint2)   PFC_ENUM_VAL(uint3)   PFC_ENUM_VAL(uint4)   PFC_ENUM_VAL(uint8)   PFC_ENUM_VAL(uint16) \
                      PFC_ENUM_VAL(long)   PFC_ENUM_VAL(long2)   PFC_ENUM_VAL(long3)   PFC_ENUM_VAL(long4)   PFC_ENUM_VAL(long8)   PFC_ENUM_VAL(long16) \
                      PFC_ENUM_VAL(ulong)  PFC_ENUM_VAL(ulong2)  PFC_ENUM_VAL(ulong3)  PFC_ENUM_VAL(ulong4)  PFC_ENUM_VAL(ulong8)  PFC_ENUM_VAL(ulong16) \
                      PFC_ENUM_VAL(half)   PFC_ENUM_VAL(half2)   PFC_ENUM_VAL(half3)   PFC_ENUM_VAL(half4)   PFC_ENUM_VAL(half8)   PFC_ENUM_VAL(half16) \
                      PFC_ENUM_VAL(float)  PFC_ENUM_VAL(float2)  PFC_ENUM_VAL(float3)  PFC_ENUM_VAL(float4)  PFC_ENUM_VAL(float8)  PFC_ENUM_VAL(float16) \
                      PFC_ENUM_VAL(double) PFC_ENUM_VAL(double2) PFC_ENUM_VAL(double3) PFC_ENUM_VAL(double4) PFC_ENUM_VAL(double8) PFC_ENUM_VAL(double16)
#include "sxp_src/core/enum.inc"
//----------------------------------------------------------------------------


//============================================================================
// e_ocl_cache_type
//============================================================================
#define PFC_ENUM_NAMESPACE pfc
#define PFC_ENUM_TYPE e_ocl_cache_type
#define PFC_ENUM_PREFIX oclcachetype_
#define PFC_ENUM_VALS PFC_ENUM_VAL(none) \
                      PFC_ENUM_VAL(read_only) \
                      PFC_ENUM_VAL(read_write)
#include "sxp_src/core/enum.inc"
//----------------------------------------------------------------------------


//============================================================================
// e_ocl_local_mem_type
//============================================================================
#define PFC_ENUM_NAMESPACE pfc
#define PFC_ENUM_TYPE e_ocl_local_mem_type
#define PFC_ENUM_PREFIX ocllocalmemtype_
#define PFC_ENUM_VALS PFC_ENUM_VAL(none) \
                      PFC_ENUM_VAL(local) \
                      PFC_ENUM_VAL(global)
#include "sxp_src/core/enum.inc"
//----------------------------------------------------------------------------


//============================================================================
// e_ocl_mem_type
//============================================================================
#define PFC_ENUM_NAMESPACE pfc
#define PFC_ENUM_TYPE e_ocl_mem_type
#define PFC_ENUM_PREFIX oclmemtype_
#define PFC_ENUM_VALS PFC_ENUM_VAL(kernel_read) \
                      PFC_ENUM_VAL(kernel_write) \
                      PFC_ENUM_VAL(host_read) \
                      PFC_ENUM_VAL(host_write) \
                      PFC_ENUM_VAL(alloc_device) \
                      PFC_ENUM_VAL(alloc_host)
#include "sxp_src/core/enum.inc"
//----------------------------------------------------------------------------


//============================================================================
// e_ocl_image_format
//============================================================================
#define PFC_ENUM_NAMESPACE pfc
#define PFC_ENUM_TYPE e_ocl_image_format
#define PFC_ENUM_PREFIX oclimgfmt_
#define PFC_ENUM_VALS PFC_ENUM_VAL(r8u) PFC_ENUM_VAL(r8s) PFC_ENUM_VAL(r8un) PFC_ENUM_VAL(r8sn) \
                      PFC_ENUM_VAL(r16u) PFC_ENUM_VAL(r16s) PFC_ENUM_VAL(r16un) PFC_ENUM_VAL(r16sn) PFC_ENUM_VAL(r16f) \
                      PFC_ENUM_VAL(r32u) PFC_ENUM_VAL(r32s) PFC_ENUM_VAL(r32f) \
                      PFC_ENUM_VAL(d16un) \
                      PFC_ENUM_VAL(d32f) \
                      PFC_ENUM_VAL(r8g8u) PFC_ENUM_VAL(r8g8s) PFC_ENUM_VAL(r8g8un) PFC_ENUM_VAL(r8g8sn) \
                      PFC_ENUM_VAL(r16g16u) PFC_ENUM_VAL(r16g16s) PFC_ENUM_VAL(r16g16un) PFC_ENUM_VAL(r16g16sn) PFC_ENUM_VAL(r16g16f) \
                      PFC_ENUM_VAL(r32g32u) PFC_ENUM_VAL(r32g32s) PFC_ENUM_VAL(r32g32f) \
                      PFC_ENUM_VAL(r8g8b8a8u) PFC_ENUM_VAL(r8g8b8a8s) PFC_ENUM_VAL(r8g8b8a8sn) PFC_ENUM_VAL(r8g8b8a8un) \
                      PFC_ENUM_VAL(r16g16b16a16u) PFC_ENUM_VAL(r16g16b16a16s) PFC_ENUM_VAL(r16g16b16a16un) PFC_ENUM_VAL(r16g16b16a16sn) PFC_ENUM_VAL(r16g16b16a16f) \
                      PFC_ENUM_VAL(r32g32b32a32u) PFC_ENUM_VAL(r32g32b32a32s) PFC_ENUM_VAL(r32g32b32a32f) \
                      PFC_ENUM_VAL(b8g8r8a8un) \
                      PFC_ENUM_VAL(sr8g8b8a8un)
#include "sxp_src/core/enum.inc"
//----------------------------------------------------------------------------


//============================================================================
// ocl_device_info
//============================================================================
ocl_device_info::ocl_device_info()
{
  // init device info
  id=0;
  type=ocldevtype_unknown;
  is_big_endian=false;
  supported_spir_versions=oclspir_none;
  max_clock_freq_mhz=0;
  max_compute_units=0;
  max_estimated_gflops=0;
  max_work_group_size=0;
  single_fp_config=oclfloatcfg_none;
  double_fp_config=oclfloatcfg_none;
  preferred_vector_width_char=0;
  preferred_vector_width_short=0;
  preferred_vector_width_int=0;
  preferred_vector_width_long=0;
  preferred_vector_width_float=0;
  preferred_vector_width_double=0;
  preferred_vector_width_half=0;
  native_vector_width_char=0;
  native_vector_width_short=0;
  native_vector_width_int=0;
  native_vector_width_long=0;
  native_vector_width_float=0;
  native_vector_width_double=0;
  native_vector_width_half=0;
  num_address_bits=0;
  global_mem_size=0;
  max_mem_alloc_size=0;
  mem_base_address_align=0;
  global_cache_type=oclcachetype_none;
  global_cache_size=0;
  global_cacheline_size=0;
  local_mem_type=ocllocalmemtype_none;
  local_mem_size=0;
  max_constant_buffer_size=0;
  max_constant_args=0;
  is_image_support=false;
  image_pitch_align=0;
  image_base_address_align=0;
  max_image_read_args=0;
  max_image_write_args=0;
  max_image_rw_args=0;
  max_image_2d_width=0;
  max_image_2d_height=0;
  max_image_3d_width=0;
  max_image_3d_height=0;
  max_image_3d_depth=0;
  max_image_array_size=0;
  max_image_buffer_size=0;
  max_image_samplers=0;
}
//----------------------------------------------------------------------------


//============================================================================
// ocl_platform_info
//============================================================================
ocl_platform_info::ocl_platform_info()
{
  id=0;
  profile=oclplatprof_unknown;
  max_estimated_gflops=0;
}
//----------------------------------------------------------------------------


//============================================================================
// sorting predicates
//============================================================================
struct ocl_platform_info_sort_pred
{
  PFC_INLINE bool before(const ocl_platform_info &plat0_, const ocl_platform_info &plat1_)
  {
    return  plat0_.max_estimated_gflops>plat1_.max_estimated_gflops;
  }
};
//----

struct ocl_device_info_sort_pred
{
  PFC_INLINE bool before(const ocl_device_info &dev0_, const ocl_device_info &dev1_)
  {
    return  dev0_.max_estimated_gflops>dev1_.max_estimated_gflops;
  }
};
//----

struct ocl_env_device_sort_pred
{
  PFC_INLINE bool before(const ocl_env::device_t &dev0_, const ocl_env::device_t &dev1_)
  {
    return  dev0_.second->max_estimated_gflops>dev1_.second->max_estimated_gflops;
  }
};
//----------------------------------------------------------------------------


//============================================================================
// ocl_program
//============================================================================
ocl_program::ocl_program()
  :m_program(0)
  ,m_num_devices(0)
{
}
//----

ocl_program::ocl_program(cl_program prog_)
  :m_program(0)
  ,m_num_devices(0)
{
  init(prog_);
}
//----

ocl_program::~ocl_program()
{
  release();
}
//----

void ocl_program::init(cl_program prog_)
{
  // release program and fetch number of devices associated with the program
  release();
  cl_uint num_devs=0;
  PFC_OCL_VERIFY_MSG(ocl_env::clGetProgramInfo(prog_, CL_PROGRAM_NUM_DEVICES, sizeof(num_devs), &num_devs, 0),
                     ("Unable to retrieve the number of program devices.\r\n"));
  m_program=prog_;
  m_num_devices=num_devs;
}
//----

void ocl_program::release()
{
  // release program
  if(m_program)
  {
    ocl_env::clReleaseProgram(m_program);
    m_program=0;
    m_num_devices=0;
  }
}
//----------------------------------------------------------------------------

cl_kernel ocl_program::create_kernel(const char *kernel_name_) const
{
  // create kernel
  PFC_ASSERT_PEDANTIC(m_program);
  cl_int ret_val=0;
  cl_kernel kernel=ocl_env::clCreateKernel(m_program, kernel_name_, &ret_val);
  PFC_OCL_VALIDATE_MSG(ret_val, ("Kernel \"%s\" creation failed.\r\n", kernel_name_), return 0);
  return kernel;
}
//----------------------------------------------------------------------------

void ocl_program::fetch_device_binaries(raw_data *binaries_) const
{
  // query binary sizes and fetch the program binaries
  PFC_ASSERT_PEDANTIC(m_program);
  size_t *binary_sizes=(size_t*)PFC_STACK_MALLOC(sizeof(size_t)*m_num_devices);
  void **binaries=(void**)PFC_STACK_MALLOC(sizeof(void*)*m_num_devices);
  PFC_OCL_VERIFY_MSG(ocl_env::clGetProgramInfo(m_program, CL_PROGRAM_BINARY_SIZES, sizeof(size_t)*m_num_devices, binary_sizes, 0),
                     ("Failed to query program binary sizes.\r\n"));
  for(unsigned i=0; i<m_num_devices; ++i)
  {
    binaries_[i].alloc(binary_sizes[i]);
    binaries[i]=binaries_[i].data;
  }
  PFC_OCL_VERIFY_MSG(ocl_env::clGetProgramInfo(m_program, CL_PROGRAM_BINARIES, sizeof(void*)*m_num_devices, binaries, 0),
                     ("Failed to fetch program binaries.\r\n"));
}
//----------------------------------------------------------------------------


//============================================================================
// ocl_kernel
//============================================================================
ocl_kernel::ocl_kernel()
  :m_kernel(0)
{
}
//----

ocl_kernel::ocl_kernel(cl_kernel kernel_)
  :m_kernel(kernel_)
{
}
//----

ocl_kernel::~ocl_kernel()
{
  release();
}
//----

void ocl_kernel::init(cl_kernel kernel_)
{
  release();
  m_kernel=kernel_;
}
//----

void ocl_kernel::release()
{
  if(m_kernel)
  {
    ocl_env::clReleaseKernel(m_kernel);
    m_kernel=0;
  }
}
//----------------------------------------------------------------------------


//============================================================================
// ocl_memory
//============================================================================
ocl_memory::ocl_memory()
  :m_mem(0)
{
}
//----

ocl_memory::ocl_memory(cl_mem mem_)
  :m_mem(mem_)
{
}
//----

ocl_memory::~ocl_memory()
{
  release();
}
//----

void ocl_memory::init(cl_mem mem_)
{
  release();
  m_mem=mem_;
}
//----

void ocl_memory::release()
{
  if(m_mem)
  {
    ocl_env::clReleaseMemObject(m_mem);
    m_mem=0;
  }
}
//----------------------------------------------------------------------------


//============================================================================
// ocl_event
//============================================================================
ocl_event::ocl_event()
  :m_event(0)
{
}
//----

ocl_event::ocl_event(cl_event event_)
  :m_event(event_)
{
}
//----

ocl_event::~ocl_event()
{
  release();
}
//----

void ocl_event::init(cl_event event_)
{
  release();
  m_event=event_;
}
//----

void ocl_event::release()
{
  if(m_event)
  {
    PFC_OCL_VERIFY_MSG(ocl_env::clReleaseEvent(m_event),
                       ("Releasing event failed.\r\n"));
    m_event=0;
  }
}
//----------------------------------------------------------------------------

void ocl_event::wait(const ocl_event *events_, unsigned num_events_)
{
  PFC_STATIC_ASSERT(sizeof(cl_event)==sizeof(ocl_event));
  PFC_OCL_VERIFY_MSG(ocl_env::clWaitForEvents(num_events_, (const cl_event*)events_),
                     ("Wait for events failed.\r\n"));
}
//----------------------------------------------------------------------------


//============================================================================
// ocl_env
//============================================================================
ocl_env *ocl_env::s_active=0;
#define PFC_OCL_FUNC(rtype__, fname__, fargs__, cargs__) rtype__(CL_API_ENTRY CL_API_CALL* ocl_env::s_fn_##fname__)fargs__=0;
#include "ocl_device.inc"
//----------------------------------------------------------------------------

ocl_env::ocl_env()
{
  // config
  enum {max_platforms=16};
  enum {max_platform_devices=16};

  // activate environment
  PFC_CHECK_MSG(!s_active, ("ocl_env has already been created.\r\n"));
  s_active=this;

  // load OpenCL and import functions
  m_module=LoadLibrary("OpenCL.dll");
  if(!m_module)
  {
    PFC_WARN(("OpenCL: Unable to load OpenCL.dll.\r\n"));
    return;
  }
  #define PFC_OCL_FUNC(rtype__, fname__, fargs__, cargs__) s_fn_##fname__=(fname__##_t)GetProcAddress(m_module, #fname__);
  #include "ocl_device.inc"

  // get available platform ID's
  cl_platform_id plat_ids[max_platforms];
  cl_uint num_plats=0;
  PFC_OCL_VERIFY_MSG(clGetPlatformIDs(max_platforms, plat_ids, &num_plats), ("Unable to query available OpenCL platforms.\r\n"))

  // fetch platform infos
  unsigned num_total_devices=0;
  m_platforms.resize(num_plats);
  char val_str[1024];
  for(unsigned pi=0; pi<num_plats; ++pi)
  {
    // setup platform ID
    ocl_platform_info &pinfo=m_platforms[pi];
    pinfo.id=plat_ids[pi];

    // fetch platform name, version and vendor
    mem_zero(val_str, sizeof(val_str));
    PFC_OCL_VERIFY_MSG(clGetPlatformInfo(pinfo.id, CL_PLATFORM_NAME, sizeof(val_str), val_str, NULL), ("Unable to query platform name.\r\n"));
    str_strip_extra_whitespace(val_str);
    pinfo.name=val_str;
    mem_zero(val_str, sizeof(val_str));
    PFC_OCL_VERIFY_MSG(clGetPlatformInfo(pinfo.id, CL_PLATFORM_VERSION, sizeof(val_str), val_str, NULL), ("Unable to query platform version.\r\n"));
    str_strip_extra_whitespace(val_str);
    pinfo.version=val_str;
    mem_zero(val_str, sizeof(val_str));
    PFC_OCL_VERIFY_MSG(clGetPlatformInfo(pinfo.id, CL_PLATFORM_VENDOR, sizeof(val_str), val_str, NULL), ("Unable to query platform vendor.\r\n"));
    str_strip_extra_whitespace(val_str);
    pinfo.vendor=val_str;

    // fetch platform profile
    mem_zero(val_str, sizeof(val_str));
    PFC_OCL_VERIFY_MSG(clGetPlatformInfo(pinfo.id, CL_PLATFORM_PROFILE, sizeof(val_str), val_str, NULL), ("Unable to query platform profile.\r\n"));
    if(str_eq(val_str, "FULL_PROFILE"))
      pinfo.profile=oclplatprof_full;
    else if(str_eq(val_str, "EMBEDDED_PROFILE"))
      pinfo.profile=oclplatprof_embedded;
    else
      PFC_WARN(("OpenCL: Unknown platform profile.\r\n"));

    // query platform device infos
    cl_device_id device_ids[max_platform_devices];
    cl_uint num_devices=0;
    PFC_OCL_VERIFY_MSG(clGetDeviceIDs(pinfo.id, CL_DEVICE_TYPE_ALL, max_platform_devices, device_ids, &num_devices), ("Device query failed.\r\n"));
    pinfo.devices.resize(num_devices);
    for(unsigned di=0; di<num_devices; ++di)
    {
      // setup device ID
      #define PFC_OCL_DEV_INFO(param__, param_type__, param_id__, param_assign__) {param_type__ p; if(clGetDeviceInfo(dinfo.id, param_id__, sizeof(param_type__), &p, 0)==CL_SUCCESS) param__=param_assign__;}
      #define PFC_OCL_DEV_INFO_STR(param__, param_id__) {mem_zero(val_str, sizeof(val_str)); if(clGetDeviceInfo(dinfo.id, param_id__, sizeof(val_str), &val_str, NULL)==CL_SUCCESS) {str_strip_extra_whitespace(val_str); param__=val_str;}}
      ocl_device_info &dinfo=pinfo.devices[di];
      dinfo.id=device_ids[di];

      // query device name, vendor & version
      PFC_OCL_DEV_INFO_STR(dinfo.name, CL_DEVICE_NAME);
      PFC_OCL_DEV_INFO_STR(dinfo.vendor_name, CL_DEVICE_VENDOR);
      PFC_OCL_DEV_INFO_STR(dinfo.version, CL_DEVICE_VERSION);
      PFC_OCL_DEV_INFO_STR(dinfo.driver_version, CL_DRIVER_VERSION);

      // query device type
      cl_device_type dev_type;
      PFC_OCL_VERIFY_MSG(clGetDeviceInfo(dinfo.id, CL_DEVICE_TYPE, sizeof(dev_type), &dev_type, 0), ("Device type query failed.\r\n"));
      switch(dev_type)
      {
        case CL_DEVICE_TYPE_CPU: dinfo.type=ocldevtype_cpu; break;
        case CL_DEVICE_TYPE_GPU: dinfo.type=ocldevtype_gpu; break;
        case CL_DEVICE_TYPE_ACCELERATOR: dinfo.type=ocldevtype_accelerator; break;
        case CL_DEVICE_TYPE_CUSTOM: dinfo.type=ocldevtype_custom; break;
        default: PFC_ERROR(("Unknown OpenGL device type\r\n"));
      }
      if(dinfo.type!=ocldevtype_unknown)
        ++num_total_devices;

      // query general device properties
      PFC_OCL_DEV_INFO(dinfo.is_big_endian, cl_bool, CL_DEVICE_ENDIAN_LITTLE, !p);
      PFC_OCL_DEV_INFO(dinfo.max_clock_freq_mhz, cl_uint, CL_DEVICE_MAX_CLOCK_FREQUENCY, p);
      PFC_OCL_DEV_INFO(dinfo.max_compute_units, cl_uint, CL_DEVICE_MAX_COMPUTE_UNITS, p);
      unsigned max_work_item_dimensions=0;
      PFC_OCL_DEV_INFO(max_work_item_dimensions, cl_uint, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, p);
      dinfo.max_dimension_work_items.resize(max_work_item_dimensions);
      PFC_OCL_VERIFY_MSG(clGetDeviceInfo(dinfo.id, CL_DEVICE_MAX_WORK_ITEM_SIZES, max_work_item_dimensions*sizeof(size_t), dinfo.max_dimension_work_items.data(), 0), ("Device query for \"CL_DEVICE_MAX_WORK_ITEM_SIZES\" property failed.\r\n"));
      PFC_OCL_DEV_INFO(dinfo.max_work_group_size, size_t, CL_DEVICE_MAX_WORK_GROUP_SIZE, p);

      // query device extensions
      size_t ext_size=0;
      PFC_OCL_VERIFY_MSG(clGetDeviceInfo(dinfo.id, CL_DEVICE_EXTENSIONS, 0, 0, &ext_size), ("Device query for size of \"CL_DEVICE_EXTENSIONS\" property failed.\r\n"));
      dinfo.extensions.resize(ext_size);
      PFC_OCL_VERIFY_MSG(clGetDeviceInfo(dinfo.id, CL_DEVICE_EXTENSIONS, ext_size, dinfo.extensions.c_str(), 0), ("Device query for \"CL_DEVICE_EXTENSIONS\" property failed.\r\n"));

      // query device SPIR support
      if(str_find_substr(dinfo.extensions.c_str(), "cl_khr_spir"))
      {
        char spir_ver[64];
        PFC_OCL_VERIFY_MSG(clGetDeviceInfo(dinfo.id, CL_DEVICE_SPIR_VERSIONS, sizeof(spir_ver), spir_ver, 0), ("Device query for \"CL_DEVICE_SPIR_VERSIONS\" property failed.\r\n"));
        if(str_find_substr(spir_ver, "1.2"))
          dinfo.supported_spir_versions=e_ocl_spir_version(dinfo.supported_spir_versions|oclspir_1_2);
        if(str_find_substr(spir_ver, "2.0"))
          dinfo.supported_spir_versions=e_ocl_spir_version(dinfo.supported_spir_versions|oclspir_2_0);
      }
      
      // query device floating point properties
      cl_device_fp_config float_cfg=0, double_cfg=0;
      PFC_OCL_DEV_INFO(float_cfg, cl_device_fp_config, CL_DEVICE_SINGLE_FP_CONFIG, p);
      dinfo.single_fp_config=ocl_map_fp_config_enum(float_cfg);
      PFC_OCL_DEV_INFO(double_cfg, cl_device_fp_config, CL_DEVICE_DOUBLE_FP_CONFIG, p);
      dinfo.double_fp_config=ocl_map_fp_config_enum(double_cfg);

      // query device vector properties
      PFC_OCL_DEV_INFO(dinfo.preferred_vector_width_char,   cl_uint, CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR,   p);
      PFC_OCL_DEV_INFO(dinfo.preferred_vector_width_short,  cl_uint, CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT,  p);
      PFC_OCL_DEV_INFO(dinfo.preferred_vector_width_int,    cl_uint, CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT,    p);
      PFC_OCL_DEV_INFO(dinfo.preferred_vector_width_long,   cl_uint, CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG,   p);
      PFC_OCL_DEV_INFO(dinfo.preferred_vector_width_float,  cl_uint, CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT,  p);
      PFC_OCL_DEV_INFO(dinfo.preferred_vector_width_double, cl_uint, CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE, p);
      PFC_OCL_DEV_INFO(dinfo.preferred_vector_width_half,   cl_uint, CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF,   p);
      PFC_OCL_DEV_INFO(dinfo.native_vector_width_char,   cl_uint, CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR,   p);
      PFC_OCL_DEV_INFO(dinfo.native_vector_width_short,  cl_uint, CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT,  p);
      PFC_OCL_DEV_INFO(dinfo.native_vector_width_int,    cl_uint, CL_DEVICE_NATIVE_VECTOR_WIDTH_INT,    p);
      PFC_OCL_DEV_INFO(dinfo.native_vector_width_long,   cl_uint, CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG,   p);
      PFC_OCL_DEV_INFO(dinfo.native_vector_width_float,  cl_uint, CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT,  p);
      PFC_OCL_DEV_INFO(dinfo.native_vector_width_double, cl_uint, CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE, p);
      PFC_OCL_DEV_INFO(dinfo.native_vector_width_half,   cl_uint, CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF,   p);

      // query device memory properties
      PFC_OCL_DEV_INFO(dinfo.num_address_bits, cl_uint, CL_DEVICE_ADDRESS_BITS, p);
      PFC_OCL_DEV_INFO(dinfo.global_mem_size, cl_ulong, CL_DEVICE_GLOBAL_MEM_SIZE, size_t(p));
      PFC_OCL_DEV_INFO(dinfo.max_mem_alloc_size, cl_ulong, CL_DEVICE_MAX_MEM_ALLOC_SIZE, size_t(p));
      PFC_OCL_DEV_INFO(dinfo.mem_base_address_align, cl_uint, CL_DEVICE_MEM_BASE_ADDR_ALIGN, p);
      cl_device_mem_cache_type global_cache_type=CL_NONE;
      PFC_OCL_DEV_INFO(global_cache_type, cl_device_mem_cache_type, CL_DEVICE_GLOBAL_MEM_CACHE_TYPE, p);
      switch(global_cache_type)
      {
        case CL_NONE: dinfo.global_cache_type=oclcachetype_none; break;
        case CL_READ_ONLY_CACHE: dinfo.global_cache_type=oclcachetype_read_only; break;
        case CL_READ_WRITE_CACHE: dinfo.global_cache_type=oclcachetype_read_write; break;
        default: PFC_ERRORF("OpenCL: Unsupported global cache type \"%i\"\r\n", global_cache_type);
      }
      PFC_OCL_DEV_INFO(dinfo.global_cache_size, cl_ulong, CL_DEVICE_GLOBAL_MEM_CACHE_SIZE, size_t(p));
      PFC_OCL_DEV_INFO(dinfo.global_cacheline_size, cl_uint, CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE, p);
      cl_device_local_mem_type local_mem_type=CL_NONE;
      PFC_OCL_DEV_INFO(local_mem_type, cl_device_local_mem_type, CL_DEVICE_LOCAL_MEM_TYPE, p);
      switch(local_mem_type)
      {
        case CL_NONE: dinfo.local_mem_type=ocllocalmemtype_none; break;
        case CL_LOCAL: dinfo.local_mem_type=ocllocalmemtype_local; break;
        case CL_GLOBAL: dinfo.local_mem_type=ocllocalmemtype_global; break;
        default: PFC_ERRORF("OpenCL: Unsupported local memory type \"%i\"\r\n", local_mem_type);
      }
      PFC_OCL_DEV_INFO(dinfo.local_mem_size, cl_ulong, CL_DEVICE_LOCAL_MEM_SIZE, size_t(p));

      // query device constant buffer properties
      PFC_OCL_DEV_INFO(dinfo.max_constant_buffer_size, cl_ulong, CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE, size_t(p));
      PFC_OCL_DEV_INFO(dinfo.max_constant_args, cl_uint, CL_DEVICE_MAX_CONSTANT_ARGS, p);

      // query device image properties
      PFC_OCL_DEV_INFO(dinfo.is_image_support, cl_bool, CL_DEVICE_IMAGE_SUPPORT, !!p);
      PFC_OCL_DEV_INFO(dinfo.image_pitch_align, cl_uint, CL_DEVICE_IMAGE_PITCH_ALIGNMENT, p);
      PFC_OCL_DEV_INFO(dinfo.image_base_address_align, cl_uint, CL_DEVICE_IMAGE_BASE_ADDRESS_ALIGNMENT, p);
      PFC_OCL_DEV_INFO(dinfo.max_image_read_args, cl_uint, CL_DEVICE_MAX_READ_IMAGE_ARGS, p);
      PFC_OCL_DEV_INFO(dinfo.max_image_write_args, cl_uint, CL_DEVICE_MAX_WRITE_IMAGE_ARGS, p);
      PFC_OCL_DEV_INFO(dinfo.max_image_rw_args, cl_uint, CL_DEVICE_MAX_READ_WRITE_IMAGE_ARGS, p);
      PFC_OCL_DEV_INFO(dinfo.max_image_2d_width, size_t, CL_DEVICE_IMAGE2D_MAX_WIDTH, p);
      PFC_OCL_DEV_INFO(dinfo.max_image_2d_height, size_t, CL_DEVICE_IMAGE2D_MAX_HEIGHT, p);
      PFC_OCL_DEV_INFO(dinfo.max_image_3d_width, size_t, CL_DEVICE_IMAGE3D_MAX_WIDTH, p);
      PFC_OCL_DEV_INFO(dinfo.max_image_3d_height, size_t, CL_DEVICE_IMAGE3D_MAX_HEIGHT, p);
      PFC_OCL_DEV_INFO(dinfo.max_image_3d_depth, size_t, CL_DEVICE_IMAGE3D_MAX_DEPTH, p);
      PFC_OCL_DEV_INFO(dinfo.max_image_array_size, size_t, CL_DEVICE_IMAGE_MAX_ARRAY_SIZE, p);
      PFC_OCL_DEV_INFO(dinfo.max_image_buffer_size, size_t, CL_DEVICE_IMAGE_MAX_BUFFER_SIZE, p);
      PFC_OCL_DEV_INFO(dinfo.max_image_samplers, cl_uint, CL_DEVICE_MAX_SAMPLERS, p);

      // estimate device GFLOPS
      {
        switch(dinfo.type)
        {
          case ocldevtype_cpu:
          {
            bool is_hyperthreading=true;
            dinfo.max_estimated_gflops=dinfo.max_clock_freq_mhz*dinfo.max_compute_units*dinfo.native_vector_width_float*(is_hyperthreading?1:2)/1000;
          } break;

          case ocldevtype_gpu:
          {
            unsigned num_threads_per_wavefront=1;
            PFC_OCL_DEV_INFO(num_threads_per_wavefront, cl_uint, CL_DEVICE_WAVEFRONT_WIDTH_AMD, p);
            PFC_OCL_DEV_INFO(num_threads_per_wavefront, cl_uint, CL_DEVICE_WARP_SIZE_NV, p);
            dinfo.max_estimated_gflops=dinfo.max_clock_freq_mhz*dinfo.max_compute_units*num_threads_per_wavefront*2/1000;
          } break;

          default: PFC_ERROR_NOT_IMPL();
        }
        pinfo.max_estimated_gflops+=dinfo.max_estimated_gflops;
      }
      #undef PFC_OCL_DEV_INFO
      #undef PFC_OCL_DEV_INFO_STR
    }

    // sort platform devices by estimated performance
    quick_sort(pinfo.devices.data(), pinfo.devices.size(), ocl_device_info_sort_pred());
  }
  quick_sort(m_platforms.data(), m_platforms.size(), ocl_platform_info_sort_pred());

  // generate available device list sorted by estimated performance
  m_devices.reserve(num_total_devices);
  const ocl_platform_info *pinfos=m_platforms.data();
  for(usize_t pi=0; pi<num_plats; ++pi)
  {
    usize_t num_devs=pinfos[pi].devices.size();
    const ocl_device_info *dinfos=pinfos[pi].devices.data();
    for(usize_t di=0; di<num_devs; ++di)
      if(dinfos[di].type!=ocldevtype_unknown)
        m_devices.push_back(device_t(pinfos+pi, dinfos+di));
  }
  quick_sort(m_devices.data(), m_devices.size(), ocl_env_device_sort_pred());
}
//----

ocl_env::~ocl_env()
{
  FreeModule(m_module);
  #define PFC_OCL_FUNC(rtype__, fname__, fargs__, cargs__) s_fn_##fname__=0;
  #include "ocl_device.inc"
  s_active=0;
}
//----

void ocl_env::remove_devices(e_ocl_device_type dev_type_)
{
  // remove devices and empty device platforms of given type
  usize_t num_platforms=m_platforms.size();
  ocl_platform_info *pinfos=m_platforms.data();
  for(usize_t pi=0; pi<num_platforms; ++pi)
  {
    // process given platform for device removal
    ocl_platform_info &pinfo=pinfos[pi];
    usize_t num_devices=pinfo.devices.size();
    ocl_device_info *dinfos=pinfo.devices.data();
    for(usize_t di=0; di<num_devices; ++di)
      if(dinfos[di].type==dev_type_)
      {
        pinfo.max_estimated_gflops-=dinfos[di].max_estimated_gflops;
        pinfo.devices.remove_at(di--);
        --num_devices;
      }

    // check for empty device platform for removal
    if(!num_devices)
    {
      m_platforms.remove_at(pi--);
      --num_platforms;
    }
  }
}
//----------------------------------------------------------------------------


//============================================================================
// ocl_context
//============================================================================
ocl_context::ocl_context()
  :m_num_devices(0)
  ,m_context(0)
{
}
//----

ocl_context::ocl_context(cl_device_id device_id_)
  :m_num_devices(0)
  ,m_context(0)
{
  init(device_id_);
}
//----

ocl_context::ocl_context(const cl_device_id *device_ids_, unsigned num_devices_)
  :m_num_devices(0)
  ,m_context(0)
{
  init(device_ids_, num_devices_);
}
//----

ocl_context::~ocl_context()
{
  release();
}
//----

bool ocl_context::init(cl_device_id device_id_)
{
  // create context
  release();
  cl_int ret_val=0;
  m_context=ocl_env::clCreateContext(0, 1, &device_id_, 0, 0, &ret_val);
  PFC_OCL_VERIFY_MSG(ret_val, ("Device context creation failed.\r\n"));
  m_num_devices=1;
  m_device_ids[0]=device_id_;
  return create_internal_kernels();
}
//----

bool ocl_context::init(const cl_device_id *device_ids_, unsigned num_devices_)
{
  // create context
  PFC_CHECK_MSG(num_devices_<=max_devices, ("Trying to create context with too many devices (%i, max=%i).\r\n", num_devices_, max_devices));
  cl_int ret_val=0;
  m_context=ocl_env::clCreateContext(0, num_devices_, device_ids_, 0, 0, &ret_val);
  PFC_OCL_VERIFY_MSG(ret_val, ("Device context creation with %i devices failed.\r\n", num_devices_));
  m_num_devices=num_devices_;
  mem_copy(m_device_ids, device_ids_, sizeof(*m_device_ids)*num_devices_);
  return create_internal_kernels();
}
//----

void ocl_context::release()
{
  if(m_context)
  {
    ocl_env::clReleaseContext(m_context);
    m_num_devices=0;
    m_context=0;
  }
}
//----------------------------------------------------------------------------

cl_command_queue ocl_context::create_queue(cl_device_id dev_id_, e_ocl_queue_flags flags_)
{
  // create command queue
  PFC_ASSERT_PEDANTIC(m_context);
  cl_int ret_val=0;
  cl_ulong flags=flags_;
  bool is_ocl2_flags=(flags_&(oclqueueflag_device|oclqueueflag_default_device))!=0;
  cl_command_queue queue=is_ocl2_flags?ocl_env::clCreateCommandQueueWithProperties(m_context, dev_id_, &flags, &ret_val)
                                      :ocl_env::clCreateCommandQueue(m_context, dev_id_, flags, &ret_val);
  PFC_OCL_VERIFY_MSG(ret_val, ("Command queue creation failed.\r\n"));
  return queue;
}
//----

cl_mem ocl_context::create_buffer(size_t size_, void *data_, e_ocl_mem_type type_)
{
  // setup buffer flags and create the buffer
  PFC_ASSERT_PEDANTIC(m_context);
  cl_int ret_val=0;
  cl_mem_flags flags=ocl_mem_flags(type_, data_!=0);
  cl_mem mem=ocl_env::clCreateBuffer(m_context, flags, size_, data_, &ret_val);
  PFC_OCL_VERIFY_MSG(ret_val,
                     ("Buffer allocation of %i bytes failed [kernel: %s, host: %s].\r\n", size_,
                     flags&CL_MEM_READ_WRITE?"read|write":flags&CL_MEM_READ_ONLY?"read":flags&CL_MEM_WRITE_ONLY?"write":"none",
                     flags&CL_MEM_HOST_READ_ONLY?"read":flags&CL_MEM_HOST_WRITE_ONLY?"write":flags&CL_MEM_HOST_NO_ACCESS?"none":"read|write"));
  return mem;
}
//----

cl_mem ocl_context::create_image1d(unsigned width_, unsigned array_size_, e_ocl_image_format fmt_, void *data_, e_ocl_mem_type type_)
{
  // create 1D image
  PFC_ASSERT_PEDANTIC(m_context);
  cl_int ret_val=0;
  cl_mem_flags flags=ocl_mem_flags(type_, data_!=0);
  cl_image_format img_fmt=ocl_image_format(fmt_);
  cl_image_desc img_desc={cl_mem_object_type(array_size_>1?CL_MEM_OBJECT_IMAGE1D_ARRAY:CL_MEM_OBJECT_IMAGE1D), width_, 1, 1, array_size_, 0, 0, 0, 0, 0};
  cl_mem mem=ocl_env::clCreateImage(m_context, flags, &img_fmt, &img_desc, data_, &ret_val);
  PFC_OCL_VERIFY_MSG(ret_val,
                     ("1D image allocation of [%ipx]x%i:%s failed [kernel: %s, host: %s].\r\n", width_, array_size_, enum_string(fmt_),
                     flags&CL_MEM_READ_WRITE?"read|write":flags&CL_MEM_READ_ONLY?"read":flags&CL_MEM_WRITE_ONLY?"write":"none",
                     flags&CL_MEM_HOST_READ_ONLY?"read":flags&CL_MEM_HOST_WRITE_ONLY?"write":flags&CL_MEM_HOST_NO_ACCESS?"none":"read|write"));
  return mem;
}
//----

cl_mem ocl_context::create_image2d(unsigned width_, unsigned height_, unsigned array_size_, e_ocl_image_format fmt_, void *data_, e_ocl_mem_type type_)
{
  // create 2D image
  PFC_ASSERT_PEDANTIC(m_context);
  cl_int ret_val=0;
  cl_mem_flags flags=ocl_mem_flags(type_, data_!=0);
  cl_image_format img_fmt=ocl_image_format(fmt_);
  cl_image_desc img_desc={ cl_mem_object_type(array_size_>1?CL_MEM_OBJECT_IMAGE2D_ARRAY:CL_MEM_OBJECT_IMAGE2D), width_, height_, 1, array_size_, 0, 0, 0, 0, 0};
  cl_mem mem=ocl_env::clCreateImage(m_context, flags, &img_fmt, &img_desc, data_, &ret_val);
  PFC_OCL_VERIFY_MSG(ret_val,
                     ("2D image allocation of [%ix%ipx]x%i:%s failed [kernel: %s, host: %s].\r\n", width_, height_, array_size_, enum_string(fmt_),
                     flags&CL_MEM_READ_WRITE?"read|write":flags&CL_MEM_READ_ONLY?"read":flags&CL_MEM_WRITE_ONLY?"write":"none",
                     flags&CL_MEM_HOST_READ_ONLY?"read":flags&CL_MEM_HOST_WRITE_ONLY?"write":flags&CL_MEM_HOST_NO_ACCESS?"none":"read|write"));
  return mem;
}
//----

cl_mem ocl_context::create_image3d(unsigned width_, unsigned height_, unsigned depth_, e_ocl_image_format fmt_, void *data_, e_ocl_mem_type type_)
{
  // create 3D image
  PFC_ASSERT_PEDANTIC(m_context);
  cl_int ret_val=0;
  cl_mem_flags flags=ocl_mem_flags(type_, data_!=0);
  cl_image_format img_fmt=ocl_image_format(fmt_);
  cl_image_desc img_desc={CL_MEM_OBJECT_IMAGE3D, width_, height_, depth_, 1, 0, 0, 0, 0, 0};
  cl_mem mem=ocl_env::clCreateImage(m_context, flags, &img_fmt, &img_desc, data_, &ret_val);
  PFC_OCL_VERIFY_MSG(ret_val,
                     ("3D image allocation of [%ix%ix%ipx]:%s failed [kernel: %s, host: %s].\r\n", width_, height_, depth_, enum_string(fmt_),
                     flags&CL_MEM_READ_WRITE?"read|write":flags&CL_MEM_READ_ONLY?"read":flags&CL_MEM_WRITE_ONLY?"write":"none",
                     flags&CL_MEM_HOST_READ_ONLY?"read":flags&CL_MEM_HOST_WRITE_ONLY?"write":flags&CL_MEM_HOST_NO_ACCESS?"none":"read|write"));
  return mem;
}
//----------------------------------------------------------------------------

cl_program ocl_context::create_source_program(const char *src_)
{
  // create program from cl source
  PFC_ASSERT_PEDANTIC(m_context);
  cl_int ret_val=0;
  cl_program prog=ocl_env::clCreateProgramWithSource(m_context, 1, &src_, 0, &ret_val);
  PFC_OCL_VALIDATE_MSG(ret_val, ("Source program creation failed.\r\n"), return 0);
  return prog;
}
//----

cl_program ocl_context::create_source_program(const char **srcs_, unsigned num_srcs_)
{
  // create program from an array of cl sources
  PFC_ASSERT_PEDANTIC(m_context);
  cl_int ret_val=0;
  cl_program prog=ocl_env::clCreateProgramWithSource(m_context, num_srcs_, srcs_, 0, &ret_val);
  PFC_OCL_VALIDATE_MSG(ret_val, ("Source program creation failed.\r\n"), return 0);
  return prog;
}
//----

cl_program ocl_context::create_binary_program(const void *binary_, size_t bin_size_, const cl_device_id *device_ids_, unsigned num_devices_)
{
  // create program from pre-compiled binary
  PFC_ASSERT_PEDANTIC(m_context);
  if(!num_devices_)
  {
    num_devices_=m_num_devices;
    device_ids_=m_device_ids;
  }
  cl_int bin_stat=0, ret_val=0;
  cl_program prog=ocl_env::clCreateProgramWithBinary(m_context, num_devices_, device_ids_, &bin_size_, (const unsigned char**)&binary_, &bin_stat, &ret_val);
  PFC_OCL_VERIFY_MSG(ret_val, ("Program creation with precompiled binary failed.\r\n"));
  PFC_OCL_VERIFY_MSG(bin_stat, ("Precompiled binary is not compatible with devices.\r\n"));
  return prog;
}
//----

cl_program ocl_context::create_binary_program(const void *binary_, size_t bin_size_, cl_device_id device_id_)
{
  return create_binary_program(binary_, bin_size_, &device_id_, 1);
}
//----

cl_program ocl_context::create_builtin_program(const char *kernel_names_, const cl_device_id *device_ids_, unsigned num_devices_)
{
  // create built-in kernel program
  PFC_ASSERT_PEDANTIC(m_context);
  if(!num_devices_)
  {
    num_devices_=m_num_devices;
    device_ids_=m_device_ids;
  }
  cl_int ret_val=0;
  cl_program prog=ocl_env::clCreateProgramWithBuiltInKernels(m_context, num_devices_, device_ids_, kernel_names_, &ret_val);
  PFC_OCL_VALIDATE_MSG(ret_val, ("Failed to create built-in kernel program for context devices \"%s\".\r\n", kernel_names_), return 0);
  return prog;
}
//----

cl_program ocl_context::create_builtin_program(const char *kernel_names_, cl_device_id device_id_)
{
  return create_builtin_program(kernel_names_, &device_id_, 1);
}
//----

cl_program ocl_context::create_il_program(const void *il_binary_, size_t bin_size_)
{
  // create program from IL binary
  PFC_ASSERT_PEDANTIC(m_context);
  cl_int ret_val=0;
  cl_program prog=ocl_env::clCreateProgramWithIL(m_context, il_binary_, bin_size_, &ret_val);
  PFC_OCL_VERIFY_MSG(ret_val, ("Failed to create program with IL binary.\r\n"));
  return prog;
}
//----

bool ocl_context::build_program(cl_program prog_, const cl_device_id *devices_, unsigned num_devices_, const char *options_, heap_str *build_log_, e_ocl_compiler_log_level log_level_)
{
  // build program
  bool build_succeeded=ocl_env::clBuildProgram(prog_, num_devices_, devices_, options_, 0, 0)==CL_SUCCESS;
  if(log_level_==oclcompilerloglevel_all || (log_level_==oclcompilerloglevel_errors && !build_succeeded))
  {
    char build_log[2048];
    build_log[0]=0;
    cl_device_id prog_dev_id;
    PFC_OCL_VERIFY_MSG(ocl_env::clGetProgramInfo(prog_, CL_PROGRAM_DEVICES, sizeof(cl_device_id), &prog_dev_id, 0),
                       ("Querying context device failed.\r\n"));
    ocl_env::clGetProgramBuildInfo(prog_, prog_dev_id, CL_PROGRAM_BUILD_LOG, sizeof(build_log), build_log, 0);
    if(build_log_)
      *build_log_=build_log;
    else
    {
      if(build_succeeded)
        log(build_log);
      else
      {
        error("OpenCL: Kernel compilation failed:\r\n");
        error(build_log);
      }
    }
  }
  return build_succeeded;
}
//----

bool ocl_context::build_program(cl_program prog_, cl_device_id device_, const char *options_, heap_str *build_log_, e_ocl_compiler_log_level log_level_)
{
  return build_program(prog_, &device_, 1, options_, build_log_, log_level_);
}
//----

cl_program ocl_context::compile_program(const char *src_, const cl_device_id *devices_, unsigned num_devices_, heap_str *build_log_, e_ocl_compiler_log_level log_level_)
{
  // create program
  PFC_ASSERT_PEDANTIC(m_context);
  cl_int ret_val=0;
  cl_program prog=ocl_env::clCreateProgramWithSource(m_context, 1, &src_, 0, &ret_val);
  PFC_OCL_VALIDATE_MSG(ret_val, ("Program creation failed.\r\n"), return 0);

  // build program
  bool build_succeeded=ocl_env::clCompileProgram(prog, num_devices_, devices_, 0, 0, 0, 0, 0, 0)==CL_SUCCESS;
  if(log_level_==oclcompilerloglevel_all || (log_level_==oclcompilerloglevel_errors && !build_succeeded))
  {
    char build_log[2048];
    build_log[0]=0;
    cl_device_id prog_dev_id;
    PFC_OCL_VERIFY_MSG(ocl_env::clGetProgramInfo(prog, CL_PROGRAM_DEVICES, sizeof(cl_device_id), &prog_dev_id, 0),
                       ("Querying context device failed.\r\n"));
    ocl_env::clGetProgramBuildInfo(prog, prog_dev_id, CL_PROGRAM_BUILD_LOG, sizeof(build_log), build_log, 0);
    if(build_log_)
      *build_log_=build_log;
    else
    {
      if(build_succeeded)
        log(build_log);
      else
      {
        error("OpenCL: Kernel compilation failed:\r\n");
        error(build_log);
      }
    }
  }
  if(!build_succeeded)
  {
    ocl_env::clReleaseProgram(prog);
    return 0;
  }
  return prog;
}
//----

cl_program ocl_context::compile_program(const char *src_, cl_device_id device_, heap_str *build_log_, e_ocl_compiler_log_level log_level_)
{
  return compile_program(src_, &device_, 1, build_log_, log_level_);
}
//----

cl_program ocl_context::link_program(const cl_program *programs_, unsigned num_programs_, const cl_device_id *devices_, unsigned num_devices_)
{
  // link programs
  PFC_ASSERT_PEDANTIC(m_context);
  cl_int ret_val=0;
  cl_program prog=ocl_env::clLinkProgram(m_context, 0, 0, 0, num_programs_, programs_, 0, 0, &ret_val);
  PFC_OCL_VERIFY_MSG(ret_val, ("Linking program failed.\r\n"));
  return prog;
}
//----

cl_program ocl_context::link_program(const cl_program *programs_, unsigned num_programs_, cl_device_id device_)
{
  return link_program(programs_, num_programs_, &device_, 1);
}
//----

cl_program ocl_context::link_program(cl_program prog_, const cl_device_id *devices_, unsigned num_devices_)
{
  return link_program(&prog_, 1, devices_, num_devices_);
}
//----

cl_program ocl_context::link_program(cl_program prog_, cl_device_id device_)
{
  return link_program(&prog_, 1, &device_, 1);
}
//----------------------------------------------------------------------------

bool ocl_context::create_internal_kernels()
{
  // internal OpenCL kernels
  static const char *s_prog_src=R"(__kernel void clear_buffer(__global uint *buf_, uint num_uints_) {uint idx=get_global_id(0); if(idx<num_uints_) buf_[idx]=0;})";

  // create program
  cl_program prog=create_source_program(s_prog_src);
  if(!prog || !build_program(prog))
    return false;
  m_program.init(prog);

  // create kernels
  m_kernel_clear_buffer.init(m_program.create_kernel("clear_buffer"));
  if(!m_kernel_clear_buffer.kernel())
    return false;
  return true;
}
//----------------------------------------------------------------------------


//============================================================================
// ocl_command_queue
//============================================================================
ocl_command_queue::ocl_command_queue()
  :m_queue(0)
  ,m_context(0)
  ,m_device(0)
{
}
//----

ocl_command_queue::ocl_command_queue(cl_command_queue queue_, ocl_context &context_)
  :m_queue(0)
  ,m_context(0)
  ,m_device(0)
{
  init(queue_, context_);
}
//----

ocl_command_queue::~ocl_command_queue()
{
  release();
}
//----

void ocl_command_queue::init(cl_command_queue queue_, ocl_context &context_)
{
  release();
  m_queue=queue_;
  m_context=&context_;
  PFC_OCL_VERIFY_MSG(ocl_env::clGetCommandQueueInfo(queue_, CL_QUEUE_DEVICE, sizeof(m_device), &m_device, 0), ("Unable to get device for a command queue.\r\n"));
}
//----

void ocl_command_queue::release()
{
  if(m_queue)
  {
    ocl_env::clReleaseCommandQueue(m_queue);
    m_queue=0;
    m_context=0;
    m_device=0;
  }
}
//----------------------------------------------------------------------------

void ocl_command_queue::exec_1d(const ocl_kernel &kernel_, size_t group_size_, size_t num_groups_, size_t offset_, const cl_event *wait_events_, unsigned num_wait_events_, cl_event *event_)
{
  PFC_ASSERT_PEDANTIC(m_queue);
  size_t work_size=group_size_*num_groups_;
  PFC_OCL_VERIFY_MSG(ocl_env::clEnqueueNDRangeKernel(m_queue, kernel_.m_kernel, 1, &offset_, &work_size, &group_size_, num_wait_events_, wait_events_, event_),
                     ("1D kernel execution failed (group size: %i, # groups: %i, offset: %i).\r\n", group_size_, num_groups_, offset_));
}
//----

void ocl_command_queue::exec_2d(const ocl_kernel &kernel_, const ocl_svec2 &group_size_, const ocl_svec2 &num_groups_, const ocl_svec2 &offset_, const cl_event *wait_events_, unsigned num_wait_events_, cl_event *event_)
{
  PFC_ASSERT_PEDANTIC(m_queue);
  ocl_svec2 work_size(group_size_.x*num_groups_.x, group_size_.y*num_groups_.y);
  PFC_OCL_VERIFY_MSG(ocl_env::clEnqueueNDRangeKernel(m_queue, kernel_.m_kernel, 2, (const size_t*)&offset_, (const size_t*)&work_size, (const size_t*)&group_size_, num_wait_events_, wait_events_, event_),
                     ("2D kernel execution failed (group size: [%i, %i], # groups: [%i, %i], offset: [%i, %i]).\r\n", group_size_.x, group_size_.y, num_groups_.x, num_groups_.y, offset_.x, offset_.y));
}
//----

void ocl_command_queue::exec_3d(const ocl_kernel &kernel_, const ocl_svec3 &group_size_, const ocl_svec3 &num_groups_, const ocl_svec3 &offset_, const cl_event *wait_events_, unsigned num_wait_events_, cl_event *event_)
{
  PFC_ASSERT_PEDANTIC(m_queue);
  ocl_svec3 work_size(group_size_.x*num_groups_.x, group_size_.y*num_groups_.y, group_size_.z*num_groups_.z);
  PFC_OCL_VERIFY_MSG(ocl_env::clEnqueueNDRangeKernel(m_queue, kernel_.m_kernel, 3, (const size_t*)&offset_, (const size_t*)&work_size, (const size_t*)&group_size_, num_wait_events_, wait_events_, event_),
                     ("3D kernel execution failed (group size: [%i, %i, %i], # groups: [%i, %i, %i], offset: [%i, %i, %i]).\r\n", group_size_.x, group_size_.y, group_size_.z, num_groups_.x, num_groups_.y, num_groups_.z, offset_.x, offset_.y, offset_.z));
}
//----

void ocl_command_queue::exec(const ocl_kernel &kernel_, unsigned work_dim_, const size_t *group_size_, const size_t *num_groups_, const size_t *offset_, const cl_event *wait_events_, unsigned num_wait_events_, cl_event *event_)
{
  PFC_ASSERT_PEDANTIC(m_queue);
  PFC_ASSERT_PEDANTIC(group_size_ && num_groups_);
  size_t *work_size=(size_t*)PFC_STACK_MALLOC(sizeof(size_t)*work_dim_);
  for(unsigned i=0; i<work_dim_; ++i)
    work_size[i]=group_size_[i]*num_groups_[i];
  PFC_OCL_VERIFY_MSG(ocl_env::clEnqueueNDRangeKernel(m_queue, kernel_.m_kernel, work_dim_, offset_, work_size, group_size_, num_wait_events_, wait_events_, event_),
                     ("%iD kernel execution failed.\r\n", work_dim_));
}
//----------------------------------------------------------------------------

void ocl_command_queue::wait_all()
{
  PFC_ASSERT_PEDANTIC(m_queue);
  ocl_env::clFinish(m_queue);
}
//----------------------------------------------------------------------------

void ocl_command_queue::read_buffer(cl_mem buffer_, void *data_, size_t size_, size_t offset_, bool is_blocking_, const cl_event *wait_events_, unsigned num_wait_events_, cl_event *event_)
{
  PFC_ASSERT_PEDANTIC(m_queue);
  PFC_OCL_VERIFY_MSG(ocl_env::clEnqueueReadBuffer(m_queue, buffer_, is_blocking_?CL_TRUE:CL_FALSE, offset_, size_, data_, num_wait_events_, wait_events_, event_),
                     ("Reading from buffer failed (offset: %i, size: %i).\r\n", offset_, size_));
}
//----

void ocl_command_queue::read_image_1d(cl_mem image_, void *data_, size_t origin_, const size_t size_, size_t start_slice_, size_t num_slices_, bool is_blocking_, const cl_event *wait_events_, unsigned num_wait_events_, cl_event *event_)
{
  PFC_ASSERT_PEDANTIC(m_queue);
  ocl_svec2 origin(origin_, start_slice_);
  ocl_svec2 size(size_, num_slices_);
  PFC_OCL_VERIFY_MSG(ocl_env::clEnqueueReadImage(m_queue, image_, is_blocking_, (const size_t*)&origin, (const size_t*)&size, 0, 0, data_, num_wait_events_, wait_events_, event_),
                     ("Reading 1D image failed (origin: %i, size: %i, slices: %i..%i).\r\n", origin_, size_, start_slice_, start_slice_+num_slices_-1));
}
//----

void ocl_command_queue::read_image_2d(cl_mem image_, void *data_, const ocl_svec2 &origin_, const ocl_svec2 &size_, size_t row_pitch_, size_t start_slice_, size_t num_slices_, bool is_blocking_, const cl_event *wait_events_, unsigned num_wait_events_, cl_event *event_)
{
  PFC_ASSERT_PEDANTIC(m_queue);
  ocl_svec3 origin(origin_.x, origin_.y, start_slice_);
  ocl_svec3 size(size_.x, size_.y, num_slices_);
  PFC_OCL_VERIFY_MSG(ocl_env::clEnqueueReadImage(m_queue, image_, is_blocking_, (const size_t*)&origin, (const size_t*)&size, row_pitch_, 0, data_, num_wait_events_, wait_events_, event_),
                     ("Reading 2D image failed (origin: [%i, %i], size: [%i, %i], slices: %i..%i).\r\n", origin_.x, origin_.y, size_.x, size_.y, start_slice_, start_slice_+num_slices_-1));
}
//----

void ocl_command_queue::read_image_3d(cl_mem image_, void *data_, const ocl_svec3 &origin_, const ocl_svec3 &size_, size_t row_pitch_, size_t slice_pitch_, bool is_blocking_, const cl_event *wait_events_, unsigned num_wait_events_, cl_event *event_)
{
  PFC_ASSERT_PEDANTIC(m_queue);
  PFC_OCL_VERIFY_MSG(ocl_env::clEnqueueReadImage(m_queue, image_, is_blocking_, (const size_t*)&origin_, (const size_t*)&size_, row_pitch_, slice_pitch_, data_, num_wait_events_, wait_events_, event_),
                     ("Reading 3D image failed (origin: [%i, %i, %i], size: [%i, %i, %i]).\r\n", origin_.x, origin_.y, origin_.z, size_.x, size_.y, size_.z));
}
//----

void ocl_command_queue::write_buffer(cl_mem buffer_, const void *data_, size_t size_, size_t offset_, bool is_blocking_, const cl_event *wait_events_, unsigned num_wait_events_, cl_event *event_)
{
  PFC_ASSERT_PEDANTIC(m_queue);
  PFC_OCL_VERIFY_MSG(ocl_env::clEnqueueWriteBuffer(m_queue, buffer_, is_blocking_?CL_TRUE:CL_FALSE, offset_, size_, data_, num_wait_events_, wait_events_, event_),
                     ("Writing to the buffer failed (size: %i, offset: %i, blocking: %i).\r\n", size_, offset_, is_blocking_?1:0));
}
//----

void ocl_command_queue::fill_buffer(cl_mem buffer_, size_t size_, const void *pattern_, size_t pattern_size_, size_t offset_, const cl_event *wait_events_, unsigned num_wait_events_, cl_event *event_)
{
  PFC_ASSERT_PEDANTIC(m_queue);
  PFC_OCL_VERIFY_MSG(ocl_env::clEnqueueFillBuffer(m_queue, buffer_, pattern_, pattern_size_, offset_, size_, num_wait_events_, wait_events_, event_),
                     ("Filling the buffer failed (size: %i, offset: %i, pattern_size: %i).\r\n", size_, offset_, pattern_size_));
}
//----

void ocl_command_queue::clear_buffer(cl_mem buffer_, size_t size_, const cl_event *wait_events_, unsigned num_wait_events_, cl_event *event_)
{
  PFC_ASSERT_PEDANTIC(m_queue);
  PFC_ASSERT_MSG(!(size_&3), ("Buffer size must be multiple of 4 (size: %i).\r\n", size_));
  size_t group_size=64;
  size_t work_size=(size_/4+group_size-1)&(0-group_size);
  m_context->m_kernel_clear_buffer.set_arg(0, buffer_);
  m_context->m_kernel_clear_buffer.set_arg(1, uint32_t(size_/4));
  PFC_OCL_VERIFY_MSG(ocl_env::clEnqueueNDRangeKernel(m_queue, m_context->m_kernel_clear_buffer.kernel(), 1, 0, &work_size, &group_size, num_wait_events_, wait_events_, event_),
                     ("Buffer clear failed (size: %i).\r\n", size_));
}
//----

void ocl_command_queue::write_image_1d(cl_mem image_, const void *data_, const size_t size_, size_t origin_, size_t start_slice_, size_t num_slices_, bool is_blocking_, const cl_event *wait_events_, unsigned num_wait_events_, cl_event *event_)
{
  PFC_ASSERT_PEDANTIC(m_queue);
  ocl_svec2 origin(origin_, start_slice_);
  ocl_svec2 size(size_, num_slices_);
  PFC_OCL_VERIFY_MSG(ocl_env::clEnqueueWriteImage(m_queue, image_, is_blocking_, (const size_t*)&origin, (const size_t*)&size, 0, 0, data_, num_wait_events_, wait_events_, event_),
                     ("Writing 1D image failed (origin: %i, size: %i, slices: %i..%i).\r\n", origin_, size_, start_slice_, start_slice_+num_slices_-1));
}
//----

void ocl_command_queue::write_image_2d(cl_mem image_, const void *data_, const ocl_svec2 &size_, const ocl_svec2 &origin_, size_t row_pitch_, size_t start_slice_, size_t num_slices_, size_t slice_pitch_, bool is_blocking_, const cl_event *wait_events_, unsigned num_wait_events_, cl_event *event_)
{
  PFC_ASSERT_PEDANTIC(m_queue);
  ocl_svec3 origin(origin_.x, origin_.y, start_slice_);
  ocl_svec3 size(size_.x, size_.y, num_slices_);
  PFC_OCL_VERIFY_MSG(ocl_env::clEnqueueWriteImage(m_queue, image_, is_blocking_, (const size_t*)&origin, (const size_t*)&size, row_pitch_, slice_pitch_, data_, num_wait_events_, wait_events_, event_),
                     ("Writing 2D image failed (origin: [%i, %i], size: [%i, %i], slices: %i..%i).\r\n", origin_.x, origin_.y, size_.x, size_.y, start_slice_, start_slice_+num_slices_-1));
}
//----

void ocl_command_queue::write_image_3d(cl_mem image_, const void *data_, const ocl_svec3 &size_, const ocl_svec3 &origin_, size_t row_pitch_, size_t slice_pitch_, bool is_blocking_, const cl_event *wait_events_, unsigned num_wait_events_, cl_event *event_)
{
  PFC_ASSERT_PEDANTIC(m_queue);
  PFC_OCL_VERIFY_MSG(ocl_env::clEnqueueWriteImage(m_queue, image_, is_blocking_, (const size_t*)&origin_, (const size_t*)&size_, row_pitch_, slice_pitch_, data_, num_wait_events_, wait_events_, event_),
                     ("Writing 3D image failed (origin: [%i, %i, %i], size: [%i, %i, %i]).\r\n", origin_.x, origin_.y, origin_.z, size_.x, size_.y, size_.z));
}
//----------------------------------------------------------------------------

ocl_svec3 ocl_command_queue::work_group_size_compiled(const ocl_kernel &kernel_)
{
  PFC_ASSERT_PEDANTIC(m_queue);
  ocl_svec3 wg_size(0, 0, 0);
  PFC_OCL_VERIFY_MSG(ocl_env::clGetKernelWorkGroupInfo(kernel_.m_kernel, m_device, CL_KERNEL_COMPILE_WORK_GROUP_SIZE, 3*sizeof(size_t), &wg_size, 0),
                     ("Unable to get compiled work group size for the kernel.\r\n"));
  return wg_size;
}
//----

ocl_svec3 ocl_command_queue::work_group_size_preferred(const ocl_kernel &kernel_)
{
  PFC_ASSERT_PEDANTIC(m_queue);
  ocl_svec3 wg_size(0, 0, 0);
  PFC_OCL_VERIFY_MSG(ocl_env::clGetKernelWorkGroupInfo(kernel_.m_kernel, m_device, CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE, 3*sizeof(size_t), &wg_size, 0),
                     ("Unable to get preferred work group size for the kernel.\r\n"));
  return wg_size;
}
//----------------------------------------------------------------------------


//============================================================================
// ocl_info_line
//============================================================================
heap_str pfc::ocl_info_line(const ocl_platform_info &pinfo_)
{
  // construct info line about the platform
  heap_str s;
  s.format("%s [%s profile, ~%i GFLOPS]", pinfo_.name.c_str(), enum_string(pinfo_.profile), pinfo_.max_estimated_gflops);
  return s;
}
//----

heap_str pfc::ocl_info_line(const ocl_device_info &dinfo_)
{
  // construct info line about the device
  heap_str s;
  s.format("%s [%s: %i MHz, %i CU's, ~%i GFLOPS]", dinfo_.name.c_str(), enum_display_string(dinfo_.type), dinfo_.max_clock_freq_mhz, dinfo_.max_compute_units, dinfo_.max_estimated_gflops);
  return s;
}
//----------------------------------------------------------------------------


//============================================================================
// ocl_device_info_str
//============================================================================
heap_str pfc::ocl_device_info_str(const ocl_device_info &dinfo_, const char *line_prefix_)
{
  // log basic device info
  heap_str s;
  const char *prefix=line_prefix_?line_prefix_:"";
  s.push_back_format("%s%s\r\n", prefix, ocl_info_line(dinfo_).c_str());
  s.push_back_format("%sVendor: %s\r\n", prefix, dinfo_.vendor_name.c_str());
  s.push_back_format("%sVersion: %s (driver %s)\r\n", prefix, dinfo_.version.c_str(), dinfo_.driver_version.c_str());
  s.push_back_format("%sLocal Memory: %i KB\r\n", prefix, dinfo_.local_mem_size/1024);
  s.push_back_format("%sGlobal Memory: %i MB (%iKB D$, %iB $line)\r\n", prefix, dinfo_.global_mem_size/(1024*1024), dinfo_.global_cache_size/1024, dinfo_.global_cacheline_size);
  s.push_back_format("%sTexturing: ", prefix);
  if(dinfo_.is_image_support)
  {
    s.push_back_format("2D: %ix%ik, 3D: %ix%ix%ik, Arr: %i, Samp: %i, R: %i, W: %i, RW: %i\r\n",
                        dinfo_.max_image_2d_width/1024, dinfo_.max_image_2d_height/1024,
                        dinfo_.max_image_3d_width/1024, dinfo_.max_image_3d_height/1024, dinfo_.max_image_3d_depth/1024,
                        dinfo_.max_image_array_size, dinfo_.max_image_samplers,
                        dinfo_.max_image_read_args, dinfo_.max_image_write_args, dinfo_.max_image_rw_args);
  }
  else
    s+="<Not Supported>\r\n";
  return s;
}
//----------------------------------------------------------------------------


//============================================================================
// ocl_log_platform_info
//============================================================================
void pfc::ocl_log_platform_info(const ocl_platform_info &pinfo_, const char *dev_prefix_, const char *info_prefix_)
{
  // get device info strings
  enum {max_devs=32};
  heap_str dev_info_strs[max_devs];
  const char *info_prefix=info_prefix_?info_prefix_:"";
  unsigned num_devs=min(unsigned(pinfo_.devices.size()), unsigned(max_devs));
  for(unsigned di=0; di<num_devs; ++di)
    dev_info_strs[di]=ocl_device_info_str(pinfo_.devices[di], info_prefix);

  // log devices
  unsigned range_start_idx=0;
  const char *dev_prefix=dev_prefix_?dev_prefix_:"";
  for(unsigned di=0; di<num_devs; ++di)
  {
    if(di+1==num_devs || dev_info_strs[di]!=dev_info_strs[di+1])
    {
      if(di-range_start_idx>0)
        logf("%sDevices #%02i-#%02i:\r\n", dev_prefix, range_start_idx, di);
      else
        logf("%sDevice #%02i:\r\n", dev_prefix, di);
      log(dev_info_strs[di].c_str());
      range_start_idx=di+1;
    }
  }
}
//----------------------------------------------------------------------------


//============================================================================
// ocl_error_msg
//============================================================================
const char *pfc::ocl_error_msg(int error_code_)
{
  switch(error_code_)
  {
    #define OCL_ERROR_CASE(code__) case code__: return #code__;
    OCL_ERROR_CASE(CL_DEVICE_NOT_FOUND)
    OCL_ERROR_CASE(CL_DEVICE_NOT_AVAILABLE)
    OCL_ERROR_CASE(CL_COMPILER_NOT_AVAILABLE)
    OCL_ERROR_CASE(CL_MEM_OBJECT_ALLOCATION_FAILURE)
    OCL_ERROR_CASE(CL_OUT_OF_RESOURCES)
    OCL_ERROR_CASE(CL_OUT_OF_HOST_MEMORY)
    OCL_ERROR_CASE(CL_PROFILING_INFO_NOT_AVAILABLE)
    OCL_ERROR_CASE(CL_MEM_COPY_OVERLAP)
    OCL_ERROR_CASE(CL_IMAGE_FORMAT_MISMATCH)
    OCL_ERROR_CASE(CL_IMAGE_FORMAT_NOT_SUPPORTED)
    OCL_ERROR_CASE(CL_BUILD_PROGRAM_FAILURE)
    OCL_ERROR_CASE(CL_MAP_FAILURE)
    OCL_ERROR_CASE(CL_MISALIGNED_SUB_BUFFER_OFFSET)
    OCL_ERROR_CASE(CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST)
    OCL_ERROR_CASE(CL_COMPILE_PROGRAM_FAILURE)
    OCL_ERROR_CASE(CL_LINKER_NOT_AVAILABLE)
    OCL_ERROR_CASE(CL_LINK_PROGRAM_FAILURE)
    OCL_ERROR_CASE(CL_DEVICE_PARTITION_FAILED)
    OCL_ERROR_CASE(CL_KERNEL_ARG_INFO_NOT_AVAILABLE)
    OCL_ERROR_CASE(CL_INVALID_VALUE)
    OCL_ERROR_CASE(CL_INVALID_DEVICE_TYPE)
    OCL_ERROR_CASE(CL_INVALID_PLATFORM)
    OCL_ERROR_CASE(CL_INVALID_DEVICE)
    OCL_ERROR_CASE(CL_INVALID_CONTEXT)
    OCL_ERROR_CASE(CL_INVALID_QUEUE_PROPERTIES)
    OCL_ERROR_CASE(CL_INVALID_COMMAND_QUEUE)
    OCL_ERROR_CASE(CL_INVALID_HOST_PTR)
    OCL_ERROR_CASE(CL_INVALID_MEM_OBJECT)
    OCL_ERROR_CASE(CL_INVALID_IMAGE_FORMAT_DESCRIPTOR)
    OCL_ERROR_CASE(CL_INVALID_IMAGE_SIZE)
    OCL_ERROR_CASE(CL_INVALID_SAMPLER)
    OCL_ERROR_CASE(CL_INVALID_BINARY)
    OCL_ERROR_CASE(CL_INVALID_BUILD_OPTIONS)
    OCL_ERROR_CASE(CL_INVALID_PROGRAM)
    OCL_ERROR_CASE(CL_INVALID_PROGRAM_EXECUTABLE)
    OCL_ERROR_CASE(CL_INVALID_KERNEL_NAME)
    OCL_ERROR_CASE(CL_INVALID_KERNEL_DEFINITION)
    OCL_ERROR_CASE(CL_INVALID_KERNEL)
    OCL_ERROR_CASE(CL_INVALID_ARG_INDEX)
    OCL_ERROR_CASE(CL_INVALID_ARG_VALUE)
    OCL_ERROR_CASE(CL_INVALID_ARG_SIZE)
    OCL_ERROR_CASE(CL_INVALID_KERNEL_ARGS)
    OCL_ERROR_CASE(CL_INVALID_WORK_DIMENSION)
    OCL_ERROR_CASE(CL_INVALID_WORK_GROUP_SIZE)
    OCL_ERROR_CASE(CL_INVALID_WORK_ITEM_SIZE)
    OCL_ERROR_CASE(CL_INVALID_GLOBAL_OFFSET)
    OCL_ERROR_CASE(CL_INVALID_EVENT_WAIT_LIST)
    OCL_ERROR_CASE(CL_INVALID_EVENT)
    OCL_ERROR_CASE(CL_INVALID_OPERATION)
    OCL_ERROR_CASE(CL_INVALID_GL_OBJECT)
    OCL_ERROR_CASE(CL_INVALID_BUFFER_SIZE)
    OCL_ERROR_CASE(CL_INVALID_MIP_LEVEL)
    OCL_ERROR_CASE(CL_INVALID_GLOBAL_WORK_SIZE)
    OCL_ERROR_CASE(CL_INVALID_PROPERTY)
    OCL_ERROR_CASE(CL_INVALID_IMAGE_DESCRIPTOR)
    OCL_ERROR_CASE(CL_INVALID_COMPILER_OPTIONS)
    OCL_ERROR_CASE(CL_INVALID_LINKER_OPTIONS)
    OCL_ERROR_CASE(CL_INVALID_DEVICE_PARTITION_COUNT)
    OCL_ERROR_CASE(CL_INVALID_PIPE_SIZE)
    OCL_ERROR_CASE(CL_INVALID_DEVICE_QUEUE)
    #undef OCL_ERROR_CASE
  }
  return 0;
}
//----------------------------------------------------------------------------
