//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "expression.h"
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// e_expr_op
//============================================================================
#define PFC_ENUM_NAMESPACE pfc
#define PFC_ENUM_TYPE e_expr_op
#define PFC_ENUM_PREFIX exprop_
#define PFC_ENUM_VALS PFC_ENUM_VAL_N(dot, ".")\
                      PFC_ENUM_VAL_N(ternary, "?:")\
                      PFC_ENUM_VAL_N(add, "+")\
                      PFC_ENUM_VAL_N(sub, "-")\
                      PFC_ENUM_VAL_N(mul, "*")\
                      PFC_ENUM_VAL_N(div, "/")\
                      PFC_ENUM_VAL_N(mod, "%")\
                      PFC_ENUM_VAL_N(inc, "++")\
                      PFC_ENUM_VAL_N(dec, "--")\
                      PFC_ENUM_VAL_N(and, "&&")\
                      PFC_ENUM_VAL_N(or, "||")\
                      PFC_ENUM_VAL_N(not, "!")\
                      PFC_ENUM_VAL_N(eq, "==")\
                      PFC_ENUM_VAL_N(neq, "!=")\
                      PFC_ENUM_VAL_N(lt, "<")\
                      PFC_ENUM_VAL_N(gt, ">")\
                      PFC_ENUM_VAL_N(lte, "<=")\
                      PFC_ENUM_VAL_N(gte, ">=")\
                      PFC_ENUM_VAL_N(bw_and, "&")\
                      PFC_ENUM_VAL_N(bw_or, "|")\
                      PFC_ENUM_VAL_N(bw_not, "~")\
                      PFC_ENUM_VAL_N(bw_xor, "^")\
                      PFC_ENUM_VAL_N(bw_shl, "<<")\
                      PFC_ENUM_VAL_N(bw_shr, ">>")
#include "enum.inc"
//----------------------------------------------------------------------------

e_expr_op pfc::expr_op_parse(const char *s_)
{
  // try to extract operator from the string
  PFC_ASSERT(s_);
  switch(*s_)
  {
    case '.': return exprop_dot;
    case ':': return exprop_ternary;
    case '+': return s_[1]=='+'?exprop_inc:exprop_add;
    case '-': return s_[1]=='-'?exprop_dec:exprop_sub;
    case '*': return exprop_mul;
    case '/': return exprop_div;
    case '%': return exprop_mod;
    case '&': return s_[1]=='&'?exprop_and:exprop_bw_and;
    case '|': return s_[1]=='|'?exprop_or:exprop_bw_or;
    case '!': return exprop_not;
    case '=': return s_[1]=='='?exprop_eq:exprop_none;
    case '<': return s_[1]=='='?exprop_lte:s_[1]=='<'?exprop_bw_shl:exprop_lt;
    case '>': return s_[1]=='='?exprop_gte:s_[1]=='>'?exprop_bw_shr:exprop_gt;
    case '~': return exprop_bw_not;
    case '^': return exprop_bw_xor;
  }
  return exprop_none;
}
//----------------------------------------------------------------------------

uint8_t pfc::expr_op_size(e_expr_op op_)
{
  // return the string size of given expression operator
  switch(op_)
  {
    case exprop_dot:     return 1;
    case exprop_ternary: return 1;
    case exprop_add:     return 1;
    case exprop_sub:     return 1;
    case exprop_mul:     return 1;
    case exprop_div:     return 1;
    case exprop_mod:     return 1;
    case exprop_inc:     return 2;
    case exprop_dec:     return 2;
    case exprop_and:     return 2;
    case exprop_or:      return 2;
    case exprop_not:     return 1;
    case exprop_eq:      return 2;
    case exprop_neq:     return 2;
    case exprop_lt:      return 1;
    case exprop_gt:      return 1;
    case exprop_lte:     return 2;
    case exprop_gte:     return 2;
    case exprop_bw_and:  return 1;
    case exprop_bw_or:   return 1;
    case exprop_bw_not:  return 1;
    case exprop_bw_xor:  return 1;
    case exprop_bw_shl:  return 2;
    case exprop_bw_shr:  return 2;
    default: PFC_ERRORF("Unsupported expression operator (%i)\r\n", op_);
  }
  return 0;
}
//----------------------------------------------------------------------------

uint8_t pfc::expr_op_num_args(e_expr_op op_)
{
  // return number of arguments for the operator
  switch(op_)
  {
    case exprop_dot:     return 2;
    case exprop_ternary: return 3;
    case exprop_add:     return 2;
    case exprop_sub:     return 2;
    case exprop_mul:     return 2;
    case exprop_div:     return 2;
    case exprop_mod:     return 2;
    case exprop_inc:     return 1;
    case exprop_dec:     return 1;
    case exprop_and:     return 2;
    case exprop_or:      return 2;
    case exprop_not:     return 1;
    case exprop_eq:      return 2;
    case exprop_neq:     return 2;
    case exprop_lt:      return 2;
    case exprop_gt:      return 2;
    case exprop_lte:     return 2;
    case exprop_gte:     return 2;
    case exprop_bw_and:  return 2;
    case exprop_bw_or:   return 2;
    case exprop_bw_not:  return 1;
    case exprop_bw_xor:  return 2;
    case exprop_bw_shl:  return 2;
    case exprop_bw_shr:  return 2;
    default: PFC_ERRORF("Unsupported expression operator (%i)\r\n", op_);
  }
  return 0;
}
//----------------------------------------------------------------------------

uint8_t pfc::expr_op_precedence(e_expr_op op_)
{
  // return operator precedence for given expression operator
  switch(op_)
  {
    case exprop_dot:     return 14;  // . 
    case exprop_ternary: return 3;   // ?:
    case exprop_add:     return 12;  // +
    case exprop_sub:     return 12;  // -
    case exprop_mul:     return 13;  // *
    case exprop_div:     return 13;  // /
    case exprop_mod:     return 13;  // %
    case exprop_inc:     return 14;  // ++
    case exprop_dec:     return 14;  // --
    case exprop_and:     return 5;   // &&
    case exprop_or:      return 4;   // ||
    case exprop_not:     return 14;  // !
    case exprop_eq:      return 9;   // ==
    case exprop_neq:     return 9;   // !=
    case exprop_lt:      return 10;  // <
    case exprop_gt:      return 10;  // >
    case exprop_lte:     return 10;  // <=
    case exprop_gte:     return 10;  // >=
    case exprop_bw_and:  return 8;   // &
    case exprop_bw_or:   return 6;   // |
    case exprop_bw_not:  return 14;  // ~
    case exprop_bw_xor:  return 7;   // ^
    case exprop_bw_shl:  return 11;  // <<
    case exprop_bw_shr:  return 11;  // >>
    default: PFC_ERRORF("Unsupported expression operator (%i)\r\n", op_);
  }
  return 0;
}
//----------------------------------------------------------------------------
