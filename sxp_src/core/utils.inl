//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// swap
//============================================================================
namespace priv
{
  template<typename T>
  static PFC_INLINE void swap_impl(T &v0_, T &v1_, meta_case<0> is_type_non_class_)
  {
    // swap values
    T t=v0_;
    v0_=v1_;
    v1_=t;
  }
  //----

  template<typename T>
  static PFC_INLINE void swap_impl(T &v0_, T &v1_, meta_case<1> is_type_pod_move_)
  {
    // swap values
    char tmp[sizeof(T)];
    mem_copy(&tmp, &v0_, sizeof(T));
    mem_copy(&v0_, &v1_, sizeof(T));
    mem_copy(&v1_, &tmp, sizeof(T));
  }
  //----

  template<typename T>
  static PFC_INLINE void swap_impl(T &v0_, T &v1_, meta_case<2> default_)
  {
    // swap values
    T v=v0_;
    v0_.~T();
    PFC_PNEW(&v0_)T(v1_);
    v1_.~T();
    PFC_PNEW(&v1_)T(v);
  }
} // namespace priv
//----

template<typename T>
PFC_INLINE void swap(T &v0_, T &v1_)
{
  priv::swap_impl(v0_, v1_, meta_case<!is_type_class<T>::res?0:is_type_pod_move<T>::res?1:2>());
}
//----

template<typename T>
PFC_INLINE void swap(T *s0_, T *s1_, usize_t count_)
{
  // swap values between arrays
  if(count_)
  {
    T *end=s0_+count_;
    do
    {
      priv::swap_impl(*s0_++, *s1_++, meta_case<!is_type_class<T>::res?0:is_type_pod_move<T>::res?1:2>());
    } while(s0_<end);
  }
}
//----------------------------------------------------------------------------


//============================================================================
// swap_bytes
//============================================================================
namespace priv
{
  static PFC_INLINE uint8_t swap_bytes(const void *p_, meta_int<1>)
  {
    return *reinterpret_cast<const uint8_t*>(p_);
  }
  //----

  static PFC_INLINE uint16_t swap_bytes(const void *p_, meta_int<2>)
  {
#ifdef PFC_INTRINSIC_BSWAP16
    uint16_t v;
    PFC_INTRINSIC_BSWAP16(v, p_);
    return v;
#else
    uint16_t v=*reinterpret_cast<const uint16_t*>(p_);
    return v<<8|v>>8;
#endif
  }
  //----

  static PFC_INLINE uint32_t swap_bytes(const void *p_, meta_int<4>)
  {
#ifdef PFC_INTRINSIC_BSWAP32
    uint32_t v;
    PFC_INTRINSIC_BSWAP32(v, p_);
    return v;
#else
    uint32_t v=*reinterpret_cast<const uint32_t*>(p_);
    return (v<<24)|(v<<8&0xff0000)|(v>>8&0xff00)|(v>>24);
#endif
  }
  //----

  static PFC_INLINE uint64_t swap_bytes(const void *p_, meta_int<8>)
  {
#ifdef PFC_INTRINSIC_BSWAP64
    uint64_t v;
    PFC_INTRINSIC_BSWAP64(v, p_);
    return v;
#else
    uint64_t v=*reinterpret_cast<const uint64_t*>(p_);
    return  (v<<56)|(v>>56)|(v<<40&PFC_CONST_UINT64(0xff000000000000))
           |(v>>40&0xff00)|(v<<24&PFC_CONST_UINT64(0xff0000000000))
           |(v>>24&0xff0000)|(v<<8&PFC_CONST_UINT64(0xff00000000))
           |(v>>8&0xff000000);
#endif
  }
  //----

  static PFC_INLINE uint128_t swap_bytes(const void *p_, meta_int<16>)
  {
    uint128_t v;
#ifdef PFC_INTRINSIC_BSWAP64
    PFC_INTRINSIC_BSWAP64(v.lo, &reinterpret_cast<const uint128_t*>(p_)->hi);
    PFC_INTRINSIC_BSWAP64(v.hi, &reinterpret_cast<const uint128_t*>(p_)->lo);
#else
    uint64_t vt=reinterpret_cast<const uint128_t*>(p_)->hi;
    v.lo= (vt<<56)|(vt>>56)|(vt<<40&PFC_CONST_UINT64(0xff000000000000))
         |(vt>>40&0xff00)|(vt<<24&PFC_CONST_UINT64(0xff0000000000))
         |(vt>>24&0xff0000)|(vt<<8&PFC_CONST_UINT64(0xff00000000))
         |(vt>>8&0xff000000);
    vt=reinterpret_cast<const uint128_t*>(p_)->lo;
    v.hi= (vt<<56)|(vt>>56)|(vt<<40&PFC_CONST_UINT64(0xff000000000000))
         |(vt>>40&0xff00)|(vt<<24&PFC_CONST_UINT64(0xff0000000000))
         |(vt>>24&0xff0000)|(vt<<8&PFC_CONST_UINT64(0xff00000000))
         |(vt>>8&0xff000000);
#endif
    return v;
  }
  //----

  static PFC_INLINE void swap_bytes(void *p_, usize_t count_, meta_int<1>)
  {
    return;
  }
  //----

  static PFC_INLINE void swap_bytes(void *p_, usize_t count_, meta_int<2>)
  {
    // swap bytes for an array of values
    uint16_t *p=(uint16_t*)p_, *end=p+count_;
    if(count_)
      do
      {
#ifdef PFC_INTRINSIC_BSWAP16
        PFC_INTRINSIC_BSWAP16(*p, p);
#else
        uint16_t v=*p;
        *p=v<<8 | v>>8;
#endif
        ++p;
      } while(p!=end);
  }
  //----

  static PFC_INLINE void swap_bytes(void *p_, usize_t count_, meta_int<4>)
  {
    // swap bytes for an array of values
    uint32_t *p=(uint32_t*)p_, *end=p+count_;
    if(count_)
      do
      {
#ifdef PFC_INTRINSIC_BSWAP32
        PFC_INTRINSIC_BSWAP32(*p, p);
#else
        uint32_t v=*p;
        *p=(v<<24) | (v<<8&0xff0000) | (v>>8&0xff00) | (v>>24);
#endif
        ++p;
      } while(p!=end);
  }
  //----

  static PFC_INLINE void swap_bytes(void *p_, usize_t count_, meta_int<8>)
  {
    // swap bytes for an array of values
    uint64_t *p=(uint64_t*)p_, *end=p+count_;
    if(count_)
      do
      {
#ifdef PFC_INTRINSIC_BSWAP64
        PFC_INTRINSIC_BSWAP64(*p, p);
#else
        uint64_t v=*p;
        *p= (v<<56)|(v>>56)|(v<<40&PFC_CONST_UINT64(0xff000000000000))
           |(v>>40&0xff00)|(v<<24&PFC_CONST_UINT64(0xff0000000000))
           |(v>>24&0xff0000)|(v<<8&PFC_CONST_UINT64(0xff00000000))
           |(v>>8&0xff000000);
#endif
        ++p;
      } while(p!=end);
  }
  //----

  static PFC_INLINE void swap_bytes(void *p_, usize_t count_, meta_int<16>)
  {
    // swap bytes for an array of values
    uint128_t *p=(uint128_t*)p_, *end=p+count_;
    if(count_)
      do
      {
#ifdef PFC_INTRINSIC_BSWAP64
        uint64_t lo;
        PFC_INTRINSIC_BSWAP64(lo, &p->lo);
        PFC_INTRINSIC_BSWAP64(p->lo, &p->hi);
        p->hi=lo;
#else
        uint64_t lo=p->lo;
        lo= (lo<<56)|(lo>>56)|(lo<<40&PFC_CONST_UINT64(0xff000000000000))
           |(lo>>40&0xff00)|(lo<<24&PFC_CONST_UINT64(0xff0000000000))
           |(lo>>24&0xff0000)|(lo<<8&PFC_CONST_UINT64(0xff00000000))
           |(lo>>8&0xff000000);
        uint64_t hi=p->hi;
        p->hi=lo;
        hi= (hi<<56)|(hi>>56)|(hi<<40&PFC_CONST_UINT64(0xff000000000000))
           |(hi>>40&0xff00)|(hi<<24&PFC_CONST_UINT64(0xff0000000000))
           |(hi>>24&0xff0000)|(hi<<8&PFC_CONST_UINT64(0xff00000000))
           |(hi>>8&0xff000000);
        p->lo=hi;
#endif
        ++p;
      } while(p!=end);
  }
} // namespace priv
//----------------------------------------------------------------------------

template<typename T>
PFC_INLINE T swap_bytes(T v_)
{
  PFC_STATIC_ASSERT_MSG(!is_type_class<T>::res, unable_to_swap_bytes_of_a_class_type);
  return raw_cast<T>(priv::swap_bytes(&v_, meta_int<sizeof(T)>()));
}
//----

template<typename T>
PFC_INLINE void swap_bytes(T *a_, usize_t count_)
{
  PFC_STATIC_ASSERT_MSG(!is_type_class<T>::res, unable_to_swap_bytes_of_a_class_type);
  priv::swap_bytes(a_, count_, meta_int<sizeof(T)>());
}
//----------------------------------------------------------------------------


//============================================================================
// to_little/big_endian
//============================================================================
template<typename T>
PFC_INLINE T to_little_endian(T v_)
{
#if PFC_BIG_ENDIAN==0
  return v_;
#else
  return raw_cast<T>(priv::swap_bytes(&v_, meta_int<sizeof(T)>()));
#endif
}
//----

template<typename T>
PFC_INLINE T to_big_endian(T v_)
{
#if PFC_BIG_ENDIAN==0
  return raw_cast<T>(priv::swap_bytes(&v_, meta_int<sizeof(T)>()));
#else
  return v_;
#endif
}
//----------------------------------------------------------------------------


//============================================================================
// array construction/destruction
//============================================================================
namespace priv
{
  //==========================================================================
  // default_construct
  //==========================================================================
  template<typename T>
  PFC_INLINE void default_construct(T *dst_, usize_t count_, meta_bool<true> is_type_pod_def_ctor_)
  {
    mem_zero(dst_, sizeof(T)*count_);
  }
  //----

  template<typename T>
  PFC_INLINE void default_construct(T *dst_, usize_t count_, meta_bool<false> is_type_pod_def_ctor_)
  {
    // default construct an array of values
    if(count_)
    {
      eh_array_dtor<T> v(dst_, dst_);
      T *end=dst_+count_;
      do
      {
        PFC_PNEW(v.dst)T;
      } while(++v.dst!=end);
      v.begin=0;
    }
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  // copy_construct
  //==========================================================================
  template<typename T>
  PFC_INLINE void copy_construct(T *dst_, const T *src_, usize_t count_, meta_bool<true> is_type_pod_copy_)
  {
    mem_copy(dst_, src_, sizeof(T)*count_);
  }
  //----

  template<typename T>
  PFC_INLINE void copy_construct(T *dst_, const T *src_, usize_t count_, meta_bool<false> is_type_pod_copy_)
  {
    // copy construct an array of values from an array
    if(count_)
    {
      eh_array_dtor<T> v(dst_, dst_);
      T *end=dst_+count_;
      do
      {
        PFC_PNEW(v.dst)T(*src_++);
      } while(++v.dst!=end);
      v.begin=0;
    }
  }
  //----

  template<typename T>
  PFC_INLINE void copy_construct(T *dst_, const T &v_, usize_t count_, meta_bool<true> is_type_pod_copy_)
  {
    // copy construct an array of values from an value
    if(count_)
    {
      T *end=dst_+count_;
      do
      {
        PFC_PNEW(dst_)T(v_);
      } while(++dst_!=end);
    }
  }
  //----

  template<typename T>
  PFC_INLINE void copy_construct(T *dst_, const T &v_, usize_t count_, meta_bool<false> is_type_pod_copy_)
  {
    // copy construct an array of values from an value
    if(count_)
    {
      eh_array_dtor<T> v(dst_, dst_);
      T *end=dst_+count_;
      do
      {
        PFC_PNEW(v.dst)T(v_);
      } while(++v.dst!=end);
      v.begin=0;
    }
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  // move_construct
  //==========================================================================
  template<typename T>
  PFC_INLINE void move_construct(T *dst_, T *src_, usize_t count_, meta_bool<true> is_type_pod_move_)
  {
    mem_move(dst_, src_, sizeof(T)*count_);
  }
  //----

  template<typename T>
  PFC_INLINE void move_construct(T *dst_, T *src_, usize_t count_, meta_bool<false> is_type_pod_move_)
  {
    // move construct an array of values
    if(count_)
    {
      if(dst_<src_)
      {
        // move items starting from the begin of the array
        T *end=src_+count_;
        do
        {
          PFC_PNEW(dst_++)T(*src_);
          src_->~T();
        } while(++src_!=end);
      }
      else
      {
        // move items starting from the end of the array
        T *end=src_;
        dst_+=count_;
        src_+=count_;
        do
        {
          PFC_PNEW(--dst_)T(*--src_);
          src_->~T();
        } while(src_!=end);
      }
    }
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  // rotate_sequence_left
  //==========================================================================
  template<typename T>
  PFC_INLINE void rotate_sequence_left(T *first_, T *last_, meta_bool<true> is_type_pod_move_)
  {
    // rotate sequence of move-POD values to the left
    char tmp[sizeof(T)];
    mem_copy(&tmp, first_, sizeof(T));
    mem_move(first_, first_+1, usize_t(last_-first_)*sizeof(T));
    mem_copy(last_, &tmp, sizeof(T));
  }
  //----

  template<typename T>
  PFC_INLINE void rotate_sequence_left(T *first_, T *last_, meta_bool<false> is_type_pod_move_)
  {
    // rotate sequence of values to the left
    T tmp(*first_);
    first_->~T();
    while(first_!=last_)
    {
      PFC_PNEW(first_)T(*(first_+1));
      (++first_)->~T();
    }
    PFC_PNEW(last_)T(tmp);
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  // rotate_sequence_right
  //==========================================================================
  template<typename T>
  PFC_INLINE void rotate_sequence_right(T *first_, T *last_, meta_bool<true> is_type_pod_move_)
  {
    // rotate sequence of move-POD values to the right
    char tmp[sizeof(T)];
    mem_copy(&tmp, last_, sizeof(T));
    mem_move(first_+1, first_, usize_t(last_-first_)*sizeof(T));
    mem_copy(first_, &tmp, sizeof(T));
  }
  //----

  template<typename T>
  PFC_INLINE void rotate_sequence_right(T *first_, T *last_, meta_bool<false> is_type_pod_move_)
  {
    // rotate sequence of values to the right
    T tmp(*last_);
    last_->~T();
    while(last_!=first_)
    {
      PFC_PNEW(last_)T(*(last_-1));
      (--last_)->~T();
    }
    PFC_PNEW(last_)T(tmp);
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  // destruct
  //==========================================================================
  PFC_INLINE void destruct(void*, usize_t, meta_bool<true> is_type_pod_dtor_)
  {
  }
  //----

  template<typename T>
  PFC_INLINE void destruct(T *dst_, usize_t count_, meta_bool<false> is_type_pod_dtor_)
  {
    // destruct an array of values
    if(count_)
    {
      T *end=dst_+count_;
      do
      {
        dst_->~T();
      } while(++dst_!=end);
    }
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  // reverse_default_construct
  //==========================================================================
  template<typename T>
  PFC_INLINE void reverse_default_construct(T *dst_, usize_t count_, meta_bool<true> is_type_pod_def_ctor_)
  {
    mem_zero(dst_, sizeof(T)*count_);
  }
  //----

  template<typename T>
  PFC_INLINE void reverse_default_construct(T *dst_, usize_t count_, meta_bool<false> is_type_pod_def_ctor_)
  {
    // default construct an array of values in reverse order
    if(count_)
    {
      dst_+=count_-1;
      eh_array_dtor<T> v(dst_, dst_);
      T *end=dst_-count_;
      do
      {
        PFC_PNEW(v.dst)T;
      } while(--v.dst!=end);
      v.begin=0;
    }
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  // reverse_copy_construct
  //==========================================================================
  template<typename T>
  PFC_INLINE void reverse_copy_construct(T *dst_, const T *src_, usize_t count_, meta_bool<true> is_type_pod_copy_)
  {
    // copy construct an array of values from an array in reverse order
    if(count_)
    {
      dst_+=count_-1;
      T *end=dst_-count_;
      do
      {
        PFC_PNEW(dst_)T(*src_++);
      } while(--dst_!=end);
    }
  }
  //----

  template<typename T>
  PFC_INLINE void reverse_copy_construct(T *dst_, const T *src_, usize_t count_, meta_bool<false> is_type_pod_copy_)
  {
    // copy construct an array of values from an array in reverse order
    if(count_)
    {
      dst_+=count_-1;
      eh_array_dtor<T> v(dst_, dst_);
      T *end=dst_-count_;
      do
      {
        PFC_PNEW(v.dst)T(*src_++);
      } while(--v.dst!=end);
      v.begin=0;
    }
  }
  //----

  template<typename T>
  PFC_INLINE void reverse_copy_construct(T *dst_, const T &v_, usize_t count_, meta_bool<true> is_type_pod_copy_)
  {
    // copy construct an array of value from an value in reverse order
    if(count_)
    {
      dst_+=count_-1;
      T *end=dst_-count_;
      do
      {
        PFC_PNEW(dst_)T(v_);
      } while(--dst_!=end);
    }
  }
  //----

  template<typename T>
  PFC_INLINE void reverse_copy_construct(T *dst_, const T &v_, usize_t count_, meta_bool<false> is_type_pod_copy_)
  {
    // copy construct an array of value from an value in reverse order
    if(count_)
    {
      dst_+=count_-1;
      eh_array_dtor<T> v(dst_, dst_);
      T *end=dst_-count_;
      do
      {
        PFC_PNEW(v.dst)T(v_);
      } while(--v.dst!=end);
      v.begin=0;
    }
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  // reverse_move_construct
  //==========================================================================
  template<typename T>
  PFC_INLINE void reverse_move_construct(T *dst_, T *src_, usize_t count_, meta_bool<true> is_type_pod_move_)
  {
    // move construct an array of values in reverse order
    if(count_)
    {
      dst_+=count_;
      T *end=src_+count_;
      do
      {
        PFC_PNEW(--dst_)T(*src_);
      } while(++src_!=end);
    }
  }
  //----

  template<typename T>
  PFC_INLINE void reverse_move_construct(T *dst_, T *src_, usize_t count_, meta_bool<false> is_type_pod_move_)
  {
    // move construct an array of values in reverse order
    if(count_)
    {
      dst_+=count_;
      T *end=src_+count_;
      do
      {
        PFC_PNEW(--dst_)T(*src_);
        src_->~T();
      } while(++src_!=end);
    }
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  // reverse_destruct
  //==========================================================================
  PFC_INLINE void reverse_destruct(void*, usize_t, meta_bool<true> is_type_pod_dtor_)
  {
  }
  //----

  template<typename T>
  PFC_INLINE void reverse_destruct(T *dst_, usize_t count_, meta_bool<false> is_type_pod_dtor_)
  {
    // destruct an array of values in reverse order
    if(count_)
    {
      T *end=dst_;
      dst_+=count_;
      do
      {
        (--dst_)->~T();
      } while(dst_!=end);
    }
  }
  //--------------------------------------------------------------------------
} // namespace priv
//----------------------------------------------------------------------------

template<typename T>
PFC_INLINE void default_construct(T *dst_, usize_t count_)
{
  // default construct an array
  priv::default_construct(dst_, count_, meta_bool<is_type_pod_def_ctor<T>::res>());
}
//----

template<typename T>
PFC_INLINE void copy_construct(T *dst_, const T *src_, usize_t count_)
{
  // copy construct an array from an array
  PFC_ASSERT_PEDANTIC_MSG(dst_+count_<=src_ || src_+count_<=dst_, ("Memory regions may not overlap\r\n"));
  priv::copy_construct(dst_, src_, count_, meta_bool<is_type_pod_copy<T>::res>());
}
//----

template<typename T>
PFC_INLINE void copy_construct(T *dst_, const T &v_, usize_t count_)
{
  // copy construct an array from a value
  PFC_ASSERT_PEDANTIC_MSG(dst_+count_<=&v_ || dst_>&v_, ("Target array overwrites the source value\r\n"));
  if(count_)
    priv::copy_construct(dst_, v_, count_, meta_bool<is_type_pod_copy<T>::res>());
}
//----

template<typename T>
PFC_INLINE void move_construct(T *dst_, T *src_, usize_t count_)
{
  // move construct an array
  priv::move_construct(dst_, src_, count_, meta_bool<is_type_pod_move<T>::res>());
}
//----

template<typename T>
PFC_INLINE void rotate_sequence_left(T *first_, T *last_)
{
  // rotate sequence of values one item to the left
  PFC_ASSERT_PEDANTIC_MSG(first_ && first_<=last_, ("First pointer must be non-zero and precede the last pointer (first: %p, last: %p)\r\n", first_, last_));
  priv::rotate_sequence_left(first_, last_, meta_bool<is_type_pod_move<T>::res>());
}
//----

template<typename T>
PFC_INLINE void rotate_sequence_right(T *first_, T *last_)
{
  // rotate sequence of values one item to the right
  PFC_ASSERT_PEDANTIC_MSG(first_ && first_<=last_, ("First pointer must be non-zero and precede the last pointer (first: %p, last: %p)\r\n", first_, last_));
  priv::rotate_sequence_right(first_, last_, meta_bool<is_type_pod_move<T>::res>());
}
//----

template<typename T>
PFC_INLINE void destruct(T *dst_, usize_t count_)
{
  // destruct an array
  priv::destruct(dst_, count_, meta_bool<is_type_pod_dtor<T>::res>());
}
//----------------------------------------------------------------------------


template<typename T>
PFC_INLINE void reverse_default_construct(T *dst_, usize_t count_)
{
  // default construct an array in reverse order
  priv::reverse_default_construct(dst_, count_, meta_bool<is_type_pod_def_ctor<T>::res>());
}
//----

template<typename T>
PFC_INLINE void reverse_copy_construct(T *dst_, const T *src_, usize_t count_)
{
  // copy construct an array from an array in reverse order
  PFC_ASSERT_PEDANTIC_MSG(dst_+count_<=src_ || src_+count_<=dst_, ("Memory regions may not overlap\r\n"));
  priv::reverse_copy_construct(dst_, src_, count_, meta_bool<is_type_pod_copy<T>::res>());
}
//----

template<typename T>
PFC_INLINE void reverse_copy_construct(T *dst_, const T &v_, usize_t count_)
{
  // copy construct an array from a value in reverse order
  PFC_ASSERT_PEDANTIC_MSG(dst_+count_<=&v_ || dst_>&v_, ("Target array overwrites the source value\r\n"));
  if(count_)
    priv::reverse_copy_construct(dst_, v_, count_, meta_bool<is_type_pod_copy<T>::res>());
}
//----

template<typename T>
PFC_INLINE void reverse_move_construct(T *dst_, T *src_, usize_t count_)
{
  // move construct an array in reverse order
  PFC_ASSERT_PEDANTIC_MSG(dst_+count_<=src_ || src_+count_<=dst_, ("Memory regions may not overlap\r\n"));
  priv::reverse_move_construct(dst_, src_, count_, meta_bool<is_type_pod_move<T>::res>());
}
//----

template<typename T>
PFC_INLINE void reverse_destruct(T *dst_, usize_t count_)
{
  // destruct an array in reverse order
  priv::reverse_destruct(dst_, count_, meta_bool<is_type_pod_dtor<T>::res>());
}
//----------------------------------------------------------------------------


//============================================================================
// rng_simple
//============================================================================
rng_simple::rng_simple(uint32_t seed_)
{
  set_seed(seed_);
}
//----

void rng_simple::set_seed(uint32_t seed_)
{
  m_w=seed_^0x82e9b275;
  m_z=seed_^0x2eb15b0f;
  if(!m_w || m_w==0x464fffff)
    ++m_w;
  if(!m_z || m_z==0x9068ffff)
    ++m_z;
}
//----

ufloat1_t rng_simple::rand_ureal1() const
{
  // return random (unsigned) real value in range [0, 1)
  m_z=36969*(m_z&65535)+(m_z>>16);
  m_w=18000*(m_w&65535)+(m_w>>16);
  return raw_cast<ufloat1_t>((((m_z<<16)+m_w)&0x007fffff)|0x3f800000)-1.0f;
}
//----

float1_t rng_simple::rand_real1() const
{
  // return random real value in range [-1, 1)
  m_z=36969*(m_z&65535)+(m_z>>16);
  m_w=18000*(m_w&65535)+(m_w>>16);
  return raw_cast<ufloat1_t>((((m_z<<16)+m_w)&0x007fffff)|0x3f800000)*2.0f-3.0f;
}
//----

uint16_t rng_simple::rand_uint16() const
{
  // return random uint16
  m_z=36969*(m_z&65535)+(m_z>>16);
  m_w=18000*(m_w&65535)+(m_w>>16);
  return uint16_t(m_z+(m_w>>16));
}
//----------------------------------------------------------------------------


//============================================================================
// rng_simple16
//============================================================================
rng_simple16::rng_simple16(uint32_t seed_)
{
  set_seed(seed_);
}
//----

void rng_simple16::set_seed(uint32_t seed_)
{
  m_w=(seed_*0x82e9b275)|0x100000;
}
//----

ufloat1_t rng_simple16::rand_ureal1() const
{
  // return random (unsigned) real value in range [0, 1)
  m_w=18000*(m_w&65535)+(m_w>>16);
  return raw_cast<ufloat1_t>((m_w&0x007fffff)|0x3f800000)-1.0f;
}
//----

float1_t rng_simple16::rand_real1() const
{
  // return random real value in range [-1, 1)
  m_w=18000*(m_w&65535)+(m_w>>16);
  return raw_cast<ufloat1_t>((m_w&0x007fffff)|0x3f800000)*2.0f-3.0f;
}
//----

uint16_t rng_simple16::rand_uint16() const
{
  // return random uint16
  m_w=18000*(m_w&65535)+(m_w>>16);
  return uint16_t(m_w>>16);
}
//----------------------------------------------------------------------------


//============================================================================
// timer
//============================================================================
timer::timer(udouble_t time_)
{
  // init timer
  m_is_ticking=false;
  m_start_time=-time_;
  m_update_time=0.0;
  m_prev_update_time=0.0;
}
//----

void timer::reset(udouble_t time_)
{
  // reset timer time
  m_start_time=m_update_time=m_prev_update_time=get_global_time();
  m_start_time-=time_;
}
//----------------------------------------------------------------------------

void timer::start()
{
  // start the timer
  if(!m_is_ticking)
  {
    m_is_ticking=true;
    udouble_t time=get_global_time();
    m_start_time+=time-m_update_time;
    m_update_time=m_prev_update_time=time;
  }
}
//----

void timer::stop()
{
  // stop the timer
  m_is_ticking=false;
}
//----

void timer::update()
{
  // update timer time
  if(m_is_ticking)
  {
    m_prev_update_time=m_update_time;
    m_update_time=get_global_time();
  }
}
//----

udouble_t timer::time() const
{
  return m_update_time-m_start_time;
}
//----

udouble_t timer::delta_time() const
{
  return m_update_time-m_prev_update_time;
}
//----

bool timer::is_ticking() const
{
  return m_is_ticking;
}
//----------------------------------------------------------------------------


//============================================================================
// hash_func
//============================================================================
namespace priv
{
  PFC_INLINE unsigned hash_func_idx(const volatile void *p_, meta_int<1>)
  {
    // return index for 8-bit value
    return *reinterpret_cast<const volatile uint8_t*>(p_);
  }
  //----

  PFC_INLINE unsigned hash_func_idx(const volatile void *p_, meta_int<2>)
  {
    // return index for 16-bit value (by Thomas Wang)
    uint32_t k=*reinterpret_cast<const volatile uint16_t*>(p_);
    k=~k+(k<<15);
    k=k^(k>>12);
    k=k+(k<<2);
    k=k^(k>>4);
    k=k*2057; // k=(k+(k<<3))+(k<<11);
    return k^(k>>16);
  }
  //----

  PFC_INLINE unsigned hash_func_idx(const volatile void *p_, meta_int<4>)
  {
    // return index for 32-bit value (by Thomas Wang)
    uint32_t k=*reinterpret_cast<const volatile uint32_t*>(p_);
    k=~k+(k<<15);
    k=k^(k>>12);
    k=k+(k<<2);
    k=k^(k>>4);
    k=k*2057; // k=(k+(k<<3))+(k<<11);
    return k^(k>>16);
  }
  //----

  PFC_INLINE unsigned hash_func_idx(const volatile void *p_, meta_int<8>)
  {
    // return index for 64-bit value (by Thomas Wang)
    uint64_t k=*reinterpret_cast<const volatile uint64_t*>(p_);
    k=(~k)+(k<<18);
    k=k^(k>>31);
    k=k*21; // k=(k+(k<<2))+(k<<4);
    k=k^(k>>11);
    k=k+(k<<6);
    return unsigned(k^(k>>22));
  }
  //----

  PFC_INLINE unsigned hash_func_idx(const volatile void *p_, meta_int<16>)
  {
    // return index for 128-bit value (by Thomas Wang)
    uint128_t k=*(const uint128_t*)p_;
    k.lo=(~k.lo)+(k.lo<<18);
    k.lo=k.lo^(k.lo>>31);
    k.lo=k.lo*21; // k=(k+(k<<2))+(k<<4);
    k.lo=k.lo^(k.lo>>11);
    k.lo=k.lo+(k.lo<<6);
    k.lo=k.lo^(k.lo>>22);
    k.hi=(~k.hi)+(k.hi<<18);
    k.hi=k.hi^(k.hi>>31);
    k.hi=k.hi*21; // k=(k+(k<<2))+(k<<4);
    k.hi=k.hi^(k.hi>>11);
    k.hi=k.hi+(k.hi<<6);
    k.hi=k.hi^(k.hi>>22);
    return unsigned(k.lo^k.hi);
  }
} // namespace priv
//----------------------------------------------------------------------------

template<typename K>
unsigned hash_func<K>::index(K k_)
{
  PFC_STATIC_ASSERT_MSG(!is_type_class<K>::res, hash_func_must_be_specialized_for_class_types);
  return priv::hash_func_idx(&k_, meta_int<sizeof(K)>());
}
//----------------------------------------------------------------------------

template<typename T>
unsigned hash_func<T*>::index(const volatile T *p_)
{
  usize_t pv=usize_t(p_)>>meta_log2<meta_alignof<T>::res>::res;
  return priv::hash_func_idx(&pv, meta_int<sizeof(usize_t)>());
}
//----------------------------------------------------------------------------


//============================================================================
// fourcc_id
//============================================================================
fourcc_id::fourcc_id()
{
  m_id=0;
}
//----

fourcc_id::fourcc_id(uint32_t id32_)
{
  PFC_ASSERT_PEDANTIC_MSG(!id32_ || id32_==filter_id32(id32_), ("FourCC ID contains invalid characters\r\n"));
  m_id=id32_;
}
//----

fourcc_id::fourcc_id(const char *str_)
{
  set(str_);
}
//----

void fourcc_id::set(uint32_t id32_)
{
  PFC_ASSERT_PEDANTIC_MSG(!id32_ || id32_==filter_id32(id32_), ("FourCC ID contains invalid characters\r\n"));
  m_id=id32_;
}
//----

void fourcc_id::set(const char *str_)
{
  // set FourCC from string
  m_id=0;
  for(unsigned i=0; i<4; ++i)
  {
    uint8_t c=*str_++;
    if(!c)
      break;
    m_id=(m_id<<8)|c;
  }
  m_id=filter_id32(m_id);
}
//----------------------------------------------------------------------------

bool fourcc_id::operator==(const fourcc_id &id_) const
{
  return m_id==id_.m_id;
}
//----

bool fourcc_id::operator!=(const fourcc_id &id_) const
{
  return m_id!=id_.m_id;
}
//----

bool fourcc_id::operator==(uint32_t id32_) const
{
  return m_id==id32_;
}
//----

bool fourcc_id::operator!=(uint32_t id32_) const
{
  return m_id!=id32_;
}
//----

uint32_t fourcc_id::id32() const
{
  return m_id;
}
//----

void fourcc_id::c_str(fourcc_cstr str_) const
{
  // return string for the id
  str_[0]=m_id>>24;
  str_[1]=(m_id>>16)&255;
  str_[2]=(m_id>>8)&255;
  str_[3]=m_id&255;
  str_[4]=0;
}
//----------------------------------------------------------------------------


//============================================================================
// str_id
//============================================================================
str_id::str_id()
  :m_crc32(0)
  ,m_str(0)
{
}
//----

str_id::str_id(const char *str_)
  :m_crc32(pfc::crc32(str_))
  ,m_str(str_)
{
}
//----

str_id::str_id(const char *str_, uint32_t crc32_)
  :m_crc32(crc32_)
  ,m_str(str_)
{
}
//----

void str_id::set(const char *str_)
{
  m_crc32=pfc::crc32(str_);
  m_str=str_;
}
//----

void str_id::set(const char *str_, uint32_t crc32_)
{
  m_crc32=crc32_;
  m_str=str_;
}
//----------------------------------------------------------------------------

bool str_id::operator==(const str_id &id_) const
{
  return m_crc32==id_.m_crc32 && str_eq(m_str, id_.m_str);
}
//----

bool str_id::operator!=(const str_id &id_) const
{
  return m_crc32!=id_.m_crc32 || !str_eq(m_str, id_.m_str);
}
//----

uint32_t str_id::crc32() const
{
  return m_crc32;
}
//----

const char *str_id::c_str() const
{
  return m_str;
}
//----------------------------------------------------------------------------


//============================================================================
// hash_func<str_id>
//============================================================================
template<>
struct hash_func<str_id>
{
  static PFC_INLINE unsigned index(const str_id &id_)
  {
    return id_.m_crc32;
  }
};
//----------------------------------------------------------------------------


//============================================================================
// pair
//============================================================================
template<typename T, typename U>
pair<T, U>::pair()
{
}
//----

template<typename T, typename U>
pair<T, U>::pair(const T &first_, const U &second_)
  :first(first_)
  ,second(second_)
{
}
//----

template<typename T, typename U>
void pair<T, U>::set(const T &first_, const U &second_)
{
  first=first_;
  second=second_;
}
//----------------------------------------------------------------------------

template<typename T, typename U>
PFC_INLINE pair<T, U> make_pair(const T &p0_, const U &p1_)
{
  return pair<T, U>(p0_, p1_);
}
//----

template<typename T, typename U>
PFC_INLINE bool operator==(const pair<T, U> &p0_, const pair<T, U> &p1_)
{
  return p0_.first==p1_.first && p0_.second==p1_.second;
}
//----

template<typename T, typename U>
PFC_INLINE bool operator==(const pair<T, U> &p_, const T &v_)
{
  return p_.first==v_;
}
//----

template<typename T, typename U>
PFC_INLINE bool operator!=(const pair<T, U> &p0_, const pair<T, U> &p1_)
{
  return p0_.first!=p1_.first || p0_.second!=p1_.second;
}
//----

template<typename T, typename U>
PFC_INLINE bool operator!=(const pair<T, U> &p_, const T &v_)
{
  return p_.first!=v_;
}
//----------------------------------------------------------------------------


//============================================================================
// hash_func<pair>
//============================================================================
template<typename T, typename U>
struct hash_func<pair<T, U> >
{
  static PFC_INLINE unsigned index(const pair<T, U> &p_)
  {
    return (hash_func<T>::index(p_.first)+hash_func<U>::index(p_.second));
  }
};
//----------------------------------------------------------------------------


//============================================================================
// radix_sort_predicate<pair>
//============================================================================
template<typename T, typename U, bool ascending_>
unsigned radix_sort_predicate<pair<T, U>, ascending_>::radix(const pair<T, U> &v_, unsigned pass_) const
{
  typedef typename meta_type_array<int8_t, int16_t, int32_t, int64_t>::get<meta_log2<sizeof(T)>::res>::res cast_type;
  return ((ascending_?(cast_type&)v_.first:-(cast_type&)v_.first)>>(pass_*8))&0xff;
}
//----------------------------------------------------------------------------


//============================================================================
// compare_sort_predicate<pair>
//============================================================================
template<typename T, typename U, bool ascending_>
bool compare_sort_predicate<pair<T, U>, ascending_>::before(const pair<T, U> &v0_, const pair<T, U> &v1_) const
{
  return ascending_?v0_.first<v1_.first:v1_.first<v0_.first;
}
//----------------------------------------------------------------------------


//============================================================================
// value_range
//============================================================================
template<typename T>
value_range<T>::value_range()
{
}
//----

template<typename T>
value_range<T>::value_range(const T &min_, const T &range_)
  :min(min_)
  ,range(range_)
{
}
//----

template<typename T>
void value_range<T>::set(const T &min_, const T &range_)
{
  min=min_;
  range=range_;
}
//----

template<typename T>
template<class Rng>
T value_range<T>::rand_value(Rng &rng_)
{
  return min+rng_.rand_ureal1()*range;
}
//----------------------------------------------------------------------------
