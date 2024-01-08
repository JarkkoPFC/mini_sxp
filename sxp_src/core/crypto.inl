//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// md5_hash
//============================================================================
md5_hash::md5_hash()
{
  // init md5 hash
  h[0]=0x67452301;
  h[1]=0xefcdab89;
  h[2]=0x98badcfe;
  h[3]=0x10325476;
}
//----

template<>
struct hash_func<md5_hash>
{
  static PFC_INLINE unsigned index(const md5_hash &h_)
  {
    return h_.h[0]^h_.h[1]^h_.h[2]^h_.h[3];
  }
};
//----------------------------------------------------------------------------

PFC_INLINE md5_hash md5(const void *data_, usize_t num_bytes_)
{
  md5_hash h;
  md5(h, data_, usize_t(-1), 0, num_bytes_);
  return h;
}
//----

PFC_INLINE md5_hash md5(const char *cstr_)
{
  md5_hash h;
  md5(h, cstr_, usize_t(-1), 0, str_size(cstr_));
  return h;
}
//----------------------------------------------------------------------------

PFC_INLINE bool is_valid(const md5_hash &h_)
{
  return h_.h[0]!=0x67452301 || h_.h[1]!=0xefcdab89 || h_.h[2]!=0x98badcfe || h_.h[3]!=0x10325476;
}
//----

PFC_INLINE bool operator==(const md5_hash &h0_, const md5_hash &h1_)
{
  return mem_eq(&h0_, &h1_, sizeof(h0_));
}
//----

PFC_INLINE bool operator!=(const md5_hash &h0_, const md5_hash &h1_)
{
  return !mem_eq(&h0_, &h1_, sizeof(h0_));
}
//----

PFC_INLINE bool operator<(const md5_hash &h0_, const md5_hash &h1_)
{
  return  h0_.h[3]<h1_.h[3] || (h0_.h[3]==h1_.h[3] &&
         (h0_.h[2]<h1_.h[2] || (h0_.h[2]==h1_.h[2] &&
         (h0_.h[1]<h1_.h[1] || (h0_.h[1]==h1_.h[1] &&
          h0_.h[0]<h1_.h[0])))));
}
//----

PFC_INLINE bool operator>(const md5_hash &h0_, const md5_hash &h1_)
{
  return  h0_.h[3]>h1_.h[3] || (h0_.h[3]==h1_.h[3] &&
         (h0_.h[2]>h1_.h[2] || (h0_.h[2]==h1_.h[2] &&
         (h0_.h[1]>h1_.h[1] || (h0_.h[1]==h1_.h[1] &&
          h0_.h[0]>h1_.h[0])))));
}
//----

PFC_INLINE bool operator<=(const md5_hash &h0_, const md5_hash &h1_)
{
  return  h0_.h[3]<h1_.h[3] || (h0_.h[3]==h1_.h[3] &&
         (h0_.h[2]<h1_.h[2] || (h0_.h[2]==h1_.h[2] &&
         (h0_.h[1]<h1_.h[1] || (h0_.h[1]==h1_.h[1] &&
          h0_.h[0]<=h1_.h[0])))));
}
//----

PFC_INLINE bool operator>=(const md5_hash &h0_, const md5_hash &h1_)
{
  return  h0_.h[3]>h1_.h[3] || (h0_.h[3]==h1_.h[3] &&
         (h0_.h[2]>h1_.h[2] || (h0_.h[2]==h1_.h[2] &&
         (h0_.h[1]>h1_.h[1] || (h0_.h[1]==h1_.h[1] &&
          h0_.h[0]>=h1_.h[0])))));
}
//----------------------------------------------------------------------------


//============================================================================
// sha256_hash
//============================================================================
sha256_hash::sha256_hash()
{
  h[0]=0x6a09e667;
  h[1]=0xbb67ae85;
  h[2]=0x3c6ef372;
  h[3]=0xa54ff53a;
  h[4]=0x510e527f;
  h[5]=0x9b05688c;
  h[6]=0x1f83d9ab;
  h[7]=0x5be0cd19;
}
//----

template<>
struct hash_func<sha256_hash>
{
  static PFC_INLINE unsigned index(const sha256_hash &h_)
  {
    return h_.h[0]^h_.h[1]^h_.h[2]^h_.h[3]^
           h_.h[4]^h_.h[5]^h_.h[6]^h_.h[7];
  }
};
//----------------------------------------------------------------------------

PFC_INLINE sha256_hash sha256(const void *data_, usize_t num_bytes_)
{
  sha256_hash h;
  sha256(h, data_, usize_t(-1), 0, num_bytes_);
  return h;
}
//----

PFC_INLINE sha256_hash sha256(const char *cstr_)
{
  sha256_hash h;
  sha256(h, cstr_, usize_t(-1), 0, str_size(cstr_));
  return h;
}
//----------------------------------------------------------------------------

PFC_INLINE bool is_valid(const sha256_hash &h_)
{
  return    h_.h[0]!=0x6a09e667 || h_.h[1]!=0xbb67ae85 || h_.h[2]!=0x3c6ef372 || h_.h[3]!=0xa54ff53a
         || h_.h[4]!=0x510e527f || h_.h[5]!=0x9b05688c || h_.h[6]!=0x1f83d9ab || h_.h[7]!=0x5be0cd19;
}
//----

PFC_INLINE bool operator==(const sha256_hash &h0_, const sha256_hash &h1_)
{
  return mem_eq(&h0_, &h1_, sizeof(h0_));
}
//----

PFC_INLINE bool operator!=(const sha256_hash &h0_, const sha256_hash &h1_)
{
  return !mem_eq(&h0_, &h1_, sizeof(h0_));
}
//----

PFC_INLINE bool operator<(const sha256_hash &h0_, const sha256_hash &h1_)
{
  return  h0_.h[7]<h1_.h[7] || (h0_.h[7]==h1_.h[7] &&
         (h0_.h[6]<h1_.h[6] || (h0_.h[6]==h1_.h[6] &&
         (h0_.h[5]<h1_.h[5] || (h0_.h[5]==h1_.h[5] &&
         (h0_.h[4]<h1_.h[4] || (h0_.h[4]==h1_.h[4] &&
         (h0_.h[3]<h1_.h[3] || (h0_.h[3]==h1_.h[3] &&
         (h0_.h[2]<h1_.h[2] || (h0_.h[2]==h1_.h[2] &&
         (h0_.h[1]<h1_.h[1] || (h0_.h[1]==h1_.h[1] &&
          h0_.h[0]<h1_.h[0])))))))))))));
}
//----

PFC_INLINE bool operator>(const sha256_hash &h0_, const sha256_hash &h1_)
{
  return  h0_.h[7]>h1_.h[7] || (h0_.h[7]==h1_.h[7] &&
         (h0_.h[6]>h1_.h[6] || (h0_.h[6]==h1_.h[6] &&
         (h0_.h[5]>h1_.h[5] || (h0_.h[5]==h1_.h[5] &&
         (h0_.h[4]>h1_.h[4] || (h0_.h[4]==h1_.h[4] &&
         (h0_.h[3]>h1_.h[3] || (h0_.h[3]==h1_.h[3] &&
         (h0_.h[2]>h1_.h[2] || (h0_.h[2]==h1_.h[2] &&
         (h0_.h[1]>h1_.h[1] || (h0_.h[1]==h1_.h[1] &&
          h0_.h[0]>h1_.h[0])))))))))))));
}
//----

PFC_INLINE bool operator<=(const sha256_hash &h0_, const sha256_hash &h1_)
{
  return  h0_.h[7]<h1_.h[7] || (h0_.h[7]==h1_.h[7] &&
         (h0_.h[6]<h1_.h[6] || (h0_.h[6]==h1_.h[6] &&
         (h0_.h[5]<h1_.h[5] || (h0_.h[5]==h1_.h[5] &&
         (h0_.h[4]<h1_.h[4] || (h0_.h[4]==h1_.h[4] &&
         (h0_.h[3]<h1_.h[3] || (h0_.h[3]==h1_.h[3] &&
         (h0_.h[2]<h1_.h[2] || (h0_.h[2]==h1_.h[2] &&
         (h0_.h[1]<h1_.h[1] || (h0_.h[1]==h1_.h[1] &&
          h0_.h[0]<=h1_.h[0])))))))))))));
}
//----

PFC_INLINE bool operator>=(const sha256_hash &h0_, const sha256_hash &h1_)
{
  return  h0_.h[7]>h1_.h[7] || (h0_.h[7]==h1_.h[7] &&
         (h0_.h[6]>h1_.h[6] || (h0_.h[6]==h1_.h[6] &&
         (h0_.h[5]>h1_.h[5] || (h0_.h[5]==h1_.h[5] &&
         (h0_.h[4]>h1_.h[4] || (h0_.h[4]==h1_.h[4] &&
         (h0_.h[3]>h1_.h[3] || (h0_.h[3]==h1_.h[3] &&
         (h0_.h[2]>h1_.h[2] || (h0_.h[2]==h1_.h[2] &&
         (h0_.h[1]>h1_.h[1] || (h0_.h[1]==h1_.h[1] &&
          h0_.h[0]>=h1_.h[0])))))))))))));
}
//----------------------------------------------------------------------------
