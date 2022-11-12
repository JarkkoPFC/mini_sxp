//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// expression_parser
//============================================================================
template<class Config>
expression_parser<Config>::expression_parser()
{
}
//----

template<class Config>
expression_parser<Config>::~expression_parser()
{
}
//----

template<class Config>
void expression_parser<Config>::clear_variables()
{
  m_vars.clear();
}
//----

template<class Config>
void expression_parser<Config>::clear_functions()
{
  m_funcs.clear();
}
//----

template<class Config>
void expression_parser<Config>::clear_operators()
{
  m_ops.clear();
}
//----

template<class Config>
void expression_parser<Config>::clear()
{
  m_vars.clear();
  m_funcs.clear();
  m_ops.clear();
}
//----------------------------------------------------------------------------

template<class Config>
const typename expression_parser<Config>::var_t *expression_parser<Config>::var(const char *var_name_) const
{
  return ptr(m_vars.find(var_name_));
}
//----

template<class Config>
const typename expression_parser<Config>::functor_t *expression_parser<Config>::func(const char *func_name_) const
{
  return ptr(m_funcs.find(func_name_));
}
//----

template<class Config>
const typename expression_parser<Config>::functor_t *expression_parser<Config>::op(e_expr_op op_) const
{
  return ptr(m_ops.find(func_name_));
}
//----------------------------------------------------------------------------

template<class Config>
void expression_parser<Config>::set_var(const char *var_name_, const var_t &var_)
{
  m_vars.insert(var_name_, var_);
}
//----

template<class Config>
void expression_parser<Config>::set_func(const char *func_name_, const functor_t &func_fun_)
{
  m_funcs.insert(func_name_, func_fun_);
}
//----

template<class Config>
void expression_parser<Config>::set_op(e_expr_op op_, const functor_t &op_fun_)
{
  m_ops.insert(op_, op_fun_);
}
//----

template<class Config>
typename Config::var_t expression_parser<Config>::evaluate(const char *expression_, const extra_var_container_t *extra_vars_, functor_t wrap_func_) const
{
  // setup evaluator state
  const char *expr=expression_;
  var_stack_t var_stack;
  func_stack_t func_stack;
  enum {max_nested_funcs=32};
  unsigned func_arg_stack[max_nested_funcs];
  int func_arg_stack_pos=-1;
  bool is_func_arg=false;

  // setup state for wrapper function
  if(wrap_func_)
  {
    func_stack_entry fe={0, 0, wrap_func_};
    func_stack.push_back(fe);
    func_arg_stack[++func_arg_stack_pos]=0;
    is_func_arg=true;
  }

  // evaluate the expression using Shunting-yard algorithm
  while(*expr)
  {
    // test for whitespace
    char c=*expr;
    if(is_whitespace(c))
    {
      ++expr;
      continue;
    }

    // process token
    uint8_t element_size=parse_operator(var_stack, func_stack, expr);
    if(!element_size)
    {
      unsigned old_func_stack_size=(unsigned)func_stack.size();
      element_size=parse_identifier(var_stack, func_stack, expr, extra_vars_);
      if(element_size && is_func_arg)
      {
        ++func_arg_stack[func_arg_stack_pos];
        is_func_arg=false;
      }
      if(old_func_stack_size!=func_stack.size())
      {
        ++func_arg_stack_pos;
        PFC_ASSERT(func_arg_stack_pos<max_nested_funcs);
        func_arg_stack[func_arg_stack_pos]=0;
        is_func_arg=true;
      }
    }
    if(!element_size)
    {
      element_size=1;
      switch(c)
      {
        // function argument separator
        case ',': is_func_arg=true;
        case '?':
        {
          while(func_stack.size() && func_stack.back().eop_prec)
          {
            const func_stack_entry &fe=func_stack.back();
            uint8_t num_eop_args=expr_op_num_args((e_expr_op)fe.eop);
            fe.func(num_eop_args, var_stack);
            func_stack.pop_back();
          }
        } break;

        // opening scope
        case '(':
        {
          func_stack_entry fe={0, 0, 0};
          func_stack.push_back(fe);
        } break;

        // closing scope/end-of-function-argument
        case ')':
        {
          // execute operators in the function stack (until func/scope)
          while(func_stack.back().eop_prec)
          {
            const func_stack_entry &fe=func_stack.back();
            uint8_t num_eop_args=expr_op_num_args((e_expr_op)fe.eop);
            fe.func(num_eop_args, var_stack);
            func_stack.pop_back();
          }

          // execute function or end-of-scope
          if(func_stack.back().func)
          {
            func_stack.back().func(func_arg_stack[func_arg_stack_pos], var_stack);
            --func_arg_stack_pos;
          }
          func_stack.pop_back();
        } break;

        // unknown token (interpret as string type)
        default:
        {
          const char *str=expr;
          while(!is_whitespace(*str) && *str!=',' && *str!='?' && *str!='(' && *str!=')' && !expr_op_parse(str))
            ++str;
          element_size=uint8_t(str-expr);
          var_stack.push_back(Config::from_str(expr, element_size));
        } break;
      }
    }
    expr+=element_size;
  }
                                                              
  // evaluate remaining functions and return the result from the top of the variable stack
  if(!var_stack.size())
    return Config::var_t();
  eval_func_stack(var_stack, func_stack, -1);
  PFC_ASSERT(var_stack.size()==1);
  return var_stack.back();
}
//----------------------------------------------------------------------------

template<class Config>
uint8_t expression_parser<Config>::parse_identifier(var_stack_t &var_stack_, func_stack_t &func_stack_, const char *s_, const extra_var_container_t *extra_vars_) const
{
  // check for string literal
  char sc=*s_;
  if(sc=='\"' || sc=='\'')
  {
    // get string length
    const char *ss=++s_;
    while(*ss && *ss!=sc)
      ++ss;
    usize_t size=ss-s_;
    var_stack_.push_back(Config::from_str(s_, size));
    return uint8_t(size+(*ss==sc?2:1));
  }

  // check for scalar literal
  float64_t valf;
  int64_t vali;
  int size=str_to_scalar64(valf, vali, s_);
  if(size)
  {
    if(size>0)
    {
      var_stack_.push_back(Config::from_scalar(valf));
      return uint8_t(size);
    }
    var_stack_.push_back(Config::from_scalar(vali));
    return uint8_t(-size);
  }

  // get potential variable/function identifier
  const char *s=s_;
  while(is_latin_alphanumeric(*s) || *s=='_')
    ++s;
  unsigned id_size=unsigned(s-s_);
  if(!id_size)
    return 0;
  char id[256];
  PFC_ASSERT(id_size<sizeof(id));
  mem_copy(id, s_, id_size);
  id[id_size]=0;
  id_str_t id_str(id);

  // check if variable with given identifier exists
  typename hash_map<id_str_t, var_t>::const_iterator var_it=m_vars.find(id_str);
  if(is_valid(var_it))
  {
    var_stack_.push_back(*var_it);
    return uint8_t(id_size);
  }
  if(extra_vars_ && Config::push_var(var_stack_, *extra_vars_, id_str))
    return uint8_t(id_size);

  // check if function with given identifier exists
  typename hash_map<id_str_t, functor_t>::const_iterator func_it=m_funcs.find(id_str);
  if(is_valid(func_it))
  {
    func_stack_entry fe={0, 0, *func_it};
    func_stack_.push_back(fe);
    s=str_skip_whitespace(s);
    if(*s!='(')
    {
      PFC_LOG(("Opening parenthesis must follow function identifier\r\n"));
      /*todo: return error code and terminate parsing*/
    }
    return uint8_t(s+1-s_);
  }
  return 0;
}
//----

template<class Config>
uint8_t expression_parser<Config>::parse_operator(var_stack_t &var_stack_, func_stack_t &func_stack_, const char *s_) const
{
  // check for potential operator function
  e_expr_op eop=expr_op_parse(s_);
  if(eop==exprop_none)
    return 0;
  uint8_t op_size=expr_op_size(eop);
  hash_map<e_expr_op, functor_t>::const_iterator it=m_ops.find(eop);
  if(is_valid(it))
  {
    uint8_t op_prec=expr_op_precedence(eop);
    eval_func_stack(var_stack_, func_stack_, op_prec);
    func_stack_entry fe={uint8_t(eop), op_prec, *it};
    func_stack_.push_back(fe);
  }
  return op_size;
}
//----

template<class Config>
void expression_parser<Config>::eval_func_stack(var_stack_t &var_stack_, func_stack_t &func_stack_, int precedence_) const
{
  // evaluate function stack entries with higher than given precedence
  while(func_stack_.size() && func_stack_.back().eop_prec>precedence_)
  {
    const func_stack_entry &fe=func_stack_.back();
    e_expr_op eop=(e_expr_op)fe.eop;
    int num_args=eop?expr_op_num_args(eop):-1;
    fe.func(num_args, var_stack_);
    func_stack_.pop_back();
  }
}
//----------------------------------------------------------------------------


//============================================================================
// expression_parser_config
//============================================================================
template<typename T>
bool expression_parser_config<T>::push_var(var_stack_t &stack_, const extra_var_container_t &ext_var_cont_, const id_str_t &id_)
{
  // find name from container and push the value to stack if found
  extra_var_container_t::const_iterator it=ext_var_cont_.find(id_);
  if(is_valid(it))
    return false;
  stack_.push_back(*it);
  return true;
}
//----

template<typename T>
T expression_parser_config<T>::from_scalar(float64_t v_)
{
  return T(v_);
}
//----

template<typename T>
T expression_parser_config<T>::from_scalar(int64_t v_)
{
  return T(v_);
}
//----

template<typename T>
T expression_parser_config<T>::from_str(const char *str_, usize_t str_len_)
{
  return T(str_, str_len_);
}
//----------------------------------------------------------------------------
