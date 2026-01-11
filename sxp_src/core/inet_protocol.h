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

// new
class inet_http;
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
  bool read_html_page(heap_str&, const char *url_, const char *encoding_=0);
  bool upload_data(const char *url_, const void *data_, usize_t data_size_, const char *content_type_, const char *header_=0);
  bool send_request(const char *url_, const char *custom_request_, const char *header_=0);
  //-------------------------------------------------------------------------- 

private:
  inet_http(const inet_http&); // not implemented
  void operator=(const inet_http&); // not implemented
  //--------------------------------------------------------------------------

  void *m_curl;
};
//----------------------------------------------------------------------------

//============================================================================
} // namespace pfc
#endif
