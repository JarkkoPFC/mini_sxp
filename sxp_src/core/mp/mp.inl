//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// fundamental atomic operations
//============================================================================
template<typename T>
PFC_INLINE T atom_inc(volatile T &v_)
{
  PFC_STATIC_ASSERT_MSG(is_type_int<T>::res, atomic_increment_works_only_on_fundamental_integral_types);
  return raw_cast<T>(priv::atom_hlp<sizeof(T), is_type_int<T>::res>::op_inc(v_));
}
//----

template<typename T>
PFC_INLINE T atom_dec(volatile T &v_)
{
  PFC_STATIC_ASSERT_MSG(is_type_int<T>::res, atomic_decrement_works_only_on_fundamental_integral_types);
  return raw_cast<T>(priv::atom_hlp<sizeof(T), is_type_int<T>::res>::op_dec(v_));
}
//----

template<typename T>
PFC_INLINE T atom_add(volatile T &dst_, T v_)
{
  PFC_STATIC_ASSERT_MSG(is_type_int<T>::res, atomic_addition_works_only_on_fundamental_integral_types);
  return raw_cast<T>(priv::atom_hlp<sizeof(T), is_type_int<T>::res>::op_add(dst_, v_));
}
//----

template<typename T>
PFC_INLINE T atom_sub(volatile T &dst_, T v_)
{
  PFC_STATIC_ASSERT_MSG(is_type_int<T>::res, atomic_subtraction_works_only_on_fundamental_integral_types);
  return raw_cast<T>(priv::atom_hlp<sizeof(T), is_type_int<T>::res>::op_sub(dst_, v_));
}
//----

template<typename T>
PFC_INLINE T atom_mov(volatile T &dst_, T v_)
{
  return raw_cast<T>(priv::atom_hlp<sizeof(T), true>::op_mov(dst_, v_));
}
//----

template<typename T>
PFC_INLINE T atom_read(const volatile T &src_)
{
  return raw_cast<T>(priv::atom_hlp<sizeof(T), true>::op_read(src_));
}
//----

template<typename T>
PFC_INLINE void atom_write(volatile T &dst_, T v_)
{
  priv::atom_hlp<sizeof(T), true>::op_write(dst_, v_);
}
//----

template<typename T>
PFC_INLINE T atom_and(volatile T &dst_, T v_)
{
  PFC_STATIC_ASSERT_MSG(is_type_int<T>::res, atomic_and_works_only_on_fundamental_integral_types);
  return raw_cast<T>(priv::atom_hlp<sizeof(T), true>::op_and(dst_, v_));
}
//----

template<typename T>
PFC_INLINE T atom_or(volatile T &dst_, T v_)
{
  PFC_STATIC_ASSERT_MSG(is_type_int<T>::res, atomic_or_works_only_on_fundamental_integral_types);
  return raw_cast<T>(priv::atom_hlp<sizeof(T), true>::op_or(dst_, v_));
}
//----

template<typename T>
PFC_INLINE T atom_xor(volatile T &dst_, T v_)
{
  PFC_STATIC_ASSERT_MSG(is_type_int<T>::res, atomic_xor_works_only_on_fundamental_integral_types);
  return raw_cast<T>(priv::atom_hlp<sizeof(T), true>::op_xor(dst_, v_));
}
//----

template<typename T>
PFC_INLINE T atom_cmov_eq(volatile T &dst_, T v_, T cmp_)
{
  return raw_cast<T>(priv::atom_hlp<sizeof(T), true>::op_cmov(dst_, v_, cmp_));
}
//----

template<typename T>
PFC_INLINE T atom_cmov_lt(volatile T &dst_, T v_, T cmp_)
{
  // move v_ to dst_ if dst_ is less than cmp_
  T dst;
  do
  {
    dst=dst_;
  } while(dst<cmp_ && raw_cast<T>(priv::atom_hlp<sizeof(T), true>::op_cmov(dst_, v_, dst))!=dst);
  return dst;
}
//----

template<typename T>
PFC_INLINE T atom_cmov_gt(volatile T &dst_, T v_, T cmp_)
{
  // move v_ to dst_ if dst_ is greater than cmp_
  T dst;
  do
  {
    dst=dst_;
  } while(dst>cmp_ && raw_cast<T>(priv::atom_hlp<sizeof(T), true>::op_cmov(dst_, v_, dst))!=dst);
  return dst;
}
//----

template<typename T>
PFC_INLINE T atom_cmov_lte(volatile T &dst_, T v_, T cmp_)
{
  // move v_ to dst_ if dst_ is less than or equal to cmp_
  T dst;
  do
  {
    dst=dst_;
  } while(dst<=cmp_ && raw_cast<T>(priv::atom_hlp<sizeof(T), true>::op_cmov(dst_, v_, dst))!=dst);
  return dst;
}
//----

template<typename T>
PFC_INLINE T atom_cmov_gte(volatile T &dst_, T v_, T cmp_)
{
  // move v_ to dst_ if dst_ is greater than or equal to cmp_
  T dst;
  do
  {
    dst=dst_;
  } while(dst>=cmp_ && raw_cast<T>(priv::atom_hlp<sizeof(T), true>::op_cmov(dst_, v_, dst))!=dst);
  return dst;
}
//----

template<typename T>
PFC_INLINE T atom_cmov_min(volatile T &dst_, T v_)
{
  // move minimum of dst_ and v_ to dst_
  T dst;
  do
  {
    dst=dst_;
  } while(dst>v_ && raw_cast<T>(priv::atom_hlp<sizeof(T), true>::op_cmov(dst_, v_, dst))!=dst);
  return dst;
}
//----

template<typename T>
PFC_INLINE T atom_cmov_max(volatile T &dst_, T v_)
{
  // move maximum of dst_ and v_ to dst_
  T dst;
  do
  {
    dst=dst_;
  } while(dst<v_ && raw_cast<T>(priv::atom_hlp<sizeof(T), true>::op_cmov(dst_, v_, dst))!=dst);
  return dst;
}
//----------------------------------------------------------------------------


//============================================================================
// atom_push_front
//============================================================================
template<typename T, T *(T::*next_mvar)>
PFC_INLINE void atom_push_front(T*&head_, T &item_)
{
  // push item to the queue
  T *head, *item=&item_;
  do
  {
    head=head_;
    item_.*next_mvar=head;
  } while(atom_cmov_eq(head_, item, head)!=head);
}
//----------------------------------------------------------------------------


//============================================================================
// mp_tptr
//============================================================================
template<typename T>
PFC_INLINE mp_tptr<T> atom_cmov_eq(volatile mp_tptr<T> &dst_, const mp_tptr<T> &v_, const mp_tptr<T> &comp_)
{
  return mp_tptr<T>(atom_cmov_eq(dst_.m_data.data, v_.m_data.data, comp_.m_data.data));
}
//----------------------------------------------------------------------------

template<typename T>
mp_tptr<T>::mp_tptr()
{
  PFC_STATIC_ASSERT(sizeof(mp_tptr)==sizeof(usize2_t) && unsigned(meta_alignof<mp_tptr>::res)==unsigned(meta_alignof<usize2_t>::res));
  m_data.ptr_data.ptr=0;
  m_data.ptr_data.count=0;
}
//----

template<typename T>
mp_tptr<T>::mp_tptr(const mp_tptr &p_)
{
  PFC_STATIC_ASSERT(sizeof(mp_tptr)==sizeof(usize2_t) && unsigned(meta_alignof<mp_tptr>::res)==unsigned(meta_alignof<usize2_t>::res));
  m_data.data=p_.m_data.data;
}
//----

template<typename T>
mp_tptr<T>::mp_tptr(const volatile mp_tptr &p_)
{
  // volatile-safe copy construction
  PFC_STATIC_ASSERT(sizeof(mp_tptr)==sizeof(usize2_t) && unsigned(meta_alignof<mp_tptr>::res)==unsigned(meta_alignof<usize2_t>::res));
  m_data.data=atom_read(p_.m_data.data);
}
//----

template<typename T>
mp_tptr<T>::mp_tptr(T *p_)
{
  PFC_STATIC_ASSERT(sizeof(mp_tptr)==sizeof(usize2_t) && unsigned(meta_alignof<mp_tptr>::res)==unsigned(meta_alignof<usize2_t>::res));
  m_data.ptr_data.ptr=p_;
  m_data.ptr_data.count=0;
}
//----

template<typename T>
mp_tptr<T>::mp_tptr(T *p_, usize_t count_)
{
  PFC_STATIC_ASSERT(sizeof(mp_tptr)==sizeof(usize2_t) && unsigned(meta_alignof<mp_tptr>::res)==unsigned(meta_alignof<usize2_t>::res));
  m_data.ptr_data.ptr=p_;
  m_data.ptr_data.count=count_;
}
//----------------------------------------------------------------------------

template<typename T>
T *mp_tptr<T>::operator->() const volatile
{
  return m_data.ptr_data.ptr;
}
//----

template<typename T>
T &mp_tptr<T>::operator*() const volatile
{
  PFC_ASSERT_PEDANTIC(m_data.ptr_data.ptr!=0);
  return *m_data.ptr_data.ptr;
}
//----

template<typename T>
T *mp_tptr<T>::ptr() const volatile
{
  return m_data.ptr_data.ptr;
}
//----

template<typename T>
usize_t mp_tptr<T>::count() const volatile
{
  return m_data.ptr_data.count;
}
//----

template<typename T>
void mp_tptr<T>::set(const mp_tptr<T> &p_)
{
  m_data.data=p_.m_data.data;
}
//----

template<typename T>
void mp_tptr<T>::set(const volatile mp_tptr<T> &p_)
{
  // volatile-safe assignment
  m_data.data=atom_read(p_.m_data.data);
}
//----

template<typename T>
void mp_tptr<T>::set(const mp_tptr<T> &p_) volatile
{
  // volatile-safe assignment
  usize2_t dst, src=p_.m_data.data;
  do
  {
    dst=atom_read(m_data.data);
  } while(atom_cmov_eq(m_data.data, src, dst)!=dst);
}
//----

template<typename T>
void mp_tptr<T>::set(const volatile mp_tptr<T> &p_) volatile
{
  // volatile-safe assignment
  usize2_t dst, src=atom_read(p_.m_data.data);
  do
  {
    dst=atom_read(m_data.data);
  } while(atom_cmov_eq(m_data.data, src, dst)!=dst);
}
//----

template<typename T>
void mp_tptr<T>::set(T *p_)
{
  m_data.ptr_data.ptr=p_;
  m_data.ptr_data.count=0;
}
//----

template<typename T>
void mp_tptr<T>::set(T *p_) volatile
{
  // volatile-safe assignment
  ptr_union p;
  p.ptr_data.ptr=p_;
  p.ptr_data.count=0;
  usize2_t dst, src=p.data;
  do
  {
    dst=atom_read(m_data.data);
  } while(atom_cmov_eq(m_data.data, src, dst)!=dst);
}
//----

template<typename T>
void mp_tptr<T>::set(T *p_, usize_t count_)
{
  m_data.ptr_data.ptr=p_;
  m_data.ptr_data.count=count_;
}
//----

template<typename T>
void mp_tptr<T>::set(T *p_, usize_t count_) volatile
{
  // volatile-safe assignment
  ptr_union p;
  p.ptr_data.ptr=p_;
  p.ptr_data.count=count_;
  usize2_t dst, src=p.data;
  do
  {
    dst=atom_read(m_data.data);
  } while(atom_cmov_eq(m_data.data, src, dst)!=dst);
}
//----------------------------------------------------------------------------

template<typename T>
bool mp_tptr<T>::operator==(const mp_tptr &p_) const
{
  // test equality of the pointers
  return m_data.data==p_.m_data.data;
}
//----

template<typename T>
bool mp_tptr<T>::operator==(const volatile mp_tptr &p_) const
{
  // test equality of the pointers (volatile-safe)
  return m_data.data==atom_read(p_.m_data.data);
}
//----

template<typename T>
bool mp_tptr<T>::operator==(const mp_tptr &p_) const volatile
{
  // test equality of the pointers (volatile-safe)
  return atom_read(m_data.data)==p_.m_data.data;
}
//----

template<typename T>
bool mp_tptr<T>::operator==(const volatile mp_tptr &p_) const volatile
{
  // test equality of the pointers (volatile-safe)
  return atom_read(m_data.data)==atom_read(p_.m_data.data);
}
//----

template<typename T>
bool mp_tptr<T>::operator!=(const mp_tptr &p_) const
{
  // test inequality of the pointers
  return m_data.data!=p_.m_data.data;
}
//----

template<typename T>
bool mp_tptr<T>::operator!=(const volatile mp_tptr &p_) const
{
  // test inequality of the pointers (volatile-safe)
  return m_data.data!=atom_read(p_.m_data.data);
}
//----

template<typename T>
bool mp_tptr<T>::operator!=(const mp_tptr &p_) const volatile
{
  // test inequality of the pointers (volatile-safe)
  return atom_read(m_data.data)!=p_.m_data.data;
}
//----

template<typename T>
bool mp_tptr<T>::operator!=(const volatile mp_tptr &p_) const volatile
{
  // test inequality of the pointers (volatile-safe)
  return atom_read(m_data.data)!=p_.m_data.data;
}
//----------------------------------------------------------------------------

template<typename T>
mp_tptr<T>::mp_tptr(usize2_t data_)
{
  m_data.data=data_;
}
//----------------------------------------------------------------------------


//============================================================================
// mp_fifo_queue
//============================================================================
// Implementation based on paper "Optimized Lock-Free FIFO Queue continued"
template<typename T, T *(T::*next_mvar)>
mp_fifo_queue<T, next_mvar>::mp_fifo_queue()
{
  force_clear();
}
//----

template<typename T, T *(T::*next_mvar)>
mp_fifo_queue<T, next_mvar>::~mp_fifo_queue()
{
  PFC_ASSERT_MSG(   m_head.ptr_data.ptr==(T*)(((char*)&m_dummy_next)-PFC_OFFSETOF_MVARPTR(T,next_mvar))
                 && m_tail.ptr_data.ptr==(T*)(((char*)&m_dummy_next)-PFC_OFFSETOF_MVARPTR(T,next_mvar)), ("FIFO-queue not empty upon destruction\r\n"));
}
//----

template<typename T, T *(T::*next_mvar)>
void mp_fifo_queue<T, next_mvar>::force_clear()
{
  // initialize the queue
  T *dummy=(T*)(((char*)&m_dummy_next)-PFC_OFFSETOF_MVARPTR(T, next_mvar));
  m_dummy_next=(T*)-1;
  m_head.ptr_data.count=0;
  m_head.ptr_data.ptr=dummy;
  m_tail.ptr_data.count=0;
  m_tail.ptr_data.ptr=dummy;
}
//----------------------------------------------------------------------------

template<typename T, T *(T::*next_mvar)>
T *mp_fifo_queue<T, next_mvar>::head() const
{
  // return queue head (skip dummy node)
  T *dummy=(T*)(((char*)&m_dummy_next)-PFC_OFFSETOF_MVARPTR(T, next_mvar));
  T *head=m_head.ptr_data.ptr;
  T *item=head==dummy?head->*next_mvar:head;
  return item==(T*)-1?0:item;
}
//----

template<typename T, T *(T::*next_mvar)>
void mp_fifo_queue<T, next_mvar>::push(T &item_)
{
  // enqueue item to the end of the queue
  item_.*next_mvar=(T*)-1;
  T *next;
  do
  {
    ptr_union new_tail, tail=atom_read(m_tail);
    T *item=&item_;
    next=atom_cmov_eq(m_tail.ptr_data.ptr->*next_mvar, item, (T*)-1);
    new_tail.ptr_data.count=tail.ptr_data.count+1;
    new_tail.ptr_data.ptr=tail.ptr_data.ptr->*next_mvar;
    atom_cmov_eq(m_tail.data, new_tail.data, tail.data);
  } while(next!=(T*)-1);
}
//----

template<typename T, T *(T::*next_mvar)>
bool mp_fifo_queue<T, next_mvar>::secure_push(T &item_)
{
  // enqueue item to the end of the queue only if it's not in the queue (i.e. next-pointer is 0)
  if(atom_cmov_eq(item_.*next_mvar, (T*)-1, (T*)0)!=0)
    return false;
  T *next;
  do
  {
    ptr_union new_tail, tail=atom_read(m_tail);
    next=atom_cmov_eq(m_tail.ptr_data.ptr->*next_mvar, &item_, (T*)-1);
    new_tail.ptr_data.count=tail.ptr_data.count+1;
    new_tail.ptr_data.ptr=tail.ptr_data.ptr->*next_mvar;
    atom_cmov_eq(m_tail.data, new_tail.data, tail.data);
  } while(next!=(T*)-1);
  return true;
}
//----

template<typename T, T *(T::*next_mvar)>
T *mp_fifo_queue<T, next_mvar>::pop()
{
  // dequeue item from the queue
  while(true)
  {
    // read initial dequeue state
    ptr_union head=atom_read(m_head);
    usize_t tail_count=m_tail.ptr_data.count;
    T *next=head.ptr_data.ptr->*next_mvar;

    // check integrity of the initial state
    if(head.ptr_data.count==m_head.ptr_data.count)
    {
      // check for empty queue / lacking tail pointer
      if(head.ptr_data.ptr==m_tail.ptr_data.ptr)
      {
        // check for empty queue
        if(next==(T*)-1)
          return 0;

        // try to advance tail
        ptr_union new_tail;
        new_tail.ptr_data.count=tail_count+1;
        new_tail.ptr_data.ptr=next;
        head.ptr_data.count=tail_count;
        atom_cmov_eq(m_tail.data, new_tail.data, head.data);
        continue;
      }

      // try to dequeue item
      ptr_union new_head;
      new_head.ptr_data.count=head.ptr_data.count+1;
      new_head.ptr_data.ptr=next;
      if(next!=(T*)-1 && atom_cmov_eq(m_head.data, new_head.data, head.data)==head.data)
      {
        // if dummy node, recycle it
        T *dummy=(T*)(((char*)&m_dummy_next)-PFC_OFFSETOF_MVARPTR(T, next_mvar));
        if(head.ptr_data.ptr!=dummy)
          return head.ptr_data.ptr;
        push(*head.ptr_data.ptr);
      }
    }
  }
}
//----

template<typename T, T *(T::*next_mvar)>
T *mp_fifo_queue<T, next_mvar>::pop_if(const T *v_)
{
  // dequeue item from the queue if it equals given value
  while(true)
  {
    // read initial dequeue state
    ptr_union head=atom_read(m_head);
    usize_t tail_count=m_tail.ptr_data.count;
    T *next=head.ptr_data.ptr->*next_mvar;

    // check if head doesn't match the requested item
    T *dummy=(T*)(((char*)&m_dummy_next)-PFC_OFFSETOF_MVARPTR(T, next_mvar));
    if(head.ptr_data.ptr!=v_ && head.ptr_data.ptr!=dummy)
      return 0;

    // check integrity of the initial state
    if(head.ptr_data.count==m_head.ptr_data.count)
    {
      // check for empty queue / lacking tail pointer
      if(head.ptr_data.ptr==m_tail.ptr_data.ptr)
      {
        // check for empty queue
        if(next==(T*)-1)
          return 0;

        // try to advance tail
        ptr_union new_tail;
        new_tail.ptr_data.count=tail_count+1;
        new_tail.ptr_data.ptr=next;
        head.ptr_data.count=tail_count;
        atom_cmov_eq(m_tail.data, new_tail.data, head.data);
        continue;
      }

      // try to dequeue item
      ptr_union new_head;
      new_head.ptr_data.count=head.ptr_data.count+1;
      new_head.ptr_data.ptr=next;
      if(next!=(T*)-1 && atom_cmov_eq(m_head.data, new_head.data, head.data)==head.data)
      {
        // if dummy node, recycle it
        if(head.ptr_data.ptr!=dummy)
          return head.ptr_data.ptr;
        push(*head.ptr_data.ptr);
      }
    }
  }
}
//----------------------------------------------------------------------------


//============================================================================
// mp_lifo_queue
//============================================================================
template<typename T, T *(T::*next_mvar)>
mp_lifo_queue<T, next_mvar>::mp_lifo_queue()
{
  m_head.ptr_data.count=0;
  m_head.ptr_data.ptr=0;
}
//----

template<typename T, T *(T::*next_mvar)>
mp_lifo_queue<T, next_mvar>::~mp_lifo_queue()
{
  PFC_ASSERT_MSG(!m_head.ptr_data.ptr, ("LIFO-queue not empty upon destruction\r\n"));
}
//----

template<typename T, T *(T::*next_mvar)>
void mp_lifo_queue<T, next_mvar>::force_clear()
{
  m_head.ptr_data.count=0;
  m_head.ptr_data.ptr=0;
}
//----------------------------------------------------------------------------

template<typename T, T *(T::*next_mvar)>
T *mp_lifo_queue<T, next_mvar>::head() const
{
  return m_head.ptr_data.ptr;
}
//----

template<typename T, T *(T::*next_mvar)>
void mp_lifo_queue<T, next_mvar>::push(T &item_)
{
  // enqueue item to the beginning of the queue
  T *head, *item=&item_;
  do
  {
    head=m_head.ptr_data.ptr;
    item_.*next_mvar=head;
  } while(atom_cmov_eq(m_head.ptr_data.ptr, item, head)!=head);
}
//----

template<typename T, T *(T::*next_mvar)>
T *mp_lifo_queue<T, next_mvar>::pop()
{
  // dequeue item from the beginning of the queue
  ptr_union item, new_head;
  do
  {
    item.data=atom_read(m_head.data);
    if(!item.ptr_data.ptr)
      return 0;
    new_head.ptr_data.count=item.ptr_data.count+1;
    new_head.ptr_data.ptr=item.ptr_data.ptr->*next_mvar;
  } while(atom_cmov_eq(m_head.data, new_head.data, item.data)!=item.data);
  return item.ptr_data.ptr;
}
//----

template<typename T, T *(T::*next_mvar)>
T *mp_lifo_queue<T, next_mvar>::pop_if(const T *v_)
{
  // dequeue item from the beginning of the queue
  ptr_union item, new_head;
  do
  {
    item.data=atom_read(m_head.data);
    if(!item.ptr_data.ptr || item.ptr_data.ptr!=v_)
      return 0;
    new_head.ptr_data.count=item.ptr_data.count+1;
    new_head.ptr_data.ptr=item.ptr_data.ptr->*next_mvar;
  } while(atom_cmov_eq(m_head.data, new_head.data, item.data)!=item.data);
  return item.ptr_data.ptr;
}
//----------------------------------------------------------------------------
