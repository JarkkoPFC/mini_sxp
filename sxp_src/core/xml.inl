//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// xml_input_stream
//============================================================================
template<typename T>
xml_input_stream &xml_input_stream::operator>>(T &v_)
{
  PFC_ASSERT_PEDANTIC(m_state!=pstate_attrib_name);
  stream(v_, meta_case<is_type_fund<T>::res?0:is_type_enum<T>::res?1:is_type_str<T>::res?2:is_type_class<T>::res?3:-1>());
  return *this;
}
//----

template<typename T>
bool xml_input_stream::read(T &v_)
{
  PFC_ASSERT_PEDANTIC(m_state!=pstate_attrib_name);
  m_parsing_error=false;
  stream(v_, meta_case<is_type_fund<T>::res?0:is_type_enum<T>::res?1:is_type_str<T>::res?2:is_type_class<T>::res?3:-1>());
  return !m_parsing_error;
}
//----

template<typename T>
void xml_input_stream::read(T *p_, usize_t count_)
{
  PFC_ASSERT(p_!=0 || !count_);
  PFC_ASSERT_PEDANTIC(m_state!=pstate_attrib_name);
  T *end=p_+count_;
  while(p_!=end)
    stream(*p_++, meta_case<is_type_fund<T>::res?0:is_type_enum<T>::res?1:is_type_str<T>::res?2:is_type_class<T>::res?3:-1>());
}
//----

template<class S>
void xml_input_stream::read_word(str_base<S> &str_)
{
  // read word (whitespace separated string) from the stream
  PFC_ASSERT(m_state!=pstate_attrib_name);
  S &str=static_cast<S&>(str_);
  str.clear();
  char buf[1024];
  char next_char, term_char=m_state==pstate_content?'<':'\"';
  do
  {
    // read string until whitespace or special XML character
    unsigned size=!m_stream.is_eos()?(unsigned)m_stream.read_word(buf, sizeof(buf), m_state==pstate_content?"&<":"&<\"", true, false, false):0;
    str.push_back(buf, size);
    next_char=m_stream.next_char();
    switch(next_char)
    {
      case '&': str+=parse_escaped_character(); break;
      case '<':
      {
        // check for leading comment block
        if(!str.size())
        {
          m_stream.skip(1);
          if(skip_comment())
            next_char='a'; // just a random character to continue parsing
          else
            m_stream.rewind(1);
        }
      } break;
    }
  } while(!is_whitespace(next_char) && next_char!=term_char);
}
//----

template<typename T>
bool xml_input_stream::find_attrib(const char *attrib_name_, T &v_, bool skip_remaining_attribs_)
{
  // find and read an attribute from the element attributes
  string_t attrib_name;
  while(start_attrib_parsing(attrib_name))
  {
    if(attrib_name==attrib_name_)
    {
      (*this)>>v_;
      if(skip_remaining_attribs_)
        skip_attribs();
      return true;
    }
    end_attrib_parsing();
  }
  return false;
}
//----

template<class S>
bool xml_input_stream::find_attrib_str(const char *attrib_name_, str_base<S> &str_, bool skip_remaining_attribs_)
{
  // find and read a string attribute from the element attributes
  string_t attrib_name;
  while(start_attrib_parsing(attrib_name))
  {
    if(attrib_name==attrib_name_)
    {
      read_word(str_);
      if(skip_remaining_attribs_)
        skip_attribs();
      return true;
    }
    end_attrib_parsing();
  }
  return false;
}
//----------------------------------------------------------------------------

bool xml_input_stream::is_eos() const
{
  return m_stream.is_eos();
}
//----------------------------------------------------------------------------

void xml_input_stream::stream(char &v_, meta_case<0> is_type_fund_)
{
  string_t str;
  read_word(str);
  if(str.size())
    v_=str[0];
  else
    m_parsing_error=true;
}
//----

template<typename T>
void xml_input_stream::stream(T &v_, meta_case<0> is_type_fund_)
{
  string_t str;
  read_word(str);
  float64_t v;
  bool conv_succeeded=str_to_float64(v, str.c_str());
  if(conv_succeeded)
    v_=T(v);
  m_parsing_error|=!conv_succeeded;
}
//----

template<typename T>
void xml_input_stream::stream(T &v_, meta_case<1> is_type_enum_)
{
  string_t str;
  read_word(str);
  m_parsing_error|=!enum_value(v_, str.c_str());
}
//----

template<class S>
void xml_input_stream::stream(str_base<S> &str_, meta_case<2> is_type_str_)
{
  // read string from the stream
  PFC_ASSERT(m_state!=pstate_attrib_name);
  S &str=static_cast<S&>(str_);
  str.clear();
  char buf[1024];
  char next_char, term_char=m_state==pstate_content?'<':'\"';
  do
  {
    // read string until whitespace or special XML character
    unsigned size=!m_stream.is_eos()?(unsigned)m_stream.read_word(buf, sizeof(buf), m_state==pstate_content?"&<":"&<\"", true, false, m_state!=pstate_attrib_value):0;
    str.push_back(buf, size);
    next_char=m_stream.next_char();
    switch(next_char)
    {
      case '&': str+=parse_escaped_character(); break;
      case '<':
      {
        m_stream.skip(1);
        if(skip_comment())
          next_char=0;
        else
          m_stream.rewind(1);
      } break;
      default:
      {
        if(is_whitespace(next_char))
        {
          do
          {
            str+=next_char;
            m_stream.skip(1);
            next_char=m_stream.next_char();
          } while(is_whitespace(next_char));
        }
      }
    }
  } while(next_char!=term_char);
}
//----

template<typename T>
void xml_input_stream::stream(T &v_, meta_case<3> is_type_class_)
{
  // read object properties from the stream
  prop_enum_input_stream<xml_input_stream> pe(*this);
  enum_props(pe, v_);
  post_load_function(&v_);
}
//----

template<typename T>
void xml_input_stream::stream(T&, meta_case<-1> default_)
{
  PFC_STATIC_ERROR(T, unable_to_deserialize_the_type);
}
//----------------------------------------------------------------------------


//============================================================================
// xml_stream_parser::prop_enum_attrib
//============================================================================
class xml_stream_parser::prop_enum_attrib: public prop_enum_interface_base<prop_enum_attrib>
{
public:
  // construction
  PFC_INLINE prop_enum_attrib(xml_stream_parser&, name_processor_func_t);
  //--------------------------------------------------------------------------

  // streaming interface
  template<typename T> PFC_INLINE bool var(T&, unsigned flags_=0, const char *mvar_name_=0);
  template<typename T, class C> PFC_INLINE bool var(T&, unsigned flags_, const char *mvar_name_, C&);
  template<typename T, class C> PFC_INLINE bool var(T&, unsigned flags_, const char *mvar_name_, C&, void(*post_mutate_func_)(C*));
  template<typename T, class C> PFC_INLINE bool var(T&, unsigned flags_, const char *mvar_name_, C&, void(C::*mutate_func_)(const T&, unsigned var_index_), unsigned var_index_);
  template<typename T> PFC_INLINE bool avar(T*, usize_t size_, unsigned flags_=0, const char *mvar_name_=0);
  template<typename T, class C> PFC_INLINE bool avar(T*, usize_t size_, unsigned flags_, const char *mvar_name_, C&);
  template<typename T, class C> PFC_INLINE bool avar(T*, usize_t size_, unsigned flags_, const char *mvar_name_, C&, void(*post_mutate_func_)(C*));
  template<typename T, class C> PFC_INLINE bool avar(T*, usize_t size_, unsigned flags_, const char *mvar_name_, C&, void(C::*mutate_func_)(const T&, unsigned index_, unsigned var_index_), unsigned var_index_);
  template<typename T> PFC_INLINE bool alias_var(T&, unsigned flags_, const char *alias_);
  template<typename T> PFC_INLINE bool alias_avar(T*, usize_t size_, unsigned flags_, const char *alias_);
  //--------------------------------------------------------------------------

private:
  inline owner_cstr process_name(const char*);
  //--------------------------------------------------------------------------

  xml_stream_parser &m_parser;
  name_processor_func_t m_name_processor_func;
};
//----------------------------------------------------------------------------

xml_stream_parser::prop_enum_attrib::prop_enum_attrib(xml_stream_parser &parser_, name_processor_func_t npf_)
  :m_parser(parser_)
  ,m_name_processor_func(npf_)
{
}
//----------------------------------------------------------------------------

template<typename T>
bool xml_stream_parser::prop_enum_attrib::var(T &v_, unsigned flags_, const char *mvar_name_)
{
  m_parser.attrib(process_name(mvar_name_).c_str(), attrib_func_t(m_parser, attrib_func_t::call_mem_func<xml_stream_parser, &xml_stream_parser::serialize_element_mvar<T> >), &v_);
  return true;
}
//----

template<typename T, class C>
bool xml_stream_parser::prop_enum_attrib::var(T &v_, unsigned flags_, const char *mvar_name_, C&)
{
  m_parser.attrib(process_name(mvar_name_).c_str(), attrib_func_t(m_parser, attrib_func_t::call_mem_func<xml_stream_parser, &xml_stream_parser::serialize_element_mvar<T> >), &v_);
  return true;
}
//----

template<typename T, class C>
bool xml_stream_parser::prop_enum_attrib::var(T &v_, unsigned flags_, const char *mvar_name_, C&, void(*)(C*))
{
  m_parser.attrib(process_name(mvar_name_).c_str(), attrib_func_t(m_parser, attrib_func_t::call_mem_func<xml_stream_parser, &xml_stream_parser::serialize_element_mvar<T> >), &v_);
  return true;
}
//----

template<typename T, class C>
bool xml_stream_parser::prop_enum_attrib::var(T &v_, unsigned flags_, const char *mvar_name_, C&, void(C::*)(const T&, unsigned), unsigned)
{
  m_parser.attrib(process_name(mvar_name_).c_str(), attrib_func_t(m_parser, attrib_func_t::call_mem_func<xml_stream_parser, &xml_stream_parser::serialize_element_mvar<T> >), &v_);
  return true;
}
//----

template<typename T>
bool xml_stream_parser::prop_enum_attrib::avar(T*, usize_t size_, unsigned flags_, const char *mvar_name_)
{
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T, class C>
bool xml_stream_parser::prop_enum_attrib::avar(T*, usize_t size_, unsigned flags_, const char *mvar_name_, C&)
{
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T, class C>
bool xml_stream_parser::prop_enum_attrib::avar(T*, usize_t size_, unsigned flags_, const char *mvar_name_, C&, void(*)(C*))
{
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T, class C>
bool xml_stream_parser::prop_enum_attrib::avar(T*, usize_t size_, unsigned flags_, const char *mvar_name_, C&, void(C::*)(const T&, unsigned index_, unsigned var_index_), unsigned)
{
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool xml_stream_parser::prop_enum_attrib::alias_var(T &v_, unsigned flags_, const char *alias_)
{
  m_parser.attrib(process_name(alias_).c_str(), attrib_func_t(m_parser, attrib_func_t::call_mem_func<xml_stream_parser, &xml_stream_parser::serialize_element_mvar<T> >), &v_);
  return true;
}
//----

template<typename T>
bool xml_stream_parser::prop_enum_attrib::alias_avar(T*, usize_t size_, unsigned flags_, const char *alias_)
{
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----------------------------------------------------------------------------

owner_cstr xml_stream_parser::prop_enum_attrib::process_name(const char *cstr_)
{
  return m_name_processor_func?m_name_processor_func(cstr_):owner_cstr(cstr_, false);
}
//----------------------------------------------------------------------------


//============================================================================
// xml_attribute
//============================================================================
xml_attribute::xml_attribute()
{
}
//----

xml_attribute::xml_attribute(const char *name_)
  :name(name_)
{
}
//----

xml_attribute::xml_attribute(const char *name_, const char *value_)
  :name(name_)
  ,value(value_)
{
}
//----------------------------------------------------------------------------


//============================================================================
// xml_stream_parser
//============================================================================
template<typename T>
xml_stream_parser &xml_stream_parser::begin_element(const char *name_, T &v_, bool add_class_attribs_, name_processor_func_t npf_)
{
  begin_element(name_, begin_func_t(*this, begin_func_t::call_mem_func<xml_stream_parser, &xml_stream_parser::begin_element_single>), &v_);
  m_current_element->type_id=type_id<T>::id;
  if(add_class_attribs_)
    add_class_attribs((T*)0, npf_, meta_bool<is_type_introspec<T>::res>());
  return *this;
}
//----

template<typename T>
xml_stream_parser &xml_stream_parser::begin_element(const char *name_, array<T> &arr_, bool add_class_attribs_, name_processor_func_t npf_)
{
  begin_element(name_, begin_func_t(*this, begin_func_t::call_mem_func<xml_stream_parser, &xml_stream_parser::begin_element_container<array<T> > >), &arr_);
  m_current_element->type_id=type_id<T>::id;
  if(add_class_attribs_)
    add_class_attribs((T*)0, npf_, meta_bool<is_type_introspec<T>::res>());
  return *this;
}
//----

template<typename T>
xml_stream_parser &xml_stream_parser::begin_element(const char *name_, deque<T> &deq_, bool add_class_attribs_, name_processor_func_t npf_)
{
  begin_element(name_, begin_func_t(*this, begin_func_t::call_mem_func<xml_stream_parser, &xml_stream_parser::begin_element_container<deque<T> > >), &deq_);
  m_current_element->type_id=type_id<T>::id;
  if(add_class_attribs_)
    add_class_attribs((T*)0, npf_, meta_bool<is_type_introspec<T>::res>());
  return *this;
}
//----

template<typename T>
xml_stream_parser &xml_stream_parser::begin_element(const char *name_, list<T> &list_, bool add_class_attribs_, name_processor_func_t npf_)
{
  begin_element(name_, begin_func_t(*this, begin_func_t::call_mem_func<xml_stream_parser, &xml_stream_parser::begin_element_container<list<T> > >), &list_);
  m_current_element->type_id=type_id<T>::id;
  if(add_class_attribs_)
    add_class_attribs((T*)0, npf_, meta_bool<is_type_introspec<T>::res>());
  return *this;
}
//----

template<typename T, class U>
xml_stream_parser &xml_stream_parser::begin_element(const char *name_, array<T>(U::*arr_mvar_), bool add_class_attribs_, name_processor_func_t npf_)
{
  PFC_ASSERT_MSG(m_current_element->type_id==type_id<U>::id, ("Invalid enclosing class type \"%s\" for current XML element\r\n", typeid(U).name()));
  begin_element(name_, begin_func_t(*this, begin_func_t::call_mem_func<xml_stream_parser, &xml_stream_parser::begin_element_member_container<array<T> > >), (void*)PFC_OFFSETOF_MVARPTR(U, arr_mvar_));
  m_current_element->type_id=type_id<T>::id;
  if(add_class_attribs_)
    add_class_attribs((T*)0, npf_, meta_bool<is_type_introspec<T>::res>());
  return *this;
}
//----

template<typename T, class U>
xml_stream_parser &xml_stream_parser::begin_element(const char *name_, deque<T>(U::*deq_mvar_), bool add_class_attribs_, name_processor_func_t npf_)
{
  PFC_ASSERT_MSG(m_current_element->type_id==type_id<U>::id, ("Invalid enclosing class type \"%s\" for current XML element\r\n", typeid(U).name()));
  begin_element(name_, begin_func_t(*this, begin_func_t::call_mem_func<xml_stream_parser, &xml_stream_parser::begin_element_member_container<deque<T> > >), (void*)PFC_OFFSETOF_MVARPTR(U, deq_mvar_));
  m_current_element->type_id=type_id<T>::id;
  if(add_class_attribs_)
    add_class_attribs((T*)0, npf_, meta_bool<is_type_introspec<T>::res>());
  return *this;
}
//----

template<typename T, class U>
xml_stream_parser &xml_stream_parser::begin_element(const char *name_, list<T>(U::*list_mvar_), bool add_class_attribs_, name_processor_func_t npf_)
{
  PFC_ASSERT_MSG(m_current_element->type_id==type_id<U>::id, ("Invalid enclosing class type \"%s\" for current XML element\r\n", typeid(U).name()));
  begin_element(name_, begin_func_t(*this, begin_func_t::call_mem_func<xml_stream_parser, &xml_stream_parser::begin_element_member_container<list<T> > >), (void*)PFC_OFFSETOF_MVARPTR(U, list_mvar_));
  m_current_element->type_id=type_id<T>::id;
  if(add_class_attribs_)
    add_class_attribs((T*)0, npf_, meta_bool<is_type_introspec<T>::res>());
  return *this;
}
//----

template<typename T>
xml_stream_parser &xml_stream_parser::attrib(const char *name_, T &v_)
{
  return attrib(name_, &deserialize<T>, &v_);
}
//----

template<typename T>
xml_stream_parser &xml_stream_parser::attrib(const char *name_, array<T> &arr_)
{
  return attrib(name_, &serialize_data_to_container<array<T>, T>, &arr_);
}
//----

template<typename T>
xml_stream_parser &xml_stream_parser::attrib(const char *name_, deque<T> &deq_)
{
  return attrib(name_, &serialize_data_to_container<deque<T>, T>, &deq_);
}
//----

template<typename T>
xml_stream_parser &xml_stream_parser::attrib(const char *name_, list<T> &list_)
{
  return attrib(name_, &serialize_data_to_container<list<T>, T>, &list_);
}
//----

template<typename T, class U>
xml_stream_parser &xml_stream_parser::attrib(const char *name_, T(U::*mem_var_))
{
  PFC_ASSERT_MSG(!m_current_element || m_current_element->type_id==type_id<U>::id, ("Invalid enclosing class type \"%s\" for current XML element\r\n", typeid(U).name()));
  return attrib(name_, attrib_func_t(*this, attrib_func_t::call_mem_func<xml_stream_parser, &xml_stream_parser::serialize_element_mvar<T> >), (void*)PFC_OFFSETOF_MVARPTR(U, mem_var_));
}
//----

template<class T>
xml_stream_parser &xml_stream_parser::attribs_ftl(list<xml_attribute>(T::*mem_var_))
{
  // set attribute fall-through list
  PFC_ASSERT_MSG(m_current_element, ("attribs_ftl() must be called inside XML element\r\n"));
  PFC_ASSERT_MSG(m_current_element->type_id==type_id<T>::id, ("Invalid enclosing class type \"%s\" for current XML element\r\n", typeid(T).name()));
  m_current_element->attribs_ftl_func=&get_attribs_ftl_mvar;
  m_current_element->attribs_ftl_data=(void*)PFC_OFFSETOF_MVARPTR(T, mem_var_);
  return *this;
}
//----------------------------------------------------------------------------

template<typename T>
void xml_stream_parser::deserialize(xml_input_stream &stream_, void *data_)
{
  stream_>>*(T*)data_;
}
//----

template<class T>
void xml_stream_parser::add_class_attribs(T*, name_processor_func_t, meta_bool<false> is_introspec_)
{
  PFC_ERRORF("Class \"%s\" doesn't have introspection\r\n", typeid(T).name());
}
//----

template<class T>
void xml_stream_parser::add_class_attribs(T*, name_processor_func_t npf_, meta_bool<true> is_introspec_)
{
  // add all reflected class properties as attributes
  prop_enum_attrib penum(*this, npf_);
  enum_props(penum, *(T*)0);
}
//----

template<class Container>
bool xml_stream_parser::begin_element_container(xml_input_stream&, void *data_)
{
  Container &cont=*(Container*)data_;
  m_current_data_element=&cont.push_back();
  return false;
}
//----

template<class Container>
bool xml_stream_parser::begin_element_member_container(xml_input_stream&, void *data_)
{
  Container &cont=*(Container*)((char*)m_current_data_element+usize_t(data_));
  m_current_data_element=&cont.push_back();
  return false;
}
//----

template<class Container, typename T>
void xml_stream_parser::serialize_data_to_container(xml_input_stream &stream_, void *data_)
{
  Container &cont=*(Container*)data_;
  stream_>>cont.push_back();
}
//----

template<typename T>
void xml_stream_parser::serialize_element_mvar(xml_input_stream &stream_, void *data_)
{
  PFC_ASSERT(m_current_data_element);
  void *data=((char*)m_current_data_element)+usize_t(data_);
  stream_>>*(T*)data;
}
//----------------------------------------------------------------------------
