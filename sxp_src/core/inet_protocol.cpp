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


//============================================================================
// external library dependencies
//============================================================================
#ifdef PFC_ENGINEOP_LIBCURL
#include "sxp_extlibs/libcurl/include/curl/curl.h"
#pragma comment(lib, PFC_STR(PFC_CAT2(libcurl_,PFC_BUILD_STR)PFC_COMPILER_LIB_EXT))
// zlib
#ifdef PFC_ENGINEOP_ZLIB
#pragma comment(lib, PFC_STR(PFC_CAT2(zlib_,PFC_BUILD_STR)PFC_COMPILER_LIB_EXT))
#endif
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
    if(heap_str *str=(heap_str*)data_)
      str->push_back((const char*)ptr_, data_size);
    return data_size;
  }
  //--------------------------------------------------------------------------

  //========================================================================== 
  // http_upload_read
  //==========================================================================
  struct http_upload_context
  {
    const uint8_t *data;
    size_t remaining;
  };
  //----

  size_t http_upload_read(void *buffer_, size_t size_, size_t nmemb_, void *data_)
  {
    http_upload_context *ctx=(http_upload_context*)data_;
    const size_t num_bytes=min(size_*nmemb_, ctx->remaining);
    std::memcpy(buffer_, ctx->data, num_bytes);
    ctx->data+=num_bytes;
    ctx->remaining-=num_bytes;
    return num_bytes;
  }
  //--------------------------------------------------------------------------

  //========================================================================== 
  // http_append_header
  //========================================================================== 
  curl_slist *http_append_header(curl_slist *list_, const char *header_)
  {
    return header_?curl_slist_append(list_, header_):list_;
  }
  //--------------------------------------------------------------------------
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

bool inet_http::read_html_page(heap_str &res_, const char *url_, const char *encoding_)
{
  // init data download
  PFC_ASSERT(m_curl);
  PFC_ASSERT(url_);
  CURL *curl=(CURL*)m_curl;
  curl_easy_setopt(curl, CURLOPT_URL, url_);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &res_);
  curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, encoding_);

  // trigger data download
  CURLcode res=curl_easy_perform(curl);
  return res==CURLE_OK;
}
//----

bool inet_http::upload_data(const char *url_, const void *data_, usize_t data_size_, const char *content_type_, const char *header_)
{
  // init data upload
  if(data_size_==0)
    return true;
  PFC_ASSERT(m_curl);
  PFC_ASSERT(url_);
  PFC_ASSERT(data_);
  PFC_ASSERT(content_type_);
  CURL *curl=(CURL*)m_curl;
  curl_easy_setopt(curl, CURLOPT_URL, url_);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, 0);
  curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
  http_upload_context ctx={(const uint8_t*)data_, data_size_};
  curl_easy_setopt(curl, CURLOPT_READFUNCTION, http_upload_read);
  curl_easy_setopt(curl, CURLOPT_READDATA, &ctx);
  curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, data_size_);

  // setup HTTP headers
  curl_slist *header_list=http_append_header(0, header_);
  stack_str64 hdr_content_type;
  hdr_content_type.format("Content-Type: %s", content_type_);
  header_list=http_append_header(header_list, hdr_content_type.c_str());
  if(header_list)
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);

  // trigger data upload
  CURLcode result=curl_easy_perform(curl);
  curl_slist_free_all(header_list);
  return result==CURLE_OK;
}
//----

bool inet_http::send_request(const char *url_, const char *custom_request_, const char *header_)
{
  // init sending request
  PFC_ASSERT(url_);
  PFC_ASSERT(m_curl);
  CURL *curl=(CURL*)m_curl;
  curl_easy_setopt(curl, CURLOPT_URL, url_);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, 0);
  if(custom_request_)
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, custom_request_);

  // setup HTTP header
  curl_slist *header_list=http_append_header(0, header_);
  if(header_list)
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);

  // trigger sending request
  CURLcode result=curl_easy_perform(curl);
  curl_slist_free_all(header_list);
  return result==CURLE_OK;
}
//----------------------------------------------------------------------------

#endif // PFC_ENGINEOP_LIBCURL
