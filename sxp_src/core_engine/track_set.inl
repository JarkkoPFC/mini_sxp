//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// track set private implementation details
//============================================================================
namespace priv_track_set
{
  template<typename T> PFC_INLINE void interpolation_post_process(T &v_) {}
  PFC_INLINE void interpolation_post_process(quatf &q_) {q_=unit(q_);}
} // namespace priv_track_set
//----------------------------------------------------------------------------


//============================================================================
// track_set
//============================================================================
ufloat_t track_set::fps() const
{
  return m_fps;
}
//----

ufloat_t track_set::spf() const
{
  return m_spf;
}
//----

unsigned track_set::num_tracks() const
{
  return m_track_data.num_tracks;
}
//----

bool track_set::has_channel(e_track_channel channel_) const
{
  // search for given channel from the track set
  const track_channel_info *cinfo=channel_infos();
  for(unsigned i=0; i<m_track_data.num_total_channels; ++i)
    if(cinfo[i].channel==channel_)
      return true;
  return false;
}
//----

bool track_set::variable_track_times() const
{
  return m_variable_track_times;
}
//----

unsigned track_set::start_frame() const
{
  return m_start_frame;
}
//----

unsigned track_set::start_frame(unsigned track_index_) const
{
  PFC_ASSERT_PEDANTIC(track_index_<m_track_data.num_tracks);
  return track_infos()[track_index_].start_frame;
}
//----

unsigned track_set::num_frames() const
{
  return m_num_frames;
}
//----

unsigned track_set::num_frames(unsigned track_index_) const
{
  PFC_ASSERT_PEDANTIC(track_index_<m_track_data.num_tracks);
  return track_infos()[track_index_].num_frames;
}
//----------------------------------------------------------------------------

const track_info *track_set::track_infos() const
{
  return (const track_info*)m_track_data.data;
}
//----

track_info *track_set::track_infos()
{
  return (track_info*)m_track_data.data;
}
//----

const track_channel_info *track_set::channel_infos() const
{
  return (const track_channel_info*)((const char*)m_track_data.data+m_track_data.num_tracks*sizeof(track_info));
}
//----

track_channel_info *track_set::channel_infos()
{
  return (track_channel_info*)((char*)m_track_data.data+m_track_data.num_tracks*sizeof(track_info));
}
//----

const track_channel_info *track_set::find_channel_info(const track_info &tinfo_, e_track_channel channel_) const
{
  // find given channel for the track
  const track_channel_info *cinfo=channel_infos()+tinfo_.channel_offset_start;
  const track_channel_info *cinfo_end=cinfo+tinfo_.num_channels;
  while(cinfo!=cinfo_end)
  {
    if(cinfo->channel==channel_)
      return cinfo;
    ++cinfo;
  }
  return 0;
}
//----

const void *track_set::channel_data() const
{
  return (const char*)m_track_data.data+m_track_data.num_tracks*sizeof(track_info)+m_track_data.num_total_channels*sizeof(track_channel_info);
}
//----

void *track_set::channel_data()
{
  return (char*)m_track_data.data+m_track_data.num_tracks*sizeof(track_info)+m_track_data.num_total_channels*sizeof(track_channel_info);
}
//----

const array<char> &track_set::track_names() const
{
  return m_track_names;
}
//----

void track_set::swap_track_names(array<char> &names_)
{
  m_track_names.swap(names_);
}
//----------------------------------------------------------------------------

template<class PE, typename T>
void track_set::serialize_spline_channel(PE &pe_, char *data_, unsigned &data_pos_, unsigned num_frames_, const meta_type<T>&)
{
  // serialize Hermite spline channel
  unsigned data_pos=data_pos_;
  pe_.var(*(T*)(data_+data_pos));
  data_pos+=sizeof(T);
  do
  {
    pe_.var(*(track_key_hermite<T>*)(data_+data_pos));
    num_frames_-=((track_key_hermite<T>*)(data_+data_pos))->num_frames;
    data_pos+=sizeof(track_key_hermite<T>);
  } while(num_frames_);
  data_pos_=data_pos;
}
//----------------------------------------------------------------------------


//============================================================================
// track_set::const_iterator
//============================================================================
template<typename T>
track_set::const_iterator<T>::const_iterator()
{
  // init iterator
  m_data=0;
  m_segment_end=0.0f;
  m_num_frames_left=0;
  m_channel_format=trackchannelformat_none;
  m_segment.a.set(0.0f);
  m_segment.d=m_segment.c=m_segment.b=m_segment.a;
}
//----

template<typename T>
track_set::const_iterator<T>::const_iterator(const track_set &set_, e_track_channel channel_, unsigned track_index_, float start_time_)
{
  init(set_, channel_, track_index_, start_time_);
}
//----------------------------------------------------------------------------

template<typename T>
bool track_set::const_iterator<T>::advance(ufloat_t time_, const track_set &set_)
{
  // advance track to given time value
  float t=m_segment_end-time_;
  if(t<0.0f && !find_segment(t, time_, set_))
    return false;
  return true;
}
//----

template<typename T>
void track_set::const_iterator<T>::evaluate(T &v_, ufloat_t time_) const
{
  // evaluate advanced track for given time value
  if(m_channel_format==trackchannelformat_hermite)
    v_=pfc::evaluate(m_segment, m_segment_end-time_);
  else
    v_=madd(m_segment.c, m_segment_end-time_, m_segment.d);
  priv_track_set::interpolation_post_process(v_);
}
//----

template<typename T>
bool track_set::const_iterator<T>::evaluate(T &v_, ufloat_t time_, const track_set &set_)
{
  // evaluate spline for the given time value
  float t=m_segment_end-time_;
  if(t<0.0f && !find_segment(t, time_, set_))
  {
    v_=m_segment.d;
    return false;
  }
  if(m_channel_format==trackchannelformat_hermite)
    v_=pfc::evaluate(m_segment, t);
  else
    v_=madd(m_segment.c, t, m_segment.d);
  priv_track_set::interpolation_post_process(v_);
  return true;
}
//----------------------------------------------------------------------------


//============================================================================
// track_set::track_data
//============================================================================
track_set::track_data::track_data()
{
  data=0;
}
//----

track_set::track_data::track_data(const track_data &tdata_)
{
  // copy construct the data
  data=0;
  *this=tdata_;
}
//----------------------------------------------------------------------------


//============================================================================
// compressed_track_set
//============================================================================
ufloat_t compressed_track_set::fps() const
{
  return m_fps;
}
//----

ufloat_t compressed_track_set::spf() const
{
  return m_spf;
}
//----

unsigned compressed_track_set::num_tracks() const
{
  return m_num_tracks;
}
//----

bool compressed_track_set::has_channel(e_track_channel channel_) const
{
  // search for given channel
  const e_track_channel *chls=m_channels.data(), *end=chls+m_channels.size();
  while(chls!=end)
    if(*chls++==channel_)
      return true;
  return false;
}
//----

bool compressed_track_set::variable_track_times() const
{
  return m_variable_track_times;
}
//----

unsigned compressed_track_set::start_frame() const
{
  return m_start_frame;
}
//----

unsigned compressed_track_set::start_frame(unsigned track_index_) const
{
  // return start frame for the given track
  PFC_ASSERT_PEDANTIC(m_variable_track_times && track_index_<m_num_tracks);
  const track_times *ttimes=(const track_times*)(m_track_channel_data.data()+m_num_tracks*m_channels.size()*sizeof(channel_offset));
  return ttimes[track_index_].start_frame;
}
//----

unsigned compressed_track_set::num_frames() const
{
  return m_num_frames;
}
//----

unsigned compressed_track_set::num_frames(unsigned track_index_) const
{
  // return number of frames for the given track
  PFC_ASSERT_PEDANTIC(m_variable_track_times && track_index_<m_num_tracks);
  const track_times *ttimes=(const track_times*)(m_track_channel_data.data()+m_num_tracks*m_channels.size()*sizeof(channel_offset));
  return ttimes[track_index_].num_frames;
}
//----------------------------------------------------------------------------

const void *compressed_track_set::track_channel_data(e_track_channel channel_, unsigned track_index_) const
{
  // return data for the given track channel
  const e_track_channel *channels=m_channels.data();
  unsigned num_channels=(unsigned)m_channels.size();
  for(unsigned i=0; i<num_channels; ++i)
    if(channels[i]==channel_)
    {
      const uint8_t *data=m_track_channel_data.data();
      const channel_offset *channel_offsets=(const channel_offset*)data;
      channel_offset offset=channel_offsets[i*m_num_tracks+track_index_];
      return offset!=null_channel_offset?data+offset:0;
    }
  return 0;
}
//----------------------------------------------------------------------------


//============================================================================
// compressed_track_set::const_iterator
//============================================================================
template<typename T>
compressed_track_set::const_iterator<T>::const_iterator()
{
  // init iterator
  m_segment_end=0.0f;
  m_data=0;
  m_num_segments_left=0;
  m_segment.a.set(0.0f);
  m_segment.d=m_segment.c=m_segment.b=m_segment.a;
}
//----

template<typename T>
compressed_track_set::const_iterator<T>::const_iterator(const compressed_track_set &set_, e_track_channel channel_, unsigned track_index_, float start_time_)
{
  init(set_, channel_, track_index_, start_time_);
}
//----------------------------------------------------------------------------

template<typename T>
bool compressed_track_set::const_iterator<T>::advance(ufloat_t time_, const compressed_track_set &set_)
{
  // advance track to given time value
  float t=m_segment_end-time_;
  if(t<0.0f && !find_segment(t, time_, set_))
    return false;
  return true;
}
//----

template<typename T>
void compressed_track_set::const_iterator<T>::evaluate(T &v_, ufloat_t time_) const
{
  // evaluate advanced track for given time value
  v_=pfc::evaluate(m_segment, m_segment_end-time_);
  priv_track_set::interpolation_post_process(v_);
}
//----

template<typename T>
bool compressed_track_set::const_iterator<T>::evaluate(T &v_, ufloat_t time_, const compressed_track_set &set_)
{
  // evaluate spline for the given time value
  float t=m_segment_end-time_;
  if(t<0.0f && !find_segment(t, time_, set_))
  {
    v_=m_segment.d;
    return false;
  }
  v_=pfc::evaluate(m_segment, t);
  priv_track_set::interpolation_post_process(v_);
  return true;
}
//----------------------------------------------------------------------------
