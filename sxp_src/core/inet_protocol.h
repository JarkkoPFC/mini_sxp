//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_INET_PROTOCOL_H
#define PFC_CORE_INET_PROTOCOL_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "str.h"
namespace pfc
{
template<typename> class array;
template<typename> class deque;

// new
class inet_http;
heap_str inet_percent_encode(const char *value_);
//----------------------------------------------------------------------------


//============================================================================
// e_http_upload_method
//============================================================================
enum e_http_upload_method
{
  httpupmethod_post,
  httpupmethod_put,
};
//----------------------------------------------------------------------------


//============================================================================
// inet_http
//============================================================================
class inet_http
{
public:
  // construction
  inet_http();
  ~inet_http();
  //--------------------------------------------------------------------------

  // data transfer
  bool read_url(heap_str&, const char *url_, const char *encoding_=0, const char *header_=0);
  bool post_form(heap_str&, const char *url_, const char *form_data_, const char *header_=0);
  bool download_data(array<uint8_t>&, const char *url_, const char *header_=0);
  bool download_data(deque<uint8_t>&, const char *url_, const char *header_=0);
  bool upload_data(const char *url_, const void *data_, usize_t data_size_, const char *content_type_, const char *header_=0, e_http_upload_method=httpupmethod_post);
  bool send_request(const char *url_, const char *custom_request_, const char *header_=0);
  //-------------------------------------------------------------------------- 

private:
  inet_http(const inet_http&); // not implemented
  void operator=(const inet_http&); // not implemented
  template<class T> bool download_data_impl(T&, const char *url_, const char *header_);
  //--------------------------------------------------------------------------

  void *m_curl;
};
//----------------------------------------------------------------------------

//============================================================================
} // namespace pfc
#endif
