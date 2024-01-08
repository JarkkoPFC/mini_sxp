//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_VARIANT_H
#define PFC_CORE_VARIANT_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "class.h"
namespace pfc
{

// new
template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9> class variant;
template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9> class pod_variant;
template<class B, unsigned max_size=sizeof(B), unsigned align=ptr_size> class poly_variant;
template<class B, unsigned max_size=sizeof(B), unsigned align=ptr_size> class poly_pod_variant;
//----------------------------------------------------------------------------


//============================================================================
// variant
//============================================================================
template<typename T0,      typename T1=void, typename T2=void, typename T3=void, typename T4=void,
         typename T5=void, typename T6=void, typename T7=void, typename T8=void, typename T9=void>
class variant
{ PFC_MONO(variant) PFC_INTROSPEC_DECL;
public:
  template<typename T> struct find_type;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE variant();
  PFC_INLINE variant(const variant&);
  template<typename T> PFC_INLINE variant(const T&);
  template<typename T> PFC_INLINE variant(meta_type<T>);
  PFC_INLINE void operator=(const variant&);
  template<typename T> PFC_INLINE void operator=(const T&);
  template<typename T> PFC_INLINE void operator=(meta_type<T>);
  PFC_INLINE ~variant();
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE unsigned type_index() const;
  PFC_INLINE const void *data() const;
  #define PFC_VARIANT_TFS template<typename U, typename U0, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9>
  PFC_VARIANT_TFS friend U &type_set(variant<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9>&);
  PFC_VARIANT_TFS friend U &type_ref(variant<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9>&);
  PFC_VARIANT_TFS friend const U &type_ref(const variant<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9>&);
  PFC_VARIANT_TFS friend volatile U &type_ref(volatile variant<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9>&);
  PFC_VARIANT_TFS friend const volatile U &type_ref(const volatile variant<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9>&);
  PFC_VARIANT_TFS friend U *type_ptr(variant<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9>&);
  PFC_VARIANT_TFS friend const U *type_ptr(const variant<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9>&);
  PFC_VARIANT_TFS friend volatile U *type_ptr(volatile variant<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9>&);
  PFC_VARIANT_TFS friend const volatile U *type_ptr(const volatile variant<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9>&);
  #undef PFC_VARIANT_TFS
  //--------------------------------------------------------------------------

private:
  template<class PE, typename T> PFC_INLINE void read_value(PE&, const meta_type<T>&, uint8_t type_index_);
  template<class PE> PFC_INLINE void read_value(PE&, const meta_type<void>&, uint8_t type_index_);
  template<class PE, typename T> PFC_INLINE void write_value(PE&, const meta_type<T>&);
  template<class PE> PFC_INLINE void write_value(PE&, const meta_type<void>&);
  //--------------------------------------------------------------------------

  typedef meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> tarray_t;
  enum {max_size=meta_max<meta_sizeof<T0>::res, meta_sizeof<T1>::res,
                          meta_sizeof<T2>::res, meta_sizeof<T3>::res,
                          meta_sizeof<T4>::res, meta_sizeof<T5>::res,
                          meta_sizeof<T6>::res, meta_sizeof<T7>::res,
                          meta_sizeof<T8>::res, meta_sizeof<T9>::res>::res};
  enum {max_align=meta_max<meta_alignof<T0>::res, meta_alignof<T1>::res,
                           meta_alignof<T2>::res, meta_alignof<T3>::res,
                           meta_alignof<T4>::res, meta_alignof<T5>::res,
                           meta_alignof<T6>::res, meta_alignof<T7>::res,
                           meta_alignof<T8>::res, meta_alignof<T9>::res>::res};
  typedef typename meta_align_n<max_align>::res atype_t;
  //--------------------------------------------------------------------------

  struct structor {void(*copy_ctor)(void*, const void*); void(*dtor)(void*);};
  static const structor s_structors[];
  uint8_t m_type_index;
  atype_t m_data[(max_size+sizeof(atype_t)-1)/sizeof(atype_t)];
};
PFC_SET_TYPE_TRAIT_PARTIAL10(typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9,
                             variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>,
                             is_type_pod_move,
                             is_type_pod_move<T0>::res && is_type_pod_move<T1>::res && is_type_pod_move<T2>::res && is_type_pod_move<T3>::res && is_type_pod_move<T4>::res && is_type_pod_move<T5>::res && is_type_pod_move<T6>::res && is_type_pod_move<T7>::res && is_type_pod_move<T8>::res && is_type_pod_move<T9>::res);
//----------------------------------------------------------------------------

//============================================================================
// variant::find_type
//============================================================================
template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
template<typename T>
struct variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::find_type
{
  enum {res=tarray_t::template find<T>::res};
  PFC_STATIC_ASSERT_MSG(res!=-1, type_not_found_from_the_variant);
};
//----------------------------------------------------------------------------


//============================================================================
// pod_variant
//============================================================================
template<typename T0,      typename T1=void, typename T2=void, typename T3=void, typename T4=void,
         typename T5=void, typename T6=void, typename T7=void, typename T8=void, typename T9=void>
class pod_variant
{ PFC_MONO(pod_variant) PFC_INTROSPEC_DECL;
public:
  template<typename T> struct find_type;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE pod_variant();
  template<typename T> PFC_INLINE pod_variant(const T&);
  template<typename T> PFC_INLINE pod_variant(meta_type<T>);
  template<typename T> PFC_INLINE void operator=(const T&);
  template<typename T> PFC_INLINE void operator=(meta_type<T>);
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE unsigned type_index() const;
  PFC_INLINE const void *data() const;
  #define PFC_POD_VARIANT_TFS template<typename U, typename U0, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9>
  PFC_POD_VARIANT_TFS friend U &type_set(variant<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9>&);
  PFC_POD_VARIANT_TFS friend U &type_ref(pod_variant<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9>&);
  PFC_POD_VARIANT_TFS friend const U &type_ref(const pod_variant<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9>&);
  PFC_POD_VARIANT_TFS friend volatile U &type_ref(volatile pod_variant<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9>&);
  PFC_POD_VARIANT_TFS friend const volatile U &type_ref(const volatile pod_variant<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9>&);
  PFC_POD_VARIANT_TFS friend U *type_ptr(pod_variant<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9>&);
  PFC_POD_VARIANT_TFS friend const U *type_ptr(const pod_variant<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9>&);
  PFC_POD_VARIANT_TFS friend volatile U *type_ptr(volatile pod_variant<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9>&);
  PFC_POD_VARIANT_TFS friend const volatile U *type_ptr(const volatile pod_variant<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9>&);
  #undef PFC_POD_VARIANT_TFS
  //--------------------------------------------------------------------------

private:
  template<class PE, typename T> PFC_INLINE void read_value(PE&, const meta_type<T>&, uint8_t type_index_);
  template<class PE> PFC_INLINE void read_value(PE&, const meta_type<void>&, uint8_t type_index_);
  template<class PE, typename T> PFC_INLINE void write_value(PE&, const meta_type<T>&);
  template<class PE> PFC_INLINE void write_value(PE&, const meta_type<void>&);
  //--------------------------------------------------------------------------

  typedef meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> tarray_t;
  enum {max_size=meta_max<meta_sizeof<T0>::res, meta_sizeof<T1>::res,
                          meta_sizeof<T2>::res, meta_sizeof<T3>::res,
                          meta_sizeof<T4>::res, meta_sizeof<T5>::res,
                          meta_sizeof<T6>::res, meta_sizeof<T7>::res,
                          meta_sizeof<T8>::res, meta_sizeof<T9>::res>::res};
  enum {max_align=meta_max<meta_alignof<T0>::res, meta_alignof<T1>::res,
                           meta_alignof<T2>::res, meta_alignof<T3>::res,
                           meta_alignof<T4>::res, meta_alignof<T5>::res,
                           meta_alignof<T6>::res, meta_alignof<T7>::res,
                           meta_alignof<T8>::res, meta_alignof<T9>::res>::res};
  typedef typename meta_align_n<max_align>::res atype_t;
  //--------------------------------------------------------------------------

  uint8_t m_type_index;
  atype_t m_data[(max_size+sizeof(atype_t)-1)/sizeof(atype_t)];
};
PFC_SET_TYPE_TRAIT_PARTIAL10(typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9,
                             pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, is_type_pod, true);
//----------------------------------------------------------------------------

//============================================================================
// pod_variant::find_type
//============================================================================
template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
template<typename T>
struct pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::find_type
{
  enum {res=tarray_t::template find<T>::res};
  PFC_STATIC_ASSERT_MSG(res!=-1, type_not_found_from_the_variant);
};
//----------------------------------------------------------------------------


//============================================================================
// poly_variant
//============================================================================
template<class B, unsigned max_size, unsigned align>
class poly_variant
{ PFC_MONO(poly_variant) PFC_INTROSPEC_DECL;
public:
  // construction
  PFC_INLINE poly_variant();
  PFC_INLINE poly_variant(const poly_variant&);
  template<class C> PFC_INLINE poly_variant(const C&);
  template<class C> PFC_INLINE poly_variant(meta_type<C>);
  PFC_INLINE void operator=(const poly_variant&);
  template<class C> PFC_INLINE void operator=(const C&);
  template<class C> PFC_INLINE void operator=(meta_type<C>);
  PFC_INLINE void release();
  PFC_INLINE ~poly_variant();
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE bool is_initialized() const;
  PFC_INLINE const B *operator->() const;
  PFC_INLINE B *operator->();
  PFC_INLINE const B &operator*() const;
  PFC_INLINE B &operator*();
  #define PFC_POLY_VARIANT_TFS template<class C, class PVB, unsigned pv_max_size, unsigned pv_align>
  PFC_POLY_VARIANT_TFS friend C &type_set(poly_variant<PVB, pv_max_size, pv_align>&);
  PFC_POLY_VARIANT_TFS friend C &type_ref(poly_variant<PVB, pv_max_size, pv_align>&);
  PFC_POLY_VARIANT_TFS friend const C &type_ref(const poly_variant<PVB, pv_max_size, pv_align>&);
  PFC_POLY_VARIANT_TFS friend volatile C &type_ref(volatile poly_variant<PVB, pv_max_size, pv_align>&);
  PFC_POLY_VARIANT_TFS friend const volatile C &type_ref(const volatile poly_variant<PVB, pv_max_size, pv_align>&);
  PFC_POLY_VARIANT_TFS friend C *type_ptr(poly_variant<PVB, pv_max_size, pv_align>&);
  PFC_POLY_VARIANT_TFS friend const C *type_ptr(const poly_variant<PVB, pv_max_size, pv_align>&);
  PFC_POLY_VARIANT_TFS friend volatile C *type_ptr(volatile poly_variant<PVB, pv_max_size, pv_align>&);
  PFC_POLY_VARIANT_TFS friend const volatile C *type_ptr(const volatile poly_variant<PVB, pv_max_size, pv_align>&);
  #undef PFC_POLY_VARIANT_TFS
  //--------------------------------------------------------------------------

private:
  PFC_STATIC_ASSERT_MSG(is_type_poly<B>::res, base_class_must_be_polymorphic);
  PFC_STATIC_ASSERT_MSG(max_size>=sizeof(B), max_size_must_be_greater_or_equal_to_base_class_size);
  //--------------------------------------------------------------------------

  typedef typename meta_align_n<align>::res atype_t;
  bool m_is_initialized;
  atype_t m_data[(max_size+sizeof(atype_t)-1)/sizeof(atype_t)];
};
PFC_SET_TYPE_TRAIT_PARTIAL3(class B, unsigned max_size, unsigned align, poly_variant<B, max_size, align>, is_type_pod_def_ctor, true);
//----------------------------------------------------------------------------


//============================================================================
// poly_pod_variant
//============================================================================
template<class B, unsigned max_size, unsigned align>
class poly_pod_variant
{ PFC_MONO(poly_pod_variant) PFC_INTROSPEC_DECL;
public:
  // construction
  PFC_INLINE poly_pod_variant();
  template<class C> PFC_INLINE poly_pod_variant(const C&);
  template<class C> PFC_INLINE poly_pod_variant(meta_type<C>);
  template<class C> PFC_INLINE void operator=(const C&);
  template<class C> PFC_INLINE void operator=(meta_type<C>);
  PFC_INLINE void release();
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE bool is_initialized() const;
  PFC_INLINE const B *operator->() const;
  PFC_INLINE B *operator->();
  PFC_INLINE const B &operator*() const;
  PFC_INLINE B &operator*();
  #define PFC_POLY_POD_VARIANT_TFS template<class C, class PVB, unsigned pv_max_size, unsigned pv_align>
  PFC_POLY_POD_VARIANT_TFS friend C &type_set(poly_pod_variant<PVB, pv_max_size, pv_align>&);
  PFC_POLY_POD_VARIANT_TFS friend C &type_ref(poly_pod_variant<PVB, pv_max_size, pv_align>&);
  PFC_POLY_POD_VARIANT_TFS friend const C &type_ref(const poly_pod_variant<PVB, pv_max_size, pv_align>&);
  PFC_POLY_POD_VARIANT_TFS friend volatile C &type_ref(volatile poly_pod_variant<PVB, pv_max_size, pv_align>&);
  PFC_POLY_POD_VARIANT_TFS friend const volatile C &type_ref(const volatile poly_pod_variant<PVB, pv_max_size, pv_align>&);
  PFC_POLY_POD_VARIANT_TFS friend C *type_ptr(poly_pod_variant<PVB, pv_max_size, pv_align>&);
  PFC_POLY_POD_VARIANT_TFS friend const C *type_ptr(const poly_pod_variant<PVB, pv_max_size, pv_align>&);
  PFC_POLY_POD_VARIANT_TFS friend volatile C *type_ptr(volatile poly_pod_variant<PVB, pv_max_size, pv_align>&);
  PFC_POLY_POD_VARIANT_TFS friend const volatile C *type_ptr(const volatile poly_pod_variant<PVB, pv_max_size, pv_align>&);
  #undef PFC_POLY_POD_VARIANT_TFS
  //--------------------------------------------------------------------------

private:
  PFC_STATIC_ASSERT_MSG(is_type_poly<B>::res, base_class_must_be_polymorphic);
  PFC_STATIC_ASSERT_MSG(max_size>=sizeof(B), max_size_must_be_greater_or_equal_to_base_class_size);
  //--------------------------------------------------------------------------

  typedef typename meta_align_n<align>::res atype_t;
  bool m_is_initialized;
  atype_t m_data[(max_size+sizeof(atype_t)-1)/sizeof(atype_t)];
};
PFC_SET_TYPE_TRAIT_PARTIAL3(class B, unsigned max_size, unsigned align, poly_pod_variant<B, max_size, align>, is_type_pod, true);
//----------------------------------------------------------------------------

//============================================================================
#include "variant.inl"
} // namespace pfc
#endif
