//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_WIN_CORE_MSVC_H
#define PFC_WIN_CORE_MSVC_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#define NOMINMAX
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "win_core.h"
#include <intrin.h>
namespace pfc
{

// new
#define PFC_INLINE __forceinline
#ifdef PFC_DEBUG
#define PFC_ABORT_FUNC() {__debugbreak();}
#else
#define PFC_ABORT_FUNC() {exit(-1);}
#endif
#define PFC_STRICMP ::_stricmp
#define PFC_WCSICMP ::_wcsicmp
#define PFC_STRNICMP ::_strnicmp
#define PFC_WCSNICMP ::_wcsnicmp
#define PFC_FUNCTION __FUNCTION__
//----------------------------------------------------------------------------


//============================================================================
// disabled MSVC warnings
//============================================================================
#pragma warning(disable:4100)  // "'identifier' : unreferenced formal parameter"
#pragma warning(disable:4127)  // "conditional expression is constant"
#pragma warning(disable:4324)  // "structure was padded due to __declspec(align())"
#pragma warning(disable:4505)  // "'function' : unreferenced local function has been removed"
#pragma warning(disable:4996)  // "'function' : was declared deprecated"
#pragma warning(disable:6326)  // "potential comparison of a constant with another constant"
#if defined(PFC_RELEASE) || defined(PFC_RETAIL)
#pragma warning(disable:4702)  // "unreachable code"
#endif
#ifdef PFC_RETAIL
#pragma warning(disable:4930)  // "'prototype': prototyped function not called (was a variable definition intended?)"
#endif
//----------------------------------------------------------------------------


//============================================================================
// alignment macros
//============================================================================
#define PFC_ALIGN(v__) __declspec(align(v__))
#define PFC_ALIGN_CACHE __declspec(align(128))
//----------------------------------------------------------------------------


//============================================================================
// memory allocation
//============================================================================
#define PFC_ALIGNED_MALLOC(size__, align__) _aligned_malloc((size_t)size__, align__)
#define PFC_ALIGNED_FREE(ptr__) _aligned_free(ptr__)
//----------------------------------------------------------------------------


//============================================================================
// heap check macro
//============================================================================
#ifdef PFC_BUILDOP_HEAP_CHECKS
} // namespace pfc
#include <crtdbg.h>
namespace pfc {
#define PFC_CHECK_HEAP() PFC_CHECK_MSG(_CrtCheckMemory(), ("Heap is corrupted\r\n"));
#endif
//----------------------------------------------------------------------------

  
//============================================================================
// misc
//============================================================================
#define PFC_THREAD_VAR __declspec(thread)
//----------------------------------------------------------------------------


//============================================================================
// fundamental data types
//============================================================================
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#define PFC_CONST_INT64(v__) int64_t(v__)
#define PFC_CONST_UINT64(v__) uint64_t(v__)
#define PFC_INT64_CPP_TYPE 0
//----------------------------------------------------------------------------


//============================================================================
// compiler intrinsics
//============================================================================
// CRT intrinsics
#pragma intrinsic(abs, _abs64, labs)
#pragma intrinsic(_byteswap_ushort, _byteswap_ulong, _byteswap_uint64)
#pragma intrinsic(_rotl, _rotl64, _lrotl, _rotr, _rotr64, _lrotr)
#pragma intrinsic(memcmp, memcpy, memset)
// math intrinsics
#pragma intrinsic(cos, sin, tan)
#pragma intrinsic(acos, asin, atan, atan2)
#pragma intrinsic(cosh, sinh, tanh)
#pragma intrinsic(exp, log, log10, pow, sqrt)
#pragma intrinsic(floor)
#pragma intrinsic(fmod)
// x86 specific intrinsics
#pragma intrinsic(_BitScanForward, _BitScanReverse)
#pragma intrinsic(_rotl8, _rotl16)
#pragma intrinsic(_rotr8, _rotr16)
#pragma intrinsic(__popcnt)
//----------------------------------------------------------------------------


//============================================================================
// intrinsic macros
//============================================================================
#ifdef PFC_BUILDOP_INTRINSICS
// up to 32-bit intrinsics
#define PFC_INTRINSIC_LSB32(res__, v__)           {unsigned long __intrinsic_res; _BitScanForward(&__intrinsic_res, v__); res__=uint32_t(1)<<uint8_t(__intrinsic_res);}
#define PFC_INTRINSIC_MSB32(res__, v__)           {unsigned long __intrinsic_res; _BitScanReverse(&__intrinsic_res, v__); res__=uint32_t(1)<<uint8_t(__intrinsic_res);}
#define PFC_INTRINSIC_LSBPOS32(res__, v__)        {unsigned long __intrinsic_res; _BitScanForward(&__intrinsic_res, v__); res__=uint8_t(__intrinsic_res);}
#define PFC_INTRINSIC_MSBPOS32(res__, v__)        {unsigned long __intrinsic_res; _BitScanReverse(&__intrinsic_res, v__); res__=uint8_t(__intrinsic_res);}
#define PFC_INTRINSIC_BSWAP32(res__, v__)         {res__=(uint32_t)_byteswap_ulong(*reinterpret_cast<const volatile uint32_t*>(v__));}
#define PFC_INTRINSIC_BSWAP16(res__, v__)         {res__=(uint16_t)_byteswap_ushort(*reinterpret_cast<const volatile uint16_t*>(v__));}
#define PFC_INTRINSIC_ROL32(res__, v__, shift__)  {res__=_rotl(v__, shift__);}
#define PFC_INTRINSIC_ROR32(res__, v__, shift__)  {res__=_rotr(v__, shift__);}
#define PFC_INTRINSIC_ROL16(res__, v__, shift__)  {res__=_rotl16(v__, shift__);}
#define PFC_INTRINSIC_ROR16(res__, v__, shift__)  {res__=_rotr16(v__, shift__);}
#define PFC_INTRINSIC_ROL8(res__, v__, shift__)   {res__=_rotl8(v__, shift__);}
#define PFC_INTRINSIC_ROR8(res__, v__, shift__)   {res__=_rotr8(v__, shift__);}
#define PFC_INTRINSIC_POPCNT(res__, v__)          {res__=__popcnt(v__);}
//----
#ifdef PFC_PLATFORM_64BIT
// 64-bit intrinsics
#define PFC_INTRINSIC_LSB64(res__, v__)           {unsigned long __intrinsic_res; _BitScanForward64(&__intrinsic_res, v__); res__=uint64_t(1)<<uint8_t(__intrinsic_res);}
#define PFC_INTRINSIC_MSB64(res__, v__)           {unsigned long __intrinsic_res; _BitScanReverse64(&__intrinsic_res, v__); res__=uint64_t(1)<<uint8_t(__intrinsic_res);}
#define PFC_INTRINSIC_LSBPOS64(res__, v__)        {unsigned long __intrinsic_res; _BitScanForward64(&__intrinsic_res, v__); res__=uint8_t(__intrinsic_res);}
#define PFC_INTRINSIC_MSBPOS64(res__, v__)        {unsigned long __intrinsic_res; _BitScanReverse64(&__intrinsic_res, v__); res__=uint8_t(__intrinsic_res);}
#define PFC_INTRINSIC_BSWAP64(res__, v__)         {res__=(uint64_t)_byteswap_uint64(*reinterpret_cast<const volatile uint64_t*>(v__));}
#define PFC_INTRINSIC_ROL64(res__, v__, shift__)  {res__=_rotl64(v__, shift__);}
#define PFC_INTRINSIC_ROR64(res__, v__, shift__)  {res__=_rotr64(v__, shift__);}
#define PFC_INTRINSIC_POPCNT64(res__, v__)        {res__=__popcnt64(v__);}
#endif
#endif
//----
#ifdef PFC_BUILDOP_INTRINSICS_BMI2
// BMI2 intrinsics
#define PFC_INTRINSIC_PDEP32(res__, v__, mask__)  {res__=_pdep_u32(v__, mask__);}
#define PFC_INSTINSIC_PEXT32(res__, v__, mask__)  {res__=_pext_u32(v__, mask__);}
#endif
//----------------------------------------------------------------------------


//============================================================================
// timing
//============================================================================
PFC_INLINE uint64_t get_thread_cycles()
{
  return __rdtsc();
}
//----------------------------------------------------------------------------

//============================================================================
} // namespace pfc
#endif
