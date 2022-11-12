//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// enumerated value function definitions
//============================================================================
// define the following macros before including this file:
// #define PFC_ENUM_NAMESPACE my_namespace
// #define PFC_ENUM_TYPE e_my_enum_type
// #define PFC_ENUM_PREFIX mytypeprefix_
// #define PFC_ENUM_VALS PFC_ENUM_VAL(val1)\   // = mytypeprefix_val1
//                       PFC_ENUM_VAL(val2)\   // = mytypeprefix_val2
//                       PFC_ENUM_VAL_N(val3, "Value 3")
#ifndef PFC_ENUM_PREFIX
#define PFC_ENUM_PREFIX
#endif
#ifdef PFC_ENUM_NAMESPACE
namespace PFC_ENUM_NAMESPACE {
#endif
//----

#define PFC_ENUM_VAL(eval__) PFC_STR(eval__),
#define PFC_ENUM_VAL_N(eval__, name__) PFC_STR(eval__),
const char *const*enum_strings(PFC_ENUM_TYPE)
{
  static const char *s_strings[]=
  {
    "<unknown>",
    PFC_ENUM_VALS
    0,
  };
  return s_strings;
}
#undef PFC_ENUM_VAL
#undef PFC_ENUM_VAL_N
//----

#define PFC_ENUM_VAL(eval__) PFC_STR(eval__),
#define PFC_ENUM_VAL_N(eval__, name__) name__,
const char *const*enum_display_strings(PFC_ENUM_TYPE)
{
  static const char *s_strings[]=
  {
    "<unknown>",
    PFC_ENUM_VALS
    0,
  };
  return s_strings;
}
#undef PFC_ENUM_VAL
#undef PFC_ENUM_VAL_N
//----

bool enum_dep_value(PFC_ENUM_TYPE &v_, const char *enum_str_)
{
#ifdef PFC_ENUM_DEP_VALS
  #define PFC_ENUM_DEP_VAL(dep_eval__, new_eval__) PFC_STR(dep_eval__),
  static const char *s_dep_strings[]=
  {
    PFC_ENUM_DEP_VALS
    0
  };
  #undef PFC_ENUM_DEP_VAL
  #define PFC_ENUM_DEP_VAL(dep_eval__, new_eval__) PFC_CAT2(PFC_ENUM_PREFIX, new_eval__),
  static PFC_ENUM_TYPE s_dep_vals[]=
  {
    PFC_ENUM_DEP_VALS
  };
  #undef PFC_ENUM_DEP_VAL
  extern int str_find_substr(const char*, const char*const*);
  int vidx=str_find_substr(enum_str_, s_dep_strings);
  if(vidx>=0)
  {
    v_=s_dep_vals[vidx];
    return true;
  }
#endif
  return false;
}
//----

#define PFC_ENUM_VAL(eval__) PFC_CAT2(PFC_ENUM_PREFIX, eval__),
#define PFC_ENUM_VAL_N(eval__, name__) PFC_CAT2(PFC_ENUM_PREFIX, eval__),
const PFC_ENUM_TYPE *enum_values(PFC_ENUM_TYPE)
{
  static const PFC_ENUM_TYPE s_vals[]=
  {
    PFC_ENUM_TYPE(0),
    PFC_ENUM_VALS
    PFC_ENUM_TYPE(0)
  };
  return s_vals;
}
#undef PFC_ENUM_VAL
#undef PFC_ENUM_VAL_N
//----

unsigned enum_string_index(PFC_ENUM_TYPE eval_)
{
  // setup static enumeration value indices
  static unsigned s_counter=0;
  #define PFC_ENUM_VAL(eval__) static const unsigned s_index_##eval__=++s_counter;
  #define PFC_ENUM_VAL_N(eval__, name__) static const unsigned s_index_##eval__=++s_counter;
  PFC_ENUM_VALS
  #undef PFC_ENUM_VAL
  #undef PFC_ENUM_VAL_N

  // return enumeration value index
  #define PFC_ENUM_VAL(eval__) case PFC_CAT2(PFC_ENUM_PREFIX, eval__): return s_index_##eval__;
  #define PFC_ENUM_VAL_N(eval__, name__) case PFC_CAT2(PFC_ENUM_PREFIX, eval__): return s_index_##eval__;
  switch(unsigned(eval_))
  {
    PFC_ENUM_VALS
  }
  #undef PFC_ENUM_VAL
  #undef PFC_ENUM_VAL_N
  return 0;
}
#undef PFC_ENUM_VAL_N
//----------------------------------------------------------------------------
#ifdef PFC_ENUM_NAMESPACE
}
#endif

#undef PFC_ENUM_NAMESPACE
#undef PFC_ENUM_TYPE
#undef PFC_ENUM_PREFIX
#undef PFC_ENUM_VALS
#undef PFC_ENUM_DEP_VALS
//----------------------------------------------------------------------------
