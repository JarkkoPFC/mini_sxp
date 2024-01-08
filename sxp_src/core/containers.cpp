//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "containers.h"
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// str_pool
//============================================================================
str_pool::str_pool()
{
  PFC_MEM_TRACK_STACK();
  m_size=0;
  m_strides.reserve(8);
}
//----

str_pool::~str_pool()
{
  clear();
}
//----

void str_pool::clear()
{
  // clear strides
  usize_t num_strides=m_strides.size();
  for(usize_t i=0; i<num_strides; ++i)
    PFC_MEM_FREE(m_strides[i].data);
  m_strides.clear();
  m_size=0;
}
//----------------------------------------------------------------------------

const char *str_pool::add_string(const char *str_)
{
  // search stride which can hold the string
  PFC_MEM_TRACK_STACK();
  usize_t size=str_size(str_);
  PFC_ASSERT_MSG(size<stride_size-1, ("String is too long (%i) for repository, max size is %i\r\n", size, stride_size-1));
  if(size==0)
    return "";
  ++size;
  usize_t num_strides=m_strides.size();
  for(usize_t i=0; i<num_strides; ++i)
  {
    stride &s=m_strides[i];
    if(s.free_space>=size)
    {
      // add new string to the stride
      char *str=s.data+stride_size-s.free_space;
      mem_copy(str, str_, size);
      s.free_space=s.free_space-(unsigned short)size;
      ++s.num_strings;
      ++m_size;
      return str;
    }
  }

  // no stride found so add new stride and string to the stride
  stride &s=m_strides.push_back();
  usize_t ssize=max<usize_t>(stride_size, size);
  s.data=(char*)PFC_MEM_ALLOC(ssize);
  s.free_space=(unsigned short)(stride_size-size);
  s.num_strings=1;
  mem_copy(s.data, str_, size);
  ++m_size;
  return (const char*)s.data;
}
//----

void str_pool::remove_string(const char *str_)
{
  // search for stride where the string is located
  usize_t num_strides=m_strides.size();
  stride *strides=m_strides.data();
  for(usize_t i=0; i<num_strides; ++i)
  {
    stride &s=strides[i];
    if(s.data<=str_ && str_<s.data+stride_size)
    {
      // free the stride if all strings for it are removed
      if(!--s.num_strings)
      {
        PFC_MEM_FREE(s.data);
        strides[i]=strides[num_strides-1];
        m_strides.pop_back();
      }
      return;
    }
  }
  PFC_ERRORF("Given string \"%s\" doesn't reside in the string pool\r\n", str_);
}
//----

void str_pool::splice(str_pool &pool_)
{
  // add strides from the pool to this pool
  usize_t idx=m_strides.size();
  usize_t num_new_strides=pool_.m_strides.size();
  m_strides.insert_back(num_new_strides);
  for(usize_t i=0; i<num_new_strides; ++i)
  {
    m_strides[idx]=pool_.m_strides[i];
    pool_.m_strides[i].data=0;
  }
  m_size+=pool_.m_size;
  pool_.clear();
}
//----------------------------------------------------------------------------
