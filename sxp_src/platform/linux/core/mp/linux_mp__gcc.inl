//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================


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
    static PFC_INLINE int8_t op_inc(volatile T &v_)
    {
      return __sync_add_and_fetch((volatile int8_t*)&v_, 1);
    }
    //----

    template<typename T>
    static PFC_INLINE int8_t op_dec(volatile T &v_)
    {
      return __sync_sub_and_fetch((volatile int8_t*)&v_, 1);
    }
    //----

    template<typename T>
    static PFC_INLINE int8_t op_add(volatile T &dst_, T v_)
    {
      return __sync_fetch_and_add((volatile int8_t*)&dst_, (int8_t&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE int8_t op_sub(volatile T &dst_, T v_)
    {
      return __sync_fetch_and_sub((volatile int8_t*)&dst_, (int8_t&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE int8_t op_mov(volatile T &dst_, T v_)
    {
      return __sync_lock_test_and_set((volatile int8_t*)&dst_, (int8_t&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE int8_t op_read(const volatile T &src_)
    {
      return (const int8_t&)src_;
    }
    //----

    template<typename T>
    static PFC_INLINE void op_write(volatile T &dst_, T v_)
    {
      (volatile int8_t&)dst_=(const int8_t&)v_;
    }
    //----

    template<typename T>
    static PFC_INLINE int8_t op_and(volatile T &dst_, T v_)
    {
      return __sync_fetch_and_and((volatile int8_t*)&dst_, (int8_t&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE int8_t op_or(volatile T &dst_, T v_)
    {
      return __sync_fetch_and_or((volatile int8_t*)&dst_, (int8_t&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE int8_t op_xor(volatile T &dst_, T v_)
    {
      return __sync_fetch_and_xor((volatile int8_t*)&dst_, (int8_t&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE int8_t op_cmov(volatile T &dst_, T v_, T comp_)
    {
      return __sync_val_compare_and_swap((volatile int8_t*)&dst_, (int8_t&)comp_, (int8_t&)v_);
    }
  };
  //----

  template<>
  struct atom_hlp<2, true>
  {
    template<typename T>
    static PFC_INLINE int16_t op_inc(volatile T &v_)
    {
      return __sync_add_and_fetch((volatile int16_t*)&v_, 1);
    }
    //----

    template<typename T>
    static PFC_INLINE int16_t op_dec(volatile T &v_)
    {
      return __sync_sub_and_fetch((volatile int16_t*)&v_, 1);
    }
    //----

    template<typename T>
    static PFC_INLINE int16_t op_add(volatile T &dst_, const T &v_)
    {
      return __sync_fetch_and_add((volatile int16_t*)&dst_, (int16_t&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE int16_t op_sub(volatile T &dst_, const T &v_)
    {
      return __sync_fetch_and_sub((volatile int16_t*)&dst_, (int16_t&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE int16_t op_mov(volatile T &dst_, const T &v_)
    {
      return __sync_lock_test_and_set((volatile int16_t*)&dst_, (int16_t&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE int16_t op_read(const volatile T &src_)
    {
      PFC_STATIC_ASSERT_MSG(meta_alignof<T>::res>=2, alignment_restrictions_of_the_type_are_not_strict_enough_for_the_atomic_operation);
      return (const int16_t&)src_;
    }
    //----

    template<typename T>
    static PFC_INLINE void op_write(volatile T &dst_, T v_)
    {
      PFC_STATIC_ASSERT_MSG(meta_alignof<T>::res>=2, alignment_restrictions_of_the_type_are_not_strict_enough_for_the_atomic_operation);
      (volatile int16_t&)dst_=(const int16_t&)v_;
    }
    //----

    template<typename T>
    static PFC_INLINE int16_t op_and(volatile T &dst_, T v_)
    {
      return __sync_fetch_and_and((volatile int16_t*)&dst_, (int16_t&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE int16_t op_or(volatile T &dst_, T v_)
    {
      return __sync_fetch_and_or((volatile int16_t*)&dst_, (int16_t&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE int16_t op_xor(volatile T &dst_, T v_)
    {
      return __sync_fetch_and_xor((volatile int16_t*)&dst_, (int16_t&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE int16_t op_cmov(volatile T &dst_, T v_, T comp_)
    {
      PFC_STATIC_ASSERT_MSG(meta_alignof<T>::res>=2, alignment_restrictions_of_the_type_are_not_strict_enough_for_the_atomic_operation);
      return __sync_val_compare_and_swap((volatile int16_t*)&dst_, (int16_t&)comp_, (int16_t&)v_);
    }
  };
  //----

  template<>
  struct atom_hlp<4, true>
  {
    template<typename T>
    static PFC_INLINE int32_t op_inc(volatile T &v_)
    {
      return __sync_add_and_fetch((volatile int32_t*)&v_, 1);
    }
    //----

    template<typename T>
    static PFC_INLINE int32_t op_dec(volatile T &v_)
    {
      return __sync_sub_and_fetch((volatile int32_t*)&v_, 1);
    }
    //----

    template<typename T>
    static PFC_INLINE int32_t op_add(volatile T &dst_, T v_)
    {
      return __sync_fetch_and_add((volatile int32_t*)&dst_, (int32_t&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE int32_t op_sub(volatile T &dst_, T v_)
    {
      return __sync_fetch_and_sub((volatile int32_t*)&dst_, (int32_t&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE int32_t op_mov(volatile T &dst_, T v_)
    {
      PFC_STATIC_ASSERT_MSG(meta_alignof<T>::res>=4, alignment_restrictions_of_the_type_are_not_strict_enough_for_the_atomic_operation);
      return __sync_lock_test_and_set((volatile int32_t*)&dst_, (int32_t&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE int32_t op_read(const volatile T &src_)
    {
      PFC_STATIC_ASSERT_MSG(meta_alignof<T>::res>=4, alignment_restrictions_of_the_type_are_not_strict_enough_for_the_atomic_operation);
      return (const int32_t&)src_;
    }
    //----

    template<typename T>
    static PFC_INLINE void op_write(volatile T &dst_, T v_)
    {
      PFC_STATIC_ASSERT_MSG(meta_alignof<T>::res>=4, alignment_restrictions_of_the_type_are_not_strict_enough_for_the_atomic_operation);
      (volatile int32_t&)dst_=(const int32_t&)v_;
    }
    //----

    template<typename T>
    static PFC_INLINE int32_t op_and(volatile T &dst_, T v_)
    {
      return __sync_fetch_and_and((volatile int32_t*)&dst_, (int32_t&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE int32_t op_or(volatile T &dst_, T v_)
    {
      return __sync_fetch_and_or((volatile int32_t*)&dst_, (int32_t&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE int32_t op_xor(volatile T &dst_, T v_)
    {
      return __sync_fetch_and_xor((volatile int32_t*)&dst_, (int32_t&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE int32_t op_cmov(volatile T &dst_, T v_, T comp_)
    {
      PFC_STATIC_ASSERT_MSG(meta_alignof<T>::res>=4, alignment_restrictions_of_the_type_are_not_strict_enough_for_the_atomic_operation);
      return __sync_val_compare_and_swap((volatile int32_t*)&dst_, (int32_t&)comp_, (int32_t&)v_);
    }
  };
  //----

  template<>
  struct atom_hlp<8, true>
  {
    template<typename T>
    static PFC_INLINE int64_t op_inc(volatile T &v_)
    {
      return __sync_add_and_fetch((volatile int64_t*)&v_, 1);
    }
    //----

    template<typename T>
    static PFC_INLINE int64_t op_dec(volatile T &v_)
    {
      return __sync_sub_and_fetch((volatile int64_t*)&v_, 1);
    }
    //----

    template<typename T>
    static PFC_INLINE int64_t op_add(volatile T &dst_, T v_)
    {
      return __sync_fetch_and_add((volatile int64_t*)&dst_, (int64_t&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE int64_t op_sub(volatile T &dst_, T v_)
    {
      PFC_STATIC_ERROR(T, atomic_sub_is_not_supported_for_the_type);
      return int64_t();
    }
    //----

    template<typename T>
    static PFC_INLINE int64_t op_mov(volatile T &dst_, T v_)
    {
      PFC_STATIC_ASSERT_MSG(meta_alignof<T>::res>=8, alignment_restrictions_of_the_type_are_not_strict_enough_for_the_atomic_operation);
      return __sync_lock_test_and_set((volatile int64_t*)&dst_, (int64_t&)v_);
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
    static PFC_INLINE int64_t op_and(volatile T &dst_, T v_)
    {
      return __sync_fetch_and_and((volatile int64_t*)&dst_, (int64_t&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE int64_t op_or(volatile T &dst_, T v_)
    {
      return __sync_fetch_and_or((volatile int64_t*)&dst_, (int64_t&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE int64_t op_xor(volatile T &dst_, T v_)
    {
      return __sync_fetch_and_xor((volatile int64_t*)&dst_, (int64_t&)v_);
    }
    //----

    template<typename T>
    static PFC_INLINE int64_t op_cmov(volatile T &dst_, T v_, T comp_)
    {
      PFC_STATIC_ASSERT_MSG(meta_alignof<T>::res>=8, alignment_restrictions_of_the_type_are_not_strict_enough_for_the_atomic_operation);
      return __sync_val_compare_and_swap((volatile int64_t*)&dst_, (int64_t&)comp_, (int64_t&)v_);
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
      return uint128_t();
    }
    //----

    template<typename T>
    static PFC_INLINE uint128_t op_dec(volatile T&)
    {
      PFC_STATIC_ERROR(T, atomic_dec_is_not_supported_for_the_type);
      return uint128_t();
    }
    //----

    template<typename T>
    static PFC_INLINE uint128_t op_add(volatile T&, T)
    {
      PFC_STATIC_ERROR(T, atomic_addition_is_not_supported_for_the_type);
      return uint128_t();
    }
    //----

    template<typename T>
    static PFC_INLINE uint128_t op_sub(volatile T&, T)
    {
      PFC_STATIC_ERROR(T, atomic_addition_is_not_supported_for_the_type);
      return uint128_t();
    }
    //----

    template<typename T>
    static PFC_INLINE uint128_t op_mov(volatile T&, T)
    {
      PFC_STATIC_ERROR(T, atomic_move_is_not_supported_for_the_type);
      return uint128_t();
    }
    //----

    template<typename T>
    static PFC_INLINE uint128_t op_read(const volatile T &src_)
    {
      // read 128-bit value from destination
      PFC_STATIC_ASSERT_MSG(meta_alignof<T>::res>=16, alignment_restrictions_of_the_type_are_not_strict_enough_for_the_atomic_operation);
      __int128 res=__sync_val_compare_and_swap((__int128*)&src_, -1, -1);
      return (uint128_t&)res;
    }
    //----

    template<typename T>
    static PFC_INLINE void op_write(volatile T &dst_, T v_)
    {
      // write 128-bit value to the destination
      PFC_STATIC_ASSERT_MSG(meta_alignof<T>::res>=16, alignment_restrictions_of_the_type_are_not_strict_enough_for_the_atomic_operation);
      __int128 test_val;
      do
      {
        test_val=(const __int128&)dst_;
      } while(test_val!=__sync_val_compare_and_swap((__int128*)&dst_, test_val, (__int128&)v_));
    }
    //----

    template<typename T>
    static PFC_INLINE uint128_t op_and(volatile T &dst_, T v_)
    {
      PFC_STATIC_ERROR(T, atomic_and_is_not_supported_for_the_type);
      return uint128_t();
    }
    //----

    template<typename T>
    static PFC_INLINE uint128_t op_or(volatile T &dst_, T v_)
    {
      PFC_STATIC_ERROR(T, atomic_or_is_not_supported_for_the_type);
      return uint128_t();
    }
    //----

    template<typename T>
    static PFC_INLINE uint128_t op_xor(volatile T &dst_, T v_)
    {
      PFC_STATIC_ERROR(T, atomic_xor_is_not_supported_for_the_type);
      return uint128_t();
    }
    //----

    template<typename T>
    static PFC_INLINE uint128_t op_cmov(volatile T &dst_, T v_, T comp_)
    {
      __int128 v=__sync_val_compare_and_swap((__int128*)&dst_, (const __int128&)comp_, (const __int128&)v_);
      return (uint128_t&)v;
    }
  };
} // namespace priv
//----------------------------------------------------------------------------
