//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// job management free functions
//============================================================================
template<typename T, typename U>
PFC_INLINE e_jobtype_id create_job_type(const char *type_name_, void(*func_)(T*, U*), e_job_scheduling scheduling_)
{
  return mp_job_queue::active().create_job_type(type_name_, func_, scheduling_);
}
//----

e_jobtype_id create_job_type(const char *type_name_, void(*func_)(void*, void*), e_job_scheduling scheduling_)
{
  return mp_job_queue::active().create_job_type(type_name_, func_, scheduling_);
}
//----

template<typename T>
void set_job_type_data(e_jobtype_id type_, T *data_)
{
  mp_job_queue::active().set_job_type_data(type_, data_);
}
//----

template<typename T>
PFC_INLINE void add_job(e_jobtype_id type_, T *data_)
{
  mp_job_queue::active().add_job(type_, data_);
}
//----

PFC_INLINE void wait_job_type(e_jobtype_id type_)
{
  mp_job_queue::active().wait_job_type(type_);
}
//----

PFC_INLINE void wait_job_types(const e_jobtype_id *types_, unsigned num_job_types_)
{
  mp_job_queue::active().wait_job_types(types_, num_job_types_);
}
//----

PFC_INLINE void wait_all_jobs()
{
  mp_job_queue::active().wait_all_jobs();
}
//----

PFC_INLINE void exec_job(e_jobtype_id jtid_)
{
  return mp_job_queue::active().exec_job(jtid_);
}
//----

PFC_INLINE bool has_jobs(e_jobtype_id jtid_, bool exec_jobs_)
{
  return mp_job_queue::active().has_jobs(jtid_, exec_jobs_);
}
//----

PFC_INLINE bool has_jobs(const e_jobtype_id *jtids_, unsigned num_job_types_, bool exec_jobs_)
{
  return mp_job_queue::active().has_jobs(jtids_, num_job_types_, exec_jobs_);
}
//----------------------------------------------------------------------------


//============================================================================
// mp_job_queue
//============================================================================
bool mp_job_queue::has_active()
{
  return s_active!=0;
}
//----

mp_job_queue &mp_job_queue::active()
{
  PFC_ASSERT_PEDANTIC_MSG(s_active, ("No mp_job_queue has been created\r\n"));
  return *s_active;
}
//----------------------------------------------------------------------------

unsigned mp_job_queue::num_worker_threads() const
{
  return (unsigned)m_workers.size();
}
//----------------------------------------------------------------------------

template<typename T, typename U>
e_jobtype_id mp_job_queue::create_job_type(const char *type_name_, void(*func_)(T*, U*), e_job_scheduling scheduling_)
{
  e_jobtype_id id=create_job_type(type_name_, (void(*)(void*, void*))func_, scheduling_);
  m_job_types[id].type_data_id=type_id<U>::id;
  m_job_types[id].job_data_id=type_id<T>::id;
  return id;
}
//----

template<typename T, typename U>
e_jobtype_id mp_job_queue::find_job_type(void(*func_)(T*, U*))
{
  return find_job_type((void(*)(void*, void*))func_);
}
//----

template<typename T>
void mp_job_queue::set_job_type_data(e_jobtype_id type_, T *data_)
{
  PFC_ASSERT_MSG(type_id<T>::id==m_job_types[type_].type_data_id, ("Added wrong type of job type data \"%s\" for the given job type \"%s\"\r\n", typeid(T).name(), m_job_types[type_].name));
  m_job_types[type_].type_data=(void*)data_;
}
//----------------------------------------------------------------------------

template<typename T>
void mp_job_queue::add_job(e_jobtype_id type_, T *data_)
{
  PFC_ASSERT_MSG(type_id<T>::id==m_job_types[type_].job_data_id, ("Added wrong type of job data \"%s\" for the given job type \"%s\"\r\n", typeid(T).name(), m_job_types[type_].name));
  add_job(type_, (void*)data_);
}
//----------------------------------------------------------------------------
