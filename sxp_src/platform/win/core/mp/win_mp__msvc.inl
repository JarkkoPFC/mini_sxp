//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// intrinsics
//============================================================================
// basic intrinsics
#pragma intrinsic(_InterlockedIncrement16, _InterlockedIncrement)
#pragma intrinsic(_InterlockedDecrement16, _InterlockedDecrement)
#pragma intrinsic(_InterlockedExchange)
#pragma intrinsic(_InterlockedExchangeAdd)
#pragma intrinsic(_InterlockedCompareExchange16, _InterlockedCompareExchange)
#pragma intrinsic(_InterlockedAnd8, _InterlockedAnd16, _InterlockedAnd)
#pragma intrinsic(_InterlockedOr8, _InterlockedOr16, _InterlockedOr)
#pragma intrinsic(_InterlockedXor8, _InterlockedXor16, _InterlockedXor)
#ifdef PFC_PLATFORM_64BIT
// 64-bit extension
#pragma intrinsic(_InterlockedIncrement64)
#pragma intrinsic(_InterlockedDecrement64)
#pragma intrinsic(_InterlockedExchange64)
#pragma intrinsic(_InterlockedExchangeAdd64)
#pragma intrinsic(_InterlockedCompareExchange64)
#pragma intrinsic(_InterlockedCompareExchange128)
#pragma intrinsic(_InterlockedAnd64)
#pragma intrinsic(_InterlockedOr64)
#pragma intrinsic(_InterlockedXor64)
#endif
//----------------------------------------------------------------------------


//============================================================================
// fundamental atomic operations
//============================================================================
namespace priv
{
  template<unsigned, bool>
  struct atom_hlp
  {
    PFC_STATIC_ERROR(unsigned, atomic_operation_is_not_supported_for_the_type);
    template<typename T> static PFC_INLINE T op_inc(volatile T&);
    template<typename T> static PFC_INLINE T op_dec(volatile T&);
    template<typename T> static PFC_INLINE T op_add(volatile T&, T);
    template<typename T> static PFC_INLINE T op_mov(volatile T&, T);
    template<typename T> static PFC_INLINE T op_and(volatile T&, T);
    template<typename T> static PFC_INLINE T op_or(volatile T&, T);
    template<typename T> static PFC_INLINE T op_xor(volatile T&, T);
    template<typename T> static PFC_INLINE T op_cmov(volatile T&, T, T);
  };
  //----

  template<>
  struct atom_hlp<1, true>
  {
    template<typename T>
    static PFC_INLINE char op_inc(volatile T&)
    {
      PFC_STATIC_ERROR(T, atomic_inc_is_not_supported_for_the_type);
    }
    //----

    template<typename T>
    static PFC_INLINE char op_dec(volatile T&)
    {
      PFC_STATIC_ERROR(T, atomic_dec_is_not_supported_for_the_type);
    }
    //----

    template<typename T>
    static PFC_INLINE char op_add(volatile T&, T)
    {
      PFC_STATIC_ERROR(T, atomic_addition_is_not_supported_for_the_type);
    }
    //----

    template<typename T>
    static PFC_INLINE char op_sub(volatile T&, T)
    {
      PFC_STATIC_ERROR(T, atomic_addition_is_not_supported_for_the_type);
    }
    //----

    template<typename T>
    static PFC_INLINE char op_mov(volatile T&, T)
    {
      PFC_STATIC_ERROR(T, atomic_move_is_not_supported_for_the_type);
    }
    //----

    template<typename T>
    static PFC_INLINE char op_read(const volatile T &src_)
    {
      return (const char&)src_;
    }
    //----

    template<typename T>
    static PFC_INLINE void op_write(volatile T &dst_, T v_)
    {
      (volatile char&)dst_=(const char&)v_;
    }
    //----

    template<typename T>
    static PFC_INLINE char op_and(volatile T &dst_, T v_)
    {
      return _InterlockedAnd8((volatile char*)&dst_, (char&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE char op_or(volatile T &dst_, T v_)
    {
      return _InterlockedOr8((volatile char*)&dst_, (char&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE char op_xor(volatile T &dst_, T v_)
    {
      return _InterlockedXor8((volatile char*)&dst_, (char&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE char op_cmov(volatile T&, T, T)
    {
      PFC_STATIC_ERROR(T, atomic_conditional_move_is_not_supported_for_the_type);
    }
  };
  //----

  template<>
  struct atom_hlp<2, true>
  {
    template<typename T>
    static PFC_INLINE short op_inc(volatile T &v_)
    {
      return _InterlockedIncrement16((volatile short*)&v_);
    }
    //----

    template<typename T>
    static PFC_INLINE short op_dec(volatile T &v_)
    {
      return _InterlockedDecrement16((volatile short*)&v_);
    }
    //----

    template<typename T>
    static PFC_INLINE short op_add(volatile T&, const T&)
    {
      PFC_STATIC_ERROR(T, atomic_addition_is_not_supported_for_the_type);
    }
    //----

    template<typename T>
    static PFC_INLINE short op_sub(volatile T&, const T&)
    {
      PFC_STATIC_ERROR(T, atomic_addition_is_not_supported_for_the_type);
    }
    //----

    template<typename T>
    static PFC_INLINE short op_mov(volatile T&, const T&)
    {
      PFC_STATIC_ERROR(T, atomic_move_is_not_supported_for_the_type);
    }
    //----

    template<typename T>
    static PFC_INLINE short op_read(const volatile T &src_)
    {
      PFC_STATIC_ASSERT_MSG(meta_alignof<T>::res>=2, alignment_restrictions_of_the_type_are_not_strict_enough_for_the_atomic_operation);
      return (const short&)src_;
    }
    //----

    template<typename T>
    static PFC_INLINE void op_write(volatile T &dst_, T v_)
    {
      PFC_STATIC_ASSERT_MSG(meta_alignof<T>::res>=2, alignment_restrictions_of_the_type_are_not_strict_enough_for_the_atomic_operation);
      (volatile short&)dst_=(const short&)v_;
    }
    //----

    template<typename T>
    static PFC_INLINE short op_and(volatile T &dst_, T v_)
    {
      return _InterlockedAnd16((volatile short*)&dst_, (short&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE short op_or(volatile T &dst_, T v_)
    {
      return _InterlockedOr16((volatile short*)&dst_, (short&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE short op_xor(volatile T &dst_, T v_)
    {
      return _InterlockedXor16((volatile short*)&dst_, (short&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE short op_cmov(volatile T &dst_, T v_, T comp_)
    {
      PFC_STATIC_ASSERT_MSG(meta_alignof<T>::res>=2, alignment_restrictions_of_the_type_are_not_strict_enough_for_the_atomic_operation);
      return _InterlockedCompareExchange16((volatile short*)&dst_, (short&)v_, (short&)comp_);
    }
  };
  //----

  template<>
  struct atom_hlp<4, true>
  {
    template<typename T>
    static PFC_INLINE long op_inc(volatile T &v_)
    {
      return _InterlockedIncrement((volatile long*)&v_);
    }
    //----

    template<typename T>
    static PFC_INLINE long op_dec(volatile T &v_)
    {
      return _InterlockedDecrement((volatile long*)&v_);
    }
    //----

    template<typename T>
    static PFC_INLINE long op_add(volatile T &dst_, T v_)
    {
      return _InterlockedExchangeAdd((volatile long*)&dst_, (long&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE long op_sub(volatile T &dst_, T v_)
    {
      (long&)v_=-long(v_);
      return _InterlockedExchangeAdd((volatile long*)&dst_, (long&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE long op_mov(volatile T &dst_, T v_)
    {
      PFC_STATIC_ASSERT_MSG(meta_alignof<T>::res>=4, alignment_restrictions_of_the_type_are_not_strict_enough_for_the_atomic_operation);
      return _InterlockedExchange((volatile long*)&dst_, (long&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE long op_read(const volatile T &src_)
    {
      PFC_STATIC_ASSERT_MSG(meta_alignof<T>::res>=4, alignment_restrictions_of_the_type_are_not_strict_enough_for_the_atomic_operation);
      return (const long&)src_;
    }
    //----

    template<typename T>
    static PFC_INLINE void op_write(volatile T &dst_, T v_)
    {
      PFC_STATIC_ASSERT_MSG(meta_alignof<T>::res>=4, alignment_restrictions_of_the_type_are_not_strict_enough_for_the_atomic_operation);
      (volatile long&)dst_=(const long&)v_;
    }
    //----

    template<typename T>
    static PFC_INLINE long op_and(volatile T &dst_, T v_)
    {
      return _InterlockedAnd((volatile long*)&dst_, (long&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE long op_or(volatile T &dst_, T v_)
    {
      return _InterlockedOr((volatile long*)&dst_, (long&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE long op_xor(volatile T &dst_, T v_)
    {
      return _InterlockedXor((volatile long*)&dst_, (long&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE long op_cmov(volatile T &dst_, T v_, T comp_)
    {
      PFC_STATIC_ASSERT_MSG(meta_alignof<T>::res>=4, alignment_restrictions_of_the_type_are_not_strict_enough_for_the_atomic_operation);
      return _InterlockedCompareExchange((volatile long*)&dst_, (long&)v_, (long&)comp_);
    }
  };
  //----

  template<>
  struct atom_hlp<8, true>
  {
    template<typename T>
    static PFC_INLINE __int64 op_inc(volatile T &v_)
    {
      return _InterlockedIncrement64((volatile __int64*)&v_);
    }
    //----

    template<typename T>
    static PFC_INLINE __int64 op_dec(volatile T &v_)
    {
      return _InterlockedDecrement64((volatile __int64*)&v_);
    }
    //----

    template<typename T>
    static PFC_INLINE __int64 op_add(volatile T &dst_, T v_)
    {
      return _InterlockedExchangeAdd64((volatile __int64*)&dst_, (__int64&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE __int64 op_sub(volatile T &dst_, T v_)
    {
      (__int64&)v_=-__int64(v_);
      return _InterlockedExchangeAdd64((volatile __int64*)&dst_, (__int64&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE __int64 op_mov(volatile T &dst_, T v_)
    {
      PFC_STATIC_ASSERT_MSG(meta_alignof<T>::res>=8, alignment_restrictions_of_the_type_are_not_strict_enough_for_the_atomic_operation);
      return _InterlockedExchange64((volatile __int64*)&dst_, (__int64&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE float64_t op_read(const volatile T &src_)
    {
      PFC_STATIC_ASSERT_MSG(meta_alignof<T>::res>=8, alignment_restrictions_of_the_type_are_not_strict_enough_for_the_atomic_operation);
      return *(const volatile float64_t*)&src_;
    }
    //----

    template<typename T>
    static PFC_INLINE void op_write(volatile T &dst_, T v_)
    {
      PFC_STATIC_ASSERT_MSG(meta_alignof<T>::res>=8, alignment_restrictions_of_the_type_are_not_strict_enough_for_the_atomic_operation);
      (volatile float64_t&)dst_=(const float64_t&)v_;
    }
    //----

    template<typename T>
    static PFC_INLINE __int64 op_and(volatile T &dst_, T v_)
    {
      return _InterlockedAnd64((volatile __int64*)&dst_, (__int64&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE __int64 op_or(volatile T &dst_, T v_)
    {
      return _InterlockedOr64((volatile __int64*)&dst_, (__int64&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE __int64 op_xor(volatile T &dst_, T v_)
    {
      return _InterlockedXor64((volatile __int64*)&dst_, (__int64&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE __int64 op_cmov(volatile T &dst_, T v_, T comp_)
    {
      PFC_STATIC_ASSERT_MSG(meta_alignof<T>::res>=8, alignment_restrictions_of_the_type_are_not_strict_enough_for_the_atomic_operation);
      return _InterlockedCompareExchange64((volatile __int64*)&dst_, (__int64&)v_, (__int64&)comp_);
    }
  };
  //----

  template<>
  struct atom_hlp<16, true>
  {
    template<typename T>
    static PFC_INLINE uint128_t op_inc(volatile T&)
    {
      PFC_STATIC_ERROR(T, atomic_inc_is_not_supported_for_the_type);
    }
    //----

    template<typename T>
    static PFC_INLINE uint128_t op_dec(volatile T&)
    {
      PFC_STATIC_ERROR(T, atomic_dec_is_not_supported_for_the_type);
    }
    //----

    template<typename T>
    static PFC_INLINE uint128_t op_add(volatile T&, T)
    {
      PFC_STATIC_ERROR(T, atomic_addition_is_not_supported_for_the_type);
    }
    //----

    template<typename T>
    static PFC_INLINE uint128_t op_sub(volatile T&, T)
    {
      PFC_STATIC_ERROR(T, atomic_addition_is_not_supported_for_the_type);
    }
    //----

    template<typename T>
    static PFC_INLINE uint128_t op_mov(volatile T &dst_, T v_)
    {
      // write 128-bit value to the destination, return old value
      PFC_STATIC_ASSERT_MSG(meta_alignof<T>::res>=16, alignment_restrictions_of_the_type_are_not_strict_enough_for_the_atomic_operation);
      uint128_t test_val;
      do
      {
        test_val=(const uint128_t&)dst_;
      } while(!_InterlockedCompareExchange128((volatile __int64*)&dst_, ((__int64*)&v_)[1], ((__int64*)&v_)[0], (__int64*)&test_val));
      return test_val;
    }
    //----

    template<typename T>
    static PFC_INLINE uint128_t op_read(const volatile T &src_)
    {
      // read 128-bit value from destination
      PFC_STATIC_ASSERT_MSG(meta_alignof<T>::res>=16, alignment_restrictions_of_the_type_are_not_strict_enough_for_the_atomic_operation);
      uint128_t res={PFC_CONST_UINT64(0xffffffffffffffff), PFC_CONST_UINT64(0xffffffffffffffff)};
      _InterlockedCompareExchange128((__int64*)&src_, PFC_CONST_UINT64(0xffffffffffffffff), PFC_CONST_UINT64(0xffffffffffffffff), (__int64*)&res);
      return res;
    }
    //----

    template<typename T>
    static PFC_INLINE void op_write(volatile T &dst_, T v_)
    {
      // write 128-bit value to the destination
      PFC_STATIC_ASSERT_MSG(meta_alignof<T>::res>=16, alignment_restrictions_of_the_type_are_not_strict_enough_for_the_atomic_operation);
      uint128_t test_val;
      do
      {
        test_val=(const uint128_t&)dst_;
      } while(!_InterlockedCompareExchange128((volatile __int64*)&dst_, ((__int64*)&v_)[1], ((__int64*)&v_)[0], (__int64*)&test_val));
    }
    //----

    template<typename T>
    static PFC_INLINE uint128_t op_and(volatile T &dst_, T v_)
    {
      PFC_STATIC_ERROR(T, atomic_and_is_not_supported_for_the_type);
    }
    //----

    template<typename T>
    static PFC_INLINE uint128_t op_or(volatile T &dst_, T v_)
    {
      PFC_STATIC_ERROR(T, atomic_or_is_not_supported_for_the_type);
    }
    //----

    template<typename T>
    static PFC_INLINE uint128_t op_xor(volatile T &dst_, T v_)
    {
      PFC_STATIC_ERROR(T, atomic_xor_is_not_supported_for_the_type);
    }
    //----

    template<typename T>
    static PFC_INLINE uint128_t op_cmov(volatile T &dst_, T v_, T comp_)
    {
      PFC_STATIC_ASSERT_MSG(meta_alignof<T>::res>=16, alignment_restrictions_of_the_type_are_not_strict_enough_for_the_atomic_operation);
      _InterlockedCompareExchange128((__int64*)&dst_, ((uint128_t&)v_).hi, ((uint128_t&)v_).lo, (__int64*)&comp_);
      return (const uint128_t&)comp_;
    }
  };
} // namespace priv
//----------------------------------------------------------------------------
