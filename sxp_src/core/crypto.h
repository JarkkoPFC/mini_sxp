//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_CRYPTO_H
#define PFC_CORE_CRYPTO_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "utils.h"
namespace pfc
{
template<typename T> class array;

// new
// md5
struct md5_hash;
void md5(md5_hash&, const void*, usize_t max_64byte_chunks_, usize_t data_offset_, usize_t total_num_bytes_);
PFC_INLINE md5_hash md5(const void*, usize_t num_bytes_);
PFC_INLINE md5_hash md5(const char*);
typedef char md5_cstr_t[33];
void md5_to_cstr(md5_cstr_t, const md5_hash&);
PFC_INLINE bool is_valid(const md5_hash&);
PFC_INLINE bool operator==(const md5_hash&, const md5_hash&);
PFC_INLINE bool operator!=(const md5_hash&, const md5_hash&);
PFC_INLINE bool operator<(const md5_hash&, const md5_hash&);
PFC_INLINE bool operator>(const md5_hash&, const md5_hash&);
PFC_INLINE bool operator<=(const md5_hash&, const md5_hash&);
PFC_INLINE bool operator>=(const md5_hash&, const md5_hash&);
// sha256
struct sha256_hash;
void sha256(sha256_hash&, const void*, usize_t max_64byte_chunks_, usize_t data_offset_, usize_t total_num_bytes_);
PFC_INLINE sha256_hash sha256(const void*, usize_t num_bytes_);
PFC_INLINE sha256_hash sha256(const char*);
typedef char sha256_cstr_t[65];
void sha256_to_cstr(sha256_cstr_t, const sha256_hash&);
PFC_INLINE bool is_valid(const sha256_hash&);
PFC_INLINE bool operator==(const sha256_hash&, const sha256_hash&);
PFC_INLINE bool operator!=(const sha256_hash&, const sha256_hash&);
PFC_INLINE bool operator<(const sha256_hash&, const sha256_hash&);
PFC_INLINE bool operator>(const sha256_hash&, const sha256_hash&);
PFC_INLINE bool operator<=(const sha256_hash&, const sha256_hash&);
PFC_INLINE bool operator>=(const sha256_hash&, const sha256_hash&);
// PEM helpers
void pem_to_der(array<uint8_t>&, const char *pem_str_);
//----------------------------------------------------------------------------


//============================================================================
// md5_hash
//============================================================================
struct md5_hash
{ PFC_MONO(md5_hash) {PFC_AVAR(h, 4);}
  // construction
  PFC_INLINE md5_hash();
  //--------------------------------------------------------------------------

  uint32_t h[4];
};
PFC_SET_TYPE_TRAIT(md5_hash, is_type_pod, true);
PFC_SET_TYPE_TRAIT(md5_hash, is_type_pod_def_ctor, false);
//----------------------------------------------------------------------------


//============================================================================
// sha256_hash
//============================================================================
struct sha256_hash
{ PFC_MONO(sha256_hash) {PFC_AVAR(h, 8);}
  // construction
  PFC_INLINE sha256_hash();
  //--------------------------------------------------------------------------

  uint32_t h[8];
};
PFC_SET_TYPE_TRAIT(sha256_hash, is_type_pod, true);
PFC_SET_TYPE_TRAIT(sha256_hash, is_type_pod_def_ctor, false);
//----------------------------------------------------------------------------

//============================================================================
#include "crypto.inl"
} // namespace pfc
#endif
