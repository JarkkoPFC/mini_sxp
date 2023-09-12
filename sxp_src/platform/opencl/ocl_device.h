//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_OCL_DEVICE_H
#define PFC_OCL_DEVICE_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "sxp_src/core/config.h"
#include "sxp_src/core/containers.h"
#include "sxp_src/core/str.h"
#define CL_TARGET_OPENCL_VERSION 300 // v3.0
#include "sxp_extlibs/opencl/cl/opencl.h"
namespace pfc
{

// new
struct ocl_svec2;
struct ocl_svec3;
struct ocl_device_info;
struct ocl_platform_info;
struct ocl_kernel_program_dependency;
class ocl_env;
class ocl_context;
class ocl_command_queue;
class ocl_program;
class ocl_kernel;
class ocl_memory;
class ocl_event;
// info functions
heap_str ocl_info_line(const ocl_platform_info&);
heap_str ocl_info_line(const ocl_device_info&);
heap_str ocl_device_info_str(const ocl_device_info&, const char *line_prefix_=0);
void ocl_log_platform_info(const ocl_platform_info&, const char *dev_prefix_=0, const char *info_prefix_=0);
const char *ocl_error_msg(int error_code_);
#define PFC_OCL_VERIFY_MSG(expr__, msg__) {if(cl_int err_code=expr__) {errorf("OpenCL: "); errorf msg__; errorf("OpenCL error code: %s\r\n", ocl_error_msg(err_code)); PFC_ABORT();}}
#define PFC_OCL_VALIDATE_MSG(expr__, msg__, error_expr__) {if(cl_int err_code=expr__) {errorf("OpenCL: "); errorf msg__; errorf("OpenCL error code: %s\r\n", ocl_error_msg(err_code)); error_expr__;}}
//----------------------------------------------------------------------------


//============================================================================
// e_ocl_platform_profile
//============================================================================
enum e_ocl_platform_profile
{
  oclplatprof_unknown,
  oclplatprof_full,
  oclplatprof_embedded,
};
PFC_ENUM(e_ocl_platform_profile);
//----------------------------------------------------------------------------


//============================================================================
// e_ocl_device_type
//============================================================================
enum e_ocl_device_type
{
  ocldevtype_unknown,
  ocldevtype_cpu,
  ocldevtype_gpu,
  ocldevtype_accelerator,
  ocldevtype_custom,
};
PFC_ENUM(e_ocl_device_type);
//----------------------------------------------------------------------------


//============================================================================
// e_ocl_float_config
//============================================================================
enum e_ocl_float_config
{
  oclfloatcfg_none             =0x00,
  oclfloatcfg_denorm           =0x01,
  oclfloatcfg_inf_nan          =0x02,
  oclfloatcfg_round_to_nearest =0x04,
  oclfloatcfg_round_to_zero    =0x08,
  oclfloatcfg_round_to_inf     =0x10,
  oclfloatcfg_fma              =0x20,
  oclfloatcfg_correct_div_sqrt =0x40,
  oclfloatcfg_soft_float       =0x80,
};
PFC_ENUM(e_ocl_float_config);
//----------------------------------------------------------------------------


//============================================================================
// e_ocl_data_type
//============================================================================
enum e_ocl_data_type
{
  // integral types
  ocldatatype_bool,
  ocldatatype_char,   ocldatatype_char2,   ocldatatype_char3,   ocldatatype_char4,   ocldatatype_char8,   ocldatatype_char16,
  ocldatatype_uchar,  ocldatatype_uchar2,  ocldatatype_uchar3,  ocldatatype_uchar4,  ocldatatype_uchar8,  ocldatatype_uchar16,
  ocldatatype_short,  ocldatatype_short2,  ocldatatype_short3,  ocldatatype_short4,  ocldatatype_short8,  ocldatatype_short16,
  ocldatatype_ushort, ocldatatype_ushort2, ocldatatype_ushort3, ocldatatype_ushort4, ocldatatype_ushort8, ocldatatype_ushort16,
  ocldatatype_int,    ocldatatype_int2,    ocldatatype_int3,    ocldatatype_int4,    ocldatatype_int8,    ocldatatype_int16,
  ocldatatype_uint,   ocldatatype_uint2,   ocldatatype_uint3,   ocldatatype_uint4,   ocldatatype_uint8,   ocldatatype_uint16,
  ocldatatype_long,   ocldatatype_long2,   ocldatatype_long3,   ocldatatype_long4,   ocldatatype_long8,   ocldatatype_long16,
  ocldatatype_ulong,  ocldatatype_ulong2,  ocldatatype_ulong3,  ocldatatype_ulong4,  ocldatatype_ulong8,  ocldatatype_ulong16,
  // float types
  ocldatatype_half,   ocldatatype_half2,   ocldatatype_half3,   ocldatatype_half4,   ocldatatype_half8,   ocldatatype_half16,
  ocldatatype_float,  ocldatatype_float2,  ocldatatype_float3,  ocldatatype_float4,  ocldatatype_float8,  ocldatatype_float16,
  ocldatatype_double, ocldatatype_double2, ocldatatype_double3, ocldatatype_double4, ocldatatype_double8, ocldatatype_double16,
};
PFC_ENUM(e_ocl_data_type);
//----------------------------------------------------------------------------


//============================================================================
// e_ocl_cache_type
//============================================================================
enum e_ocl_cache_type
{
  oclcachetype_none,
  oclcachetype_read_only,
  oclcachetype_read_write,
};
PFC_ENUM(e_ocl_cache_type);
//----------------------------------------------------------------------------


//============================================================================
// e_ocl_local_mem_type
//============================================================================
enum e_ocl_local_mem_type
{
  ocllocalmemtype_none,
  ocllocalmemtype_local,
  ocllocalmemtype_global,
};
PFC_ENUM(e_ocl_local_mem_type);
//----------------------------------------------------------------------------


//============================================================================
// e_ocl_mem_type
//============================================================================
enum e_ocl_mem_type
{
  oclmemtype_kernel_read   =0x01, // kernel-readable memory
  oclmemtype_kernel_write  =0x02, // kernel-writable memory
  oclmemtype_host_read     =0x04, // host-readable memory
  oclmemtype_host_write    =0x08, // host-writable memory
  oclmemtype_alloc_device  =0x10, // allocate from device memory
  oclmemtype_alloc_host    =0x20, // allocate from host memory
};
PFC_ENUM(e_ocl_mem_type);
//----------------------------------------------------------------------------


//============================================================================
// e_ocl_image_format
//============================================================================
enum e_ocl_image_format
{
  // minimum spec formats
  // R-channel
  oclimgfmt_r8u,
  oclimgfmt_r8s,
  oclimgfmt_r8un,
  oclimgfmt_r8sn,
  oclimgfmt_r16u,
  oclimgfmt_r16s,
  oclimgfmt_r16un,
  oclimgfmt_r16sn,
  oclimgfmt_r16f,
  oclimgfmt_r32u,
  oclimgfmt_r32s,
  oclimgfmt_r32f,
  // Depth-channel
  oclimgfmt_d16un,
  oclimgfmt_d32f,
  // RG-channels
  oclimgfmt_r8g8u,
  oclimgfmt_r8g8s,
  oclimgfmt_r8g8un,
  oclimgfmt_r8g8sn,
  oclimgfmt_r16g16u,
  oclimgfmt_r16g16s,
  oclimgfmt_r16g16un,
  oclimgfmt_r16g16sn,
  oclimgfmt_r16g16f,
  oclimgfmt_r32g32u,
  oclimgfmt_r32g32s,
  oclimgfmt_r32g32f,
  // RGBA-channels
  oclimgfmt_r8g8b8a8u,
  oclimgfmt_r8g8b8a8s,
  oclimgfmt_r8g8b8a8un,
  oclimgfmt_r8g8b8a8sn,
  oclimgfmt_r16g16b16a16u,
  oclimgfmt_r16g16b16a16s,
  oclimgfmt_r16g16b16a16un,
  oclimgfmt_r16g16b16a16sn,
  oclimgfmt_r16g16b16a16f,
  oclimgfmt_r32g32b32a32u,
  oclimgfmt_r32g32b32a32s,
  oclimgfmt_r32g32b32a32f,
  // BGRA-channels
  oclimgfmt_b8g8r8a8un,
  // sRGBA-channels
  oclimgfmt_sr8g8b8a8un,
};
PFC_ENUM(e_ocl_image_format);
//----------------------------------------------------------------------------


//============================================================================
// e_ocl_spir_version
//============================================================================
enum e_ocl_spir_version
{
  oclspir_none = 0x0000,
  oclspir_1_2  = 0x0001,
  oclspir_2_0  = 0x0002,
  oclspir_v    = 0x0004,
};
PFC_ENUM(e_ocl_spir_version);
//----------------------------------------------------------------------------


//============================================================================
// e_ocl_compiler_log_level
//============================================================================
enum e_ocl_compiler_log_level
{
  oclcompilerloglevel_none,
  oclcompilerloglevel_errors,
  oclcompilerloglevel_all,
};
//----------------------------------------------------------------------------


//============================================================================
// ocl_svec2
//============================================================================
struct ocl_svec2
{ PFC_MONO(ocl_svec2) {PFC_VAR2(x, y);}
  // construction
  PFC_INLINE ocl_svec2();
  PFC_INLINE ocl_svec2(size_t x_, size_t y_);
  //--------------------------------------------------------------------------

  size_t x, y;
};
PFC_SET_TYPE_TRAIT(ocl_svec2, is_type_pod, true);
//----------------------------------------------------------------------------


//============================================================================
// ocl_svec3
//============================================================================
struct ocl_svec3
{ PFC_MONO(ocl_svec3) {PFC_VAR3(x, y, z);}
  // construction
  PFC_INLINE ocl_svec3();
  PFC_INLINE ocl_svec3(size_t x_, size_t y_, size_t z_);
  //--------------------------------------------------------------------------

  size_t x, y, z;
};
PFC_SET_TYPE_TRAIT(ocl_svec3, is_type_pod, true);
//----------------------------------------------------------------------------


//============================================================================
// ocl_device_info
//============================================================================
struct ocl_device_info
{
  // construction
  ocl_device_info();
  //--------------------------------------------------------------------------

  // general properties
  cl_device_id id;
  heap_str name;
  heap_str vendor_name;
  heap_str version;
  heap_str driver_version;
  heap_str extensions;
  e_ocl_device_type type;
  bool is_big_endian;
  e_ocl_spir_version supported_spir_versions;
  unsigned max_clock_freq_mhz;
  unsigned max_compute_units;
  unsigned max_estimated_gflops;
  array<size_t> max_dimension_work_items;
  size_t max_work_group_size;
  // floating point properties
  e_ocl_float_config single_fp_config;
  e_ocl_float_config double_fp_config;
  // vector properties
  unsigned preferred_vector_width_char;
  unsigned preferred_vector_width_short;
  unsigned preferred_vector_width_int;
  unsigned preferred_vector_width_long;
  unsigned preferred_vector_width_float;
  unsigned preferred_vector_width_double;
  unsigned preferred_vector_width_half;
  unsigned native_vector_width_char;
  unsigned native_vector_width_short;
  unsigned native_vector_width_int;
  unsigned native_vector_width_long;
  unsigned native_vector_width_float;
  unsigned native_vector_width_double;
  unsigned native_vector_width_half;
  // memory properties
  unsigned num_address_bits;
  size_t global_mem_size;
  size_t max_mem_alloc_size;
  unsigned mem_base_address_align;
  e_ocl_cache_type global_cache_type;
  size_t global_cache_size;
  unsigned global_cacheline_size;
  e_ocl_local_mem_type local_mem_type;
  size_t local_mem_size;
  // constant buffer properties
  size_t max_constant_buffer_size;
  unsigned max_constant_args;
  // image properties
  bool is_image_support;
  unsigned image_pitch_align;
  unsigned image_base_address_align;
  unsigned max_image_read_args;
  unsigned max_image_write_args;
  unsigned max_image_rw_args;
  size_t max_image_2d_width;
  size_t max_image_2d_height;
  size_t max_image_3d_width;
  size_t max_image_3d_height;
  size_t max_image_3d_depth;
  size_t max_image_array_size;
  size_t max_image_buffer_size;
  unsigned max_image_samplers;
};
PFC_SET_TYPE_TRAIT(ocl_device_info, is_type_pod_move, true);
//----------------------------------------------------------------------------


//============================================================================
// ocl_platform_info
//============================================================================
struct ocl_platform_info
{
  // construction
  ocl_platform_info();
  //--------------------------------------------------------------------------

  cl_platform_id id;
  heap_str name;
  heap_str version;
  heap_str vendor;
  e_ocl_platform_profile profile;
  unsigned max_estimated_gflops;
  array<ocl_device_info> devices;
};
PFC_SET_TYPE_TRAIT(ocl_platform_info, is_type_pod_move, true);
//----------------------------------------------------------------------------


//============================================================================
// ocl_compiled_program
//============================================================================
struct ocl_compiled_program
{ PFC_MONO(ocl_compiled_program) {PFC_VAR2(source_code, device_binaries);}
  enum {version=1};
  heap_str source_code;
  array<raw_data> device_binaries;
};
PFC_SET_TYPE_TRAIT(ocl_compiled_program, is_type_pod_move, true);
//----------------------------------------------------------------------------


//============================================================================
// ocl_kernel_program_dependency
//============================================================================
struct ocl_kernel_program_dependency
{ PFC_MONO(ocl_kernel_program_dependency) {PFC_VAR2(source_file, dependent_files);}
  heap_str source_file;
  array<heap_str> dependent_files;
};
PFC_SET_TYPE_TRAIT(ocl_kernel_program_dependency, is_type_pod_move, true);
//----------------------------------------------------------------------------


//============================================================================
// ocl_env
//============================================================================
class ocl_env
{
public:
  // nested
  typedef pair<const ocl_platform_info*, const ocl_device_info*> device_t;
  //--------------------------------------------------------------------------

  // construction
  ocl_env();
  ~ocl_env();
  static PFC_INLINE ocl_env &active();
  void remove_devices(e_ocl_device_type);
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE unsigned num_platforms() const;
  PFC_INLINE const ocl_platform_info *platforms() const;
  PFC_INLINE ocl_platform_info *platforms();
  PFC_INLINE unsigned num_devices() const;
  PFC_INLINE const device_t *devices() const;
  //--------------------------------------------------------------------------

private:
  friend class ocl_context;
  friend class ocl_command_queue;
  friend class ocl_program;
  friend class ocl_kernel;
  friend class ocl_memory;
  friend class ocl_event;
  ocl_env(const ocl_env&); // not implemented
  void operator=(const ocl_env&); // not implemented
  //--------------------------------------------------------------------------

  // OpenCL functions
  #define PFC_OCL_FUNC(rtype__, fname__, fargs__, cargs__)\
    typedef rtype__(CL_API_ENTRY CL_API_CALL* fname__##_t)fargs__;\
    static fname__##_t s_fn_##fname__;\
    static PFC_INLINE rtype__ fname__ fargs__\
    {\
      PFC_ASSERT_PEDANTIC_MSG(s_fn_##fname__, ("OpenCL function %s() not available\r\n", #fname__));\
      return (*s_fn_##fname__)cargs__;\
    }
  #include "ocl_device.inc"
  //--------------------------------------------------------------------------

  static ocl_env *s_active;
  HMODULE m_module;
  array<ocl_platform_info> m_platforms;
  array<device_t> m_devices;
};
//----------------------------------------------------------------------------


//============================================================================
// ocl_context
//============================================================================
class ocl_context
{
public:
  // construction
  ocl_context();
  ocl_context(cl_device_id);
  ocl_context(const cl_device_id*, unsigned num_devices_);
  ~ocl_context();
  void init(cl_device_id);
  void init(const cl_device_id*, unsigned num_devices_);
  void release();
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE unsigned num_devices() const;
  PFC_INLINE const cl_device_id *device_ids() const;
  //--------------------------------------------------------------------------

  // resource creation
  cl_command_queue create_queue(cl_device_id);
  cl_mem create_buffer(size_t size_, void *data_, e_ocl_mem_type type_=e_ocl_mem_type(oclmemtype_kernel_read|oclmemtype_alloc_device));
  cl_mem create_image1d(unsigned width_, unsigned array_size_, e_ocl_image_format, void *data_, e_ocl_mem_type type_=e_ocl_mem_type(oclmemtype_kernel_read|oclmemtype_alloc_device));
  cl_mem create_image2d(unsigned width_, unsigned height_, unsigned array_size_, e_ocl_image_format, void *data_, e_ocl_mem_type type_=e_ocl_mem_type(oclmemtype_kernel_read|oclmemtype_alloc_device));
  cl_mem create_image3d(unsigned width_, unsigned height_, unsigned depth_, e_ocl_image_format, void *data_, e_ocl_mem_type type_=e_ocl_mem_type(oclmemtype_kernel_read|oclmemtype_alloc_device));
  //--------------------------------------------------------------------------

  // program creation & building
  cl_program create_source_program(const char *src_);
  cl_program create_binary_program(const void *binary_, size_t bin_size_, const cl_device_id *devices_=0, unsigned num_devices_=0);
  cl_program create_binary_program(const void *binary_, size_t bin_size_, cl_device_id);
  cl_program create_builtin_program(const char *kernel_names_, const cl_device_id *devices_=0, unsigned num_devices_=0);
  cl_program create_builtin_program(const char *kernel_names_, cl_device_id);
  cl_program create_il_program(const void *il_binary_, size_t bin_size_);
  bool build_program(cl_program, const cl_device_id *devices_=0, unsigned num_devices_=0, const char *options_=0, heap_str *build_log_=0, e_ocl_compiler_log_level log_level_=oclcompilerloglevel_errors);
  bool build_program(cl_program, cl_device_id, const char *options_=0, heap_str *build_log_=0, e_ocl_compiler_log_level log_level_=oclcompilerloglevel_errors);
  cl_program compile_program(const char *src_, const cl_device_id *devices_=0, unsigned num_devices_=0, heap_str *build_log_=0, e_ocl_compiler_log_level log_level_=oclcompilerloglevel_errors);
  cl_program compile_program(const char *src_, cl_device_id, heap_str *build_log_=0, e_ocl_compiler_log_level log_level_=oclcompilerloglevel_errors);
  cl_program link_program(const cl_program*, unsigned num_programs_, const cl_device_id *devices_=0, unsigned num_devices_=0);
  cl_program link_program(const cl_program*, unsigned num_programs_, cl_device_id);
  cl_program link_program(cl_program, const cl_device_id *devices_=0, unsigned num_devices_=0);
  cl_program link_program(cl_program, cl_device_id);
  //--------------------------------------------------------------------------

private:
  ocl_context(const ocl_context&); // not implemented
  void operator=(const ocl_context&); // not implemented
  //--------------------------------------------------------------------------

  enum {max_devices=32};
  unsigned m_num_devices;
  cl_device_id m_device_ids[max_devices];
  cl_context m_context;
};
PFC_SET_TYPE_TRAIT2(ocl_context, is_type_pod_def_ctor, is_type_pod_move, true);
//----------------------------------------------------------------------------


//============================================================================
// ocl_command_queue
//============================================================================
class ocl_command_queue
{
public:
  // construction
  ocl_command_queue();
  ocl_command_queue(cl_command_queue);
  ~ocl_command_queue();
  void init(cl_command_queue);
  void release();
  //--------------------------------------------------------------------------

  // kernel execution
  void exec_1d(const ocl_kernel&, size_t group_size_, size_t num_groups_, size_t offset_=0, const cl_event *wait_events_=0, unsigned num_wait_events_=0, cl_event *event_=0);
  void exec_2d(const ocl_kernel&, const ocl_svec2 &group_size_, const ocl_svec2 &num_groups_, const ocl_svec2 &offset_=ocl_svec2(0, 0), const cl_event *wait_events_=0, unsigned num_wait_events_=0, cl_event *event_=0);
  void exec_3d(const ocl_kernel&, const ocl_svec3 &group_size_, const ocl_svec3 &num_groups_, const ocl_svec3 &offset_=ocl_svec3(0, 0, 0), const cl_event *wait_events_=0, unsigned num_wait_events_=0, cl_event *event_=0);
  void exec(const ocl_kernel&, unsigned work_dim_, const size_t *group_size_, const size_t *num_groups_, const size_t *offset_=0, const cl_event *wait_events_=0, unsigned num_wait_events_=0, cl_event *event_=0);
  //--------------------------------------------------------------------------

  // synchronization
  void wait_all();
  //--------------------------------------------------------------------------

  // data read/write
  void read_buffer(cl_mem buffer_, void *data_, size_t size_, size_t offset_=0, bool is_blocking_=true, const cl_event *wait_events_=0, unsigned num_wait_events_=0, cl_event *event_=0);
  void read_image_1d(cl_mem image_, void *data_, size_t origin_, const size_t size_, size_t start_slice_=0, size_t num_slices_=1, bool is_blocking_=true, const cl_event *wait_events_=0, unsigned num_wait_events_=0, cl_event *event_=0);
  void read_image_2d(cl_mem image_, void *data_, const ocl_svec2 &origin_, const ocl_svec2 &size_, size_t row_pitch_=0, size_t start_slice_=0, size_t num_slices_=1, bool is_blocking_=true, const cl_event *wait_events_=0, unsigned num_wait_events_=0, cl_event *event_=0);
  void read_image_3d(cl_mem image_, void *data_, const ocl_svec3 &origin_, const ocl_svec3 &size_, size_t row_pitch_=0, size_t slice_pitch_=0, bool is_blocking_=true, const cl_event *wait_events_=0, unsigned num_wait_events_=0, cl_event *event_=0);
  void write_buffer(cl_mem buffer_, const void *data_, size_t size_, size_t offset_=0, bool is_blocking_=true, const cl_event *wait_events_=0, unsigned num_wait_events_=0, cl_event *event_=0);
  void write_image_1d(cl_mem image_, const void *data_, const size_t size_, size_t origin_, size_t start_slice_=0, size_t num_slices_=1, bool is_blocking_=true, const cl_event *wait_events_=0, unsigned num_wait_events_=0, cl_event *event_=0);
  void write_image_2d(cl_mem image_, const void *data_, const ocl_svec2 &size_, const ocl_svec2 &origin_, size_t row_pitch_=0, size_t start_slice_=0, size_t num_slices_=1, size_t slice_pitch_=0, bool is_blocking_=true, const cl_event *wait_events_=0, unsigned num_wait_events_=0, cl_event *event_=0);
  void write_image_3d(cl_mem image_, const void *data_, const ocl_svec3 &size_, const ocl_svec3 &origin_, size_t row_pitch_=0, size_t slice_pitch_=0, bool is_blocking_=true, const cl_event *wait_events_=0, unsigned num_wait_events_=0, cl_event *event_=0);
  //--------------------------------------------------------------------------

  // accessors
  ocl_svec3 work_group_size_compiled(const ocl_kernel&); 
  ocl_svec3 work_group_size_preferred(const ocl_kernel&);
  //--------------------------------------------------------------------------

private:
  ocl_command_queue(const ocl_command_queue&); // not implemented
  void operator=(const ocl_command_queue&); // not implemented
  //--------------------------------------------------------------------------

  cl_command_queue m_queue;
  cl_device_id m_device;
};
PFC_SET_TYPE_TRAIT2(ocl_command_queue, is_type_pod_def_ctor, is_type_pod_move, true);
//----------------------------------------------------------------------------


//============================================================================
// ocl_program
//============================================================================
class ocl_program
{
public:
  // construction
  ocl_program();
  ocl_program(cl_program);
  ~ocl_program();
  void init(cl_program);
  void release();
  //--------------------------------------------------------------------------

  // kernel creation
  cl_kernel create_kernel(const char *kernel_name_) const;
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE cl_program program() const;
  PFC_INLINE unsigned num_devices() const;
  void fetch_device_binaries(raw_data *binaries_) const;
  //--------------------------------------------------------------------------

private:
  ocl_program(const ocl_program&); // not implemented
  void operator=(const ocl_program&); // not implemented
  //--------------------------------------------------------------------------

  cl_program m_program;
  unsigned m_num_devices;
};
PFC_SET_TYPE_TRAIT2(ocl_program, is_type_pod_def_ctor, is_type_pod_move, true);
//----------------------------------------------------------------------------


//============================================================================
// ocl_kernel
//============================================================================
class ocl_kernel
{
public:
  // construction
  ocl_kernel();
  ocl_kernel(cl_kernel);
  ~ocl_kernel();
  void init(cl_kernel);
  void release();
  PFC_INLINE bool is_init() const;
  //--------------------------------------------------------------------------

  // argument setup
  PFC_INLINE void set_arg_bytes(unsigned index_, const void *data_, unsigned num_bytes_);
  template<typename T> PFC_INLINE void set_arg(unsigned index_, const T&);
  template<typename T> PFC_INLINE void set_arg(unsigned index_, const T*, unsigned num_values_);
  //--------------------------------------------------------------------------

private:
  friend class ocl_command_queue;
  ocl_kernel(const ocl_kernel&); // not implemented
  void operator=(const ocl_kernel&); // not implemented
  //--------------------------------------------------------------------------

  cl_kernel m_kernel;
};
PFC_SET_TYPE_TRAIT2(ocl_kernel, is_type_pod_def_ctor, is_type_pod_move, true);
//----------------------------------------------------------------------------


//============================================================================
// ocl_memory
//============================================================================
class ocl_memory
{
public:
  // construction
  ocl_memory();
  ocl_memory(cl_mem);
  ~ocl_memory();
  void init(cl_mem);
  void release();
  //--------------------------------------------------------------------------

  // argument accessor
  enum {arg_size=sizeof(cl_mem)};
  PFC_INLINE const void *arg_data() const;
  PFC_INLINE cl_mem handle() const;
  //--------------------------------------------------------------------------

private:
  ocl_memory(const ocl_memory&); // not implemented
  void operator=(const ocl_memory&); // not implemented
  //--------------------------------------------------------------------------

  cl_mem m_mem;
};
PFC_SET_TYPE_TRAIT2(ocl_memory, is_type_pod_def_ctor, is_type_pod_move, true);
//----------------------------------------------------------------------------


//============================================================================
// ocl_event
//============================================================================
class ocl_event
{
public:
  // construction
  ocl_event();
  ocl_event(cl_event);
  ~ocl_event();
  void init(cl_event);
  void release();
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE cl_event handle() const;
  PFC_INLINE bool is_complete() const;
  static void wait(const ocl_event*, unsigned num_events_);
  //--------------------------------------------------------------------------

private:
  ocl_event(const ocl_event&); // not implemented
  void operator=(const ocl_event&); // not implemented
  //--------------------------------------------------------------------------

  cl_event m_event;
};
PFC_SET_TYPE_TRAIT2(ocl_event, is_type_pod_def_ctor, is_type_pod_move, true);
//----------------------------------------------------------------------------

//============================================================================
#include "ocl_device.inl"
} // namespace pfc
#endif
