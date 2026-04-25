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
void str_append_uri_encoded(heap_str &dst_, const char *src_, bool keep_slash_=false);
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
  void set_timeout(unsigned seconds_);
  //--------------------------------------------------------------------------

  // data transfer
  bool read_url(heap_str&, const char *url_, const char *const*headers_=0, unsigned num_headers_=0, const char *encoding_=0);
  bool post_form(heap_str&, const char *url_, const char *form_data_, const char *const*headers_=0, unsigned num_headers_=0);
  bool download_data(array<uint8_t>&, const char *url_, const char *const*headers_=0, unsigned num_headers_=0);
  bool download_data(deque<uint8_t>&, const char *url_, const char *const*headers_=0, unsigned num_headers_=0);
  bool upload_data(const char *url_, const void *data_, usize_t data_size_, const char *content_type_, const char *const*headers_=0, unsigned num_headers_=0, e_http_upload_method=httpupmethod_post);
  bool send_request(const char *url_, const char *custom_request_, const char *const*headers_=0, unsigned num_headers_=0);
  usize_t get_content_length(const char *url_);
  long get_last_http_code() const;
  int get_last_curl_code() const;
  //-------------------------------------------------------------------------- 

private:
  inet_http(const inet_http&); // not implemented
  void operator=(const inet_http&); // not implemented
  template<class T> bool download_data_impl(T&, const char *url_, const char *const*headers_, unsigned num_headers_);
  //--------------------------------------------------------------------------

  void *m_curl;
  long m_last_http_code;
  int m_last_curl_code;
};
//----------------------------------------------------------------------------

//============================================================================
} // namespace pfc
#endif
