//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "crypto.h"
#include "sxp_src/core/math/bit_math.h"
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// md5
//============================================================================
// Can be used to calculate MD5 hash progressively for data in blocks:
//   uint8_t buffer[1024]; // must be multiple of 64
//   md5_hash md5h;
//   for(usize_t data_offs=0; data_offs<data_size; data_offs+=sizeof(buffer))
//   {
//     // load data to the buffer here
//
//     md5(md5h, buffer, sizeof(buffer)/64, data_offs, data_size);
//   }
void pfc::md5(md5_hash &hash_, const void *data_, usize_t max_64byte_chunks_, usize_t data_offset_, usize_t total_num_bytes_)
{
  // process data in 64-byte chunks
  PFC_ASSERT(data_offset_<=total_num_bytes_);
  uint32_t buffer[16];
  const uint8_t *data=(const uint8_t*)data_, *data_end=data-data_offset_+total_num_bytes_;
  unsigned remaining=(64-total_num_bytes_)&63;
  const uint8_t *md5_data_end=data_end+remaining+(remaining<9?64:0);
  bool is_complete=false;
  while(data<md5_data_end && max_64byte_chunks_)
  {
    // fetch data for hashing
    if(data+64<=data_end)
    {
      mem_copy(buffer, data, sizeof(buffer));
      --max_64byte_chunks_;
    }
    else
    {
      mem_zero(buffer, sizeof(buffer));
      ((uint8_t*)buffer)[total_num_bytes_&63]=0x80;
      if(data+(total_num_bytes_&63)==data_end)
        mem_copy(buffer, data, total_num_bytes_&63);
      if(data+64==md5_data_end)
      {
        buffer[14]=uint32_t(total_num_bytes_*8);
        buffer[15]=uint32_t(total_num_bytes_>>29);
        is_complete=true;
      }
    }
    data+=64;

    // define helper macros
    #define F(x__, y__, z__) (z__^(x__&(y__^z__)))
    #define G(x__, y__, z__) (y__^(z__&(y__^x__)))
    #define H(x__, y__, z__) ((x__)^(y__)^(z__))
    #define I(x__, y__, z__) ((y__)^((x__)|(~z__)))
    #define FF(a__, b__, c__, d__, x__, s__, ac__)\
    {\
      (a__)+=F((b__), (c__), (d__))+(x__)+(uint32_t)(ac__);\
      (a__)=rol((a__), (s__));\
      (a__)+=(b__);\
    }
    #define GG(a__, b__, c__, d__, x__, s__, ac__)\
    {\
      (a__)+=G((b__), (c__), (d__))+(x__)+(uint32_t)(ac__);\
      (a__)=rol((a__), (s__));\
      (a__)+=(b__);\
    }
    #define HH(a__, b__, c__, d__, x__, s__, ac__)\
    {\
      (a__)+=H((b__), (c__), (d__))+(x__)+(uint32_t)(ac__);\
      (a__)=rol((a__), (s__));\
      (a__)+=(b__);\
    }
    #define II(a__, b__, c__, d__, x__, s__, ac__)\
    {\
      (a__)+=I((b__), (c__), (d__))+(x__)+(uint32_t)(ac__);\
      (a__)=rol((a__), (s__));\
      (a__)+=(b__);\
    }

    // apply md5 hash transform to the block
    uint32_t a=hash_.h[0], b=hash_.h[1], c=hash_.h[2], d=hash_.h[3];
    FF(a, b, c, d, buffer[ 0],  7, 0xD76AA478);
    FF(d, a, b, c, buffer[ 1], 12, 0xE8C7B756);
    FF(c, d, a, b, buffer[ 2], 17, 0x242070DB);
    FF(b, c, d, a, buffer[ 3], 22, 0xC1BDCEEE);
    FF(a, b, c, d, buffer[ 4],  7, 0xF57C0FAF);
    FF(d, a, b, c, buffer[ 5], 12, 0x4787C62A);
    FF(c, d, a, b, buffer[ 6], 17, 0xA8304613);
    FF(b, c, d, a, buffer[ 7], 22, 0xFD469501);
    FF(a, b, c, d, buffer[ 8],  7, 0x698098D8);
    FF(d, a, b, c, buffer[ 9], 12, 0x8B44F7AF);
    FF(c, d, a, b, buffer[10], 17, 0xFFFF5BB1);
    FF(b, c, d, a, buffer[11], 22, 0x895CD7BE);
    FF(a, b, c, d, buffer[12],  7, 0x6B901122);
    FF(d, a, b, c, buffer[13], 12, 0xFD987193);
    FF(c, d, a, b, buffer[14], 17, 0xA679438E);
    FF(b, c, d, a, buffer[15], 22, 0x49B40821);
    GG(a, b, c, d, buffer[ 1],  5, 0xF61E2562);
    GG(d, a, b, c, buffer[ 6],  9, 0xC040B340);
    GG(c, d, a, b, buffer[11], 14, 0x265E5A51);
    GG(b, c, d, a, buffer[ 0], 20, 0xE9B6C7AA);
    GG(a, b, c, d, buffer[ 5],  5, 0xD62F105D);
    GG(d, a, b, c, buffer[10],  9, 0x02441453);
    GG(c, d, a, b, buffer[15], 14, 0xD8A1E681);
    GG(b, c, d, a, buffer[ 4], 20, 0xE7D3FBC8);
    GG(a, b, c, d, buffer[ 9],  5, 0x21E1CDE6);
    GG(d, a, b, c, buffer[14],  9, 0xC33707D6);
    GG(c, d, a, b, buffer[ 3], 14, 0xF4D50D87);
    GG(b, c, d, a, buffer[ 8], 20, 0x455A14ED);
    GG(a, b, c, d, buffer[13],  5, 0xA9E3E905);
    GG(d, a, b, c, buffer[ 2],  9, 0xFCEFA3F8);
    GG(c, d, a, b, buffer[ 7], 14, 0x676F02D9);
    GG(b, c, d, a, buffer[12], 20, 0x8D2A4C8A);
    HH(a, b, c, d, buffer[ 5],  4, 0xFFFA3942);
    HH(d, a, b, c, buffer[ 8], 11, 0x8771F681);
    HH(c, d, a, b, buffer[11], 16, 0x6D9D6122);
    HH(b, c, d, a, buffer[14], 23, 0xFDE5380C);
    HH(a, b, c, d, buffer[ 1],  4, 0xA4BEEA44);
    HH(d, a, b, c, buffer[ 4], 11, 0x4BDECFA9);
    HH(c, d, a, b, buffer[ 7], 16, 0xF6BB4B60);
    HH(b, c, d, a, buffer[10], 23, 0xBEBFBC70);
    HH(a, b, c, d, buffer[13],  4, 0x289B7EC6);
    HH(d, a, b, c, buffer[ 0], 11, 0xEAA127FA);
    HH(c, d, a, b, buffer[ 3], 16, 0xD4EF3085);
    HH(b, c, d, a, buffer[ 6], 23, 0x04881D05);
    HH(a, b, c, d, buffer[ 9],  4, 0xD9D4D039);
    HH(d, a, b, c, buffer[12], 11, 0xE6DB99E5);
    HH(c, d, a, b, buffer[15], 16, 0x1FA27CF8);
    HH(b, c, d, a, buffer[ 2], 23, 0xC4AC5665);
    II(a, b, c, d, buffer[ 0],  6, 0xF4292244);
    II(d, a, b, c, buffer[ 7], 10, 0x432AFF97);
    II(c, d, a, b, buffer[14], 15, 0xAB9423A7);
    II(b, c, d, a, buffer[ 5], 21, 0xFC93A039);
    II(a, b, c, d, buffer[12],  6, 0x655B59C3);
    II(d, a, b, c, buffer[ 3], 10, 0x8F0CCC92);
    II(c, d, a, b, buffer[10], 15, 0xFFEFF47D);
    II(b, c, d, a, buffer[ 1], 21, 0x85845DD1);
    II(a, b, c, d, buffer[ 8],  6, 0x6FA87E4F);
    II(d, a, b, c, buffer[15], 10, 0xFE2CE6E0);
    II(c, d, a, b, buffer[ 6], 15, 0xA3014314);
    II(b, c, d, a, buffer[13], 21, 0x4E0811A1);
    II(a, b, c, d, buffer[ 4],  6, 0xF7537E82);
    II(d, a, b, c, buffer[11], 10, 0xBD3AF235);
    II(c, d, a, b, buffer[ 2], 15, 0x2AD7D2BB);
    II(b, c, d, a, buffer[ 9], 21, 0xEB86D391);

    // undef helper macros
    #undef FF
    #undef GG
    #undef HH
    #undef II
    #undef F
    #undef G
    #undef H
    #undef I

    // add the transform to the hash
    hash_.h[0]+=a;
    hash_.h[1]+=b;
    hash_.h[2]+=c;
    hash_.h[3]+=d;
  }

  // if md5 hash is equal to the empty md5 value, increment by one
  if(is_complete && !is_valid(hash_))
    ++hash_.h[0];
}
//----------------------------------------------------------------------------


//============================================================================
// md5_to_cstr
//============================================================================
void pfc::md5_to_cstr(md5_cstr_t res_, const md5_hash &h_)
{
  // write md5 as 32-char hex string
  char *r=res_;
  const char *s=(const char*)&h_;
  for(unsigned i=0; i<16; ++i)
  {
    uint8_t v=*s, vlo=v&0xf, vhi=v>>4;
    *r++=vhi+(vhi>9?'a'-10:'0');
    *r++=vlo+(vlo>9?'a'-10:'0');
    ++s;
  }
  *r=0;
}
//----------------------------------------------------------------------------


//============================================================================
// sha256
//============================================================================
void pfc::sha256(sha256_hash &hash_, const void *data_, usize_t max_64byte_chunks_, usize_t data_offset_, usize_t total_num_bytes_)
{
  // process data in 64-byte chunks
  PFC_ASSERT(data_offset_<=total_num_bytes_);
  uint32_t buffer[16];
  const uint8_t *data=(const uint8_t*)data_, *data_end=data-data_offset_+total_num_bytes_;
  unsigned remaining=(64-total_num_bytes_)&63;
  const uint8_t *sha256_data_end=data_end+remaining+(remaining<9?64:0);
  bool is_complete=false;
  while(data<sha256_data_end && max_64byte_chunks_)
  {
    // fetch data for hashing
    if(data+64<=data_end)
    {
      mem_copy(buffer, data, sizeof(buffer));
      --max_64byte_chunks_;
    }
    else
    {
      mem_zero(buffer, sizeof(buffer));
      ((uint8_t*)buffer)[total_num_bytes_&63]=0x80;
      if(data+(total_num_bytes_&63)==data_end)
        mem_copy(buffer, data, total_num_bytes_&63);
      if(data+64==sha256_data_end)
      {
        buffer[14]=to_big_endian(uint32_t(total_num_bytes_>>29));
        buffer[15]=to_big_endian(uint32_t(total_num_bytes_*8));
        is_complete=true;
      }
    }
    data+=64;

    // prepare the message schedule
    #define SIG0(x__) (ror(x__, 7)^ror(x__, 18)^(x__>>3))
    #define SIG1(x__) (ror(x__, 17)^ror(x__, 19)^(x__>>10))
    uint32_t m[64];
    for(unsigned i=0; i<16; ++i)
      m[i]=to_big_endian(buffer[i]);
    for(unsigned i=16; i<64; ++i)
      m[i]=SIG1(m[i-2])+m[i-7]+SIG0(m[i-15])+m[i-16];
    #undef SIG0
    #undef SIG1

    // apply sha256
    static const uint32_t s_k[64]=
    {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	   0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	   0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	   0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	   0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	   0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	   0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	   0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};
    uint32_t h[8];
    mem_copy(h, hash_.h, sizeof(h));
    for(unsigned i=0; i<64; ++i)
    {
      #define CH(x__, y__, z__) ((x__&y__)^(~x__&z__))
      #define MAJ(x__, y__, z__) ((x__&y__)^(x__&z__)^(y__&z__))
      #define EP0(x__) (ror(x__, 2)^ror(x__, 13)^ror(x__, 22))
      #define EP1(x__) (ror(x__, 6)^ror(x__, 11)^ror(x__, 25))
      uint32_t t1=h[7]+EP1(h[4])+CH(h[4], h[5], h[6])+s_k[i]+m[i];
      uint32_t t2=EP0(h[0])+MAJ(h[0], h[1], h[2]);
      mem_move(h+1, h, 7*4);
      h[0]=t1+t2;
      h[4]+=t1;
      #undef CH
      #undef MAJ
      #undef EP0
      #undef EP1
    }
    for(unsigned i=0; i<8; ++i)
      hash_.h[i]+=h[i];
  }

  if(is_complete)
  {
    // finalize hash
    for(unsigned i=0; i<8; ++i)
      hash_.h[i]=to_big_endian(hash_.h[i]);
    if(!is_valid(hash_))
      ++hash_.h[0];
  }
}
//----------------------------------------------------------------------------


//============================================================================
// sha256_to_cstr
//============================================================================
void pfc::sha256_to_cstr(sha256_cstr_t res_, const sha256_hash &h_)
{
  // write md5 as 64-char hex string
  char *r=res_;
  const char *s=(const char*)&h_;
  for(unsigned i=0; i<32; ++i)
  {
    uint8_t v=*s, vlo=v&0xf, vhi=v>>4;
    *r++=vhi+(vhi>9?'a'-10:'0');
    *r++=vlo+(vlo>9?'a'-10:'0');
    ++s;
  }
  *r=0;
}
//----------------------------------------------------------------------------
