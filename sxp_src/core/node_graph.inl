//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// graph_node_base
//============================================================================
graph_node_base::graph_node_base()
  :m_input_pin_info_start_idx(0)
  ,m_output_pin_info_start_idx(0)
{
}
//----

template<typename T>
const T *graph_node_base::read_pin_data(unsigned input_pin_idx_, node_graph_exec_context &ctx_)
{
  // validate pin input request (pin index & type)
  PFC_ASSERT_MSG(input_pin_idx_<num_pins(true), ("Trying to read from input pin %i of \"%s\" node class with only %i input pins\r\n", input_pin_idx_, object_typename(), num_pins(true)));
  const node_graph::input_pin_info &info=ctx_.graph->m_input_pin_infos[m_input_pin_info_start_idx+input_pin_idx_];
  PFC_ASSERT_MSG(!info.connected_pin_type || info.connected_pin_type==type_id<T>::id,
                 ("Trying to fetch incorrect type \"%s\" from \"%s\" input pin of \"%s\" node class\r\n", typeid(T).name(), pin_info(input_pin_idx_, true).name, object_typename()));

  // return data address for the pin
  uint32_t data_offset=info.pin_data_offset;
  const char *src_datas[]={0, (const char*)ctx_.local_data, (const char*)ctx_.instance->m_instance_cache_data.data, (const char*)ctx_.graph->m_uniform_cache_data.data};
  return (const T*)(src_datas[data_offset>>30]+(data_offset&0x3fffffff));
}
//----

template<typename T>
T *graph_node_base::write_pin_data(unsigned output_pin_idx_, node_graph_exec_context &ctx_)
{
  // validate pin output request (pin index, type & connected pin)
  PFC_ASSERT_MSG(output_pin_idx_<num_pins(false), ("Trying to write to output pin %i of \"%s\" node class with only %i output pins\r\n", output_pin_idx_, object_typename(), num_pins(false)));
  unsigned output_pin_info_idx=m_output_pin_info_start_idx+output_pin_idx_;
  node_graph::output_pin_info &info=ctx_.graph->m_output_pin_infos[output_pin_info_idx];
  uint32_t data_offset=info.pin_data_offset;
  if(!data_offset)
    return 0;
  PFC_ASSERT_MSG(info.connected_pin_type==type_id<T>::id, ("Trying to output incorrect type \"%s\" to \"%s\" output pin of \"%s\" node class\r\n", typeid(T).name(), pin_info(output_pin_idx_, false).name, object_typename()));

  // get data address for the pin
  unsigned data_type=data_offset>>30;
  char *dst_datas[]={0, (char*)ctx_.local_data, (char*)ctx_.instance->m_instance_cache_data.data, (char*)ctx_.graph->m_uniform_cache_data.data};
  T *p=(T*)(dst_datas[data_type]+(data_offset&0x3fffffff));
  if(!is_type_pod<T>::res)
  {
    // handle destruction & construction for non-POD pin data type
    info.destructor=&destruct<T>;
    switch(data_type)
    {
      case 1: ctx_.constructed_output_pins_mask[output_pin_info_idx/32]|=1<<(output_pin_info_idx&31); break;
      case 2: if(ctx_.graph->m_is_executed) p->~T(); break;
      case 3: if(ctx_.instance->m_is_executed) p->~T(); break;
    }
    PFC_PNEW(p)T();
  }
  return p;
}
//----------------------------------------------------------------------------

template<typename T>
void graph_node_base::destruct(void *p_)
{
  ((T*)p_)->~T();
}
//----------------------------------------------------------------------------
