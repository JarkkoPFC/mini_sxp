//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// collada_info
//============================================================================
const mat33f &collada_info::basis_tform() const
{
  return m_basis_tform;
}
//----------------------------------------------------------------------------


//============================================================================
// collada_data
//============================================================================
collada_data::source &collada_data::append_source()
{
  return m_sources.push_back();
}
//----------------------------------------------------------------------------

const collada_data::data_array<heap_str> &collada_data::name_array(unsigned idx_) const
{
  return m_data_array_name[idx_];
}
//----

const collada_data::data_array<float> &collada_data::float_array(unsigned idx_) const
{
  return m_data_array_float[idx_];
}
//----------------------------------------------------------------------------


//============================================================================
// collada_data::data_array
//============================================================================
template<typename T>
collada_data::data_array<T>::data_array()
{
  stride=0;
}
//----

template<typename T>
bool collada_data::data_array<T>::operator==(const string_t &s_) const
{
  return id==s_;
}
//----------------------------------------------------------------------------


//============================================================================
// collada_data::source
//============================================================================
bool collada_data::source::operator==(const string_t &s_) const
{
  return id==s_;
}
//----------------------------------------------------------------------------


//============================================================================
// collada_data::source_input
//============================================================================
collada_data::source_input::source_input()
{
  semantic=collsemantic_none;
  array_index=0;
  offset=0;
  set=0;
}
//----

bool collada_data::source_input::operator==(e_collada_input_semantic s_)
const
{
  return semantic==s_;
}
//----------------------------------------------------------------------------
