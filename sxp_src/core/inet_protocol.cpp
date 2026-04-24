//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "sxp_src/core/containers.h"
#include "sxp_src/core/inet.h"
#include "inet_protocol.h"
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// external library dependencies
//============================================================================
#ifdef PFC_ENGINEOP_LIBCURL
#include "sxp_extlibs/libcurl/include/curl/curl.h"
//----------------------------------------------------------------------------


//============================================================================
// locals
//============================================================================
namespace
{
  //==========================================================================
  // http_write_heap_str
  //==========================================================================
  size_t http_write_heap_str(void *ptr_, size_t size_, size_t item_size_, void *data_)
  {
    size_t data_size=size_*item_size_;
    if(heap_str *str=(heap_str*)data_)
      str->push_back((const char*)ptr_, data_size);
    return data_size;
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  // http_write_container
  //==========================================================================
  template<class Container>
  size_t http_write_container(void *ptr_, size_t size_, size_t item_size_, void *data_)
  {
    size_t data_size=size_*item_size_;
    if(Container *c=(Container*)data_)
      c->insert_back(data_size, (uint8_t*)ptr_);
    return data_size;
  }
  //--------------------------------------------------------------------------

  //========================================================================== 
  // http_read_buffer
  //==========================================================================
  struct http_read_buffer_context
  {
    const uint8_t *data;
    size_t remaining;
  };
  //----

  size_t http_read_buffer(void *buffer_, size_t size_, size_t nmemb_, void *data_)
  {
    http_read_buffer_context *ctx=(http_read_buffer_context*)data_;
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
// str_append_uri_encoded
//============================================================================
void pfc::str_append_uri_encoded(heap_str &dst_, const char *src_, bool keep_slash_)
{
  PFC_ASSERT(src_);
  while(char ch=*src_++)
  {
    if(is_uri_unreserved(ch) || (keep_slash_ && ch=='/'))
      dst_.push_back(ch);
    else
    {
      const char hex[3]={'%', uint8_to_hex_char_uc((ch>>4)&0x0f), uint8_to_hex_char_uc(ch&0x0f)};
      dst_.push_back(hex, 3);
    }
  }
}
//----------------------------------------------------------------------------


//============================================================================
// inet_http
//============================================================================
inet_http::inet_http()
{
  m_last_http_code=0;
  m_last_curl_code=0;
  inet_system_base &inet=inet_system_base::active();
  CURL *curl=inet.curl_create_easy_handle();
  m_curl=curl;
  if(!curl)
    return;
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
  curl_easy_setopt(curl, CURLOPT_CA_CACHE_TIMEOUT, 604800L);
}
//----

inet_http::~inet_http()
{
  inet_system_base &inet=inet_system_base::active();
  inet.curl_delete_easy_handle((CURL*)m_curl);
}
//----------------------------------------------------------------------------

bool inet_http::read_url(heap_str &res_, const char *url_, const char *const*headers_, unsigned num_headers_, const char *encoding_)
{
  // init data download
  PFC_ASSERT(m_curl);
  PFC_ASSERT(url_);
  PFC_ASSERT(headers_ || !num_headers_);
  CURL *curl=(CURL*)m_curl;
  curl_easy_setopt(curl, CURLOPT_URL, url_);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, http_write_heap_str);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &res_);
  curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, encoding_);
  curl_slist *header_list=0;
  for(unsigned hidx=0; hidx<num_headers_; ++hidx)
    header_list=http_append_header(header_list, headers_[hidx]);
  if(header_list)
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);

  // trigger data download
  m_last_http_code=0;
  m_last_curl_code=0;
  CURLcode res=curl_easy_perform(curl);
  m_last_curl_code=int(res);
  if(res==CURLE_OK)
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &m_last_http_code);
  curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, 0);
  curl_slist_free_all(header_list);
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, 0);
  return res==CURLE_OK && m_last_http_code && m_last_http_code<400;
}
//----

bool inet_http::post_form(heap_str &res_, const char *url_, const char *form_data_, const char *const*headers_, unsigned num_headers_)
{
  // init data upload
  PFC_ASSERT(m_curl);
  PFC_ASSERT(url_);
  PFC_ASSERT(form_data_);
  PFC_ASSERT(headers_ || !num_headers_);
  CURL *curl=(CURL*)m_curl;
  curl_easy_setopt(curl, CURLOPT_URL, url_);
  curl_easy_setopt(curl, CURLOPT_POST, 1L);
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, form_data_);
  curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, long(str_size(form_data_)));
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, http_write_heap_str);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &res_);

  // setup HTTP headers
  curl_slist *header_list=0;
  for(unsigned hidx=0; hidx<num_headers_; ++hidx)
    header_list=http_append_header(header_list, headers_[hidx]);
  header_list=http_append_header(header_list, "Content-Type: application/x-www-form-urlencoded");
  header_list=http_append_header(header_list, "Accept: application/json");
  if(header_list)
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);

  // trigger data upload
  m_last_http_code=0;
  m_last_curl_code=0;
  CURLcode result=curl_easy_perform(curl);
  m_last_curl_code=int(result);
  if(result==CURLE_OK)
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &m_last_http_code);
  curl_slist_free_all(header_list);
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, 0);
  curl_easy_setopt(curl, CURLOPT_POST, 0L);
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, 0);
  return result==CURLE_OK && m_last_http_code && m_last_http_code<400;
}
//----

bool inet_http::download_data(array<uint8_t> &data_, const char *url_, const char *const*headers_, unsigned num_headers_)
{
  return download_data_impl(data_, url_, headers_, num_headers_);
}
//----

bool inet_http::download_data(deque<uint8_t> &data_, const char *url_, const char *const*headers_, unsigned num_headers_)
{
  return download_data_impl(data_, url_, headers_, num_headers_);
}
//----

bool inet_http::upload_data(const char *url_, const void *data_, usize_t data_size_, const char *content_type_, const char *const*headers_, unsigned num_headers_, e_http_upload_method up_method_)
{
  // init data upload
  m_last_http_code=0;
  m_last_curl_code=0;
  if(data_size_==0)
    return true;
  PFC_ASSERT(m_curl);
  PFC_ASSERT(url_);
  PFC_ASSERT(data_);
  PFC_ASSERT(content_type_);
  PFC_ASSERT(headers_ || !num_headers_);
  CURL *curl=(CURL*)m_curl;
  curl_easy_setopt(curl, CURLOPT_URL, url_);
  heap_str res;
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, http_write_heap_str);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &res);
  curl_easy_setopt(curl, CURLOPT_READFUNCTION, http_read_buffer);
  http_read_buffer_context ctx={(const uint8_t*)data_, data_size_};
  curl_easy_setopt(curl, CURLOPT_READDATA, &ctx);

  // setup requested upload method
  switch(up_method_)
  {
    case httpupmethod_post:
    {
      curl_easy_setopt(curl, CURLOPT_POST, 1L);
      curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE_LARGE, data_size_);
    } break;

    case httpupmethod_put:
    {
      curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
      curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, data_size_);
    } break;

    default: PFC_ERROR_NOT_IMPL();
  }

  // setup HTTP headers
  curl_slist *header_list=0;
  for(unsigned hidx=0; hidx<num_headers_; ++hidx)
    header_list=http_append_header(header_list, headers_[hidx]);
  stack_str64 hdr_content_type;
  hdr_content_type.format("Content-Type: %s", content_type_);
  header_list=http_append_header(header_list, hdr_content_type.c_str());
  if(header_list)
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);

  // trigger data upload
  CURLcode result=curl_easy_perform(curl);
  m_last_curl_code=int(result);
  if(result==CURLE_OK)
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &m_last_http_code);
  curl_slist_free_all(header_list);
  curl_easy_setopt(curl, CURLOPT_READFUNCTION, 0);
  curl_easy_setopt(curl, CURLOPT_POST, 0L);
  curl_easy_setopt(curl, CURLOPT_UPLOAD, 0L);
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, 0);
  return result==CURLE_OK && m_last_http_code && m_last_http_code<400;
}
//----

bool inet_http::send_request(const char *url_, const char *custom_request_, const char *const*headers_, unsigned num_headers_)
{
  // init sending request
  PFC_ASSERT(url_);
  PFC_ASSERT(m_curl);
  PFC_ASSERT(headers_ || !num_headers_);
  CURL *curl=(CURL*)m_curl;
  curl_easy_setopt(curl, CURLOPT_URL, url_);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, http_write_heap_str);
  heap_str res;
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &res);
  if(custom_request_)
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, custom_request_);

  // setup HTTP header
  curl_slist *header_list=0;
  for(unsigned hidx=0; hidx<num_headers_; ++hidx)
    header_list=http_append_header(header_list, headers_[hidx]);
  if(header_list)
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);

  // trigger sending request
  m_last_http_code=0;
  m_last_curl_code=0;
  CURLcode result=curl_easy_perform(curl);
  m_last_curl_code=int(result);
  if(result==CURLE_OK)
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &m_last_http_code);
  curl_slist_free_all(header_list);
  curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, 0);
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, 0);
  return result==CURLE_OK && m_last_http_code && m_last_http_code<400;
}
//----------------------------------------------------------------------------

usize_t inet_http::get_content_length(const char *url_)
{
  // send request and return content length from response headers
  PFC_ASSERT(url_);
  PFC_ASSERT(m_curl);
  CURL *curl=(CURL*)m_curl;
  curl_easy_setopt(curl, CURLOPT_URL, url_);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, http_write_heap_str);
  heap_str res;
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &res);
  curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "HEAD");
  curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);

  // trigger sending request and read response metadata
  m_last_http_code=0;
  m_last_curl_code=0;
  CURLcode result=curl_easy_perform(curl);
  m_last_curl_code=int(result);
  curl_off_t content_length=-1;
  if(result==CURLE_OK)
  {
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &m_last_http_code);
    curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD_T, &content_length);
  }
  curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, 0);
  curl_easy_setopt(curl, CURLOPT_NOBODY, 0L);
  return m_last_http_code && m_last_http_code<400?usize_t(content_length):usize_t(-1);
}
//----

long inet_http::get_last_http_code() const
{
  return m_last_http_code;
}
//----

int inet_http::get_last_curl_code() const
{
  return m_last_curl_code;
}
//----------------------------------------------------------------------------

template<class Container>
bool inet_http::download_data_impl(Container &cont_, const char *url_, const char *const*headers_, unsigned num_headers_)
{
  // init data download
  PFC_ASSERT(m_curl);
  PFC_ASSERT(url_);
  PFC_ASSERT(headers_ || !num_headers_);
  CURL *curl=(CURL*)m_curl;
  curl_easy_setopt(curl, CURLOPT_URL, url_);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, http_write_container<Container>);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &cont_);

  // setup HTTP header
  curl_slist *header_list=0;
  for(unsigned hidx=0; hidx<num_headers_; ++hidx)
    header_list=http_append_header(header_list, headers_[hidx]);
  if(header_list)
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);

  // trigger sending request
  m_last_http_code=0;
  m_last_curl_code=0;
  CURLcode result=curl_easy_perform(curl);
  m_last_curl_code=int(result);
  if(result==CURLE_OK)
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &m_last_http_code);
  curl_slist_free_all(header_list);
  curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, 0);
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, 0);
  return result==CURLE_OK && m_last_http_code && m_last_http_code<400;
}
//----------------------------------------------------------------------------

#endif // PFC_ENGINEOP_LIBCURL
