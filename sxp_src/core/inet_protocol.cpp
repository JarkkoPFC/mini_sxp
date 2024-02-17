//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "inet_protocol.h"
using namespace pfc;
//----------------------------------------------------------------------------

#ifdef PFC_ENGINEOP_LIBCURL
#include "sxp_extlibs/libcurl/include/curl/curl.h"
#pragma comment(lib, PFC_STR(PFC_CAT2(libcurl_,PFC_BUILD_STR)PFC_COMPILER_LIB_EXT))
//----------------------------------------------------------------------------


//============================================================================
// locals
//============================================================================
namespace
{
  //==========================================================================
  // curl init/deinit
  //==========================================================================
  unsigned s_curl_init_count=0;
  //--------------------------------------------------------------------------

  void init_curl()
  {
    if(!s_curl_init_count++)
      curl_global_init(CURL_GLOBAL_DEFAULT);
  }
  //----

  void deinit_curl()
  {
    if(!--s_curl_init_count)
      curl_global_cleanup();
  }
  //--------------------------------------------------------------------------


  //==========================================================================
  // http_write
  //==========================================================================
  size_t http_write(void *ptr_, size_t size_, size_t item_size_, void *data_)
  {
    size_t data_size=size_*item_size_;
    heap_str *str=(heap_str*)data_;
    str->push_back((const char*)ptr_, data_size);
    return data_size;
  }
} // namespace <anonymous>
//----------------------------------------------------------------------------


//============================================================================
// inet_http
//============================================================================
inet_http::inet_http()
{
  init_curl();
  CURL *curl=curl_easy_init();
  m_curl=curl;
  if(!curl)
    return;
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
  curl_easy_setopt(curl, CURLOPT_CA_CACHE_TIMEOUT, 604800L);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, http_write);
}
//----

inet_http::~inet_http()
{
  curl_easy_cleanup((CURL*)m_curl);
  deinit_curl();
}
//----------------------------------------------------------------------------

bool inet_http::read_html_page(heap_str &res_, const char *html_address_)
{
  PFC_ASSERT(m_curl);
  res_.clear();
  CURL *curl=(CURL*)m_curl;
  curl_easy_setopt(curl, CURLOPT_URL, html_address_);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &res_);
  CURLcode res=curl_easy_perform(curl);
  return res==CURLE_OK;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
#endif // PFC_ENGINEOP_LIBCURL
