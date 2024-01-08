//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// align_type
//============================================================================
template<unsigned> struct align_type {PFC_STATIC_ERROR(int, given_alignment_doesnt_have_type);};
template<> struct align_type<0>  {typedef void res;};
template<> struct align_type<1>  {typedef align_type_1 res;};
template<> struct align_type<2>  {typedef align_type_2 res;};
template<> struct align_type<4>  {typedef align_type_4 res;};
template<> struct align_type<8>  {typedef align_type_8 res;};
template<> struct align_type<16> {typedef align_type_16 res;};
//----------------------------------------------------------------------------


//============================================================================
// alloc_site_info
//============================================================================
alloc_site_info::alloc_site_info(const char *filename_, const char *funcname_, unsigned line_)
  :filename(filename_)
  ,funcname(funcname_)
  ,line(line_)
{
}
//----

template<unsigned>
static PFC_INLINE const alloc_site_info &get_alloc_site_info(const char *filename_, const char *funcname_, unsigned line_)
{
  static const alloc_site_info s_site_info(filename_, funcname_, line_);
  return s_site_info;
}
//----------------------------------------------------------------------------


//============================================================================
// low-level memory management
//============================================================================
PFC_INLINE void *mem_alloc(usize_t num_bytes_, const alloc_site_info *site_info_)
{
#ifdef PFC_BUILDOP_MEMORY_TRACKING
  memory_info *info=(memory_info*)PFC_ALIGNED_MALLOC(num_bytes_+memory_info_size, memory_align);
  PFC_ASSERT_MSG(info, ("Memory allocation of %u bytes failed\r\n", num_bytes_+memory_info_size));
  info->site_info=site_info_;
  info->num_items=memory_flag_typeless|num_bytes_;
  extern void add_memory_info(memory_info&);
  add_memory_info(*info);
  return ((char*)info)+memory_info_size;
#else
  return PFC_ALIGNED_MALLOC(num_bytes_, memory_align);
#endif
}
//----

template<typename T>
PFC_INLINE T *mem_alloc(const alloc_site_info *site_info_)
{
#ifdef PFC_BUILDOP_MEMORY_TRACKING
  memory_info *info=(memory_info*)PFC_ALIGNED_MALLOC(sizeof(T)+memory_info_size, memory_align);
  PFC_ASSERT_MSG(info, ("Memory allocation of %u bytes failed\r\n", sizeof(T)+memory_info_size));
  info->num_items=usize_t(memory_flag_typeless)|sizeof(T);
  info->site_info=site_info_;
  extern void add_memory_info(memory_info&);
  add_memory_info(*info);
  return (T*)(((char*)info)+memory_info_size);
#else
  return (T*)PFC_ALIGNED_MALLOC(sizeof(T), memory_align);
#endif
}
//----

PFC_INLINE void mem_free(void *p_)
{
#ifdef PFC_BUILDOP_MEMORY_TRACKING
  if(p_)
  {
    memory_info *info=(memory_info*)(((char*)p_)-memory_info_size);
    extern void remove_memory_info(memory_info&);
    remove_memory_info(*info);
    PFC_ALIGNED_FREE(info);
  }
#else
  PFC_ALIGNED_FREE(p_);
#endif
}
//----

PFC_INLINE void mem_copy(void *dst_, const void *src_, usize_t num_bytes_)
{
  PFC_ASSERT_PEDANTIC(!num_bytes_ || (dst_ && src_));
  PFC_ASSERT_PEDANTIC_MSG(!num_bytes_ || dst_==src_ || (dst_<src_ && ((char*)dst_)+num_bytes_<=src_) || (dst_>src_ && ((char*)src_)+num_bytes_<=dst_),
                          ("Overlapping memory regions for mem_copy() result in undefined behavior\r\n"));
  ::memcpy(dst_, src_, (size_t)num_bytes_);
}
//----

PFC_INLINE void mem_move(void *dst_, const void *src_, usize_t num_bytes_)
{
  PFC_ASSERT_PEDANTIC(!num_bytes_ || (dst_ && src_));
  ::memmove(dst_, src_, (size_t)num_bytes_);
}
//----

PFC_INLINE void mem_zero(void *p_, usize_t num_bytes_)
{
  PFC_ASSERT_PEDANTIC(!num_bytes_ || p_);
  ::memset(p_, 0, (size_t)num_bytes_);
}
//----

PFC_INLINE void mem_set(void *p_, unsigned char c_, usize_t num_bytes_)
{
  PFC_ASSERT_PEDANTIC(!num_bytes_ || p_);
  ::memset(p_, c_, (size_t)num_bytes_);
}
//----

PFC_INLINE bool mem_eq(const void *p0_, const void *p1_, usize_t num_bytes_)
{
  PFC_ASSERT_PEDANTIC(!num_bytes_ || (p0_ && p1_));
  return ::memcmp(p0_, p1_, (size_t)num_bytes_)==0;
}
//----

PFC_INLINE bool is_mem_zero(void *p_, usize_t num_bytes_)
{
  PFC_ASSERT_PEDANTIC(!num_bytes_ || p_);
  const char *p=(const char*)p_;
  return *p==0 && ::memcmp(p, p+1, num_bytes_-1)==0;
}
//----

PFC_INLINE int mem_diff(const void *p0_, const void *p1_, usize_t num_bytes_)
{
  PFC_ASSERT_PEDANTIC(!num_bytes_ || (p0_ && p1_));
  return ::memcmp(p0_, p1_, (size_t)num_bytes_);
}
//----------------------------------------------------------------------------


//============================================================================
// memory tracking
//============================================================================
memory_stack_entry::memory_stack_entry(const char *func_)
{
  PFC_ASSERT_PEDANTIC(s_stack_depth<max_memory_stack_depth);
  s_stack[s_stack_depth++]=func_;
}
//----

memory_stack_entry::~memory_stack_entry()
{
  --s_stack_depth;
}
//----------------------------------------------------------------------------


//============================================================================
// memory_allocator_base
//============================================================================
memory_allocator_base::memory_allocator_base()
{
}
//----

memory_allocator_base::~memory_allocator_base()
{
}
//----------------------------------------------------------------------------


//============================================================================
// default_memory_allocator
//============================================================================
PFC_INLINE default_memory_allocator &default_memory_allocator::inst()
{
  static default_memory_allocator s_allocator;
  return s_allocator;
}
//----------------------------------------------------------------------------


//============================================================================
// pointer ops
//============================================================================
template<typename T> T *ptr(T *p_)
{
  return p_;
}
//----

template<typename T> bool is_valid(T *p_)
{
  return p_!=0;
}
//----------------------------------------------------------------------------


//============================================================================
// object construction and destruction
//============================================================================
template<typename T>
PFC_INLINE T *array_new(usize_t num_items_, const alloc_site_info *site_info_)
{
  // alloc memory and setup memory info
  memory_info *info=(memory_info*)PFC_ALIGNED_MALLOC(num_items_*sizeof(T)+memory_info_size, memory_align);
  info->num_items=num_items_;
#ifdef PFC_BUILDOP_MEMORY_TRACKING
  info->site_info=site_info_;
  extern void add_memory_info(memory_info&);
  add_memory_info(*info);
#endif

  // construct array
  T *p=(T*)(((char*)info)+memory_info_size);
  if(num_items_)
  {
    eh_array_dtor<T> v(p, p);
    T *end=p+num_items_;
    do
    {
      PFC_PNEW(v.dst)T;
    } while(++v.dst!=end);
    v.begin=0;
  }
  return p;
}
//----

template<typename T>
PFC_INLINE void array_delete(const T *p_)
{
  // read memory block info
  if(!p_)
    return;
  memory_info *info=(memory_info*)(((char*)p_)-memory_info_size);
  usize_t num_items=info->num_items;
  PFC_ASSERT_MSG((num_items&memory_flag_typeless)==0, ("Trying to release typeless data with array_delete()\r\n"));
#ifdef PFC_BUILDOP_MEMORY_TRACKING
  extern void remove_memory_info(memory_info&);
  remove_memory_info(*info);
#endif

  // destruct objects and free memory
  for(usize_t i=0; i<num_items; ++i)
  {
    p_->~T();
    ++p_;
  }
  PFC_ALIGNED_FREE(info);
}
//----

template<typename T>
PFC_INLINE usize_t array_size(const T *p_)
{
  // get number of items from memory block info
  if(!p_)
    return 0;
  const memory_info *info=(const memory_info*)(((char*)p_)-memory_info_size);
  return info->num_items&~memory_flag_typeless;
}
//----

template<typename T>
PFC_INLINE void *destruct(const T *p_)
{
  if(p_)
    p_->~T();
  return (void*)p_;
}
//----------------------------------------------------------------------------


//============================================================================
// type ID
//============================================================================
namespace priv
{
  template<typename T>
  PFC_INLINE unsigned new_type_id()
  {
    extern unsigned g_typeid;
    static unsigned s_type_typeid=++g_typeid;
    return s_type_typeid;
  }
} // namespace priv
//----

template<typename T> const unsigned type_id<T>::id=priv::new_type_id<const volatile T>();
//----

template<typename T>
struct ptr_id<T*>
{
  static PFC_INLINE unsigned id()
  {
    return type_id<T>::id;
  }
};
//----

template<typename T>
struct ref_id<T&>
{
  static PFC_INLINE unsigned id()
  {
    return type_id<T>::id;
  }
};
//----------------------------------------------------------------------------


//============================================================================
// class_reg_info
//============================================================================
template<class T> const char *class_reg_info<T>::reg_name=0;
template<class T> unsigned class_reg_info<T>::reg_count=0;
template<class T> const char *class_reg_info<T>::deprecated_name=0;
//----------------------------------------------------------------------------


//============================================================================
// class_reg_func_info
//============================================================================
template<class T> bool class_reg_func_info<T>::is_called=false;
//----------------------------------------------------------------------------


//============================================================================
// introspection
//============================================================================
template<class PE>
template<class T>
bool prop_enum_interface_base<PE>::subclass(T*)
{
  return true;
}
//----

template<class PE>
template<class T>
unsigned prop_enum_interface_base<PE>::set_custom_streaming(T&, unsigned version_)
{
  return version_;
}
//----

template<class PE>
int prop_enum_interface_base<PE>::stream()
{
  return 0;
}
//----

template<class PE>
template<typename T>
bool prop_enum_interface_base<PE>::var(const T&, unsigned flags_, const char *mvar_name_)
{
  return true;
}
//----

template<class PE>
template<typename T, class C>
bool prop_enum_interface_base<PE>::var(const T&, unsigned flags_, const char *mvar_name_, C&)
{
  return true;
}
//----

template<class PE>
template<typename T, class C>
bool prop_enum_interface_base<PE>::var(const T&, unsigned flags_, const char *mvar_name_, C&, void(*post_mutate_func_)(C*))
{
  return true;
}
//----

template<class PE>
template<typename T, class C>
bool prop_enum_interface_base<PE>::var(const T&, unsigned flags_, const char *mvar_name_, C&, void(C::*mutate_func_)(const T&, unsigned var_index_), unsigned var_index_)
{
  return true;
}
//----

template<class PE>
template<typename T>
bool prop_enum_interface_base<PE>::avar(const T*, usize_t size_, unsigned flags_, const char *mvar_name_)
{
  return true;
}
//----

template<class PE>
template<typename T, class C>
bool prop_enum_interface_base<PE>::avar(const T*, usize_t size_, unsigned flags_, const char *mvar_name_, C&)
{
  return true;
}
//----

template<class PE>
template<typename T, class C>
bool prop_enum_interface_base<PE>::avar(const T*, usize_t size_, unsigned flags_, const char *mvar_name_, C&, void(*post_mutate_func_)(C*))
{
  return true;
}
//----

template<class PE>
template<typename T, class C>
bool prop_enum_interface_base<PE>::avar(const T*, usize_t size_, unsigned flags_, const char *mvar_name_, C&, void(C::*mutate_func_)(const T&, unsigned index_, unsigned var_index_), unsigned var_index_)
{
  return true;
}
//----

template<class PE>
bool prop_enum_interface_base<PE>::data(const void*, usize_t num_bytes_)
{
  return true;
}
//----

template<class PE>
void prop_enum_interface_base<PE>::skip(usize_t num_bytes_)
{
  PFC_ERROR_NOT_IMPL();
}
//----

template<class PE>
template<typename T>
bool prop_enum_interface_base<PE>::alias_var(const T&, unsigned flags_, const char *alias_)
{
  return true;
}
//----

template<class PE>
template<typename T>
bool prop_enum_interface_base<PE>::alias_avar(const T*, usize_t size_, unsigned flags_, const char *alias_)
{
  return true;
}
//----------------------------------------------------------------------------

template<class PE>
void prop_enum_interface_base<PE>::group_begin(const char *group_name_)
{
}
//----

template<class PE>
void prop_enum_interface_base<PE>::group_end()
{
}
//----

template<class PE>
void prop_enum_interface_base<PE>::name(const char*)
{
}
//----

template<class PE>
void prop_enum_interface_base<PE>::desc(const char*)
{
}
//----

template<class PE>
void prop_enum_interface_base<PE>::color(uint32_t rgb_)
{
}
//----

template<class PE>
void prop_enum_interface_base<PE>::expanded()
{
}
//----

template<class PE>
template<typename T>
void prop_enum_interface_base<PE>::slider(const T &min_, const T &max_, const T &step_)
{
}
//----------------------------------------------------------------------------

template<class PE>
prop_enum_interface_base<PE>::prop_enum_interface_base()
{
}
//----

template<class PE>
prop_enum_interface_base<PE>::~prop_enum_interface_base()
{
}
//----------------------------------------------------------------------------


//============================================================================
// enum_props_lambda
//============================================================================
namespace priv
{
  //==========================================================================
  // prop_enum_lambda
  //==========================================================================
  template<class L>
  class prop_enum_lambda: public pfc::prop_enum_interface_base<prop_enum_lambda<L> >
  {
  public:
    // construction
    prop_enum_lambda(const L&);
    //--------------------------------------------------------------------------

    // streaming interface
    template<typename T> PFC_INLINE bool var(T&, unsigned flags_=0, const char *mvar_name_=0); // returns true if property enumeration should continue
    template<typename T, class C> PFC_INLINE bool var(T&, unsigned flags_, const char *mvar_name_, C&);
    template<typename T, class C> PFC_INLINE bool var(T&, unsigned flags_, const char *mvar_name_, C&, void(*post_mutate_func_)(C*));
    template<typename T, class C> PFC_INLINE bool var(T&, unsigned flags_, const char *mvar_name_, C&, void(C::*mutate_func_)(const T&, unsigned var_index_), unsigned var_index_);
    template<typename T> PFC_INLINE bool avar(T*, pfc::usize_t size_, unsigned flags_=0, const char *mvar_name_=0);
    template<typename T, class C> PFC_INLINE bool avar(T*, pfc::usize_t size_, unsigned flags_, const char *mvar_name_, C&);
    template<typename T, class C> PFC_INLINE bool avar(T*, pfc::usize_t size_, unsigned flags_, const char *mvar_name_, C&, void(*post_mutate_func_)(C*));
    template<typename T, class C> PFC_INLINE bool avar(T*, pfc::usize_t size_, unsigned flags_, const char *mvar_name_, C&, void(C::*mutate_func_)(const T&, unsigned index_, unsigned var_index_), unsigned var_index_);
    //--------------------------------------------------------------------------

  private:
    L m_lambda;
  };
  //----------------------------------------------------------------------------

  template<class L>
  prop_enum_lambda<L>::prop_enum_lambda(const L &lambda_)
    :m_lambda(lambda_)
  {
  }
  //----------------------------------------------------------------------------

  template<class L>
  template<typename T>
  bool prop_enum_lambda<L>::var(T &v_, unsigned flags_, const char *mvar_name_)
  {
    m_lambda(v_, 1, flags_, mvar_name_);
    return true;
  }
  //----

  template<class L>
  template<typename T, class C>
  bool prop_enum_lambda<L>::var(T &v_, unsigned flags_, const char *mvar_name_, C&)
  {
    m_lambda(v_, 1, flags_, mvar_name_);
    return true;
  }
  //----

  template<class L>
  template<typename T, class C>
  bool prop_enum_lambda<L>::var(T &v_, unsigned flags_, const char *mvar_name_, C&, void(*post_mutate_func_)(C*))
  {
    m_lambda(v_, 1, flags_, mvar_name_);
    return true;
  }
  //----

  template<class L>
  template<typename T, class C>
  bool prop_enum_lambda<L>::var(T &v_, unsigned flags_, const char *mvar_name_, C&, void(C::*)(const T&, unsigned var_index_), unsigned)
  {
    m_lambda(v_, 1, flags_, mvar_name_);
    return true;
  }
  //----

  template<class L>
  template<typename T>
  bool prop_enum_lambda<L>::avar(T *v_, pfc::usize_t size_, unsigned flags_, const char *mvar_name_)
  {
    m_lambda(v_, size_, flags_, mvar_name_);
    return true;
  }
  //----

  template<class L>
  template<typename T, class C>
  bool prop_enum_lambda<L>::avar(T *v_, pfc::usize_t size_, unsigned flags_, const char *mvar_name_, C&)
  {
    m_lambda(v_, size_, flags_, mvar_name_);
    return true;
  }
  //----

  template<class L>
  template<typename T, class C>
  bool prop_enum_lambda<L>::avar(T *v_, pfc::usize_t size_, unsigned flags_, const char *mvar_name_, C&, void(*)(C*))
  {
    m_lambda(v_, size_, flags_, mvar_name_);
    return true;
  }
  //----

  template<class L>
  template<typename T, class C>
  bool prop_enum_lambda<L>::avar(T *v_, pfc::usize_t size_, unsigned flags_, const char *mvar_name_, C&, void(C::*)(const T&, unsigned index_, unsigned var_index_), unsigned)
  {
    m_lambda(v_, size_, flags_, mvar_name_);
    return true;
  }
  //----------------------------------------------------------------------------

  template<class T, class L>
  void enum_props_lambda(T &v_, const L &lambda_)
  {
    prop_enum_lambda<L> pe(lambda_);
    enum_props(pe, v_);
  }
} // namespace priv
//----------------------------------------------------------------------------

template<class T, class L>
void enum_props_lambda(T &v_, const L &lambda_)
{
  priv::prop_enum_lambda<L> pe(lambda_);
  enum_props(pe, v_);
}
//----------------------------------------------------------------------------


//============================================================================
// uint128_t operations
//============================================================================
PFC_INLINE bool operator==(const uint128_t &v0_, const uint128_t &v1_)
{
  return v0_.lo==v1_.lo && v0_.hi==v1_.hi;
}
//----

PFC_INLINE bool operator==(const volatile uint128_t &v0_, const uint128_t &v1_)
{
  return v0_.lo==v1_.lo && v0_.hi==v1_.hi;
}
//----

PFC_INLINE bool operator==(const uint128_t &v0_, const volatile uint128_t &v1_)
{
  return v0_.lo==v1_.lo && v0_.hi==v1_.hi;
}
//----

PFC_INLINE bool operator==(const volatile uint128_t &v0_, const volatile uint128_t &v1_)
{
  return v0_.lo==v1_.lo && v0_.hi==v1_.hi;
}
//----

PFC_INLINE bool operator!=(const uint128_t &v0_, const uint128_t &v1_)
{
  return v0_.lo!=v1_.lo || v0_.hi!=v1_.hi;
}
//----

PFC_INLINE bool operator!=(const volatile uint128_t &v0_, const uint128_t &v1_)
{
  return v0_.lo!=v1_.lo || v0_.hi!=v1_.hi;
}
//----

PFC_INLINE bool operator!=(const uint128_t &v0_, const volatile uint128_t &v1_)
{
  return v0_.lo!=v1_.lo || v0_.hi!=v1_.hi;
}
//----

PFC_INLINE bool operator!=(const volatile uint128_t &v0_, const volatile uint128_t &v1_)
{
  return v0_.lo!=v1_.lo || v0_.hi!=v1_.hi;
}
//----------------------------------------------------------------------------


//============================================================================
// incomplete type forwarding
//============================================================================
// type traits
template<typename T> struct is_type_fwd_clone {enum {res=false};};
template<typename T> struct is_type_fwd_delete {enum {res=false};};
template<typename T> struct is_type_fwd_introspec {enum {res=false};};
// pointer traits
template<typename T> struct is_ptr_fwd_clone {enum {res=false};};
template<typename T> struct is_ptr_fwd_clone<T*> {enum {res=is_type_fwd_clone<T>::res};};
template<typename T> struct is_ptr_fwd_delete {enum {res=false};};
template<typename T> struct is_ptr_fwd_delete<T*> {enum {res=is_type_fwd_delete<T>::res};};
template<typename T> struct is_ptr_fwd_introspec {enum {res=false};};
template<typename T> struct is_ptr_fwd_introspec<T*> {enum {res=is_type_fwd_introspec<T>::res};};
// reference traits
template<typename T> struct is_ref_fwd_clone {enum {res=false};};
template<typename T> struct is_ref_fwd_clone<T&> {enum {res=is_type_fwd_clone<T>::res};};
template<typename T> struct is_ref_fwd_delete {enum {res=false};};
template<typename T> struct is_ref_fwd_delete<T&> {enum {res=is_type_fwd_delete<T>::res};};
template<typename T> struct is_ref_fwd_introspec {enum {res=false};};
template<typename T> struct is_ref_fwd_introspec<T&> {enum {res=is_type_fwd_introspec<T>::res};};
//----------------------------------------------------------------------------

// clone forwarding
template<typename T>
struct fwd_type_func_clone
{
  static owner_ref<T>(*s_func)(const T&);
};
template<typename T> owner_ref<T>(*fwd_type_func_clone<T>::s_func)(const T&)=0;
//----

template<typename T> void register_fwd_clone()
{
  PFC_STATIC_ASSERT_MSG(is_type_fwd_clone<T>::res, type_not_declared_as_forward_clonable);
  struct func_type
  {
    static owner_ref<T> func(const T &v_)
    {
      return v_.clone();
    }
  };
  fwd_type_func_clone<T>::s_func=&func_type::func;
}
//----

template<typename T> owner_ref<T> fwd_clone(const T &v_)
{
  PFC_STATIC_ASSERT_MSG(is_type_fwd_clone<T>::res, type_not_declared_as_forward_clonable);
  PFC_ASSERT_MSG((fwd_type_func_clone<T>::s_func), ("Forward cloning not registered for the type\r\n"));
  return (*fwd_type_func_clone<T>::s_func)(v_);
}
//----------------------------------------------------------------------------

// delete forwarding
template<typename T>
struct fwd_type_func_delete
{
  static void(*s_func)(T*);
};
template<typename T> void(*fwd_type_func_delete<T>::s_func)(T*)=0;
//----

template<typename T> void register_fwd_delete()
{
  PFC_STATIC_ASSERT_MSG(is_type_fwd_delete<T>::res, type_not_declared_as_forward_deletable);
  struct func_type
  {
    static void func(T *p_)
    {
      PFC_DELETE(p_);
    }
  };
  fwd_type_func_delete<T>::s_func=&func_type::func;
}
//----

template<typename T> PFC_INLINE void fwd_delete(T *p_)
{
  PFC_STATIC_ASSERT_MSG(is_type_fwd_delete<T>::res, type_not_declared_as_forward_deletable);
  if(p_)
  {
    PFC_ASSERT_MSG((fwd_type_func_delete<T>::s_func), ("Forward delete not registered for the type\r\n"));
    (*fwd_type_func_delete<T>::s_func)(p_);
  }
}
//----------------------------------------------------------------------------

// type introspection forwarding
template<class PE, typename T>
struct fwd_type_func_introspec
{
  static void(*s_func)(PE&, T&, unsigned, const char*);
};
template<class PE, class T> void(*fwd_type_func_introspec<PE, T>::s_func)(PE&, T&, unsigned, const char*)=0;
//----

template<class PE, class T> void register_fwd_introspec()
{
  PFC_STATIC_ASSERT_MSG(is_type_fwd_introspec<T>::res, type_not_declared_as_forward_introspectable);
  struct func_type
  {
    static void func(PE &pe_, T &v_, unsigned flags_, const char *mvar_name_)
    {
      pe_.var(v_, flags_, mvar_name_);
    }
  };
  fwd_type_func_introspec<PE, T>::s_func=&func_type::func;
}
//----

template<class PE, class T> PFC_INLINE void fwd_introspec(PE &pe_, T *v_, unsigned flags_, const char *mvar_name_)
{
  PFC_STATIC_ASSERT_MSG(is_type_fwd_introspec<T>::res, type_not_declared_as_forward_introspectable);
  PFC_ASSERT_MSG(!v_ || (fwd_type_func_introspec<PE, T>::s_func), ("Forward introspection not defined for the enumerator and type\r\n"));
  if(fwd_type_func_introspec<PE, T>::s_func)
    (*fwd_type_func_introspec<PE, T>::s_func)(pe_, *v_, flags_, mvar_name_);
}
//----------------------------------------------------------------------------


//============================================================================
// event system
//============================================================================
template<class EH, typename E>
PFC_INLINE void send_event(EH &v_, E &e_)
{
  v_.dispatch_event(pfc::type_id<E>::id, &e_);
}
//----------------------------------------------------------------------------


//============================================================================
// owner_ptr
//============================================================================
namespace priv
{
  template<bool is_fwd_delete>
  struct delete_helper
  {
    template<typename T> static PFC_INLINE void delete_ptr(T *p_)
    {
      PFC_FWD_DELETE(p_);
    }
  };

  template<>
  struct delete_helper<false>
  {
    template<typename T> static PFC_INLINE void delete_ptr(T *p_)
    {
      PFC_DELETE(p_);
    }
  };
}
//----------------------------------------------------------------------------

template<typename T>
owner_ptr<T>::owner_ptr()
  :data(0)
{
}
//----

template<typename T>
owner_ptr<T>::owner_ptr(T *p_)
  :data(p_)
{
}
//----

template<typename T>
owner_ptr<T>::owner_ptr(const owner_ptr &ptr_)
  :data(ptr_.data)
{
  ptr_.data=0;
}
//----

template<typename T>
template<typename U>
owner_ptr<T>::owner_ptr(const owner_ptr<U> &ptr_)
  :data(ptr_.data)
{
  ptr_.data=0;
}
//----

template<typename T>
template<typename U>
owner_ptr<T>::owner_ptr(const owner_ref<U> &ref_)
  :data(ref_.data)
{
  PFC_ASSERT_PEDANTIC(ref_.data);
  ref_.data=0;
}
//----

template<typename T>
void owner_ptr<T>::operator=(T *p_)
{
  if(data!=p_)
  {
    priv::delete_helper<is_type_fwd_delete<T>::res>::delete_ptr(data);
    data=p_;
  }
}
//----

template<typename T>
void owner_ptr<T>::operator=(const owner_ptr &ptr_)
{
  if(this!=&ptr_)
  {
    priv::delete_helper<is_type_fwd_delete<T>::res>::delete_ptr(data);
    data=ptr_.data;
    ptr_.data=0;
  }
}
//----

template<typename T>
template<typename U>
void owner_ptr<T>::operator=(const owner_ptr<U> &ptr_)
{
  priv::delete_helper<is_type_fwd_delete<T>::res>::delete_ptr(data);
  data=ptr_.data;
  ptr_.data=0;
}
//----

template<typename T>
template<typename U>
void owner_ptr<T>::operator=(const owner_ref<U> &ref_)
{
  PFC_ASSERT_PEDANTIC(ref_.data);
  priv::delete_helper<is_type_fwd_delete<T>::res>::delete_ptr(data);
  data=ref_.data;
  ref_.data=0;
}
//----

template<typename T>
owner_ptr<T>::~owner_ptr()
{
  priv::delete_helper<is_type_fwd_delete<T>::res>::delete_ptr(data);
}
//----------------------------------------------------------------------------

template<typename T>
T *owner_ptr<T>::operator->() const
{
  PFC_ASSERT_PEDANTIC_MSG(data, ("Dereferencing \"%s\" NULL pointer\r\n", typeid(T).name()));
  return data;
}
//----

template<typename T>
T &owner_ptr<T>::operator*() const
{
  PFC_ASSERT_PEDANTIC_MSG(data, ("Dereferencing \"%s\" NULL pointer\r\n", typeid(T).name()));
  return *data;
}
//----------------------------------------------------------------------------


//============================================================================
// owner_ref
//============================================================================
template<typename T>
owner_ref<T>::owner_ref(T *p_)
  :data(p_)
{
  PFC_ASSERT_PEDANTIC(p_);
}
//----

template<typename T>
owner_ref<T>::owner_ref(const owner_ref &ref_)
  :data(ref_.data)
{
  PFC_ASSERT_PEDANTIC(ref_.data);
  ref_.data=0;
}
//----

template<typename T>
template<typename U>
owner_ref<T>::owner_ref(const owner_ref<U> &ref_)
  :data(ref_.data)
{
  PFC_ASSERT_PEDANTIC(ref_.data);
  ref_.data=0;
}
//----

template<typename T>
template<typename U>
owner_ref<T>::owner_ref(const owner_ptr<U> &ptr_)
  :data(ptr_.data)
{
  PFC_ASSERT_PEDANTIC(ptr_.data);
  ptr_.data=0;
}
//----

template<typename T>
owner_ref<T>::~owner_ref()
{
  priv::delete_helper<is_type_fwd_delete<T>::res>::delete_ptr(data);
}
//----------------------------------------------------------------------------

template<typename T>
T *owner_ref<T>::operator->() const
{
  PFC_ASSERT_PEDANTIC_MSG(data, ("Dereferencing \"%s\" NULL pointer\r\n", typeid(T).name()));
  return data;
}
//----

template<typename T>
T &owner_ref<T>::operator*() const
{
  PFC_ASSERT_PEDANTIC_MSG(data, ("Dereferencing \"%s\" NULL pointer\r\n", typeid(T).name()));
  return *data;
}
//----------------------------------------------------------------------------


//============================================================================
// owner_data
//============================================================================
owner_data::owner_data()
{
  data=0;
}
//----

owner_data::owner_data(void *p_)
{
  data=p_;
}
//----

owner_data::owner_data(const owner_data &ptr_)
{
  data=ptr_.data;
  ptr_.data=0;
}
//----

void owner_data::operator=(void *p_)
{
  if(data!=p_)
  {
    PFC_MEM_FREE(data);
    data=p_;
  }
}
//----

void owner_data::operator=(const owner_data &ptr_)
{
  if(this!=&ptr_)
  {
    PFC_MEM_FREE(data);
    data=ptr_.data;
    ptr_.data=0;
  }
}
//----

owner_data::~owner_data()
{
  PFC_MEM_FREE(data);
}
//----------------------------------------------------------------------------


//============================================================================
// raw_cast
//============================================================================
template<typename T, typename U>
PFC_INLINE T raw_cast(U v_)
{
  PFC_STATIC_ASSERT_MSG(sizeof(T)==sizeof(U), source_and_destination_types_must_have_equal_size);
  return reinterpret_cast<const T&>(v_);
}
//----------------------------------------------------------------------------


//============================================================================
// safe_cast
//============================================================================
#ifdef PFC_BUILDOP_SAFE_CASTS
} // namespace pfc
namespace pfc
{
#endif
//----

namespace priv
{
  template<class T> struct safe_cast_hlp;
  template<class T>
  struct safe_cast_hlp<T&>
  {
    typedef T res;
  };
  template<class T>
  struct safe_cast_hlp<T*>
  {
    typedef T res;
  };
} // namespace priv
//----

template<class T, class U>
PFC_INLINE T safe_cast(U &v_)
{
#ifdef PFC_BUILDOP_SAFE_CASTS
  typedef typename priv::safe_cast_hlp<T>::res ptr_type;
  PFC_ASSERT_PEDANTIC_MSG(dynamic_cast<ptr_type*>(&v_), ("Downcasting reference to a wrong type (%s& -> %s&)\r\n", typeid(U).name(), typeid(T).name()));
#endif
  return static_cast<T>(v_);
}
//----

template<class T, class U>
PFC_INLINE T safe_cast(U *v_)
{
#ifdef PFC_BUILDOP_SAFE_CASTS
  PFC_ASSERT_PEDANTIC_MSG(v_==0 || dynamic_cast<T>(v_), ("Downcasting pointer to a wrong type (%s* -> %s*)\r\n", typeid(U).name(), typeid(typename priv::safe_cast_hlp<T>::res).name()));
#endif
  return static_cast<T>(v_);
}
//----

#if defined(__cplusplus_winrt) || defined(__cplusplus_cli)
template<class T, class U>
PFC_INLINE T safe_cast(U ^v_)
{
#ifdef PFC_BUILDOP_SAFE_CASTS
  PFC_ASSERT_PEDANTIC_MSG(v_==nullptr || dynamic_cast<T>(v_), ("Downcasting pointer to a wrong type (%s^ -> %s)\r\n", typeid(U).name(), typeid(T).name()));
#endif
  return static_cast<T>(v_);
}
#endif
//----

template<class T, class U>
inline T safe_cast(const owner_ptr<U> &v_)
{
  typedef typename T::type type;
#ifdef PFC_BUILDOP_SAFE_CASTS
  PFC_ASSERT_PEDANTIC_MSG(v_.data==0 || dynamic_cast<type*>(v_.data), ("Downcasting pointer to a wrong type (%s -> %s)\r\n", typeid(owner_ptr<U>).name(), typeid(T).name()));
#endif
  type *p=static_cast<type*>(v_.data);
  v_.data=0;
  return p;
}
//----

template<class T, class U>
inline T safe_cast(const owner_ref<U> &v_)
{
  PFC_ASSERT_PEDANTIC(v_.data);
  typedef typename T::type type;
#ifdef PFC_BUILDOP_SAFE_CASTS
  PFC_ASSERT_PEDANTIC_MSG(v_.data==0 || dynamic_cast<type*>(v_.data), ("Downcasting pointer to a wrong type (%s -> %s)\r\n", typeid(owner_ref<U>).name(), typeid(T).name()));
#endif
  type *p=static_cast<type*>(v_.data);
  v_.data=0;
  return p;
}
//----------------------------------------------------------------------------


//============================================================================
// down_cast
//============================================================================
template<class T, class U>
PFC_INLINE T down_cast(U *v_)
{
  if(v_)
  {
    // check type for given type id
    unsigned subids[max_subclasses];
    unsigned num_subids=v_->subobject_type_ids(subids);
    unsigned id=ptr_id<T>::id();
    for(unsigned i=0; i<num_subids; ++i)
      if(subids[i]==id)
        return static_cast<T>(v_);
  }
  return 0;
}
//----

template<class T, class U>
PFC_INLINE T down_cast(const owner_ptr<U> &v_)
{
  if(v_.data)
  {
    // check type for given type id
    unsigned subids[max_subclasses];
    unsigned num_subids=v_.data->subobject_type_ids(subids);
    for(unsigned i=0; i<num_subids; ++i)
      if(subids[i]==type_id<typename T::type>::id)
      {
        typename T::type *p=static_cast<typename T::type>(v_.data);
        v_.data=0;
        return p;
      }
  }
  return 0;
}
//----

template<class T, class U>
PFC_INLINE T down_cast(const owner_ref<U> &v_)
{
  // check type for given type id
  PFC_ASSERT_PEDANTIC(v_.data);
  unsigned subids[max_subclasses];
  unsigned num_subids=v_.data->subobject_type_ids(subids);
  for(unsigned i=0; i<num_subids; ++i)
    if(subids[i]==type_id<typename T::type>::id)
    {
      typename T::type *p=static_cast<typename T::type>(v_.data);
      v_.data=0;
      return p;
    }
  return 0;
}
//----------------------------------------------------------------------------


//============================================================================
// down_cast_check
//============================================================================
template<class T, class U>
PFC_INLINE bool down_cast_check(U *v_)
{
  if(v_)
  {
    // check type for given type id
    unsigned subids[max_subclasses];
    unsigned num_subids=v_->subobject_type_ids(subids);
    unsigned id=ptr_id<T>::id();
    for(unsigned i=0; i<num_subids; ++i)
      if(subids[i]==id)
        return true;
  }
  return false;
}
//----------------------------------------------------------------------------


//============================================================================
// find_cast
//============================================================================
template<class T>
int find_cast(T &v_, const unsigned *type_ids_, unsigned num_type_ids_)
{
  // check first type id and get number of ids to test
  unsigned subids[max_subclasses];
  unsigned num_subids=v_.subobject_type_ids(subids);
  unsigned i;
  for(i=0; i<num_subids&&subids[i]!=type_id<T>::id; ++i)
    if(subids[i]==*type_ids_)
      return 0;
  num_subids=i;

  // check remaining type ids
  for(unsigned j=1; j<num_type_ids_; ++j)
    for(unsigned i=0; i<num_subids; ++i)
      if(subids[i]==type_ids_[j])
        return j;
  return -1;
}
//----------------------------------------------------------------------------


//============================================================================
// min/max
//============================================================================
template<typename T>
PFC_INLINE T min(T v0_, T v1_)
{
  // return minimum of the two
  return v0_<v1_?v0_:v1_;
}
//----

template<typename T>
PFC_INLINE T min(T v0_, T v1_, T v2_)
{
  // return minimum of the three
  T v=v0_<v1_?v0_:v1_;
  return v<v2_?v:v2_;
}
//----

template<typename T>
PFC_INLINE T min(T v0_, T v1_, T v2_, T v3_)
{
  // return minimum of the four
  T v=v0_<v1_?v0_:v1_;
  v=v<v2_?v:v2_;
  return v<v3_?v:v3_;
}
//----

template<typename T>
PFC_INLINE T max(T v0_, T v1_)
{
  // return maximum of the two
  return v1_<v0_?v0_:v1_;
}
//----

template<typename T>
PFC_INLINE T max(T v0_, T v1_, T v2_)
{
  // return maximum of the three
  T v=v1_<v0_?v0_:v1_;
  return v2_<v?v:v2_;
}
//----

template<typename T>
PFC_INLINE T max(T v0_, T v1_, T v2_, T v3_)
{
  // return maximum of the four
  T v=v1_<v0_?v0_:v1_;
  v=v2_<v?v:v2_;
  return v3_<v?v:v3_;
}
//----

template<typename T>
PFC_INLINE minmax_res<T> minmax(T v0_, T v1_)
{
  minmax_res<T> res;
  if(v0_<v1_)
  {
    res.min=v0_;
    res.max=v1_;
  }
  else
  {
    res.min=v1_;
    res.max=v0_;
  }
  return res;
}
//----

template<typename T>
PFC_INLINE minmax_res<T> minmax(T v0_, T v1_, T v2_)
{
  minmax_res<T> res;
  if(v0_<v1_)
  {
    res.min=v0_;
    res.max=v1_;
  }
  else
  {
    res.min=v1_;
    res.max=v0_;
  }
  if(v2_<res.min)
    res.min=v2_;
  else
    if(res.max<v2_)
      res.max=v2_;
  return res;
}
//----

template<typename T>
PFC_INLINE minmax_res<T> minmax(T v0_, T v1_, T v2_, T v3_)
{
  minmax_res<T> res;
  if(v0_<v1_)
  {
    res.min=v0_;
    res.max=v1_;
  }
  else
  {
    res.min=v1_;
    res.max=v0_;
  }
  if(v2_<res.min)
    res.min=v2_;
  else
    if(res.max<v2_)
      res.max=v2_;
  if(v3_<res.min)
    res.min=v3_;
  else
    if(res.max<v3_)
      res.max=v3_;
  return res;
}
//----------------------------------------------------------------------------


//============================================================================
// eh_data
//============================================================================
template<typename T>
eh_data<T>::eh_data(memory_allocator_base &alloc_, usize_t size_, usize_t align_)
#ifdef PFC_BUILDOP_EXCEPTIONS
  :m_allocator(alloc_)
#endif
{
  data=size_?(T*)alloc_.alloc(sizeof(T)*size_, align_):0;
}
//----

template<typename T>
eh_data<T>::~eh_data()
{
#ifdef PFC_BUILDOP_EXCEPTIONS
  m_allocator.free(data);
#endif
}
//----

template<typename T>
void eh_data<T>::reset()
{
#ifdef PFC_BUILDOP_EXCEPTIONS
  data=0;
#endif
}
//----------------------------------------------------------------------------


//============================================================================
// eh_dtor
//============================================================================
template<typename T>
eh_dtor::eh_dtor(T &dtor_, void(T::*method_)())
{
#ifdef PFC_BUILDOP_EXCEPTIONS
  m_dtor=(eh_dtor*)&dtor_;
  m_method=(void(eh_dtor::*)())method_;
#endif
}
//----

eh_dtor::~eh_dtor()
{
#ifdef PFC_BUILDOP_EXCEPTIONS
  if(m_dtor)
    (m_dtor->*m_method)();
#endif
}
//----

void eh_dtor::reset()
{
#ifdef PFC_BUILDOP_EXCEPTIONS
  m_dtor=0;
#endif
}
//----------------------------------------------------------------------------


//============================================================================
// eh_array_dtor
//============================================================================
template<typename T>
eh_array_dtor<T>::eh_array_dtor()
{
  begin=0;
  dst=0;
}
//----

template<typename T>
eh_array_dtor<T>::eh_array_dtor(T *begin_, T *dst_)
{
  begin=begin_;
  dst=dst_;
}
//----

template<typename T>
eh_array_dtor<T>::~eh_array_dtor()
{
#ifdef PFC_BUILDOP_EXCEPTIONS
  if(begin)
  {
    if(dst>begin)
      while(dst--!=begin)
        dst->~T();
    else
      while(dst++!=begin)
        dst->~T();
  }
#endif
}
//----------------------------------------------------------------------------


//============================================================================
// raw_data
//============================================================================
PFC_INTROSPEC_INL_DEF(raw_data)
{ PFC_CUSTOM_STREAMING(0);
  switch(unsigned(PE::pe_type))
  {
    // read raw data
    case penum_input:
    {
      uint32_t s;
      pe_.var(s);
      size=s;
      PFC_MEM_FREE(data);
      data=size?PFC_MEM_ALLOC(size):0;
      pe_.data(data, size);
    } break;

    // write/display raw data
    case penum_output:
    case penum_display:
    {
      uint32_t s=(uint32_t)size;
      pe_.var(s, 0, "size");
      pe_.data(data, size);
    } break;
  }
}
//----------------------------------------------------------------------------

raw_data::raw_data()
{
  size=0;
  data=0;
}
//----

raw_data::raw_data(usize_t bytes_)
{
  size=bytes_;
  data=PFC_MEM_ALLOC(bytes_);
}
//----

raw_data::~raw_data()
{
  PFC_MEM_FREE(data);
}
//----

void raw_data::alloc(usize_t num_bytes_)
{
  if(size!=num_bytes_)
  {
    free();
    size=num_bytes_;
    data=size?PFC_MEM_ALLOC(size):0;
  }
}
//----

void raw_data::free()
{
  PFC_MEM_FREE(data);
  data=0;
  size=0;
}
//----

void raw_data::swap(raw_data &data_)
{
  // swap raw data contents
  usize_t temp_size=size;
  void *temp_data=data;
  size=data_.size;
  data=data_.data;
  data_.size=temp_size;
  data_.data=temp_data;
}
//----------------------------------------------------------------------------


//============================================================================
// definit_var
//============================================================================
template<typename T>
definit_var<T>::definit_var()
  :value(T())
{
}
//----------------------------------------------------------------------------


//============================================================================
// uninit_var
//============================================================================
namespace priv
{
  template<typename T, typename U> struct uninit_var_hlp {enum {res=false};};
  template<typename T> struct uninit_var_hlp<T, T> {enum {res=true};};
}
//----------------------------------------------------------------------------

template<class T>
uninit_var<T>::uninit_var()
  :m_is_initialized(false)
{
}
//----

template<class T>
uninit_var<T>::~uninit_var()
{
  if(m_is_initialized)
    ((T*)m_data)->~T();
}
//----

template<class T>
template<class U>
void *uninit_var<T>::new_data()
{
  PFC_STATIC_ASSERT_MSG((priv::uninit_var_hlp<T, U>::res), trying_to_initialize_incorrect_type);
  PFC_ASSERT_PEDANTIC(!m_is_initialized);
  m_is_initialized=true;
  return m_data;
}
//----------------------------------------------------------------------------

template<class T>
bool uninit_var<T>::is_initialized() const
{
  return m_is_initialized;
}
//----

template<class T>
uninit_var<T>::operator T&()
{
  PFC_ASSERT_PEDANTIC(m_is_initialized);
  return *(T*)m_data;
}
//----

template<class T>
T &uninit_var<T>::ref()
{
  PFC_ASSERT_PEDANTIC(m_is_initialized);
  return *(T*)m_data;
}
//----

template<class T>
uninit_var<T>::operator const T&() const
{
  PFC_ASSERT_PEDANTIC(m_is_initialized);
  return *(const T*)m_data;
}
//----

template<class T>
const T &uninit_var<T>::ref() const
{
  PFC_ASSERT_PEDANTIC(m_is_initialized);
  return *(const T*)m_data;
}
//----------------------------------------------------------------------------


//============================================================================
// enumerated value string
//============================================================================
template<typename T>
PFC_INLINE const char *enum_string(T eval_)
{
  return enum_strings(eval_)[enum_string_index(eval_)];
}
//----

template<typename T>
PFC_INLINE const char *enum_display_string(T eval_)
{
  return enum_display_strings(eval_)[enum_string_index(eval_)];
}
//----

template<typename T>
PFC_INLINE bool enum_value(T &v_, const char *enum_str_)
{
  extern int str_find_substr(const char*, const char*const*);
  unsigned eidx=str_find_substr(enum_str_, enum_strings(v_)+1)+1;
  if(!eidx)
  {
    if(enum_dep_value(v_, enum_str_))
      return true;
    PFC_WARNF("No value found for enum %s = %s\r\n", enum_type_name(v_), enum_str_);
    return false;
  }
  const T *evals=enum_values(v_);
  v_=evals?evals[eidx]:T(eidx-1);
  return true;
}
//----------------------------------------------------------------------------


//============================================================================
// perf_timer
//============================================================================
void perf_timer::start()
{
  // start the timer
  if(s_enable_timers<1)
    return;
  if(!priv_is_initialized)
    init();
  priv_start_cycles=get_thread_cycles();
}
//----

void perf_timer::pause()
{
  // stop the timer
  if(s_enable_timers<1)
    return;
  uint64_t t=get_thread_cycles();
  num_cycles+=t-priv_start_cycles;
  priv_start_cycles=0;
}
//----

void perf_timer::stop()
{
  // stop the timer
  if(s_enable_timers<1)
    return;
  uint64_t t=get_thread_cycles();
  num_cycles+=t-priv_start_cycles;
  priv_start_cycles=0;
  ++priv_frame_peak_count;
}
//----------------------------------------------------------------------------


//============================================================================
// perf_timer::toggle
//============================================================================
perf_timer::toggle::toggle(perf_timer &t_)
  :m_timer(t_)
{
  m_timer.start();
}
//----

perf_timer::toggle::~toggle()
{
  m_timer.stop();
}
//----------------------------------------------------------------------------
