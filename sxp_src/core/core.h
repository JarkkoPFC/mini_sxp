//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_H
#define PFC_CORE_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "config.h"
#include <new>
#include <typeinfo>
#include <string.h>
#include <stdint.h>
#include PFC_STR(PFC_CAT3(sxp_src/platform/PFC_PLATFORM_SRC_STR/core/PFC_PLATFORM_SRC_STR, _core__, PFC_COMPILER_SRC_STR.h))  // expands to e.g. "sxp_src/platform/win/core/win_core__msvc.h"
namespace pfc
{

// new
// sized types
typedef uint16_t float16_t;
typedef uint16_t ufloat16_t;
typedef float float32_t;
typedef float ufloat32_t;
typedef double float64_t;
typedef double ufloat64_t;
#if PFC_BIG_ENDIAN==0
struct uint128_t {PFC_ALIGN(16) uint64_t lo; uint64_t hi;};
#else
struct uint128_t {PFC_ALIGN(16) uint64_t hi; uint64_t lo;};
#endif
// ranged types
typedef float ufloat_t;     // [0, +inf]
typedef float float1_t;     // [-1, 1]
typedef float ufloat1_t;    // [0, 1]
typedef double udouble_t;   // [0, +inf]
typedef double double1_t;   // [-1, 1]
typedef double udouble1_t;  // [0, 1]
// aligned types
struct align_type_1  {PFC_ALIGN(1) int8_t dummy;};
struct align_type_2  {PFC_ALIGN(2) int16_t dummy;};
struct align_type_4  {PFC_ALIGN(4) int32_t dummy;};
struct align_type_8  {PFC_ALIGN(8) int64_t dummy;};
struct align_type_16 {PFC_ALIGN(16) int64_t dummy[2];};
template<unsigned> struct align_type;
// pointer related types
enum {ptr_size=sizeof(void*)};
#ifdef PFC_PLATFORM_32BIT
typedef uint32_t usize_t;
typedef int32_t ssize_t;
typedef uint64_t usize2_t;
#define PFC_PTR_SIZE 4
#elif defined(PFC_PLATFORM_64BIT)
typedef uint64_t usize_t;
typedef int64_t ssize_t;
typedef uint128_t usize2_t;
#define PFC_PTR_SIZE 8
#endif
// class hierarchy config
enum {max_subclasses=16};
// registration
void register_classes_core(bool);
// logging
bool enable_logging(bool enable_);
void log(const char*);
void logf(const char*, ...);
void log_indention();
void warn(const char*);
void warnf(const char*, ...);
void warn_indention();
void error(const char*);
void errorf(const char*, ...);
void error_indention();
void set_logging_funcs(void(*logf_)(const char*, usize_t), void(*warnf_)(const char*, usize_t), void(*errorf_)(const char*, usize_t));
void default_logging_func(const char*, usize_t);
void indent_log();
void unindent_log();
// aborting
bool preabort();
void set_preabort_func(bool(*preabort_)());
#define PFC_ABORT() {if(pfc::preabort()) PFC_ABORT_FUNC();}
// low-level memory management
struct alloc_site_info;
template<unsigned> static PFC_INLINE const alloc_site_info &get_alloc_site_info(const char *filename_, const char *funcname_, unsigned line_);
PFC_INLINE void *mem_alloc(usize_t num_bytes_, const alloc_site_info *site_info_=0);
template<typename T> PFC_INLINE T *mem_alloc(const alloc_site_info *site_info_=0);
PFC_INLINE void mem_free(void*);
void log_allocated_memory();
PFC_INLINE void mem_copy(void*, const void*, usize_t num_bytes_);
PFC_INLINE void mem_move(void*, const void*, usize_t num_bytes_);
PFC_INLINE void mem_zero(void*, usize_t num_bytes_);
PFC_INLINE void mem_set(void*, unsigned char, usize_t num_bytes_);
PFC_INLINE bool mem_eq(const void*, const void*, usize_t num_bytes_);
PFC_INLINE bool is_mem_zero(void*, usize_t num_bytes_);
PFC_INLINE int mem_diff(const void*, const void*, usize_t num_bytes_);
class memory_allocator_base;
class default_memory_allocator;
// pointer ops
template<typename T> T *ptr(T*);
template<typename T> bool is_valid(T*);
// object construction and destruction
template<typename T> PFC_INLINE T *array_new(usize_t num_items_, const alloc_site_info *site_info_=0);
template<typename T> PFC_INLINE void array_delete(const T*);
template<typename T> PFC_INLINE usize_t array_size(const T*);
template<typename T> PFC_INLINE void *destruct(const T*);
// type info
template<typename T> struct type_id;
template<typename T> struct static_type_id;
template<typename T> struct ptr_id;
template<typename T> struct ref_id;
template<class T> struct class_reg_info;
// ownership "smart" pointers
template<typename T> class owner_ptr;
template<typename T> class owner_ref;
class owner_data;
// casting
template<typename T, typename U> PFC_INLINE T raw_cast(U);
template<typename T, typename U> union raw_cast_union;
template<class T, class U> PFC_INLINE T safe_cast(U&);
template<class T, class U> PFC_INLINE T safe_cast(U*);
template<class T, class U> inline T safe_cast(const owner_ptr<U>&);
template<class T, class U> inline T safe_cast(const owner_ref<U>&);
template<class T, class U> PFC_INLINE T down_cast(U*);
template<class T, class U> PFC_INLINE T down_cast(const owner_ptr<U>&);
template<class T, class U> PFC_INLINE T down_cast(const owner_ref<U>&);
template<class T, class U> PFC_INLINE bool down_cast_check(U*);
template<class T> int find_cast(const T&, const unsigned *type_ids_, unsigned num_type_ids_);
// min/max
template<typename T> PFC_INLINE T min(T, T);
template<typename T> PFC_INLINE T min(T, T, T);
template<typename T> PFC_INLINE T min(T, T, T, T);
template<typename T> PFC_INLINE T max(T, T);
template<typename T> PFC_INLINE T max(T, T, T);
template<typename T> PFC_INLINE T max(T, T, T, T);
template<typename T> struct minmax_res {T min, max;};
template<typename T> PFC_INLINE minmax_res<T> minmax(T, T);
template<typename T> PFC_INLINE minmax_res<T> minmax(T, T, T);
template<typename T> PFC_INLINE minmax_res<T> minmax(T, T, T, T);
// exception handling constructs
template<typename> class eh_data;        // RAII data pointer
class eh_dtor;                           // RAII destructor
template<typename> struct eh_array_dtor; // RAII array destructor
// raw data
struct raw_data;
// data initialization
template<typename T> struct definit_var;
template<typename T> class uninit_var;
// profiling
struct perf_timer;
// directory setup and accessors
void init_working_dir();
const char *executable_dir();
const char *executable_name();
const char *executable_filepath();
const char *working_dir();
void init_editor_data_dir(const char *editor_data_dir_);
const char *editor_data_dir();
// command execution
int system_call(const char *cmd_);
//----------------------------------------------------------------------------


//============================================================================
// config check
//============================================================================
#ifndef PFC_BIG_ENDIAN
#error PFC_BIG_ENDIAN not defined (define in platform/compiler specific header)
#endif
//----------------------------------------------------------------------------


//============================================================================
// PFC_TO_LITTLE/BIG_ENDIAN macros
//============================================================================
#if PFC_BIG_ENDIAN==0
#define PFC_TO_LITTLE_ENDIAN_U16(v__)  uint16_t(v__)
#define PFC_TO_LITTLE_ENDIAN_U32(v__)  uint32_t(v__)
#define PFC_TO_LITTLE_ENDIAN_U64(v__)  uint64_t(v__)
#define PFC_TO_BIG_ENDIAN_U16(v__)     ((uint16_t(v__)<<8)|(uint16_t(v__)>>8))
#define PFC_TO_BIG_ENDIAN_U32(v__)     ((uint32_t(v__)>>24)|((uint32_t(v__)>>8)&0x0000ff00)|((uint32_t(v__)<<8)&0x00ff0000)|(uint32_t(v__)<<24))
#define PFC_TO_BIG_ENDIAN_U64(v__)     ((uint64_t(v__)>>56)|((uint64_t(v__)>>40)&0x000000000000ff00)|((uint64_t(v__)>>24)&0x0000000000ff0000)|((uint64_t(v__)>>8)&0x00000000ff000000)|((uint64_t(v__)<<8)&0x000000ff00000000)|((uint64_t(v__)<<24)&0x0000ff0000000000)|((uint64_t(v__)<<40)&0x00ff000000000000)|(uint64_t(v__)<<56))
#else
#define PFC_TO_LITTLE_ENDIAN_U16(v__)  ((uint16_t(v__)<<8)|(uint16_t(v__)>>8))
#define PFC_TO_LITTLE_ENDIAN_U32(v__)  ((uint32_t(v__)>>24)|((uint32_t(v__)>>8)&0x0000ff00)|((uint32_t(v__)<<8)&0x00ff0000)|(uint32_t(v__)<<24))
#define PFC_TO_LITTLE_ENDIAN_U64(v__)  ((uint64_t(v__)>>56)|((uint64_t(v__)>>40)&0x000000000000ff00)|((uint64_t(v__)>>24)&0x0000000000ff0000)|((uint64_t(v__)>>8)&0x00000000ff000000)|((uint64_t(v__)<<8)&0x000000ff00000000)|((uint64_t(v__)<<24)&0x0000ff0000000000)|((uint64_t(v__)<<40)&0x00ff000000000000)|(uint64_t(v__)<<56))
#define PFC_TO_BIG_ENDIAN_U16(v__)     uint16_t(v__)
#define PFC_TO_BIG_ENDIAN_U32(v__)     uint32_t(v__)
#define PFC_TO_BIG_ENDIAN_U64(v__)     uint64_t(v__)
#endif
//----------------------------------------------------------------------------


//============================================================================
// alloc_site_info
//============================================================================
struct alloc_site_info
{
  // construction
  PFC_INLINE alloc_site_info(const char *filename_, const char *funcname_, unsigned line_);
  //--------------------------------------------------------------------------

  const char *filename;
  const char *funcname;
  unsigned line;
};
//----------------------------------------------------------------------------


//============================================================================
// memory management & new/delete
//============================================================================
#ifdef PFC_BUILDOP_MEMORY_TRACKING
#define PFC_MEM_TRACK_STACK() memory_stack_entry memstack_entry(PFC_FUNCTION)
#define PFC_MEM_ALLOC(bytes__) pfc::mem_alloc(bytes__, &pfc::get_alloc_site_info<__COUNTER__>(__FILE__, PFC_FUNCTION, __LINE__))
#define PFC_NEW(type__) new(pfc::mem_alloc<type__ >(&pfc::get_alloc_site_info<__COUNTER__>(__FILE__, PFC_FUNCTION, __LINE__)))type__
#define PFC_ARRAY_NEW(type__, num_items__) pfc::array_new<type__ >(num_items__, &pfc::get_alloc_site_info<__COUNTER__>(__FILE__, PFC_FUNCTION, __LINE__))
#else
#define PFC_MEM_TRACK_STACK()
#define PFC_MEM_ALLOC(bytes__) pfc::mem_alloc(bytes__)
#define PFC_NEW(type__) new(pfc::mem_alloc<type__ >())type__
#define PFC_ARRAY_NEW(type__, num_items__) pfc::array_new<type__ >(num_items__)
#endif
#define PFC_STACK_MALLOC(bytes__) PFC_ALLOCA(bytes__)
#define PFC_ALIGNED_STACK_MALLOC(bytes__, alignment__) ((void*)((usize_t(PFC_ALLOCA(bytes__+alignment__))+alignment__)&-alignment__))
#define PFC_MEM_FREE(ptr__) pfc::mem_free(ptr__)
#define PFC_DELETE(ptr__) pfc::mem_free(pfc::destruct(ptr__))
#define PFC_ARRAY_DELETE(ptr__) pfc::array_delete(ptr__)
#define PFC_ARRAY_SIZE(ptr__) pfc::array_size(ptr__)
#define PFC_CARRAY_SIZE(array__) (sizeof(array__)/sizeof(*array__))
#define PFC_FWD_DELETE(ptr__) fwd_delete(ptr__)
#define PFC_PNEW(ptr__) new(ptr__)
//----------------------------------------------------------------------------


//============================================================================
// logging/warnings/errors
//============================================================================
// logging
#ifdef PFC_BUILDOP_LOGS
#define PFC_LOG(msg__) {pfc::log_indention(); pfc::log(msg__);}
#define PFC_LOGF(...)  {pfc::log_indention(); pfc::logf(__VA_ARGS__);}
#define PFC_INDENT_LOG() {pfc::indent_log();}
#define PFC_UNINDENT_LOG() {pfc::unindent_log();}
#else
#define PFC_LOG(msg__) (void*)0
#define PFC_LOGF(...) (void*)0
#define PFC_INDENT_LOG() (void*)0
#define PFC_UNINDENT_LOG() (void*)0
#endif
// warnings
#ifdef PFC_BUILDOP_WARNINGS_FILEPATH
#define PFC_WARN_PREFIX(str__) {pfc::warn_indention(); pfc::warnf("%s(%i) : " str__, __FILE__, __LINE__);}
#else
#define PFC_WARN_PREFIX(str__) {pfc::warn_indention(); pfc::warn(str__);}
#endif
#ifdef PFC_BUILDOP_WARNINGS
#define PFC_WARN(msg__)      {PFC_WARN_PREFIX("warning : "); pfc::warn(msg__);}
#define PFC_WARNF(...)       {PFC_WARN_PREFIX("warning : "); pfc::warnf(__VA_ARGS__);}
#define PFC_WARN_ONCE(msg__) {static bool s_is_first=true; if(s_is_first) {s_is_first=false; PFC_WARN_PREFIX("warning : "); pfc::warn(msg__);}}
#define PFC_WARNF_ONCE(...)  {static bool s_is_first=true; if(s_is_first) {s_is_first=false; PFC_WARN_PREFIX("warning : "); pfc::warnf(__VA_ARGS__);}}
#else
#define PFC_WARN(msg__)      (void*)0
#define PFC_WARNF(...)       (void*)0
#define PFC_WARN_ONCE(msg__) (void*)0
#define PFC_WARNF_ONCE(...)  (void*)0
#endif
// errors
#ifdef PFC_BUILDOP_ERRORS_FILEPATH
#define PFC_ERROR_PREFIX(str__) {pfc::error_indention(); pfc::errorf("%s(%i) : " str__, __FILE__, __LINE__);}
#else
#define PFC_ERROR_PREFIX(str__) {pfc::error_indention(); pfc::error(str__);}
#endif
#ifdef PFC_BUILDOP_ERRORS
#define PFC_ERROR(msg__)     {PFC_ERROR_PREFIX("error : "); pfc::error(msg__); PFC_ABORT();}
#define PFC_ERRORF(...)      {PFC_ERROR_PREFIX("error : "); pfc::errorf(__VA_ARGS__); PFC_ABORT();}
#define PFC_ERROR_NOT_IMPL() {PFC_ERROR_PREFIX("error : Functionality not implemented\r\n"); PFC_ABORT();}
#else
#define PFC_ERROR(msg__)      (void*)0
#define PFC_ERRORF(...)       (void*)0
#define PFC_ERROR_NOT_IMPL()  (void*)0
#endif
//----------------------------------------------------------------------------


//============================================================================
// asserts/checks
//============================================================================
// compile-time asserts
#define PFC_STATIC_ASSERT(e__)            static_assert(e__, #e__);
#define PFC_STATIC_ASSERT_MSG(e__, msg__) static_assert(e__, #msg__);
#define PFC_STATIC_ERROR(type__, msg__)   struct PFC_CAT2(cterror_,__LINE__) {char msg__:sizeof(type__)==0;};
// run-time asserts
#ifdef PFC_BUILDOP_ASSERTS
#define PFC_ASSERT(e__)            {if(!(e__)) {PFC_ERROR_PREFIX("assert failed : "#e__"\r\n"); PFC_ABORT();}}
#define PFC_ASSERT_MSG(e__, msg__) {if(!(e__)) {PFC_ERROR_PREFIX("assert failed : "); pfc::errorf msg__; PFC_ABORT();}}
#define PFC_ASSERT_CALL(e__)       {e__;}
#else
#define PFC_ASSERT(e__)            {}
#define PFC_ASSERT_MSG(e__, msg__) {}
#define PFC_ASSERT_CALL(e__)       {}
#endif
// run-time checks
#ifdef PFC_BUILDOP_CHECKS
#define PFC_CHECK(e__)                   {if(!(e__)) {PFC_ERROR_PREFIX("check failed : "#e__"\r\n"); PFC_ABORT();}}
#define PFC_CHECK_MSG(e__, msg__)        {if(!(e__)) {PFC_ERROR_PREFIX("check failed : "); pfc::errorf msg__; PFC_ABORT();}}
#define PFC_CHECK_CALL(e__)              {e__;}
#define PFC_CHECK_WARN(e__, msg__)       {if(!(e__)) {PFC_WARN_PREFIX("warning : "); pfc::warnf msg__;}}
#define PFC_CHECK_WARN_ONCE(e__, msg__)  {static bool s_is_first=true; if(s_is_first && !(e__)) {s_is_first=false; PFC_WARN_PREFIX("warning : "); pfc::warnf msg__;}}
#define PFC_VERIFY(e__)                  PFC_CHECK(e__)
#define PFC_VERIFY_MSG(e__, msg__)       PFC_CHECK_MSG(e__, msg__)
#define PFC_VERIFY_WARN(e__, msg__)      PFC_CHECK_WARN(e__, msg__)
#define PFC_VERIFY_WARN_ONCE(e__, msg__) PFC_CHECK_WARN_ONCE(e__, msg__)
#else
#define PFC_CHECK(e__)                   {}
#define PFC_CHECK_MSG(e__, msg__)        {}
#define PFC_CHECK_CALL(e__)              {}
#define PFC_CHECK_WARN(e__, msg__)       {}
#define PFC_CHECK_WARN_ONCE(e__, msg__)  {}
#define PFC_VERIFY(e__)                  {(e__);}
#define PFC_VERIFY_MSG(e__, msg__)       {(e__);}
#define PFC_VERIFY_WARN(e__, msg__)      {(e__);}
#define PFC_VERIFY_WARN_ONCE(e__, msg__) {(e__);}
#endif
// pedantic asserts/checks
#ifdef PFC_BUILDOP_PEDANTIC
#define PFC_ASSERT_PEDANTIC(e__)            PFC_ASSERT(e__)
#define PFC_ASSERT_PEDANTIC_MSG(e__, msg__) PFC_ASSERT_MSG(e__, msg__)
#define PFC_ASSERT_PEDANTIC_CALL(e__)       PFC_ASSERT_CALL(e__)
#define PFC_CHECK_PEDANTIC(e__)             PFC_CHECK(e__)
#define PFC_CHECK_PEDANTIC_MSG(e__, msg__)  PFC_CHECK_MSG(e__, msg__)
#define PFC_CHECK_PEDANTIC_CALL(e__)        PFC_CHECK_CALL(e__)
#else
#define PFC_ASSERT_PEDANTIC(e__)            {}
#define PFC_ASSERT_PEDANTIC_MSG(e__, msg__) {}
#define PFC_ASSERT_PEDANTIC_CALL(e__)       {}
#define PFC_CHECK_PEDANTIC(e__)             {}
#define PFC_CHECK_PEDANTIC_MSG(e__, msg__)  {}
#define PFC_CHECK_PEDANTIC_CALL(e__)        {}
#endif
//----------------------------------------------------------------------------


//============================================================================
// misc
//============================================================================
#define PFC_OFFSETOF(type__, mvar__) ((usize_t)&(((type__*)0)->mvar__))
#define PFC_OFFSETOF_MVARPTR(type__, mvarptr__) ((usize_t)&(((type__*)0)->*mvarptr__))   /* todo: temp workaround of a gcc bug */
#define PFC_NOTHROW throw()
#define PFC_SAFE_ADDREF(v__) {if(v__) {(v__)->AddRef();}}
#define PFC_SAFE_RELEASE(v__) {if(v__) {(v__)->Release(); v__=0;}}
//----------------------------------------------------------------------------


//============================================================================
// e_jobtype_id
//============================================================================
enum e_jobtype_id {jobtype_none};
//----------------------------------------------------------------------------


//============================================================================
// e_file_open_check
//============================================================================
enum e_file_open_check
{
  fopencheck_none,
  fopencheck_warn,
  fopencheck_abort,
};
//----------------------------------------------------------------------------


//============================================================================
// e_file_open_write_mode
//============================================================================
enum e_file_open_write_mode
{
  fopenwritemode_clear,
  fopenwritemode_keep,
};
//----------------------------------------------------------------------------


//============================================================================
// memory tracking
//============================================================================
#define PFC_MEM_TRACK_STACK_DEPTH 4
enum {memory_align=16,
      max_memory_stack_depth=256};
//----------------------------------------------------------------------------

struct memory_info
{
  usize_t num_items;
#ifdef PFC_BUILDOP_MEMORY_TRACKING
  const alloc_site_info *site_info;
  memory_info *prev, *next;
#if PFC_MEM_TRACK_STACK_DEPTH>0
  const char *stack[PFC_MEM_TRACK_STACK_DEPTH];
#endif
  static memory_info s_head;
#endif
};
//----

enum {memory_info_size=((sizeof(memory_info)+memory_align-1)/memory_align)*memory_align,
      memory_flag_typeless=0x80000000};
//----------------------------------------------------------------------------

struct memory_stack_entry
{
  // construction
  PFC_INLINE memory_stack_entry(const char *func_);
  PFC_INLINE ~memory_stack_entry();
  //--------------------------------------------------------------------------

  static PFC_THREAD_VAR const char *s_stack[max_memory_stack_depth];
  static PFC_THREAD_VAR unsigned s_stack_depth;
};
//----------------------------------------------------------------------------


//============================================================================
// memory_allocator_base
//============================================================================
class memory_allocator_base
{
public:
  // construction
  PFC_INLINE memory_allocator_base();
  virtual PFC_INLINE ~memory_allocator_base();
  virtual void check_allocator(usize_t num_bytes_, usize_t mem_align_)=0;
  //--------------------------------------------------------------------------

  // memory management
  virtual void *alloc(usize_t num_bytes_, usize_t mem_align_=memory_align)=0;
  virtual void free(void*)=0;
  //--------------------------------------------------------------------------

private:
  memory_allocator_base (const memory_allocator_base&); // not implemented
  void operator=(const memory_allocator_base&); // not implemented
};
//----------------------------------------------------------------------------


//============================================================================
// default_memory_allocator
//============================================================================
class default_memory_allocator: public memory_allocator_base
{
public:
  // construction
  static PFC_INLINE default_memory_allocator& inst();
  virtual void check_allocator(usize_t num_bytes_, usize_t mem_align_);
  //--------------------------------------------------------------------------

  // memory management
  virtual void *alloc(usize_t num_bytes_, usize_t mem_align_=memory_align);
  virtual void free(void*);
  //--------------------------------------------------------------------------

private:
  default_memory_allocator();
  virtual ~default_memory_allocator();
  default_memory_allocator(const default_memory_allocator&); // not implemented
  void operator=(const default_memory_allocator&); // not implemented
};
//----------------------------------------------------------------------------


//============================================================================
// type ID
//============================================================================
template<typename T>
struct type_id
{
  static const unsigned id;
};
//----

template<typename T>
struct ptr_id
{
  static const unsigned id;
  PFC_STATIC_ERROR(T, ptr_id_can_not_be_queried_for_non_pointer_types);
};
//----

template<typename T>
struct ref_id
{
  static const unsigned id;
  PFC_STATIC_ERROR(T, ref_id_can_not_be_queried_for_non_reference_types);
};
//----

#define PFC_STATIC_TYPEID(type__, id__) template<> struct static_type_id<type__ > {enum {id=id__};};\
                                        template<> struct static_type_id<const type__ > {enum {id=id__};};\
                                        template<> struct static_type_id<volatile type__ > {enum {id=id__};};\
                                        template<> struct static_type_id<const volatile type__ > {enum {id=id__};};\
                                        template<> struct type_id<type__ > {static const unsigned id;};\
                                        template<> struct type_id<const type__ > {static const unsigned id;};\
                                        template<> struct type_id<volatile type__ > {static const unsigned id;};\
                                        template<> struct type_id<const volatile type__ > {static const unsigned id;}
#include "typeid.inc"
#undef PFC_STATIC_TYPEID
//----------------------------------------------------------------------------


//============================================================================
// class_reg_info
//============================================================================
template<typename T> PFC_INLINE unsigned object_type_id(const T&)                {return type_id<T>::id;}
template<typename T> PFC_INLINE const char *object_typename(const T&)            {return 0;}
template<typename T> PFC_INLINE const char *registered_object_typename(const T&) {return 0;}
template<class T>
struct class_reg_info
{
  static const char *reg_name;
  static unsigned reg_count;
  static const char *deprecated_name;
};
//----------------------------------------------------------------------------


//============================================================================
// class_reg_func_info
//============================================================================
template<class>
struct class_reg_func_info
{
  static bool is_called;
};
//----------------------------------------------------------------------------


//============================================================================
// incomplete type forwarding
//============================================================================
// type, pointer and reference traits
template<typename> struct is_type_fwd_clone;      // rs: classes supporting cloning through pointers to incomplete types
template<typename> struct is_type_fwd_delete;     // rs: classes supporting deletion through pointers to incomplete types
template<typename> struct is_type_fwd_introspec;  // rs: classes supporting introspection through pointers to incomplete types
template<typename> struct is_ptr_fwd_clone;       // pointers to objects supporting cloning through pointers to incomplete types
template<typename> struct is_ptr_fwd_delete;      // pointers to objects supporting deletion through pointers to incomplete types
template<typename> struct is_ptr_fwd_introspec;   // pointers to objects supporting introspection through pointers to incomplete types
template<typename> struct is_ref_fwd_clone;       // references to objects supporting cloning through pointers to incomplete types
template<typename> struct is_ref_fwd_delete;      // references to objects supporting deletion through pointers to incomplete types
template<typename> struct is_ref_fwd_introspec;   // references to objects supporting introspection through pointers to incomplete types
// forwarding registration and functions
template<typename T> void register_fwd_clone();
template<typename T> owner_ref<T> fwd_clone(const T&);
template<typename T> void register_fwd_delete();
template<typename T> PFC_INLINE void fwd_delete(T*);
template<class PE, class T> void register_fwd_introspec();
template<class PE, class T> PFC_INLINE void fwd_introspec(PE&, T*, unsigned flags_=0, const char *mvar_name_=0);
//----------------------------------------------------------------------------


//============================================================================
// introspection
//============================================================================
enum e_penum
{
  penum_none,
  penum_input,     // read data
  penum_output,    // write data
  penum_display,   // display data
  penum_type_info, // collect type info
};
//----

enum e_mvar_flag
{
  mvarflag_mutable     =0x00000001,
  mvarflag_mutable_ptr =0x00000002,
  mvarflag_hidden      =0x00000004,
  mvarflag_array_tail  =0x00000008,
};
//----

template<class PE>
class prop_enum_interface_base
{
public:
  // enumerator type
  enum {pe_type=penum_none};
  //--------------------------------------------------------------------------

  // streaming interface
  template<class T> PFC_INLINE bool subclass(T*); // returns true if sub-class should be processed
  template<class T> PFC_INLINE unsigned set_custom_streaming(T&, unsigned version_); // returns version number
  PFC_INLINE int stream(); // returns reference to the used stream (or the default "int" if not defined)
  template<typename T> PFC_INLINE bool var(const T&, unsigned flags_=0, const char *mvar_name_=0); // returns true if property enumeration should continue
  template<typename T, class C> PFC_INLINE bool var(const T&, unsigned flags_, const char *mvar_name_, C&);
  template<typename T, class C> PFC_INLINE bool var(const T&, unsigned flags_, const char *mvar_name_, C&, void(*post_mutate_func_)(C*));
  template<typename T, class C> PFC_INLINE bool var(const T&, unsigned flags_, const char *mvar_name_, C&, void(C::*mutate_func_)(const T&, unsigned var_index_), unsigned var_index_);
  template<typename T> PFC_INLINE bool avar(const T*, usize_t size_, unsigned flags_=0, const char *mvar_name_=0);
  template<typename T, class C> PFC_INLINE bool avar(const T*, usize_t size_, unsigned flags_, const char *mvar_name_, C&);
  template<typename T, class C> PFC_INLINE bool avar(const T*, usize_t size_, unsigned flags_, const char *mvar_name_, C&, void(*post_mutate_func_)(C*));
  template<typename T, class C> PFC_INLINE bool avar(const T*, usize_t size_, unsigned flags_, const char *mvar_name_, C&, void(C::*mutate_func_)(const T&, unsigned index_, unsigned var_index_), unsigned var_index_);
  PFC_INLINE bool data(const void*, usize_t num_bytes_);
  PFC_INLINE void skip(usize_t num_bytes_);
  template<typename T> PFC_INLINE bool alias_var(const T&, unsigned flags_, const char *alias_);
  template<typename T> PFC_INLINE bool alias_avar(const T*, usize_t size_, unsigned flags_, const char *alias_);
  //--------------------------------------------------------------------------

  // editor specific exposure interface
  PFC_INLINE void group_begin(const char *category_name_);
  PFC_INLINE void group_end();
  PFC_INLINE void name(const char*);
  PFC_INLINE void desc(const char*);
  PFC_INLINE void color(uint32_t rgb_);
  PFC_INLINE void expanded();
  template<typename T> PFC_INLINE void slider(const T &min_, const T &max_, const T &step_);
  //--------------------------------------------------------------------------

protected:
  // construction
  PFC_INLINE prop_enum_interface_base();
  PFC_INLINE ~prop_enum_interface_base();
  //--------------------------------------------------------------------------

private:
  prop_enum_interface_base(const prop_enum_interface_base&); // not implemented
  void operator=(const prop_enum_interface_base&); // not implemented
};
//----

// monomorphic class introspection
template<class PE, class T> void enum_props(PE&, T&) {PFC_STATIC_ERROR(T, class_does_not_have_introspection_definition);}
template<class PE, class T> void enum_props_most_derived(PE&, T&) {PFC_STATIC_ERROR(T, class_does_not_have_introspection_definition);}
PFC_INLINE void post_load_function(void*)  {}
template<class T> class class_factory;
template<class T> struct has_class_trait {};
template<class T> struct pointer_mutator_mono;
// class introspection with lambda expressions
template<class T, class L> void enum_props_lambda(T&, const L&); // [](auto &v_, size_t size_, unsigned flags_, const char *mvar_name_) {...}
// monomorphic class definition
#define PFC_CLASS_REG_FUNC_DECL() friend void register_class_func(this_class_t *p_, bool reg_)\
                                  {\
                                    if(class_reg_func_info<this_class_t>::is_called!=reg_)\
                                    {\
                                      register_class_func((this_class_t::parent_class_t*)p_, reg_);\
                                      this_class_t::register_class_func_this(reg_);\
                                      class_reg_func_info<this_class_t>::is_called=reg_;\
                                    }\
                                  }\
                                  static void register_class_func_this(bool reg_)
#define PFC_CLASS_REG_FUNC_DEF(class__) void class__::register_class_func_this(bool reg_)
#define PFC_LEAF_CLASS_ALIAS(name__) PFC_INLINE friend const pfc::str_id *leaf_class_alias(this_class_t*) {static const pfc::str_id s_id(name__); return &s_id;}
#define PFC_VARIABLE_CLASS_SIGNATURE() friend int has_variable_class_signature(pfc::has_class_trait<const volatile this_class_t>)
#define PFC_MONO(class__) public:\
                          typedef class__ this_class_t;\
                          typedef void parent_class_t;\
                          friend class pfc::class_factory<class__ >;\
                          friend struct pfc::pointer_mutator_mono<class__ >;\
                          friend PFC_INLINE const char *class_typename(class__*) {return #class__;}\
                          friend PFC_INLINE const char *registered_class_typename(class__*) {return pfc::class_reg_info<class__ >::reg_name;}\
                          friend PFC_INLINE unsigned subclass_type_ids(class__*, unsigned *ids_) {*ids_=pfc::type_id<class__ >::id; return 1;}\
                          friend int has_class_introspection(pfc::has_class_trait<const volatile class__ >) {return 0;}\
                          friend PFC_INLINE const char *object_typename(const class__&) {return class_typename((class__*)0);}\
                          friend PFC_INLINE const char *registered_object_typename(const class__&) {return registered_class_typename((class__*)0);}\
                          PFC_INLINE unsigned subobject_type_ids(unsigned *ids_) const {*ids_=pfc::type_id<class__ >::id; return 1;}\
                          template<class PE> friend PFC_INLINE void enum_props(PE &pe_, class__ &v_) {enum_props_most_derived(pe_, v_);}\
                          template<class PE> friend PFC_INLINE void enum_props_most_derived(PE &pe_, class__ &v_) {if(pe_.subclass(&v_)) enum_props_this(pe_, v_);}\
                          template<class PE> friend PFC_INLINE void enum_props_this(PE &pe_, class__ &v_)
// introspection declaration & definition
#define PFC_INTROSPEC_DECL {v_.enum_props_impl(pe_, v_);} template<class PE> void enum_props_impl(PE&, this_class_t&)
#define PFC_INTROSPEC_CPP_DEF(class__) template void class__::enum_props_impl(pfc::prop_enum_input_stream<pfc::bin_input_stream_base>&, class__&);\
                                       template void class__::enum_props_impl(pfc::prop_enum_output_stream<pfc::bin_output_stream_base>&, class__&);\
                                       template void class__::enum_props_impl(pfc::prop_enum_input_archive<pfc::bin_input_stream_base>&, class__&);\
                                       template void class__::enum_props_impl(pfc::prop_enum_output_archive<pfc::bin_output_stream_base>&, class__&);\
                                       template void class__::enum_props_impl(pfc::prop_enum_output_archive<pfc::bin_output_stream_base>::prop_enum_type_info&, class__&);\
                                       template void class__::enum_props_impl(pfc::class_factory_base::prop_enum_input_converter<pfc::bin_input_stream_base>&, class__&);\
                                       PFC_ENDIAN_INTROSPEC_DEF(class__);\
                                       template void class__::enum_props_impl(pfc::prop_enum_exposure_base&, class__&);\
                                       template<class PE> void class__::enum_props_impl(PE &pe_, this_class_t &v_)
#define PFC_INTROSPEC_INL_DEF(class__) template<class PE> void class__::enum_props_impl(PE &pe_, this_class_t &v_)
#define PFC_INTROSPEC_INL_TDEF1(a0__, class__) template<a0__> template<class PE> void class__::enum_props_impl(PE &pe_, this_class_t &v_)
#define PFC_INTROSPEC_INL_TDEF2(a0__, a1__, c0__, c1__) template<a0__, a1__> template<class PE> void c0__, c1__::enum_props_impl(PE &pe_, this_class_t &v_)
#define PFC_INTROSPEC_INL_TDEF3(a0__, a1__, a2__, c0__, c1__, c2__) template<a0__, a1__, a2__> template<class PE> void c0__, c1__, c2__::enum_props_impl(PE &pe_, this_class_t &v_)
#define PFC_INTROSPEC_INL_TDEF4(a0__, a1__, a2__, a3__, c0__, c1__, c2__, c3__) template<a0__, a1__, a2__, a3__> template<class PE> void c0__, c1__, c2__, c3__::enum_props_impl(PE &pe_, this_class_t &v_)
#define PFC_INTROSPEC_INL_TDEF5(a0__, a1__, a2__, a3__, a4__, c0__, c1__, c2__, c3__, c4__) template<a0__, a1__, a2__, a3__, a4__> template<class PE> void c0__, c1__, c2__, c3__, c4__::enum_props_impl(PE &pe_, this_class_t &v_)
#define PFC_INTROSPEC_INL_TDEF6(a0__, a1__, a2__, a3__, a4__, a5__, c0__, c1__, c2__, c3__, c4__, c5__) template<a0__, a1__, a2__, a3__, a4__, a5__> template<class PE> void c0__, c1__, c2__, c3__, c4__, c5__::enum_props_impl(PE &pe_, this_class_t &v_)
#define PFC_INTROSPEC_INL_TDEF7(a0__, a1__, a2__, a3__, a4__, a5__, a6__, c0__, c1__, c2__, c3__, c4__, c5__, c6__) template<a0__, a1__, a2__, a3__, a4__, a5__, a6__> template<class PE> void c0__, c1__, c2__, c3__, c4__, c5__, c6__::enum_props_impl(PE &pe_, this_class_t &v_)
#define PFC_INTROSPEC_INL_TDEF8(a0__, a1__, a2__, a3__, a4__, a5__, a6__, a7__, c0__, c1__, c2__, c3__, c4__, c5__, c6__, c7__) template<a0__, a1__, a2__, a3__, a4__, a5__, a6__, a7__> template<class PE> void c0__, c1__, c2__, c3__, c4__, c5__, c6__, c7__::enum_props_impl(PE &pe_, this_class_t &v_)
#define PFC_INTROSPEC_INL_TDEF9(a0__, a1__, a2__, a3__, a4__, a5__, a6__, a7__, a8__, c0__, c1__, c2__, c3__, c4__, c5__, c6__, c7__, c8__) template<a0__, a1__, a2__, a3__, a4__, a5__, a6__, a7__, a8__> template<class PE> void c0__, c1__, c2__, c3__, c4__, c5__, c6__, c7__, c8__::enum_props_impl(PE &pe_, this_class_t &v_)
#define PFC_INTROSPEC_INL_TDEF10(a0__, a1__, a2__, a3__, a4__, a5__, a6__, a7__, a8__, a9__, c0__, c1__, c2__, c3__, c4__, c5__, c6__, c7__, c8__, c9__) template<a0__, a1__, a2__, a3__, a4__, a5__, a6__, a7__, a8__, a9__> template<class PE> void c0__, c1__, c2__, c3__, c4__, c5__, c6__, c7__, c8__, c9__::enum_props_impl(PE &pe_, this_class_t &v_)
//----

// member variable introspection
#define PFC_VAR(vname__) if(!pe_.var(v_.vname__, 0, #vname__, v_)) return
#define PFC_VAR2(vn0__, vn1__) if(!pe_.var(v_.vn0__, 0, #vn0__, v_)) return; if(!pe_.var(v_.vn1__, 0, #vn1__, v_)) return
#define PFC_VAR3(vn0__, vn1__, vn2__) if(!pe_.var(v_.vn0__, 0, #vn0__, v_)) return; if(!pe_.var(v_.vn1__, 0, #vn1__, v_)) return; if(!pe_.var(v_.vn2__, 0, #vn2__, v_)) return
#define PFC_VAR4(vn0__, vn1__, vn2__, vn3__) if(!pe_.var(v_.vn0__, 0, #vn0__, v_)) return; if(!pe_.var(v_.vn1__, 0, #vn1__, v_)) return; if(!pe_.var(v_.vn2__, 0, #vn2__, v_)) return; if(!pe_.var(v_.vn3__, 0, #vn3__, v_)) return
#define PFC_VAR5(vn0__, vn1__, vn2__, vn3__, vn4__) PFC_VAR4(vn0__, vn1__, vn2__, vn3__); PFC_VAR(vn4__)
#define PFC_VAR6(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__) PFC_VAR4(vn0__, vn1__, vn2__, vn3__); PFC_VAR2(vn4__, vn5__)
#define PFC_VAR7(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__, vn6__) PFC_VAR4(vn0__, vn1__, vn2__, vn3__); PFC_VAR3(vn4__, vn5__, vn6__)
#define PFC_VAR8(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__, vn6__, vn7__) PFC_VAR4(vn0__, vn1__, vn2__, vn3__); PFC_VAR4(vn4__, vn5__, vn6__, vn7__)
#define PFC_VAR9(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__, vn6__, vn7__, vn8__) PFC_VAR8(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__, vn6__, vn7__); PFC_VAR(vn8__)
#define PFC_VAR10(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__, vn6__, vn7__, vn8__, vn9__) PFC_VAR8(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__, vn6__, vn7__); PFC_VAR2(vn8__, vn9__)
//----

// custom flag member variable introspection
#define PFC_FVAR(vname__, flags__) if(!pe_.var(v_.vname__, flags__, #vname__, v_)) return
#define PFC_FVAR2(vn0__, vn1__, flags__) if(!pe_.var(v_.vn0__, flags__, #vn0__, v_)) return; if(!pe_.var(v_.vn1__, flags__, #vn1__, v_)) return
#define PFC_FVAR3(vn0__, vn1__, vn2__, flags__) if(!pe_.var(v_.vn0__, flags__, #vn0__, v_)) return; if(!pe_.var(v_.vn1__, flags__, #vn1__, v_)) return; if(!pe_.var(v_.vn2__, flags__, #vn2__, v_)) return
#define PFC_FVAR4(vn0__, vn1__, vn2__, vn3__, flags__) if(!pe_.var(v_.vn0__, flags__, #vn0__, v_)) return; if(!pe_.var(v_.vn1__, flags__, #vn1__, v_)) return; if(!pe_.var(v_.vn2__, flags__, #vn2__, v_)) return; if(!pe_.var(v_.vn3__, flags__, #vn3__, v_)) return
#define PFC_FVAR5(vn0__, vn1__, vn2__, vn3__, vn4__, flags__) PFC_FVAR4(vn0__, vn1__, vn2__, vn3__, flags__); PFC_FVAR(vn4__, flags__)
#define PFC_FVAR6(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__, flags__) PFC_FVAR4(vn0__, vn1__, vn2__, vn3__, flags__); PFC_FVAR2(vn4__, vn5__, flags__)
#define PFC_FVAR7(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__, vn6__, flags__) PFC_FVAR4(vn0__, vn1__, vn2__, vn3__, flags__); PFC_FVAR3(vn4__, vn5__, vn6__, flags__)
#define PFC_FVAR8(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__, vn6__, vn7__, flags__) PFC_FVAR4(vn0__, vn1__, vn2__, vn3__, flags__); PFC_FVAR4(vn4__, vn5__, vn6__, vn7__, flags__)
#define PFC_FVAR9(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__, vn6__, vn7__, vn8__, flags__) PFC_FVAR8(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__, vn6__, vn7__, flags__); PFC_FVAR(vn8__, flags__)
#define PFC_FVAR10(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__, vn6__, vn7__, vn8__, vn9__, flags__) PFC_FVAR8(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__, vn6__, vn7__, flags__); PFC_FVAR2(vn8__, vn9__, flags__)
//----

// hidden (in editor) member variable introspection
#define PFC_HVAR(vname__) if(!pe_.var(v_.vname__, pfc::mvarflag_hidden, #vname__, v_)) return
#define PFC_HVAR2(vn0__, vn1__) if(!pe_.var(v_.vn0__, pfc::mvarflag_hidden, #vn0__, v_)) return; if(!pe_.var(v_.vn1__, pfc::mvarflag_hidden, #vn1__, v_)) return
#define PFC_HVAR3(vn0__, vn1__, vn2__) if(!pe_.var(v_.vn0__, pfc::mvarflag_hidden, #vn0__, v_)) return; if(!pe_.var(v_.vn1__, pfc::mvarflag_hidden, #vn1__, v_)) return; if(!pe_.var(v_.vn2__, pfc::mvarflag_hidden, #vn2__, v_)) return
#define PFC_HVAR4(vn0__, vn1__, vn2__, vn3__) if(!pe_.var(v_.vn0__, pfc::mvarflag_hidden, #vn0__, v_)) return; if(!pe_.var(v_.vn1__, pfc::mvarflag_hidden, #vn1__, v_)) return; if(!pe_.var(v_.vn2__, pfc::mvarflag_hidden, #vn2__, v_)) return; if(!pe_.var(v_.vn3__, pfc::mvarflag_hidden, #vn3__, v_)) return
#define PFC_HVAR5(vn0__, vn1__, vn2__, vn3__, vn4__) PFC_VAR4(vn0__, vn1__, vn2__, vn3__); PFC_VAR(vn4__)
#define PFC_HVAR6(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__) PFC_VAR4(vn0__, vn1__, vn2__, vn3__); PFC_VAR2(vn4__, vn5__)
#define PFC_HVAR7(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__, vn6__) PFC_VAR4(vn0__, vn1__, vn2__, vn3__); PFC_VAR3(vn4__, vn5__, vn6__)
#define PFC_HVAR8(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__, vn6__, vn7__) PFC_VAR4(vn0__, vn1__, vn2__, vn3__); PFC_VAR4(vn4__, vn5__, vn6__, vn7__)
#define PFC_HVAR9(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__, vn6__, vn7__, vn8__) PFC_VAR8(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__, vn6__, vn7__); PFC_VAR(vn8__)
#define PFC_HVAR10(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__, vn6__, vn7__, vn8__, vn9__) PFC_VAR8(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__, vn6__, vn7__); PFC_VAR2(vn8__, vn9__)
//----

// mutable (in editor) member variable introspection
#define PFC_MVAR(vname__) if(!pe_.var(v_.vname__, pfc::mvarflag_mutable, #vname__, v_)) return
#define PFC_MVAR2(vn0__, vn1__) if(!pe_.var(v_.vn0__, pfc::mvarflag_mutable, #vn0__, v_)) return; if(!pe_.var(v_.vn1__, pfc::mvarflag_mutable, #vn1__, v_)) return
#define PFC_MVAR3(vn0__, vn1__, vn2__) if(!pe_.var(v_.vn0__, pfc::mvarflag_mutable, #vn0__, v_)) return; if(!pe_.var(v_.vn1__, pfc::mvarflag_mutable, #vn1__, v_)) return; if(!pe_.var(v_.vn2__, pfc::mvarflag_mutable, #vn2__, v_)) return
#define PFC_MVAR4(vn0__, vn1__, vn2__, vn3__) if(!pe_.var(v_.vn0__, pfc::mvarflag_mutable, #vn0__, v_)) return; if(!pe_.var(v_.vn1__, pfc::mvarflag_mutable, #vn1__, v_)) return; if(!pe_.var(v_.vn2__, pfc::mvarflag_mutable, #vn2__, v_)) return; if(!pe_.var(v_.vn3__, pfc::mvarflag_mutable, #vn3__, v_)) return
#define PFC_MVAR5(vn0__, vn1__, vn2__, vn3__, vn4__) PFC_MVAR4(vn0__, vn1__, vn2__, vn3__); PFC_MVAR(vn4__)
#define PFC_MVAR6(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__) PFC_MVAR4(vn0__, vn1__, vn2__, vn3__); PFC_MVAR2(vn4__, vn5__)
#define PFC_MVAR7(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__, vn6__) PFC_MVAR4(vn0__, vn1__, vn2__, vn3__); PFC_MVAR3(vn4__, vn5__, vn6__)
#define PFC_MVAR8(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__, vn6__, vn7__) PFC_MVAR4(vn0__, vn1__, vn2__, vn3__); PFC_MVAR4(vn4__, vn5__, vn6__, vn7__)
#define PFC_MVAR9(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__, vn6__, vn7__, vn8__) PFC_MVAR8(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__, vn6__, vn7__); PFC_MVAR(vn8__)
#define PFC_MVAR10(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__, vn6__, vn7__, vn8__, vn9__) PFC_MVAR8(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__, vn6__, vn7__); PFC_MVAR2(vn8__, vn9__)
//----

// mutable (in editor) pointer member variable introspection
#define PFC_VARMP(vname__) if(!pe_.var(v_.vname__, pfc::mvarflag_mutable_ptr, #vname__, v_)) return
#define PFC_VARMP2(vn0__, vn1__) if(!pe_.var(v_.vn0__, pfc::mvarflag_mutable_ptr, #vn0__, v_)) return; if(!pe_.var(v_.vn1__, pfc::mvarflag_mutable_ptr, #vn1__, v_)) return
#define PFC_VARMP3(vn0__, vn1__, vn2__) if(!pe_.var(v_.vn0__, pfc::mvarflag_mutable_ptr, #vn0__, v_)) return; if(!pe_.var(v_.vn1__, pfc::mvarflag_mutable_ptr, #vn1__, v_)) return; if(!pe_.var(v_.vn2__, pfc::mvarflag_mutable_ptr, #vn2__, v_)) return
#define PFC_VARMP4(vn0__, vn1__, vn2__, vn3__) if(!pe_.var(v_.vn0__, pfc::mvarflag_mutable_ptr, #vn0__, v_)) return; if(!pe_.var(v_.vn1__, pfc::mvarflag_mutable_ptr, #vn1__, v_)) return; if(!pe_.var(v_.vn2__, pfc::mvarflag_mutable_ptr, #vn2__, v_)) return; if(!pe_.var(v_.vn3__, pfc::mvarflag_mutable_ptr, #vn3__, v_)) return
#define PFC_VARMP5(vn0__, vn1__, vn2__, vn3__, vn4__) PFC_VARMP4(vn0__, vn1__, vn2__, vn3__); PFC_VARMP(vn4__)
#define PFC_VARMP6(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__) PFC_VARMP4(vn0__, vn1__, vn2__, vn3__); PFC_VARMP2(vn4__, vn5__)
#define PFC_VARMP7(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__, vn6__) PFC_VARMP4(vn0__, vn1__, vn2__, vn3__); PFC_VARMP3(vn4__, vn5__, vn6__)
#define PFC_VARMP8(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__, vn6__, vn7__) PFC_VARMP4(vn0__, vn1__, vn2__, vn3__); PFC_VARMP4(vn4__, vn5__, vn6__, vn7__)
#define PFC_VARMP9(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__, vn6__, vn7__, vn8__) PFC_VARMP8(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__, vn6__, vn7__); PFC_VARMP(vn8__)
#define PFC_VARMP10(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__, vn6__, vn7__, vn8__, vn9__) PFC_VARMP8(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__, vn6__, vn7__); PFC_VARMP2(vn8__, vn9__)

// mutable (in editor) pointer member variable pointing to mutable class
#define PFC_MVARMP(vname__) if(!pe_.var(v_.vname__, pfc::mvarflag_mutable|pfc::mvarflag_mutable_ptr, #vname__, v_)) return
#define PFC_MVARMP2(vn0__, vn1__) if(!pe_.var(v_.vn0__, pfc::mvarflag_mutable|pfc::mvarflag_mutable_ptr, #vn0__, v_)) return; if(!pe_.var(v_.vn1__, pfc::mvarflag_mutable|pfc::mvarflag_mutable_ptr, #vn1__, v_)) return
#define PFC_MVARMP3(vn0__, vn1__, vn2__) if(!pe_.var(v_.vn0__, pfc::mvarflag_mutable|pfc::mvarflag_mutable_ptr, #vn0__, v_)) return; if(!pe_.var(v_.vn1__, pfc::mvarflag_mutable|pfc::mvarflag_mutable_ptr, #vn1__, v_)) return; if(!pe_.var(v_.vn2__, pfc::mvarflag_mutable|pfc::mvarflag_mutable_ptr, #vn2__, v_)) return
#define PFC_MVARMP4(vn0__, vn1__, vn2__, vn3__) if(!pe_.var(v_.vn0__, pfc::mvarflag_mutable|pfc::mvarflag_mutable_ptr, #vn0__, v_)) return; if(!pe_.var(v_.vn1__, pfc::mvarflag_mutable|pfc::mvarflag_mutable_ptr, #vn1__, v_)) return; if(!pe_.var(v_.vn2__, pfc::mvarflag_mutable|pfc::mvarflag_mutable_ptr, #vn2__, v_)) return; if(!pe_.var(v_.vn3__, pfc::mvarflag_mutable|pfc::mvarflag_mutable_ptr, #vn3__, v_)) return
#define PFC_MVARMP5(vn0__, vn1__, vn2__, vn3__, vn4__) PFC_MVARMP4(vn0__, vn1__, vn2__, vn3__); PFC_MVARMP(vn4__)
#define PFC_MVARMP6(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__) PFC_MVARMP4(vn0__, vn1__, vn2__, vn3__); PFC_MVARMP2(vn4__, vn5__)
#define PFC_MVARMP7(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__, vn6__) PFC_MVARMP4(vn0__, vn1__, vn2__, vn3__); PFC_MVARMP3(vn4__, vn5__, vn6__)
#define PFC_MVARMP8(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__, vn6__, vn7__) PFC_MVARMP4(vn0__, vn1__, vn2__, vn3__); PFC_MVARMP4(vn4__, vn5__, vn6__, vn7__)
#define PFC_MVARMP9(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__, vn6__, vn7__, vn8__) PFC_MVARMP8(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__, vn6__, vn7__); PFC_MVARMP(vn8__)
#define PFC_MVARMP10(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__, vn6__, vn7__, vn8__, vn9__) PFC_MVARMP8(vn0__, vn1__, vn2__, vn3__, vn4__, vn5__, vn6__, vn7__); PFC_MVARMP2(vn8__, vn9__)
//----

// aliased member variable introspection
#define PFC_ALIAS_VAR(vname__, alias__) if(!pe_.alias_var(v_.vname__, 0, alias__)) return
#define PFC_ALIAS_AVAR(vname__, size__, alias__) if(!pe_.alias_avar(v_.vname__, size__, 0, alias__)) return
//----

// array variables
#define PFC_AVAR(vname__, size__) if(!pe_.avar(v_.vname__, size__, 0, #vname__, v_)) return
#define PFC_FAVAR(vname__, size__, flags__) if(!pe_.avar(v_.vname__, size__, flags__, #vname__, v_)) return
#define PFC_HAVAR(vname__, size__) if(!pe_.avar(v_.vname__, size__, pfc::mvarflag_hidden, #vname__, v_)) return
#define PFC_MAVAR(vname__, size__) if(!pe_.avar(v_.vname__, size__, pfc::mvarflag_mutable, #vname__, v_)) return
#define PFC_AVARMP(vname__, size__) if(!pe_.avar(v_.vname__, size__, pfc::mvarflag_mutable_ptr, #vname__, v_)) return
#define PFC_MAVARMP(vname__, size__) if(!pe_.avar(v_.vname__, size__, pfc::mvarflag_mutable|pfc::mvarflag_mutable_ptr, #vname__, v_)) return
//----

// mutable post-mutate function call variables
#define PFC_MVAR_MCALL(vname__, call__) {struct func_call {static void call(this_class_t *p_) {p_->call__;}}; if(!pe_.var(v_.vname__, pfc::mvarflag_mutable, #vname__, v_, &func_call::call)) return;}
#define PFC_MVARMP_MCALL(vname__, call__) {struct func_call {static void call(this_class_t *p_) {p_->call__;}}; if(!pe_.var(v_.vname__, pfc::mvarflag_mutable|pfc::mvarflag_mutable_ptr, #vname__, v_, &func_call::call)) return;}
#define PFC_MAVAR_MCALL(vname__, size__, call__) {struct func_call {static void call(this_class_t *p_) {p_->call__;}}; if(!pe_.avar(v_.vname__, size__, pfc::mvarflag_mutable, #vname__, v_, &func_call::call)) return;}
#define PFC_MAVARMP_MCALL(vname__, call__) {struct func_call {static void call(this_class_t *p_) {p_->call__;}}; if(!pe_.avar(v_.vname__, size__, pfc::mvarflag_mutable|pfc::mvarflag_mutable_ptr, #vname__, v_, &func_call::call)) return;}
//----

// mutable virtual variables (variable mutation is done through a class member function call)
#define PFC_MVVAR(vname__, func__, var_index__) if(!pe_.var(v_.vname__, pfc::mvarflag_mutable, #vname__, v_, &this_class_t::func__, var_index__)) return
#define PFC_MVVARMP(vname__, func__, var_index__) if(!pe_.var(v_.vname__, pfc::mvarflag_mutable|pfc::mvarflag_mutable_ptr, #vname__, v_, &this_class_t::func__, var_index__)) return
#define PFC_MVAVAR(vname__, size__, func__, var_index__) if(!pe_.avar(v_.vname__, size__, pfc::mvarflag_mutable, #vname__, v_, &this_class_t::func__, var_index__)) return
#define PFC_MVAVARMP(vname__, size__, func__, var_index__) if(!pe_.avar(v_.vname__, size__, pfc::mvarflag_mutable|pfc::mvarflag_mutable_ptr, #vname__, v_, &this_class_t::func__, var_index__)) return
//----

// introspection function calls
#define PFC_CUSTOM_STREAMING(version__) pe_.set_custom_streaming(v_, version__)
#define PFC_CUSTOM_STREAMING_FUNCS() if(stream_func(pe_.stream(), v_)) return;
#define PFC_POST_LOAD_CALL(call__) friend PFC_INLINE void post_load_function(this_class_t *v_) {post_load_function(static_cast<parent_class_t*>(v_)); v_->call__;}
#define PFC_SAVE_CALL(call__) if(PE::pe_type==pfc::penum_output) v_.call__
#define PFC_VAR_GROUP(group_name__) pe_.group_begin(group_name__)
#define PFC_VAR_GROUP_END() pe_.group_end()
//----

// custom streaming function definitions
template<class S, typename T> bool stream_func(const S&, T&) {return false;}
#define PFC_CUSTOM_STREAMING_FUNC(stream_type__, type__) PFC_INLINE bool stream_func(stream_type__ &s_, type__ &v_)
#define PFC_CALL_CUSTOM_STREAMING_FUNC(stream__, val__) stream_func(stream__, val__)
//----

// special variable exposure macros
#define PFC_VEXP_N(name__) {}
#define PFC_VEXP_D(desc__) {}
#define PFC_VEXP_C(rgb__) {}
#define PFC_VEXP_ND(name__, desc__) {}
#define PFC_VEXP_NC(name__, rgb__) {}
#define PFC_VEXP_DC(desc__, rgb__) {}
#define PFC_VEXP_NDC(name__, desc__, rgb__) {}
#define PFC_VEXP_EXPANDED() {}
// short-hand versions for single variable macros (name)
#define PFC_VAR_N(vname__, name__) PFC_VAR(vname__); PFC_VEXP_N(name__)
#define PFC_FVAR_N(vname__, flags__, name__) PFC_FVAR(vname__, flags__); PFC_VEXP_N(name__)
#define PFC_VARMP_N(vname__, name__) PFC_VARMP(vname__); PFC_VEXP_N(name__)
#define PFC_MVAR_N(vname__, name__) PFC_MVAR(vname__); PFC_VEXP_N(name__)
#define PFC_MVARMP_N(vname__, name__) PFC_MVARMP(vname__); PFC_VEXP_N(name__)
#define PFC_AVAR_N(vname__, size__, name__) PFC_AVAR(vname__, size__); PFC_VEXP_N(name__)
#define PFC_FAVAR_N(vname__, size__, flags__, name__) PFC_FAVAR(vname__, size__, flags__); PFC_VEXP_N(name__)
#define PFC_MAVAR_N(vname__, size__, name__) PFC_MAVAR(vname__, size__); PFC_VEXP_N(name__)
#define PFC_AVARMP_N(vname__, size__, name__) PFC_AVARMP(vname__, size__); PFC_VEXP_N(name__)
#define PFC_MAVARMP_N(vname__, size__, name__) PFC_MAVARMP(vname__, size__); PFC_VEXP_N(name__)
#define PFC_MVAR_MCALL_N(vname__, call__, name__) PFC_MVAR_MCALL(vname__, call__); PFC_VEXP_N(name__)
#define PFC_MVARMP_MCALL_N(vname__, call__, name__) PFC_MVARMP_MCALL(vname__, call__); PFC_VEXP_N(name__)
#define PFC_MAVAR_MCALL_N(vname__, size__, call__, name__) PFC_MAVAR_MCALL(vname__, size__, call__); PFC_VEXP_N(name__)
#define PFC_MAVARMP_MCALL_N(vname__, size__, call__, name__) PFC_MAVARMP_MCALL(vname__, size__, call__); PFC_VEXP_N(name__)
#define PFC_MVVAR_N(vname__, func__, var_idx__, name__) PFC_MVVAR(vname__, func__, var_idx__); PFC_VEXP_N(name__)
#define PFC_MVVARMP_N(vname__, func__, var_idx__, name__) PFC_MVVARMP(vname__, func__, var_idx__); PFC_VEXP_N(name__)
#define PFC_MVAVAR_N(vname__, size__, func__, var_idx__, name__) PFC_MVAVAR(vname__, size__, func__, var_idx__); PFC_VEXP_N(name__)
#define PFC_MVAVARMP_N(vname__, size__, func__, var_idx__, name__) PFC_MVAVARMP(vname__, size__, func__, var_idx__); PFC_VEXP_N(name__)
// short-hand versions for single variable macros (description)
#define PFC_VAR_D(vname__, desc__) PFC_VAR(vname__); PFC_VEXP_D(desc__)
#define PFC_FVAR_D(vname__, flags__, desc__) PFC_FVAR(vname__, flags__); PFC_VEXP_D(desc__)
#define PFC_VARMP_D(vname__, desc__) PFC_VARMP(vname__); PFC_VEXP_D(desc__)
#define PFC_MVAR_D(vname__, desc__) PFC_MVAR(vname__); PFC_VEXP_D(desc__)
#define PFC_MVARMP_D(vname__, desc__) PFC_MVARMP(vname__); PFC_VEXP_D(desc__)
#define PFC_AVAR_D(vname__, size__, desc__) PFC_AVAR(vname__, size__); PFC_VEXP_D(desc__)
#define PFC_FAVAR_D(vname__, size__, flags__, desc__) PFC_FAVAR(vname__, size__, flags__); PFC_VEXP_D(desc__)
#define PFC_MAVAR_D(vname__, size__, desc__) PFC_MAVAR(vname__, size__); PFC_VEXP_D(desc__)
#define PFC_AVARMP_D(vname__, size__, desc__) PFC_AVARMP(vname__, size__); PFC_VEXP_D(desc__)
#define PFC_MAVARMP_D(vname__, size__, desc__) PFC_MAVARMP(vname__, size__); PFC_VEXP_D(desc__)
#define PFC_MVAR_MCALL_D(vname__, call__, desc__) PFC_MVAR_MCALL(vname__, call__); PFC_VEXP_D(desc__)
#define PFC_MVARMP_MCALL_D(vname__, call__, desc__) PFC_MVARMP_MCALL(vname__, call__); PFC_VEXP_D(desc__)
#define PFC_MAVAR_MCALL_D(vname__, size__, call__, desc__) PFC_MAVAR_MCALL(vname__, size__, call__); PFC_VEXP_D(desc__)
#define PFC_MAVARMP_MCALL_D(vname__, size__, call__, desc__) PFC_MAVARMP_MCALL(vname__, size__, call__); PFC_VEXP_D(desc__)
#define PFC_MVVAR_D(vname__, func__, var_idx__, desc__) PFC_MVVAR(vname__, func__, var_idx__); PFC_VEXP_D(desc__)
#define PFC_MVVARMP_D(vname__, func__, var_idx__, desc__) PFC_MVVARMP(vname__, func__, var_idx__); PFC_VEXP_D(desc__)
#define PFC_MVAVAR_D(vname__, size__, func__, var_idx__, desc__) PFC_MVAVAR(vname__, size__, func__, var_idx__); PFC_VEXP_D(desc__)
#define PFC_MVAVARMP_D(vname__, size__, func__, var_idx__, desc__) PFC_MVAVARMP(vname__, size__, func__, var_idx__); PFC_VEXP_D(desc__)
// short-hand versions for single variable macros (name+description)
#define PFC_VAR_ND(vname__, name__, desc__) PFC_VAR(vname__); PFC_VEXP_ND(name__, desc__)
#define PFC_FVAR_ND(vname__, flags__, name__, desc__) PFC_FVAR(vname__, flags__); PFC_VEXP_ND(name__, desc__)
#define PFC_VARMP_ND(vname__, name__, desc__) PFC_VARMP(vname__); PFC_VEXP_ND(name__, desc__)
#define PFC_MVAR_ND(vname__, name__, desc__) PFC_MVAR(vname__); PFC_VEXP_ND(name__, desc__)
#define PFC_MVARMP_ND(vname__, name__, desc__) PFC_MVARMP(vname__); PFC_VEXP_ND(name__, desc__)
#define PFC_AVAR_ND(vname__, size__, name__, desc__) PFC_AVAR(vname__, size__); PFC_VEXP_ND(name__, desc__)
#define PFC_FAVAR_ND(vname__, size__, flags__, name__, desc__) PFC_FAVAR(vname__, size__, flags__); PFC_VEXP_ND(name__, desc__)
#define PFC_MAVAR_ND(vname__, size__, name__, desc__) PFC_MAVAR(vname__, size__); PFC_VEXP_ND(name__, desc__)
#define PFC_AVARMP_ND(vname__, size__, name__, desc__) PFC_AVARMP(vname__, size__); PFC_VEXP_ND(name__, desc__)
#define PFC_MAVARMP_ND(vname__, size__, name__, desc__) PFC_MAVARMP(vname__, size__); PFC_VEXP_ND(name__, desc__)
#define PFC_MVAR_MCALL_ND(vname__, call__, name__, desc__) PFC_MVAR_MCALL(vname__, call__); PFC_VEXP_ND(name__, desc__)
#define PFC_MVARMP_MCALL_ND(vname__, call__, name__, desc__) PFC_MVARMP_MCALL(vname__, call__); PFC_VEXP_ND(name__, desc__)
#define PFC_MAVAR_MCALL_ND(vname__, size__, call__, name__, desc__) PFC_MAVAR_MCALL(vname__, size__, call__); PFC_VEXP_ND(name__, desc__)
#define PFC_MAVARMP_MCALL_ND(vname__, size__, call__, name__, desc__) PFC_MAVARMP_MCALL(vname__, size__, call__); PFC_VEXP_ND(name__, desc__)
#define PFC_MVVAR_ND(vname__, func__, var_idx__, name__, desc__) PFC_MVVAR(vname__, func__, var_idx__); PFC_VEXP_ND(name__, desc__)
#define PFC_MVVARMP_ND(vname__, func__, var_idx__, name__, desc__) PFC_MVVARMP(vname__, func__, var_idx__); PFC_VEXP_ND(name__, desc__)
#define PFC_MVAVAR_ND(vname__, size__, func__, var_idx__, name__, desc__) PFC_MVAVAR(vname__, size__, func__, var_idx__); PFC_VEXP_ND(name__, desc__)
#define PFC_MVAVARMP_ND(vname__, size__, func__, var_idx__, name__, desc__) PFC_MVAVARMP(vname__, size__, func__, var_idx__); PFC_VEXP_ND(name__, desc__)
//----------------------------------------------------------------------------


//============================================================================
// event system
//============================================================================
#define PFC_EVENT_HANDLER_BEGIN_BASE(class__)\
  template<class EH, typename E> friend void pfc::send_event(EH&, E&);\
  public:\
  virtual void dispatch_event(unsigned eid_, void *e_)\
  {\
    struct event_handler {static PFC_INLINE void dispatch_event(unsigned, void*) {}};\
    typedef class__ this_class_t;\
    typedef event_handler base_class_t;\
    typedef void(event_handler::*event_mem_func)(void*);\
    struct event {unsigned eid; event_mem_func func;};\
    static const event s_efuncs[]={
#define PFC_EVENT_HANDLER_BEGIN(class__, base__)\
  template<class EH, typename E> friend void pfc::send_event(EH&, E&);\
  public:\
  virtual void dispatch_event(unsigned eid_, void *e_)\
  {\
    struct event_handler {};\
    typedef class__ this_class_t;\
    typedef base__ base_class_t;\
    typedef void(event_handler::*event_mem_func)(void*);\
    struct event {unsigned eid; event_mem_func func;};\
    static const event s_efuncs[]={
#define PFC_EVENT_HANDLER_END\
    {0, 0}};\
    enum {num_events=PFC_CARRAY_SIZE(s_efuncs)-1};\
    if(num_events)\
    {\
      unsigned i=0;\
      do\
      {\
        if(s_efuncs[i].eid==eid_)\
          return (this->*((void(this_class_t::*)(void*))s_efuncs[i].func))(e_);\
      } while(++i<num_events);\
    }\
    base_class_t::dispatch_event(eid_, e_);\
  }\
  private:
#define PFC_EVENT(event__) {pfc::type_id<event__ >::id, event_mem_func(static_cast<void(this_class_t::*)(event__&)>(&this_class_t::handle_event))},
//----------------------------------------------------------------------------


//============================================================================
// raw_cast_union
//============================================================================
template<typename T, typename U>
union raw_cast_union
{
  T first;
  U second;
};
//----------------------------------------------------------------------------


//============================================================================
// owner_ptr
//============================================================================
template<typename T>
class owner_ptr
{ PFC_MONO(owner_ptr) {pe_.var(v_.data, mvarflag_mutable|mvarflag_mutable_ptr, 0, v_);/*todo: add "collapse" flag for proper implementation*/}
public:
  // nested types
  typedef T type;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE owner_ptr();
  PFC_INLINE owner_ptr(T*);
  PFC_INLINE owner_ptr(const owner_ptr&);
  template<typename U> PFC_INLINE owner_ptr(const owner_ptr<U>&);
  template<typename U> PFC_INLINE owner_ptr(const owner_ref<U>&);
  PFC_INLINE void operator=(T*);
  PFC_INLINE void operator=(const owner_ptr&);
  template<typename U> PFC_INLINE void operator=(const owner_ptr<U>&);
  template<typename U> PFC_INLINE void operator=(const owner_ref<U>&);
  PFC_INLINE ~owner_ptr();
  //--------------------------------------------------------------------------
  
  // accessors
  PFC_INLINE friend bool is_valid(const owner_ptr &ptr_)  {return ptr_.data!=0;}
  PFC_INLINE T *operator->() const;
  PFC_INLINE T &operator*() const;
  PFC_INLINE friend T *ptr(const owner_ptr &ptr_)         {return ptr_.data;}
  //--------------------------------------------------------------------------

  mutable T *data;
};
//----------------------------------------------------------------------------


//============================================================================
// owner_ref
//============================================================================
template<typename T>
class owner_ref
{ PFC_MONO(owner_ref) {pe_.var(v_.data, mvarflag_mutable|mvarflag_mutable_ptr, 0, v_);/*todo: add "collapse" flag for proper implementation*/}
public:
  // nested types
  typedef T type;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE owner_ref(T*);
  PFC_INLINE owner_ref(const owner_ref&);
  template<typename U> PFC_INLINE owner_ref(const owner_ref<U>&);
  template<typename U> PFC_INLINE owner_ref(const owner_ptr<U>&);
  PFC_INLINE ~owner_ref();
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE T *operator->() const;
  PFC_INLINE T &operator*() const;
  PFC_INLINE friend T *ptr(const owner_ref &ref_)  {return ref_.data;}
  //--------------------------------------------------------------------------

  mutable T *data;
  //--------------------------------------------------------------------------

private:
  void operator=(const owner_ref&); // not implemented
};
//----------------------------------------------------------------------------


//============================================================================
// owner_data
//============================================================================
class owner_data
{
public:
  // construction
  PFC_INLINE owner_data();
  PFC_INLINE owner_data(void*);
  PFC_INLINE owner_data(const owner_data&);
  PFC_INLINE void operator=(void*);
  PFC_INLINE void operator=(const owner_data&);
  PFC_INLINE ~owner_data();
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE friend bool is_valid(const owner_data &data_)  {return data_.data!=0;}
  PFC_INLINE friend void *ptr(const owner_data &data_)      {return data_.data;}
  //--------------------------------------------------------------------------

  mutable void *data;
};
//----------------------------------------------------------------------------


//============================================================================
// eh_data
//============================================================================
template<typename T>
class eh_data
{
public:
  // construction
  PFC_INLINE eh_data(memory_allocator_base&, usize_t size_, usize_t align_); /* todo: instead of passing alignment, should use meta_alignof<T>::res in implementation, but not done due to meta.h dependency*/
  PFC_INLINE ~eh_data();
  PFC_INLINE void reset();
  //--------------------------------------------------------------------------

  T *data;
  //--------------------------------------------------------------------------

private:
  eh_data(const eh_data&); // not implemented
  void operator=(const eh_data&); // not implemented
  //--------------------------------------------------------------------------

#ifdef PFC_BUILDOP_EXCEPTIONS
  memory_allocator_base &m_allocator;
#endif
};
//----------------------------------------------------------------------------


//============================================================================
// eh_dtor
//============================================================================
#ifdef PFC_BUILDOP_EXCEPTIONS
#define PFC_EDTOR(dtor__, method__) pfc::eh_dtor exception_destructor(dtor__, method__)
#define PFC_EDTOR_RESET() {exception_destructor.reset();}
#else
#define PFC_EDTOR(dtor__, method__) {}
#define PFC_EDTOR_RESET() {}
#endif
//----------------------------------------------------------------------------

class eh_dtor
{
public:
  // construction
  template<typename T> PFC_INLINE eh_dtor(T &dtor_, void(T::*method_)());
  PFC_INLINE ~eh_dtor();
  PFC_INLINE void reset();
  //--------------------------------------------------------------------------

private:
#ifdef PFC_BUILDOP_EXCEPTIONS
  eh_dtor *m_dtor;
  void(eh_dtor::*m_method)();
#endif
};
//----------------------------------------------------------------------------


//============================================================================
// eh_array_dtor
//============================================================================
template<typename T>
struct eh_array_dtor
{
  // destruction
  PFC_INLINE eh_array_dtor();
  PFC_INLINE eh_array_dtor(T *begin_, T *dst_);
  PFC_INLINE ~eh_array_dtor();
  //----

  T *begin, *dst;
};
//----------------------------------------------------------------------------


//============================================================================
// raw_data
//============================================================================
struct raw_data
{ PFC_MONO(raw_data) PFC_INTROSPEC_DECL;
  // construction
  PFC_INLINE raw_data();
  PFC_INLINE raw_data(usize_t bytes_);
  PFC_INLINE ~raw_data();
  PFC_INLINE void alloc(usize_t num_bytes_);
  PFC_INLINE void free();
  PFC_INLINE void swap(raw_data&);
  //--------------------------------------------------------------------------

  usize_t size;
  void *data;
  //--------------------------------------------------------------------------

private:
  raw_data(const raw_data&); // not implemented
  void operator=(const raw_data&); // not implemented
};
//----------------------------------------------------------------------------


//============================================================================
// definit_var
//============================================================================
template<typename T>
struct definit_var
{
  // construction
  PFC_INLINE definit_var();
  //--------------------------------------------------------------------------

  T value;
};
//----------------------------------------------------------------------------


//============================================================================
// uninit_var
//============================================================================
template<typename T>
class uninit_var
{
public:
  // construction
  PFC_INLINE uninit_var();
  PFC_INLINE ~uninit_var();
  template<typename U> PFC_INLINE void *new_data();
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE bool is_initialized() const;
  PFC_INLINE operator T&();
  PFC_INLINE T &ref();
  PFC_INLINE operator const T&() const;
  PFC_INLINE const T &ref() const;
  //--------------------------------------------------------------------------

private:
  struct align_hlp {align_hlp(); void operator=(const align_hlp&); char x; T y;};
  typedef typename align_type<sizeof(align_hlp)-sizeof(T)>::res storage_t;
  char m_is_initialized;
  storage_t m_data[(sizeof(T)+sizeof(storage_t)-1)/sizeof(storage_t)];
};
#define PFC_PNEW_UVAR(var__, type__) PFC_PNEW(var__.new_data<type__>())type__
//----------------------------------------------------------------------------


//============================================================================
// enumerated value string
//============================================================================
#define PFC_ENUM(etype__) PFC_INLINE const char *enum_type_name(etype__) {return #etype__;}\
                          const char *const*enum_strings(etype__);\
                          const char *const*enum_display_strings(etype__);\
                          const etype__ *enum_values(etype__);\
                          unsigned enum_string_index(etype__);\
                          bool enum_dep_value(etype__&, const char *enum_str_)
#define PFC_CLASS_ENUM(etype__) PFC_INLINE friend const char *enum_type_name(etype__) {return #etype__;}\
                                friend const char *const*enum_strings(etype__);\
                                friend const char *const*enum_display_strings(etype__);\
                                friend const etype__ *enum_values(etype__);\
                                friend unsigned enum_string_index(etype__);\
                                friend bool enum_dep_value(etype__&, const char *enum_str_)
template<typename T> PFC_INLINE const char *enum_string(T);
template<typename T> PFC_INLINE const char *enum_display_string(T);
template<typename T> PFC_INLINE bool enum_value(T&, const char*);
//----

template<typename T> PFC_INLINE const char *enum_type_name(T)             {PFC_STATIC_ERROR(T, use_of_undefined_enum_type); return 0;} // if you get the error here, the enum type isn't defined with PFC_ENUM() macro
template<typename T> PFC_INLINE const char *const*enum_strings(T)         {PFC_STATIC_ERROR(T, use_of_undefined_enum_type); return 0;}
template<typename T> PFC_INLINE const char *const*enum_display_strings(T) {PFC_STATIC_ERROR(T, use_of_undefined_enum_type); return 0;}
template<typename T> PFC_INLINE const T *enum_values(T)                   {PFC_STATIC_ERROR(T, use_of_undefined_enum_type); return 0;}
template<typename T> PFC_INLINE unsigned enum_string_index(T)             {PFC_STATIC_ERROR(T, use_of_undefined_enum_type); return 0;}
template<typename T> PFC_INLINE bool enum_dep_value(T&, const char*)      {PFC_STATIC_ERROR(T, use_of_undefined_enum_type); return 0;}
//----------------------------------------------------------------------------


//============================================================================
// timing and sleeping
//============================================================================
PFC_INLINE uint64_t get_thread_cycles();
udouble_t get_global_time();
PFC_INLINE void thread_nap();
PFC_INLINE void thread_sleep(ufloat_t time_);
//----------------------------------------------------------------------------


//============================================================================
// perf_timer
//============================================================================
#ifdef PFC_BUILDOP_PROFILING
#define PFC_PERF_TIMERS_ENABLE() {++perf_timer::s_enable_timers;}
#define PFC_PERF_TIMERS_DISABLE() {--perf_timer::s_enable_timers;}
#define PFC_PERF_TIMER(timer__, group__, name__) static PFC_THREAD_VAR pfc::perf_timer s_timer_##timer__={group__, name__, 0, 0.0, 0.0, 0, false, 0, 0}
#define PFC_PERF_TIMER_START(timer__) {s_timer_##timer__.start();}
#define PFC_PERF_TIMER_PAUSE(timer__) {s_timer_##timer__.pause();}
#define PFC_PERF_TIMER_STOP(timer__) {s_timer_##timer__.stop();}
#define PFC_PERF_TIMER_SCOPE(timer__) pfc::perf_timer::toggle perf_timer##__LINE__(s_timer_##timer__)
#define PFC_PERF_TIMER_AUTO(timer__, group__, name__) static PFC_THREAD_VAR pfc::perf_timer s_timer_##timer__={group__, name__, 0, 0.0, 0.0, 0, false, 0, 0}; pfc::perf_timer::toggle perf_timer##__LINE__(s_timer_##timer__)
#else
#define PFC_PERF_TIMERS_ENABLE() {}
#define PFC_PERF_TIMERS_DISABLE() {}
#define PFC_PERF_TIMER(timer__, group__, name__)
#define PFC_PERF_TIMER_START(timer__)  {}
#define PFC_PERF_TIMER_PAUSE(timer__)  {}
#define PFC_PERF_TIMER_STOP(timer__)   {}
#define PFC_PERF_TIMER_SCOPE(timer__)  {}
#define PFC_PERF_TIMER_AUTO(timer__, group__, name__)
#endif
//----------------------------------------------------------------------------

struct perf_timer
{
  // nested types
  class toggle;
  //--------------------------------------------------------------------------

  // construction & timing
  void init();
  static void refresh_all_timers();
  static const perf_timer *first_timer();
  static unsigned num_timers();
  static unsigned num_groups();
  PFC_INLINE void start();
  PFC_INLINE void pause();
  PFC_INLINE void stop();
  //--------------------------------------------------------------------------

  static int s_enable_timers;
  const char *group, *name;
  uint64_t num_cycles;
  ufloat_t time, peak_time, avg_time;
  unsigned peak_count;
  perf_timer *next;
  // private variables
  bool priv_is_initialized;
  uint64_t priv_start_cycles;
  ufloat_t priv_cur_peak_time;
  unsigned priv_frame_peak_count, priv_cur_peak_count;
  ufloat_t priv_total_time;
  perf_timer *priv_next;
};
//----------------------------------------------------------------------------

//============================================================================
// perf_timer::toggle
//============================================================================
class perf_timer::toggle
{
public:
  // construction
  PFC_INLINE toggle(perf_timer&);
  PFC_INLINE ~toggle();
  //--------------------------------------------------------------------------

private:
  toggle(const toggle&); // not implemented
  void operator=(const toggle&); // not implemented
  //--------------------------------------------------------------------------

  perf_timer &m_timer;
};
//----------------------------------------------------------------------------

//============================================================================
#include "core.inl"
} // namespace pfc
#endif
