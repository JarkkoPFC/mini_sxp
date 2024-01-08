//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// ffunc_callstack
//============================================================================
ffunc_callstack::ffunc_callstack(unsigned capacity_)
{
  m_stack=malloc(capacity_);
  m_ffunc_tick=0;
  m_capacity=int(capacity_);
  m_size=0;
#ifdef PFC_FFUNC_ENABLE_MEM_TRACK
  m_peak_size=0;
#endif
}
//----

ffunc_callstack::ffunc_callstack(usize_t *buffer_, unsigned capacity_)
{
  m_stack=buffer_;
  m_ffunc_tick=0;
  m_capacity=-int(capacity_); // negative capacity to indicate the buffer isn't dynamically allocated by the class (skip free upon destruction)
  m_size=0;
#ifdef PFC_FFUNC_ENABLE_MEM_TRACK
  m_peak_size=0;
#endif
}
//----

ffunc_callstack::~ffunc_callstack()
{
  PFC_ASSERT_MSG(m_size==0, ("Destroying stack while used by a fiber\r\n"));
  if(m_capacity>0)
    free(m_stack);
}
//----

void ffunc_callstack::abort()
{
#ifdef PFC_FFUNC_DISABLE_SAFE_ABORT
  m_ffunc_tick=0;
  m_size=0;
#else
  m_size=unsigned(-1);
  tick(0);
  m_size=0;
#endif
}
//----

void ffunc_callstack::force_abort()
{
  m_ffunc_tick=0;
  m_size=0;
}
//----------------------------------------------------------------------------

unsigned ffunc_callstack::capacity() const
{
  return abs(m_capacity);
}
//----

unsigned ffunc_callstack::size() const
{
  return m_size;
}
//----

unsigned ffunc_callstack::peak_size() const
{
#ifdef PFC_FFUNC_ENABLE_MEM_TRACK
  return m_peak_size;
#else
  return 0;
#endif
}
//----

bool ffunc_callstack::is_running() const
{
  return m_ffunc_tick!=0;
}
//----

bool ffunc_callstack::is_abort() const
{
#ifdef PFC_FFUNC_DISABLE_SAFE_ABORT
  return false;
#else
  return m_size>(unsigned(-1)>>1);
#endif
}
//----------------------------------------------------------------------------

bool ffunc_callstack::tick(float delta_time_)
{
  return m_ffunc_tick && m_ffunc_tick(*this, delta_time_);
}
//----------------------------------------------------------------------------

template<class FFunc>
void *ffunc_callstack::impl_start()
{
  PFC_ASSERT_MSG(!m_ffunc_tick, ("Stack used by another fiber\r\n"));
  PFC_ASSERT_MSG(sizeof(FFunc)<=abs(m_capacity), ("Stack overflow by %i bytes\r\n", unsigned(sizeof(FFunc)-abs(m_capacity))));
  m_ffunc_tick=&ffunc_tick<FFunc>;
  m_size+=sizeof(FFunc);
#ifdef PFC_FFUNC_ENABLE_MEM_TRACK
  m_peak_size=max(m_peak_size, unsigned(sizeof(FFunc)));
#endif
  ((FFunc*)m_stack)->__m_ffunc_active_line=0;
  return m_stack;
}
//----

template<class FFunc>
void *ffunc_callstack::impl_push()
{
  PFC_ASSERT_MSG(m_size+sizeof(FFunc)<=abs(m_capacity), ("Stack overflow by %i bytes\r\n", unsigned(m_size+sizeof(FFunc)-abs(m_capacity))));
  FFunc *v=(FFunc*)(((char*)m_stack)+m_size);
  m_size+=sizeof(FFunc);
#ifdef PFC_FFUNC_ENABLE_MEM_TRACK
  m_peak_size=max(m_peak_size, m_size);
#endif
  v->__m_ffunc_active_line=0;
  return v;
}
//----

template<class FFunc>
bool ffunc_callstack::impl_tick(unsigned stack_pos_, float dtime_)
{
  FFunc *ff=(FFunc*)((char*)m_stack+stack_pos_);
  if(ff->tick(*this, stack_pos_+sizeof(FFunc), dtime_))
    return true;
  m_size-=sizeof(FFunc);
  ff->~FFunc();
  return false;
}
//----------------------------------------------------------------------------


//============================================================================
// ffunc_sleep
//============================================================================
ffunc_sleep::ffunc_sleep(ufloat_t t_)
  :sleep_time(t_)
{
}
//----------------------------------------------------------------------------
