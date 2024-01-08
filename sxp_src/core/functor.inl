//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// functor
//============================================================================
template<typename R>
functor<R()>::functor()
  :m_this(0)
  ,m_func(0)
{
}
//----

template<typename R>
functor<R()>::functor(R(*func_)())
  :m_this(0)
  ,m_func((void*)func_)
{
}
//----

template<typename R>
template<class T, class U>
functor<R()>::functor(T &this_, R(*func_)(U&))
  :m_this((void*)static_cast<U*>(&this_))
  ,m_func((void*)func_)
{
  PFC_STATIC_ASSERT_MSG((is_type_derived<T, U>::res), object_does_not_have_compatible_type_with_the_function_signature);
}
//----

template<typename R>
R functor<R()>::operator()() const
{
  // call member/free function
  PFC_ASSERT_PEDANTIC(m_func!=0);
  return m_this?(*(R(*)(void*))m_func)(m_this):(*(R(*)())m_func)();
}
//----

template<typename R>
functor<R()>::operator bool() const
{
  return m_func!=0;
}
//----

template<typename R>
void functor<R()>::clear()
{
  m_func=0;
}
//----------------------------------------------------------------------------

template<typename R>
template<class T, R(T::*mem_fun)()>
R functor<R()>::call_mem_func(T &this_)
{
  return (this_.*mem_fun)();
}
//----

template<typename R>
template<class T, R(T::*mem_fun)() const>
R functor<R()>::call_cmem_func(const T &this_)
{
  return (this_.*mem_fun)();
}
//----

template<typename R>
template<class T, R(T::*mem_fun)() volatile>
R functor<R()>::call_vmem_func(volatile T &this_)
{
  return (this_.*mem_fun)();
}
//----

template<typename R>
template<class T, R(T::*mem_fun)() const volatile>
R functor<R()>::call_cvmem_func(const volatile T &this_)
{
  return (this_.*mem_fun)();
}
//----------------------------------------------------------------------------

template<class T, class U, typename R>
PFC_INLINE functor<R()> make_functor(T &v_, R(*func_)(U&))
{
  return functor<R()>(v_, func_);
}
//----------------------------------------------------------------------------

#define PFC_FUNCTOR_TMPL()\
  template<typename R, PFC_FUNCTOR_TEMPLATE_ARG_LIST>\
  class functor<R(PFC_FUNCTOR_TYPE_LIST)>\
  {\
  public:\
    PFC_INLINE functor()                                                                           :m_this(0), m_func(0) {}\
    PFC_INLINE functor(R(*func_)(PFC_FUNCTOR_TYPE_LIST))                                           :m_this(0), m_func((void*)func_) {}\
    template<class T, class U> PFC_INLINE functor(T &this_, R(*func_)(U&, PFC_FUNCTOR_TYPE_LIST))  :m_this((void*)static_cast<U*>(&this_)), m_func((void*)func_) {PFC_STATIC_ASSERT_MSG((is_type_derived<T, U>::res), object_does_not_have_compatible_type_with_the_function_signature);}\
    inline R operator()(PFC_FUNCTOR_PROTO_ARG_LIST) const                                          {PFC_ASSERT_PEDANTIC(m_func!=0); return m_this?(*(R(*)(void*, PFC_FUNCTOR_TYPE_LIST))m_func)(m_this, PFC_FUNCTOR_ARG_LIST):(*(R(*)(PFC_FUNCTOR_TYPE_LIST))m_func)(PFC_FUNCTOR_ARG_LIST);}\
    PFC_INLINE operator bool() const                                                               {return m_func!=0;}\
    PFC_INLINE void clear()                                                                        {m_func=0;}\
    template<class T, R(T::*mem_fun)(PFC_FUNCTOR_TYPE_LIST)> static R call_mem_func(T &this_, PFC_FUNCTOR_PROTO_ARG_LIST) {return (this_.*mem_fun)(PFC_FUNCTOR_ARG_LIST);}\
    template<class T, R(T::*mem_fun)(PFC_FUNCTOR_TYPE_LIST) const> static R call_cmem_func(const T &this_, PFC_FUNCTOR_PROTO_ARG_LIST) {return (this_.*mem_fun)(PFC_FUNCTOR_ARG_LIST);}\
    template<class T, R(T::*mem_fun)(PFC_FUNCTOR_TYPE_LIST) volatile> static R call_vmem_func(volatile T &this_, PFC_FUNCTOR_PROTO_ARG_LIST) {return (this_.*mem_fun)(PFC_FUNCTOR_ARG_LIST);}\
    template<class T, R(T::*mem_fun)(PFC_FUNCTOR_TYPE_LIST) const volatile> static R call_cvmem_func(const volatile T &this_, PFC_FUNCTOR_PROTO_ARG_LIST) {return (this_.*mem_fun)(PFC_FUNCTOR_ARG_LIST);}\
  private:\
    void *m_this;\
    void *m_func;\
  };\
  template<class T, class U, typename R, PFC_FUNCTOR_TEMPLATE_ARG_LIST> functor<R(PFC_FUNCTOR_TYPE_LIST)> make_functor(T &v_, R(*func_)(U&, PFC_FUNCTOR_TYPE_LIST)) {return functor<R(PFC_FUNCTOR_TYPE_LIST)>(v_, func_);}
//----

// functor 1 argument implementation
#define PFC_FUNCTOR_TEMPLATE_ARG_LIST typename A0
#define PFC_FUNCTOR_TYPE_LIST A0
#define PFC_FUNCTOR_PROTO_ARG_LIST A0 a0_
#define PFC_FUNCTOR_ARG_LIST a0_
PFC_FUNCTOR_TMPL();
#undef PFC_FUNCTOR_TEMPLATE_ARG_LIST
#undef PFC_FUNCTOR_TYPE_LIST
#undef PFC_FUNCTOR_PROTO_ARG_LIST
#undef PFC_FUNCTOR_ARG_LIST
// functor 2 argument implementation
#define PFC_FUNCTOR_TEMPLATE_ARG_LIST typename A0, typename A1
#define PFC_FUNCTOR_TYPE_LIST A0, A1
#define PFC_FUNCTOR_PROTO_ARG_LIST A0 a0_, A1 a1_
#define PFC_FUNCTOR_ARG_LIST a0_, a1_
PFC_FUNCTOR_TMPL();
#undef PFC_FUNCTOR_TEMPLATE_ARG_LIST
#undef PFC_FUNCTOR_TYPE_LIST
#undef PFC_FUNCTOR_PROTO_ARG_LIST
#undef PFC_FUNCTOR_ARG_LIST
// functor 3 argument implementation
#define PFC_FUNCTOR_TEMPLATE_ARG_LIST typename A0, typename A1, typename A2
#define PFC_FUNCTOR_TYPE_LIST A0, A1, A2
#define PFC_FUNCTOR_PROTO_ARG_LIST A0 a0_, A1 a1_, A2 a2_
#define PFC_FUNCTOR_ARG_LIST a0_, a1_, a2_
PFC_FUNCTOR_TMPL();
#undef PFC_FUNCTOR_TEMPLATE_ARG_LIST
#undef PFC_FUNCTOR_TYPE_LIST
#undef PFC_FUNCTOR_PROTO_ARG_LIST
#undef PFC_FUNCTOR_ARG_LIST
// functor 4 argument implementation
#define PFC_FUNCTOR_TEMPLATE_ARG_LIST typename A0, typename A1, typename A2, typename A3
#define PFC_FUNCTOR_TYPE_LIST A0, A1, A2, A3
#define PFC_FUNCTOR_PROTO_ARG_LIST A0 a0_, A1 a1_, A2 a2_, A3 a3_
#define PFC_FUNCTOR_ARG_LIST a0_, a1_, a2_, a3_
PFC_FUNCTOR_TMPL();
#undef PFC_FUNCTOR_TEMPLATE_ARG_LIST
#undef PFC_FUNCTOR_TYPE_LIST
#undef PFC_FUNCTOR_PROTO_ARG_LIST
#undef PFC_FUNCTOR_ARG_LIST
// functor 5 argument implementation
#define PFC_FUNCTOR_TEMPLATE_ARG_LIST typename A0, typename A1, typename A2, typename A3, typename A4
#define PFC_FUNCTOR_TYPE_LIST A0, A1, A2, A3, A4
#define PFC_FUNCTOR_PROTO_ARG_LIST A0 a0_, A1 a1_, A2 a2_, A3 a3_, A4 a4_
#define PFC_FUNCTOR_ARG_LIST a0_, a1_, a2_, a3_, a4_
PFC_FUNCTOR_TMPL();
#undef PFC_FUNCTOR_TEMPLATE_ARG_LIST
#undef PFC_FUNCTOR_TYPE_LIST
#undef PFC_FUNCTOR_PROTO_ARG_LIST
#undef PFC_FUNCTOR_ARG_LIST
// functor 6 argument implementation
#define PFC_FUNCTOR_TEMPLATE_ARG_LIST typename A0, typename A1, typename A2, typename A3, typename A4, typename A5
#define PFC_FUNCTOR_TYPE_LIST A0, A1, A2, A3, A4, A5
#define PFC_FUNCTOR_PROTO_ARG_LIST A0 a0_, A1 a1_, A2 a2_, A3 a3_, A4 a4_, A5 a5_
#define PFC_FUNCTOR_ARG_LIST a0_, a1_, a2_, a3_, a4_, a5_
PFC_FUNCTOR_TMPL();
#undef PFC_FUNCTOR_TEMPLATE_ARG_LIST
#undef PFC_FUNCTOR_TYPE_LIST
#undef PFC_FUNCTOR_PROTO_ARG_LIST
#undef PFC_FUNCTOR_ARG_LIST
// functor 7 argument implementation
#define PFC_FUNCTOR_TEMPLATE_ARG_LIST typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6
#define PFC_FUNCTOR_TYPE_LIST A0, A1, A2, A3, A4, A5, A6
#define PFC_FUNCTOR_PROTO_ARG_LIST A0 a0_, A1 a1_, A2 a2_, A3 a3_, A4 a4_, A5 a5_, A6 a6_
#define PFC_FUNCTOR_ARG_LIST a0_, a1_, a2_, a3_, a4_, a5_, a6_
PFC_FUNCTOR_TMPL();
#undef PFC_FUNCTOR_TEMPLATE_ARG_LIST
#undef PFC_FUNCTOR_TYPE_LIST
#undef PFC_FUNCTOR_PROTO_ARG_LIST
#undef PFC_FUNCTOR_ARG_LIST
// functor 8 argument implementation
#define PFC_FUNCTOR_TEMPLATE_ARG_LIST typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7
#define PFC_FUNCTOR_TYPE_LIST A0, A1, A2, A3, A4, A5, A6, A7
#define PFC_FUNCTOR_PROTO_ARG_LIST A0 a0_, A1 a1_, A2 a2_, A3 a3_, A4 a4_, A5 a5_, A6 a6_, A7 a7_
#define PFC_FUNCTOR_ARG_LIST a0_, a1_, a2_, a3_, a4_, a5_, a6_, a7_
PFC_FUNCTOR_TMPL();
#undef PFC_FUNCTOR_TEMPLATE_ARG_LIST
#undef PFC_FUNCTOR_TYPE_LIST
#undef PFC_FUNCTOR_PROTO_ARG_LIST
#undef PFC_FUNCTOR_ARG_LIST
// functor 9 argument implementation
#define PFC_FUNCTOR_TEMPLATE_ARG_LIST typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8
#define PFC_FUNCTOR_TYPE_LIST A0, A1, A2, A3, A4, A5, A6, A7, A8
#define PFC_FUNCTOR_PROTO_ARG_LIST A0 a0_, A1 a1_, A2 a2_, A3 a3_, A4 a4_, A5 a5_, A6 a6_, A7 a7_, A8 a8_
#define PFC_FUNCTOR_ARG_LIST a0_, a1_, a2_, a3_, a4_, a5_, a6_, a7_, a8_
PFC_FUNCTOR_TMPL();
#undef PFC_FUNCTOR_TEMPLATE_ARG_LIST
#undef PFC_FUNCTOR_TYPE_LIST
#undef PFC_FUNCTOR_PROTO_ARG_LIST
#undef PFC_FUNCTOR_ARG_LIST
// functor 10 argument implementation
#define PFC_FUNCTOR_TEMPLATE_ARG_LIST typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
#define PFC_FUNCTOR_TYPE_LIST A0, A1, A2, A3, A4, A5, A6, A7, A8, A9
#define PFC_FUNCTOR_PROTO_ARG_LIST A0 a0_, A1 a1_, A2 a2_, A3 a3_, A4 a4_, A5 a5_, A6 a6_, A7 a7_, A8 a8_, A9 a9_
#define PFC_FUNCTOR_ARG_LIST a0_, a1_, a2_, a3_, a4_, a5_, a6_, a7_, a8_, a9_
PFC_FUNCTOR_TMPL();
#undef PFC_FUNCTOR_TEMPLATE_ARG_LIST
#undef PFC_FUNCTOR_TYPE_LIST
#undef PFC_FUNCTOR_PROTO_ARG_LIST
#undef PFC_FUNCTOR_ARG_LIST
//----
#undef PFC_FUNCTOR_TMPL
//----------------------------------------------------------------------------


//============================================================================
// mem_func/cmem_func
//============================================================================
template<typename R>
mem_func<R()>::mem_func()
  :m_mem_func(0)
{
}
//----

template<typename R>
template<class T>
mem_func<R()>::mem_func(R(T::*mf_)())
  :m_mem_func(reinterpret_cast<R(mem_func::*)()>(mf_))
{
}
//----

template<typename R>
template<class T>
R mem_func<R()>::operator()(T &v_) const
{
  PFC_ASSERT_PEDANTIC(m_mem_func!=0);
  return (v_.*reinterpret_cast<R(T::*)()>(m_mem_func))();
}
//----

template<typename R>
mem_func<R()>::operator bool() const
{
  return m_mem_func!=0;
}
//----------------------------------------------------------------------------

template<typename R>
cmem_func<R()>::cmem_func()
  :m_mem_func(0)
{
}
//----

template<typename R>
cmem_func<R()>::cmem_func(const mem_func<R()> &mf_)
  :m_mem_func(reinterpret_cast<R(cmem_func::*)()>(mf_.m_mem_func))
{
}
//----

template<typename R>
template<class T>
cmem_func<R()>::cmem_func(R(T::*mf_)() const)
  :m_mem_func(reinterpret_cast<R(cmem_func::*)() const>(mf_))
{
}
//----

template<typename R>
template<class T>
R cmem_func<R()>::operator()(const T &v_) const
{
  PFC_ASSERT_PEDANTIC(m_mem_func!=0);
  return (v_.*reinterpret_cast<R(T::*)() const>(m_mem_func))();
}
//----

template<typename R>
cmem_func<R()>::operator bool() const
{
  return m_mem_func!=0;
}
//----------------------------------------------------------------------------

template<class T, typename R>
PFC_INLINE mem_func<R()> make_mem_func(R(T::*mf_)())
{
  return mem_func<R()>(mf_);
}
//----

template<class T, typename R>
PFC_INLINE cmem_func<R()> make_mem_func(R(T::*mf_)() const)
{
  return cmem_func<R()>(mf_);
}
//----------------------------------------------------------------------------

#define PFC_MEM_FUNC_TMPL(type_list__, proto_arg_list__, cproto_arg_list__, arg_list__)\
  template<typename R, PFC_MEM_FUNC_ARG>\
  class mem_func<R type_list__>\
  {\
  public:\
    PFC_INLINE mem_func()                                            :m_mem_func(0) {}\
    template<class T> PFC_INLINE mem_func(R(T::*mf_)type_list__)     :m_mem_func(reinterpret_cast<R(mem_func::*)type_list__>(mf_)) {}\
    template<class T> inline R operator()proto_arg_list__ const      {PFC_ASSERT_PEDANTIC(m_mem_func!=0); return (v_.*reinterpret_cast<R(T::*)type_list__>(m_mem_func))arg_list__;}\
    PFC_INLINE operator bool() const                                 {return m_mem_func!=0;}\
  private:\
    friend class cmem_func<R type_list__>;\
    R(mem_func::*m_mem_func)type_list__;\
  };\
  template<typename R, PFC_MEM_FUNC_ARG>\
  class cmem_func<R type_list__>\
  {\
  public:\
    PFC_INLINE cmem_func()                                               :m_mem_func(0) {}\
    PFC_INLINE cmem_func(const mem_func<R type_list__> &mf_)             :m_mem_func(reinterpret_cast<R(cmem_func::*)type_list__ const>(mf_.m_mem_func)) {}\
    template<class T> PFC_INLINE cmem_func(R(T::*mf_)type_list__ const)  :m_mem_func(reinterpret_cast<R(cmem_func::*)type_list__ const>(mf_)) {}\
    template<class T> inline R operator()cproto_arg_list__ const         {PFC_ASSERT_PEDANTIC(m_mem_func!=0); return (v_.*reinterpret_cast<R(T::*)type_list__ const>(m_mem_func))arg_list__;}\
    PFC_INLINE operator bool() const                                     {return m_mem_func!=0;}\
  private:\
    R(cmem_func::*m_mem_func)type_list__ const;\
  };\
  template<class T, typename R, PFC_MEM_FUNC_ARG> PFC_INLINE  mem_func<R type_list__> make_mem_func(R(T::*mf_)type_list__)        {return mem_func<R type_list__>(mf_);}\
  template<class T, typename R, PFC_MEM_FUNC_ARG> PFC_INLINE cmem_func<R type_list__> make_mem_func(R(T::*mf_)type_list__ const)  {return cmem_func<R type_list__>(mf_);}
//----

#define PFC_MEM_FUNC_ARG typename A0
PFC_MEM_FUNC_TMPL((A0), (T &v_, A0 a0_), (const T &v_, A0 a0_), (a0_));
#undef PFC_MEM_FUNC_ARG
#define PFC_MEM_FUNC_ARG typename A0, typename A1
PFC_MEM_FUNC_TMPL((A0, A1), (T &v_, A0 a0_, A1 a1_), (const T &v_, A0 a0_, A1 a1_), (a0_, a1_));
#undef PFC_MEM_FUNC_ARG
#define PFC_MEM_FUNC_ARG typename A0, typename A1, typename A2
PFC_MEM_FUNC_TMPL((A0, A1, A2), (T &v_, A0 a0_, A1 a1_, A2 a2_), (const T &v_, A0 a0_, A1 a1_, A2 a2_), (a0_, a1_, a2_));
#undef PFC_MEM_FUNC_ARG
#define PFC_MEM_FUNC_ARG typename A0, typename A1, typename A2, typename A3
PFC_MEM_FUNC_TMPL((A0, A1, A2, A3), (T &v_, A0 a0_, A1 a1_, A2 a2_, A3 a3_), (const T &v_, A0 a0_, A1 a1_, A2 a2_, A3 a3_), (a0_, a1_, a2_, a3_));
#undef PFC_MEM_FUNC_ARG
#define PFC_MEM_FUNC_ARG typename A0, typename A1, typename A2, typename A3, typename A4
PFC_MEM_FUNC_TMPL((A0, A1, A2, A3, A4), (T &v_, A0 a0_, A1 a1_, A2 a2_, A3 a3_, A4 a4_), (const T &v_, A0 a0_, A1 a1_, A2 a2_, A3 a3_, A4 a4_), (a0_, a1_, a2_, a3_, a4_));
#undef PFC_MEM_FUNC_ARG
#define PFC_MEM_FUNC_ARG typename A0, typename A1, typename A2, typename A3, typename A4, typename A5
PFC_MEM_FUNC_TMPL((A0, A1, A2, A3, A4, A5), (T &v_, A0 a0_, A1 a1_, A2 a2_, A3 a3_, A4 a4_, A5 a5_), (const T &v_, A0 a0_, A1 a1_, A2 a2_, A3 a3_, A4 a4_, A5 a5_), (a0_, a1_, a2_, a3_, a4_, a5_));
#undef PFC_MEM_FUNC_ARG
#define PFC_MEM_FUNC_ARG typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6
PFC_MEM_FUNC_TMPL((A0, A1, A2, A3, A4, A5, A6), (T &v_, A0 a0_, A1 a1_, A2 a2_, A3 a3_, A4 a4_, A5 a5_, A6 a6_), (const T &v_, A0 a0_, A1 a1_, A2 a2_, A3 a3_, A4 a4_, A5 a5_, A6 a6_), (a0_, a1_, a2_, a3_, a4_, a5_, a6_));
#undef PFC_MEM_FUNC_ARG
#define PFC_MEM_FUNC_ARG typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7
PFC_MEM_FUNC_TMPL((A0, A1, A2, A3, A4, A5, A6, A7), (T &v_, A0 a0_, A1 a1_, A2 a2_, A3 a3_, A4 a4_, A5 a5_, A6 a6_, A7 a7_), (const T &v_, A0 a0_, A1 a1_, A2 a2_, A3 a3_, A4 a4_, A5 a5_, A6 a6_, A7 a7_), (a0_, a1_, a2_, a3_, a4_, a5_, a6_, a7_));
#undef PFC_MEM_FUNC_ARG
#define PFC_MEM_FUNC_ARG typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8
PFC_MEM_FUNC_TMPL((A0, A1, A2, A3, A4, A5, A6, A7, A8), (T &v_, A0 a0_, A1 a1_, A2 a2_, A3 a3_, A4 a4_, A5 a5_, A6 a6_, A7 a7_, A8 a8_), (const T &v_, A0 a0_, A1 a1_, A2 a2_, A3 a3_, A4 a4_, A5 a5_, A6 a6_, A7 a7_, A8 a8_), (a0_, a1_, a2_, a3_, a4_, a5_, a6_, a7_, a8_));
#undef PFC_MEM_FUNC_ARG
#define PFC_MEM_FUNC_ARG typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
PFC_MEM_FUNC_TMPL((A0, A1, A2, A3, A4, A5, A6, A7, A8, A9), (T &v_, A0 a0_, A1 a1_, A2 a2_, A3 a3_, A4 a4_, A5 a5_, A6 a6_, A7 a7_, A8 a8_, A9 a9_), (const T &v_, A0 a0_, A1 a1_, A2 a2_, A3 a3_, A4 a4_, A5 a5_, A6 a6_, A7 a7_, A8 a8_, A9 a9_), (a0_, a1_, a2_, a3_, a4_, a5_, a6_, a7_, a8_, a9_));
#undef PFC_MEM_FUNC_ARG
#undef PFC_MEM_FUNC_TMPL
//----------------------------------------------------------------------------
