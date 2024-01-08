//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// win_com_ptr
//============================================================================
template<class T>
win_com_ptr<T>::win_com_ptr()
{
  data=0;
}
//----

template<class T>
win_com_ptr<T>::win_com_ptr(T *p_)
{
  data=p_;
}
//----

template<class T>
win_com_ptr<T>::win_com_ptr(const win_com_ptr &ptr_)
{
  if(ptr_.data)
    ptr_.data->AddRef();
  data=ptr_.data;
}
//----

template<class T>
template<typename U>
win_com_ptr<T>::win_com_ptr(const win_com_ptr<U> &ptr_)
{
  if(ptr_.data)
    ptr_.data->AddRef();
  data=ptr_.data;
}
//----

template<class T>
template<typename U>
win_com_ptr<T>::win_com_ptr(const win_com_ref<U> &ref_)
{
  ref_.data->AddRef();
  data=ref_.data;
}
//----

template<class T>
void win_com_ptr<T>::operator=(T *p_)
{
  if(data)
    data->Release();
  data=p_;
}
//----

template<class T>
void win_com_ptr<T>::operator=(const win_com_ptr &ptr_)
{
  if(ptr_.data)
    ptr_.data->AddRef();
  if(data)
    data->Release();
  data=ptr_.data;
}
//----

template<class T>
template<typename U>
void win_com_ptr<T>::operator=(const win_com_ptr<U> &ptr_)
{
  if(ptr_.data)
    ptr_.data->AddRef();
  if(data)
    data->Release();
  data=ptr_.data;
}
//----

template<class T>
template<typename U>
void win_com_ptr<T>::operator=(const win_com_ref<U> &ref_)
{
  ref_.data->AddRef();
  if(data)
    data->Release();
  data=ref_.data;
}
//----

template<class T>
win_com_ptr<T>::~win_com_ptr()
{
  if(data)
    data->Release();
}
//----------------------------------------------------------------------------

template<class T>
T *win_com_ptr<T>::operator->() const
{
  PFC_ASSERT_PEDANTIC_MSG(data, ("Dereferencing \"%s\" NULL pointer\r\n", typeid(T).name()));
  return data;
}
//----

template<class T>
T &win_com_ptr<T>::operator*() const
{
  PFC_ASSERT_PEDANTIC_MSG(data, ("Dereferencing \"%s\" NULL pointer\r\n", typeid(T).name()));
  return *data;
}
//----------------------------------------------------------------------------


//============================================================================
// win_com_ref
//============================================================================
template<class T>
win_com_ref<T>::win_com_ref(T *p_)
  :data(p_)
{
  PFC_ASSERT_PEDANTIC(p_);
}
//----

template<class T>
win_com_ref<T>::win_com_ref(const win_com_ref &ref_)
  :data(ref_.data)
{
  data->AddRef();
}
//----

template<class T>
template<typename U>
win_com_ref<T>::win_com_ref(const win_com_ref<U> &ref_)
  :data(ref_.data)
{
  data->AddRef();
}
//----

template<class T>
template<typename U>
win_com_ref<T>::win_com_ref(const win_com_ptr<U> &ptr_)
{
  PFC_ASSERT_PEDANTIC(ptr_.data);
  data=ptr_.data;
  data->AddRef();
}
//----

template<class T>
win_com_ref<T>::~win_com_ref()
{
  data->Release();
}
//----------------------------------------------------------------------------

template<class T>
T *win_com_ref<T>::operator->() const
{
  return data;
}
//----

template<class T>
T &win_com_ref<T>::operator*() const
{
  return *data;
}
//----------------------------------------------------------------------------
