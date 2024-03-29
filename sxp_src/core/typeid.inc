//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

// fundamental data type IDs
PFC_STATIC_TYPEID(void,           0x80000000);
PFC_STATIC_TYPEID(bool,           0x80000001);
PFC_STATIC_TYPEID(char,           0x80000002);
PFC_STATIC_TYPEID(signed char,    0x80000003);
PFC_STATIC_TYPEID(unsigned char,  0x80000004);
PFC_STATIC_TYPEID(signed short,   0x80000005);
PFC_STATIC_TYPEID(unsigned short, 0x80000006);
PFC_STATIC_TYPEID(signed int,     0x80000007);
PFC_STATIC_TYPEID(unsigned int,   0x80000008);
PFC_STATIC_TYPEID(signed long,    0x80000009);
PFC_STATIC_TYPEID(unsigned long,  0x8000000a);
#if PFC_INT64_CPP_TYPE==0
PFC_STATIC_TYPEID(int64_t,        0x8000000b);
PFC_STATIC_TYPEID(uint64_t,       0x8000000c);
#endif
PFC_STATIC_TYPEID(float,          0x8000000d);
PFC_STATIC_TYPEID(double,         0x8000000e);
PFC_STATIC_TYPEID(long double,    0x8000000f);
//----------------------------------------------------------------------------
