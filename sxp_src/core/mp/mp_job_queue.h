//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_MP_JOB_QUEUE_H
#define PFC_CORE_MP_JOB_QUEUE_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "mp_memory.h"
namespace pfc
{

// new
enum e_job_scheduling {jobscheduling_normal, jobscheduling_realtime};
class mp_job_queue;
template<typename T, typename U> PFC_INLINE e_jobtype_id create_job_type(const char *type_name_, void(*)(T*, U*), e_job_scheduling=jobscheduling_normal);
PFC_INLINE e_jobtype_id create_job_type(const char *type_name_, void(*)(void*, void*), e_job_scheduling=jobscheduling_normal);
template<typename T> PFC_INLINE void set_job_type_data(e_jobtype_id, T*);
template<typename T> PFC_INLINE void add_job(e_jobtype_id, T*);
PFC_INLINE void wait_job_type(e_jobtype_id);
PFC_INLINE void wait_job_types(const e_jobtype_id*, unsigned num_jobs_types_);
PFC_INLINE void wait_all_jobs();
PFC_INLINE void exec_job(e_jobtype_id);
PFC_INLINE bool has_jobs(e_jobtype_id, bool exec_jobs_=false);
PFC_INLINE bool has_jobs(const e_jobtype_id*, unsigned num_job_types_, bool exec_jobs_=false);
extern PFC_THREAD_VAR unsigned g_job_queue_thread_id;
//----------------------------------------------------------------------------


//============================================================================
// mp_job_queue
//============================================================================
class mp_job_queue
{
public:
  // construction
  mp_job_queue(int max_num_worker_threads_=-1);
  ~mp_job_queue();
  static PFC_INLINE bool has_active();
  static PFC_INLINE mp_job_queue &active();
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE unsigned num_worker_threads() const;
  void set_worker_priority(e_thread_priority);
  //--------------------------------------------------------------------------

  // job type management
  template<typename T, typename U> PFC_INLINE e_jobtype_id create_job_type(const char *type_name_, void(*)(T*, U*), e_job_scheduling=jobscheduling_normal);
  e_jobtype_id create_job_type(const char *type_name_, void(*)(void*, void*), e_job_scheduling=jobscheduling_normal);
  template<typename T, typename U> PFC_INLINE e_jobtype_id find_job_type(void(*)(T*, U*));
  e_jobtype_id find_job_type(void(*)(void*, void*));
  template<typename T> PFC_INLINE void set_job_type_data(e_jobtype_id, T*);
  //--------------------------------------------------------------------------

  // job management
  template<typename T> PFC_INLINE void add_job(e_jobtype_id, T*);
  void add_job(e_jobtype_id, void*);
  void wait_job_type(e_jobtype_id);
  void wait_job_types(const e_jobtype_id*, unsigned num_job_types_);
  void wait_all_jobs();
  void exec_job(e_jobtype_id);
  bool has_jobs(e_jobtype_id, bool exec_jobs_=false);
  bool has_jobs(const e_jobtype_id*, unsigned num_job_types_, bool exec_jobs_=false);
  void reprioritize();
  //--------------------------------------------------------------------------

private:
  struct job_type;
  mp_job_queue(const mp_job_queue&); // not implemented
  void operator=(const mp_job_queue&); // not implemented
  void exec_top_priority_job_type(bool wait_jobs_, bool exec_single_job_);
  //--------------------------------------------------------------------------

  //==========================================================================
  // mp_job_queue::job
  //==========================================================================
  struct job
  {
    void *data;
    job *next;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // mp_job_queue::job_type
  //==========================================================================
  struct job_type
  {
    const char *name;               // job type name
    void(*job_func)(void*, void*);  // job function for the type
    void *type_data;                // job type data
    uint32_t type_data_id;          // type ID of per-type data
    uint32_t job_data_id;           // type ID of per-job data
    uint8_t scheduling_type;        // scheduling type of the job
    uint8_t priority;               // priority of the job type (updated at reprioritize())
    uint32_t num_pending_jobs;      // number of jobs pending for execution
    uint32_t max_kcycles;           // maximum k-cycles of running a job
    mp_fifo_queue<job> jobs;        // list of jobs for the job type
    job_type *next_pq;              // next job type in a priority queue
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // mp_job_queue::worker
  //==========================================================================
  struct worker
  {
    mp_thread thread;
    mp_job_queue *job_queue;
    //------------------------------------------------------------------------

    int func();
  };
  //--------------------------------------------------------------------------

  static mp_job_queue *s_active;
  enum {max_job_types=1024};
  enum {max_wait_jobs=64};
  enum {num_priorities=32};
  volatile bool m_process_jobs;
  volatile unsigned m_num_pending_job_types;
  volatile unsigned m_num_pending_jobs;
  unsigned m_num_job_types;
  job_type m_job_types[max_job_types];
  mp_fifo_queue<job_type, &job_type::next_pq> m_priority_queues[num_priorities];
  mp_free_list m_job_pool;
  mp_gate m_run_workers_state;
  array<worker> m_workers;
};
//----------------------------------------------------------------------------

//============================================================================
#include "mp_job_queue.inl"
} // namespace pfc
#endif
