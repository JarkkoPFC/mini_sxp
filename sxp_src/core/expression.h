//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_EXPRESSION_H
#define PFC_CORE_EXPRESSION_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "containers.h"
#include "sort.h"
#include "functor.h"
namespace pfc
{

// new
template<class Config> class expression_parser;
template<typename> struct expression_parser_config;
//----------------------------------------------------------------------------


//============================================================================
// e_expr_op
//============================================================================
enum e_expr_op
{
  exprop_none,
  // misc
  exprop_dot,     // .
  exprop_ternary, // ?:
  // math ops
  exprop_add,     // +
  exprop_sub,     // -
  exprop_mul,     // *
  exprop_div,     // /
  exprop_mod,     // %
  exprop_inc,     // ++
  exprop_dec,     // --
  // logical ops
  exprop_and,     // &&
  exprop_or,      // ||
  exprop_not,     // !
  // comparison ops
  exprop_eq,      // ==
  exprop_neq,     // !=
  exprop_lt,      // <
  exprop_gt,      // >
  exprop_lte,     // <=
  exprop_gte,     // >=
  // bitwise ops
  exprop_bw_and,  // &
  exprop_bw_or,   // |
  exprop_bw_not,  // ~
  exprop_bw_xor,  // ^
  exprop_bw_shl,  // <<
  exprop_bw_shr,  // >>
};
PFC_ENUM(e_expr_op);
//----

e_expr_op expr_op_parse(const char*);
uint8_t expr_op_size(e_expr_op);
uint8_t expr_op_num_args(e_expr_op);
uint8_t expr_op_precedence(e_expr_op);
//----------------------------------------------------------------------------


//============================================================================
// expression_parser
//============================================================================
template<class Config>
class expression_parser
{
public:
  // nested
  typedef typename Config::var_t var_t;
  typedef typename Config::id_str_t id_str_t;
  typedef typename Config::extra_var_container_t extra_var_container_t;
  typedef typename Config::var_stack_t var_stack_t;
  typedef functor<void(int, var_stack_t&)> functor_t;
  //--------------------------------------------------------------------------

  // construction
  expression_parser();
  ~expression_parser();
  void clear_variables();
  void clear_functions();
  void clear_operators();
  void clear();
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE const var_t *var(const char *var_name_) const;
  PFC_INLINE const functor_t *func(const char *func_name_) const;
  PFC_INLINE const functor_t *op(e_expr_op) const;
  //--------------------------------------------------------------------------

  // expression evaluation
  void set_var(const char *var_name_, const var_t&);
  void set_func(const char *func_name_, const functor_t&);
  void set_op(e_expr_op, const functor_t&);
  var_t evaluate(const char *expression_, const extra_var_container_t *extra_vars_=0, functor_t wrap_func_=functor_t()) const;
  //--------------------------------------------------------------------------

private:
  struct func_stack_entry {uint8_t eop, eop_prec; functor_t func;};
  typedef array<func_stack_entry> func_stack_t;
  expression_parser(const expression_parser&); // not implemented
  void operator=(const expression_parser&); // not implemented
  //--------------------------------------------------------------------------

  // parsing
  uint8_t parse_identifier(var_stack_t&, func_stack_t&, const char*, const extra_var_container_t*) const;
  uint8_t parse_operator(var_stack_t&, func_stack_t&, const char*) const;
  void eval_func_stack(var_stack_t&, func_stack_t&, int precedence_) const;
  //--------------------------------------------------------------------------

  hash_map<id_str_t, var_t> m_vars;
  hash_map<id_str_t, functor_t> m_funcs;
  hash_map<e_expr_op, functor_t> m_ops;
};
//----------------------------------------------------------------------------


//============================================================================
// expression_parser_config
//============================================================================
template<typename T>
struct expression_parser_config
{
  typedef T var_t;
  typedef str_id id_str_t;
  typedef array<var_t> var_stack_t;
  typedef hash_map<str_id, var_t> extra_var_container_t;
  //--------------------------------------------------------------------------

  static PFC_INLINE bool push_var(var_stack_t&, const extra_var_container_t&, const id_str_t&);
  static PFC_INLINE T from_scalar(float64_t);
  static PFC_INLINE T from_scalar(int64_t);
  static PFC_INLINE T from_str(const char *str_, usize_t str_len_);
};
//----------------------------------------------------------------------------

//============================================================================
#include "expression.inl"
} // namespace pfc
#endif
