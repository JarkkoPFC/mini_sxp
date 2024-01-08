//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_MP_H
#define PFC_CORE_MP_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "sxp_src/core/functor.h"
#include PFC_STR(PFC_CAT2(sxp_src/platform/PFC_PLATFORM_SRC_STR/core/mp/PFC_PLATFORM_SRC_STR, _mp.h))  // expands to e.g. "sxp_src/platform/win/core/mp/win_mp.h"
namespace pfc
{

// new
// fundamental atomic operations
template<typename T> PFC_INLINE T atom_inc(volatile T &dst_);                     // ++dst_; returns dst_ after increment
template<typename T> PFC_INLINE T atom_dec(volatile T &dst_);                     // --dst_; returns dst_ after decrement
template<typename T> PFC_INLINE T atom_add(volatile T &dst_, T v_);               // dst_+=v_; returns dst_ before addition
template<typename T> PFC_INLINE T atom_sub(volatile T &dst_, T v_);               // dst_-=v_; returns dst_ before subtraction
template<typename T> PFC_INLINE T atom_mov(volatile T &dst_, T v_);               // dst_=v_; returns dst_ before mov
template<typename T> PFC_INLINE T atom_read(const volatile T&);                   // atomically read a memory location
template<typename T> PFC_INLINE void atom_write(volatile T &dst_, T v_);          // atomically write the value to the memory location
template<typename T> PFC_INLINE T atom_and(volatile T &dst_, T v_);               // dst_&=v_; returns dst_ before AND-op
template<typename T> PFC_INLINE T atom_or(volatile T &dst_, T v_);                // dst_|=v_; returns dst_ before OR-op
template<typename T> PFC_INLINE T atom_xor(volatile T &dst_, T v_);               // dst_^=v_; returns dst_ before XOR-op
template<typename T> PFC_INLINE T atom_cmov_eq(volatile T &dst_, T v_, T cmp_);   // dst_=dst_==cmp_?v_:dst_; returns dst_ before cmov
template<typename T> PFC_INLINE T atom_cmov_lt(volatile T &dst_, T v_, T cmp_);   // dst_=dst_<cmp_?v_:dst_; returns dst_ before cmov
template<typename T> PFC_INLINE T atom_cmov_gt(volatile T &dst_, T v_, T cmp_);   // dst_=dst_>cmp_?v_:dst_; returns dst_ before cmov
template<typename T> PFC_INLINE T atom_cmov_lte(volatile T &dst_, T v_, T cmp_);  // dst_=dst_<=cmp_?v_:dst_; returns dst_ before cmov
template<typename T> PFC_INLINE T atom_cmov_gte(volatile T &dst_, T v_, T cmp_);  // dst_=dst_>=cmp_?v_:dst_; returns dst_ before cmov
template<typename T> PFC_INLINE T atom_cmov_min(volatile T &dst_, T v_);          // dst_=dst_<v_?dst_:v_; returns dst_ before cmov
template<typename T> PFC_INLINE T atom_cmov_max(volatile T &dst_, T v_);          // dst_=dst_>v_?dst_:v_; returns dst_ before cmov
// basic lock-free constructs
template<typename T, T *(T::*next_mvar)> PFC_INLINE void atom_push_front(T*&, T&);
template<typename T> class mp_tptr;
// lock-free data structures
template<typename T, T *(T::*next_mvar)> class mp_fifo_queue;
template<typename T, T *(T::*next_mvar)> class mp_lifo_queue;
// thread & synchronization objects
class mp_thread;
class mp_event;
class mp_gate;
class mp_critical_section;
// synchronization functions
PFC_INLINE int wait_thread(mp_thread&);
PFC_INLINE void wait_event(mp_event&);
PFC_INLINE void wait_gate(mp_gate&);
// misc
void set_hardware_thread(unsigned hw_thread_idx_);
unsigned num_hardware_threads();
enum e_process_priority
{
  processpriority_idle=-3,
  processpriority_lower=-2,
  processpriority_low=-1,
  processpriority_normal=0,
  processpriority_high=1,
  processpriority_higher=2,
  processpriority_realtime=3,
};
void set_process_priority(e_process_priority);
//----------------------------------------------------------------------------


//============================================================================
// mp_tptr
//============================================================================
template<typename T>
class mp_tptr
{
public:
  // construction
  PFC_INLINE mp_tptr();
  PFC_INLINE mp_tptr(const mp_tptr&);
  PFC_INLINE mp_tptr(const volatile mp_tptr&);
  PFC_INLINE mp_tptr(T*);
  PFC_INLINE mp_tptr(T*, usize_t count_);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE T *operator->() const volatile;
  PFC_INLINE T &operator*() const volatile;
  PFC_INLINE T *ptr() const volatile;
  PFC_INLINE usize_t count() const volatile;
  PFC_INLINE void set(const mp_tptr&);
  PFC_INLINE void set(const volatile mp_tptr&);
  PFC_INLINE void set(const mp_tptr&) volatile;
  PFC_INLINE void set(const volatile mp_tptr&) volatile;
  PFC_INLINE void set(T*);
  PFC_INLINE void set(T*) volatile;
  PFC_INLINE void set(T*, usize_t count_);
  PFC_INLINE void set(T*, usize_t count_) volatile;
  //--------------------------------------------------------------------------

  // comparison
  PFC_INLINE bool operator==(const mp_tptr&) const;
  PFC_INLINE bool operator==(const volatile mp_tptr&) const;
  PFC_INLINE bool operator==(const mp_tptr&) const volatile;
  PFC_INLINE bool operator==(const volatile mp_tptr&) const volatile;
  PFC_INLINE bool operator!=(const mp_tptr&) const;
  PFC_INLINE bool operator!=(const volatile mp_tptr&) const;
  PFC_INLINE bool operator!=(const mp_tptr&) const volatile;
  PFC_INLINE bool operator!=(const volatile mp_tptr&) const volatile;
  //--------------------------------------------------------------------------

private:
  void operator=(const mp_tptr&); // not implemented
  PFC_INLINE mp_tptr(usize2_t);
  template<typename U> friend mp_tptr<U> atom_cmov_eq(volatile mp_tptr<U>&, const mp_tptr<U>&, const mp_tptr<U>&);
  //--------------------------------------------------------------------------

  //==========================================================================
  // mp_tptr::ptr_union
  //==========================================================================
  union ptr_union
  {
    // construction
    PFC_INLINE ptr_union() {}
    PFC_INLINE ptr_union(const ptr_union &p_) :data(p_.data) {}
    //------------------------------------------------------------------------

    struct ptr_data_struct
    {
      T *ptr;
      usize_t count;
    } ptr_data;
    usize2_t data;
  };
  //--------------------------------------------------------------------------

  ptr_union m_data;
};
//----------------------------------------------------------------------------


//============================================================================
// mp_fifo_queue
//============================================================================
template<typename T, T *(T::*next_mvar)=&T::next>
class mp_fifo_queue
{
public:
  // construction
  PFC_INLINE mp_fifo_queue();
  PFC_INLINE ~mp_fifo_queue();
  PFC_INLINE void force_clear();
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE T *head() const;
  PFC_INLINE void push(T&);
  PFC_INLINE bool secure_push(T&);
  T *pop();
  T *pop_if(const T*);
  //--------------------------------------------------------------------------

private:
  mp_fifo_queue(const mp_fifo_queue&); // not implemented
  void operator=(const mp_fifo_queue&); // not implemented
  //--------------------------------------------------------------------------

  //==========================================================================
  // mp_fifo_queue::ptr_union
  //==========================================================================
  union ptr_union
  {
    // construction
    PFC_INLINE ptr_union() {}
    PFC_INLINE ptr_union(const ptr_union &p_) :data(p_.data) {}
    //------------------------------------------------------------------------

    struct ptr_data_struct
    {
      T *volatile ptr;
      volatile usize_t count;
    } ptr_data;
    usize2_t data;
  };
  //--------------------------------------------------------------------------

  volatile ptr_union m_head;
  volatile ptr_union m_tail;
  T *m_dummy_next;
};
//----------------------------------------------------------------------------


//============================================================================
// mp_lifo_queue
//============================================================================
template<typename T, T *(T::*next_mvar)=&T::next>
class mp_lifo_queue
{
public:
  // construction
  PFC_INLINE mp_lifo_queue();
  PFC_INLINE ~mp_lifo_queue();
  PFC_INLINE void force_clear();
  //--------------------------------------------------------------------------

  // queue operations
  PFC_INLINE T *head() const;
  PFC_INLINE void push(T&);
  PFC_INLINE T *pop();
  PFC_INLINE T *pop_if(const T*);
  //--------------------------------------------------------------------------

private:
  mp_lifo_queue(const mp_lifo_queue&); // not implemented
  void operator=(const mp_lifo_queue&); // not implemented
  //--------------------------------------------------------------------------

  //==========================================================================
  // mp_lifo_queue::ptr_union
  //==========================================================================
  union ptr_union
  {
    // construction
    PFC_INLINE ptr_union() {}
    PFC_INLINE ptr_union(const ptr_union &p_) :data(p_.data) {}
    //------------------------------------------------------------------------

    struct ptr_data_struct
    {
      T *volatile ptr;
      volatile usize_t count;
    } ptr_data;
    usize2_t data;
  };
  //--------------------------------------------------------------------------

  volatile ptr_union m_head;
};
//----------------------------------------------------------------------------


//============================================================================
// e_thread_priority
//============================================================================
enum e_thread_priority
{
  threadpriority_idle=-3,
  threadpriority_lower=-2,
  threadpriority_low=-1,
  threadpriority_normal=0,
  threadpriority_high=1,
  threadpriority_higher=2,
  threadpriority_realtime=3,
};
//----------------------------------------------------------------------------


//============================================================================
// mp_thread
//============================================================================
class mp_thread
{
public:
  // construction
  mp_thread();
  mp_thread(const functor<int()>&, bool suspended_=false, int hw_thread_=-1, usize_t stack_size_=0);
  void init(const functor<int()>&, bool suspended_=false, int hw_thread_=-1, usize_t stack_size_=0);
  ~mp_thread();
  void start();
  void set_priority(e_thread_priority);
  //--------------------------------------------------------------------------

  // accessors
  bool is_terminated() const;
  //--------------------------------------------------------------------------

private:
  mp_thread(const mp_thread&); // not implemented
  void operator=(const mp_thread&); // not implemented
  static PFC_THREAD_PROC;
  friend int wait_thread(mp_thread&);
  //--------------------------------------------------------------------------

  mp_thread_handle_t m_handle;
  functor<int()> m_func;
};
//----------------------------------------------------------------------------


//============================================================================
// mp_event
//============================================================================
class mp_event
{
public:
  // construction
  mp_event();
  ~mp_event();
  //--------------------------------------------------------------------------

  // triggering
  PFC_INLINE void trigger();
  //--------------------------------------------------------------------------

private:
  mp_event(const mp_event&); // not implemented
  void operator=(const mp_event&); // not implemented
  friend void wait_event(mp_event&);
  //--------------------------------------------------------------------------

  mp_event_handle_t m_handle;
};
//----------------------------------------------------------------------------


//============================================================================
// mp_gate
//============================================================================
class mp_gate
{
public:
  // construction
  mp_gate();
  ~mp_gate();
  //--------------------------------------------------------------------------

  // state changing
  PFC_INLINE void open();
  PFC_INLINE void close();
  //--------------------------------------------------------------------------

private:
  mp_gate(const mp_gate&); // not implemented
  void operator=(const mp_gate&); // not implemented
  friend void wait_gate(mp_gate&);
  //--------------------------------------------------------------------------

  mp_gate_handle_t m_handle;
};
//----------------------------------------------------------------------------


//============================================================================
// mp_critical_section
//============================================================================
class mp_critical_section
{
public:
  // construction
  mp_critical_section();
  ~mp_critical_section();
  //--------------------------------------------------------------------------

  // management
  PFC_INLINE void enter();
  PFC_INLINE void leave();
  //--------------------------------------------------------------------------

private:
  mp_critical_section(const mp_critical_section&); // not implemented
  void operator=(const mp_critical_section&); // not implemented
  //--------------------------------------------------------------------------

  mp_critical_section_handle_t m_handle;
};
//----------------------------------------------------------------------------

//============================================================================
#include PFC_STR(PFC_CAT2(sxp_src/platform/PFC_PLATFORM_SRC_STR/core/mp/PFC_PLATFORM_SRC_STR, _mp.inl))  // expands to e.g. "sxp_src/platform/win/core/mp/win_mp.inl"
#include "mp.inl"
} // namespace pfc
#endif
