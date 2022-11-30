//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// default leaf_class_alias implementation
//============================================================================
PFC_INLINE const str_id *leaf_class_alias(void*) {return 0;}
//----------------------------------------------------------------------------


//============================================================================
// find_mvar
//============================================================================
template<typename T, class U>
const T &find_mvar(const U &obj_, const char *mvar_name_)
{
  prop_enum_find_mvar pe(mvar_name_);
  enum_props(pe, const_cast<U&>(obj_));
  T *data=(T*)pe.mvar_data();
  PFC_ASSERT_MSG(data, ("Unable to find member variable \"%s\" from class \"%s\"\r\n", mvar_name_, object_typename(obj_))); 
  PFC_ASSERT_MSG(type_id<T>::id==pe.mvar_type_id(), ("Member variable \"%s\" of class \"%s\" is not type \"%s\"\r\n", mvar_name_, typeid(U).name(), typeid(T).name()));
  return *data;
}
//----

template<typename T, class U>
T &find_mvar(U &obj_, const char *mvar_name_, void(**post_mutate_func_)(void*))
{
  prop_enum_find_mvar pe(mvar_name_);
  enum_props(pe, obj_);
  T *data=(T*)pe.mvar_data();
  PFC_ASSERT_MSG(data, ("Unable to find member variable \"%s\" from class \"%s\"\r\n", mvar_name_, object_typename(obj_))); 
  PFC_ASSERT_MSG(type_id<T>::id==pe.mvar_type_id(), ("Member variable \"%s\" of class \"%s\" is not type \"%s\"\r\n", mvar_name_, typeid(U).name(), typeid(T).name()));
  if(post_mutate_func_)
    *post_mutate_func_=pe.post_mutate_func();
  return *data;
}
//----------------------------------------------------------------------------


//============================================================================
// object pool management
//============================================================================
object_repository_pool &add_object_pool(const char *name_, object_repository_pool *parent_, bool activate_)
{
  object_repository_pool &pool=object_repository_base::add_pool(name_, parent_);
  if(activate_)
    object_repository_base::activate_pool(&pool);
  return pool;
}
//----

void remove_object_pool(object_repository_pool &pool_)
{
  object_repository_base::remove_pool(pool_);
}
//----

object_repository_pool *active_pool()
{
  return object_repository_base::active_pool();
}
//----

object_repository_pool *activate_object_pool(object_repository_pool *pool_)
{
  return object_repository_base::activate_pool(pool_);
}
//----

object_repository_pool *find_object_pool(const char *name_)
{
  return object_repository_base::find_pool(name_);
}
//----------------------------------------------------------------------------


//============================================================================
// object repository management
//============================================================================
PFC_INLINE const class_factory_base *find_mono_factory(const str_id &id_)
{
  // search for monomorphic class factory from the factory list
  extern hash_map<str_id, const class_factory_base*> g_mono_factories;
  hash_map<str_id, const class_factory_base*>::const_iterator it=g_mono_factories.find(id_);
  return is_valid(it)?*it:0;
}
//----

PFC_INLINE class_repository_base *find_class_repository(const str_id &id_)
{
  return class_repository_base::find_repository(id_);
}
//----

PFC_INLINE object_repository_base *find_object_repository(const str_id &id_)
{
  return object_repository_base::find_repository(id_);
}
//----

template<class B>
PFC_INLINE void add_object(const str_id &id_, B &object_)
{
  B::orep().add_object(id_, object_);
}
//----

template<class B>
PFC_INLINE void remove_object(B &object_)
{
  B::orep().remove_object(object_);
}
//----

template<class B>
PFC_INLINE B *create_object(const str_id &id_)
{
  return safe_cast<B*>(B::crep().create(id_));
}
//----

template<class B>
PFC_INLINE B *create_object()
{
  const str_id *leaf_id=leaf_class_alias((B*)0);
  PFC_ASSERT_MSG(leaf_id!=0, ("Base class doesn't define leaf class alias\r\n"));
  return safe_cast<B*>(B::crep().create(*leaf_id));
}
//----

template<class B>
PFC_INLINE B *find_object(const str_id &id_)
{
  return safe_cast<B*>(B::orep().find_object(id_));
}
//----

template<class B>
PFC_INLINE const str_id *find_object_name(const B &obj_)
{
  PFC_STATIC_ASSERT_MSG(is_type_orep<B>::res, find_object_name_works_only_with_object_repository_types);
  return B::orep().find_object_name(&obj_);
}
//----

template<class B>
PFC_INLINE B *load_object(const str_id &id_, const char *file_ext_, const char *path_)
{
  PFC_STATIC_ASSERT_MSG(is_type_orep<B>::res, load_object_works_only_with_object_repository_types);
  return safe_cast<B*>(B::orep().load_object(id_, file_ext_, path_));
}
//----

template<class B>
PFC_INLINE B *load_object(const str_id &id_, bin_input_stream_base &s_, const char *file_ext_, const char *path_)
{
  PFC_STATIC_ASSERT_MSG(is_type_orep<B>::res, load_object_works_only_with_object_repository_types);
  return safe_cast<B*>(B::orep().load_object(id_, s_, file_ext_, path_));
}
//----

template<class B>
inline owner_ptr<B> read_object(const char *filename_, const char *file_ext_, const char *path_)
{
  // open and read archive file
  extern owner_ptr<bin_input_stream_base> afs_open_read(const char *filename_, const char *path_, e_file_open_check);
  stack_str256 fname=filename_;
  if(file_ext_)
    fname+=file_ext_;
  owner_ptr<bin_input_stream_base> s=afs_open_read(fname.c_str(), path_, fopencheck_warn);
  if(s.data)
  {
    extern void *read_object_impl(bin_input_stream_base&, const char *file_ext_, const char *path_, unsigned type_id_);
    return static_cast<B*>(read_object_impl(*s.data, file_ext_, path_, type_id<B>::id));
  }
  extern filepath_str afs_complete_path(const char *name_, const char *path_, bool collapse_relative_dirs_);
  PFC_WARNF("Unable to read object \"%s\"\r\n", afs_complete_path(fname.c_str(), path_, true).c_str());
  return 0;
}
//----

template<class B>
inline owner_ptr<B> read_object(bin_input_stream_base &s_, const char *file_ext_, const char *path_)
{
  // read object from archive stream
  extern void *read_object_impl(bin_input_stream_base&, const char *file_ext_, const char *path_, unsigned type_id_);
  return static_cast<B*>(read_object_impl(s_, file_ext_, path_, type_id<B>::id));
}
//----

template<class B>
void save_object(const B &v_, const char *filename_, const char *path_, const char *custom_id_, bool save_type_info_, bool swap_endianness_)
{
  // write object to file
  extern owner_ptr<bin_output_stream_base> afs_open_write(const char *filename_, const char *path_, e_file_open_write_mode, uint64_t fpos_, bool makedir_, e_file_open_check);
  extern filepath_str afs_complete_path(const char *name_, const char *path_, bool collapse_relative_dirs_);
  owner_ptr<bin_output_stream_base> s=afs_open_write(filename_, path_, fopenwritemode_clear, 0, true, fopencheck_warn);
  PFC_CHECK_MSG(s.data, ("Unable to open file \"%s\" for writing\r\n", afs_complete_path(filename_, path_, true).c_str()));
  if(swap_endianness_)
  {
#ifdef PFC_BUILDOP_ARCHIVE_ENDIAN_SUPPORT
    endian_output_stream es(*s.data);
    prop_enum_output_archive<endian_output_stream> pe(es, save_type_info_);
    pe.write(v_, custom_id_);
#else
    PFC_ERRORF("Executable doesn't support writing %s-endian archive files\r\n", PFC_BIG_ENDIAN?"little", "big");
#endif
  }
  else
  {
    prop_enum_output_archive<bin_output_stream_base> pe(*s.data, save_type_info_);
    pe.write(v_, custom_id_);
  }
}
//----

template<class B>
void save_object(const B &v_, bin_output_stream_base &s_, const char *custom_id_, bool save_type_info_, bool swap_endianness_)
{
  // write object to the stream
  if(swap_endianness_)
  {
#ifdef PFC_BUILDOP_ARCHIVE_ENDIAN_SUPPORT
    endian_output_stream es(s_);
    prop_enum_output_archive<endian_output_stream> pe(es, save_type_info_);
    pe.write(v_, custom_id_);
#else
    PFC_ERRORF("Executable doesn't support writing %s-endian archive files\r\n", PFC_BIG_ENDIAN?"little", "big");
#endif
  }
  else
  {
    prop_enum_output_archive<bin_output_stream_base> pe(s_, save_type_info_);
    pe.write(v_, custom_id_);
  }
}
//----------------------------------------------------------------------------


//============================================================================
// archive_mvar_type_id
//============================================================================
template<typename T>
struct archive_mvar_type_id
{
  // member variable id
  enum {size=meta_log2<meta_sizeof<typename meta_if<!is_type_class<T>::res, T, void>::res>::res>::res,
        res=(is_type_class<T>::res || is_type_equal<T, void>::res)?0:
            is_type_ptr<T>::res?1:
            is_type_enum<T>::res?12:
            is_type_equal<T, bool>::res?3:
            is_type_int<T>::res?(2*size+(is_type_signed<T>::res?2:3)):
            is_type_float<T>::res?8+size:-1};

  // check for proper type
  PFC_STATIC_ASSERT_MSG(res!=-1, unsupported_fundamental_member_variable_type);
  PFC_STATIC_ASSERT_MSG(!is_type_int<T>::res || size<4, integral_member_variable_size_must_be_less_or_equal_to_64_bits);
  PFC_STATIC_ASSERT_MSG(!is_type_float<T>::res || size==2 || size==3, float_member_variable_size_must_be_32_or_64_bits);
  PFC_STATIC_ASSERT_MSG(res<unsigned(archtype_class_start), fundamental_data_types_overlap_with_class_types);
};
//----------------------------------------------------------------------------


//============================================================================
// class_factory_base
//============================================================================
class_factory_base::~class_factory_base()
{
}
//----------------------------------------------------------------------------


//============================================================================
// class_factory_base::prop_enum_input_converter
//============================================================================
template<class S>
class class_factory_base::prop_enum_input_converter: public prop_enum_interface_base<prop_enum_input_converter<S> >
{
public:
  // construction
  enum {pe_type=penum_input};
  prop_enum_input_converter(prop_enum_input_archive<S>&, const class_mvar_t *mvars_, unsigned num_mvars_, const uint16_t *csub_vers_);
  PFC_INLINE bool requires_conversion() const;
  //--------------------------------------------------------------------------

  // serialization
  template<class T> void read(T&);
  template<class T> PFC_INLINE bool subclass(T*);
  template<class T> PFC_INLINE unsigned set_custom_streaming(T&, unsigned version_);
  template<typename T> bool var(T&, unsigned flags_=0, const char *mvar_name_=0);
  template<typename T, class C> PFC_INLINE bool var(T&, unsigned flags_, const char *mvar_name_, C&);
  template<typename T, class C> PFC_INLINE bool var(T&, unsigned flags_, const char *mvar_name_, C&, void(*post_mutate_func_)(C*));
  template<typename T, class C> PFC_INLINE bool var(T&, unsigned flags_, const char *mvar_name_, C&, void(C::*mutate_func_)(const T&, unsigned var_index_), unsigned var_index_);
  template<typename T> bool avar(T*, usize_t size_, unsigned flags_=0, const char *mvar_name_=0);
  template<typename T, class C> PFC_INLINE bool avar(T*, usize_t size_, unsigned flags_, const char *mvar_name_, C&);
  template<typename T, class C> PFC_INLINE bool avar(T*, usize_t size_, unsigned flags_, const char *mvar_name_, C&, void(*post_mutate_func_)(C*));
  template<typename T, class C> PFC_INLINE bool avar(T*, usize_t size_, unsigned flags_, const char *mvar_name_, C&, void(C::*mutate_func_)(const T&, unsigned index_, unsigned var_index_), unsigned var_index_);
  bool data(void*, usize_t num_bytes_);
  template<typename T> bool alias_var(T&, unsigned flags_, const char *alias_);
  template<typename T> bool alias_avar(T*, usize_t size_, unsigned flags_, const char *alias_);
  //--------------------------------------------------------------------------

private:
  prop_enum_input_converter(const prop_enum_input_converter&); // not implemented
  void operator=(const prop_enum_input_converter&); // not implemented
  template<typename T> PFC_INLINE bool is_typename_match(T*, const char *arch_name_);
  void skip_type(archive_type_id_t type_id_, usize_t num_objects_=1);
  template<typename T, typename U> PFC_INLINE void stream_fund(T&, meta_type<U>, meta_bool<true> is_type_fund_);
  template<typename U> PFC_INLINE void stream_fund(bool&, meta_type<U>, meta_bool<true> is_type_fund_);
  template<typename T, typename U> PFC_INLINE void stream_fund(T&, meta_type<U>, meta_bool<false> is_type_fund_);
  template<typename T> PFC_INLINE void stream_enum(T&, meta_bool<true> is_type_enum_);
  template<typename T> PFC_INLINE void stream_enum(T&, meta_bool<false> is_type_enum_);
  template<typename T> PFC_INLINE void stream_ptr(T&, meta_bool<true> is_type_ptr_);
  template<typename T> PFC_INLINE void stream_ptr(T&, meta_bool<false> is_type_ptr_);
  template<typename T> PFC_INLINE void stream_class(T&, meta_bool<true> is_type_class_);
  template<typename T> PFC_INLINE void stream_class(T&, meta_bool<false> is_type_class_);
  template<typename T> PFC_INLINE void stream_class(T*, usize_t num_objects_, meta_bool<true> is_type_class_);
  template<typename T> PFC_INLINE void stream_class(T*, usize_t num_objects_, meta_bool<false> is_type_class_);
  //--------------------------------------------------------------------------

  prop_enum_input_archive<S> &m_penum;
  S &m_stream;
  const class_mvar_t *m_mvars;
  unsigned m_num_mvars;
  const uint16_t *m_csub_vers;
  bool m_active_custom_subclass;
  unsigned m_cur_active_subclass;
  unsigned m_cur_subclass;
  unsigned m_cur_csub_ver;
  unsigned m_cur_mvar;
  const str_id *m_leaf_str_id;
  unsigned m_leaf_type_id;
  bool m_custom_streaming;
  bool m_requires_conversion;
  archive_type_id_t m_type_id;
};
//----------------------------------------------------------------------------

template<class S>
class_factory_base::prop_enum_input_converter<S>::prop_enum_input_converter(prop_enum_input_archive<S> &penum_, const class_mvar_t *mvars_, unsigned num_mvars_, const uint16_t *csub_vers_)
  :m_penum(penum_)
  ,m_stream(penum_.stream())
  ,m_mvars(mvars_)
  ,m_num_mvars(num_mvars_)
  ,m_csub_vers(csub_vers_)
  ,m_active_custom_subclass(false)
  ,m_cur_active_subclass(0)
  ,m_cur_subclass(0)
  ,m_cur_csub_ver(0)
  ,m_cur_mvar(0)
  ,m_leaf_str_id(0)
  ,m_leaf_type_id(0)
  ,m_custom_streaming(false)
  ,m_requires_conversion(false)
  ,m_type_id(0)
{
}
//----

template<class S>
bool class_factory_base::prop_enum_input_converter<S>::requires_conversion() const
{
  return m_requires_conversion;
}
//----------------------------------------------------------------------------

template<class S>
template<typename T>
void class_factory_base::prop_enum_input_converter<S>::read(T &v_)
{
  // process all member variables of the class object in the stream
  m_cur_active_subclass=0;
  m_cur_csub_ver=0;
  m_cur_mvar=0;
  m_leaf_str_id=leaf_class_alias((T*)0);
  m_leaf_type_id=m_leaf_str_id?type_id<T>::id:0;
  while(m_cur_mvar<m_num_mvars)
  {
    // try to read all member variables
    unsigned old_cur_mvar=m_cur_mvar;
    m_cur_subclass=0;
    enum_props_most_derived(*this, v_);

    // if no progress made in processing the stream, skip the variable
    if(old_cur_mvar==m_cur_mvar)
    {
      archive_type_id_t type=m_mvars[m_cur_mvar++].first;
      if(type==archtype_subclass)
      {
        while(m_cur_mvar<m_num_mvars && m_mvars[m_cur_mvar].first<archtype_subclass)
          skip_type(m_mvars[m_cur_mvar++].first);
      }
      else
        skip_type(type);
    }
  }
}
//----

template<class S>
template<class T>
bool class_factory_base::prop_enum_input_converter<S>::subclass(T*)
{
  // check for subclass that's being currently provided by the stream
  m_custom_streaming=false;
  ++m_cur_subclass;
  m_active_custom_subclass=false;
  const class_mvar_t *mvar=m_mvars+m_cur_mvar;
  if(m_cur_mvar<m_num_mvars && mvar->first>=archtype_subclass && is_typename_match((T*)0, mvar->second))
  {
    m_cur_active_subclass=m_cur_subclass;
    m_active_custom_subclass=mvar->first==archtype_subclass_custom;
    ++m_cur_mvar;
  }
  return m_cur_active_subclass==m_cur_subclass;
}
//----

template<class S>
template<class T>
unsigned class_factory_base::prop_enum_input_converter<S>::set_custom_streaming(T&, unsigned version_)
{
  // check for active custom streamed subclass
  if(!m_active_custom_subclass)
  {
    m_requires_conversion=true;
    return unsigned(-1);
  }

  // skip the size of the sub-object and return the subclass version
  m_custom_streaming=true;
  m_stream.skip(sizeof(archive_object_size_t));
  unsigned ver=m_csub_vers[m_cur_csub_ver++];
  if(ver!=version_)
    m_requires_conversion=true;
  return ver;
}
//----

template<class S>
template<typename T>
bool class_factory_base::prop_enum_input_converter<S>::var(T &v_, unsigned flags_, const char *mvar_name_)
{
  // check for variable that's currently being provided by the stream
  const class_mvar_t *mvar=m_mvars+m_cur_mvar;
  if(m_custom_streaming || (m_cur_mvar<m_num_mvars && mvar->first<archtype_subclass && (!mvar_name_ || str_eq(mvar_name_, mvar->second))))
  {
    // get type ID of the archived variable
    if(!m_custom_streaming)
    {
      m_type_id=mvar->first;
      ++m_cur_mvar;
    }
    else
      if(!(flags_&mvarflag_array_tail))
        m_stream>>m_type_id;

    // switch to proper conversion procedure for the member variable
    switch(m_type_id)
    {
      // pointer type
      case archive_mvar_type_id<void*>::res:   stream_ptr(v_, meta_bool<is_type_ptr<T>::res>()); break;
      // fundamental & enum types
      case archive_mvar_type_id<int8_t>::res:    stream_fund(v_, meta_type<int8_t>(), meta_bool<is_type_fund<T>::res>()); break;
      case archive_mvar_type_id<uint8_t>::res:   stream_fund(v_, meta_type<uint8_t>(), meta_bool<is_type_fund<T>::res>()); break;
      case archive_mvar_type_id<int16_t>::res:   stream_fund(v_, meta_type<int16_t>(), meta_bool<is_type_fund<T>::res>()); break;
      case archive_mvar_type_id<uint16_t>::res:  stream_fund(v_, meta_type<uint16_t>(), meta_bool<is_type_fund<T>::res>()); break;
      case archive_mvar_type_id<int32_t>::res:   stream_fund(v_, meta_type<int32_t>(), meta_bool<is_type_fund<T>::res>()); break;
      case archive_mvar_type_id<uint32_t>::res:  stream_fund(v_, meta_type<uint32_t>(), meta_bool<is_type_fund<T>::res>()); break;
      case archive_mvar_type_id<int64_t>::res:   stream_fund(v_, meta_type<int64_t>(), meta_bool<is_type_fund<T>::res>()); break;
      case archive_mvar_type_id<uint64_t>::res:  stream_fund(v_, meta_type<uint64_t>(), meta_bool<is_type_fund<T>::res>()); break;
      case archive_mvar_type_id<float32_t>::res: stream_fund(v_, meta_type<float32_t>(), meta_bool<is_type_fund<T>::res>()); break;
      case archive_mvar_type_id<float64_t>::res: stream_fund(v_, meta_type<float64_t>(), meta_bool<is_type_fund<T>::res>()); break;
      // enum type
      case archive_mvar_type_id<e_penum>::res: stream_enum(v_, meta_bool<is_type_enum<T>::res>()); break;
      // composite class object
      default: stream_class(v_, meta_bool<is_type_class<T>::res>()); break;
    }
  }
  else
    m_requires_conversion=true;
  return true;
}
//----

template<class S>
template<typename T, class C>
bool class_factory_base::prop_enum_input_converter<S>::var(T &v_, unsigned flags_, const char *mvar_name_, C&)
{
  var(v_, flags_, mvar_name_);
  return true;
}
//----

template<class S>
template<typename T, class C>
bool class_factory_base::prop_enum_input_converter<S>::var(T &v_, unsigned flags_, const char *mvar_name_, C&, void(*post_mutate_func_)(C*))
{
  var(v_, flags_, mvar_name_);
  return true;
}
//----

template<class S>
template<typename T, class C>
bool class_factory_base::prop_enum_input_converter<S>::var(T &v_, unsigned flags_, const char *mvar_name_, C&, void(C::*mutate_func_)(const T&, unsigned var_index_), unsigned var_index_)
{
  var(v_, flags_, mvar_name_);
  return true;
}
//----

template<class S>
template<typename T>
bool class_factory_base::prop_enum_input_converter<S>::avar(T *a_, usize_t size_, unsigned flags_, const char *mvar_name_)
{
  const class_mvar_t *mvar=m_mvars+m_cur_mvar;
  if(m_custom_streaming || (m_cur_mvar<m_num_mvars && mvar->first<archtype_subclass && (!mvar_name_ || str_eq(mvar_name_, mvar->second))))
  {
    // get type ID of the archived variable
    if(!m_custom_streaming)
    {
      // check the number of objects in the archive
      archive_array_size_t num_objects;
      m_stream>>num_objects;
      PFC_CHECK_MSG(num_objects==size_, ("Number of objects in the archive (%i) for variable \"%s\" doesn't match the number of objects to be read (%i)\r\n", num_objects, mvar_name_?mvar_name_:"", size_));
      m_type_id=mvar->first;
      ++m_cur_mvar;
    }
    else
      m_stream>>m_type_id;

    // switch to proper conversion procedure for the array
    switch(m_type_id&~archtype_flag_array)
    {
      // pointer type
      case archive_mvar_type_id<void*>::res:   for(usize_t i=0; i<size_; ++i) stream_ptr(a_[i], meta_bool<is_type_ptr<T>::res>()); break;
      // fundamental & enum types
      case archive_mvar_type_id<int8_t>::res:    for(usize_t i=0; i<size_; ++i) stream_fund(a_[i], meta_type<int8_t>(), meta_bool<is_type_fund<T>::res>()); break;
      case archive_mvar_type_id<uint8_t>::res:   for(usize_t i=0; i<size_; ++i) stream_fund(a_[i], meta_type<uint8_t>(), meta_bool<is_type_fund<T>::res>()); break;
      case archive_mvar_type_id<int16_t>::res:   for(usize_t i=0; i<size_; ++i) stream_fund(a_[i], meta_type<int16_t>(), meta_bool<is_type_fund<T>::res>()); break;
      case archive_mvar_type_id<uint16_t>::res:  for(usize_t i=0; i<size_; ++i) stream_fund(a_[i], meta_type<uint16_t>(), meta_bool<is_type_fund<T>::res>()); break;
      case archive_mvar_type_id<int32_t>::res:   for(usize_t i=0; i<size_; ++i) stream_fund(a_[i], meta_type<int32_t>(), meta_bool<is_type_fund<T>::res>()); break;
      case archive_mvar_type_id<uint32_t>::res:  for(usize_t i=0; i<size_; ++i) stream_fund(a_[i], meta_type<uint32_t>(), meta_bool<is_type_fund<T>::res>()); break;
      case archive_mvar_type_id<int64_t>::res:   for(usize_t i=0; i<size_; ++i) stream_fund(a_[i], meta_type<int64_t>(), meta_bool<is_type_fund<T>::res>()); break;
      case archive_mvar_type_id<uint64_t>::res:  for(usize_t i=0; i<size_; ++i) stream_fund(a_[i], meta_type<uint64_t>(), meta_bool<is_type_fund<T>::res>()); break;
      case archive_mvar_type_id<float32_t>::res: for(usize_t i=0; i<size_; ++i) stream_fund(a_[i], meta_type<float32_t>(), meta_bool<is_type_fund<T>::res>()); break;
      case archive_mvar_type_id<float64_t>::res: for(usize_t i=0; i<size_; ++i) stream_fund(a_[i], meta_type<float64_t>(), meta_bool<is_type_fund<T>::res>()); break;
      case archive_mvar_type_id<e_penum>::res: for(usize_t i=0; i<size_; ++i) stream_enum(a_[i], meta_bool<is_type_enum<T>::res>()); break;
      // composite class object
      default: stream_class(a_, size_, meta_bool<is_type_class<T>::res>()); break;
    }
  }
  else
    m_requires_conversion=true;
  return true;
}
//----

template<class S>
template<typename T, class C>
bool class_factory_base::prop_enum_input_converter<S>::avar(T *a_, usize_t size_, unsigned flags_, const char *mvar_name_, C&)
{
  avar(a_, size_, flags_, mvar_name_);
  return true;
}
//----

template<class S>
template<typename T, class C>
bool class_factory_base::prop_enum_input_converter<S>::avar(T *a_, usize_t size_, unsigned flags_, const char *mvar_name_, C&, void(*post_mutate_func_)(C*))
{
  avar(a_, size_, flags_, mvar_name_);
  return true;
}
//----

template<class S>
template<typename T, class C>
bool class_factory_base::prop_enum_input_converter<S>::avar(T *a_, usize_t size_, unsigned flags_, const char *mvar_name_, C&, void(C::*mutate_func_)(const T&, unsigned index_, unsigned var_index_), unsigned var_index_)
{
  avar(a_, size_, flags_, mvar_name_);
  return true;
}
//----

template<class S>
bool class_factory_base::prop_enum_input_converter<S>::data(void *data_, usize_t num_bytes_)
{
  m_penum.data(data_, num_bytes_);
  return true;
}
//----

template<class S>
template<typename T>
bool class_factory_base::prop_enum_input_converter<S>::alias_var(T &v_, unsigned flags_, const char *alias_)
{
  // try to read deprecated variable
  PFC_ASSERT_MSG(!m_custom_streaming, ("Aliased variables not supported for custom streamed classes\r\n"));
  unsigned old_cur_mvar=m_cur_mvar;
  bool old_requires_conversion=m_requires_conversion;
  var(v_, 0, alias_);
  if(old_cur_mvar==m_cur_mvar)
    m_requires_conversion=old_requires_conversion;
  return true;
}
//----

template<class S>
template<typename T>
bool class_factory_base::prop_enum_input_converter<S>::alias_avar(T *a_, usize_t size_, unsigned flags_, const char *alias_)
{
  // try to read deprecated array variable
  PFC_ASSERT_MSG(!m_custom_streaming, ("Aliased variables not supported for custom streamed classes\r\n"));
  unsigned old_cur_mvar=m_cur_mvar;
  bool old_requires_conversion=m_requires_conversion;
  avar(a_, size_, 0, alias_);
  if(old_cur_mvar==m_cur_mvar)
    m_requires_conversion=old_requires_conversion;
  return true;
}
//----------------------------------------------------------------------------

template<class S>
template<typename T>
bool class_factory_base::prop_enum_input_converter<S>::is_typename_match(T*, const char *name_)
{
  return    class_reg_info<T>::reg_name?str_eq(class_reg_info<T>::reg_name, name_) || (class_reg_info<T>::deprecated_name?str_eq(class_reg_info<T>::deprecated_name, name_):false):str_eq(class_typename((T*)0), name_)
         || (type_id<T>::id==m_leaf_type_id && str_eq(m_leaf_str_id->c_str(), name_));
}
//----

template<class S>
void class_factory_base::prop_enum_input_converter<S>::skip_type(archive_type_id_t type_id_, usize_t num_objects_)
{
  // switch to proper skipping procedure of the member variable
  PFC_ASSERT(type_id_!=archtype_subclass);
  m_requires_conversion=true;
  switch(type_id_)
  {
    // pointer type
    case archive_mvar_type_id<void*>::res:   m_stream.skip(sizeof(archive_pointer_t)*num_objects_); return;

    // fundamental types
    case archive_mvar_type_id<int8_t>::res:    m_stream.skip(sizeof(int8_t)*num_objects_); return;
    case archive_mvar_type_id<uint8_t>::res:   m_stream.skip(sizeof(uint8_t)*num_objects_); return;
    case archive_mvar_type_id<int16_t>::res:   m_stream.skip(sizeof(int16_t)*num_objects_); return;
    case archive_mvar_type_id<uint16_t>::res:  m_stream.skip(sizeof(uint16_t)*num_objects_); return;
    case archive_mvar_type_id<int32_t>::res:   m_stream.skip(sizeof(int32_t)*num_objects_); return;
    case archive_mvar_type_id<uint32_t>::res:  m_stream.skip(sizeof(uint32_t)*num_objects_); return;
    case archive_mvar_type_id<int64_t>::res:   m_stream.skip(sizeof(int64_t)*num_objects_); return;
    case archive_mvar_type_id<uint64_t>::res:  m_stream.skip(sizeof(uint64_t)*num_objects_); return;
    case archive_mvar_type_id<float32_t>::res: m_stream.skip(sizeof(float32_t)*num_objects_); return;
    case archive_mvar_type_id<float64_t>::res: m_stream.skip(sizeof(float64_t)*num_objects_); return;

    // enum
    case archive_mvar_type_id<e_penum>::res:
    {
      uint8_t ssize;
      m_stream>>ssize;
      m_stream.skip(ssize);
    } return;

    // custom streamed subclass
    case archtype_subclass_custom:
    {
      // skip custom streamed subclass
      archive_object_size_t size;
      m_stream>>size;
      m_stream.skip(size);
    } return;

    // arrays and class object
    default:
    {
      // check for array type
      if(type_id_&archtype_flag_array)
      {
        // read the number of objects and skip the objects
        PFC_ASSERT(num_objects_==1);
        archive_array_size_t num_objects;
        m_stream>>num_objects;
        skip_type(type_id_&~archtype_flag_array, num_objects);
        return;
      }

      // skip all members of the class objects
      unsigned num_mvars=0;
      const uint16_t *csub_vers=0;
      const class_mvar_t *mvars=m_penum.composite_type_info(type_id_, num_mvars, csub_vers);
      for(usize_t i=0; i<num_objects_; ++i)
        for(unsigned mvi=0; mvi<num_mvars; ++mvi)
        {
          archive_type_id_t type=mvars[mvi].first;
          if(type!=archtype_subclass)
            skip_type(type);
        }
    }
  }
}
//----

template<class S>
template<typename T, typename U>
void class_factory_base::prop_enum_input_converter<S>::stream_fund(T &v_, meta_type<U>, meta_bool<true> is_type_fund_)
{
  // convert between fundamental types (or no conversion between equal types)
  m_requires_conversion|=!is_type_equal<T, U>::res;
  U v;
  m_penum.var(v);
  v_=T(v);
}
//----

template<class S>
template<typename U>
void class_factory_base::prop_enum_input_converter<S>::stream_fund(bool &v_, meta_type<U>, meta_bool<true> is_type_fund_)
{
  // convert to boolean type (or no conversion between boolean types)
  m_requires_conversion|=!is_type_equal<uint8_t, U>::res;
  U v;
  m_penum.var(v);
  v_=v!=U();
}
//----

template<class S>
template<typename T, typename U>
void class_factory_base::prop_enum_input_converter<S>::stream_fund(T&, meta_type<U>, meta_bool<false> is_type_fund_)
{
  // unable to perform conversion (from non-fundamental to fundamental type)
  skip_type(m_type_id);
}
//----

template<class S>
template<typename T>
void class_factory_base::prop_enum_input_converter<S>::stream_enum(T &v_, meta_bool<true> is_type_enum_)
{
  // read enum value
  m_penum.var(v_);
}
//----

template<class S>
template<typename T>
void class_factory_base::prop_enum_input_converter<S>::stream_enum(T&, meta_bool<false> is_type_enum_)
{
  // not an enum type thus unable to perform conversion
  uint8_t ssize;
  m_stream>>ssize;
  m_stream.skip(ssize);
}
//----

template<class S>
template<typename T>
void class_factory_base::prop_enum_input_converter<S>::stream_ptr(T &v_, meta_bool<true> is_type_ptr_)
{
  // read pointer
  m_penum.var(v_);
}
//----

template<class S>
template<typename T>
void class_factory_base::prop_enum_input_converter<S>::stream_ptr(T &v_, meta_bool<false> is_type_ptr_)
{
  // not a pointer type thus unable to perform conversion
  m_stream.skip(sizeof(archive_pointer_t));
}
//----

template<class S>
template<typename T>
void class_factory_base::prop_enum_input_converter<S>::stream_class(T &v_, meta_bool<true> is_type_class_)
{
  // convert the composite class object
  unsigned num_mvars=0;
  const uint16_t *csub_vers=0;
  const class_mvar_t *mvars=m_penum.composite_type_info(m_type_id, num_mvars, csub_vers);
  prop_enum_input_converter<S> pe_conv(m_penum, mvars, num_mvars, csub_vers);
  pe_conv.read(v_);
  post_load_function(&v_);
  m_requires_conversion|=pe_conv.requires_conversion();
}
//----

template<class S>
template<typename T>
void class_factory_base::prop_enum_input_converter<S>::stream_class(T&, meta_bool<false> is_type_class_)
{
  // unable to convert from a class to non-class type => skip
  skip_type(m_type_id);
}
//----

template<class S>
template<typename T>
void class_factory_base::prop_enum_input_converter<S>::stream_class(T *a_, usize_t num_objects_, meta_bool<true> is_type_class_)
{
  if(num_objects_)
  {
    // init type converter
    unsigned num_mvars=0;
    const uint16_t *csub_vers=0;
    const class_mvar_t *mvars=m_penum.composite_type_info(m_type_id&~archtype_flag_array, num_mvars, csub_vers);
    prop_enum_input_converter<S> pe_conv(m_penum, mvars, num_mvars, csub_vers);

    // read first item and check if conversion is required
    pe_conv.read(*a_);
    post_load_function(a_);
    if(pe_conv.requires_conversion())
    {
      // convert remaining objects
      for(usize_t i=1; i<num_objects_; ++i)
      {
        pe_conv.read(a_[i]);
        post_load_function(a_+i);
      }
      m_requires_conversion=true;
    }
    else
    {
      // read objects without conversion
      for(usize_t i=1; i<num_objects_; ++i)
      {
        enum_props_most_derived(m_penum, a_[i]);
        post_load_function(a_+i);
      }
      m_penum.reset();
    }
  }
}
//----

template<class S>
template<typename T>
void class_factory_base::prop_enum_input_converter<S>::stream_class(T *a_, usize_t num_objects_, meta_bool<false> is_type_class_)
{
  // unable to convert from a class array to non-class array => skip array
  skip_type(m_type_id, num_objects_);
}
//----------------------------------------------------------------------------


//============================================================================
// class_factory
//============================================================================
template<class T>
void *class_factory<T>::create() const
{
  return PFC_NEW(T);
}
//----

template<class T>
void class_factory<T>::create(void *p_) const
{
  PFC_PNEW(p_)T;
}
//----

template<class T>
void class_factory<T>::create(void **objs_, usize_t num_objects_) const
{
  for(usize_t i=0; i<num_objects_; ++i)
    objs_[i]=PFC_NEW(T);
}
//----

template<class T>
void class_factory<T>::post_load(void **objs_, usize_t num_objects_) const
{
  // call post-load functions for the objects
  for(usize_t i=0; i<num_objects_; ++i)
    post_load_function((T*)objs_[i]);
}
//----------------------------------------------------------------------------

template<class T>
unsigned class_factory<T>::subobject_type_ids(unsigned *ids_) const
{
  return subclass_type_ids((T*)0, ids_);
}
//----

#ifdef PFC_BUILDOP_ASSERTS
template<class T>
const char *class_factory<T>::assert_class_name() const
{
  return typeid(T).name();
}
#endif
//----------------------------------------------------------------------------

template<class T>
template<class S>
void class_factory<T>::read_impl(prop_enum_input_archive<S> &pe_, void **objs_, usize_t num_objects_, const class_mvar_t *mvars_, unsigned num_mvars_, const uint16_t *csub_vers_) const
{
#ifdef PFC_BUILDOP_ARCHIVE_VERSION_SUPPORT
  if(pe_.has_type_info())
  {
    if(num_objects_)
    {
      // read objects and convert if necessary
      prop_enum_input_converter<S> pe_conv(pe_, mvars_, num_mvars_, csub_vers_);
      pe_conv.read(*(T*)objs_[0]);
      if(pe_conv.requires_conversion())
      {
        for(usize_t i=1; i<num_objects_; ++i)
          pe_conv.read(*(T*)objs_[i]);
      }
      else
        for(usize_t i=1; i<num_objects_; ++i)
          enum_props_most_derived(pe_, *(T*)objs_[i]);
    }
  }
  else
    for(usize_t i=0; i<num_objects_; ++i)
      enum_props_most_derived(pe_, *(T*)objs_[i]);
#else
  for(usize_t i=0; i<num_objects_; ++i)
    enum_props_most_derived(pe_, *(T*)objs_[i]);
#endif
  pe_.reset();
}
//----------------------------------------------------------------------------


//============================================================================
// class_repository_base
//============================================================================
class_repository_base *class_repository_base::find_repository(const str_id &id_)
{
  hash_map<str_id, class_repository_base*>::const_iterator it=s_repository_map.find(id_);
  return is_valid(it)?*it:0;
}
//----

const class_factory_base *class_repository_base::find_factory(const str_id &id_) const
{
  hash_map<str_id, const class_factory_base*>::const_iterator it=m_factories.find(id_);
  return is_valid(it)?*it:0;
}
//----

class_repository_base::const_iterator class_repository_base::first_factory() const
{
  return m_factories.begin();
}
//----

unsigned class_repository_base::num_factories() const
{
  return (unsigned)m_factories.size();
}
//----------------------------------------------------------------------------

class_repository_base::class_repository_base(const str_id &id_)
{
  s_repository_map.insert(id_, this);
}
//----

class_repository_base::~class_repository_base()
{
}
//----------------------------------------------------------------------------


//============================================================================
// class_repository
//============================================================================
template<class B>
class_repository<B> &class_repository<B>::instance(const str_id &id_)
{
  static class_repository s_repository(id_);
  return s_repository;
}
//----

template<class B>
template<class C>
void class_repository<B>::add(const str_id &id_, const char *deprecated_name_, meta_type<C>)
{
  // add new class factory to the repository
  PFC_ASSERT(id_.c_str());
  static class_factory<C> s_factory;
  add_factory(id_, s_factory);

  // check for deprecated name
  if(deprecated_name_)
  {
    add_factory(deprecated_name_, s_factory);
    class_reg_info<C>::deprecated_name=deprecated_name_;
  }
}
//----

template<class B>
B *class_repository<B>::create(const str_id &id_)
{
  // search proper factory from the repository and create an object
  const class_factory_base *f=find_factory(id_);
  PFC_CHECK_WARN(f, ("Unable to instantiate class \"%s\"", id_.c_str()));
  return f?static_cast<B*>(f->create()):0;
}
//----------------------------------------------------------------------------

template<class B>
class_repository<B>::class_repository(const str_id &id_)
  :class_repository_base(id_)
{
  PFC_ASSERT_MSG(id_.c_str(), ("Class repository base class \"%s\" not registered\r\n", typeid(B).name()));
  PFC_STATIC_ASSERT_MSG(is_type_poly<B>::res, class_repository_base_class_must_be_polymorphic);
}
//----

template<class B>
class_repository<B>::~class_repository()
{
}
//----------------------------------------------------------------------------


//============================================================================
// object_repository_pool
//============================================================================
object_repository_pool::object_repository_pool()
{
  m_parent=0;
}
//----------------------------------------------------------------------------

object_repository_pool *object_repository_pool::parent() const
{
  return m_parent;
}
//----------------------------------------------------------------------------


//============================================================================
// object_repository
//============================================================================
template<class B>
object_repository<B> &object_repository<B>::instance(const str_id &id_)
{
  PFC_ASSERT_MSG(id_.c_str(), ("Repository base class \"%s\" not registered\r\n", typeid(B).name()));
  static object_repository s_repository(id_);
  return s_repository;
}
//----

template<class B>
void object_repository<B>::add_object(const str_id &id_, B &object_)
{
  PFC_ASSERT(id_.c_str());
  const char *name=object_repository_base::add_object(id_, &object_);
  object_.debug_object_name.value=name;
}
//----

template<class B>
void object_repository<B>::remove_object(B &object_)
{
  object_repository_base::remove_object(&object_);
  object_.debug_object_name.value=0;
}
//----

template<class B>
B *object_repository<B>::find_object(const str_id &id_) const
{
  PFC_ASSERT(id_.c_str());
  return static_cast<B*>(object_repository_base::find_object(id_));
}
//----

template<class B>
B *object_repository<B>::load_object(const str_id &id_, const char *file_ext_, const char *path_)
{
  PFC_ASSERT(id_.c_str());
  return static_cast<B*>(object_repository_base::load_object(id_, file_ext_, path_, type_id<B>::id));
}
//----

template<class B>
B *object_repository<B>::load_object(const str_id &id_, bin_input_stream_base &s_, const char *file_ext_, const char *path_)
{
  PFC_ASSERT(id_.c_str());
  return static_cast<B*>(object_repository_base::load_object(id_, s_, file_ext_, path_, type_id<B>::id));
}
//----------------------------------------------------------------------------

template<class B>
object_repository<B>::object_repository(const str_id &id_)
  :object_repository_base(id_)
{
  PFC_STATIC_ASSERT_MSG(is_type_poly<B>::res, object_repository_base_class_must_be_polymorphic);
}
//----

template<class B>
object_repository<B>::~object_repository()
{
}
//----

template<class B>
const char *object_repository<B>::add_object(const str_id &id_, void *p_)
{
  const char *name=object_repository_base::add_object(id_, p_);
  static_cast<B*>(p_)->debug_object_name.value=name;
  return name;
}
//----

template<class B>
void object_repository<B>::remove_object(void *p_)
{
  static_cast<B*>(p_)->debug_object_name.value=0;
  object_repository_base::remove_object(p_);
}
//----

template<class B>
void object_repository<B>::clear_container(repository_container &c_)
{
  // delete all objects in the container
  repository_container::const_iterator it=c_.begin();
  while(is_valid(it))
  {
    B *p=(B*)*it;
    PFC_DELETE(p);
    ++it;
  }
  c_.clear();
}
//----------------------------------------------------------------------------


//============================================================================
// prop_enum_input_archive
//============================================================================
template<class S>
prop_enum_input_archive<S>::prop_enum_input_archive(S &s_, const char *file_ext_, const char *path_)
  :m_stream(s_)
  ,m_has_type_info(false)
  ,m_custom_streaming(false)
  ,m_root_idx(0)
  ,m_root_factory(0)
  ,m_num_composite_sigs(0)
  ,m_composite_sigs(0)
{
  // read and check archive version
  uint16_t arch_ver;
  m_stream>>arch_ver;
  PFC_CHECK_MSG((arch_ver&0xff00)==(archive_version&0xff00),
                ("Invalid pfc archive version v%s, while expecting v%s\r\n", version_str(arch_ver).c_str(), version_str(archive_version).c_str()));

  // read the rest of the header
  uint16_t arch_flags;
  uint32_t crc32;
  m_stream>>arch_flags>>crc32;
  m_has_type_info=(arch_flags&archflag_type_info)!=0;
#ifndef PFC_BUILDOP_ARCHIVE_VERSION_SUPPORT
  PFC_CHECK_MSG(!m_has_type_info, ("Executable doesn't support handling of archives with type information\r\n"));
#endif

  // read archive properties
  uint32_t num_mono, num_poly, num_creps, num_oreps, num_objs_total;
  m_stream>>num_mono>>num_poly>>num_creps>>num_oreps>>num_objs_total;
  unsigned num_classes_total=num_mono+num_poly;
  m_stream>>m_root_idx;
  array<class_info> classes(num_classes_total); /*todo: allocate from temporal memory pool*/
  m_objects.resize(1+num_objs_total); /*todo: allocate from temporal memory pool*/
  mem_zero(m_objects.data(), (1+num_objs_total)*sizeof(m_objects[0]));
  usize_t object_idx=1;
  unsigned factory_idx=0;

  // read composite class type information
#ifdef PFC_BUILDOP_ARCHIVE_VERSION_SUPPORT
  array<char> composite_mvar_strs;
  array<class_mvar_t> composite_mvars;
  array<composite_class_sig> composite_class_sigs;
  array<uint16_t> composite_csub_vers;
  if(m_has_type_info)
  {
    // read composite type info header and allocate space for composite type info
    uint32_t num_composite_classes;
    uint32_t total_composite_mvars;
    uint32_t total_composite_mvar_str_size;
    uint32_t total_composite_csub_vers;
    m_stream>>num_composite_classes>>total_composite_mvars>>total_composite_mvar_str_size>>total_composite_csub_vers;
    composite_mvar_strs.resize(total_composite_mvar_str_size+total_composite_mvars); /*todo: allocate from temporal memory pool*/
    composite_mvars.resize(total_composite_mvars); /*todo: allocate from temporal memory pool*/
    composite_class_sigs.resize(num_composite_classes); /*todo: allocate from temporal memory pool*/
    composite_csub_vers.resize(total_composite_csub_vers); /*todo: allocate from temporal memory pool*/
    char *mvar_str=composite_mvar_strs.data();
    class_mvar_t *mvar=composite_mvars.data();
    uint16_t *csub_ver=composite_csub_vers.data();

    // read signatures for all composite classes
    for(unsigned i=0; i<num_composite_classes; ++i)
    {
      // read composite class signature (i.e. member variable types & names)
      uint8_t num_mvars, num_csub_vers=0;
      m_stream>>num_mvars;
      composite_class_sig &ccs=composite_class_sigs[i];
      ccs.mvars=mvar;
      ccs.num_mvars=num_mvars;
      ccs.csub_vers=csub_ver;
      for(unsigned mvi=0; mvi<num_mvars; ++mvi)
      {
        // read and store composite class member variable info
        archive_type_id_t type;
        uint8_t name_len;
        m_stream>>type>>name_len;
        m_stream.read(mvar_str, name_len);
        mvar->first=type;
        mvar->second=mvar_str;
        mvar_str+=name_len;
        *mvar_str++=0;
        ++mvar;
        if(type==archtype_subclass_custom)
          ++num_csub_vers;
      }

      // read composite subclass versions
      m_stream.read(csub_ver, num_csub_vers);
      csub_ver+=num_csub_vers;
    }

    // set composite type info for composite class signature validation/conversion
    m_num_composite_sigs=num_composite_classes;
    m_composite_sigs=composite_class_sigs.data();
  }
#endif

  // instantiate monomorphic objects
  uint8_t str_len;
  char name[256];
  for(unsigned i=0; i<num_mono; ++i)
  {
    // find monomorphic class factory
    m_stream>>str_len;
    m_stream.read(name, str_len);
    name[str_len]=0;
    const class_factory_base *fact=find_mono_factory(name);
    PFC_CHECK_WARN(fact!=0, ("Unable to instantiate class \"%s\"", name));

    // instantiate object for the class
    uint32_t num_inst, total_bytes=0;
    m_stream>>num_inst;
    uint8_t class_flags=0;
    if(arch_ver>=0x1520)
      m_stream>>class_flags;
#ifdef PFC_BUILDOP_ARCHIVE_VERSION_SUPPORT
    if(m_has_type_info)
      m_stream>>total_bytes;
#endif
    classes[factory_idx].factory=fact;
    classes[factory_idx].flags=class_flags;
    classes[factory_idx].num_instancies=num_inst;
    classes[factory_idx].total_bytes=total_bytes;
    ++factory_idx;
    if(fact)
    {
      fact->create(&m_objects[object_idx], num_inst);
      if(m_root_idx>=object_idx && m_root_idx<object_idx+num_inst)
        m_root_factory=fact;
    }
    object_idx+=num_inst;
  }

  // instantiate polymorphic objects
  for(unsigned rep_idx=0; rep_idx<num_creps; ++rep_idx)
  {
    // find class repository
    m_stream>>str_len;
    m_stream.read(name, str_len);
    name[str_len]=0;
    class_repository_base *rep=find_class_repository(name);
    PFC_CHECK_WARN(rep!=0, ("Class repository \"%s\" not registered", name));
    uint32_t num_classes;
    m_stream>>num_classes;

    // process classes in the class repository
    for(unsigned i=0; i<num_classes; ++i)
    {
      // find class factory
      m_stream>>str_len;
      m_stream.read(name, str_len);
      name[str_len]=0;
      const class_factory_base *fact=rep?rep->find_factory(name):0;
      PFC_CHECK_WARN(!m_has_type_info || fact!=0, ("Unable to instantiate class \"%s\"\r\n", name));
      PFC_CHECK_MSG(m_has_type_info || fact!=0, ("Unable to instantiate class \"%s\"\r\n", name));

      // instantiate objects for the class
      uint32_t num_inst, total_bytes=0;
      m_stream>>num_inst;
      uint8_t class_flags=0;
      if(arch_ver>=0x1520)
        m_stream>>class_flags;
#ifdef PFC_BUILDOP_ARCHIVE_VERSION_SUPPORT
      if(m_has_type_info)
        m_stream>>total_bytes;
#endif
      classes[factory_idx].factory=fact;
      classes[factory_idx].flags=class_flags;
      classes[factory_idx].num_instancies=num_inst;
      classes[factory_idx].total_bytes=total_bytes;
      ++factory_idx;
      if(fact)
      {
        fact->create(&m_objects[object_idx], num_inst);
        if(m_root_idx>=object_idx && m_root_idx<object_idx+num_inst)
          m_root_factory=fact;
      }
      object_idx+=num_inst;
    }
  }

  // setup orep object pointers
  for(unsigned rep_idx=0; rep_idx<num_oreps; ++rep_idx)
  {
    // find object repository
    m_stream>>str_len;
    m_stream.read(name, str_len);
    name[str_len]=0;
    object_repository_base *rep=find_object_repository(name);
    PFC_CHECK_WARN(rep!=0, ("No objects added to \"%s\" object repository", name));
    uint32_t num_objs;
    m_stream>>num_objs;

    // process objects in the object repository
    for(unsigned i=0; i<num_objs; ++i)
    {
      // read object
      m_stream>>str_len;
      m_stream.read(name, str_len);
      name[str_len]=0;
      m_objects[object_idx++]=rep?rep->load_object(name, file_ext_, path_):0;
    }
  }

  // read data for instantiated classes
#ifdef PFC_BUILDOP_ARCHIVE_VERSION_SUPPORT
  {
    object_idx=1;
    array<char> mvar_strbuf(65536); /*todo: allocate from temporal memory pool*/
    uint16_t csub_vers[max_subclasses];
    class_mvar_t mvars[256];
    for(unsigned ci=0; ci<num_classes_total; ++ci)
    {
      // check if factory for the class is registered
      const class_factory_base *fact=classes[ci].factory;
      if(fact)
      {
        usize_t num_inst=classes[ci].num_instancies;
        if(m_has_type_info)
        {
          if(classes[ci].flags&classflag_var_csig)
          {
            // read variable class signature objects
            for(unsigned i=0; i<num_inst; ++i)
            {
              unsigned num_mvars=read_type_info(mvars, csub_vers, mvar_strbuf.data());
              fact->read(*this, &m_objects[object_idx], 1, mvars, num_mvars, csub_vers);
              ++object_idx;
            }
          }
          else
          {
            // read constant class signature objects
            unsigned num_mvars=read_type_info(mvars, csub_vers, mvar_strbuf.data());
            fact->read(*this, &m_objects[object_idx], num_inst, mvars, num_mvars, csub_vers);
            object_idx+=num_inst;
          }
        }
        else
        {
          fact->read(*this, &m_objects[object_idx], num_inst, 0, 0, 0);
          object_idx+=num_inst;
        }
      }
      else
      {
        // skip class data
        if(m_has_type_info && !(classes[ci].flags&classflag_var_csig))
          read_type_info(mvars, csub_vers, mvar_strbuf.data());
        m_stream.skip(classes[ci].total_bytes);
        object_idx+=classes[ci].num_instancies;
      }
    }
  }
#else
  object_idx=1;
  for(unsigned i=0; i<num_classes_total; ++i)
  {
    // read data
    unsigned num_inst=classes[i].num_instancies;
    classes[i].factory->read(*this, &m_objects[object_idx], num_inst, 0, 0, 0);
    object_idx+=num_inst;
  }
#endif

  // call post-load functions for all loaded objects
  object_idx=1;
  for(unsigned i=0; i<num_classes_total; ++i)
  {
    const class_factory_base *fact=classes[i].factory;
    usize_t num_inst=classes[i].num_instancies;
    if(fact)
      fact->post_load(&m_objects[object_idx], num_inst);
    object_idx+=num_inst;
  }

  // reset composite class signature info
  m_num_composite_sigs=0;
  m_composite_sigs=0;
}
//----

template<class S>
void prop_enum_input_archive<S>::reset()
{
#ifdef PFC_BUILDOP_ARCHIVE_VERSION_SUPPORT
  m_custom_streaming=false;
#endif
}
//----

template<class S>
S &prop_enum_input_archive<S>::stream() const
{
  return m_stream;
}
//----

template<class S>
const class_mvar_t *prop_enum_input_archive<S>::composite_type_info(archive_type_id_t typeid_, unsigned &num_mvars_, const uint16_t *&csub_vers_) const
{
  // return composite class signature
  PFC_ASSERT_PEDANTIC(typeid_>=archtype_class_start && typeid_<archtype_class_start+m_num_composite_sigs);
  const composite_class_sig &sig=m_composite_sigs[typeid_-archtype_class_start];
  num_mvars_=sig.num_mvars;
  csub_vers_=sig.csub_vers;
  return sig.mvars;
}
//----

template<class S>
bool prop_enum_input_archive<S>::has_type_info() const
{
  return m_has_type_info;
}
//----------------------------------------------------------------------------

template<class S>
void *prop_enum_input_archive<S>::root_object(unsigned type_id_)
{
#ifdef PFC_BUILDOP_ASSERTS
  if(m_root_factory && type_id_)
  {
    unsigned subids[max_subclasses];
    unsigned num_subids=m_root_factory->subobject_type_ids(subids);
    for(unsigned i=0; i<num_subids; ++i)
      if(subids[i]==type_id_)
        return m_objects[m_root_idx];
    PFC_ERRORF("Unable to cast archive type \"%s\" to the requested type\r\n", m_root_factory->assert_class_name());
  }
#endif
  return m_objects[m_root_idx];
}
//----

template<class S>
template<class T>
bool prop_enum_input_archive<S>::subclass(T*)
{
#ifdef PFC_BUILDOP_ARCHIVE_VERSION_SUPPORT
  m_custom_streaming=false;
#endif
  return true;
}
//----

template<class S>
template<class T>
unsigned prop_enum_input_archive<S>::set_custom_streaming(T&, unsigned version_)
{
#ifdef PFC_BUILDOP_ARCHIVE_VERSION_SUPPORT
  if(m_has_type_info)
    m_stream.skip(sizeof(archive_object_size_t));
  m_custom_streaming=true;
#endif
  return version_;
}
//----

template<class S>
template<typename T>
bool prop_enum_input_archive<S>::var(T &v_, unsigned flags_, const char *mvar_name_)
{
#ifdef PFC_BUILDOP_ARCHIVE_VERSION_SUPPORT
  // skip type-id for custom streamed variable
  if(m_has_type_info && m_custom_streaming && !(flags_&mvarflag_array_tail))
    m_stream.skip(sizeof(archive_type_id_t));
#endif

  // switch to proper streaming for the given target type
  stream(v_, meta_case<is_type_equal<T, bool>::res?0:
                       is_type_fund<T>::res?1:
                       is_type_enum<T>::res?2:
                       is_type_class<T>::res?3:
                       is_type_ptr<T>::res?4:
                       -1>());
  return true;
}
//----

template<class S>
template<typename T, class C>
bool prop_enum_input_archive<S>::var(T &v_, unsigned flags_, const char *mvar_name_, C &ve_)
{
  var(v_, flags_, mvar_name_);
  return true;
}
//----

template<class S>
template<typename T, class C>
bool prop_enum_input_archive<S>::var(T &v_, unsigned flags_, const char *mvar_name_, C &ve_, void(*post_mutate_func_)(C*))
{
  var(v_, flags_, mvar_name_);
  return true;
}
//----

template<class S>
template<typename T, class C>
bool prop_enum_input_archive<S>::var(T &v_, unsigned flags_, const char *mvar_name_, C &ve_, void(C::*mutate_func_)(const T&, unsigned var_index_), unsigned var_index_)
{
  var(v_, flags_, mvar_name_);
  return true;
}
//----

template<class S>
template<typename T>
bool prop_enum_input_archive<S>::avar(T *a_, usize_t size_, unsigned flags_, const char *mvar_name_)
{
#ifdef PFC_BUILDOP_ARCHIVE_VERSION_SUPPORT
  if(m_has_type_info)
  {
    if(m_custom_streaming)
      m_stream.skip(sizeof(archive_type_id_t));
    else
    {
      // get number of array items stored to the archive
      archive_array_size_t num_objects;
      m_stream>>num_objects;
      PFC_CHECK_MSG(num_objects==size_, ("Number of objects in the archive (%i) for variable \"%s\" doesn't match the number of objects to be read (%i)\r\n", num_objects, mvar_name_?mvar_name_:"", size_));
    }
  }
#endif

  // read array objects
  for(usize_t i=0; i<size_; ++i)
    stream(a_[i], meta_case<is_type_equal<T, bool>::res?0:
                            is_type_fund<T>::res?1:
                            is_type_enum<T>::res?2:
                            is_type_class<T>::res?3:
                            is_type_ptr<T>::res?4:
                            -1>());
  return true;
}
//----

template<class S>
template<typename T, class C>
bool prop_enum_input_archive<S>::avar(T *a_, usize_t size_, unsigned flags_, const char *mvar_name_, C &ve_)
{
  avar(a_, size_, flags_, mvar_name_);
  return true;
}
//----

template<class S>
template<typename T, class C>
bool prop_enum_input_archive<S>::avar(T *a_, usize_t size_, unsigned flags_, const char *mvar_name_, C &ve_, void(*post_mutate_func_)(C*))
{
  avar(a_, size_, flags_, mvar_name_);
  return true;
}
//----

template<class S>
template<typename T, class C>
bool prop_enum_input_archive<S>::avar(T *a_, usize_t size_, unsigned flags_, const char *mvar_name_, C &ve_, void(C::*mutate_func_)(const T&, unsigned index_, unsigned var_index_), unsigned var_index_)
{
  avar(a_, size_, flags_, mvar_name_);
  return true;
}
//----

template<class S>
bool prop_enum_input_archive<S>::data(void *data_, usize_t num_bytes_)
{
  // read bytes
  m_stream.read_bytes(data_, num_bytes_);
  return true;
}
//----

template<class S>
void prop_enum_input_archive<S>::skip(usize_t num_bytes_)
{
  m_stream.skip(num_bytes_);
}
//----------------------------------------------------------------------------

template<class S>
stack_str16 prop_enum_input_archive<S>::version_str(uint16_t ver_) const
{
  // return string for the archive version stored in BCD format
  stack_str16 ver_str, minor_str, rev_str;
  rev_str.format("%x", ver_&0xf);
  minor_str.format("%02x", (ver_>>4)&0xff);
  if(minor_str[1]=='0')
    minor_str[1]=0;
  ver_str.format("%x.%s%c\0", ver_>>12, minor_str.c_str(), ver_&0xf?*rev_str.c_str():0);
  return ver_str;
}
//----

template<class S>
unsigned prop_enum_input_archive<S>::read_type_info(class_mvar_t *mvars_, uint16_t *csub_vers_, char *mvar_str_buf_)
{
  // read class signature
  uint8_t num_mvars;
  unsigned num_csub_vers=0;
  m_stream>>num_mvars;
  for(unsigned mvi=0; mvi<num_mvars; ++mvi)
  {
    // read member variable type and name
    archive_type_id_t type;
    uint8_t name_len;
    m_stream>>type>>name_len;
    m_stream.read(mvar_str_buf_, name_len);
    mvars_[mvi].first=type;
    mvars_[mvi].second=mvar_str_buf_;
    mvar_str_buf_+=name_len;
    *mvar_str_buf_++=0;
    if(type==archtype_subclass_custom)
      ++num_csub_vers;
  }

  // read custom subclass versions
  m_stream.read(csub_vers_, num_csub_vers);
  return num_mvars;
}
//----

template<class S>
void prop_enum_input_archive<S>::stream(bool &v_, meta_case<0> is_type_bool_)
{
  archive_bool_t v;
  m_stream>>v;
  v_=v!=0;
}
//----

template<class S>
template<typename T>
void prop_enum_input_archive<S>::stream(T &v_, meta_case<1> is_type_fund_)
{
  m_stream>>v_;
}
//----

template<class S>
template<typename T>
void prop_enum_input_archive<S>::stream(T &v_, meta_case<2> is_type_enum_)
{
#ifdef PFC_BUILDOP_ARCHIVE_VERSION_SUPPORT
  if(m_has_type_info)
  {
    // read enum string and map to enum value
    char estr[256];
    uint8_t ssize;
    m_stream>>ssize;
    m_stream.read(estr, ssize);
    estr[ssize]=0;
    enum_value(v_, estr);
  }
  else
#endif
  {
    // read enum value
    archive_enum_t e;
    m_stream>>e;
    v_=T(e);
  }
}
//----

template<class S>
template<typename T>
void prop_enum_input_archive<S>::stream(T &v_, meta_case<3> is_type_class_)
{
  // read class variable
#ifdef PFC_BUILDOP_ARCHIVE_VERSION_SUPPORT
  bool old_custom_streaming=m_custom_streaming;
  m_custom_streaming=false;
#endif
  enum_props_most_derived(*this, v_);
  post_load_function(&v_);
#ifdef PFC_BUILDOP_ARCHIVE_VERSION_SUPPORT
  m_custom_streaming=old_custom_streaming;
#endif
}
//----

template<class S>
template<typename T>
void prop_enum_input_archive<S>::stream(T *&v_, meta_case<4> is_type_ptr_)
{
  // read pointer value
  archive_pointer_t ptr;
  m_stream>>ptr;
  v_=(T*)m_objects[ptr];
}
//----

template<class S>
template<typename T>
void prop_enum_input_archive<S>::stream(T &v_, meta_case<-1> default_)
{
  PFC_STATIC_ERROR(T, no_archiving_defined_for_the_type);
}
//----------------------------------------------------------------------------


//============================================================================
// prop_enum_output_archive
//============================================================================
template<class S>
prop_enum_output_archive<S>::prop_enum_output_archive(S &s_, bool save_type_info_)
  :m_stream(s_)
  ,m_has_type_info(save_type_info_)
  ,m_custom_streaming(false)
  ,m_is_collecting_pointers(false)
  ,m_num_mono(0)
  ,m_num_poly(0)
  ,m_num_crep(0)
  ,m_num_orep(0)
  ,m_num_objs_total(0)
  ,m_mono_list(0)
  ,m_crep_list(0)
  ,m_orep_list(0)
  ,m_ptr_mvar_pool(sizeof(ptr_mvar), meta_alignof<ptr_mvar>::res)
  ,m_composite_type_list(0)
  ,m_composite_type_tail_ptr(&m_composite_type_list)
  ,m_cur_object_type(0)
  ,m_cur_collected_class(0)
  ,m_cur_collected_object(0)
  ,m_cur_ptr_mvar(0)
  ,m_fwd_ptr(0)
{
}
//----------------------------------------------------------------------------

template<class S>
template<class T>
void prop_enum_output_archive<S>::write(const T &v_, const char *custom_id_)
{
  // collect and save objects
  object_entry obj;
  m_cur_collected_object=&obj;
  m_cur_collected_class=&ptr_type_internal<T>::inst();
  m_is_collecting_pointers=true;
  collect_pointers(&v_, meta_case<is_type_crep<T>::res?2:
                                  is_type_introspec<T>::res?3:
                                  -1>());
  m_is_collecting_pointers=false;
  m_custom_streaming=false;

  // save archive info & data
  init_save();
  save_info(obj.ptr_mvar_list->object->index, custom_id_);
  save_data();
  clean_up();
}
//----

template<class S>
template<class T>
bool prop_enum_output_archive<S>::subclass(T*)
{
#ifdef PFC_BUILDOP_ARCHIVE_VERSION_SUPPORT
  m_custom_streaming=false;
#endif
  return true;
}
//----

template<class S>
template<class T>
unsigned prop_enum_output_archive<S>::set_custom_streaming(T &v_, unsigned version_)
{
#ifdef PFC_BUILDOP_ARCHIVE_VERSION_SUPPORT
  if(m_has_type_info)
  {
    m_custom_streaming=true;
    if(m_is_collecting_pointers)
      m_cur_collected_class->total_bytes+=sizeof(archive_object_size_t);
    else
    {
      // write size of the custom streamed sub-object
      prop_enum_custom_counter pe_counter(m_has_type_info);
      enum_props_this(pe_counter, const_cast<T&>(v_));
      m_stream<<archive_object_size_t(pe_counter.num_bytes()-sizeof(archive_object_size_t));
    }
  }
#endif
  return version_;
}
//----

template<class S>
template<typename T>
bool prop_enum_output_archive<S>::var(const T &v_, unsigned flags_, const char *mvar_name_)
{
  if(m_is_collecting_pointers)
  {
#ifdef PFC_BUILDOP_ARCHIVE_VERSION_SUPPORT
    if(m_has_type_info && m_custom_streaming && !(flags_&mvarflag_array_tail))
      m_cur_collected_class->total_bytes+=sizeof(archive_type_id_t);
#endif
    // check for forwarded type
    if(m_fwd_ptr)
    {
      T *fwd_ptr=(T*)m_fwd_ptr;
      m_fwd_ptr=0;
      collect_pointers(fwd_ptr, meta_case<!is_type_fwd_introspec<T>::res?-2:
                                          is_type_orep<T>::res?1:
                                          is_type_crep<T>::res?2:
                                          is_type_introspec<T>::res?3:-1
                                         >());
      return true;
    }

    // collect pointers for the type
    collect_pointers(v_, meta_case<is_type_class<T>::res?0:
                                   is_ptr_orep<T>::res?1:
                                   is_ptr_crep<T>::res?2:
                                   is_ptr_introspec<T>::res?3:
                                   is_ptr_fwd_introspec<T>::res?4:
                                   is_type_enum<T>::res?5:
                                   -1>());
  }
  else
  {
#ifdef PFC_BUILDOP_ARCHIVE_VERSION_SUPPORT
    if(m_has_type_info && m_custom_streaming && !(flags_&mvarflag_array_tail))
      m_stream<<archive_type_id_t(type_info<T>::index);
#endif
    stream(v_, meta_case<is_type_class<T>::res?0:
                         is_type_ptr<T>::res?1:
                         is_type_equal<T, bool>::res?2:
                         is_type_fund<T>::res?3:
                         is_type_enum<T>::res?4:
                         -1>());
  }
  return true;
}
//----

template<class S>
template<typename T, class C>
bool prop_enum_output_archive<S>::var(const T &v_, unsigned flags_, const char *mvar_name_, C&)
{
  var(v_, flags_, mvar_name_);
  return true;
}
//----

template<class S>
template<typename T, class C>
bool prop_enum_output_archive<S>::var(const T &v_, unsigned flags_, const char *mvar_name_, C&, void(*post_mutate_func_)(C*))
{
  var(v_, flags_, mvar_name_);
  return true;
}
//----

template<class S>
template<typename T, class C>
bool prop_enum_output_archive<S>::var(const T &v_, unsigned flags_, const char *mvar_name_, C&, void(C::*mutate_func_)(const T&, unsigned var_index_), unsigned var_index_)
{
  var(v_, flags_, mvar_name_);
  return true;
}
//----

template<class S>
template<typename T>
bool prop_enum_output_archive<S>::avar(const T *a_, usize_t size_, unsigned flags_, const char *mvar_name_)
{
  if(m_is_collecting_pointers)
  {
#ifdef PFC_BUILDOP_ARCHIVE_VERSION_SUPPORT
    if(m_has_type_info)
    {
      // update total size
      if(m_custom_streaming)
        m_cur_collected_class->total_bytes+=sizeof(archive_type_id_t);
      else
        m_cur_collected_class->total_bytes+=sizeof(archive_array_size_t);
    }
#endif
    for(usize_t i=0; i<size_; ++i)
      collect_pointers(a_[i], meta_case<is_type_class<T>::res?0:
                                        is_ptr_orep<T>::res?1:
                                        is_ptr_crep<T>::res?2:
                                        is_ptr_introspec<T>::res?3:
                                        is_ptr_fwd_introspec<T>::res?4:
                                        is_type_enum<T>::res?5:
                                        -1>());
  }
  else
  {
#ifdef PFC_BUILDOP_ARCHIVE_VERSION_SUPPORT
    // save type information
    if(m_has_type_info)
    {
      // write type id and array size
      if(m_custom_streaming)
        m_stream<<archive_type_id_t(type_info<T>::index);
      else
        m_stream<<archive_array_size_t(size_);
    }
#endif

    // save object array
    for(usize_t i=0; i<size_; ++i)
      stream(a_[i], meta_case<is_type_class<T>::res?0:
                              is_type_ptr<T>::res?1:
                              is_type_equal<T, bool>::res?2:
                              is_type_fund<T>::res?3:
                              is_type_enum<T>::res?4:
                              -1>());
  }
  return true;
}
//----

template<class S>
template<typename T, class C>
bool prop_enum_output_archive<S>::avar(const T *a_, usize_t size_, unsigned flags_, const char *mvar_name_, C&)
{
  avar(a_, size_, flags_, mvar_name_);
  return true;
}
//----

template<class S>
template<typename T, class C>
bool prop_enum_output_archive<S>::avar(const T *a_, usize_t size_, unsigned flags_, const char *mvar_name_, C&, void(*post_mutate_func_)(C*))
{
  avar(a_, size_, flags_, mvar_name_);
  return true;
}
//----

template<class S>
template<typename T, class C>
bool prop_enum_output_archive<S>::avar(const T *a_, usize_t size_, unsigned flags_, const char *mvar_name_, C&, void(C::*mutate_func_)(const T&, unsigned index_, unsigned var_index_), unsigned var_index_)
{
  avar(a_, size_, flags_, mvar_name_);
  return true;
}
//----

template<class S>
bool prop_enum_output_archive<S>::data(const void *data_, usize_t num_bytes_)
{
  if(m_is_collecting_pointers)
    m_cur_collected_class->total_bytes+=num_bytes_;
  else
    m_stream.write_bytes(data_, num_bytes_);
  return true;
}
//----

template<class S>
template<class T>
void prop_enum_output_archive<S>::set_object_type(const T&)
{
  m_cur_object_type=&ptr_type_internal<T>::inst();
}
//----------------------------------------------------------------------------

template<class S>
typename prop_enum_output_archive<S>::ptr_mvar *prop_enum_output_archive<S>::reverse_mptr_list(ptr_mvar *mp_)
{
  // reverse the direction of the pointer mvar list
  ptr_mvar *l=mp_, *prev=0;
  while(l)
  {
    ptr_mvar *next=l->next;
    l->next=prev;
    prev=l;
    l=next;
  }
  return prev;
}
//----------------------------------------------------------------------------

template<class S>
template<class T>
void prop_enum_output_archive<S>::collect_pointers(const T &v_, meta_case<0> is_type_class_)
{
#ifdef PFC_BUILDOP_ARCHIVE_VERSION_SUPPORT
  bool old_custom_streaming=m_custom_streaming;
  m_custom_streaming=false;
#endif
  enum_props_most_derived(*this, const_cast<T&>(v_));
#ifdef PFC_BUILDOP_ARCHIVE_VERSION_SUPPORT
  m_custom_streaming=old_custom_streaming;
  if(m_has_type_info && !type_info<T>::index)
  {
    // add composite type info
    type_info<T>::index=1;
    composite_type<T>::s_instance.next=0;
    *m_composite_type_tail_ptr=&composite_type<T>::s_instance;
    m_composite_type_tail_ptr=&composite_type<T>::s_instance.next;
  }
#endif
}
//----

template<class S>
template<class T>
void prop_enum_output_archive<S>::collect_pointers(const T *p_, meta_case<1> is_ptr_orep_)
{
  m_cur_collected_class->total_bytes+=sizeof(archive_pointer_t);
  if(p_)
  {
    // insert pointer entry and pointer member variable for the pointer
    ptr_type_base &pt=ptr_type_external<typename T::base_class_t>::inst();
    typename hash_map<const void*, object_entry>::inserter ins=pt.object_ptrs.insert(p_, object_entry(), false);
    ptr_mvar *mvar=(ptr_mvar*)m_ptr_mvar_pool.alloc_block();
    mvar->object=&*ins.it;
    mvar->next=m_cur_collected_object->ptr_mvar_list;
    m_cur_collected_object->ptr_mvar_list=mvar;
    if(!pt.is_added)
    {
      // add pointer type to orep pointer type list
      pt.is_added=true;
      pt.next=m_orep_list;
      pt.total_bytes=0;
      m_orep_list=&pt;
    }
  }
}
//----

template<class S>
template<class T>
void prop_enum_output_archive<S>::collect_pointers(const T *p_, meta_case<2> is_ptr_crep_)
{
  m_cur_collected_class->total_bytes+=sizeof(archive_pointer_t);
  if(p_)
  {
    // insert pointer entry and pointer member variable for the pointer
    p_->set_object_type(*this);
    ptr_type_base &pt=*m_cur_object_type;
    typename hash_map<const void*, object_entry>::inserter ins=pt.object_ptrs.insert(p_, object_entry(), false);
    ptr_mvar *mvar=(ptr_mvar*)m_ptr_mvar_pool.alloc_block();
    mvar->object=&*ins.it;
    mvar->next=m_cur_collected_object->ptr_mvar_list;
    m_cur_collected_object->ptr_mvar_list=mvar;
    if(ins.is_new)
    {
      if(!pt.is_added)
      {
        // add repository to class repository list
        ptr_rep_base &rep=ptr_rep<typename T::base_class_t>::inst();
        if(!rep.is_added)
        {
          rep.is_added=true;
          rep.next=m_crep_list;
          m_crep_list=&rep;
        }

        // add pointer type to crep pointer type list
        pt.is_added=true;
        pt.next=rep.types;
        pt.total_bytes=0;
        rep.types=&pt;
        ++rep.num_types;
      }

      // process the pointee
      ptr_type_base *old_collected_class=m_cur_collected_class;
      m_cur_collected_class=&pt;
      object_entry *old_obj=m_cur_collected_object;
      m_cur_collected_object=mvar->object;
      enum_props(*this, static_cast<typename T::base_class_t&>(const_cast<T&>(*p_)));
      m_cur_collected_class=old_collected_class;
      m_cur_collected_object=old_obj;
    }
  }
}
//----

template<class S>
template<class T>
void prop_enum_output_archive<S>::collect_pointers(const T *p_, meta_case<3> is_ptr_introspec_)
{
  m_cur_collected_class->total_bytes+=sizeof(archive_pointer_t);
  if(p_)
  {
    // insert pointer entry and pointer member variable for the pointer
    ptr_type_base &pt=ptr_type_internal<T>::inst();
    typename hash_map<const void*, object_entry>::inserter ins=pt.object_ptrs.insert(p_, object_entry(), false);
    ptr_mvar *mvar=(ptr_mvar*)m_ptr_mvar_pool.alloc_block();
    mvar->object=&*ins.it;
    mvar->next=m_cur_collected_object->ptr_mvar_list;
    m_cur_collected_object->ptr_mvar_list=mvar;
    if(ins.is_new)
    {
      // add pointer type to monomorphic pointer type list
      if(!pt.is_added)
      {
        pt.is_added=true;
        pt.next=m_mono_list;
        pt.total_bytes=0;
        m_mono_list=&pt;
      }

      // process the pointee
      ptr_type_base *old_collected_class=m_cur_collected_class;
      m_cur_collected_class=&pt;
      object_entry *old_obj=m_cur_collected_object;
      m_cur_collected_object=mvar->object;
      enum_props_most_derived(*this, const_cast<T&>(*p_));
      m_cur_collected_class=old_collected_class;
      m_cur_collected_object=old_obj;
    }
  }
}
//----

template<class S>
template<class T>
void prop_enum_output_archive<S>::collect_pointers(const T *p_, meta_case<4> is_ptr_fwd_introspec_)
{
  if(p_)
  {
    m_fwd_ptr=(void*)p_;
    fwd_introspec(*this, (T*)p_);
  }
}
//----

template<class S>
template<typename T>
void prop_enum_output_archive<S>::collect_pointers(const T &v_, meta_case<5> is_type_enum_)
{
#ifdef PFC_BUILDOP_ARCHIVE_VERSION_SUPPORT
  if(m_has_type_info)
    m_cur_collected_class->total_bytes+=1+str_size(enum_string(v_));
  else
    m_cur_collected_class->total_bytes+=sizeof(archive_enum_t);
#else
  m_cur_collected_class->total_bytes+=sizeof(archive_enum_t);
#endif
}
//----

template<class S>
template<typename T>
void prop_enum_output_archive<S>::collect_pointers(const T&, meta_case<-1> default_)
{
  // check for unsupported types for archiving
  PFC_STATIC_ASSERT_MSG(!is_type_ptr<T>::res, unable_to_archive_given_pointer_type);
  PFC_STATIC_ASSERT_MSG(is_type_fund<T>::res, unable_to_archive_given_type);
  m_cur_collected_class->total_bytes+=is_type_equal<T, bool>::res?sizeof(archive_bool_t):sizeof(T);
}
//----

template<class S>
template<typename T>
void prop_enum_output_archive<S>::collect_pointers(const T&, meta_case<-2> null_)
{
}
//----

template<class S>
template<typename T>
void prop_enum_output_archive<S>::stream(const T &v_, meta_case<0> is_type_class_)
{
#ifdef PFC_BUILDOP_ARCHIVE_VERSION_SUPPORT
  bool old_custom_streaming=m_custom_streaming;
  m_custom_streaming=false;
#endif
  // stream the class object
  enum_props_most_derived(*this, const_cast<T&>(v_));
#ifdef PFC_BUILDOP_ARCHIVE_VERSION_SUPPORT
  m_custom_streaming=old_custom_streaming;
#endif
}
//----

template<class S>
template<typename T>
void prop_enum_output_archive<S>::stream(const T *p_, meta_case<1> is_type_ptr_)
{
  if(p_)
  {
    m_stream<<archive_pointer_t(m_cur_ptr_mvar->object->index);
    m_cur_ptr_mvar=m_cur_ptr_mvar->next;
  }
  else
    m_stream<<archive_pointer_t(0);
}
//----

template<class S>
void prop_enum_output_archive<S>::stream(bool v_, meta_case<2> is_type_bool_)
{
  m_stream<<archive_bool_t(v_);
}
//----

template<class S>
template<typename T>
void prop_enum_output_archive<S>::stream(T v_, meta_case<3> is_type_fund_)
{
  m_stream<<v_;
}
//----

template<class S>
template<typename T>
void prop_enum_output_archive<S>::stream(T v_, meta_case<4> is_type_enum_)
{
#ifdef PFC_BUILDOP_ARCHIVE_VERSION_SUPPORT
  if(m_has_type_info)
  {
    // save enum value string
    const char *estr=enum_string(v_);
    unsigned ssize=(unsigned)str_size(estr);
    PFC_ASSERT_PEDANTIC_MSG(ssize<256, ("Enumerated value string must be less than 256 bytes\r\n"));
    m_stream<<uint8_t(ssize);
    m_stream.write(estr, ssize);
  }
  else
    m_stream<<archive_enum_t(v_);
#else
  m_stream<<archive_enum_t(v_);
#endif
}
//----

template<class S>
template<typename T>
void prop_enum_output_archive<S>::stream(const T &v_, meta_case<-1> default_)
{
  PFC_STATIC_ERROR(T, unable_to_save_type);
}
//----

template<class S>
void prop_enum_output_archive<S>::init_save()
{
  // reset archive stats
  m_num_mono=0;
  m_num_poly=0;
  m_num_crep=0;
  m_num_orep=0;
  m_num_objs_total=0;

  // setup object indices for monomorphic objects
  ptr_type_base *p=m_mono_list;
  while(p)
  {
    typename hash_map<const void*, object_entry>::iterator it=p->object_ptrs.begin();
    do
    {
      it->index=archive_pointer_t(++m_num_objs_total);
      ++it;
    } while(is_valid(it));
    ++m_num_mono;
    p->is_added=false;
    p=p->next;
  }

  // setup object indices for crep objects
  ptr_rep_base *rep=m_crep_list;
  while(rep)
  {
    p=rep->types;
    while(p)
    {
      typename hash_map<const void*, object_entry>::iterator it=p->object_ptrs.begin();
      do
      {
        it->index=archive_pointer_t(++m_num_objs_total);
        ++it;
      } while(is_valid(it));
      ++m_num_poly;
      p->is_added=false;
      p=p->next;
    }
    ++m_num_crep;
    rep->is_added=false;
    rep=rep->next;
  }

  // setup object indices for orep objects
  p=m_orep_list;
  while(p)
  {
    typename hash_map<const void*, object_entry>::iterator it=p->object_ptrs.begin();
    do
    {
      it->index=archive_pointer_t(++m_num_objs_total);
      ++it;
    } while(is_valid(it));
    ++m_num_orep;
    p->is_added=false;
    p=p->next;
  }
}
//----

template<class S>
void prop_enum_output_archive<S>::save_info(archive_pointer_t root_idx_, const char *custom_id_)
{
  // setup archive flags
  uint16_t arch_flags=m_has_type_info?archflag_type_info:0;

  // write archive identifiers and version
  m_stream<<(S::is_big_endian?"PFC_ARCH":"pfc_arch");
  char custom_id[8]={0};
  if(custom_id_)
  {
    unsigned custom_id_size=(unsigned)str_size(custom_id_);
    PFC_ASSERT_MSG(custom_id_size<=8, ("Size of the custom ID must be less or equal to 8 characters\r\n"));
    mem_copy(custom_id, custom_id_, custom_id_size);
  }
  m_stream.write_bytes(custom_id, 8);
  m_stream<<uint16_t(archive_version);

  // write the rest of the header
  m_stream<<arch_flags;
  m_stream<<uint32_t(0x00000000);
  m_stream<<uint32_t(m_num_mono)<<uint32_t(m_num_poly);
  m_stream<<uint32_t(m_num_crep)<<uint32_t(m_num_orep);
  m_stream<<uint32_t(m_num_objs_total);
  m_stream<<archive_pointer_t(root_idx_);

#ifdef PFC_BUILDOP_ARCHIVE_VERSION_SUPPORT
  if(m_has_type_info)
  {
    // init composite type info
    composite_type_base *ct=m_composite_type_list;
    unsigned num_composite_classes=0;
    unsigned total_composite_mvars=0;
    unsigned total_composite_mvar_str_size=0;
    unsigned total_composite_csub_vers=0;
    while(ct)
    {
      unsigned num_mvars=0, num_csubs=0;
      const class_mvar_t *mvars=ct->init_type_info(num_composite_classes, num_mvars, num_csubs);
      total_composite_mvars+=num_mvars;
      total_composite_csub_vers+=num_csubs;
      for(unsigned i=0; i<num_mvars; ++i)
        total_composite_mvar_str_size+=mvars[i].second?(unsigned)str_size(mvars[i].second):0;
      ct=ct->next;
      ++num_composite_classes;
    }

    // save composite type info
    m_stream<<uint32_t(num_composite_classes);
    m_stream<<uint32_t(total_composite_mvars);
    m_stream<<uint32_t(total_composite_mvar_str_size);
    m_stream<<uint32_t(total_composite_csub_vers);
    ct=m_composite_type_list;
    while(ct)
    {
      ct->save_type_info(m_stream);
      ct=ct->next;
    }
  }
#endif

  // save monomorphic class infos
  ptr_type_base *type_mono=m_mono_list;
  while(type_mono)
  {
    type_mono->save_info(*this);
    type_mono=type_mono->next;
  }

  // save class repository infos
  ptr_rep_base *crep=m_crep_list;
  while(crep)
  {
    // write repository properties
    unsigned name_len=(unsigned)str_size(crep->name);
    PFC_ASSERT_MSG(name_len<256, ("Class repository name is too long (%i) for archiving\r\n", name_len));
    m_stream<<uint8_t(name_len);
    m_stream.write(crep->name, name_len);
    m_stream<<uint32_t(crep->num_types);

    // save all repository classes
    ptr_type_base *type_crep=crep->types;
    while(type_crep)
    {
      type_crep->save_info(*this);
      type_crep=type_crep->next;
    }
    crep=crep->next;
  }

  // save object repositories
  ptr_type_base *orep=m_orep_list;
  while(orep)
  {
    orep->save_info(*this);
    orep->save_data(*this);
    orep=orep->next;
  }
}
//----

template<class S>
void prop_enum_output_archive<S>::save_data()
{
  // save monomorphic objects
  ptr_type_base *type_mono=m_mono_list;
  while(type_mono)
  {
    type_mono->save_data(*this);
    type_mono=type_mono->next;
  }

  // save crep objects
  ptr_rep_base *crep=m_crep_list;
  while(crep)
  {
    ptr_type_base *type_crep=crep->types;
    while(type_crep)
    {
      type_crep->save_data(*this);
      type_crep=type_crep->next;
    }
    crep=crep->next;
  }
}
//----

template<class S>
void prop_enum_output_archive<S>::clean_up()
{
  // clean monomorphic objects
  ptr_type_base *p=m_mono_list;
  while(p)
  {
    p->object_ptrs.clear();
    p=p->next;
  }

  // clean crep objects
  ptr_rep_base *rep=m_crep_list;
  while(rep)
  {
    p=rep->types;
    while(p)
    {
      p->object_ptrs.clear();
      p=p->next;
    }
    rep->num_types=0;
    rep->types=0;
    rep=rep->next;
  }

  // clear orep objects
  p=m_orep_list;
  while(p)
  {
    p->object_ptrs.clear();
    p=p->next;
  }

  // reset composite type indices
  composite_type_base *ct=m_composite_type_list;
  while(ct)
  {
    ct->reset_type_index();
    ct=ct->next;
  }
  m_composite_type_list=0;
  m_composite_type_tail_ptr=&m_composite_type_list;

  m_ptr_mvar_pool.force_release();
}
//----------------------------------------------------------------------------


//============================================================================
// prop_enum_output_archive::type_info
//============================================================================
template<class S>
template<typename T>
struct prop_enum_output_archive<S>::type_info
{
  static unsigned index;
};
//----

template<class S> template<typename T> unsigned prop_enum_output_archive<S>::type_info<T>::index=archive_mvar_type_id<T>::res;
//----------------------------------------------------------------------------


//============================================================================
// prop_enum_output_archive::composite_type_base
//============================================================================
template<class S>
struct prop_enum_output_archive<S>::composite_type_base
{
  // saving
  virtual const class_mvar_t *init_type_info(unsigned typeinfo_index_, unsigned &num_mvars_, unsigned &num_csubs_) const=0;
  virtual void save_type_info(S&) const=0;
  virtual void reset_type_index() const=0;
  //--------------------------------------------------------------------------

  composite_type_base *next;
};
//----------------------------------------------------------------------------


//============================================================================
// prop_enum_output_archive::composite_type
//============================================================================
template<class S>
template<class T>
struct prop_enum_output_archive<S>::composite_type: composite_type_base
{
  // saving
  virtual const class_mvar_t *init_type_info(unsigned typeinfo_index_, unsigned &num_mvars_, unsigned &num_csubs_) const;
  virtual void save_type_info(S&) const;
  virtual void reset_type_index() const;
  //--------------------------------------------------------------------------

  static composite_type s_instance;
};
//----------------------------------------------------------------------------

template<class S>
template<class T>
typename prop_enum_output_archive<S>::template composite_type<T> prop_enum_output_archive<S>::composite_type<T>::s_instance;
//----------------------------------------------------------------------------

template<class S>
template<class T>
const class_mvar_t *prop_enum_output_archive<S>::composite_type<T>::init_type_info(unsigned typeinfo_index_, unsigned &num_mvars_, unsigned &num_csubs_) const
{
  // collect type info and init type index
  prop_enum_type_info pe(type_id<T>::id);
  enum_props_most_derived(pe, *(T*)0);
  const class_mvar_t *mvars=pe.mvars(num_mvars_);
  num_csubs_=pe.num_custom_subclasses();
  type_info<T>::index=(typeinfo_index_+archtype_class_start);
  return mvars;
}
//----

template<class S>
template<class T>
void prop_enum_output_archive<S>::composite_type<T>::save_type_info(S &s_) const
{
  // save composite class type info to the stream
  prop_enum_type_info pe(type_id<T>::id);
  enum_props_most_derived(pe, *(T*)0);
  pe.save_type_info(s_);
}
//----

template<class S>
template<class T>
void prop_enum_output_archive<S>::composite_type<T>::reset_type_index() const
{
  type_info<T>::index=0;
}
//----------------------------------------------------------------------------


//============================================================================
// prop_enum_output_archive::prop_enum_type_info
//============================================================================
template<class S>
class prop_enum_output_archive<S>::prop_enum_type_info: public prop_enum_interface_base<prop_enum_type_info>
{
public:
  // construction
  enum {pe_type=penum_type_info};
  PFC_INLINE prop_enum_type_info(unsigned leaf_type_id_);
  void save_type_info(S&);
  unsigned type_info_size();
  PFC_INLINE const class_mvar_t *mvars(unsigned &num_mvars_) const;
  PFC_INLINE unsigned num_custom_subclasses() const;
  //--------------------------------------------------------------------------

  // serialization
  template<class T> PFC_INLINE bool subclass(T*);
  template<class T> PFC_INLINE unsigned set_custom_streaming(T&, unsigned version_);
  template<typename T> PFC_INLINE bool var(const volatile T&, unsigned flags_=0, const char *mvar_name_=0);
  template<typename T, class C> PFC_INLINE bool var(const volatile T&, unsigned flags_, const char *mvar_name_, C&);
  template<typename T, class C> PFC_INLINE bool var(const volatile T&, unsigned flags_, const char *mvar_name_, C&, void(*post_mutate_func_)(C*));
  template<typename T, class C> PFC_INLINE bool var(const volatile T&, unsigned flags_, const char *mvar_name_, C&, void(C::*mutate_func_)(const T&, unsigned var_index_), unsigned var_index_);
  template<typename T> PFC_INLINE bool avar(const volatile T*, usize_t size_, unsigned flags_=0, const char *mvar_name_=0);
  template<typename T, class C> PFC_INLINE bool avar(const volatile T*, usize_t size_, unsigned flags_, const char *mvar_name_, C&);
  template<typename T, class C> PFC_INLINE bool avar(const volatile T*, usize_t size_, unsigned flags_, const char *mvar_name_, C&, void(*post_mutate_func_)(C*));
  template<typename T, class C> PFC_INLINE bool avar(const volatile T*, usize_t size_, unsigned flags_, const char *mvar_name_, C&, void(C::*mutate_func_)(const T&, unsigned index_, unsigned var_index_), unsigned var_index_);
  PFC_INLINE bool data(const void*, usize_t num_bytes_);
  //--------------------------------------------------------------------------

private:
  void operator=(const prop_enum_type_info&); // not implemented
  //--------------------------------------------------------------------------

  static class_mvar_t s_mvars[];
  static uint16_t s_custom_subclass_vers[];
  const unsigned m_leaf_type_id;
  unsigned m_num_mvars;
  unsigned m_num_custom_subclasses;
  bool m_custom_streaming;
};
//----------------------------------------------------------------------------

template<class S> class_mvar_t prop_enum_output_archive<S>::prop_enum_type_info::s_mvars[256];
template<class S> uint16_t prop_enum_output_archive<S>::prop_enum_type_info::s_custom_subclass_vers[max_subclasses];
//----------------------------------------------------------------------------

template<class S>
prop_enum_output_archive<S>::prop_enum_type_info::prop_enum_type_info(unsigned leaf_type_id_)
  :m_leaf_type_id(leaf_type_id_)
  ,m_num_mvars(0)
  ,m_num_custom_subclasses(0)
  ,m_custom_streaming(false)
{
}
//----

template<class S>
void prop_enum_output_archive<S>::prop_enum_type_info::save_type_info(S &s_)
{
  // save member variable and subclass into to the stream
  PFC_ASSERT_PEDANTIC_MSG(m_num_mvars<256, ("Class must have less than 256 exposed member variables\r\n"));
  s_<<uint8_t(m_num_mvars);
  for(unsigned i=0; i<m_num_mvars; ++i)
  {
    const char *mvar_name=s_mvars[i].second;
    unsigned name_len=mvar_name?(unsigned)str_size(mvar_name):0;
    PFC_ASSERT_PEDANTIC(name_len<256);
    s_<<s_mvars[i].first;
    s_<<uint8_t(name_len);
    s_.write(mvar_name, name_len);
  }

  // save custom subclass versions
  s_.write(s_custom_subclass_vers, m_num_custom_subclasses);
}
//----

template<class S>
unsigned prop_enum_output_archive<S>::prop_enum_type_info::type_info_size()
{
  // calculate total type info size in bytes
  unsigned size=1+m_num_mvars*(sizeof(s_mvars->first)+1)+m_num_custom_subclasses*sizeof(*s_custom_subclass_vers);
  for(unsigned i=0; i<m_num_mvars; ++i)
  {
    const char *mvar_name=s_mvars[i].second;
    size+=mvar_name?(unsigned)str_size(mvar_name):0;
  }
  return size;
}
//----

template<class S>
const class_mvar_t *prop_enum_output_archive<S>::prop_enum_type_info::mvars(unsigned &num_mvars_) const
{
  // get member variable info
  num_mvars_=m_num_mvars;
  return s_mvars;
}
//----

template<class S>
unsigned prop_enum_output_archive<S>::prop_enum_type_info::num_custom_subclasses() const
{
  return m_num_custom_subclasses;
}
//----------------------------------------------------------------------------

template<class S>
template<class T>
bool prop_enum_output_archive<S>::prop_enum_type_info::subclass(T*)
{
  // store standard subclass boundary marker
  s_mvars[m_num_mvars].first=archtype_subclass;
  s_mvars[m_num_mvars].second=class_reg_info<T>::reg_name?class_reg_info<T>::reg_name:(type_id<T>::id==m_leaf_type_id && leaf_class_alias((T*)0))?leaf_class_alias((T*)0)->c_str():class_typename((T*)0);
  m_custom_streaming=false;
  ++m_num_mvars;
  return true;
}
//----

template<class S>
template<class T>
unsigned prop_enum_output_archive<S>::prop_enum_type_info::set_custom_streaming(T&, unsigned version_)
{
  // store custom streaming subclass boundary marker
  PFC_ASSERT(m_num_custom_subclasses<max_subclasses);
  s_mvars[m_num_mvars-1].first=archtype_subclass_custom;
  s_custom_subclass_vers[m_num_custom_subclasses++]=uint16_t(version_);
  m_custom_streaming=true;
  return version_;
}
//----

template<class S>
template<typename T>
bool prop_enum_output_archive<S>::prop_enum_type_info::var(const volatile T&, unsigned flags_, const char *mvar_name_)
{
  if(!m_custom_streaming)
  {
    // store type info
    s_mvars[m_num_mvars].first=archive_type_id_t(is_type_ptr<T>::res?archive_mvar_type_id<void*>::res:type_info<T>::index);
    s_mvars[m_num_mvars].second=mvar_name_;
    ++m_num_mvars;
  }
  return true;
}
//----

template<class S>
template<typename T, class C>
bool prop_enum_output_archive<S>::prop_enum_type_info::var(const volatile T &v_, unsigned flags_, const char *mvar_name_, C&)
{
  var(v_, flags_, mvar_name_);
  return true;
}
//----

template<class S>
template<typename T, class C>
bool prop_enum_output_archive<S>::prop_enum_type_info::var(const volatile T &v_, unsigned flags_, const char *mvar_name_, C&, void(*post_mutate_func_)(C*))
{
  var(v_, flags_, mvar_name_);
  return true;
}
//----

template<class S>
template<typename T, class C>
bool prop_enum_output_archive<S>::prop_enum_type_info::var(const volatile T &v_, unsigned flags_, const char *mvar_name_, C&, void(C::*mutate_func_)(const T&, unsigned var_index_), unsigned var_index_)
{
  var(v_, flags_, mvar_name_);
  return true;
}
//----

template<class S>
template<typename T>
bool prop_enum_output_archive<S>::prop_enum_type_info::avar(const volatile T*, usize_t size_, unsigned flags_, const char *mvar_name_)
{
  if(!m_custom_streaming)
  {
    // store type info
    s_mvars[m_num_mvars].first=archive_type_id_t((is_type_ptr<T>::res?archive_mvar_type_id<void*>::res:type_info<T>::index)|archtype_flag_array);
    s_mvars[m_num_mvars].second=mvar_name_;
    ++m_num_mvars;
  }
  return true;
}
//----

template<class S>
template<typename T, class C>
bool prop_enum_output_archive<S>::prop_enum_type_info::avar(const volatile T *a_, usize_t size_, unsigned flags_, const char *mvar_name_, C&)
{
  avar(a_, size_, flags_, mvar_name_);
  return true;
}
//----

template<class S>
template<typename T, class C>
bool prop_enum_output_archive<S>::prop_enum_type_info::avar(const volatile T *a_, usize_t size_, unsigned flags_, const char *mvar_name_, C&, void(*post_mutate_func_)(C*))
{
  avar(a_, size_, flags_, mvar_name_);
  return true;
}
//----

template<class S>
template<typename T, class C>
bool prop_enum_output_archive<S>::prop_enum_type_info::avar(const volatile T *a_, usize_t size_, unsigned flags_, const char *mvar_name_, C&, void(C::*mutate_func_)(const T&, unsigned index_, unsigned var_index_), unsigned var_index_)
{
  avar(a_, size_, flags_, mvar_name_);
  return true;
}
//----

template<class S>
bool prop_enum_output_archive<S>::prop_enum_type_info::data(const void*, usize_t num_bytes_)
{
  PFC_ERROR_NOT_IMPL();
  return true;
}
//----------------------------------------------------------------------------


//============================================================================
// prop_enum_output_archive::prop_enum_custom_counter
//============================================================================
template<class S>
class prop_enum_output_archive<S>::prop_enum_custom_counter: public prop_enum_interface_base<prop_enum_custom_counter>
{
public:
  // construction
  enum {pe_type=penum_output};
  prop_enum_custom_counter(bool has_type_info_);
  PFC_INLINE usize_t num_bytes() const;
  //--------------------------------------------------------------------------

  // serialization
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
  //--------------------------------------------------------------------------

private:
  template<class T> PFC_INLINE void stream(const T&, meta_case<0> is_type_class_);
  template<typename T> PFC_INLINE void stream(const T*, meta_case<1> is_type_ptr_);
  PFC_INLINE void stream(bool, meta_case<2> is_type_bool_);
  template<typename T> PFC_INLINE void stream(T, meta_case<3> is_type_fund_);
  template<typename T> PFC_INLINE void stream(T, meta_case<4> is_type_enum_);
  template<typename T> PFC_INLINE void stream(const T&, meta_case<-1> default_);
  //--------------------------------------------------------------------------

  const bool m_has_type_info;
  bool m_custom_streaming;
  usize_t m_num_bytes;
};
//----------------------------------------------------------------------------

template<class S>
prop_enum_output_archive<S>::prop_enum_custom_counter::prop_enum_custom_counter(bool has_type_info_)
  :m_has_type_info(has_type_info_)
{
  m_custom_streaming=false;
  m_num_bytes=0;
}
//----

template<class S>
usize_t prop_enum_output_archive<S>::prop_enum_custom_counter::num_bytes() const
{
  return m_num_bytes;
}
//----------------------------------------------------------------------------

template<class S>
template<class T>
bool prop_enum_output_archive<S>::prop_enum_custom_counter::subclass(T*)
{
  m_custom_streaming=false;
  return true;
}
//----

template<class S>
template<class T>
unsigned prop_enum_output_archive<S>::prop_enum_custom_counter::set_custom_streaming(T&, unsigned version_)
{
  if(m_has_type_info)
    m_num_bytes+=sizeof(archive_object_size_t);
  m_custom_streaming=true;
  return version_;
}
//----

template<class S>
template<typename T>
bool prop_enum_output_archive<S>::prop_enum_custom_counter::var(const T &v_, unsigned flags_, const char *mvar_name_)
{
  if(m_has_type_info && m_custom_streaming && !(flags_&mvarflag_array_tail))
    m_num_bytes+=sizeof(archive_type_id_t);
  stream(v_, meta_case<is_type_class<T>::res?0:
                       is_type_ptr<T>::res?1:
                       is_type_equal<T, bool>::res?2:
                       is_type_fund<T>::res?3:
                       is_type_enum<T>::res?4:
                       -1>());
  return true;
}
//----

template<class S>
template<typename T, class C>
bool prop_enum_output_archive<S>::prop_enum_custom_counter::var(const T &v_, unsigned flags_, const char *mvar_name_, C&)
{
  var(v_, flags_, mvar_name_);
  return true;
}
//----

template<class S>
template<typename T, class C>
bool prop_enum_output_archive<S>::prop_enum_custom_counter::var(const T &v_, unsigned flags_, const char *mvar_name_, C&, void(*post_mutate_func_)(C*))
{
  var(v_, flags_, mvar_name_);
  return true;
}
//----

template<class S>
template<typename T, class C>
bool prop_enum_output_archive<S>::prop_enum_custom_counter::var(const T &v_, unsigned flags_, const char *mvar_name_, C&, void(C::*mutate_func_)(const T&, unsigned var_index_), unsigned var_index_)
{
  var(v_, flags_, mvar_name_);
  return true;
}
//----

template<class S>
template<typename T>
bool prop_enum_output_archive<S>::prop_enum_custom_counter::avar(const T *a_, usize_t size_, unsigned flags_, const char *mvar_name_)
{
  if(m_has_type_info)
    m_num_bytes+=m_custom_streaming?sizeof(archive_type_id_t):sizeof(archive_array_size_t);
  for(usize_t i=0; i<size_; ++i)
    stream(a_[i], meta_case<is_type_class<T>::res?0:
                            is_type_ptr<T>::res?1:
                            is_type_equal<T, bool>::res?2:
                            is_type_fund<T>::res?3:
                            is_type_enum<T>::res?4:
                            -1>());
  return true;
}
//----

template<class S>
template<typename T, class C>
bool prop_enum_output_archive<S>::prop_enum_custom_counter::avar(const T *a_, usize_t size_, unsigned flags_, const char *mvar_name_, C&)
{
  avar(a_, size_, flags_, mvar_name_);
  return true;
}
//----

template<class S>
template<typename T, class C>
bool prop_enum_output_archive<S>::prop_enum_custom_counter::avar(const T *a_, usize_t size_, unsigned flags_, const char *mvar_name_, C&, void(*post_mutate_func_)(C*))
{
  avar(a_, size_, flags_, mvar_name_);
  return true;
}
//----

template<class S>
template<typename T, class C>
bool prop_enum_output_archive<S>::prop_enum_custom_counter::avar(const T *a_, usize_t size_, unsigned flags_, const char *mvar_name_, C&, void(C::*mutate_func_)(const T&, unsigned index_, unsigned var_index_), unsigned var_index_)
{
  avar(a_, size_, flags_, mvar_name_);
  return true;
}
//----

template<class S>
bool prop_enum_output_archive<S>::prop_enum_custom_counter::data(const void *data_, usize_t num_bytes_)
{
  m_num_bytes+=num_bytes_;
  return true;
}
//----------------------------------------------------------------------------

template<class S>
template<class T>
void prop_enum_output_archive<S>::prop_enum_custom_counter::stream(const T &v_, meta_case<0> is_type_class_)
{
  // add object size for custom streamed class and enumerate properties
  bool old_custom_streaming=m_custom_streaming;
  m_custom_streaming=false;
  enum_props_most_derived(*this, const_cast<T&>(v_));
  m_custom_streaming=old_custom_streaming;
}
//----

template<class S>
template<typename T>
void prop_enum_output_archive<S>::prop_enum_custom_counter::stream(const T*, meta_case<1> is_type_ptr_)
{
  m_num_bytes+=sizeof(archive_pointer_t);
}
//----

template<class S>
void prop_enum_output_archive<S>::prop_enum_custom_counter::stream(bool, meta_case<2> is_type_bool_)
{
  m_num_bytes+=sizeof(archive_bool_t);
}
//----

template<class S>
template<typename T>
void prop_enum_output_archive<S>::prop_enum_custom_counter::stream(T, meta_case<3> is_type_fund_)
{
  m_num_bytes+=sizeof(T);
}
//----

template<class S>
template<typename T>
void prop_enum_output_archive<S>::prop_enum_custom_counter::stream(T v_, meta_case<4> is_type_enum_)
{
  if(m_has_type_info)
  {
    const char *estr=enum_string(v_);
    unsigned ssize=(unsigned)str_size(estr);
    m_num_bytes+=ssize+1;
  }
  else
    m_num_bytes+=sizeof(archive_enum_t);
}
//----

template<class S>
template<typename T>
void prop_enum_output_archive<S>::prop_enum_custom_counter::stream(const T&, meta_case<-1> default_)
{
  PFC_STATIC_ERROR(T, unable_to_save_type);
}
//----------------------------------------------------------------------------


//============================================================================
// prop_enum_output_archive::ptr_mvar
//============================================================================
template<class S>
struct prop_enum_output_archive<S>::ptr_mvar
{
  object_entry *object;
  ptr_mvar *next;
};
//----------------------------------------------------------------------------


//============================================================================
// prop_enum_output_archive::object_entry
//============================================================================
template<class S>
struct prop_enum_output_archive<S>::object_entry
{
  // construction
  PFC_INLINE object_entry();
  //--------------------------------------------------------------------------

  archive_pointer_t index;
  ptr_mvar *ptr_mvar_list;
};
//----------------------------------------------------------------------------

template<class S>
prop_enum_output_archive<S>::object_entry::object_entry()
  :index(0)
  ,ptr_mvar_list(0)
{
}
//----------------------------------------------------------------------------


//============================================================================
// prop_enum_output_archive::ptr_type_base
//============================================================================
template<class S>
struct prop_enum_output_archive<S>::ptr_type_base
{
  // construction and saving
  PFC_INLINE ptr_type_base(const char *name_);
  virtual void save_info(prop_enum_output_archive&) const;
  virtual void save_data(prop_enum_output_archive&)=0;
  //--------------------------------------------------------------------------

  const char *name;
  bool is_added;
  ptr_type_base *next;
  usize_t total_bytes;
  hash_map<const void*, object_entry> object_ptrs;
};
//----------------------------------------------------------------------------

template<class S>
prop_enum_output_archive<S>::ptr_type_base::ptr_type_base(const char *name_)
  :name(name_)
  ,is_added(false)
  ,next(0)
  ,total_bytes(0)
{
}
//----

template<class S>
void prop_enum_output_archive<S>::ptr_type_base::save_info(prop_enum_output_archive &pe_) const
{
  // write type info
  unsigned name_len=(unsigned)str_size(name);
  PFC_ASSERT_MSG(name_len<256, ("Class name is too long (%i) for archiving\r\n", name_len));
  pe_.m_stream<<uint8_t(name_len);
  pe_.m_stream.write(name, name_len);
  pe_.m_stream<<uint32_t(object_ptrs.size());
}
//----------------------------------------------------------------------------


//============================================================================
// prop_enum_output_archive::ptr_type_internal
//============================================================================
template<class S>
template<typename T>
class prop_enum_output_archive<S>::ptr_type_internal: public ptr_type_base
{
public:
  // construction and saving
  static PFC_INLINE ptr_type_internal &inst()
  {
    static ptr_type_internal s_instance;
    return s_instance;
  }
  virtual void save_info(prop_enum_output_archive&) const;
  virtual void save_data(prop_enum_output_archive&);
  //--------------------------------------------------------------------------

private:
  ptr_type_internal();
};
//----------------------------------------------------------------------------

template<class S>
template<typename T>
void prop_enum_output_archive<S>::ptr_type_internal<T>::save_info(prop_enum_output_archive &pe_) const
{
  ptr_type_base::save_info(pe_);
  pe_.m_stream<<uint8_t(is_type_var_csig<T>::res?classflag_var_csig:0);
#ifdef PFC_BUILDOP_ARCHIVE_VERSION_SUPPORT
  if(pe_.m_has_type_info)
  {
    if(is_type_var_csig<T>::res)
    {
      // calculate total type info size for variable class signature objects
      typename hash_map<const void*, object_entry>::const_iterator it=this->object_ptrs.begin();
      unsigned total_type_info_bytes=0;
      do
      {
        prop_enum_type_info pe(type_id<T>::id);
        enum_props_most_derived(pe, *(T*)it.key());
        total_type_info_bytes+=pe.type_info_size();
        ++it;
      } while(is_valid(it));
      pe_.m_stream<<uint32_t(this->total_bytes+total_type_info_bytes);
    }
    else
      pe_.m_stream<<uint32_t(this->total_bytes);
  }
#endif
}
//----

template<class S>
template<typename T>
void prop_enum_output_archive<S>::ptr_type_internal<T>::save_data(prop_enum_output_archive &pe_)
{
#ifdef PFC_BUILDOP_ARCHIVE_VERSION_SUPPORT
  if(pe_.m_has_type_info)
  {
    if(is_type_var_csig<T>::res)
    {
      // save type info & object data for each object
      typename hash_map<const void*, object_entry>::const_iterator it=this->object_ptrs.begin();
      do
      {
        // save type info
        T &obj=*(T*)it.key();
        prop_enum_type_info pe(type_id<T>::id);
        enum_props_most_derived(pe, obj);
        pe.save_type_info(pe_.m_stream);

        // save pointer data
        pe_.m_cur_ptr_mvar=pe_.reverse_mptr_list(it->ptr_mvar_list);
        enum_props_most_derived(pe_, obj);
        ++it;
      } while(is_valid(it));
      return;
    }
    else
    {
      // save type info shared by all objects
      prop_enum_type_info pe(type_id<T>::id);
      enum_props_most_derived(pe, *(T*)0);
      pe.save_type_info(pe_.m_stream);
    }
  }
#endif

  // save data of the internal objects
  typename hash_map<const void*, object_entry>::const_iterator it=this->object_ptrs.begin();
  do
  {
    // save pointer data
    pe_.m_cur_ptr_mvar=pe_.reverse_mptr_list(it->ptr_mvar_list);
    enum_props_most_derived(pe_, *(T*)it.key());
    ++it;
  } while(is_valid(it));
}
//----------------------------------------------------------------------------

template<class S>
template<typename T>
prop_enum_output_archive<S>::ptr_type_internal<T>::ptr_type_internal()
  :ptr_type_base(class_reg_info<T>::reg_name)
{
  PFC_ASSERT_MSG(this->name!=0, ("Class type \"%s\" not registered\r\n", typeid(T).name()));
}
//----------------------------------------------------------------------------


//============================================================================
// prop_enum_output_archive::ptr_type_external
//============================================================================
template<class S>
template<typename T>
class prop_enum_output_archive<S>::ptr_type_external: public ptr_type_base
{
public:
  static PFC_INLINE ptr_type_external &inst()
  {
    static ptr_type_external s_instance;
    return s_instance;
  }
  virtual void save_data(prop_enum_output_archive&);
  //--------------------------------------------------------------------------

private:
  ptr_type_external();
};
//----------------------------------------------------------------------------

template<class S>
template<typename T>
void prop_enum_output_archive<S>::ptr_type_external<T>::save_data(prop_enum_output_archive &pe_)
{
  // save names of orep objects
  typename hash_map<const void*, object_entry>::const_iterator it=this->object_ptrs.begin();
  do
  {
    object_repository<T> &orep=T::orep();
    const str_id *sid=orep.find_object_name(it.key());
    PFC_ASSERT_MSG(sid, ("Pointer of type \"%s\" doesn't exist in the object repository (unable to save unnamed object)\r\n", class_reg_info<T>::reg_name));
    const char *name=sid->c_str();
    unsigned name_len=(unsigned)str_size(name);
    PFC_ASSERT_MSG(name_len<256, ("Object name is too long (%i) for archiving\r\n", name_len));
    pe_.m_stream<<uint8_t(name_len);
    pe_.m_stream.write(name, name_len);
    ++it;
  } while(is_valid(it));
}
//----------------------------------------------------------------------------

template<class S>
template<typename T>
prop_enum_output_archive<S>::ptr_type_external<T>::ptr_type_external()
  :ptr_type_base(class_reg_info<T>::reg_name)
{
  PFC_ASSERT_MSG(this->name!=0, ("Class type \"%s\" not registered\r\n", typeid(T).name()));
}
//----------------------------------------------------------------------------


//============================================================================
// prop_enum_output_archive::ptr_rep_base
//============================================================================
template<class S>
struct prop_enum_output_archive<S>::ptr_rep_base
{
  // construction
  PFC_INLINE ptr_rep_base(const char *name_);
  //--------------------------------------------------------------------------

  const char *name;
  unsigned num_types;
  ptr_type_base *types;
  bool is_added;
  ptr_rep_base *next;
};
//----------------------------------------------------------------------------

template<class S>
prop_enum_output_archive<S>::ptr_rep_base::ptr_rep_base(const char *name_)
  :name(name_)
  ,num_types(0)
  ,types(0)
  ,is_added(false)
  ,next(0)
{
}
//----------------------------------------------------------------------------


//============================================================================
// prop_enum_output_archive::ptr_rep
//============================================================================
template<class S>
template<class T>
class prop_enum_output_archive<S>::ptr_rep: public ptr_rep_base
{
public:
  static PFC_INLINE ptr_rep &inst()
  {
    static ptr_rep s_instance;
    return s_instance;
  }
  //--------------------------------------------------------------------------

private:
  ptr_rep(const ptr_rep&); // not implemented
  PFC_INLINE ptr_rep();
};
//----------------------------------------------------------------------------

template<class S>
template<class T>
prop_enum_output_archive<S>::ptr_rep<T>::ptr_rep()
  :ptr_rep_base(class_reg_info<T>::reg_name)
{
  PFC_ASSERT_MSG(this->name!=0, ("Class type \"%s\" not registered\r\n", typeid(T).name()));
}
//----------------------------------------------------------------------------


//============================================================================
// register_class
//============================================================================
PFC_INLINE void register_class_func(void*, bool)  {}
template<class> void register_class_fwd(bool);
//----------------------------------------------------------------------------

template<class T>
void register_class(const char *name_, const char *deprecated_name_, meta_case<0> is_mono_)
{
  // insert monomorphic class factory
  extern hash_map<str_id, const class_factory_base*> g_mono_factories;
  const str_id *leaf_id=leaf_class_alias((T*)0);
  const char *name=leaf_id?leaf_id->c_str():name_;
  PFC_ASSERT_MSG(!class_reg_info<T>::reg_name || str_eq(class_reg_info<T>::reg_name, name),
                 ("While registering class \"%s\" with name \"%s\", the class has already been registered with name \"%s\"\r\n", typeid(T).name(), name, class_reg_info<T>::reg_name));
  if(class_reg_info<T>::reg_count++)
    return;
  class_reg_info<T>::reg_name=name;
  static class_factory<T> s_factory;
  hash_map<str_id, const class_factory_base*>::inserter ins=g_mono_factories.insert(name, &s_factory, false);
  PFC_ASSERT_MSG(ins.is_new, ("While registering class \"%s\" with name \"%s\", another class \"%s\" has already been registered with the name\r\n", typeid(T).name(), name, (*ins.it)->assert_class_name()));

  // check for deprecated name
  if(deprecated_name_)
  {
    ins=g_mono_factories.insert(deprecated_name_, &s_factory, false);
    PFC_ASSERT_MSG(ins.is_new, ("While registering class \"%s\" with deprecated name \"%s\", another class \"%s\" has already been registered with the name\r\n", typeid(T).name(), deprecated_name_, (*ins.it)->assert_class_name()));
    class_reg_info<T>::deprecated_name=deprecated_name_;
  }
  register_class_func((T*)0, true);
}
//----

template<class T>
void register_class(const char *name_, const char *deprecated_name_, meta_case<1> is_orep_)
{
  // insert class repository class factory
  const str_id *leaf_id=leaf_class_alias((T*)0);
  const char *name=leaf_id?leaf_id->c_str():name_;
  PFC_ASSERT_MSG(!class_reg_info<T>::reg_name || str_eq(class_reg_info<T>::reg_name, name),
                 ("While registering class \"%s\" with name \"%s\", the class has already been registered with name \"%s\"\r\n", typeid(T).name(), name, class_reg_info<T>::reg_name));
  if(class_reg_info<T>::reg_count++)
    return;
  class_reg_info<T>::reg_name=name;
  T::crep().add(leaf_id?*leaf_id:name, deprecated_name_, meta_type<T>());
  T::orep();
  register_class_func((T*)0, true);
}
//----

template<class T>
void register_class(const char *name_, const char *deprecated_name_, meta_case<2> is_crep_)
{
  // insert class repository class factory
  const str_id *leaf_id=leaf_class_alias((T*)0);
  const char *name=leaf_id?leaf_id->c_str():name_;
  PFC_ASSERT_MSG(!class_reg_info<T>::reg_name || str_eq(class_reg_info<T>::reg_name, name),
                 ("While registering class \"%s\" with name \"%s\", the class has already been registered with name \"%s\"\r\n", typeid(T).name(), name, class_reg_info<T>::reg_name));
  if(class_reg_info<T>::reg_count++)
    return;
  class_reg_info<T>::reg_name=name;
  T::crep().add(leaf_id?*leaf_id:name, deprecated_name_, meta_type<T>());
  register_class_func((T*)0, true);
}
//----

template<class T>
void register_class(const char *name_, const char *deprecated_name_, meta_case<-1> default_)
{
  PFC_STATIC_ERROR(T, unable_to_register_class_type); // the class must have PFC_MONO() or PFC_CLASS() definition for registration
}
//----------------------------------------------------------------------------


//============================================================================
// register_base_class
//============================================================================
template<class T>
void register_base_class(const char *name_, const char *deprecated_name_, meta_case<0> is_orep_)
{
  // register object repository base class
  PFC_ASSERT_MSG(!class_reg_info<T>::reg_name || str_eq(class_reg_info<T>::reg_name, name_),
                 ("While registering class \"%s\" with name \"%s\", the class has already been registered with name \"%s\"\r\n", typeid(T).name(), name_, class_reg_info<T>::reg_name));
  if(class_reg_info<T>::reg_count++)
    return;
  class_reg_info<T>::reg_name=name_;
  class_reg_info<T>::deprecated_name=deprecated_name_;
  T::orep();
  register_class_func((T*)0, true);
}
//----

template<class T>
void register_base_class(const char *name_, const char *deprecated_name_, meta_case<1> is_crep_)
{
  // register object repository base class
  PFC_ASSERT_MSG(!class_reg_info<T>::reg_name || str_eq(class_reg_info<T>::reg_name, name_),
                 ("While registering class \"%s\" with name \"%s\", the class has already been registered with name \"%s\"\r\n", typeid(T).name(), name_, class_reg_info<T>::reg_name));
  if(class_reg_info<T>::reg_count++)
    return;
  class_reg_info<T>::reg_name=name_;
  class_reg_info<T>::deprecated_name=deprecated_name_;
  T::crep();
  register_class_func((T*)0, true);
}
//----

template<class T>
void register_base_class(const char *name_, const char *deprecated_name_, meta_case<-1> default_)
{
  PFC_STATIC_ERROR(T, unable_to_register_class_type_as_base_class); // is class declared with PFC_REPOSITORY_BASE_CLASS()/PFC_BASE_CLASS() macro?
}
//----------------------------------------------------------------------------


//============================================================================
// unregister_class
//============================================================================
template<class T>
void unregister_class(meta_case<0> is_mono_)
{
  PFC_ASSERT_MSG(class_reg_info<T>::reg_name, ("Class \"%s\" hasn't been registered\r\n", typeid(T).name()));
  if(--class_reg_info<T>::reg_count)
    return;
  extern hash_map<str_id, const class_factory_base*> g_mono_factories;
  hash_map<str_id, const class_factory_base*>::iterator it=g_mono_factories.find(class_reg_info<T>::reg_name);
  g_mono_factories.erase(it);
  class_reg_info<T>::reg_name=0;
  if(class_reg_info<T>::deprecated_name)
  {
    it=g_mono_factories.find(class_reg_info<T>::deprecated_name);
    g_mono_factories.erase(it);
    class_reg_info<T>::deprecated_name=0;
  }
  register_class_func((T*)0, false);
}
//----

template<class T>
void unregister_class(meta_case<1> is_crep_)
{
  PFC_ASSERT_MSG(class_reg_info<T>::reg_name, ("Class \"%s\" hasn't been registered\r\n", typeid(T).name()));
  if(--class_reg_info<T>::reg_count)
    return;
  T::crep().remove(class_reg_info<T>::reg_name, class_reg_info<T>::deprecated_name);
  class_reg_info<T>::reg_name=0;
  class_reg_info<T>::deprecated_name=0;
  register_class_func((T*)0, false);
}
//----

template<class T>
void unregister_class(meta_case<-1> default_)
{
  PFC_STATIC_ERROR(T, unable_to_unregister_class_type);
}
//----------------------------------------------------------------------------


//============================================================================
// unregister_base_class
//============================================================================
template<class T>
void unregister_base_class(meta_bool<true> is_introspec_)
{
  class_reg_info<T>::reg_name=0;
  class_reg_info<T>::deprecated_name=0;
}
//----

template<class T>
void unregister_base_class(meta_bool<false> is_introspec_)
{
  PFC_STATIC_ERROR(T, unable_to_unregister_class_type);
}
//----------------------------------------------------------------------------


//============================================================================
// prop_enum_find_mvar
//============================================================================
prop_enum_find_mvar::prop_enum_find_mvar(const char *mvar_name_)
  :m_mvar_name(mvar_name_)
{
  m_mvar_data=0;
  m_mvar_type_id=0;
  m_mvar_post_mutate_func=0;
}
//----

void *prop_enum_find_mvar::mvar_data() const
{
  return m_mvar_data;
}
//----

unsigned prop_enum_find_mvar::mvar_type_id() const
{
  return m_mvar_type_id;
}
//----

prop_enum_find_mvar::post_mutate_func_t prop_enum_find_mvar::post_mutate_func() const
{
  return m_mvar_post_mutate_func;
}
//----------------------------------------------------------------------------

template<class T>
bool prop_enum_find_mvar::subclass(T*)
{
  return m_mvar_data==0;
}
//----

template<typename T>
bool prop_enum_find_mvar::var(T &v_, unsigned flags_, const char *mvar_name_)
{
  if(!str_eq(m_mvar_name, mvar_name_))
    return true;
  m_mvar_data=&v_;
  m_mvar_type_id=type_id<T>::id;
  return false;
}
//----

template<typename T, class C>
bool prop_enum_find_mvar::var(T &v_, unsigned flags_, const char *mvar_name_, C&)
{
  return var(v_, flags_, mvar_name_);
}
//----

template<typename T, class C>
bool prop_enum_find_mvar::var(T &v_, unsigned flags_, const char *mvar_name_, C&, void(*post_mutate_func_)(C*))
{
  m_mvar_post_mutate_func=(post_mutate_func_t)post_mutate_func_;
  return var(v_, flags_, mvar_name_);
}
//----

template<typename T, class C>
bool prop_enum_find_mvar::var(T &v_, unsigned flags_, const char *mvar_name_, C&, void(C::*mutate_func_)(const T&, unsigned var_index_), unsigned var_index_)
{
  return var(v_, flags_, mvar_name_);
}
//----

template<typename T>
bool prop_enum_find_mvar::avar(T *a_, usize_t size_, unsigned flags_, const char *mvar_name_)
{
  if(!str_eq(m_mvar_name, mvar_name_))
    return true;
  m_mvar_data=a_;
  m_mvar_type_id=type_id<T>::id;
  return false;
}
//----

template<typename T, class C>
bool prop_enum_find_mvar::avar(T *a_, usize_t size_, unsigned flags_, const char *mvar_name_, C&)
{
  return avar(a_, size_, flags_, mvar_name_);
}
//----

template<typename T, class C>
bool prop_enum_find_mvar::avar(T *a_, usize_t size_, unsigned flags_, const char *mvar_name_, C&, void(*post_mutate_func_)(C*))
{
  return avar(a_, size_, flags_, mvar_name_);
}
//----

template<typename T, class C>
bool prop_enum_find_mvar::avar(T *a_, usize_t size_, unsigned flags_, const char *mvar_name_, C&, void(C::*mutate_func_)(const T&, unsigned index_, unsigned var_index_), unsigned var_index_)
{
  return avar(a_, size_, flags_, mvar_name_);
}
//----

bool prop_enum_find_mvar::data(void*, usize_t num_bytes_)
{
  return true;
}
//----

template<typename T>
bool prop_enum_find_mvar::alias_var(T &v_, unsigned flags_, const char *alias_)
{
  return var(v_, 0, alias_);
}
//----

template<typename T>
bool prop_enum_find_mvar::alias_avar(T *a_, usize_t size_, unsigned flags_, const char *alias_)
{
  return avar(a_, size_, 0, alias_);
}
//----------------------------------------------------------------------------


//============================================================================
// pointer_mutator_poly
//============================================================================
template<class T>
pointer_mutator_poly<T>::pointer_mutator_poly()
{
  ptr_id=type_id<T>::id;
  is_orep_type=is_type_orep<T>::res;
}
//----

template<class T>
void *pointer_mutator_poly<T>::create(const char *class_name_) const
{
  // delete old and create new object
  PFC_ASSERT_MSG(!is_type_orep<T>::res, ("Unable to instantiate object repository type of classes\r\n"));
  return create_object<T>(class_name_);
}
//----

template<class T>
void pointer_mutator_poly<T>::release(void *ptr_) const
{
  if(!is_type_orep<T>::res)
    PFC_DELETE((T*)ptr_);
}
//----

template<class T>
void pointer_mutator_poly<T>::expose(prop_enum_exposure_base &pe_, void *data_) const
{
  enum_props(pe_, *(T*)data_);
}
//----

template<class T>
const char *pointer_mutator_poly<T>::registered_typename(const void *obj_) const
{
  return registered_object_typename(*(const T*)obj_);
}
//----

template<class T>
unsigned pointer_mutator_poly<T>::registered_class_typenames(const char **cnames_) const
{
  // get list of registered class names compatible with the pointer type
  class_repository_base::const_iterator it=T::crep().first_factory();
  unsigned num_cnames=0;
  while(is_valid(it))
  {
    // check if the factory creates objects compatible with the pointer type
    if(down_cast_check<T*>(*it))
      cnames_[num_cnames++]=it.key().c_str();
    ++it;
  }
  return num_cnames;
}
//----------------------------------------------------------------------------


//============================================================================
// pointer_mutator_mono
//============================================================================
template<class T>
pointer_mutator_mono<T>::pointer_mutator_mono()
{
  ptr_id=type_id<T>::id;
  is_orep_type=false;
}
//----

template<class T>
void *pointer_mutator_mono<T>::create(const char *class_name_) const
{
  // delete old and create new object
  PFC_ASSERT_MSG(str_eq(class_name_, class_reg_info<T>::reg_name), ("Given class name \"%s\" doesn't match the registered class name \"%s\"\r\n", class_name_, class_reg_info<T>::reg_name));
  return PFC_NEW(T);
}
//----

template<class T>
void pointer_mutator_mono<T>::release(void *ptr_) const
{
  PFC_DELETE((T*)ptr_);
}
//----

template<class T>
void pointer_mutator_mono<T>::expose(prop_enum_exposure_base &pe_, void *data_) const
{
  enum_props(pe_, *(T*)data_);
}
//----

template<class T>
const char *pointer_mutator_mono<T>::registered_typename(const void *obj_) const
{
  return registered_object_typename(*(const T*)obj_);
}
//----

template<class T>
unsigned pointer_mutator_mono<T>::registered_class_typenames(const char **cnames_) const
{
  // get list of registered class names compatible with the pointer type
  cnames_[0]=class_reg_info<T>::reg_name;
  return 1;
}
//----------------------------------------------------------------------------


//============================================================================
// prop_enum_exposure_base
//============================================================================
prop_enum_exposure_base::prop_enum_exposure_base(e_traverse_flags traverse_flags_)
  :m_traverse_flags(traverse_flags_)
{
  m_const_recursion=0;
  m_ptr_const_recursion=0;
  m_containing_object=0;
  m_post_mutate_func=0;
  m_mutate_func=0;
  m_mutate_arr_func=0;
  m_mutate_var_index=0;
  m_fwd_ptr=0;
}
//----------------------------------------------------------------------------

template<typename T>
bool prop_enum_exposure_base::var(const T &v_, unsigned flags_, const char *mvar_name_)
{
  // check for forwarded type
  if(m_fwd_ptr)
  {
    T *&fwd_ptr=(T*&)*m_fwd_ptr;
    m_fwd_ptr=0;
    var_type(mvar_name_, fwd_ptr, meta_case<is_type_fwd_introspec<T>::res?3:-2>());
    return true;
  }

  // apply variable flags
  if(flags_&mvarflag_hidden)
    return true;
  m_const_recursion+=!(flags_&mvarflag_mutable);
  m_ptr_const_recursion+=!(flags_&mvarflag_mutable_ptr);

  // expose type
  var_type(mvar_name_, (T&)v_, meta_case<is_type_fund<T>::res?0:
                                         is_type_class<T>::res?1:
                                         is_type_enum<T>::res?2:
                                         is_ptr_introspec<T>::res?3:
                                         is_ptr_fwd_introspec<T>::res?4:
                                         -1>());

  // restore exposure states
  m_const_recursion-=!(flags_&mvarflag_mutable);
  m_ptr_const_recursion-=!(flags_&mvarflag_mutable_ptr);
  return true;
}
//----

template<typename T, class C>
bool prop_enum_exposure_base::var(const T &v_, unsigned flags_, const char *mvar_name_, C &ve_)
{
  m_containing_object=&ve_;
  var(v_, flags_, mvar_name_);
  return true;
}
//----

template<typename T, class C>
bool prop_enum_exposure_base::var(const T &v_, unsigned flags_, const char *mvar_name_, C &ve_, void(*post_mutate_func_)(C*))
{
  // setup post-mutate function and expose the variable
  m_containing_object=&ve_;
  m_post_mutate_func=(void(*)(void*))post_mutate_func_;
  var(v_, flags_, mvar_name_);
  m_post_mutate_func=0;
  return true;
}
//----

template<typename T, class C>
bool prop_enum_exposure_base::var(const T &v_, unsigned flags_, const char *mvar_name_, C &ve_, void(C::*mutate_func_)(const T&, unsigned var_index_), unsigned var_index_)
{
  // setup mutate function, variable index and expose the variable
  m_containing_object=&ve_;
  m_mutate_func=(mutate_func_ptr_t)mutate_func_;
  m_mutate_var_index=var_index_;
  var(v_, flags_, mvar_name_);
  m_mutate_func=0;
  return true;
}
//----

template<typename T>
bool prop_enum_exposure_base::avar(const T *p_, usize_t size_, unsigned flags_, const char *mvar_name_)
{
  // apply variable flags
  PFC_ASSERT(p_ || !size_);
  if(flags_&mvarflag_hidden)
    return true;

  // expose array variable
  const char *class_name=p_?registered_object_typename(*p_):0;
  if(!class_name)
    class_name=p_?object_typename(*p_):0;
  if(begin_class(mvar_name_, class_name))
  {
    m_post_mutate_func=0;
    m_mutate_arr_func=0;
    for(usize_t i=0; i<size_; ++i)
    {
      stack_str32 label;
      label.format("[%i]", i);
      var(p_[i], flags_, label.c_str());
    }
    end_class();
  }
  return true;
}
//----

template<typename T, class C>
bool prop_enum_exposure_base::avar(const T *a_, usize_t size_, unsigned flags_, const char *mvar_name_, C &ve_)
{
  m_containing_object=&ve_;
  avar(a_, size_, flags_, mvar_name_);
  return true;
}
//----

template<typename T, class C>
bool prop_enum_exposure_base::avar(const T *a_, usize_t size_, unsigned flags_, const char *mvar_name_, C &ve_, void(*post_mutate_func_)(C*))
{
  // setup post-mutate function and expose the variable
  m_containing_object=&ve_;
  m_post_mutate_func=(void(*)(void*))post_mutate_func_;
  avar(a_, size_, flags_, mvar_name_);
  m_post_mutate_func=0;
  return true;
}
//----

template<typename T, class C>
bool prop_enum_exposure_base::avar(const T *a_, usize_t size_, unsigned flags_, const char *mvar_name_, C &ve_, void(C::*mutate_func_)(const T&, unsigned index_, unsigned var_index_), unsigned var_index_)
{
  // setup post-mutate function and expose the variable
  m_containing_object=&ve_;
  m_mutate_arr_func=(mutate_arr_func_ptr_t)mutate_func_;
  m_mutate_var_index=var_index_;
  avar(a_, size_, flags_, mvar_name_);
  m_mutate_arr_func=0;
  return true;
}
//----

bool prop_enum_exposure_base::data(const void *p_, usize_t num_bytes_)
{
  data_impl(const_cast<void*>(p_), num_bytes_);
  return true;
}
//----------------------------------------------------------------------------

void prop_enum_exposure_base::group_begin(const char *group_name_)
{
  begin_class(group_name_, 0);
}
//----

void prop_enum_exposure_base::group_end()
{
  end_class();
}
//----

template<typename T>
void prop_enum_exposure_base::slider(const T &min_, const T &max_, const T &step_)
{
  slider_impl(&min_, &max_, &step_);
}
//----------------------------------------------------------------------------

template<typename T>
void prop_enum_exposure_base::var_type(const char *mvar_name_, const T &v_, meta_case<0> is_type_fund_)
{
  var_impl(mvar_name_, type_id<T>::id, (void*)&v_);
}
//----

template<typename T>
void prop_enum_exposure_base::var_type(const char *mvar_name_, const T &v_, meta_case<1> is_type_class_)
{
  // expose composite class variable
  PFC_STATIC_ASSERT_MSG(is_type_introspec<T>::res, type_does_not_have_introspection_definition);
  const char *class_name=registered_object_typename(v_);
  if(!class_name)
    class_name=object_typename(v_);
  if(   !var_impl(mvar_name_, type_id<T>::id, (void*)&v_) && m_traverse_flags&traverse_composite_objs
     && begin_class(mvar_name_, class_name))
  {
    m_post_mutate_func=0;
    enum_props_most_derived(*this, const_cast<T&>(v_));
    end_class();
  }
}
//----

template<typename T>
void prop_enum_exposure_base::var_type(const char *mvar_name_, const T &v_, meta_case<2> is_type_enum_)
{
  // expose enumerated value variable
  PFC_STATIC_ASSERT(sizeof(T)==sizeof(int));
  enum_impl(mvar_name_, type_id<T>::id, (int*)&v_, enum_display_strings(v_), (const int*)enum_values(v_), enum_string_index(v_));
}
//----

template<typename T>
void prop_enum_exposure_base::var_type(const char *mvar_name_, T *&v_, meta_case<3> is_ptr_introspec_)
{
  // expose pointer to monomorphic class variable
  typedef pointer_mutator_mono<typename remove_cv<T>::res> mono_mutator_t;
  typedef pointer_mutator_poly<typename remove_cv<T>::res> poly_mutator_t;
  typedef typename meta_if<is_type_mono<T>::res, mono_mutator_t, poly_mutator_t>::res mutator_t;
  static const mutator_t s_ptr_mutator;
  const char *class_name=v_?registered_object_typename(*v_):0;
  if(!class_name)
    class_name=v_?object_typename(*v_):0;
  if(begin_class_ptr(mvar_name_, object_name(v_, meta_bool<is_type_orep<T>::res>()), class_name, (void*&)v_, s_ptr_mutator))
  {
    if(v_ && m_traverse_flags&(is_type_orep<T>::res?traverse_external_ptrs:traverse_internal_ptrs))
    {
      m_post_mutate_func=0;
      unsigned old_const_recursion=m_const_recursion;
      m_const_recursion=m_ptr_const_recursion;
      enum_props(*this, const_cast<typename remove_cv<T>::res&>(*v_));
      m_const_recursion=old_const_recursion;
    }
    end_class();
  }
}
//----

template<typename T>
void prop_enum_exposure_base::var_type(const char *mvar_name_, T *&v_, meta_case<4> is_ptr_fwd_introspec_)
{
  // setup forward pointer for introspection
  m_fwd_ptr=(void**)&v_;
  fwd_introspec(*this, v_);
}
//----

template<typename T>
void prop_enum_exposure_base::var_type(const char*, const T&, meta_case<-1> default_)
{
  PFC_STATIC_ERROR(T, unable_to_expose_the_type);
}
//----

template<typename T>
void prop_enum_exposure_base::var_type(const char*, const T&, meta_case<-2> default_)
{
}
//----

template<typename T>
const char *prop_enum_exposure_base::object_name(const T *p_, meta_bool<true> is_type_orep_)
{
  const str_id *sid=T::orep().find_object_name(p_);
  return sid?sid->c_str():0;
}
//----

template<typename T>
const char *prop_enum_exposure_base::object_name(const T*, meta_bool<false> is_type_orep_)
{
  return 0;
}
//----------------------------------------------------------------------------
