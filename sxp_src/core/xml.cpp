//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "xml.h"
#include "sort.h"
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// xml_input_stream
//============================================================================
xml_input_stream::xml_input_stream(bin_input_stream_base &stream_)
  :m_stream(stream_)
{
  m_state=pstate_content;
  m_bool_true_strings=0;
  m_case_sensitive_bool_strings=false;
}
//----

void xml_input_stream::set_bool_true_strings(const char **strings_, bool case_sensitive_)
{
  // setup strings for bool value parsing
  m_bool_true_strings=strings_;
  m_case_sensitive_bool_strings=case_sensitive_;
}
//----------------------------------------------------------------------------

e_xml_item xml_input_stream::parse_item(string_t &item_name_, bool skip_attribs_)
{
  // try to start element parsing
  PFC_ASSERT(m_state==pstate_content);
  redo_read:
  m_stream.skip_whitespace();
  char next_char=m_stream.next_char();
  switch(next_char)
  {
    case 0: return xmlitem_end;
    case '>': m_stream.skip(1); return xmlitem_end;
    case '<':
    {
      // read tag and check for end tag
      m_stream.skip(1);
      unsigned size=(unsigned)m_stream.read_word(item_name_.c_str(), item_name_.capacity(), "/>");
      item_name_.resize(size);
      if(skip_comment(item_name_))
        goto redo_read;

      if(!size && m_stream.next_char()=='/')
      {
        m_stream.skip_to('>', true);
        return xmlitem_end;
      }

      // set stream to element attribute reading state
      m_state=pstate_attrib_name;
      if(skip_attribs_)
        skip_attribs();
    } return xmlitem_element;
  }

  // parse regular string
  read_word(item_name_);
  return item_name_.size()?xmlitem_text:xmlitem_end;
}
//----

bool xml_input_stream::parse_element(string_t &tag_name_, bool skip_attribs_)
{
  // skip text items and return true for element items
  e_xml_item item_type;
  while((item_type=parse_item(tag_name_, skip_attribs_))==xmlitem_text);
  return item_type==xmlitem_element;
}
//----

bool xml_input_stream::start_attrib_parsing(string_t &attrib_name_)
{
  // try to start attribute parsing
  if(m_state!=pstate_attrib_name)
    return false;
  unsigned size;
  do
  {
    size=(unsigned)m_stream.read_word(attrib_name_.c_str(), attrib_name_.capacity(), "=/>");
    attrib_name_.resize(size);
  } while(skip_comment(attrib_name_, 1));
  char next_char=m_stream.next_char();
  if(next_char=='/' || next_char=='>')
  {
    m_stream.skip(1);
    m_state=pstate_content;
    return false;
  }

  // skip to the attribute value
  m_stream.skip_to('"', true);
  m_state=pstate_attrib_value;
  return true;
}
//----

void xml_input_stream::end_attrib_parsing()
{
  PFC_ASSERT_MSG(m_state==pstate_attrib_value, ("XML element attribute parsing not started\r\n"));
  m_stream.skip_to('"', true);
  m_state=pstate_attrib_name;
}
//----------------------------------------------------------------------------

void xml_input_stream::skip_attribs()
{
  // skip element attributes
  PFC_ASSERT(m_state!=pstate_content);
  do
  {
    m_stream.skip_to("<>");
    if(m_stream.next_char()=='>')
      break;
    m_stream.skip(1);
    PFC_VERIFY(skip_comment());
  } while(true);
  m_stream.rewind(1);
  m_stream.skip(m_stream.next_char()=='/'?1:2);
  m_state=pstate_content;
}
//----

void xml_input_stream::skip_element()
{
  // skip attribute block if parsing attributes
  if(m_state!=pstate_content)
    skip_attribs();

  // check for start-end tag
  if(m_stream.next_char()=='>')
  {
    m_stream.skip(1);
    return;
  }

  // skip until tag recursion reaches zero
  unsigned tag_recursion=1;
  do
  {
    // skip to the next tag
    do
      m_stream.skip_to('<', true);
    while(skip_comment());
    char c;
    m_stream>>c;
    m_stream.skip_to('>');
    m_stream.rewind(1);
    if(m_stream.next_char()=='/')
      --tag_recursion;
    m_stream.skip(2);
    tag_recursion+=c=='/'?-1:+1;
  } while(tag_recursion);
}
//----------------------------------------------------------------------------

char xml_input_stream::parse_escaped_character()
{
  // read escaped character code
  PFC_ASSERT(m_stream.next_char()=='&');
  m_stream.skip(1);
  char buf[16];
  unsigned size=(unsigned)m_stream.read_word(buf, sizeof(buf), ";");
  PFC_CHECK_MSG(size<sizeof(buf), ("Invalid XML character code\r\n"));
  m_stream.skip(1);

  // check for numeric character reference
  if(buf[0]=='#')
  {
    unsigned code=0;
    if(buf[1]=='x')
    {
      // decode hex character code
      for(unsigned i=2; i<size; ++i)
      {
        char c=buf[i];
        PFC_CHECK_MSG(is_hex(c), ("Invalid XML hex character code\r\n"));
        c=(char)hex_char_to_uint(c);
        code=code*16+c;
      }
    }
    else
    {
      // decode decimal character code
      for(unsigned i=1; i<size; ++i)
      {
        char c=buf[i];
        PFC_CHECK_MSG(is_decimal(c), ("Invalid XML decimal character code\r\n"));
        code=code*10+dec_char_to_uint(c);
      }
    }

    PFC_ASSERT(code!=0);
    return char(code);
  }

  // check for character code string
  switch(size)
  {
    case 2:
    {
      if(str_eq(buf, "lt", 2))
        return '<';
      if(str_eq(buf, "gt", 2))
        return '>';
    } break;

    case 3:
    {
      if(str_eq(buf, "amp", 3))
        return '&';
    } break;

    case 4:
    {
      if(str_eq(buf, "apos", 4))
        return '\'';
      if(str_eq(buf, "quot", 4))
        return '"';
    } break;
  }

  // unknown character code
  PFC_ERRORF("Unknown character code: &%s;\r\n", buf);
  return 0;
}
//----

bool xml_input_stream::skip_comment()
{
  // check for a comment
  if(m_stream.next_char()!='!')
    return false;
  m_stream.skip(1);
  if(m_stream.next_char()!='-')
  {
    m_stream.rewind(1);
    return false;
  }
  m_stream.skip(1);
  if(m_stream.next_char()!='-')
  {
    m_stream.rewind(2);
    return false;
  }
  m_stream.skip(1);

  // skip stream until the end of the comment: "-->"
  char buf[2]={'-', '-'}, c='-';
  do
  {
    do
    {
      if(m_stream.is_eos())
        return true;
      buf[0]=buf[1];
      buf[1]=c;
      m_stream>>c;
    } while(c!='>');
  } while(buf[0]!='-' || buf[1]!='-');
  return true;
}
//----

bool xml_input_stream::skip_comment(const string_t &item_, unsigned str_offset_)
{
  // check for a comment
  const char *s=item_.c_str()+str_offset_;
  if(item_.size()<3 || !str_eq(s, "!--", 3))
    return false;

  // check for closing comment in the string
  if(m_stream.next_char()=='>' && str_eq(s-str_offset_+item_.size()-2, "--"))
  {
    m_stream.skip(1);
    return true;
  }

  // skip stream until the end of the comment: "-->"
  char buf[2]={0}, c=0;
  do
  {
    do
    {
      if(m_stream.is_eos())
        return true;
      buf[0]=buf[1];
      buf[1]=c;
      m_stream>>c;
    } while(c!='>');
  } while(buf[0]!='-' || buf[1]!='-');
  return true;
}
//----

void xml_input_stream::stream(bool &v_, meta_case<0> is_type_fund_)
{
  // read bool word
  string_t str;
  read_word(str);

  // check for bool string comparison
  if(m_bool_true_strings)
  {
    // search for bool true string
    const char **bs=m_bool_true_strings;
    const char *s=str.c_str();
    while(*bs)
    {
      if(m_case_sensitive_bool_strings?str_eq(*bs, s):str_ieq(*bs, s))
      {
        v_=true;
        return;
      }
      ++bs;
    }
    v_=false;
    return;
  }

  // test for non-zero value for true-value
  float64_t v;
  bool conv_succeeded=str_to_float64(v, str.c_str());
  if(conv_succeeded)
    v_=!!v;
  m_parsing_error|=!conv_succeeded;
}
//----------------------------------------------------------------------------


//============================================================================
// xml_stream_parser
//============================================================================
xml_stream_parser::xml_stream_parser()
{
  // init parser
  xml_element &root_element=m_elements.push_back();
  root_element.data=0;
  root_element.type_id=0;
  root_element.begin_func=0;
  root_element.end_func=0;
  root_element.parent=0;
  root_element.attribs=0;
  root_element.attribs_ftl_func=0;
  root_element.attribs_ftl_data=0;
  root_element.children=0;
  root_element.next=0;
  m_current_element=&m_elements[0];
  m_current_data_element=0;
}
//----

void xml_stream_parser::process_stream(xml_input_stream &stream_)
{
  // parse elements
  PFC_CHECK(m_current_element==&m_elements[0]);
  xml_input_stream::string_t xml_tag;
  process_element(stream_, xml_tag);
}
//----------------------------------------------------------------------------

xml_stream_parser &xml_stream_parser::begin_element(const char *name_, const begin_func_t &func_, void *data_)
{
  // setup element
  xml_element &element=m_elements.push_back();
  element.name_id=name_;
  element.data=data_;
  element.type_id=0;
  element.begin_func=func_;
  element.end_func=0;
  element.parent=m_current_element;
  element.attribs=0;
  element.attribs_ftl_func=0;
  element.attribs_ftl_data=0;
  element.children=0;
  element.next=m_current_element->children;
  m_current_element->children=&element;
  m_current_element=&element;
  return *this;
}
//----

xml_stream_parser &xml_stream_parser::attrib(const char *name_, const attrib_func_t &func_, void *data_)
{
  // setup attrib
  PFC_ASSERT_MSG(m_current_element, ("attrib() must be called inside XML element\r\n"));
  xml_attrib &attrib=m_attribs.push_back();
  attrib.name_id=name_;
  attrib.data=data_;
  attrib.func=func_;
  attrib.next=m_current_element->attribs;
  m_current_element->attribs=&attrib;
  return *this;
}
//----

xml_stream_parser &xml_stream_parser::attribs_ftl(list<xml_attribute> &attribs_)
{
  // set attribute fall-through list
  PFC_ASSERT_MSG(m_current_element, ("attribs_ftl() must be called inside XML element\r\n"));
  m_current_element->attribs_ftl_func=&get_attribs_ftl;
  m_current_element->attribs_ftl_data=&attribs_;
  return *this;
}
//----

xml_stream_parser &xml_stream_parser::end_element(const end_func_t &func_)
{
  // end element
  PFC_ASSERT_MSG(m_current_element, ("end_element() must match begin_element() calls\r\n"));
  m_current_element->end_func=func_;
  m_current_element=m_current_element->parent;
  return *this;
}
//----------------------------------------------------------------------------

void xml_stream_parser::process_element(xml_input_stream &stream_, xml_input_stream::string_t &xml_tag_)
{
  // process elements
  while(stream_.parse_element(xml_tag_))
  {
    // search for element tag
    typedef slist_iterator<xml_element, &xml_element::next> element_iterator_t;
    element_iterator_t it=linear_search(element_iterator_t(m_current_element->children), element_iterator_t(0), xml_tag_.c_str());
    if(is_valid(it))
    {
      // set current element and parse element attributes
      xml_element *old_current_element=m_current_element;
      m_current_element=ptr(it);
      void *old_current_data_element=m_current_data_element;
      bool skip_element_processing=false;
      if(m_current_element->begin_func)
        skip_element_processing=m_current_element->begin_func(stream_, m_current_element->data);
      if(!skip_element_processing)
      {
        while(stream_.start_attrib_parsing(xml_tag_))
        {
          // search for attrib tag
          typedef slist_const_iterator<xml_attrib, &xml_attrib::next> attrib_iterator_t;
          attrib_iterator_t it=linear_search(attrib_iterator_t(m_current_element->attribs), attrib_iterator_t(0), xml_tag_.c_str());
          if(is_valid(it))
          {
            // deserialize attribute from the stream
            const xml_attrib *attrib=ptr(it);
            attrib->func(stream_, attrib->data);
          }
          else if(m_current_element->attribs_ftl_func)
          {
            list<xml_attribute> *l=(*m_current_element->attribs_ftl_func)(m_current_element->attribs_ftl_data, m_current_data_element);
            xml_attribute &attr=l->push_back();
            attr.name=xml_tag_;
            stream_>>attr.value;
          }

          stream_.end_attrib_parsing();
        }
        process_element(stream_, xml_tag_);
      }
      if(m_current_element->end_func)
        m_current_element->end_func(stream_, m_current_element->data);
      m_current_element=old_current_element;
      m_current_data_element=old_current_data_element;
    }
    else
      stream_.skip_element();
  }
}
//----

bool xml_stream_parser::begin_element_single(xml_input_stream&, void *data_)
{
  m_current_data_element=data_;
  return false;
}
//----------------------------------------------------------------------------

list<xml_attribute> *xml_stream_parser::get_attribs_ftl(void *ftl_data_, void *curr_data_elem_)
{
  return (list<xml_attribute>*)ftl_data_;
}
//----

list<xml_attribute> *xml_stream_parser::get_attribs_ftl_mvar(void *ftl_data_, void *curr_data_elem_)
{
  return (list<xml_attribute>*)(((char*)curr_data_elem_)+usize_t(ftl_data_));
}
//----------------------------------------------------------------------------

//============================================================================
// xml_stream_parser::xml_attrib
//============================================================================
bool xml_stream_parser::xml_attrib::operator==(const str_id &id_) const
{
  return name_id==id_;
}
//----------------------------------------------------------------------------

//============================================================================
// xml_stream_parser::xml_element
//============================================================================
bool xml_stream_parser::xml_element::operator==(const str_id &id_) const
{
  return name_id==id_;
}
//----------------------------------------------------------------------------


//============================================================================
// default_mvar_name_cleanup
//============================================================================
owner_cstr pfc::default_mvar_name_cleanup(const char *mvar_)
{
  // clean-up member variable name
  if(mvar_[0]=='m' && mvar_[1]=='_')
    mvar_+=2;
  return owner_cstr(mvar_, false);
}
//----------------------------------------------------------------------------
