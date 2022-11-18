//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// fsm_state_base
//============================================================================
template<class FSM>
fsm_state_base<FSM>::fsm_state_base()
  :fsm(fsm)
{
}
//----

template<class FSM>
fsm_state_base<FSM>::~fsm_state_base()
{
}
//----

template<class FSM>
void fsm_state_base<FSM>::dispatch_event(unsigned eid_, void *e_)
{
  fsm->dispatch_fallthrough_event(eid_, e_);
}
//----

template<class FSM>
void fsm_state_base<FSM>::tick(float delta_time_)
{
}
//----------------------------------------------------------------------------


//============================================================================
// fsm_poly_variant
//============================================================================
template<class FSM, unsigned max_size, unsigned align>
fsm_poly_variant<FSM, max_size, align>::fsm_poly_variant()
  :poly_variant<fsm_state_base<FSM>, max_size, align>(meta_type<state_null>())
{
/*  const_cast<FSM*&>(this->ref().fsm)=0;*/
}
//----

template<class FSM, unsigned max_size, unsigned align>
template<class C>
void fsm_poly_variant<FSM, max_size, align>::operator=(meta_type<C> type_)
{
  poly_variant<fsm_state_base<FSM>, max_size, align>::operator=(type_);
}
//----------------------------------------------------------------------------
