//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_WIN_CORE_COM_H
#define PFC_WIN_CORE_COM_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "sxp_src/core/core.h"
namespace pfc
{

// new
template<class> class win_com_ptr;
template<class> class win_com_ref;
//----------------------------------------------------------------------------


//============================================================================
// win_com_ptr
//============================================================================
template<class T>
class win_com_ptr
{ PFC_STATIC_ASSERT(sizeof(win_com_ptr<T>)==sizeof(T*));
public:
  // nested types
  typedef T type;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE win_com_ptr();
  PFC_INLINE win_com_ptr(T*);
  PFC_INLINE win_com_ptr(const win_com_ptr&);
  template<typename U> PFC_INLINE win_com_ptr(const win_com_ptr<U>&);
  template<typename U> PFC_INLINE win_com_ptr(const win_com_ref<U>&);
  PFC_INLINE void operator=(T*);
  PFC_INLINE void operator=(const win_com_ptr&);
  template<typename U> PFC_INLINE void operator=(const win_com_ptr<U>&);
  template<typename U> PFC_INLINE void operator=(const win_com_ref<U>&);
  PFC_INLINE ~win_com_ptr();
  //--------------------------------------------------------------------------
  
  // accessors
  PFC_INLINE friend bool is_valid(const win_com_ptr &ptr_)  {return ptr_.data!=0;}
  PFC_INLINE T *operator->() const;
  PFC_INLINE T &operator*() const;
  PFC_INLINE friend T *ptr(const win_com_ptr &ptr_)         {return ptr_.data;}
  //--------------------------------------------------------------------------

  T *data;
};
//----------------------------------------------------------------------------


//============================================================================
// win_com_ref
//============================================================================
template<typename T>
class win_com_ref
{
public:
  // nested types
  typedef T type;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE win_com_ref(T*);
  PFC_INLINE win_com_ref(const win_com_ref&);
  template<typename U> PFC_INLINE win_com_ref(const win_com_ref<U>&);
  template<typename U> PFC_INLINE win_com_ref(const win_com_ptr<U>&);
  PFC_INLINE ~win_com_ref();
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE T *operator->() const;
  PFC_INLINE T &operator*() const;
  PFC_INLINE friend T *ptr(const win_com_ref &ref_)  {return ref_.data;}
  //--------------------------------------------------------------------------

  T *const data;
  //--------------------------------------------------------------------------

private:
  void operator=(const win_com_ref&); // not implemented
};
//----------------------------------------------------------------------------

//============================================================================
#include "win_com.inl"
} // namespace pfc
#endif
