//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_NODE_GRAPH_H
#define PFC_CORE_NODE_GRAPH_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "containers.h"
#include "class.h"
namespace pfc
{

// new
struct graph_node_pin_info;
struct node_graph_exec_context;
class graph_node_base;
class node_graph;
class node_graph_instance;
//----------------------------------------------------------------------------


//============================================================================
// graph_node_pin_info
//============================================================================
struct graph_node_pin_info
{
  const char *name;
  const uint32_t *supported_type_ids; // 0-terminated
};
//----------------------------------------------------------------------------


//============================================================================
// node_graph_exec_context
//============================================================================
struct node_graph_exec_context
{
  node_graph *graph;
  const node_graph_instance *instance;
  void *local_data;
  uint32_t *constructed_output_pins_mask;
};
//----------------------------------------------------------------------------


//============================================================================
// e_graph_node_type
//============================================================================
enum e_graph_node_type
{
  graphnodetype_global_pure   =0x00,
  graphnodetype_local_pure    =0x01,
  graphnodetype_global_impure =0x02,
  graphnodetype_local_impure  =0x03,
};
//----------------------------------------------------------------------------


//============================================================================
// graph_node_base
//============================================================================
class graph_node_base
{ PFC_BASE_CLASS(graph_node_base) {}
public:
  // construction
  virtual ~graph_node_base()=0;
  virtual owner_data create_impure_node_data() const;
  //--------------------------------------------------------------------------

  // accessors
  virtual e_graph_node_type type() const=0;
  virtual bool has_impure_node_changed(void*) const;
  virtual unsigned num_pins(bool is_input_) const=0;
  virtual const graph_node_pin_info &pin_info(unsigned pin_idx_, bool is_input_) const=0;
  //--------------------------------------------------------------------------

  // execution
  virtual void exec(node_graph_exec_context&)=0;
  //--------------------------------------------------------------------------

protected:
  PFC_INLINE graph_node_base();
  template<typename T> const T *read_pin_data(unsigned input_pin_idx_, node_graph_exec_context&);
  template<typename T> T *write_pin_data(unsigned output_pin_idx_, node_graph_exec_context&);
  //--------------------------------------------------------------------------

private:
  friend class node_graph;
  graph_node_base(const graph_node_base&); // not implemented
  void operator=(const graph_node_base&); // not implemented
  template<typename T> static void destruct(void*);
  //--------------------------------------------------------------------------

  unsigned m_input_pin_info_start_idx;
  unsigned m_output_pin_info_start_idx;
};
//----------------------------------------------------------------------------


//============================================================================
// graph_node_instance_base
//============================================================================
class graph_node_instance_base
{ PFC_BASE_CLASS(graph_node_instance_base) {}
public:
  // construction
  virtual ~graph_node_instance_base()=0;
  //--------------------------------------------------------------------------

private:
  graph_node_instance_base(const graph_node_instance_base&); // not implemented
  void operator=(const graph_node_instance_base&); // not implemented
};
//----------------------------------------------------------------------------


//============================================================================
// node_graph
//============================================================================
class node_graph
{ PFC_MONO(node_graph) {}
public:
  // construction
  node_graph();
  ~node_graph();
  //--------------------------------------------------------------------------

  // graph construction
  void add_node(owner_ptr<graph_node_base>);
  //--------------------------------------------------------------------------

  // execution
  void exec(node_graph_instance&);
  //--------------------------------------------------------------------------

private:
  node_graph(const node_graph&); // not implemented
  void operator=(const node_graph&); // not implemented
  friend class graph_node_base;
  friend class node_graph_instance;
  void setup_pin_data_offsets();
  //--------------------------------------------------------------------------

  //==========================================================================
  // input_pin_info
  //==========================================================================
  struct input_pin_info
  {
    uint32_t connected_pin_type;
    uint32_t pin_data_offset;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // output_pin_info
  //==========================================================================
  struct output_pin_info
  {
    uint32_t connected_pin_type;
    uint16_t connected_node_idx;
    uint16_t connected_node_pin_idx;
    uint32_t pin_data_offset;
    void(*destructor)(void*);
  };
  //--------------------------------------------------------------------------

  array<graph_node_base*> m_nodes;
  array<input_pin_info> m_input_pin_infos;
  array<output_pin_info> m_output_pin_infos;
  array<uint32_t> m_impure_node_data;
  owner_array<void> m_uniform_cache_data;
  unsigned m_num_impure_nodes;
  unsigned m_num_node_exec_mask_words;
  unsigned m_instance_cache_data_size;
  unsigned m_exec_context_local_data_size;
  bool m_is_executed;
};
//----------------------------------------------------------------------------


//============================================================================
// node_graph_instance
//============================================================================
class node_graph_instance
{ PFC_MONO(node_graph_instance) {}
public:
  // construction
  node_graph_instance(const node_graph&);
  ~node_graph_instance();
  //--------------------------------------------------------------------------

private:
  node_graph_instance(const node_graph_instance&); // not implemented
  void operator=(const node_graph_instance&); // not implemented
  friend class graph_node_base;
  friend class node_graph;
  //--------------------------------------------------------------------------

  owner_data m_instance_cache_data;
  array<owner_data> m_impure_node_datas;
  bool m_is_executed;
};
//----------------------------------------------------------------------------

//============================================================================
#include "node_graph.inl"
} // namespace pfc
#endif
