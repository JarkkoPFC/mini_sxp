//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// ocl_svec2
//============================================================================
ocl_svec2::ocl_svec2()
  :x(0)
  ,y(0)
{
}
//----

ocl_svec2::ocl_svec2(size_t x_, size_t y_)
  :x(x_)
  ,y(y_)
{
}
//----------------------------------------------------------------------------


//============================================================================
// ocl_svec3
//============================================================================
ocl_svec3::ocl_svec3()
  :x(0)
  ,y(0)
  ,z(0)
{
}
//----

ocl_svec3::ocl_svec3(size_t x_, size_t y_, size_t z_)
  :x(x_)
  ,y(y_)
  ,z(z_)
{
}
//----------------------------------------------------------------------------


//============================================================================
// ocl_env
//============================================================================
ocl_env &ocl_env::active()
{
  PFC_ASSERT_PEDANTIC_MSG(s_active, ("No ocl_env has been created\r\n"));
  return *s_active;
}
//----------------------------------------------------------------------------

unsigned ocl_env::num_platforms() const
{
  return unsigned(m_platforms.size());
}
//----

const ocl_platform_info *ocl_env::platforms() const
{
  return m_platforms.data();
}
//----

ocl_platform_info *ocl_env::platforms()
{
  return m_platforms.data();
}
//----

unsigned ocl_env::num_devices() const
{
  return unsigned(m_devices.size());
}
//----

const ocl_env::device_t *ocl_env::devices() const
{
  return m_devices.data();
}
//----------------------------------------------------------------------------


//============================================================================
// ocl_context
//============================================================================
unsigned ocl_context::num_devices() const
{
  return m_num_devices;
}
//----

const cl_device_id *ocl_context::device_ids() const
{
  return m_device_ids;
}
//----------------------------------------------------------------------------


//============================================================================
// ocl_program
//============================================================================
cl_program ocl_program::program() const
{
  return m_program;
}
//----

unsigned ocl_program::num_devices() const
{
  return m_num_devices;
}
//----------------------------------------------------------------------------


//============================================================================
// ocl_kernel
//============================================================================
namespace priv
{
  template<bool is_fund, typename T>
  struct ocl_hlp_arg
  {
    enum{size=sizeof(T)};
    static PFC_INLINE const void *arg_data(const T &arg_) {return &arg_;}
  };
  template<typename T>
  struct ocl_hlp_arg<false, T>
  {
    enum{size=T::arg_size};
    static PFC_INLINE const void *arg_data(const T &arg_) {return arg_.arg_data();}
  };
  template<>
  struct ocl_hlp_arg<false, cl_mem>
  {
    enum{size=sizeof(cl_mem)};
    static PFC_INLINE const void *arg_data(const cl_mem &arg_) {return &arg_;}
  };
}
//----------------------------------------------------------------------------

cl_kernel ocl_kernel::kernel() const
{
  return m_kernel;
}
//----------------------------------------------------------------------------

void ocl_kernel::set_arg_bytes(unsigned index_, const void *v_, unsigned num_bytes_)
{
  PFC_OCL_VERIFY_MSG(ocl_env::clSetKernelArg(m_kernel, index_, num_bytes_, v_),
                     ("OpenCL: Setting argument %i of %i bytes failed.\r\n", index_, num_bytes_));
}
//----

template<typename T>
void ocl_kernel::set_arg(unsigned index_, const T &arg_)
{
  PFC_OCL_VERIFY_MSG(ocl_env::clSetKernelArg(m_kernel, index_, priv::ocl_hlp_arg<is_type_fund<T>::res, T>::size, priv::ocl_hlp_arg<is_type_fund<T>::res, T>::arg_data(arg_)),
                     ("OpenCL: Setting argument %i of type \"%s\" (%i bytes) failed.\r\n", index_, typeid(arg_).name(), priv::ocl_hlp_arg<is_type_fund<T>::res, T>::size));
}
//----

template<typename T>
void ocl_kernel::set_arg(unsigned index_, const T *v_, unsigned num_values_)
{
  PFC_CTF_ASSERT_MSG(is_type_fund<T>::res, array_must_be_fundamental_data_type);
  PFC_OCL_VERIFY_MSG(ocl_env::clSetKernelArg(m_kernel, index_, sizeof(T)*num_values_, v_),
                     ("OpenCL: Setting argument %i of %ix\"%s\" (%i bytes) failed.\r\n", index_, num_values_, typeid(T).name(), sizeof(T)*num_values_));
}
//----------------------------------------------------------------------------


//============================================================================
// ocl_memory
//============================================================================
const void *ocl_memory::arg_data() const
{
  return &m_mem;
}
//----

cl_mem ocl_memory::handle() const
{
  return m_mem;
}
//----------------------------------------------------------------------------


//============================================================================
// ocl_event
//============================================================================
cl_event ocl_event::handle() const
{
  return m_event;
}
//----

bool ocl_event::is_complete() const
{
  // check event execution status
  PFC_ASSERT_PEDANTIC(m_event);
  cl_int res=0;
  PFC_OCL_VERIFY_MSG(ocl_env::clGetEventInfo(m_event, CL_EVENT_COMMAND_EXECUTION_STATUS, sizeof(cl_int), &res, 0),
                     ("Querying event info failed.\r\n"));
  return res==CL_COMPLETE;
}
//----------------------------------------------------------------------------
