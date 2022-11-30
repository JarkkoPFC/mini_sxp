//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_CLASS_H
#define PFC_CORE_CLASS_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "memory.h"
#include "streams.h"
namespace pfc
{

// new
enum {archive_version=0x1520}; // v1.52
template<typename> struct archive_mvar_type_id;
class class_factory_base;
template<class T> class class_factory;
class class_repository_base;
template<class B> class class_repository;
class object_repository_pool;
class object_repository_base;
template<class B> class object_repository;
template<class S> class prop_enum_input_archive;
template<class S> class prop_enum_output_archive;
class prop_enum_find_mvar;
class prop_enum_exposure_base;
// class accessors
template<typename T, class U> const T &find_mvar(const U&, const char *mvar_name_);
template<typename T, class U> T &find_mvar(U&, const char *mvar_name_, void(**post_mutate_func_)(void*));
#define PFC_SET_MVAR(object__, type__, mvar_name__, value__)\
  {\
    static PFC_THREAD_VAR void *s_cached_object=0; static PFC_THREAD_VAR type__ *s_cached_mvar=0; static PFC_THREAD_VAR void(*s_cached_post_mutate_func)(void*)=0;\
    if(s_cached_object!=&object__) {s_cached_object=&object__; s_cached_mvar=&pfc::find_mvar<type__ >(object__, mvar_name__"", &s_cached_post_mutate_func);}\
    *s_cached_mvar=value__;\
    if(s_cached_post_mutate_func)\
      (*s_cached_post_mutate_func)(s_cached_object);\
  }
#define PFC_GET_MVAR(object__, type__, mvar_name__, res__)\
  {\
    static PFC_THREAD_VAR const void *s_cached_object=0; static PFC_THREAD_VAR const type__ *s_cached_mvar=0;\
    if(s_cached_object!=&object__) {s_cached_object=&object__; s_cached_mvar=&pfc::find_mvar<type__ >(object__, mvar_name__"");}\
    res__=*s_cached_mvar;\
  }
// object pool management
PFC_INLINE object_repository_pool &add_object_pool(const char *name_, object_repository_pool *parent_=0, bool activate_=false);
PFC_INLINE void remove_object_pool(object_repository_pool&);
PFC_INLINE object_repository_pool *active_pool();
PFC_INLINE object_repository_pool *activate_object_pool(object_repository_pool*);
PFC_INLINE object_repository_pool *find_object_pool(const char *name_);
// repository management
PFC_INLINE const class_factory_base *find_mono_factory(const str_id&);
PFC_INLINE class_repository_base *find_class_repository(const str_id&);
PFC_INLINE object_repository_base *find_object_repository(const str_id&);
template<class B> PFC_INLINE void add_object(const str_id&, B&);
template<class B> PFC_INLINE void remove_object(B&);
template<class B> PFC_INLINE B *create_object(const str_id&);
template<class B> PFC_INLINE B *create_object();
template<class B> PFC_INLINE B *find_object(const str_id&);
template<class B> PFC_INLINE const str_id *find_object_name(const B&);
template<class B> PFC_INLINE B *load_object(const str_id&, const char *file_ext_=0, const char *path_=0);
template<class B> PFC_INLINE B *load_object(const str_id&, bin_input_stream_base&, const char *file_ext_=0, const char *path_=0);
template<class B> inline owner_ptr<B> read_object(const char *filename_, const char *file_ext_=0, const char *path_=0);
template<class B> inline owner_ptr<B> read_object(bin_input_stream_base&, const char *file_ext_=0, const char *path_=0);
template<class B> void save_object(const B&, const char *filename_, const char *path_=0, const char *custom_id_=0, bool save_type_info_=true, bool swap_endianness_=false);
template<class B> void save_object(const B&, bin_output_stream_base&, const char *custom_id_=0, bool save_type_info_=true, bool swap_endianness_=false);
#define PFC_CREATE_OBJECT(id__, ptr__)  {static const pfc::str_id s_id(id__); ptr__=ptr__->crep().create(s_id);}
#define PFC_FIND_OBJECT(id__, ptr__)    {static const pfc::str_id s_id(id__); ptr__=ptr__->orep().find_object(s_id);}
#define PFC_LOAD_OBJECT(id__, ptr__)    {static const pfc::str_id s_id(id__); ptr__=ptr__->orep().load_object(s_id);}
// class registration macros
#define PFC_REG_CLASS(reg__, class__) {if(reg__) pfc::register_class<class__ >(#class__, 0, pfc::meta_case<pfc::is_type_mono<class__ >::res?0:pfc::is_type_orep<class__ >::res?1:pfc::is_type_crep<class__ >::res?2:-1>());\
                                                 else pfc::unregister_class<class__ >(pfc::meta_case<pfc::is_type_mono<class__ >::res?0:pfc::is_type_crep<class__ >::res?1:-1>());}
#define PFC_REG_CLASS_ALIAS(reg__, class__, alias__) {if(reg__) pfc::register_class<class__ >(alias__, 0, pfc::meta_case<pfc::is_type_mono<class__ >::res?0:pfc::is_type_orep<class__ >::res?1:pfc::is_type_crep<class__ >::res?2:-1>());\
                                                                else pfc::unregister_class<class__ >(pfc::meta_case<pfc::is_type_mono<class__ >::res?0:pfc::is_type_crep<class__ >::res?1:-1>());}
#define PFC_REG_BASE_CLASS(reg__, class__) {if(reg__) pfc::register_base_class<class__ >(#class__, 0, pfc::meta_case<pfc::is_type_orep<class__ >::res?0:pfc::is_type_crep<class__ >::res?1:-1>());\
                                                      else pfc::unregister_base_class<class__ >(pfc::meta_bool<pfc::is_type_introspec<class__ >::res>());}
#define PFC_REG_CLASS_DEPNAME(reg__, class__, depname__) {if(reg__) pfc::register_class<class__ >(#class__, depname__, pfc::meta_case<pfc::is_type_mono<class__ >::res?0:pfc::is_type_orep<class__ >::res?1:pfc::is_type_crep<class__ >::res?2:-1>());\
                                                                    else pfc::unregister_class<class__ >(pfc::meta_case<pfc::is_type_mono<class__ >::res?0:pfc::is_type_crep<class__ >::res?1:-1>());}
#define PFC_REG_BASE_CLASS_DEPNAME(reg__, class__, depname__) {if(reg__) pfc::register_base_class<class__ >(#class__, depname__, pfc::meta_case<pfc::is_type_orep<class__ >::res?0:pfc::is_type_crep<class__ >::res?1:-1>());\
                                                                         else pfc::unregister_base_class<class__ >(pfc::meta_bool<pfc::is_type_introspec<class__ >::res>());}
#define PFC_REG_FWD_INTROSPEC(class__) {pfc::register_fwd_introspec<pfc::prop_enum_input_stream<pfc::bin_input_stream_base>, class__ >();\
                                        pfc::register_fwd_introspec<pfc::prop_enum_output_stream<pfc::bin_output_stream_base>, class__ >();\
                                        pfc::register_fwd_introspec<pfc::prop_enum_output_archive<pfc::bin_output_stream_base>, class__ >();\
                                        PFC_ENDIAN_REG_FWD_INTROSPEC(class__);\
                                        pfc::register_fwd_introspec<pfc::prop_enum_find_mvar, class__ >();\
                                        pfc::register_fwd_introspec<pfc::prop_enum_exposure_base, class__ >();}
// class forward registration macros
#define PFC_REG_CLASS_FWD(reg__, class__) pfc::register_class_fwd<class__ >(reg__)
#define PFC_REG_CLASS_FWD_DEF(class__) namespace pfc {template<> void register_class_fwd<class__ >(bool reg_) {PFC_REG_CLASS(reg_, class__);}}
#define PFC_REG_BASE_CLASS_FWD_DEF(class__) namespace pfc {template<> void register_class_fwd<class__ >(bool reg_) {PFC_REG_BASE_CLASS(reg_, class__);}}
#define PFC_REG_CLASS_DEPNAME_FWD_DEF(class__, depname__) namespace pfc {template<> void register_class_fwd<class__ >(bool reg_) {PFC_REG_CLASS_DEPNAME(reg_, class__, depname__);}}
#define PFC_REG_BASE_CLASS_DEPNAME_FWD_DEF(class__, depname__) namespace pfc {template<> void register_class_fwd<class__ >(bool reg_) {PFC_REG_BASE_CLASS_DEPNAME(reg_, class__, depname__);}}
#define PFC_PROP_ENUM_INTERFACE PFC_PROP_ENUM_DEF(prop_enum_input_stream<bin_input_stream_base>)\
                                PFC_PROP_ENUM_DEF(prop_enum_output_stream<bin_output_stream_base>)\
                                PFC_PROP_ENUM_DEF(prop_enum_input_archive<bin_input_stream_base>)\
                                PFC_PROP_ENUM_DEF(prop_enum_output_archive<bin_output_stream_base>)\
                                PFC_PROP_ENUM_DEF(prop_enum_output_archive<bin_output_stream_base>::prop_enum_type_info)\
                                PFC_PROP_ENUM_DEF(class_factory_base::prop_enum_input_converter<bin_input_stream_base>)\
                                PFC_PROP_ENUM_DEF(prop_enum_find_mvar)\
                                PFC_PROP_ENUM_DEF(prop_enum_exposure_base)\
                                PFC_ENDIAN_PROP_ENUM_INTERFACE
// class definition macros
#define PFC_BASE_CLASS(class__) public:\
                                typedef class__ this_class_t;\
                                typedef this_class_t base_class_t;\
                                typedef void parent_class_t;\
                                friend class pfc::class_factory<this_class_t>;\
                                static PFC_INLINE pfc::class_repository<this_class_t> &crep()                                        {return pfc::class_repository<this_class_t>::instance(pfc::class_reg_info<this_class_t>::reg_name);}\
                                friend PFC_INLINE const char *class_typename(this_class_t*)                                          {return #class__;}\
                                friend PFC_INLINE const char *registered_class_typename(this_class_t*)                               {return pfc::class_reg_info<this_class_t>::reg_name;}\
                                friend PFC_INLINE unsigned subclass_type_ids(this_class_t*, unsigned *ids_)                          {*ids_=pfc::type_id<this_class_t>::id; return 1;}\
                                friend int has_class_introspection(pfc::has_class_trait<const volatile this_class_t>)                {return 0;}\
                                friend int has_class_repository(pfc::has_class_trait<const volatile this_class_t>)                   {return 0;}\
                                friend unsigned object_type_id(const this_class_t &v_)                                               {return v_.object_type_id();}\
                                friend const char *object_typename(const this_class_t &v_)                                           {return v_.object_typename();}\
                                friend const char *registered_object_typename(const this_class_t &v_)                                {return v_.registered_object_typename();}\
                                virtual unsigned object_type_id() const                                                              {return pfc::type_id<this_class_t>::id;}\
                                virtual const char *object_typename() const                                                          {return class_typename((this_class_t*)0);}\
                                virtual const char *registered_object_typename() const                                               {return registered_class_typename((this_class_t*)0);}\
                                virtual unsigned subobject_type_ids(unsigned *ids_) const                                            {*ids_=pfc::type_id<this_class_t>::id; return 1;}\
                                virtual void enum_props(pfc::prop_enum_input_stream<pfc::bin_input_stream_base> &pe_)                {enum_props_most_derived(pe_, *this);}\
                                virtual void enum_props(pfc::prop_enum_output_stream<pfc::bin_output_stream_base> &pe_) const        {enum_props_most_derived(pe_, const_cast<this_class_t&>(*this));}\
                                virtual void enum_props(pfc::prop_enum_output_archive<pfc::bin_output_stream_base> &pe_) const       {enum_props_most_derived(pe_, const_cast<this_class_t&>(*this));}\
                                virtual void set_object_type(pfc::prop_enum_output_archive<pfc::bin_output_stream_base> &pe_) const  {pe_.set_object_type(*this);}\
                                PFC_ENDIAN_CLASS();\
                                virtual void enum_props(pfc::prop_enum_find_mvar &pe_) const                                         {enum_props_most_derived(pe_, const_cast<this_class_t&>(*this));}\
                                virtual void enum_props(pfc::prop_enum_exposure_base &pe_) const                                     {enum_props_most_derived(pe_, const_cast<this_class_t&>(*this));}\
                                private:\
                                template<class PE> friend PFC_INLINE void enum_props(PE &pe_, this_class_t &v_)                      {v_.enum_props(pe_);}\
                                template<class PE> friend PFC_INLINE void enum_props_most_derived(PE &pe_, this_class_t &v_)         {if(pe_.subclass(&v_)) enum_props_this(pe_, v_);}\
                                template<class PE> friend PFC_INLINE void enum_props_this(PE &pe_, this_class_t &v_)
#define PFC_BASE_CLASS_DECL(class__) public:\
                                     typedef class__ this_class_t;\
                                     typedef this_class_t base_class_t;\
                                     typedef void parent_class_t;\
                                     friend class pfc::class_factory<this_class_t>;\
                                     static PFC_INLINE pfc::class_repository<this_class_t> &crep()                                      {return pfc::class_repository<this_class_t>::instance(pfc::class_reg_info<this_class_t>::reg_name);}\
                                     friend PFC_INLINE const char *class_typename(this_class_t*)                                        {return #class__;}\
                                     friend PFC_INLINE const char *registered_class_typename(this_class_t*)                             {return pfc::class_reg_info<this_class_t>::reg_name;}\
                                     friend PFC_INLINE unsigned subclass_type_ids(this_class_t*, unsigned *ids_)                        {*ids_=pfc::type_id<this_class_t>::id; return 1;}\
                                     friend int has_class_introspection(pfc::has_class_trait<const volatile this_class_t>)              {return 0;}\
                                     friend int has_class_repository(pfc::has_class_trait<const volatile this_class_t>)                 {return 0;}\
                                     friend unsigned object_type_id(const this_class_t &v_)                                             {return v_.object_type_id();}\
                                     friend const char *object_typename(const this_class_t &v_)                                         {return v_.object_typename();}\
                                     friend const char *registered_object_typename(const this_class_t &v_)                              {return v_.registered_object_typename();}\
                                     virtual unsigned object_type_id() const;\
                                     virtual const char *object_typename() const;\
                                     virtual const char *registered_object_typename() const;\
                                     virtual unsigned subobject_type_ids(unsigned *ids_) const;\
                                     virtual void enum_props(pfc::prop_enum_input_stream<pfc::bin_input_stream_base>&);\
                                     virtual void enum_props(pfc::prop_enum_output_stream<pfc::bin_output_stream_base>&) const;\
                                     virtual void enum_props(pfc::prop_enum_output_archive<pfc::bin_output_stream_base>&) const;\
                                     virtual void set_object_type(pfc::prop_enum_output_archive<pfc::bin_output_stream_base>&) const;\
                                     PFC_ENDIAN_CLASS_DECL();\
                                     virtual void enum_props(pfc::prop_enum_find_mvar&) const;\
                                     virtual void enum_props(pfc::prop_enum_exposure_base&) const;\
                                     private:\
                                     template<class PE> friend PFC_INLINE void enum_props(PE &pe_, this_class_t &v_)                    {v_.enum_props(pe_);}\
                                     template<class PE> friend PFC_INLINE void enum_props_most_derived(PE &pe_, this_class_t &v_)       {if(pe_.subclass(&v_)) enum_props_this(pe_, v_);}\
                                     template<class PE> friend PFC_INLINE void enum_props_this(PE &pe_, this_class_t &v_)
#define PFC_REPOSITORY_BASE_CLASS(class__) public:\
                                           definit_var<const char*> debug_object_name;\
                                           static PFC_INLINE pfc::object_repository<class__ > &orep() {static pfc::object_repository<class__ > &rep=pfc::object_repository<class__ >::instance(pfc::class_reg_info<class__ >::reg_name); return rep;}\
                                           friend int has_object_repository(pfc::has_class_trait<const volatile class__>);\
                                           PFC_BASE_CLASS(class__)
#define PFC_REPOSITORY_BASE_CLASS_DECL(class__) public:\
                                                definit_var<const char*> debug_object_name;\
                                                static PFC_INLINE pfc::object_repository<class__ > &orep() {static pfc::object_repository<class__ > &rep=pfc::object_repository<class__ >::instance(pfc::class_reg_info<class__ >::reg_name); return rep;}\
                                                friend int has_object_repository(pfc::has_class_trait<const volatile class__>);\
                                                PFC_BASE_CLASS_DECL(class__)
#define PFC_CLASS(class__, parent__) public:\
                                     typedef class__ this_class_t;\
                                     typedef parent__ parent_class_t;\
                                     friend class pfc::class_factory<this_class_t>;\
                                     friend PFC_INLINE const char *class_typename(this_class_t*)                                          {return #class__;}\
                                     friend PFC_INLINE const char *registered_class_typename(this_class_t*)                               {return pfc::class_reg_info<this_class_t>::reg_name;}\
                                     friend PFC_INLINE unsigned subclass_type_ids(this_class_t*, unsigned *ids_)                          {*ids_=pfc::type_id<this_class_t>::id; return subclass_type_ids((parent__*)0, ids_+1)+1;}\
                                     friend int has_class_introspection(pfc::has_class_trait<const volatile this_class_t>)                {return 0;}\
                                     friend int has_class_repository(pfc::has_class_trait<const volatile this_class_t>)                   {return 0;}\
                                     friend unsigned object_type_id(const this_class_t &v_)                                               {return v_.object_type_id();}\
                                     friend const char *object_typename(const this_class_t &v_)                                           {return v_.object_typename();}\
                                     friend const char *registered_object_typename(const this_class_t &v_)                                {return v_.registered_object_typename();}\
                                     virtual unsigned object_type_id() const                                                              {return pfc::type_id<this_class_t>::id;}\
                                     virtual const char *object_typename() const                                                          {return class_typename((this_class_t*)0);}\
                                     virtual const char *registered_object_typename() const                                               {return registered_class_typename((this_class_t*)0);}\
                                     virtual unsigned subobject_type_ids(unsigned *ids_) const                                            {return subclass_type_ids((this_class_t*)0, ids_);}\
                                     virtual void enum_props(pfc::prop_enum_input_stream<pfc::bin_input_stream_base> &pe_)                {enum_props_most_derived(pe_, *this);}\
                                     virtual void enum_props(pfc::prop_enum_output_stream<pfc::bin_output_stream_base> &pe_) const        {enum_props_most_derived(pe_, const_cast<this_class_t&>(*this));}\
                                     virtual void enum_props(pfc::prop_enum_output_archive<pfc::bin_output_stream_base> &pe_) const       {enum_props_most_derived(pe_, const_cast<this_class_t&>(*this));}\
                                     virtual void set_object_type(pfc::prop_enum_output_archive<pfc::bin_output_stream_base> &pe_) const  {pe_.set_object_type(*this);}\
                                     PFC_ENDIAN_CLASS();\
                                     virtual void enum_props(pfc::prop_enum_find_mvar &pe_) const                                         {enum_props_most_derived(pe_, const_cast<this_class_t&>(*this));}\
                                     virtual void enum_props(pfc::prop_enum_exposure_base &pe_) const                                     {enum_props_most_derived(pe_, const_cast<this_class_t&>(*this));}\
                                     private:\
                                     template<class PE> friend PFC_INLINE void enum_props(PE &pe_, this_class_t &v_)                      {v_.enum_props(pe_);}\
                                     template<class PE> friend PFC_INLINE void enum_props_most_derived(PE &pe_, this_class_t &v_)         {enum_props_most_derived(pe_, static_cast<parent__&>(v_)); if(pe_.subclass(&v_)) enum_props_this(pe_, v_);}\
                                     template<class PE> friend PFC_INLINE void enum_props_this(PE &pe_, this_class_t &v_)
#define PFC_CLASS_DECL(class__, parent__) public:\
                                          typedef class__ this_class_t;\
                                          typedef parent__ parent_class_t;\
                                          friend class pfc::class_factory<this_class_t>;\
                                          friend PFC_INLINE const char *class_typename(this_class_t*)                                        {return #class__;}\
                                          friend PFC_INLINE const char *registered_class_typename(this_class_t*)                             {return pfc::class_reg_info<this_class_t>::reg_name;}\
                                          friend PFC_INLINE unsigned subclass_type_ids(this_class_t*, unsigned *ids_)                        {*ids_=pfc::type_id<this_class_t>::id; return subclass_type_ids((parent__*)0, ids_+1)+1;}\
                                          friend int has_class_introspection(pfc::has_class_trait<const volatile this_class_t>)              {return 0;}\
                                          friend int has_class_repository(pfc::has_class_trait<const volatile this_class_t>)                 {return 0;}\
                                          friend unsigned object_type_id(const this_class_t &v_)                                             {return v_.object_type_id();}\
                                          friend const char *object_typename(const this_class_t &v_)                                         {return v_.object_typename();}\
                                          friend const char *registered_object_typename(const this_class_t &v_)                              {return v_.registered_object_typename();}\
                                          virtual unsigned object_type_id() const;\
                                          virtual const char *object_typename() const;\
                                          virtual const char *registered_object_typename() const;\
                                          virtual unsigned subobject_type_ids(unsigned *ids_) const;\
                                          virtual void enum_props(pfc::prop_enum_input_stream<pfc::bin_input_stream_base>&);\
                                          virtual void enum_props(pfc::prop_enum_output_stream<pfc::bin_output_stream_base>&) const;\
                                          virtual void enum_props(pfc::prop_enum_output_archive<pfc::bin_output_stream_base>&) const;\
                                          virtual void set_object_type(pfc::prop_enum_output_archive<pfc::bin_output_stream_base>&) const;\
                                          PFC_ENDIAN_CLASS_DECL();\
                                          virtual void enum_props(pfc::prop_enum_find_mvar&) const;\
                                          virtual void enum_props(pfc::prop_enum_exposure_base&) const;\
                                          private:\
                                          template<class PE> friend PFC_INLINE void enum_props(PE &pe_, this_class_t &v_)                    {v_.enum_props(pe_);}\
                                          template<class PE> friend PFC_INLINE void enum_props_most_derived(PE &pe_, this_class_t &v_)       {enum_props_most_derived(pe_, static_cast<parent__&>(v_)); if(pe_.subclass(&v_)) enum_props_this(pe_, v_);}\
                                          template<class PE> friend PFC_INLINE void enum_props_this(PE &pe_, this_class_t &v_)
#define PFC_CLASS_DEF(class__) unsigned class__::object_type_id() const                                                              {return pfc::type_id<this_class_t>::id;}\
                               const char *class__::object_typename() const                                                          {return class_typename((this_class_t*)0);}\
                               const char *class__::registered_object_typename() const                                               {return registered_class_typename((this_class_t*)0);}\
                               unsigned class__::subobject_type_ids(unsigned *ids_) const                                            {return subclass_type_ids((this_class_t*)0, ids_);}\
                               void class__::enum_props(pfc::prop_enum_input_stream<pfc::bin_input_stream_base> &pe_)                {enum_props_most_derived(pe_, *this);}\
                               void class__::enum_props(pfc::prop_enum_output_stream<pfc::bin_output_stream_base> &pe_) const        {enum_props_most_derived(pe_, const_cast<this_class_t&>(*this));}\
                               void class__::enum_props(pfc::prop_enum_output_archive<pfc::bin_output_stream_base> &pe_) const       {enum_props_most_derived(pe_, const_cast<this_class_t&>(*this));}\
                               void class__::set_object_type(pfc::prop_enum_output_archive<pfc::bin_output_stream_base> &pe_) const  {pe_.set_object_type(*this);}\
                               PFC_ENDIAN_CLASS_DEF(class__);\
                               void class__::enum_props(pfc::prop_enum_find_mvar &pe_) const                                         {enum_props_most_derived(pe_, const_cast<this_class_t&>(*this));}\
                               void class__::enum_props(pfc::prop_enum_exposure_base &pe_) const                                     {enum_props_most_derived(pe_, const_cast<this_class_t&>(*this));}
// endian support
#ifdef PFC_BUILDOP_ARCHIVE_ENDIAN_SUPPORT
#define PFC_ENDIAN_REG_FWD_INTROSPEC(class__) pfc::register_fwd_introspec<pfc::prop_enum_input_stream<pfc::endian_input_stream>, class__ >();\
                                              pfc::register_fwd_introspec<pfc::prop_enum_output_stream<pfc::endian_output_stream>, class__ >();\
                                              pfc::register_fwd_introspec<pfc::prop_enum_output_archive<pfc::endian_output_stream>, class__ >();
#define PFC_ENDIAN_CLASS() virtual void enum_props(pfc::prop_enum_input_stream<pfc::endian_input_stream> &pe_)                {enum_props_most_derived(pe_, *this);}\
                           virtual void enum_props(pfc::prop_enum_output_stream<pfc::endian_output_stream> &pe_) const        {enum_props_most_derived(pe_, const_cast<this_class_t&>(*this));}\
                           virtual void enum_props(pfc::prop_enum_output_archive<pfc::endian_output_stream> &pe_) const       {enum_props_most_derived(pe_, const_cast<this_class_t&>(*this));}\
                           virtual void set_object_type(pfc::prop_enum_output_archive<pfc::endian_output_stream> &pe_) const  {pe_.set_object_type(*this);}
#define PFC_ENDIAN_CLASS_DECL() virtual void enum_props(pfc::prop_enum_input_stream<pfc::endian_input_stream>&);\
                                virtual void enum_props(pfc::prop_enum_output_stream<pfc::endian_output_stream>&) const;\
                                virtual void enum_props(pfc::prop_enum_output_archive<pfc::endian_output_stream>&) const;\
                                virtual void set_object_type(pfc::prop_enum_output_archive<pfc::endian_output_stream>&) const
#define PFC_ENDIAN_CLASS_DEF(class__) void class__::enum_props(pfc::prop_enum_input_stream<pfc::endian_input_stream> &pe_)                {enum_props_most_derived(pe_, *this);}\
                                      void class__::enum_props(pfc::prop_enum_output_stream<pfc::endian_output_stream> &pe_) const        {enum_props_most_derived(pe_, const_cast<this_class_t&>(*this));}\
                                      void class__::enum_props(pfc::prop_enum_output_archive<pfc::endian_output_stream> &pe_) const       {enum_props_most_derived(pe_, const_cast<this_class_t&>(*this));}\
                                      void class__::set_object_type(pfc::prop_enum_output_archive<pfc::endian_output_stream> &pe_) const  {pe_.set_object_type(*this);}
#define PFC_ENDIAN_INTROSPEC_DEF(class__) template void class__::enum_props_impl(pfc::prop_enum_input_stream<pfc::endian_input_stream>&, class__&);\
                                          template void class__::enum_props_impl(pfc::prop_enum_output_stream<pfc::endian_output_stream>&, class__&);\
                                          template void class__::enum_props_impl(pfc::prop_enum_input_archive<pfc::endian_input_stream>&, class__&);\
                                          template void class__::enum_props_impl(pfc::prop_enum_output_archive<pfc::endian_output_stream>&, class__&);\
                                          template void class__::enum_props_impl(pfc::prop_enum_output_archive<pfc::endian_output_stream>::prop_enum_type_info&, class__&);\
                                          template void class__::enum_props_impl(pfc::class_factory_base::prop_enum_input_converter<pfc::endian_input_stream>&, class__&);
#define PFC_ENDIAN_PROP_ENUM_INTERFACE PFC_PROP_ENUM_DEF(prop_enum_input_stream<endian_input_stream>)\
                                       PFC_PROP_ENUM_DEF(prop_enum_output_stream<endian_output_stream>)\
                                       PFC_PROP_ENUM_DEF(prop_enum_input_archive<endian_input_stream>)\
                                       PFC_PROP_ENUM_DEF(prop_enum_output_archive<endian_output_stream>)\
                                       PFC_PROP_ENUM_DEF(prop_enum_output_archive<endian_output_stream>::prop_enum_type_info)\
                                       PFC_PROP_ENUM_DEF(class_factory_base::prop_enum_input_converter<endian_input_stream>)
#else
#define PFC_ENDIAN_REG_FWD_INTROSPEC(class__)
#define PFC_ENDIAN_CLASS()
#define PFC_ENDIAN_CLASS_DECL()
#define PFC_ENDIAN_CLASS_DEF(class__)
#define PFC_ENDIAN_INTROSPEC_DEF(class__)
#define PFC_ENDIAN_PROP_ENUM_INTERFACE
#endif
//----------------------------------------------------------------------------


//============================================================================
// archive config
//============================================================================
// stored archive types
typedef uint16_t archive_type_id_t;
typedef uint16_t archive_subclass_version_t;
typedef uint32_t archive_array_size_t;
typedef uint32_t archive_object_size_t;
typedef uint32_t archive_pointer_t;
typedef int32_t archive_enum_t;
typedef uint8_t archive_bool_t;
typedef pair<archive_type_id_t, const char*> class_mvar_t;
// archive type id
enum e_archive_type_id
{
  archtype_subclass=0xfffe,
  archtype_subclass_custom=0xffff,
  archtype_class_start=32,
  archtype_flag_array=0x8000,
};
// archive flags
enum e_archive_flag
{
  archflag_type_info =0x0001,
};
// class flags
enum e_class_flag
{
  classflag_var_csig =0x01,
};
//----------------------------------------------------------------------------


//============================================================================
// class_factory_base
//============================================================================
class class_factory_base
{
public:
  // nested
  template<class S> class prop_enum_input_converter;
  //--------------------------------------------------------------------------

  // construction
  virtual PFC_INLINE ~class_factory_base()=0;
  virtual void *create() const=0;
  virtual void create(void*) const=0;
  virtual void create(void**, usize_t num_objects_) const=0;
  virtual void read(prop_enum_input_archive<bin_input_stream_base>&, void**, usize_t num_objects_, const class_mvar_t *mvars_, unsigned num_mvars_, const uint16_t *csub_vers_) const=0;
#ifdef PFC_BUILDOP_ARCHIVE_ENDIAN_SUPPORT
  virtual void read(prop_enum_input_archive<endian_input_stream>&, void**, usize_t num_objects_, const class_mvar_t *mvars_, unsigned num_mvars_, const uint16_t *csub_vers_) const=0;
#endif
  virtual void post_load(void**, usize_t num_objects_) const=0;
  //--------------------------------------------------------------------------

  // accessors
  virtual unsigned subobject_type_ids(unsigned*) const=0;
#ifdef PFC_BUILDOP_ASSERTS
  virtual const char *assert_class_name() const=0;
#endif
};
//----------------------------------------------------------------------------


//============================================================================
// class_factory
//============================================================================
template<class T>
class class_factory: public class_factory_base
{
public:
  // class construction
  virtual void *create() const;
  virtual void create(void*) const;
  virtual void create(void**, usize_t num_objects_) const;
  virtual void read(prop_enum_input_archive<bin_input_stream_base> &pe_, void **objs_, usize_t num_objects_, const class_mvar_t *mvars_, unsigned num_mvars_, const uint16_t *csub_vers_) const  {read_impl(pe_, objs_, num_objects_, mvars_, num_mvars_, csub_vers_);}
#ifdef PFC_BUILDOP_ARCHIVE_ENDIAN_SUPPORT
  virtual void read(prop_enum_input_archive<endian_input_stream> &pe_, void **objs_, usize_t num_objects_, const class_mvar_t *mvars_, unsigned num_mvars_, const uint16_t *csub_vers_) const    {read_impl(pe_, objs_, num_objects_, mvars_, num_mvars_, csub_vers_);}
#endif
  virtual void post_load(void**, usize_t num_objects_) const;
  //--------------------------------------------------------------------------

  // accessors
  virtual unsigned subobject_type_ids(unsigned*) const;
#ifdef PFC_BUILDOP_ASSERTS
  virtual const char *assert_class_name() const;
#endif
  //--------------------------------------------------------------------------

private:
  template<class S> PFC_INLINE void read_impl(prop_enum_input_archive<S>&, void**, usize_t num_objects_, const class_mvar_t *mvars_, unsigned num_mvars_, const uint16_t *csub_vers_) const;
};
//----------------------------------------------------------------------------


//============================================================================
// class_repository_base
//============================================================================
class class_repository_base
{
public:
  // construction
  void remove(const str_id&, const char *deprecated_name_);
  static void shutdown_repositories();
  //--------------------------------------------------------------------------

  // accessors
  typedef hash_map<str_id, const class_factory_base*>::const_iterator const_iterator;
  static PFC_INLINE class_repository_base *find_repository(const str_id&);
  const PFC_INLINE class_factory_base *find_factory(const str_id&) const;
  PFC_INLINE const_iterator first_factory() const;
  PFC_INLINE unsigned num_factories() const;
  //--------------------------------------------------------------------------

protected:
  // construction
  PFC_INLINE class_repository_base(const str_id&);
  PFC_INLINE ~class_repository_base();
  void add_factory(const str_id&, const class_factory_base&);
  //--------------------------------------------------------------------------

private:
  void operator=(const class_repository_base&); // not implemented
  //--------------------------------------------------------------------------

  static hash_map<str_id, class_repository_base*> s_repository_map;
  hash_map<str_id, const class_factory_base*> m_factories;
};
//----------------------------------------------------------------------------


//============================================================================
// class_repository
//============================================================================
template<class B>
class class_repository: public class_repository_base
{
public:
  // class construction
  static PFC_INLINE class_repository &instance(const str_id&);
  template<class C> PFC_INLINE void add(const str_id&, const char *deprecated_name_, meta_type<C>);
  PFC_INLINE B *create(const str_id&);
  //--------------------------------------------------------------------------

private:
  // construction
  PFC_INLINE class_repository(const str_id&);
  PFC_INLINE ~class_repository();
};
//----------------------------------------------------------------------------


//============================================================================
// object_repository_pool
//============================================================================
class object_repository_pool
{
public:
  // construction
  PFC_INLINE object_repository_pool();
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE object_repository_pool *parent() const;
  //--------------------------------------------------------------------------

private:
  friend class object_repository_base;
  heap_str m_name;
  deque<hash_bimap<str_id, void*> > m_containers;
  str_pool m_strings;
  object_repository_pool *m_parent;
};
//----------------------------------------------------------------------------


//============================================================================
// object_repository_base
//============================================================================
class object_repository_base
{
public:
  // construction
  static void shutdown_repositories();
  //--------------------------------------------------------------------------

  // pool management
  static object_repository_pool &add_pool(const char *name_, object_repository_pool *parent_=0);
  static void remove_pool(object_repository_pool&);
  static void remove_all_pools();
  static object_repository_pool *active_pool();
  static object_repository_pool *activate_pool(object_repository_pool*);
  static object_repository_pool *find_pool(const char *name_);
  //--------------------------------------------------------------------------

  // accessors
  static object_repository_base *find_repository(const str_id&);
  void *find_object(const str_id&) const;
  const str_id *find_object_name(const void*) const;
  void *load_object(const str_id&, const char *file_ext_=0, const char *path_=0, unsigned type_id_=0);
  void *load_object(const str_id&, bin_input_stream_base&, const char *file_ext_=0, const char *path_=0, unsigned type_id_=0);
  //--------------------------------------------------------------------------

protected:
  // construction
  typedef hash_bimap<str_id, void*> repository_container;
  object_repository_base(const str_id&);
  ~object_repository_base();
  virtual const char *add_object(const str_id&, void*);
  virtual void remove_object(void*);
  virtual void clear_container(repository_container&)=0;
  //--------------------------------------------------------------------------

private:
  object_repository_base(const object_repository_base&); // not implemented
  void operator=(const object_repository_base&); // not implemented
  //--------------------------------------------------------------------------

  static hash_map<str_id, object_repository_base*> s_repository_map;
  static deque<object_repository_base*> s_repositories;
  static list<object_repository_pool> s_pools;
  static object_repository_pool *s_active_pool;
  const str_id m_name;
  const unsigned m_index;
};
//----------------------------------------------------------------------------


//============================================================================
// object_repository
//============================================================================
template<class B>
class object_repository: public object_repository_base
{
public:
  // accessors
  static PFC_INLINE object_repository &instance(const str_id&);
  PFC_INLINE void add_object(const str_id&, B&);
  PFC_INLINE void remove_object(B&);
  PFC_INLINE B *find_object(const str_id&) const;
  PFC_INLINE B *load_object(const str_id&, const char *file_ext_=0, const char *path_=0);
  PFC_INLINE B *load_object(const str_id&, bin_input_stream_base&, const char *file_ext_=0, const char *path_=0);
  //--------------------------------------------------------------------------

private:
  // construction
  PFC_INLINE object_repository(const str_id&);
  PFC_INLINE ~object_repository();
  virtual const char *add_object(const str_id&, void*);
  virtual void remove_object(void*);
  virtual void clear_container(repository_container&);
};
//----------------------------------------------------------------------------


//============================================================================
// prop_enum_input_archive
//============================================================================
template<class S>
class prop_enum_input_archive: public prop_enum_interface_base<prop_enum_input_archive<S> >
{
public:
  // construction
  enum {pe_type=penum_input};
  prop_enum_input_archive(S&, const char *file_ext_=0, const char *path_=0);
  PFC_INLINE void reset();
  PFC_INLINE S &stream() const;
  PFC_INLINE const class_mvar_t *composite_type_info(archive_type_id_t typeid_, unsigned &num_mvars_, const uint16_t *&csub_vers_) const;
  PFC_INLINE bool has_type_info() const;
  //--------------------------------------------------------------------------

  // serialization
  PFC_INLINE void *root_object(unsigned type_id_);
  template<class T> PFC_INLINE bool subclass(T*);
  template<class T> PFC_INLINE unsigned set_custom_streaming(T&, unsigned version_);
  template<typename T> PFC_INLINE bool var(T&, unsigned flags_=0, const char *mvar_name_=0);
  template<typename T, class C> PFC_INLINE bool var(T&, unsigned flags_, const char *mvar_name_, C&);
  template<typename T, class C> PFC_INLINE bool var(T&, unsigned flags_, const char *mvar_name_, C&, void(*post_mutate_func_)(C*));
  template<typename T, class C> PFC_INLINE bool var(T&, unsigned flags_, const char *mvar_name_, C&, void(C::*mutate_func_)(const T&, unsigned var_index_), unsigned var_index_);
  template<typename T> PFC_INLINE bool avar(T*, usize_t size_, unsigned flags_=0, const char *mvar_name_=0);
  template<typename T, class C> PFC_INLINE bool avar(T*, usize_t size_, unsigned flags_, const char *mvar_name_, C&);
  template<typename T, class C> PFC_INLINE bool avar(T*, usize_t size_, unsigned flags_, const char *mvar_name_, C&, void(*post_mutate_func_)(C*));
  template<typename T, class C> PFC_INLINE bool avar(T*, usize_t size_, unsigned flags_, const char *mvar_name_, C&, void(C::*mutate_func_)(const T&, unsigned index_, unsigned var_index_), unsigned var_index_);
  PFC_INLINE bool data(void*, usize_t num_bytes_);
  PFC_INLINE void skip(usize_t num_bytes_);
  //--------------------------------------------------------------------------

private:
  //==========================================================================
  // class_info
  //==========================================================================
  struct class_info
  {
    const class_factory_base *factory;
    uint8_t flags; // e_class_flag
    usize_t num_instancies;
    usize_t total_bytes;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // composite_class_sig
  //==========================================================================
  struct composite_class_sig
  {
    uint16_t num_mvars;
    const class_mvar_t *mvars;
    uint16_t *csub_vers;
  };
  //--------------------------------------------------------------------------

  void operator=(const prop_enum_input_archive&); // not implemented
  stack_str16 version_str(uint16_t ver_) const;
  unsigned read_type_info(class_mvar_t *mvars_, uint16_t *csub_vers_, char *mvar_str_buf_);
  PFC_INLINE void stream(bool&, meta_case<0> is_type_bool_);
  template<typename T> PFC_INLINE void stream(T&, meta_case<1> is_type_fund_);
  template<typename T> PFC_INLINE void stream(T&, meta_case<2> is_type_enum_);
  template<typename T> PFC_INLINE void stream(T&, meta_case<3> is_type_class_);
  template<typename T> PFC_INLINE void stream(T*&, meta_case<4> is_type_ptr_);
  template<typename T> PFC_INLINE void stream(T&, meta_case<-1> default_);
  //--------------------------------------------------------------------------

  S &m_stream;
  bool m_has_type_info;
  bool m_custom_streaming;
  archive_pointer_t m_root_idx;
  const class_factory_base *m_root_factory;
  unsigned m_num_composite_sigs;
  const composite_class_sig *m_composite_sigs;
  array<void*> m_objects;
};
//----------------------------------------------------------------------------


//============================================================================
// prop_enum_output_archive
//============================================================================
template<class S>
class prop_enum_output_archive: public prop_enum_interface_base<prop_enum_output_archive<S> >
{
public:
  // nested
  class prop_enum_type_info;
  //--------------------------------------------------------------------------

  // construction
  enum {pe_type=penum_output};
  prop_enum_output_archive(S&, bool save_type_info_);
  //--------------------------------------------------------------------------

  // serialization
  template<class T> void write(const T&, const char *custom_id_=0);
  template<class T> PFC_INLINE bool subclass(T*);
  template<class T> PFC_INLINE unsigned set_custom_streaming(T&, unsigned version_);
  template<typename T> bool var(const T&, unsigned flags_=0, const char *mvar_name_=0);
  template<typename T, class C> PFC_INLINE bool var(const T&, unsigned flags_, const char *mvar_name_, C&);
  template<typename T, class C> PFC_INLINE bool var(const T&, unsigned flags_, const char *mvar_name_, C&, void(*post_mutate_func_)(C*));
  template<typename T, class C> PFC_INLINE bool var(const T&, unsigned flags_, const char *mvar_name_, C&, void(C::*mutate_func_)(const T&, unsigned var_index_), unsigned var_index_);
  template<typename T> bool avar(const T*, usize_t size_, unsigned flags_=0, const char *mvar_name_=0);
  template<typename T, class C> PFC_INLINE bool avar(const T*, usize_t size_, unsigned flags_, const char *mvar_name_, C&);
  template<typename T, class C> PFC_INLINE bool avar(const T*, usize_t size_, unsigned flags_, const char *mvar_name_, C&, void(*post_mutate_func_)(C*));
  template<typename T, class C> PFC_INLINE bool avar(const T*, usize_t size_, unsigned flags_, const char *mvar_name_, C&, void(C::*mutate_func_)(const T&, unsigned index_, unsigned var_index_), unsigned var_index_);
  PFC_INLINE bool data(const void*, usize_t num_bytes_);
  template<class T> PFC_INLINE void set_object_type(const T&);
  //--------------------------------------------------------------------------

private:
  void operator=(const prop_enum_output_archive&); // not implemented
  template<typename> struct type_info;
  struct composite_type_base;
  template<class> struct composite_type;
  class prop_enum_custom_counter;
  struct ptr_mvar;
  struct object_entry;
  struct ptr_type_base;
  template<typename> class ptr_type_internal;
  template<typename> class ptr_type_external;
  struct ptr_rep_base;
  template<class> class ptr_rep;
  PFC_INLINE ptr_mvar *reverse_mptr_list(ptr_mvar*);
  //--------------------------------------------------------------------------

  template<class T> PFC_INLINE void collect_pointers(const T&, meta_case<0> is_type_class_);
  template<class T> PFC_INLINE void collect_pointers(const T*, meta_case<1> is_ptr_orep_);
  template<class T> PFC_INLINE void collect_pointers(const T*, meta_case<2> is_ptr_crep_);
  template<class T> PFC_INLINE void collect_pointers(const T*, meta_case<3> is_ptr_introspec_);
  template<class T> PFC_INLINE void collect_pointers(const T*, meta_case<4> is_ptr_fwd_introspec_);
  template<class T> PFC_INLINE void collect_pointers(const T&, meta_case<5> is_type_enum_);
  template<typename T> PFC_INLINE void collect_pointers(const T&, meta_case<-1> default_);
  template<class T> PFC_INLINE void collect_pointers(const T&, meta_case<-2> null_);
  template<class T> PFC_INLINE void stream(const T&, meta_case<0> is_type_class_);
  template<typename T> PFC_INLINE void stream(const T*, meta_case<1> is_type_ptr_);
  PFC_INLINE void stream(bool, meta_case<2> is_type_bool_);
  template<typename T> PFC_INLINE void stream(T, meta_case<3> is_type_fund_);
  template<typename T> PFC_INLINE void stream(T, meta_case<4> is_type_enum_);
  template<typename T> PFC_INLINE void stream(const T&, meta_case<-1> default_);
  void init_save();
  void save_info(archive_pointer_t root_idx_, const char *custom_id_);
  void save_data();
  void clean_up();
  //--------------------------------------------------------------------------

  S &m_stream;
  bool m_has_type_info;
  bool m_custom_streaming;
  bool m_is_collecting_pointers;
  unsigned m_num_mono, m_num_poly;
  unsigned m_num_crep, m_num_orep;
  usize_t m_num_objs_total;
  ptr_type_base *m_mono_list;
  ptr_rep_base *m_crep_list;
  ptr_type_base *m_orep_list;
  free_list m_ptr_mvar_pool;
  //----
  composite_type_base *m_composite_type_list;
  composite_type_base **m_composite_type_tail_ptr;
  ptr_type_base *m_cur_object_type;
  ptr_type_base *m_cur_collected_class;
  object_entry *m_cur_collected_object;
  ptr_mvar *m_cur_ptr_mvar;
  void *m_fwd_ptr;
};
//----------------------------------------------------------------------------


//============================================================================
// prop_enum_find_mvar
//============================================================================
class prop_enum_find_mvar: public prop_enum_interface_base<prop_enum_find_mvar>
{
public:
  typedef void(*post_mutate_func_t)(void*);
  //--------------------------------------------------------------------------

  // construction and accessors
  PFC_INLINE prop_enum_find_mvar(const char *mvar_name_);
  PFC_INLINE void *mvar_data() const;
  PFC_INLINE unsigned mvar_type_id() const;
  PFC_INLINE post_mutate_func_t post_mutate_func() const;
  //--------------------------------------------------------------------------

  // streaming interface
  template<class T> PFC_INLINE bool subclass(T*);
  template<typename T> PFC_INLINE bool var(T&, unsigned flags_=0, const char *mvar_name_=0);
  template<typename T, class C> PFC_INLINE bool var(T&, unsigned flags_, const char *mvar_name_, C&);
  template<typename T, class C> PFC_INLINE bool var(T&, unsigned flags_, const char *mvar_name_, C&, void(*post_mutate_func_)(C*));
  template<typename T, class C> PFC_INLINE bool var(T&, unsigned flags_, const char *mvar_name_, C&, void(C::*mutate_func_)(const T&, unsigned var_index_), unsigned var_index_);
  template<typename T> PFC_INLINE bool avar(T*, usize_t size_, unsigned flags_=0, const char *mvar_name_=0);
  template<typename T, class C> PFC_INLINE bool avar(T*, usize_t size_, unsigned flags_, const char *mvar_name_, C&);
  template<typename T, class C> PFC_INLINE bool avar(T*, usize_t size_, unsigned flags_, const char *mvar_name_, C&, void(*post_mutate_func_)(C*));
  template<typename T, class C> PFC_INLINE bool avar(T*, usize_t size_, unsigned flags_, const char *mvar_name_, C&, void(C::*mutate_func_)(const T&, unsigned index_, unsigned var_index_), unsigned var_index_);
  PFC_INLINE bool data(void*, usize_t num_bytes_);
  template<typename T> PFC_INLINE bool alias_var(T&, unsigned flags_, const char *alias_=0);
  template<typename T> PFC_INLINE bool alias_avar(T*, usize_t size_, unsigned flags_, const char *alias_=0);
  //--------------------------------------------------------------------------

private:
  prop_enum_find_mvar(const prop_enum_find_mvar&); // not implemented
  void operator=(const prop_enum_find_mvar&); // not implemented
  //--------------------------------------------------------------------------

  const char *m_mvar_name;
  void *m_mvar_data;
  unsigned m_mvar_type_id;
  post_mutate_func_t m_mvar_post_mutate_func;
};
//----------------------------------------------------------------------------


//============================================================================
// pointer_mutator_base
//============================================================================
struct pointer_mutator_base
{
  virtual void *create(const char *class_name_) const=0;
  virtual void release(void*) const=0;
  virtual void expose(prop_enum_exposure_base&, void*) const=0;
  virtual const char *registered_typename(const void*) const=0;
  virtual unsigned registered_class_typenames(const char**) const=0;
  //--------------------------------------------------------------------------

  unsigned ptr_id;
  bool is_orep_type;
};
//----------------------------------------------------------------------------


//============================================================================
// pointer_mutator_poly
//============================================================================
template<class T>
struct pointer_mutator_poly: pointer_mutator_base
{
  PFC_INLINE pointer_mutator_poly();
  virtual void *create(const char *class_name_) const;
  virtual void release(void*) const;
  virtual void expose(prop_enum_exposure_base&, void*) const;
  virtual const char *registered_typename(const void*) const;
  virtual unsigned registered_class_typenames(const char**) const;
  //--------------------------------------------------------------------------

  PFC_STATIC_ASSERT(is_type_crep<T>::res);
};
//----------------------------------------------------------------------------


//============================================================================
// pointer_mutator_mono
//============================================================================
template<class T>
struct pointer_mutator_mono: pointer_mutator_base
{
  PFC_INLINE pointer_mutator_mono();
  virtual void *create(const char *class_name_) const;
  virtual void release(void*) const;
  virtual void expose(prop_enum_exposure_base&, void*) const;
  virtual const char *registered_typename(const void*) const;
  virtual unsigned registered_class_typenames(const char**) const;
  //--------------------------------------------------------------------------

  PFC_STATIC_ASSERT(is_type_mono<T>::res);
  PFC_STATIC_ASSERT(is_type_introspec<T>::res);
};
//----------------------------------------------------------------------------


//============================================================================
// prop_enum_exposure_base
//============================================================================
class prop_enum_exposure_base: public prop_enum_interface_base<prop_enum_exposure_base>
{
public:
  // nested types
  enum {pe_type=penum_display};
  enum e_traverse_flags
  {
    traverse_members_only  =0x00000000,
    traverse_composite_objs=0x00000001,
    traverse_internal_ptrs =0x00000002,
    traverse_external_ptrs =0x00000004,
    traverse_all_ptrs      =traverse_internal_ptrs|traverse_external_ptrs,
    traverse_all           =0xffffffff
  };
  typedef void(prop_enum_exposure_base::*mutate_func_ptr_t)(const void*, unsigned var_index_);
  typedef void(prop_enum_exposure_base::*mutate_arr_func_ptr_t)(const void*, unsigned index_, unsigned var_index_);
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE prop_enum_exposure_base(e_traverse_flags=traverse_all);
  //--------------------------------------------------------------------------

  // serialization
  template<typename T> PFC_INLINE bool var(const T&, unsigned flags_=0, const char *mvar_name_=0);
  template<typename T, class C> PFC_INLINE bool var(const T&, unsigned flags_, const char *mvar_name_, C&);
  template<typename T, class C> PFC_INLINE bool var(const T&, unsigned flags_, const char *mvar_name_, C&, void(*post_mutate_func_)(C*));
  template<typename T, class C> PFC_INLINE bool var(const T&, unsigned flags_, const char *mvar_name_, C&, void(C::*mutate_func_)(const T&, unsigned var_index_), unsigned var_index_);
  template<typename T> PFC_INLINE bool avar(const T*, usize_t size_, unsigned flags_=0, const char *mvar_name_=0);
  template<typename T, class C> PFC_INLINE bool avar(const T*, usize_t size_, unsigned flags_, const char *mvar_name_, C&);
  template<typename T, class C> PFC_INLINE bool avar(const T*, usize_t size_, unsigned flags_, const char *mvar_name_, C&, void(*post_mutate_func_)(C*));
  template<typename T, class C> PFC_INLINE bool avar(const T*, usize_t size_, unsigned flags_, const char *mvar_name_, C&, void(C::*mutate_func_)(const T&, unsigned index_, unsigned var_index_), unsigned var_index_);
  PFC_INLINE bool data(const void*, usize_t num_bytes_);
  //--------------------------------------------------------------------------

  // editor specific exposure interface
  PFC_INLINE void group_begin(const char *category_name_);
  PFC_INLINE void group_end();
  virtual void name(const char*)=0;
  virtual void desc(const char*)=0;
  virtual void color(uint32_t rgb_)=0;
  virtual void expanded()=0;
  template<typename T> PFC_INLINE void slider(const T &min_, const T &max_, const T &step_);
  //--------------------------------------------------------------------------

protected:
  unsigned m_const_recursion;
  unsigned m_ptr_const_recursion;
  void *m_containing_object;
  void(*m_post_mutate_func)(void*);
  mutate_func_ptr_t m_mutate_func;
  mutate_arr_func_ptr_t m_mutate_arr_func;
  unsigned m_mutate_var_index;
  //--------------------------------------------------------------------------

  virtual bool var_impl(const char *mvar_name_, unsigned type_id_, void*)=0;
  virtual void data_impl(void*, usize_t num_bytes_)=0;
  virtual void enum_impl(const char *mvar_name_, unsigned type_id_, int *eval_, const char *const*enum_strings_, const int *enum_vals_, unsigned enum_index_)=0;
  virtual void slider_impl(const void *min_, const void *max_, const void *step_)=0;
  virtual bool begin_class(const char *mvar_name_, const char *class_name_)=0;
  virtual bool begin_class_ptr(const char *mvar_name_, const char *object_name_, const char *class_name_, void *&ptr_, const pointer_mutator_base&)=0;
  virtual void end_class()=0;
  //--------------------------------------------------------------------------

  template<typename T> PFC_INLINE void var_type(const char *mvar_name_, const T&, meta_case<0> is_type_fund_);
  template<typename T> PFC_INLINE void var_type(const char *mvar_name_, const T&, meta_case<1> is_type_class_);
  template<typename T> PFC_INLINE void var_type(const char *mvar_name_, const T&, meta_case<2> is_type_enum_);
  template<typename T> PFC_INLINE void var_type(const char *mvar_name_, T*&, meta_case<3> is_ptr_introspec_);
  template<typename T> PFC_INLINE void var_type(const char *mvar_name_, T*&, meta_case<4> is_ptr_fwd_introspec_);
  template<typename T> PFC_INLINE void var_type(const char *mvar_name_, const T&, meta_case<-1> default_);
  template<typename T> PFC_INLINE void var_type(const char *mvar_name_, const T&, meta_case<-2> null_);
  template<typename T> PFC_INLINE const char *object_name(const T*, meta_bool<true> is_type_orep_);
  template<typename T> PFC_INLINE const char *object_name(const T*, meta_bool<false> is_type_orep_);
  //--------------------------------------------------------------------------

private:
  const e_traverse_flags m_traverse_flags;
  void **m_fwd_ptr;
};
//----------------------------------------------------------------------------

//============================================================================
#include "class.inl"
} // namespace pfc
#endif
