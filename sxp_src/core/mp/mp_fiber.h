//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_MP_FIBER_H
#define PFC_CORE_MP_FIBER_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "sxp_src/core/utils.h"
namespace pfc
{

// new
class ffunc_callstack;
struct ffunc_sleep;
#define PFC_FFUNC() usize_t __m_ffunc_active_line; bool tick(ffunc_callstack &__ffunc_cs_, unsigned __ffunc_stack_pos_, float &__ffunc_dtime_)
#define PFC_FFUNC_IMPL(ffunc__) bool ffunc__::tick(ffunc_callstack &__ffunc_cs_, unsigned __ffunc_stack_pos_, float &__ffunc_dtime_)
#define PFC_FFUNC_BODY_BEGIN switch(__m_ffunc_active_line) {case 0:
#define PFC_FFUNC_BODY_END break;} return false;
#define PFC_FFUNC_CALL(ffunc__, ffunc_args__)\
  case __LINE__:\
  {\
    if(__ffunc_cs_.size()==__ffunc_stack_pos_)\
    {\
      __m_ffunc_active_line=__LINE__;\
      new(__ffunc_cs_.impl_push<ffunc__ >())ffunc__ ffunc_args__;\
    }\
    if(__ffunc_cs_.impl_tick<ffunc__ >(__ffunc_stack_pos_, __ffunc_dtime_))\
      return true;\
    if(__ffunc_cs_.is_abort())\
      return false;\
  }
#define PFC_FFUNC_START(ffunc_callstack__, ffunc__, ffunc_args__) new(ffunc_callstack__.impl_start<ffunc__ >())ffunc__ ffunc_args__
//----------------------------------------------------------------------------


//============================================================================
// ffunc_callstack
//============================================================================
class ffunc_callstack
{
public:
  // construction
  PFC_INLINE ffunc_callstack(unsigned capacity_=256);
  PFC_INLINE ffunc_callstack(usize_t *buffer_, unsigned capacity_=0);
  PFC_INLINE ~ffunc_callstack();
  PFC_INLINE void abort();
  PFC_INLINE void force_abort();
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE unsigned capacity() const;
  PFC_INLINE unsigned size() const;
  PFC_INLINE unsigned peak_size() const;
  PFC_INLINE bool is_running() const;
  PFC_INLINE bool is_abort() const;
  //--------------------------------------------------------------------------

  // ticking
  PFC_INLINE bool tick(ufloat_t delta_time_);
  //--------------------------------------------------------------------------

  // private interface for FFUNC macros (do not use)
  template<class FFunc> void *impl_start();
  template<class FFunc> void *impl_push();
  template<class FFunc> bool impl_tick(unsigned stack_pos_, float dtime_);
  //--------------------------------------------------------------------------

private:
  ffunc_callstack(const ffunc_callstack&); // not implemented
  void operator=(const ffunc_callstack&); // not implemented
  //--------------------------------------------------------------------------

  template<typename FFunc> static bool ffunc_tick(ffunc_callstack &cs_, float delta_time_)
  {
    if(cs_.impl_tick<FFunc>(0, delta_time_))
      return true;
    cs_.m_ffunc_tick=0;
    return false;
  }
  //--------------------------------------------------------------------------

  void *m_stack;
  bool(*m_ffunc_tick)(ffunc_callstack&, float delta_time_);
  int m_capacity;
  unsigned m_size;
#ifdef PFC_FFUNC_ENABLE_MEM_TRACK
  unsigned m_peak_size;
#endif
};
//----------------------------------------------------------------------------


//============================================================================
// ffunc_sleep
//============================================================================
struct ffunc_sleep
{
  ufloat_t sleep_time;
  PFC_INLINE ffunc_sleep(float t_);
  PFC_FFUNC();
};
//----------------------------------------------------------------------------

//============================================================================
#include "mp_fiber.inl"
} // namespace pfc
#endif
