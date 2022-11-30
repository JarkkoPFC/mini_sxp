//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_FUNCTOR_H
#define PFC_CORE_FUNCTOR_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "core.h"
namespace pfc
{

// new
// functor
template<typename FS> class functor;
template<class T, class U, typename R> PFC_INLINE functor<R()> make_functor(T&, R(*)(U&));
#define PFC_MAKE_MEM_FUNCTOR(functor_t__, obj__, class__, mem_func__) functor_t__(obj__, functor_t__::call_mem_func<class__, &class__::mem_func__>)
#define PFC_MAKE_CMEM_FUNCTOR(functor_t__, obj__, class__, mem_func__) functor_t__(obj__, functor_t__::call_cmem_func<class__, &class__::mem_func__>)
#define PFC_MAKE_VMEM_FUNCTOR(functor_t__, obj__, class__, mem_func__) functor_t__(obj__, functor_t__::call_vmem_func<class__, &class__::mem_func__>)
#define PFC_MAKE_CVMEM_FUNCTOR(functor_t__, obj__, class__, mem_func__) functor_t__(obj__, functor_t__::call_cvmem_func<class__, &class__::mem_func__>)
// class member function wrappers
template<typename FS> class mem_func;
template<typename FS> class cmem_func;
template<class T, typename R> PFC_INLINE mem_func<R()> make_mem_func(R(T::*)());
template<class T, typename R> PFC_INLINE cmem_func<R()> make_mem_func(R(T::*)() const);
//----------------------------------------------------------------------------


//============================================================================
// functor
//============================================================================
// functor takes a function signature as a template argument, e.g.
//   int trunc(float f_)  {return int(f_);}
//   functor<int(float)> f(trunc);
// for member functions use cv-qualifier matching call_*mem_func function, e.g.
//   struct foo {int trunc(float f_) const {return int(f_);}};
//   foo obj;
//   functor<int(float)> f(obj, functor<int(float)>::call_cmem_func<foo, &foo::trunc>);
// and to reduce some redundancy there's helper macro:
//   auto f=PFC_MAKE_CMEM_FUNCTOR(functor<int(float)>, obj, foo, trunc);
// note: function signatures up to 10 arguments are supported
template<typename R>
class functor<R()>
{
public:
  // construction and execution
  PFC_INLINE functor();
  PFC_INLINE functor(R(*)());
  template<class T, class U> PFC_INLINE functor(T&, R(*)(U&));
  inline R operator()() const;
  PFC_INLINE operator bool() const;
  PFC_INLINE void clear();
  //--------------------------------------------------------------------------

  // member function call functions
  template<class T, R(T::*mem_fun)()> static R call_mem_func(T&);
  template<class T, R(T::*mem_fun)() const> static R call_cmem_func(const T&);
  template<class T, R(T::*mem_fun)() volatile> static R call_vmem_func(volatile T&);
  template<class T, R(T::*mem_fun)() const volatile> static R call_cvmem_func(const volatile T&);
  //--------------------------------------------------------------------------

private:
  void *m_this;
  void *m_func;
};
//----------------------------------------------------------------------------


//============================================================================
// mem_func/cmem_func
//============================================================================
// mem_func takes a function signature as a template argument, e.g.
//   int foo::bar(float);
//   mem_func<int(float)> f(&foo::bar);
//  note: member function signatures up to 10 arguments are supported
//        for const member functions use cmem_func
template<typename R>
class mem_func<R()>
{
public:
  // construction and execution
  PFC_INLINE mem_func();
  template<class T> PFC_INLINE mem_func(R(T::*)());
  template<class T> inline R operator()(T&) const;
  PFC_INLINE operator bool() const;
  //--------------------------------------------------------------------------

private:
  friend class cmem_func<R()>;
  R(mem_func::*m_mem_func)();
};
//----

template<typename R>
class cmem_func<R()>
{
public:
  // construction and execution
  PFC_INLINE cmem_func();
  PFC_INLINE cmem_func(const mem_func<R()>&);
  template<class T> PFC_INLINE cmem_func(R(T::*)() const);
  template<class T> inline R operator()(const T&) const;
  PFC_INLINE operator bool() const;
  //--------------------------------------------------------------------------

private:
  R(cmem_func::*m_mem_func)() const;
};
//----------------------------------------------------------------------------

//============================================================================
#include "functor.inl"
} // namespace pfc
#endif
