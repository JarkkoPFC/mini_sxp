//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_UTILS_H
#define PFC_CORE_UTILS_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "meta.h"
#include "cstr.h"
namespace pfc
{
template<typename T, bool ascending_> struct radix_sort_predicate;
template<typename T, bool ascending_> struct compare_sort_predicate;

// new
// data swapping
template<typename T> PFC_INLINE void swap(T&, T&);
template<typename T> PFC_INLINE void swap(T*, T*, usize_t count_);
template<typename T> PFC_INLINE T swap_bytes(T);
template<typename T> PFC_INLINE void swap_bytes(T*, usize_t count_);
template<typename T> PFC_INLINE T to_little_endian(T);
template<typename T> PFC_INLINE T to_big_endian(T);
// array construction/destruction
template<typename T> PFC_INLINE void default_construct(T*, usize_t count_);
template<typename T> PFC_INLINE void copy_construct(T*, const T*, usize_t count_);
template<typename T> PFC_INLINE void copy_construct(T*, const T&, usize_t count_);
template<typename T> PFC_INLINE void move_construct(T*, T*, usize_t count_);
template<typename T> PFC_INLINE void rotate_sequence_left(T *first_, T *last_);
template<typename T> PFC_INLINE void rotate_sequence_right(T *first_, T *last_);
template<typename T> PFC_INLINE void destruct(T*, usize_t count_);
template<typename T> PFC_INLINE void reverse_default_construct(T*, usize_t count_);
template<typename T> PFC_INLINE void reverse_copy_construct(T*, const T*, usize_t count_);
template<typename T> PFC_INLINE void reverse_copy_construct(T*, const T&, usize_t count_);
template<typename T> PFC_INLINE void reverse_move_construct(T*, T*, usize_t count_);
template<typename T> PFC_INLINE void reverse_destruct(T*, usize_t count_);
// randomization
class rng_simple;
class rng_simple16;
// timing
class timer;
// hash key and functions
template<typename> struct hash_func;
uint32_t crc32(const void*, usize_t num_bytes_, uint32_t seed_=0xffffffff);
uint32_t crc32(const char*, uint32_t seed_=0xffffffff);
// id classes
class fourcc_id;
typedef char fourcc_cstr[5];
#define PFC_BE_FOURCC_ID(c0__, c1__, c2__, c3__) uint32_t(uint32_t(c0__)<<24|uint32_t(c1__)<<16|uint32_t(c2__)<<8|uint32_t(c3__))
#define PFC_LE_FOURCC_ID(c0__, c1__, c2__, c3__) uint32_t(uint32_t(c0__)|uint32_t(c1__)<<8|uint32_t(c2__)<<16|uint32_t(c3__)<<24)
class str_id;
// tokenization
unsigned tokenize_command_line(char *cmd_line_, const char **tokens_, unsigned max_tokens_);
// pair
template<typename, typename> struct pair;
template<typename T, typename U> PFC_INLINE pair<T, U> make_pair(const T&, const U&);
template<typename T, typename U> PFC_INLINE bool operator==(const pair<T, U>&, const pair<T, U>&);
template<typename T, typename U> PFC_INLINE bool operator==(const pair<T, U>&, const T&);
template<typename T, typename U> PFC_INLINE bool operator!=(const pair<T, U>&, const pair<T, U>&);
template<typename T, typename U> PFC_INLINE bool operator!=(const pair<T, U>&, const T&);
// value_range
template<typename> struct value_range;
//----------------------------------------------------------------------------


//============================================================================
// rng_simple
//============================================================================
// Uses George Marsaglia's "Multiply with carry" RNG algorithm
class rng_simple
{
public:
  // construction
  PFC_INLINE rng_simple(uint32_t seed_=0);
  PFC_INLINE void set_seed(uint32_t seed_);
  PFC_INLINE ufloat1_t rand_ureal1() const;
  PFC_INLINE float1_t rand_real1() const;
  PFC_INLINE uint16_t rand_uint16() const;
  //--------------------------------------------------------------------------

private:
  mutable uint32_t m_w, m_z;
};
PFC_SET_TYPE_TRAIT(rng_simple, is_type_pod_move, true);
//----------------------------------------------------------------------------


//============================================================================
// rng_simple16
//============================================================================
// 16-bit George Marsaglia's "Multiply with carry" RNG algorithm
class rng_simple16
{
public:
  // construction
  PFC_INLINE rng_simple16(uint32_t seed_=0);
  PFC_INLINE void set_seed(uint32_t seed_);
  PFC_INLINE ufloat1_t rand_ureal1() const;
  PFC_INLINE float1_t rand_real1() const;
  PFC_INLINE uint16_t rand_uint16() const;
  //--------------------------------------------------------------------------

private:
  mutable uint32_t m_w;
};
PFC_SET_TYPE_TRAIT(rng_simple16, is_type_pod_move, true);
//----------------------------------------------------------------------------


//============================================================================
// timer
//============================================================================
class timer
{
public:
  // construction
  PFC_INLINE timer(udouble_t time_=0.0);
  PFC_INLINE void reset(udouble_t time_=0.0);
  //--------------------------------------------------------------------------

  // timer manipulation and time accessor
  PFC_INLINE void start();
  PFC_INLINE void stop();
  PFC_INLINE void update();
  PFC_INLINE udouble_t time() const;
  PFC_INLINE udouble_t delta_time() const;
  PFC_INLINE bool is_ticking() const;
  //--------------------------------------------------------------------------

private:
  bool m_is_ticking;
  udouble_t m_start_time;
  udouble_t m_update_time;
  udouble_t m_prev_update_time;
};
//----------------------------------------------------------------------------


//============================================================================
// hash_func
//============================================================================
template<typename K>
struct hash_func
{
  static PFC_INLINE unsigned index(K);
};
//----

template<typename T>
struct hash_func<T*>
{
  static PFC_INLINE unsigned index(const volatile T*);
};
//----------------------------------------------------------------------------


//============================================================================
// fourcc_id
//============================================================================
class fourcc_id
{ PFC_MONO(fourcc_id) {PFC_MVAR(m_id);}
public:
  // construction
  PFC_INLINE fourcc_id();
  PFC_INLINE fourcc_id(uint32_t id32_);
  PFC_INLINE fourcc_id(const char*);
  PFC_INLINE void set(uint32_t id32_);
  PFC_INLINE void set(const char*);
  //--------------------------------------------------------------------------

  // comparison and accessors
  PFC_INLINE bool operator==(const fourcc_id&) const;
  PFC_INLINE bool operator!=(const fourcc_id&) const;
  PFC_INLINE bool operator==(uint32_t) const;
  PFC_INLINE bool operator!=(uint32_t) const;
  PFC_INLINE uint32_t id32() const;
  PFC_INLINE void c_str(fourcc_cstr) const;
  //--------------------------------------------------------------------------

private:
  uint32_t filter_id32(uint32_t) const;
  //--------------------------------------------------------------------------

  uint32_t m_id;
};
PFC_SET_TYPE_TRAIT(fourcc_id, is_type_pod, true);
//----------------------------------------------------------------------------


//============================================================================
// str_id
//============================================================================
class str_id
{
public:
  // construction
  PFC_INLINE str_id();
  PFC_INLINE str_id(const char*);
  PFC_INLINE str_id(const char*, uint32_t crc32_);
  PFC_INLINE void set(const char*);
  PFC_INLINE void set(const char*, uint32_t crc32_);
  //--------------------------------------------------------------------------

  // comparison and accessors
  PFC_INLINE bool operator==(const str_id&) const;
  PFC_INLINE bool operator!=(const str_id&) const;
  PFC_INLINE uint32_t crc32() const;
  PFC_INLINE const char *c_str() const;
  //--------------------------------------------------------------------------

private:
  friend struct hash_func<str_id>;
  //--------------------------------------------------------------------------

  uint32_t m_crc32;
  const char *m_str;
};
PFC_SET_TYPE_TRAIT(str_id, is_type_pod_move, true);
//----------------------------------------------------------------------------


//============================================================================
// pair
//============================================================================
template<typename T, typename U>
struct pair
{ PFC_MONO(pair) {PFC_VAR2(first, second);}
  // construction
  PFC_INLINE pair();
  PFC_INLINE pair(const T&, const U&);
  PFC_INLINE void set(const T&, const U&);
  //--------------------------------------------------------------------------

  T first;
  U second;
};
PFC_SET_TYPE_TRAIT_PARTIAL2(typename T, typename U, pair<T, U>, is_type_pod_move, is_type_pod_move<T>::res && is_type_pod_move<U>::res);
//----------------------------------------------------------------------------


//============================================================================
// radix_sort_predicate<pair>
//============================================================================
template<typename T, typename U, bool ascending_>
struct radix_sort_predicate<pair<T, U>, ascending_>
{ PFC_STATIC_ASSERT_MSG(!is_type_class<T>::res, pair_first_type_can_not_be_class_type_for_radix_sort_predicate);
  enum {radix_passes=sizeof(T)};
  enum {radix_range=256};
  PFC_INLINE unsigned radix(const pair<T, U>&, unsigned pass_) const;
};
//----------------------------------------------------------------------------

//============================================================================
// compare_sort_predicate<pair>
//============================================================================
template<typename T, typename U, bool ascending_>
struct compare_sort_predicate<pair<T, U>, ascending_>
{
  PFC_INLINE bool before(const pair<T, U>&, const pair<T, U>&) const;
};
//----------------------------------------------------------------------------


//============================================================================
// value_range
//============================================================================
template<typename T>
struct value_range
{ PFC_MONO(value_range) {PFC_MVAR2(min, range);}
  // construction
  PFC_INLINE value_range();
  PFC_INLINE value_range(const T &min_, const T &range_);
  PFC_INLINE void set(const T &min_, const T &range_);
  template<class Rng> PFC_INLINE T rand_value(Rng&);
  //--------------------------------------------------------------------------

  T min, range;
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, value_range<T>, is_type_pod_move, is_type_pod_move<T>::res);
//----------------------------------------------------------------------------

//============================================================================
#include "utils.inl"
} // namespace pfc
#endif
