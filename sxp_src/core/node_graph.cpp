//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "node_graph.h"
#include "sort.h"
#include "sxp_src/core/math/bit_math.h"
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// graph_node_base
//============================================================================
owner_data graph_node_base::create_impure_node_data() const
{
  return 0;
}
//----------------------------------------------------------------------------

bool graph_node_base::has_impure_node_changed(void*) const
{
  return true;
}
//----------------------------------------------------------------------------


//============================================================================
// node_graph
//============================================================================
node_graph::node_graph()
  :m_num_impure_nodes(0)
  ,m_num_node_exec_mask_words(0)
  ,m_instance_cache_data_size(0)
  ,m_exec_context_local_data_size(0)
  ,m_is_executed(false)
{
}
//----

node_graph::~node_graph()
{
}
//----------------------------------------------------------------------------

void node_graph::add_node(owner_ptr<graph_node_base> n_)
{
  // add node to the graph
  PFC_ASSERT(n_.data);
  m_nodes.push_back(n_.data);
  n_.data=0;
}
//----------------------------------------------------------------------------

void node_graph::exec(node_graph_instance &inst_)
{
  // build node execution mask by merging masks of changed impure nodes
  graph_node_base **nodes=m_nodes.data();
  uint32_t *node_exec_mask=(uint32_t*)PFC_STACK_MALLOC(m_num_node_exec_mask_words*4);
  mem_zero(node_exec_mask, m_num_node_exec_mask_words*4);
  const uint32_t *impure_node_indices=m_impure_node_data.data();
  const uint32_t *node_exec_masks=impure_node_indices+m_num_impure_nodes;
  bool exec_nodes=false;
  for(unsigned ii=0; ii<m_num_impure_nodes; ++ii)
  {
    // check for changed impure node and merge mask if node has changed
    unsigned impure_node_idx=impure_node_indices[ii];
    if(nodes[impure_node_idx]->has_impure_node_changed(inst_.m_impure_node_datas[ii].data))
    {
      for(unsigned i=0; i<m_num_node_exec_mask_words; ++i)
        node_exec_mask[i]|=node_exec_masks[i];
      exec_nodes=true;
    }
    node_exec_masks+=m_num_node_exec_mask_words;
  }

  if(exec_nodes)
  {
    // setup graph execution context
    node_graph_exec_context exec_context;
    exec_context.graph=this;
    exec_context.instance=&inst_;
    exec_context.local_data=PFC_STACK_MALLOC(m_exec_context_local_data_size);
    unsigned num_output_pin_mask_words=((unsigned)m_output_pin_infos.size()+31)/32;
    exec_context.constructed_output_pins_mask=(uint32_t*)PFC_STACK_MALLOC(num_output_pin_mask_words*4);
    mem_zero(exec_context.constructed_output_pins_mask, num_output_pin_mask_words*4);

    // execute nodes
    unsigned node_base_idx=0;
    for(unsigned i=0; i<m_num_node_exec_mask_words; ++i)
    {
      uint32_t exec_mask_word=node_exec_mask[i];
      while(exec_mask_word)
      {
        uint32_t mask_lsb=lsb(exec_mask_word);
        nodes[node_base_idx+bitpos(mask_lsb)]->exec(exec_context);
        exec_mask_word^=mask_lsb;
      }
      node_base_idx+=32;
    }

    // destruct the written non-POD context data
    unsigned pin_base_idx=0;
    for(unsigned i=0; i<num_output_pin_mask_words; ++i)
    {
      uint32_t destruct_mask_word=exec_context.constructed_output_pins_mask[i];
      while(destruct_mask_word)
      {
        // destruct the pin context data for given output pin bit
        uint32_t destruct_mask_lsb=lsb(destruct_mask_word);
        output_pin_info &info=m_output_pin_infos[pin_base_idx+bitpos(destruct_mask_lsb)];
        PFC_ASSERT(info.destructor);
        (*info.destructor)((char*)exec_context.local_data+(info.pin_data_offset&0x3fffffff));
        destruct_mask_word^=destruct_mask_lsb;
      }
      pin_base_idx+=32;
    }
    m_is_executed=true;
    inst_.m_is_executed=true;
  }
}
//----------------------------------------------------------------------------


//============================================================================
// node_graph_instance
//============================================================================
node_graph_instance::node_graph_instance(const node_graph &graph_)
  :m_is_executed(false)
{
  // create instance data for impure nodes
  const graph_node_base *const*nodes=graph_.m_nodes.data();
  unsigned num_impure_nodes=graph_.m_num_impure_nodes;
  const uint32_t *impure_node_indices=graph_.m_impure_node_data.data();
  m_impure_node_datas.resize(num_impure_nodes);
  for(unsigned i=0; i<num_impure_nodes; ++i)
    m_impure_node_datas[i]=nodes[impure_node_indices[i]]->create_impure_node_data();
}
//----

node_graph_instance::~node_graph_instance()
{
}
//----------------------------------------------------------------------------

//============================================================================
// test_node
//============================================================================
static const graph_node_pin_info s_input_pins[]=
{
  {"hello-input", meta_type_array<array<int>, int>::s_ids},
};

static const graph_node_pin_info s_output_pins[]=
{
  {"hello-output", meta_type_array<int, float>::s_ids},
};

class test_node: public graph_node_base
{ PFC_CLASS(test_node, graph_node_base) {}
public:
  virtual e_graph_node_type type() const {return graphnodetype_global_pure;}
  virtual unsigned num_pins(bool is_input_) const {return is_input_?PFC_CARRAY_SIZE(s_input_pins):PFC_CARRAY_SIZE(s_output_pins);}
  virtual const graph_node_pin_info &pin_info(unsigned pin_idx_, bool is_input_) const {return is_input_?s_input_pins[pin_idx_]:s_output_pins[pin_idx_];}
  virtual void exec(node_graph_exec_context &ctx_)
  {
/*    float *out=write_pin_data<float>(0, ctx_);
    const float *in=read_pin_data<float>(0, ctx_);*/
  }

private:
};
//----------------------------------------------------------------------------
