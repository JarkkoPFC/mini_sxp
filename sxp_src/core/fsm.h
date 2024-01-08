//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_FSM_H
#define PFC_CORE_FSM_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "variant.h"
namespace pfc
{

// new
template<class FSM> class fsm_state_base;
//----------------------------------------------------------------------------


//============================================================================
// fsm_state_base
//============================================================================
template<class FSM>
class fsm_state_base
{
public:
  // state interface
  PFC_INLINE fsm_state_base();
  virtual PFC_INLINE ~fsm_state_base()=0;
  virtual PFC_INLINE void dispatch_event(unsigned eid_, void *e_);
  virtual void tick(float delta_time_);
  //--------------------------------------------------------------------------

  FSM *const fsm;
  //--------------------------------------------------------------------------

private:
  void operator=(const fsm_state_base&); // not implemented
};
//----------------------------------------------------------------------------


//============================================================================
// fsm_poly_variant
//============================================================================
template<class FSM, unsigned max_size, unsigned align>
class fsm_poly_variant: public poly_variant<fsm_state_base<FSM>, max_size, align>
{
  struct state_null: fsm_state_base<FSM> {};
public:
  // construction
  fsm_poly_variant();
  template<class C> PFC_INLINE void operator=(meta_type<C>);
};
//----------------------------------------------------------------------------


//============================================================================
// finite-state machine
//============================================================================
#define PFC_FSM_BASE(fsm__, max_size__, align__)\
  friend class fsm_state_base<fsm__ >;\
  template<class EH, typename E> friend void pfc::send_event(EH&, E&);\
  template<typename S> static PFC_INLINE S *set_state(fsm__ &v_) {v_.m_fsm_state=meta_type<S>(); return &static_cast<S&>(v_.m_fsm_state.ref());}\
  fsm_poly_variant<fsm__, max_size__, align__> m_fsm_state;\
  virtual void dispatch_event(unsigned eid_, void *e_) {m_fsm_state->dispatch_event(eid_, e_);}\
  void dispatch_fallthrough_event(unsigned eid_, void *e_)\
  {\
    struct event_handler {static PFC_INLINE void dispatch_event(unsigned, void*) {}};\
    typedef fsm__ this_class_t;\
    typedef event_handler base_class_t;\
    typedef void(event_handler::*event_mem_func)(void*);\
    struct event {unsigned eid; event_mem_func func;};\
    static const event s_efuncs[]={
#define PFC_FSM(fsm__, base__, max_size__, align__)\
  friend class fsm_state_base<fsm__ >;\
  template<class EH, typename E> friend void pfc::send_event(EH&, E&);\
  template<typename S> static PFC_INLINE S *set_state(fsm__ &v_) {v_.m_fsm_state=meta_type<S>(); return &static_cast<S&>(v_.m_fsm_state.ref());}\
  fsm_poly_variant<fsm__, max_size__, align__> m_fsm_state;\
  virtual void dispatch_event(unsigned eid_, void *e_) {m_fsm_state->dispatch_event(eid_, e_);}\
  void dispatch_fallthrough_event(unsigned eid_, void *e_)\
  {\
    struct event_handler {};\
    typedef fsm__ this_class_t;\
    typedef base__ base_class_t;\
    typedef void(event_handler::*event_mem_func)(void*);\
    struct event {unsigned eid; event_mem_func func;};\
    static const event s_efuncs[]={
#define PFC_FSM_INIT(state__) {(void*&)m_fsm_state->fsm=this; set_state<state__ >(*this);}
//----------------------------------------------------------------------------

//============================================================================
#include "fsm.inl"
} // namespace pfc
#endif
