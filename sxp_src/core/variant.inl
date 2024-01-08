//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// variant
//============================================================================
namespace priv
{
  template<typename T>
  PFC_INLINE void variant_copy_ctor(void *dst_, const void *src_)
  {
    PFC_PNEW(dst_)T(*static_cast<const T*>(src_));
  }
  //----

  template<>
  PFC_INLINE void variant_copy_ctor<void>(void *dst_, const void *src_)
  {
    PFC_ERROR("Variant type doesn't have copy-constructor\r\n");
  }
  //----

  template<typename T>
  PFC_INLINE void variant_dtor(void *dst_)
  {
    ((T*)dst_)->~T();
  }
  //----

  template<>
  PFC_INLINE void variant_dtor<void>(void *dst_)
  {
    PFC_ERROR("Variant type doesn't have destructor\r\n");
  }
} // namespace priv
//----------------------------------------------------------------------------

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
const typename variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::structor variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::s_structors[]=
{
  {priv::variant_copy_ctor<typename meta_if<is_type_copyable<T0>::res, T0, void>::res>, priv::variant_dtor<T0>},
  {priv::variant_copy_ctor<typename meta_if<is_type_copyable<T1>::res, T1, void>::res>, priv::variant_dtor<T1>},
  {priv::variant_copy_ctor<typename meta_if<is_type_copyable<T2>::res, T2, void>::res>, priv::variant_dtor<T2>},
  {priv::variant_copy_ctor<typename meta_if<is_type_copyable<T3>::res, T3, void>::res>, priv::variant_dtor<T3>},
  {priv::variant_copy_ctor<typename meta_if<is_type_copyable<T4>::res, T4, void>::res>, priv::variant_dtor<T4>},
  {priv::variant_copy_ctor<typename meta_if<is_type_copyable<T5>::res, T5, void>::res>, priv::variant_dtor<T5>},
  {priv::variant_copy_ctor<typename meta_if<is_type_copyable<T6>::res, T6, void>::res>, priv::variant_dtor<T6>},
  {priv::variant_copy_ctor<typename meta_if<is_type_copyable<T7>::res, T7, void>::res>, priv::variant_dtor<T7>},
  {priv::variant_copy_ctor<typename meta_if<is_type_copyable<T8>::res, T8, void>::res>, priv::variant_dtor<T8>},
  {priv::variant_copy_ctor<typename meta_if<is_type_copyable<T9>::res, T9, void>::res>, priv::variant_dtor<T9>},
};
//----------------------------------------------------------------------------

PFC_INTROSPEC_INL_TDEF10(typename T0, typename T1, typename T2, typename T3, typename T4,
                         typename T5, typename T6, typename T7, typename T8, typename T9,
                         variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>)
{
  PFC_CUSTOM_STREAMING(0);
  switch(unsigned(PE::pe_type))
  {
    case penum_input:
    {
      // read type ID and switch to proper reading function
      uint8_t type_index;
      pe_.var(type_index);
      switch(type_index)
      {
        case 0: read_value(pe_, meta_type<T0>(), type_index); break;
        case 1: read_value(pe_, meta_type<T1>(), type_index); break;
        case 2: read_value(pe_, meta_type<T2>(), type_index); break;
        case 3: read_value(pe_, meta_type<T3>(), type_index); break;
        case 4: read_value(pe_, meta_type<T4>(), type_index); break;
        case 5: read_value(pe_, meta_type<T5>(), type_index); break;
        case 6: read_value(pe_, meta_type<T6>(), type_index); break;
        case 7: read_value(pe_, meta_type<T7>(), type_index); break;
        case 8: read_value(pe_, meta_type<T8>(), type_index); break;
        case 9: read_value(pe_, meta_type<T9>(), type_index); break;
      }
    } break;

    case penum_output:
    case penum_display:
    {
      // save type ID and switch to proper writing function
      pe_.var(m_type_index);
      switch(m_type_index)
      {
        case 0: write_value(pe_, meta_type<T0>()); break;
        case 1: write_value(pe_, meta_type<T1>()); break;
        case 2: write_value(pe_, meta_type<T2>()); break;
        case 3: write_value(pe_, meta_type<T3>()); break;
        case 4: write_value(pe_, meta_type<T4>()); break;
        case 5: write_value(pe_, meta_type<T5>()); break;
        case 6: write_value(pe_, meta_type<T6>()); break;
        case 7: write_value(pe_, meta_type<T7>()); break;
        case 8: write_value(pe_, meta_type<T8>()); break;
        case 9: write_value(pe_, meta_type<T9>()); break;
      }
    } break;
  }
}
//----------------------------------------------------------------------------

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::variant()
  :m_type_index(0)
{
  PFC_PNEW(m_data)T0;
}
//----

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::variant(const variant &v_)
  :m_type_index(v_.m_type_index)
{
  s_structors[m_type_index].copy_ctor(m_data, v_.m_data);
}
//----

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
template<typename T>
variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::variant(const T &v_)
{
  enum {id=tarray_t::template find<T>::res};
  PFC_STATIC_ASSERT_MSG(id!=-1, assigned_type_is_not_one_of_the_variant_types);
  m_type_index=uint8_t(id);
  PFC_PNEW(m_data)T(v_);
}
//----

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
template<typename T>
variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::variant(meta_type<T>)
{
  enum {id=tarray_t::template find<T>::res};
  PFC_STATIC_ASSERT_MSG(id!=-1, assigned_type_is_not_one_of_the_variant_types);
  m_type_index=uint8_t(id);
  PFC_PNEW(m_data)T;
}
//----

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
void variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::operator=(const variant &v_)
{
  if(this!=&v_)
  {
    s_structors[m_type_index].dtor(m_data);
    m_type_index=v_.m_type_index;
    s_structors[m_type_index].copy_ctor(m_data, v_.m_data);
  }
}
//----

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
template<typename T>
void variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::operator=(const T &v_)
{
  enum {id=tarray_t::template find<T>::res};
  PFC_STATIC_ASSERT_MSG(id!=-1, assigned_type_is_not_one_of_the_variant_types);
  s_structors[m_type_index].dtor(m_data);
  m_type_index=uint8_t(id);
  PFC_PNEW(m_data)T(v_);
}
//----

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
template<typename T>
void variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::operator=(meta_type<T>)
{
  enum {id=tarray_t::template find<T>::res};
  PFC_STATIC_ASSERT_MSG(id!=-1, assigned_type_is_not_one_of_the_variant_types);
  s_structors[m_type_index].dtor(m_data);
  m_type_index=uint8_t(id);
  PFC_PNEW(m_data)T;
}
//----

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::~variant()
{
  s_structors[m_type_index].dtor(m_data);
}
//----------------------------------------------------------------------------

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
unsigned variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::type_index() const
{
  return m_type_index;
}
//----

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
const void *variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::data() const
{
  return m_data;
}
//----

template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4,
                     typename T5, typename T6, typename T7, typename T8, typename T9>
T &type_set(variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &v_)
{
  enum {id=meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::template find<T>::res};
  PFC_STATIC_ASSERT_MSG(id!=-1, assigned_type_is_not_one_of_the_variant_types);
  v_.s_structors[v_.m_type_index].dtor(v_.m_data);
  v_.m_type_index=uint8_t(id);
  PFC_PNEW(v_.m_data)T;
  return *reinterpret_cast<T*>(v_.m_data);
}
//----

template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4,
                     typename T5, typename T6, typename T7, typename T8, typename T9>
T &type_ref(variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &v_)
{
  enum {id=meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::template find<T>::res};
  PFC_STATIC_ASSERT_MSG(id!=-1, queried_type_is_not_one_of_the_variant_types);
  PFC_ASSERT_PEDANTIC_MSG(id==v_.m_type_index, ("Queried type \"%s\" is not currently active\r\n", typeid(T).name()));
  return *reinterpret_cast<T*>(v_.m_data);
}
//----

template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4,
                     typename T5, typename T6, typename T7, typename T8, typename T9>
const T &type_ref(const variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &v_)
{
  enum {id=meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::template find<typename remove_cv<T>::res>::res};
  PFC_STATIC_ASSERT_MSG(id!=-1, queried_type_is_not_one_of_the_variant_types);
  PFC_ASSERT_PEDANTIC_MSG(id==v_.m_type_index, ("Queried type \"%s\" is not currently active\r\n", typeid(T).name()));
  return *reinterpret_cast<const T*>(v_.m_data);
}
//----

template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4,
                     typename T5, typename T6, typename T7, typename T8, typename T9>
volatile T &type_ref(volatile variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &v_)
{
  enum {id=meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::template find<typename remove_cv<T>::res>::res};
  PFC_STATIC_ASSERT_MSG(id!=-1, queried_type_is_not_one_of_the_variant_types);
  PFC_ASSERT_PEDANTIC_MSG(id==v_.m_type_index, ("Queried type \"%s\" is not currently active\r\n", typeid(T).name()));
  return *reinterpret_cast<volatile T*>(v_.m_data);
}
//----

template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4,
                     typename T5, typename T6, typename T7, typename T8, typename T9>
const volatile T &type_ref(const volatile variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &v_)
{
  enum {id=meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::template find<typename remove_cv<T>::res>::res};
  PFC_STATIC_ASSERT_MSG(id!=-1, queried_type_is_not_one_of_the_variant_types);
  PFC_ASSERT_PEDANTIC_MSG(id==v_.m_type_index, ("Queried type \"%s\" is not currently active\r\n", typeid(T).name()));
  return *reinterpret_cast<const volatile T*>(v_.m_data);
}
//----

template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4,
                     typename T5, typename T6, typename T7, typename T8, typename T9>
T *type_ptr(variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &v_)
{
  enum {id=meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::template find<T>::res};
  PFC_STATIC_ASSERT_MSG(id!=-1, queried_type_is_not_one_of_the_variant_types);
  return id==v_.m_type_index?reinterpret_cast<T*>(v_.m_data):0;
}
//----

template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4,
                     typename T5, typename T6, typename T7, typename T8, typename T9>
const T *type_ptr(const variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &v_)
{
  enum {id=meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::template find<typename remove_cv<T>::res>::res};
  PFC_STATIC_ASSERT_MSG(id!=-1, queried_type_is_not_one_of_the_variant_types);
  return id==v_.m_type_index?reinterpret_cast<const T*>(v_.m_data):0;
}
//----

template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4,
                     typename T5, typename T6, typename T7, typename T8, typename T9>
volatile T *type_ptr(volatile variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &v_)
{
  enum {id=meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::template find<typename remove_cv<T>::res>::res};
  PFC_STATIC_ASSERT_MSG(id!=-1, queried_type_is_not_one_of_the_variant_types);
  return id==v_.m_type_index?reinterpret_cast<volatile T*>(v_.m_data):0;
}
//----

template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4,
                     typename T5, typename T6, typename T7, typename T8, typename T9>
const volatile T *type_ptr(const volatile variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &v_)
{
  enum {id=meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::template find<typename remove_cv<T>::res>::res};
  PFC_STATIC_ASSERT_MSG(id!=-1, queried_type_is_not_one_of_the_variant_types);
  return id==v_.m_type_index?reinterpret_cast<const volatile T*>(v_.m_data):0;
}
//----------------------------------------------------------------------------

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
template<class PE, typename T>
void variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::read_value(PE &pe_, const meta_type<T>&, uint8_t)
{
  // set given type and read the value
  operator=(meta_type<T>());
  pe_.var(*reinterpret_cast<T*>(m_data));
}
//----

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
template<class PE>
void variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::read_value(PE &pe_, const meta_type<void>&, uint8_t type_index_)
{
  PFC_ERRORF("No type defined for given type ID (%i)\r\n", type_index_);
}
//----

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
template<class PE, typename T>
void variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::write_value(PE &pe_, const meta_type<T>&)
{
  // write given value type
  pe_.var(*reinterpret_cast<T*>(m_data));
}
//----

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
template<class PE>
void variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::write_value(PE &pe_, const meta_type<void>&)
{
  PFC_ERRORF("Invalid variant type ID (%i)\r\n", m_type_index);
}
//----------------------------------------------------------------------------


//============================================================================
// pod_variant
//============================================================================
PFC_INTROSPEC_INL_TDEF10(typename T0, typename T1, typename T2, typename T3, typename T4,
                         typename T5, typename T6, typename T7, typename T8, typename T9,
                         pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>)
{
  PFC_CUSTOM_STREAMING(0);
  switch(unsigned(PE::pe_type))
  {
    case penum_input:
    {
      // read type ID and switch to proper reading function
      uint8_t type_index;
      pe_.var(type_index);
      switch(type_index)
      {
        case 0: read_value(pe_, meta_type<T0>(), type_index); break;
        case 1: read_value(pe_, meta_type<T1>(), type_index); break;
        case 2: read_value(pe_, meta_type<T2>(), type_index); break;
        case 3: read_value(pe_, meta_type<T3>(), type_index); break;
        case 4: read_value(pe_, meta_type<T4>(), type_index); break;
        case 5: read_value(pe_, meta_type<T5>(), type_index); break;
        case 6: read_value(pe_, meta_type<T6>(), type_index); break;
        case 7: read_value(pe_, meta_type<T7>(), type_index); break;
        case 8: read_value(pe_, meta_type<T8>(), type_index); break;
        case 9: read_value(pe_, meta_type<T9>(), type_index); break;
      }
    } break;

    case penum_output:
    case penum_display:
    {
      // save type ID and switch to proper writing function
      pe_.var(m_type_index);
      switch(m_type_index)
      {
        case 0: write_value(pe_, meta_type<T0>()); break;
        case 1: write_value(pe_, meta_type<T1>()); break;
        case 2: write_value(pe_, meta_type<T2>()); break;
        case 3: write_value(pe_, meta_type<T3>()); break;
        case 4: write_value(pe_, meta_type<T4>()); break;
        case 5: write_value(pe_, meta_type<T5>()); break;
        case 6: write_value(pe_, meta_type<T6>()); break;
        case 7: write_value(pe_, meta_type<T7>()); break;
        case 8: write_value(pe_, meta_type<T8>()); break;
        case 9: write_value(pe_, meta_type<T9>()); break;
      }
    } break;
  }
}
//----------------------------------------------------------------------------

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::pod_variant()
  :m_type_index(0)
{
  PFC_PNEW(m_data)T0;
}
//----

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
template<typename T>
pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::pod_variant(const T &v_)
{
  enum {id=tarray_t::template find<T>::res};
  PFC_STATIC_ASSERT_MSG(id!=-1, assigned_type_is_not_one_of_the_variant_types);
  m_type_index=uint8_t(id);
  mem_copy(m_data, &v_, sizeof(T));
}
//----

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
template<typename T>
pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::pod_variant(meta_type<T>)
{
  enum {id=tarray_t::template find<T>::res};
  PFC_STATIC_ASSERT_MSG(id!=-1, assigned_type_is_not_one_of_the_variant_types);
  m_type_index=uint8_t(id);
  PFC_PNEW(m_data)T;
}
//----

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
template<typename T>
void pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::operator=(const T &v_)
{
  enum {id=tarray_t::template find<T>::res};
  PFC_STATIC_ASSERT_MSG(id!=-1, assigned_type_is_not_one_of_the_variant_types);
  m_type_index=uint8_t(id);
  mem_copy(m_data, &v_, sizeof(T));
}
//----

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
template<typename T>
void pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::operator=(meta_type<T>)
{
  enum {id=tarray_t::template find<T>::res};
  PFC_STATIC_ASSERT_MSG(id!=-1, assigned_type_is_not_one_of_the_variant_types);
  m_type_index=uint8_t(id);
  PFC_PNEW(m_data)T;
}
//----------------------------------------------------------------------------

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
unsigned pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::type_index() const
{
  return m_type_index;
}
//----

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
const void *pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::data() const
{
  return m_data;
}
//----

template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4,
                     typename T5, typename T6, typename T7, typename T8, typename T9>
T &type_set(pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &v_)
{
  enum {id=meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::template find<T>::res};
  PFC_STATIC_ASSERT_MSG(id!=-1, assigned_type_is_not_one_of_the_variant_types);
  v_.m_type_index=uint8_t(id);
  PFC_PNEW(v_.m_data)T;
  return *reinterpret_cast<T*>(v_.m_data);
}
//----

template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4,
                     typename T5, typename T6, typename T7, typename T8, typename T9>
T &type_ref(pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &v_)
{
  enum {id=meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::template find<T>::res};
  PFC_STATIC_ASSERT_MSG(id!=-1, queried_type_is_not_one_of_the_variant_types);
  PFC_ASSERT_PEDANTIC_MSG(id==v_.m_type_index, ("Queried type \"%s\" is not currently active\r\n", typeid(T).name()));
  return *reinterpret_cast<T*>(v_.m_data);
}
//----

template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4,
                     typename T5, typename T6, typename T7, typename T8, typename T9>
const T &type_ref(const pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &v_)
{
  enum {id=meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::template find<typename remove_cv<T>::res>::res};
  PFC_STATIC_ASSERT_MSG(id!=-1, queried_type_is_not_one_of_the_variant_types);
  PFC_ASSERT_PEDANTIC_MSG(id==v_.m_type_index, ("Queried type \"%s\" is not currently active\r\n", typeid(T).name()));
  return *reinterpret_cast<const T*>(v_.m_data);
}
//----

template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4,
                     typename T5, typename T6, typename T7, typename T8, typename T9>
volatile T &type_ref(volatile pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &v_)
{
  enum {id=meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::template find<typename remove_cv<T>::res>::res};
  PFC_STATIC_ASSERT_MSG(id!=-1, queried_type_is_not_one_of_the_variant_types);
  PFC_ASSERT_PEDANTIC_MSG(id==v_.m_type_index, ("Queried type \"%s\" is not currently active\r\n", typeid(T).name()));
  return *reinterpret_cast<volatile T*>(v_.m_data);
}
//----

template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4,
                     typename T5, typename T6, typename T7, typename T8, typename T9>
const volatile T &type_ref(const volatile pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &v_)
{
  enum {id=meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::template find<typename remove_cv<T>::res>::res};
  PFC_STATIC_ASSERT_MSG(id!=-1, queried_type_is_not_one_of_the_variant_types);
  PFC_ASSERT_PEDANTIC_MSG(id==v_.m_type_index, ("Queried type \"%s\" is not currently active\r\n", typeid(T).name()));
  return *reinterpret_cast<const volatile T*>(v_.m_data);
}
//----

template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4,
                     typename T5, typename T6, typename T7, typename T8, typename T9>
T *type_ptr(pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &v_)
{
  enum {id=meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::template find<T>::res};
  PFC_STATIC_ASSERT_MSG(id!=-1, queried_type_is_not_one_of_the_variant_types);
  return id==v_.m_type_index?reinterpret_cast<T*>(v_.m_data):0;
}
//----

template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4,
                     typename T5, typename T6, typename T7, typename T8, typename T9>
const T *type_ptr(const pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &v_)
{
  enum {id=meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::template find<typename remove_cv<T>::res>::res};
  PFC_STATIC_ASSERT_MSG(id!=-1, queried_type_is_not_one_of_the_variant_types);
  return id==v_.m_type_index?reinterpret_cast<const T*>(v_.m_data):0;
}
//----

template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4,
                     typename T5, typename T6, typename T7, typename T8, typename T9>
volatile T *type_ptr(volatile pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &v_)
{
  enum {id=meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::template find<typename remove_cv<T>::res>::res};
  PFC_STATIC_ASSERT_MSG(id!=-1, queried_type_is_not_one_of_the_variant_types);
  return id==v_.m_type_index?reinterpret_cast<volatile T*>(v_.m_data):0;
}
//----

template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4,
                     typename T5, typename T6, typename T7, typename T8, typename T9>
const volatile T *type_ptr(const volatile pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> &v_)
{
  enum {id=meta_type_array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::template find<typename remove_cv<T>::res>::res};
  PFC_STATIC_ASSERT_MSG(id!=-1, queried_type_is_not_one_of_the_variant_types);
  return id==v_.m_type_index?reinterpret_cast<const volatile T*>(v_.m_data):0;
}
//----------------------------------------------------------------------------

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
template<class PE, typename T>
void pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::read_value(PE &pe_, const meta_type<T>&, uint8_t)
{
  // set given type and read the value
  operator=(meta_type<T>());
  pe_.var(*reinterpret_cast<T*>(m_data));
}
//----

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
template<class PE>
void pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::read_value(PE &pe_, const meta_type<void>&, uint8_t type_index_)
{
  PFC_ERRORF("No type defined for given type ID (%i)\r\n", type_index_);
}
//----

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
template<class PE, typename T>
void pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::write_value(PE &pe_, const meta_type<T>&)
{
  // write given value type
  pe_.var(*reinterpret_cast<T*>(m_data));
}
//----

template<typename T0, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
template<class PE>
void pod_variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::write_value(PE &pe_, const meta_type<void>&)
{
  PFC_ERRORF("Invalid variant type ID (%i)\r\n", m_type_index);
}
//----------------------------------------------------------------------------


//============================================================================
// poly_variant
//============================================================================
PFC_INTROSPEC_INL_TDEF3(class B, unsigned max_size, unsigned align, poly_variant<B, max_size, align>)
{
  PFC_STATIC_ASSERT_MSG(is_type_crep<B>::res, no_polymorphic_introspection_defined_for_the_base_class);
  PFC_CUSTOM_STREAMING(0);
  switch(unsigned(PE::pe_type))
  {
    case penum_input:
    {
      B *obj=(B*)m_data;
      if(m_is_initialized)
        obj->~B();
      pe_.var(m_is_initialized);
      if(m_is_initialized)
      {
        // read class name
        uint8_t cname_size;
        pe_.var(cname_size);
        char cname[256];
        pe_.data(cname, cname_size);
        cname[cname_size]=0;

        // instantiate and deserialize class contents
        const class_factory_base *factory=B::crep().find_factory(cname);
        PFC_ASSERT_MSG(factory, ("No class factory found for instantiating class \"%s\"\r\n", cname));
        factory->create(m_data);
        enum_props(pe_, *obj);
      }
    } break;

    case penum_output:
    case penum_display:
    {
      pe_.var(m_is_initialized, 0, "is_initialized");
      if(m_is_initialized)
      {
        // write registered class name and contents
        B *obj=(B*)m_data;
        const char *reg_cname=obj->registered_object_typename();
        PFC_ASSERT_MSG(reg_cname, ("Class type \"%s\" not registered\r\n", obj->object_typename()));
        uint8_t cname_size=(uint8_t)str_size(reg_cname);
        pe_.var(cname_size);
        pe_.data((void*)reg_cname, cname_size);
        enum_props(pe_, *obj);
      }
    } break;
  }
}
//----------------------------------------------------------------------------

template<class B, unsigned max_size, unsigned align>
poly_variant<B, max_size, align>::poly_variant()
  :m_is_initialized(false)
{
}
//----

template<class B, unsigned max_size, unsigned align>
poly_variant<B, max_size, align>::poly_variant(const poly_variant &pv_)
  :m_is_initialized(true)
{
  // copy-construct poly-variant object from another
  reinterpret_cast<const B*>(pv_.m_data)->clone(reinterpret_cast<B*>(m_data));
}
//----

template<class B, unsigned max_size, unsigned align>
template<class C>
poly_variant<B, max_size, align>::poly_variant(const C &v_)
  :m_is_initialized(true)
{
  // construct poly-variant object from a value
  PFC_STATIC_ASSERT_MSG((is_type_derived<C, B>::res), class_must_be_derived_from_base_class);
  PFC_STATIC_ASSERT_MSG(sizeof(C)<=max_size, object_is_too_large_to_fit_into_the_poly_variant_object);
  PFC_STATIC_ASSERT_MSG(meta_alignof<C>::res<=align, poly_variant_object_doesnt_comply_alignment_requirements_of_the_class);
  PFC_PNEW(m_data)C(v_);
}
//----

template<class B, unsigned max_size, unsigned align>
template<class C>
poly_variant<B, max_size, align>::poly_variant(meta_type<C>)
  :m_is_initialized(true)
{
  // construct poly-variant object from a value
  PFC_STATIC_ASSERT_MSG((is_type_derived<C, B>::res), class_must_be_derived_from_base_class);
  PFC_STATIC_ASSERT_MSG(sizeof(C)<=max_size, object_is_too_large_to_fit_into_the_poly_variant_object);
  PFC_STATIC_ASSERT_MSG(meta_alignof<C>::res<=align, poly_variant_object_doesnt_comply_alignment_requirements_of_the_class);
  PFC_PNEW(m_data)C;
}
//----

template<class B, unsigned max_size, unsigned align>
void poly_variant<B, max_size, align>::operator=(const poly_variant &pv_)
{
  // destruct old poly-variant object and construct new one from another
  if(this!=&pv_)
  {
    if(m_is_initialized)
      reinterpret_cast<B*>(m_data)->~B();
    if(pv_.m_is_initialized)
      reinterpret_cast<B*>(pv_.m_data)->clone(reinterpret_cast<B*>(m_data));
    m_is_initialized=pv_.m_is_initialized;
  }
}
//----

template<class B, unsigned max_size, unsigned align>
template<class C>
void poly_variant<B, max_size, align>::operator=(const C &v_)
{
  // destruct old poly-variant object and construct new one from a value
  PFC_STATIC_ASSERT_MSG((is_type_derived<C, B>::res), class_must_be_derived_from_base_class);
  PFC_STATIC_ASSERT_MSG(sizeof(C)<=max_size, object_is_too_large_to_fit_into_the_poly_variant_object);
  PFC_STATIC_ASSERT_MSG(meta_alignof<C>::res<=align, poly_variant_object_doesnt_comply_alignment_requirements_of_the_object);
  if(m_is_initialized)
    reinterpret_cast<B*>(m_data)->~B();
  PFC_PNEW(m_data)C(v_);
  m_is_initialized=true;
}
//----

template<class B, unsigned max_size, unsigned align>
template<class C>
void poly_variant<B, max_size, align>::operator=(meta_type<C>)
{
  // destruct old poly-variant object and construct new one from a value
  PFC_STATIC_ASSERT_MSG((is_type_derived<C, B>::res), class_must_be_derived_from_base_class);
  PFC_STATIC_ASSERT_MSG(sizeof(C)<=max_size, object_is_too_large_to_fit_into_the_poly_variant_object);
  PFC_STATIC_ASSERT_MSG(meta_alignof<C>::res<=align, poly_variant_object_doesnt_comply_alignment_requirements_of_the_object);
  if(m_is_initialized)
    reinterpret_cast<B*>(m_data)->~B();
  PFC_PNEW(m_data)C;
  m_is_initialized=true;
}
//----

template<class B, unsigned max_size, unsigned align>
void poly_variant<B, max_size, align>::release()
{
  // destruct the object
  if(m_is_initialized)
  {
    reinterpret_cast<B*>(m_data)->~B();
    m_is_initialized=false;
  }
}
//----

template<class B, unsigned max_size, unsigned align>
poly_variant<B, max_size, align>::~poly_variant()
{
  // destruct the object
  if(m_is_initialized)
    reinterpret_cast<B*>(m_data)->~B();
}
//----------------------------------------------------------------------------

template<class B, unsigned max_size, unsigned align>
bool poly_variant<B, max_size, align>::is_initialized() const
{
  return m_is_initialized;
}
//----

template<class B, unsigned max_size, unsigned align>
const B *poly_variant<B, max_size, align>::operator->() const
{
  PFC_ASSERT_PEDANTIC(m_is_initialized)
  return reinterpret_cast<const B*>(m_data);
}
//----

template<class B, unsigned max_size, unsigned align>
B *poly_variant<B, max_size, align>::operator->()
{
  PFC_ASSERT_PEDANTIC(m_is_initialized)
  return reinterpret_cast<B*>(m_data);
}
//----

template<class B, unsigned max_size, unsigned align>
const B &poly_variant<B, max_size, align>::operator*() const
{
  PFC_ASSERT_PEDANTIC(m_is_initialized)
  return *reinterpret_cast<const B*>(m_data);
}
//----

template<class B, unsigned max_size, unsigned align>
B &poly_variant<B, max_size, align>::operator*()
{
  PFC_ASSERT_PEDANTIC(m_is_initialized)
  return *reinterpret_cast<B*>(m_data);
}
//----

template<class C, class B, unsigned max_size, unsigned align>
C &type_set(poly_variant<B, max_size, align> &pv_)
{
  // construct poly-variant object from a value
  PFC_STATIC_ASSERT_MSG((is_type_derived<C, B>::res), set_class_must_be_derived_from_the_base_class);
  PFC_STATIC_ASSERT_MSG(sizeof(C)<=max_size, object_is_too_large_to_fit_into_the_poly_variant_object);
  PFC_STATIC_ASSERT_MSG(meta_alignof<C>::res<=align, poly_variant_object_doesnt_comply_alignment_requirements_of_the_class);
  if(pv_.m_is_initialized)
    reinterpret_cast<B*>(pv_.m_data)->~B();
  PFC_PNEW(pv_.m_data)C;
  pv_.m_is_initialized=true;
  return *(C*)pv_.m_data;
}
//----

template<class C, class B, unsigned max_size, unsigned align>
C &type_ref(poly_variant<B, max_size, align> &pv_)
{
  PFC_STATIC_ASSERT_MSG((is_type_derived<C, B>::res), referred_class_must_be_derived_from_the_base_class);
  PFC_ASSERT_PEDANTIC(pv_.m_is_initialized);
  return safe_cast<C&>(*(B*)pv_.m_data);
}
//----

template<class C, class B, unsigned max_size, unsigned align>
const C &type_ref(const poly_variant<B, max_size, align> &pv_)
{
  PFC_STATIC_ASSERT_MSG((is_type_derived<C, B>::res), referred_class_must_be_derived_from_the_base_class);
  PFC_ASSERT_PEDANTIC(pv_.m_is_initialized);
  return safe_cast<C&>(*(B*)pv_.m_data);
}
//----

template<class C, class B, unsigned max_size, unsigned align>
volatile C &type_ref(volatile poly_variant<B, max_size, align> &pv_)
{
  PFC_STATIC_ASSERT_MSG((is_type_derived<C, B>::res), referred_class_must_be_derived_from_the_base_class);
  PFC_ASSERT_PEDANTIC(pv_.m_is_initialized);
  return safe_cast<C&>(*(B*)pv_.m_data);
}
//----

template<class C, class B, unsigned max_size, unsigned align>
const volatile C &type_ref(const volatile poly_variant<B, max_size, align> &pv_)
{
  PFC_STATIC_ASSERT_MSG((is_type_derived<C, B>::res), referred_class_must_be_derived_from_the_base_class);
  PFC_ASSERT_PEDANTIC(pv_.m_is_initialized);
  return safe_cast<C&>(*(B*)pv_.m_data);
}
//----

template<class C, class B, unsigned max_size, unsigned align>
C *type_ptr(poly_variant<B, max_size, align> &pv_)
{
  PFC_STATIC_ASSERT_MSG((is_type_derived<C, B>::res), referred_class_must_be_derived_from_the_base_class);
  PFC_ASSERT_PEDANTIC(pv_.m_is_initialized);
  return down_cast<C*>((B*)pv_.m_data);
}
//----

template<class C, class B, unsigned max_size, unsigned align>
const C *type_ptr(const poly_variant<B, max_size, align> &pv_)
{
  PFC_STATIC_ASSERT_MSG((is_type_derived<C, B>::res), referred_class_must_be_derived_from_the_base_class);
  PFC_ASSERT_PEDANTIC(pv_.m_is_initialized);
  return down_cast<C*>((B*)pv_.m_data);
}
//----

template<class C, class B, unsigned max_size, unsigned align>
volatile C *type_ptr(volatile poly_variant<B, max_size, align> &pv_)
{
  PFC_STATIC_ASSERT_MSG((is_type_derived<C, B>::res), referred_class_must_be_derived_from_the_base_class);
  PFC_ASSERT_PEDANTIC(pv_.m_is_initialized);
  return down_cast<C*>((B*)pv_.m_data);
}
//----

template<class C, class B, unsigned max_size, unsigned align>
const volatile C *type_ptr(const volatile poly_variant<B, max_size, align> &pv_)
{
  PFC_STATIC_ASSERT_MSG((is_type_derived<C, B>::res), referred_class_must_be_derived_from_the_base_class);
  PFC_ASSERT_PEDANTIC(pv_.m_is_initialized);
  return down_cast<C*>((B*)pv_.m_data);
}
//----------------------------------------------------------------------------


//============================================================================
// poly_pod_variant
//============================================================================
PFC_INTROSPEC_INL_TDEF3(class B, unsigned max_size, unsigned align, poly_pod_variant<B, max_size, align>)
{
  PFC_STATIC_ASSERT_MSG(is_type_crep<B>::res, no_polymorphic_introspection_defined_for_the_base_class);
  PFC_CUSTOM_STREAMING(0);
  switch(unsigned(PE::pe_type))
  {
    case penum_input:
    {
      pe_.var(m_is_initialized);
      if(m_is_initialized)
      {
        // read class name
        uint8_t cname_size;
        pe_.var(cname_size);
        char cname[256];
        pe_.data(cname, cname_size);
        cname[cname_size]=0;

        // instantiate and deserialize class contents
        const class_factory_base *factory=B::crep().find_factory(cname);
        PFC_ASSERT_MSG(factory, ("No class factory found for instantiating class \"%s\"\r\n", cname));
        factory->create(m_data);
        enum_props(pe_, *(B*)m_data);
      }
    } break;

    case penum_output:
    case penum_display:
    {
      pe_.var(m_is_initialized, 0, "is_initialized");
      if(m_is_initialized)
      {
        // write registered class name and contents
        B *obj=(B*)m_data;
        const char *reg_cname=obj->registered_object_typename();
        PFC_ASSERT_MSG(reg_cname, ("Class type \"%s\" not registered\r\n", obj->object_typename()));
        uint8_t cname_size=(uint8_t)str_size(reg_cname);
        pe_.var(cname_size);
        pe_.data((void*)reg_cname, cname_size);
        enum_props(pe_, *obj);
      }
    } break;
  }
}
//----------------------------------------------------------------------------

template<class B, unsigned max_size, unsigned align>
poly_pod_variant<B, max_size, align>::poly_pod_variant()
  :m_is_initialized(false)
{
}
//----

template<class B, unsigned max_size, unsigned align>
template<class C>
poly_pod_variant<B, max_size, align>::poly_pod_variant(const C &v_)
  :m_is_initialized(true)
{
  // construct poly-variant object from a value
  PFC_STATIC_ASSERT_MSG((is_type_derived<C, B>::res), class_must_be_derived_from_base_class);
  PFC_STATIC_ASSERT_MSG(sizeof(C)<=max_size, object_is_too_large_to_fit_into_the_poly_variant_object);
  PFC_STATIC_ASSERT_MSG(meta_alignof<C>::res<=align, poly_variant_object_doesnt_comply_alignment_requirements_of_the_class);
  mem_copy(m_data, &v_, sizeof(C));
}
//----

template<class B, unsigned max_size, unsigned align>
template<class C>
poly_pod_variant<B, max_size, align>::poly_pod_variant(meta_type<C>)
  :m_is_initialized(true)
{
  // construct poly-variant object from a value
  PFC_STATIC_ASSERT_MSG((is_type_derived<C, B>::res), class_must_be_derived_from_base_class);
  PFC_STATIC_ASSERT_MSG(sizeof(C)<=max_size, object_is_too_large_to_fit_into_the_poly_variant_object);
  PFC_STATIC_ASSERT_MSG(meta_alignof<C>::res<=align, poly_variant_object_doesnt_comply_alignment_requirements_of_the_class);
  PFC_PNEW(m_data)C;
}
//----

template<class B, unsigned max_size, unsigned align>
template<class C>
void poly_pod_variant<B, max_size, align>::operator=(const C &v_)
{
  // construct poly-variant object from a value
  PFC_STATIC_ASSERT_MSG((is_type_derived<C, B>::res), class_must_be_derived_from_base_class);
  PFC_STATIC_ASSERT_MSG(sizeof(C)<=max_size, object_is_too_large_to_fit_into_the_poly_variant_object);
  PFC_STATIC_ASSERT_MSG(meta_alignof<C>::res<=align, poly_variant_object_doesnt_comply_alignment_requirements_of_the_object);
  mem_copy(m_data, &v_, sizeof(C));
  m_is_initialized=true;
}
//----

template<class B, unsigned max_size, unsigned align>
template<class C>
void poly_pod_variant<B, max_size, align>::operator=(meta_type<C>)
{
  // construct poly-variant object from a value
  PFC_STATIC_ASSERT_MSG((is_type_derived<C, B>::res), class_must_be_derived_from_base_class);
  PFC_STATIC_ASSERT_MSG(sizeof(C)<=max_size, object_is_too_large_to_fit_into_the_poly_variant_object);
  PFC_STATIC_ASSERT_MSG(meta_alignof<C>::res<=align, poly_variant_object_doesnt_comply_alignment_requirements_of_the_object);
  PFC_PNEW(m_data)C;
  m_is_initialized=true;
}
//----

template<class B, unsigned max_size, unsigned align>
void poly_pod_variant<B, max_size, align>::release()
{
  m_is_initialized=false;
}
//----------------------------------------------------------------------------

template<class B, unsigned max_size, unsigned align>
bool poly_pod_variant<B, max_size, align>::is_initialized() const
{
  return m_is_initialized;
}
//----

template<class B, unsigned max_size, unsigned align>
const B *poly_pod_variant<B, max_size, align>::operator->() const
{
  PFC_ASSERT_PEDANTIC(m_is_initialized);
  return reinterpret_cast<const B*>(m_data);
}
//----

template<class B, unsigned max_size, unsigned align>
B *poly_pod_variant<B, max_size, align>::operator->()
{
  PFC_ASSERT_PEDANTIC(m_is_initialized);
  return reinterpret_cast<B*>(m_data);
}
//----

template<class B, unsigned max_size, unsigned align>
const B &poly_pod_variant<B, max_size, align>::operator*() const
{
  PFC_ASSERT_PEDANTIC(m_is_initialized);
  return *reinterpret_cast<const B*>(m_data);
}
//----

template<class B, unsigned max_size, unsigned align>
B &poly_pod_variant<B, max_size, align>::operator*()
{
  PFC_ASSERT_PEDANTIC(m_is_initialized);
  return *reinterpret_cast<B*>(m_data);
}
//----

template<class C, class B, unsigned max_size, unsigned align>
C &type_set(poly_pod_variant<B, max_size, align> &pv_)
{
  // construct poly-POD variant object from a value
  PFC_STATIC_ASSERT_MSG((is_type_derived<C, B>::res), set_class_must_be_derived_from_the_base_class);
  PFC_STATIC_ASSERT_MSG(sizeof(C)<=max_size, object_is_too_large_to_fit_into_the_poly_pod_variant_object);
  PFC_STATIC_ASSERT_MSG(meta_alignof<C>::res<=align, poly_pod_variant_object_doesnt_comply_alignment_requirements_of_the_class);
  PFC_PNEW(pv_.m_data)C;
  pv_.m_is_initialized=true;
  return *(C*)pv_.m_data;
}
//----

template<class C, class B, unsigned max_size, unsigned align>
C &type_ref(poly_pod_variant<B, max_size, align> &pv_)
{
  PFC_STATIC_ASSERT_MSG((is_type_derived<C, B>::res), referred_class_must_be_derived_from_the_base_class);
  PFC_ASSERT_PEDANTIC(pv_.m_is_initialized);
  return safe_cast<C&>(*(B*)pv_.m_data);
}
//----

template<class C, class B, unsigned max_size, unsigned align>
const C &type_ref(const poly_pod_variant<B, max_size, align> &pv_)
{
  PFC_STATIC_ASSERT_MSG((is_type_derived<C, B>::res), referred_class_must_be_derived_from_the_base_class);
  PFC_ASSERT_PEDANTIC(pv_.m_is_initialized);
  return safe_cast<C&>(*(B*)pv_.m_data);
}
//----

template<class C, class B, unsigned max_size, unsigned align>
volatile C &type_ref(volatile poly_pod_variant<B, max_size, align> &pv_)
{
  PFC_STATIC_ASSERT_MSG((is_type_derived<C, B>::res), referred_class_must_be_derived_from_the_base_class);
  PFC_ASSERT_PEDANTIC(pv_.m_is_initialized);
  return safe_cast<C&>(*(B*)pv_.m_data);
}
//----

template<class C, class B, unsigned max_size, unsigned align>
const volatile C &type_ref(const volatile poly_pod_variant<B, max_size, align> &pv_)
{
  PFC_STATIC_ASSERT_MSG((is_type_derived<C, B>::res), referred_class_must_be_derived_from_the_base_class);
  PFC_ASSERT_PEDANTIC(pv_.m_is_initialized);
  return safe_cast<C&>(*(B*)pv_.m_data);
}
//----

template<class C, class B, unsigned max_size, unsigned align>
C *type_ptr(poly_pod_variant<B, max_size, align> &pv_)
{
  PFC_STATIC_ASSERT_MSG((is_type_derived<C, B>::res), referred_class_must_be_derived_from_the_base_class);
  PFC_ASSERT_PEDANTIC(pv_.m_is_initialized);
  return down_cast<C*>((B*)pv_.m_data);
}
//----

template<class C, class B, unsigned max_size, unsigned align>
const C *type_ptr(const poly_pod_variant<B, max_size, align> &pv_)
{
  PFC_STATIC_ASSERT_MSG((is_type_derived<C, B>::res), referred_class_must_be_derived_from_the_base_class);
  PFC_ASSERT_PEDANTIC(pv_.m_is_initialized);
  return down_cast<C*>((B*)pv_.m_data);
}
//----

template<class C, class B, unsigned max_size, unsigned align>
volatile C *type_ptr(volatile poly_pod_variant<B, max_size, align> &pv_)
{
  PFC_STATIC_ASSERT_MSG((is_type_derived<C, B>::res), referred_class_must_be_derived_from_the_base_class);
  PFC_ASSERT_PEDANTIC(pv_.m_is_initialized);
  return down_cast<C*>((B*)pv_.m_data);
}
//----

template<class C, class B, unsigned max_size, unsigned align>
const volatile C *type_ptr(const volatile poly_pod_variant<B, max_size, align> &pv_)
{
  PFC_STATIC_ASSERT_MSG((is_type_derived<C, B>::res), referred_class_must_be_derived_from_the_base_class);
  PFC_ASSERT_PEDANTIC(pv_.m_is_initialized);
  return down_cast<C*>((B*)pv_.m_data);
}
//----------------------------------------------------------------------------
