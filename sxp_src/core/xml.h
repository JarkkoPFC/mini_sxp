//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_XML_H
#define PFC_CORE_XML_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "streams.h"
#include "containers.h"
#include "functor.h"
namespace pfc
{

// new
class xml_input_stream;
class xml_stream_parser;
owner_cstr default_mvar_name_cleanup(const char*);
//----------------------------------------------------------------------------


//============================================================================
// xml_input_stream
//============================================================================
enum e_xml_item
{
  xmlitem_end,     // end of an element: </hello>
  xmlitem_text,    // regular text in element contents: hello
  xmlitem_element, // start of an element: <hello[...]> or <hello[...]/>
};
//----

class xml_input_stream
{
public:
  // nested types
  typedef stack_str1024 string_t;
  //--------------------------------------------------------------------------

  // construction
  xml_input_stream(bin_input_stream_base&);
  void set_bool_true_strings(const char**, bool case_sensitive_=false);
  //--------------------------------------------------------------------------

  // item and element attribute parsing
  e_xml_item parse_item(string_t &item_name_, bool skip_attribs_=false);
  bool parse_element(string_t &tag_name_, bool skip_attribs_=false);
  bool start_attrib_parsing(string_t &attrib_name_);
  void end_attrib_parsing();
  //--------------------------------------------------------------------------

  // attribute value and content streaming
  template<typename T> PFC_INLINE xml_input_stream &operator>>(T&);
  template<typename T> PFC_INLINE bool read(T&);
  template<typename T> PFC_INLINE void read(T*, usize_t count_);
  template<class S> void read_word(str_base<S>&);
  template<typename T> bool find_attrib(const char *attrib_name_, T&, bool skip_remaining_attribs_=true);
  template<class S> bool find_attrib_str(const char *attrib_name_, str_base<S>&, bool skip_remaining_attribs_=true);
  //--------------------------------------------------------------------------

  // accessors and seeking
  PFC_INLINE bool is_eos() const;
  void skip_attribs();
  void skip_element();
  //--------------------------------------------------------------------------

private:
  xml_input_stream(const xml_input_stream&); // not implemented
  void operator=(const xml_input_stream&); // not implemented
  char parse_escaped_character();
  bool skip_comment();
  bool skip_comment(const string_t&, unsigned str_offset_=0);
  void stream(bool&, meta_case<0> is_type_fund_);
  PFC_INLINE void stream(char&, meta_case<0> is_type_fund_);
  template<typename T> PFC_INLINE void stream(T&, meta_case<0> is_type_int_);
  template<typename T> PFC_INLINE void stream(T&, meta_case<1> is_type_float_);
  template<typename T> PFC_INLINE void stream(T&, meta_case<2> is_type_enum_);
  template<class S> PFC_INLINE void stream(str_base<S>&, meta_case<3> is_type_str_);
  template<typename T> PFC_INLINE void stream(T&, meta_case<4> is_type_class_);
  template<typename T> PFC_INLINE void stream(T&, meta_case<-1> default_);
  //--------------------------------------------------------------------------

  //==========================================================================
  // e_parsing_state
  //==========================================================================
  enum e_parsing_state
  {
    pstate_content,
    pstate_attrib_name,
    pstate_attrib_value,
  };
  //--------------------------------------------------------------------------

  text_input_stream m_stream;
  e_parsing_state m_state;
  bool m_parsing_error;
  const char **m_bool_true_strings;
  bool m_case_sensitive_bool_strings;
};
//----------------------------------------------------------------------------


//============================================================================
// xml_attribute
//============================================================================
struct xml_attribute
{
  // construction
  PFC_INLINE xml_attribute();
  PFC_INLINE xml_attribute(const char *name_);
  PFC_INLINE xml_attribute(const char *name_, const char *value_);
  //--------------------------------------------------------------------------

  heap_str name;
  heap_str value;
};
//----------------------------------------------------------------------------


//============================================================================
// xml_stream_parser
//============================================================================
class xml_stream_parser
{
  class prop_enum_attrib;
public:
  // nested
  typedef functor<bool(xml_input_stream&, void*)> begin_func_t;
  typedef functor<void(xml_input_stream&, void*)> end_func_t;
  typedef functor<void(xml_input_stream&, void*)> attrib_func_t;
  typedef functor<owner_cstr(const char*)> name_processor_func_t;
  template<class PE> struct is_attrib_penum {enum {res=is_type_equal<PE, prop_enum_attrib>::res};};
  //--------------------------------------------------------------------------

  // construction
  xml_stream_parser();
  void process_stream(xml_input_stream&);
  //--------------------------------------------------------------------------

  // XML structure setup
  xml_stream_parser &begin_element(const char *name_, const begin_func_t &func_=0, void *data_=0);
  template<typename T> xml_stream_parser &begin_element(const char *name_, T&, bool add_class_attribs_=false, name_processor_func_t npf_=name_processor_func_t());
  template<typename T> xml_stream_parser &begin_element(const char *name_, array<T>&, bool add_class_attribs_=false, name_processor_func_t npf_=name_processor_func_t());
  template<typename T> xml_stream_parser &begin_element(const char *name_, deque<T>&, bool add_class_attribs_=false, name_processor_func_t npf_=name_processor_func_t());
  template<typename T> xml_stream_parser &begin_element(const char *name_, list<T>&, bool add_class_attribs_=false, name_processor_func_t npf_=name_processor_func_t());
  template<class U, typename T> xml_stream_parser &begin_element(const char *name_, T(U::*), bool add_class_attribs_=false, name_processor_func_t npf_=name_processor_func_t());
  template<class U, typename T> xml_stream_parser &begin_element(const char *name_, array<T>(U::*), bool add_class_attribs_=false, name_processor_func_t npf_=name_processor_func_t());
  template<class U, typename T> xml_stream_parser &begin_element(const char *name_, deque<T>(U::*), bool add_class_attribs_=false, name_processor_func_t npf_=name_processor_func_t());
  template<class U, typename T> xml_stream_parser &begin_element(const char *name_, list<T>(U::*), bool add_class_attribs_=false, name_processor_func_t npf_=name_processor_func_t());
  template<class U, typename T> xml_stream_parser &begin_element_mvar(const char *name_, T *mvar_offset_ptr_, bool add_class_attribs_=false, name_processor_func_t npf_=name_processor_func_t());
  template<class U, typename T> xml_stream_parser &flatten_element(T(U::*));
  xml_stream_parser &attrib(const char *name_, const attrib_func_t&, void *data_=0);
  template<typename T> xml_stream_parser &attrib(const char *name_, T&);
  template<typename T> xml_stream_parser &attrib(const char *name_, array<T>&);
  template<typename T> xml_stream_parser &attrib(const char *name_, deque<T>&);
  template<typename T> xml_stream_parser &attrib(const char *name_, list<T>&);
  template<typename T, class U> xml_stream_parser &attrib(const char *name_, T(U::*));
  template<class T> xml_stream_parser &attribs_prop();
  xml_stream_parser &attribs_ftl(list<xml_attribute>&);
  template<class T> xml_stream_parser &attribs_ftl(list<xml_attribute>(T::*));
  xml_stream_parser &end_element(const end_func_t &func_=0);
  //--------------------------------------------------------------------------

private:
  xml_stream_parser(const xml_stream_parser&); // not implemented
  void operator=(const xml_stream_parser&); // not implemented
  template<typename T> static void deserialize(xml_input_stream&, void*);
  void process_element(xml_input_stream&, xml_input_stream::string_t&, bool flatten_element_);
  template<class T> PFC_INLINE void add_class_attribs(T*, name_processor_func_t, meta_bool<false> is_introspec_);
  template<class T> PFC_INLINE void add_class_attribs(T*, name_processor_func_t, meta_bool<true> is_introspec_);
  bool begin_element_single(xml_input_stream&, void*);
  template<class Container> bool begin_element_container(xml_input_stream&, void*);
  template<typename T> bool begin_element_member(xml_input_stream&, void*);
  template<class Container> bool begin_element_member_container(xml_input_stream&, void*);
  template<class Container, typename T> static void serialize_data_to_container(xml_input_stream&, void*);
  template<typename T> void serialize_element_mvar(xml_input_stream&, void*);
  static list<xml_attribute> *get_attribs_ftl(void *ftl_data_, void *curr_data_elem_);
  static list<xml_attribute> *get_attribs_ftl_mvar(void *ftl_data_, void *curr_data_elem_);
  //--------------------------------------------------------------------------

  //==========================================================================
  // xml_attrib
  //==========================================================================
  struct xml_attrib
  {
    // operations
    PFC_INLINE bool operator==(const str_id&) const;
    //------------------------------------------------------------------------

    str_id name_id;
    void *data;
    functor<void(xml_input_stream&, void*)> func;
    xml_attrib *next;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // xml_element
  //==========================================================================
  struct xml_element
  {
    // operations
    PFC_INLINE bool operator==(const str_id&) const;
    //------------------------------------------------------------------------

    str_id name_id;
    void *data;
    unsigned type_id;
    begin_func_t begin_func;
    end_func_t end_func;
    xml_element *parent;
    xml_attrib *attribs;
    list<xml_attribute>*(*attribs_ftl_func)(void*, void*);
    void *attribs_ftl_data;
    xml_element *children;
    xml_element *next;
  };
  //--------------------------------------------------------------------------

  deque<xml_attrib> m_attribs;
  deque<xml_element> m_elements;
  // parser state
  xml_element *m_current_element;
  void *m_current_data_element;
};
//----------------------------------------------------------------------------


//============================================================================
// XML parsing helper macros
//============================================================================
#define PFC_XML_PARSE_ATTRIBS_START(xml_stream__) {pfc::xml_input_stream &__xml_stream=xml_stream__; pfc::xml_input_stream::string_t __xml_attr_tag; while(xml_stream__.start_attrib_parsing(__xml_attr_tag)) {
#define PFC_XML_PARSE_ATTRIB(obj__, attrib__) if(__xml_attr_tag==#attrib__) {__xml_stream>>obj__.attrib__; __xml_stream.end_attrib_parsing(); continue;}
#define PFC_XML_PARSE_ATTRIBS_END }}
#define PFC_XML_PARSE_ATTRIBS1(xml_stream__, obj__, a0__) PFC_XML_PARSE_ATTRIBS_START(xml_stream__) PFC_XML_PARSE_ATTRIB(obj__, a0__) PFC_XML_PARSE_ATTRIBS_END
#define PFC_XML_PARSE_ATTRIBS2(xml_stream__, obj__, a0__, a1__) PFC_XML_PARSE_ATTRIBS_START(xml_stream__) PFC_XML_PARSE_ATTRIB(obj__, a0__) PFC_XML_PARSE_ATTRIB(obj__, a1__) PFC_XML_PARSE_ATTRIBS_END
#define PFC_XML_PARSE_ATTRIBS3(xml_stream__, obj__, a0__, a1__, a2__) PFC_XML_PARSE_ATTRIBS_START(xml_stream__) PFC_XML_PARSE_ATTRIBS2(obj__, a0__, a1__) PFC_XML_PARSE_ATTRIB(obj__, a2__) PFC_XML_PARSE_ATTRIBS_END
#define PFC_XML_PARSE_ATTRIBS4(xml_stream__, obj__, a0__, a1__, a2__, a3__) PFC_XML_PARSE_ATTRIBS_START(xml_stream__) PFC_XML_PARSE_ATTRIBS2(obj__, a0__, a1__) PFC_XML_PARSE_ATTRIBS2(obj__, a2__, a3__) PFC_XML_PARSE_ATTRIBS_END
#define PFC_XML_PARSE_ATTRIBS5(xml_stream__, obj__, a0__, a1__, a2__, a3__, a4__) PFC_XML_PARSE_ATTRIBS_START(xml_stream__) PFC_XML_PARSE_ATTRIBS3(obj__, a0__, a1__, a2__) PFC_XML_PARSE_ATTRIBS2(obj__, a3__, a4__) PFC_XML_PARSE_ATTRIBS_END
#define PFC_XML_PARSE_ATTRIBS6(xml_stream__, obj__, a0__, a1__, a2__, a3__, a4__, a5__) PFC_XML_PARSE_ATTRIBS_START(xml_stream__) PFC_XML_PARSE_ATTRIBS3(obj__, a0__, a1__, a2__) PFC_XML_PARSE_ATTRIBS3(obj__, a3__, a4__, a5__) PFC_XML_PARSE_ATTRIBS_END
#define PFC_XML_PARSE_ATTRIBS7(xml_stream__, obj__, a0__, a1__, a2__, a3__, a4__, a5__, a6__) PFC_XML_PARSE_ATTRIBS_START(xml_stream__) PFC_XML_PARSE_ATTRIBS4(obj__, a0__, a1__, a2__, a3__) PFC_XML_PARSE_ATTRIBS3(obj__, a4__, a5__, a6__) PFC_XML_PARSE_ATTRIBS_END
#define PFC_XML_PARSE_ATTRIBS8(xml_stream__, obj__, a0__, a1__, a2__, a3__, a4__, a5__, a6__, a7__) PFC_XML_PARSE_ATTRIBS_START(xml_stream__) PFC_XML_PARSE_ATTRIBS4(obj__, a0__, a1__, a2__, a3__) PFC_XML_PARSE_ATTRIBS4(obj__, a4__, a5__, a6__, a7__) PFC_XML_PARSE_ATTRIBS_END
#define PFC_XML_PARSE_ATTRIBS9(xml_stream__, obj__, a0__, a1__, a2__, a3__, a4__, a5__, a6__, a7__, a8__) PFC_XML_PARSE_ATTRIBS_START(xml_stream__) PFC_XML_PARSE_ATTRIBS5(obj__, a0__, a1__, a2__, a3__, a4__) PFC_XML_PARSE_ATTRIBS4(obj__, a5__, a6__, a7__, a8__) PFC_XML_PARSE_ATTRIBS_END
#define PFC_XML_PARSE_ATTRIBS10(xml_stream__, obj__, a0__, a1__, a2__, a3__, a4__, a5__, a6__, a7__, a8__, a9__) PFC_XML_PARSE_ATTRIBS_START(xml_stream__) PFC_XML_PARSE_ATTRIBS5(obj__, a0__, a1__, a2__, a3__, a4__) PFC_XML_PARSE_ATTRIBS5(obj__, a5__, a6__, a7__, a8__, a9__) PFC_XML_PARSE_ATTRIBS_END
//----------------------------------------------------------------------------

//============================================================================
#include "xml.inl"
} // namespace pfc
#endif
