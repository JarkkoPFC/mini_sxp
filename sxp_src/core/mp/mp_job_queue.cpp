//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "mp_job_queue.h"
#include "sxp_src/core/math/bit_math.h"
#include "sxp_src/core/sort.h"
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// mp_job_queue
//============================================================================
static unsigned s_num_job_queue_worker_threads=0;
mp_job_queue *mp_job_queue::s_active=0;
//----------------------------------------------------------------------------

mp_job_queue::mp_job_queue(int max_num_worker_threads_)
  :m_job_pool(sizeof(job), meta_alignof<job>::res)
{
  // setup active job queue
  PFC_CHECK_MSG(!s_active, ("mp_job_queue has already been created\r\n"));
  s_active=this;
  s_num_job_queue_worker_threads=0;

  // init the queue
  m_process_jobs=true;
  m_num_pending_job_types=0;
  m_num_pending_jobs=0;
  m_num_job_types=0;
  for(unsigned i=0; i<max_job_types; ++i)
  {
    job_type &jt=m_job_types[i];
    jt.name=0;
    jt.job_func=0;
    jt.type_data=0;
    jt.type_data_id=0;
    jt.job_data_id=0;
    jt.scheduling_type=jobscheduling_normal;
    jt.priority=1;
    jt.num_pending_jobs=0;
    jt.max_kcycles=0;
    jt.next_pq=0;
  }

  // limit the number of threads to the number of available hardware threads
  unsigned avail_threads=num_hardware_threads();
  PFC_CHECK_MSG(avail_threads, ("No hardware threads available\r\n"));
  unsigned num_worker_threads=max_num_worker_threads_>=0?min(unsigned(max_num_worker_threads_), avail_threads-1):avail_threads-1;
  array<worker> workers(num_worker_threads);
  m_workers.swap(workers);

  // setup hardware thread for the main thread and create workers
  unsigned hw_thread_idx=0;
  set_hardware_thread(hw_thread_idx++);
  for(unsigned i=0; i<num_worker_threads; ++i)
  {
    worker &w=m_workers[i];
    w.job_queue=this;
    w.thread.init(PFC_MAKE_MEM_FUNCTOR(functor<int()>, w, worker, func), false, hw_thread_idx++);
  }
  logf("Created job queue (%i worker %s)\r\n", num_worker_threads, num_worker_threads==1?"thread":"threads");
}
//----

mp_job_queue::~mp_job_queue()
{
  // quit worker threads
  PFC_ASSERT_MSG(m_num_pending_jobs==0, ("All pending jobs (%i) are not completed\r\n", m_num_pending_jobs));
  m_process_jobs=false;
  atom_inc(m_num_pending_job_types);
  m_run_workers_state.open();
  unsigned num_workers=(unsigned)m_workers.size();
  for(unsigned i=0; i<num_workers; ++i)
    wait_thread(m_workers[i].thread);

  // ensure that priority queues are empty
  for(unsigned i=0; i<num_priorities; ++i)
    while(job_type *jt=m_priority_queues[i].pop())
    {
      PFC_ASSERT(!jt->jobs.head());
    }

  // reset active job queue
  s_active=0;
}
//----------------------------------------------------------------------------

void mp_job_queue::set_worker_priority(e_thread_priority p_)
{
  for(unsigned i=0; i<m_workers.size(); ++i)
    m_workers[i].thread.set_priority(p_);
}
//----------------------------------------------------------------------------

e_jobtype_id mp_job_queue::create_job_type(const char *type_name_, void(*func_)(void*, void*), e_job_scheduling scheduling_)
{
  // asserts/checks
  PFC_ASSERT_MSG(type_name_, ("Job type name not defined\r\n"));
  PFC_ASSERT_MSG(func_, ("Job type function not defined\r\n"));
  e_jobtype_id type_id=e_jobtype_id(atom_inc(m_num_job_types));
  PFC_ASSERT_MSG(type_id<int(max_job_types), ("Creating too many job types (max=%i)\r\n", max_job_types));

  // setup new job type
  job_type &jt=m_job_types[type_id];
  jt.name=type_name_;
  jt.job_func=func_;
  jt.type_data_id=pfc::type_id<void>::id;
  jt.job_data_id=pfc::type_id<void>::id;
  jt.priority=scheduling_==jobscheduling_realtime?0:1;
  jt.scheduling_type=uint8_t(scheduling_);
  return type_id;
}
//----

e_jobtype_id mp_job_queue::find_job_type(void(*func_)(void*, void*))
{
  for(unsigned i=1; i<m_num_job_types; ++i)
    if(m_job_types[i].job_func==func_)
      return e_jobtype_id(i);
  return e_jobtype_id(0);
}
//----------------------------------------------------------------------------

void mp_job_queue::add_job(e_jobtype_id type_, void *data_)
{
  // setup new job and add it to the job type
  PFC_ASSERT_PEDANTIC_MSG(type_, ("Job type ID not defined\r\n"));
  PFC_ASSERT_PEDANTIC_MSG(unsigned(type_)<=m_num_job_types, ("Job type ID (%i) not created\r\n", type_));
  atom_inc(m_num_pending_jobs);
  job_type &jt=m_job_types[type_];
  atom_inc(jt.num_pending_jobs);
  job *j=(job*)m_job_pool.alloc_block();
  j->data=data_;
  jt.jobs.push(*j);

  // ensure that job type is in a priority queue
  if(   m_priority_queues[jt.priority].secure_push(jt)
     && atom_inc(m_num_pending_job_types)==1)
    m_run_workers_state.open();
}
//----

void mp_job_queue::wait_job_type(e_jobtype_id type_)
{
  // execute top-priority jobs until given job is executed
  job_type &type=m_job_types[type_];
  while(type.num_pending_jobs)
    exec_top_priority_job_type(false, false);
}
//----

void mp_job_queue::wait_job_types(const e_jobtype_id *types_, unsigned num_job_types_)
{
  while(num_job_types_--)
    wait_job_type(*types_++);
}
//----

void mp_job_queue::wait_all_jobs()
{
  // run jobs until all jobs have been completed
  while(m_num_pending_jobs)
    exec_top_priority_job_type(false, false);
}
//----

void mp_job_queue::exec_job(e_jobtype_id jtid_)
{
  job_type &type=m_job_types[jtid_];
  if(type.num_pending_jobs)
    exec_top_priority_job_type(false, true);
}
//----

bool mp_job_queue::has_jobs(e_jobtype_id jtid_, bool exec_jobs_)
{
  job_type &type=m_job_types[jtid_];
  if(exec_jobs_ && type.num_pending_jobs)
    exec_top_priority_job_type(false, true);
  return type.num_pending_jobs!=0;
}
//----

bool mp_job_queue::has_jobs(const e_jobtype_id *jtids_, unsigned num_job_types_, bool exec_jobs_)
{
  while(num_job_types_--)
    if(has_jobs(*jtids_++, exec_jobs_))
      return true;
  return false;
}
//----

void mp_job_queue::reprioritize()
{
  PFC_ASSERT_MSG(m_num_pending_jobs==0, ("All pending jobs (%i) are not completed\r\n", m_num_pending_jobs));
  if(!m_num_job_types)
    return;

  // calculate cumulative priority weights for job types
/*  pair<uint32_t, unsigned> pweights[max_job_types], tmp[max_job_types];
  mem_zero(pweights, (m_num_job_types+1)*sizeof(*pweights));
  unsigned num_normal_scheduled_types=0;
  for(unsigned i=m_num_job_types; i>0; --i)
  {
    job_type &jt=m_job_types[i];
    pweights[i].first+=jt.pweight;
    pweights[jt.depends_on].first+=pweights[i].first;
    pweights[i].second=i;
    jt.pweight=0;
    jt.state_dep=uint8_t(jt.depends_on?0:statedep_can_exec);
    if(jt.scheduling_type==jobscheduling_normal)
      ++num_normal_scheduled_types;
  }

  // sort job types by priority weights and setup job type priorities
  radix_sort(pweights+1, tmp, m_num_job_types, radix_sort_predicate<pair<uint32_t, unsigned>, false>());
  float delta=float(num_priorities-1)/float(num_normal_scheduled_types);
  float priority=0.0f;
  for(unsigned i=1; i<m_num_job_types+1; ++i)
  {
    job_type &jt=m_job_types[pweights[i].second];
    if(jt.scheduling_type==jobscheduling_normal)
    {
      jt.priority=uint8_t(priority)+1;
      priority+=delta;
    }
  }*/
}
//----------------------------------------------------------------------------

void mp_job_queue::exec_top_priority_job_type(bool wait_jobs_, bool exec_single_job_)
{
  // process jobs for a job type with top priority
  for(unsigned i=0; i<num_priorities; ++i)
  {
    mp_fifo_queue<job_type, &job_type::next_pq> &pq=m_priority_queues[i];
    if(job_type *jt=pq.head())
    {
      // execute all jobs for the job type
      while(job *j=jt->jobs.pop())
      {
        // execute and profile the job
        uint64_t job_cycles=get_thread_cycles();
        (*jt->job_func)(j->data, jt->type_data);
        job_cycles=get_thread_cycles()-job_cycles;
        m_job_pool.free(j);
        atom_cmov_max(jt->max_kcycles, uint32_t(job_cycles>>10));
        atom_dec(jt->num_pending_jobs);
        atom_dec(m_num_pending_jobs);
        if(exec_single_job_)
        {
          if(jt->jobs.head())
            return;
          break;
        }
      }

      // remove the type from the priority queue
      if(pq.pop_if(jt))
      {
        // inactivate workers if number of pending job types drops to zero
        while(   atom_dec(m_num_pending_job_types)==0
              && atom_cmov_eq(m_num_pending_job_types, 1u, 0u)==0)
        {
          m_run_workers_state.close();
          if(atom_cmov_eq(m_num_pending_job_types, 0u, 1u)==1)
            break;
          m_run_workers_state.open();
        }

        // add job type back to queue if new jobs were added while removing
        jt->next_pq=0;
        if(   jt->jobs.head()
           && pq.secure_push(*jt)
           && atom_inc(m_num_pending_job_types)==1)
          m_run_workers_state.open();
      }
      return;
    }
  }

  // wait for jobs to execute
  if(wait_jobs_)
    wait_gate(m_run_workers_state);
}
//----------------------------------------------------------------------------


//============================================================================
// mp_job_queue::worker
//============================================================================
PFC_THREAD_VAR unsigned pfc::g_job_queue_thread_id=0;
//----------------------------------------------------------------------------

int mp_job_queue::worker::func()
{
  // run jobs until job queue exits
  g_job_queue_thread_id=atom_inc(s_num_job_queue_worker_threads);
  do
  {
    job_queue->exec_top_priority_job_type(true, false);
  } while(job_queue->m_process_jobs);
  return 0;
}
//----------------------------------------------------------------------------
