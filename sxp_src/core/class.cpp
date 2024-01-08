//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "class.h"
#include "sort.h"
#include "sxp_src/core/fsys/fsys.h"
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// globals
//============================================================================
namespace pfc
{
  hash_map<str_id, const class_factory_base*> g_mono_factories;
} // namespace pfc
//----------------------------------------------------------------------------


//============================================================================
// read_object_impl
//============================================================================
namespace pfc
{
  void *read_object_impl(bin_input_stream_base &s_, const char *file_ext_, const char *path_, unsigned type_id_)
  {
    // read archive signature and perform proper archive deserialization
    void *p=0;
    char sig[16];
    s_.read_bytes(sig, 16);
    if(mem_eq(sig, PFC_BIG_ENDIAN?"PFC_ARCH":"pfc_arch", 8))
    {
      // normal deserialization
      prop_enum_input_archive<bin_input_stream_base> pe(s_, file_ext_, path_);
      p=pe.root_object(type_id_);
    }
    else if(mem_eq(sig, PFC_BIG_ENDIAN?"pfc_arch":"PFC_ARCH", 8))
    {
#ifdef PFC_BUILDOP_ARCHIVE_ENDIAN_SUPPORT
      // endian swapped deserialization
      endian_input_stream es(s_);
      prop_enum_input_archive<endian_input_stream> pe(es, file_ext_, path_);
      p=pe.root_object(type_id_);
#else
      PFC_ERRORF("Executable doesn't support reading %s-endian archive files\r\n", PFC_BIG_ENDIAN?"little":"big");
#endif
    }
    else
      PFC_ERROR("Invalid archive signature\r\n");
    return p;
  }
} // namespace pfc
//----------------------------------------------------------------------------


//============================================================================
// class_repository_base
//============================================================================
hash_map<str_id, class_repository_base*> class_repository_base::s_repository_map;
//----------------------------------------------------------------------------

void class_repository_base::remove(const str_id &id_, const char *deprecated_name_)
{
  // remove class id & optional deprecated name
  hash_map<str_id, const class_factory_base*>::iterator it=m_factories.find(id_);
  m_factories.erase(it);
  if(deprecated_name_)
  {
    it=m_factories.find(deprecated_name_);
    m_factories.erase(it);
  }
}
//----

void class_repository_base::shutdown_repositories()
{
  // clean-up all class repositories
  bool is_first=true;
  hash_map<str_id, class_repository_base*>::iterator it_rep=s_repository_map.begin();
  while(is_valid(it_rep))
  {
    class_repository_base *rep=*it_rep;
    if(rep->m_factories.size())
    {
      // log header for first repository
      if(is_first)
      {
        PFC_LOG("\r\n");
        PFC_LOG("============================================================================\r\n");
        PFC_LOG("Unregistered classes in class repositories\r\n");
        PFC_LOG("----------------------------------------------------------------------------\r\n");
        is_first=false;
      }

      // log unregistered classes for the repository
      PFC_LOGF("Class repository \"%s\" contains registered classes:\r\n", it_rep.key().c_str());
      hash_map<str_id, const class_factory_base*>::iterator it_fact=rep->m_factories.begin();
      while(is_valid(it_fact))
      {
#ifdef PFC_BUILDOP_ASSERTS
        PFC_LOGF("  %s (%s)\r\n", it_fact.key().c_str(), (*it_fact)->assert_class_name());
#else
        PFC_LOGF("  %s\r\n", it_fact.key().c_str());
#endif
        ++it_fact;
      }
    }
    rep->m_factories.clear();
    ++it_rep;
  }

  if(g_mono_factories.size())
  {
    // log header for first repository
    if(is_first)
    {
      PFC_LOG("\r\n");
      PFC_LOG("============================================================================\r\n");
      PFC_LOG("Unregistered classes in class repositories\r\n");
      PFC_LOG("----------------------------------------------------------------------------\r\n");
      is_first=false;
    }

    // log registered monomorphic classes
    PFC_LOG("Monomorphic class repository contains registered classes:\r\n");
    hash_map<str_id, const class_factory_base*>::iterator it_fact=g_mono_factories.begin();
    while(is_valid(it_fact))
    {
#ifdef PFC_BUILDOP_ASSERTS
      PFC_LOGF("  %s (%s)\r\n", it_fact.key().c_str(), (*it_fact)->assert_class_name());
#else
      PFC_LOGF("  %s\r\n", it_fact.key().c_str());
#endif
      ++it_fact;
    }
  }
  g_mono_factories.clear();

  if(!is_first)
    PFC_LOG("----------------------------------------------------------------------------\r\n\r\n");
  s_repository_map.clear();
}
//----------------------------------------------------------------------------

void class_repository_base::add_factory(const str_id &id_, const class_factory_base &f_)
{
  hash_map<str_id, const class_factory_base*>::inserter ins=m_factories.insert(id_, &f_, false);
  PFC_ASSERT_MSG(ins.is_new || *ins.it==&f_, ("Class \"%s\" has already been registered with name \"%s\"\r\n", (*ins.it)->assert_class_name(), id_.c_str()));
}
//----------------------------------------------------------------------------


//============================================================================
// object_repository_base
//============================================================================
hash_map<str_id, object_repository_base*> object_repository_base::s_repository_map;
deque<object_repository_base*> object_repository_base::s_repositories;
list<object_repository_pool> object_repository_base::s_pools;
object_repository_pool *object_repository_base::s_active_pool=0;
//----------------------------------------------------------------------------

void object_repository_base::shutdown_repositories()
{
  remove_all_pools();
  s_repository_map.clear();
  s_repositories.clear();
}
//----------------------------------------------------------------------------

object_repository_pool &object_repository_base::add_pool(const char *name_, object_repository_pool *parent_)
{
  // add repository pool
  PFC_ASSERT_MSG(!find_pool(name_), ("Object pool \"%s\" already exists\r\n", name_));
  object_repository_pool &pool=s_pools.push_back();
  pool.m_name=name_;
  pool.m_containers.resize(s_repository_map.size());
  pool.m_parent=parent_;
  return pool;
}
//----

void object_repository_base::remove_pool(object_repository_pool &pool_)
{
  // remove pool and all child pools
  list<object_repository_pool>::iterator it=s_pools.begin();
  while(is_valid(it))
  {
    if(ptr(it)==&pool_)
    {
      // clear containers and remove the pool
      if(s_active_pool==&pool_)
        s_active_pool=0;
      unsigned num_reps=(unsigned)s_repositories.size();
      for(unsigned i=0; i<num_reps; ++i)
        s_repositories[i]->clear_container(it->m_containers[i]);
      s_pools.erase(it);
    }
    else if(it->m_parent==&pool_)
    {
      // remove child pool and restart from beginning (iterator is invalidated)
      remove_pool(*it);
      it=s_pools.begin();
    }
    else
      ++it;
  }
}
//----

void object_repository_base::remove_all_pools()
{
  // iterate through all pools
  unsigned num_reps=(unsigned)s_repositories.size();
  list<object_repository_pool>::iterator it=s_pools.begin();
  while(is_valid(it))
  {
    // clear all repository containers in the pool
    for(unsigned i=0; i<num_reps; ++i)
      s_repositories[i]->clear_container(it->m_containers[i]);
    ++it;
  }
  s_pools.clear();
  s_active_pool=0;
}
//----

object_repository_pool *object_repository_base::active_pool()
{
  return s_active_pool;
}
//----

object_repository_pool *object_repository_base::activate_pool(object_repository_pool *pool_)
{
  object_repository_pool *old_pool=s_active_pool;
  s_active_pool=pool_;
  return old_pool;
}
//----

object_repository_pool *object_repository_base::find_pool(const char *name_)
{
  // find object pool with given name
  list<object_repository_pool>::iterator it=s_pools.begin();
  while(is_valid(it))
  {
    if(it->m_name==name_)
      return ptr(it);
    ++it;
  }
  return 0;
}
//----------------------------------------------------------------------------

object_repository_base *object_repository_base::find_repository(const str_id &id_)
{
  PFC_ASSERT(id_.c_str());
  hash_map<str_id, object_repository_base*>::const_iterator it=s_repository_map.find(id_);
  return is_valid(it)?*it:0;
}
//----

void *object_repository_base::find_object(const str_id &id_) const
{
  // find object with given id from the repository
  PFC_ASSERT_MSG(s_active_pool, ("No object repository pool has been activated\r\n"));
  PFC_ASSERT(id_.c_str());
  object_repository_pool *pool=s_active_pool;
  do
  {
    repository_container::const_iterator it=pool->m_containers[m_index].find(id_);
    if(is_valid(it))
      return *it;
    pool=pool->m_parent;
  } while(pool);
  return 0;
}
//----

const str_id *object_repository_base::find_object_name(const void *p_) const
{
  // find name associated with the pointer
  if(!p_)
    return 0;
  PFC_ASSERT_MSG(s_active_pool, ("No object repository pool has been activated\r\n"));
  object_repository_pool *pool=s_active_pool;
  do
  {
    repository_container::const_iterator it=pool->m_containers[m_index].find_val(const_cast<void*>(p_));
    if(is_valid(it))
      return &it.key();
    pool=pool->m_parent;
  } while(pool);
  return 0;
}
//----

void *object_repository_base::load_object(const str_id &id_, const char *file_ext_, const char *path_, unsigned type_id_)
{
  // search for object from the repository
  void *p=find_object(id_);
  if(!p)
  {
    // load object from archive file
    filepath_str asset_file=id_.c_str();
    if(file_ext_)
      asset_file+=file_ext_;
    owner_ptr<bin_input_stream_base> s=file_system_base::active().open_read(asset_file.c_str(), path_, fopencheck_none);
    if(s.data)
    {
      // read object and add to repository
      p=read_object_impl(*s.data, file_ext_, path_, type_id_);
      if(p)
        add_object(id_, p);
    }
    else
      PFC_WARNF("Unable to load file \"%s\" for \"%s\" repository object \"%s\"\r\n", afs_complete_path(asset_file.c_str(), path_).c_str(), m_name.c_str(), id_.c_str());
  }
  return p;
}
//----

void *object_repository_base::load_object(const str_id &id_, bin_input_stream_base &s_, const char *file_ext_, const char *path_, unsigned type_id_)
{
  // search for object from the repository
  void *p=find_object(id_);
  if(!p)
  {
    // read object and add to repository
    p=read_object_impl(s_, file_ext_, path_, type_id_);
    if(p)
      add_object(id_, p);
  }
  return p;
}
//----------------------------------------------------------------------------

object_repository_base::object_repository_base(const str_id &id_)
  :m_name(id_)
  ,m_index((unsigned)s_repositories.size())
{
  // add repository and add repository container to all object pools
  PFC_ASSERT(id_.c_str());
  s_repository_map.insert(id_, this);
  s_repositories.push_back(this);
  list<object_repository_pool>::iterator it=s_pools.begin();
  while(is_valid(it))
  {
    it->m_containers.push_back();
    ++it;
  }
}
//----

object_repository_base::~object_repository_base()
{
}
//----

const char *object_repository_base::add_object(const str_id &id_, void *p_)
{
  // add new object to the repository
  PFC_ASSERT_MSG(s_active_pool, ("No object repository pool has been activated while adding resource \"%s\" to \"%s\" repository\r\n", id_.c_str(), m_name.c_str()));
  PFC_ASSERT(p_!=0);
  repository_container &container=s_active_pool->m_containers[m_index];
  PFC_ASSERT_MSG(!is_valid(container.find(id_)), ("Object \"%s\" already exists in \"%s\" repository\r\n", id_.c_str(), m_name.c_str()));
  const char *name=s_active_pool->m_strings.add_string(id_.c_str());
  container.insert(str_id(name, id_.crc32()), p_);
  return name;
}
//----

void object_repository_base::remove_object(void *p_)
{
  // remove object from the repository
  PFC_ASSERT_MSG(s_active_pool, ("No object repository pool has been activated\r\n"));
  PFC_ASSERT(p_!=0);
  repository_container::iterator it=s_active_pool->m_containers[m_index].find_val(p_);
  if(is_valid(it))
  {
    const char *name=it.key().c_str();
    it.remove_val();
    s_active_pool->m_strings.remove_string(name);
  }
}
//----------------------------------------------------------------------------
