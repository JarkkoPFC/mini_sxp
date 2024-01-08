//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "sxp_src/core_engine/track_set.h"
#include "sxp_src/core/math/tform3.h"
#include "sxp_src/core/sort.h"
using namespace pfc;
//----------------------------------------------------------------------------


#ifdef PFC_ENGINEOP_COLLADA
//============================================================================
// track_set_loader_collada
//============================================================================
class track_set_loader_collada
{
public:
  // loading
  void load(track_set&, bin_input_stream_base&);
  //--------------------------------------------------------------------------

private:
  // nested types
  typedef xml_input_stream::string_t string_t;
  struct rotation_sampler;
  struct rotation_sampler_scalar;
  struct translation_sampler;
  struct translation_sampler_scalar;
  struct matrix_sampler;
  struct matrix_sampler_scalar;
  //--------------------------------------------------------------------------

  //==========================================================================
  // sampler
  //==========================================================================
  struct sampler
  {
    // operations
    bool operator==(const string_t &s_) const  {return id==s_;}
    //------------------------------------------------------------------------

    heap_str id;
    array<collada_data::source_input> inputs;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // anim_channel
  //==========================================================================
  struct anim_channel
  {
    // construction and operations
    PFC_INLINE anim_channel() {target_member_idx=unsigned(-1); sampler_idx=channel_name_idx=0; next=0;}
    PFC_INLINE bool operator==(unsigned channel_name_idx_) const  {return channel_name_idx==channel_name_idx_;}
    //------------------------------------------------------------------------

    unsigned target_member_idx;
    unsigned sampler_idx;
    unsigned channel_name_idx;
    anim_channel *next;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // anim_target
  //==========================================================================
  struct anim_target
  {
    // construction and operations
    PFC_INLINE anim_target()  {channel_list=0; start_time=end_time=0.0f;}
    PFC_INLINE bool operator==(const string_t &id_) const  {return id==id_;}
    //------------------------------------------------------------------------

    heap_str id;
    anim_channel *channel_list;
    float start_time, end_time;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // e_channel_type
  //==========================================================================
  enum e_channel_type
  {
    channeltype_none,
    //----
    channeltype_rotate,
    channeltype_scale,
    channeltype_translate,
    channeltype_matrix,
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // node_input_channel
  //==========================================================================
  struct node_input_channel
  {
    // construction and operations
    PFC_INLINE node_input_channel()  {type=channeltype_none; channel_name_idx=num_floats=init_data_idx=0; next=0;}
    //------------------------------------------------------------------------

    e_channel_type type;
    unsigned channel_name_idx;
    unsigned num_floats;
    unsigned init_data_idx;
    node_input_channel *next;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // e_node_type
  //==========================================================================
  enum e_node_type
  {
    nodetype_node,
    nodetype_joint,
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // scene_node
  //==========================================================================
  struct scene_node
  {
    // construction
    PFC_INLINE scene_node() {type=nodetype_node; parent_idx=-1; target=0; input_list=0; rotation_chl_format=translation_chl_format=trackchannelformat_none;}
    //------------------------------------------------------------------------

    e_node_type type;
    heap_str id, sid;
    int parent_idx;
    tform3f init_tform_n2p;
    array<tform3f> tforms_n2p;
    array<tform_rt3f> tforms_n2p_rt;
    anim_target *target;
    node_input_channel *input_list;
    e_track_channel_format rotation_chl_format;
    e_track_channel_format translation_chl_format;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // e_segment_type
  //==========================================================================
  enum e_segment_type
  {
    segmenttype_none,
    segmenttype_linear,
    segmenttype_bezier,
    segmenttype_hermite,
    segmenttype_bspline,
  };
  //--------------------------------------------------------------------------

  // data parsing
  void parse_animation(xml_input_stream&, string_t&);
  void parse_scene_node(xml_input_stream&, string_t&, int parent_idx_);
  void parse_scene_node_input(xml_input_stream&, string_t&, scene_node&, e_channel_type, unsigned num_floats_);
  unsigned add_channel_name(const string_t&);
  //--------------------------------------------------------------------------

  // track set generation
  void generate_track_set(track_set&);
  template<typename T> void apply_uniform_samples(T *channel_data_, unsigned stride_, const anim_channel&, unsigned start_frame_, unsigned num_frames_);
  e_segment_type segment_type(const heap_str&);
  //--------------------------------------------------------------------------

  collada_info m_asset_info;
  collada_data m_data;
  array<heap_str> m_channel_names;
  array<anim_target> m_anim_targets;
  array<scene_node> m_scene_nodes;
  unsigned m_num_joints;
  deque<sampler> m_samplers;
  deque<anim_channel> m_output_channels;
  deque<node_input_channel> m_input_channels;
  array<float> m_channel_init_data;
  ufloat_t m_sampling_fps;
  float m_global_start_time;
  bool m_has_rotation_data, m_has_translation_data;
};
//----------------------------------------------------------------------------

void track_set_loader_collada::load(track_set &tset_, bin_input_stream_base &stream_)
{
  // parse <?xml...> and <COLLADA...> tags
  xml_input_stream xml_stream(stream_);
  string_t item_name;
  xml_stream.parse_item(item_name, true);
  xml_stream.parse_item(item_name, true);
  PFC_CHECK(item_name=="COLLADA");

  // parse COLLADA sub-tags
  while(xml_stream.parse_element(item_name, true))
  {
    if(item_name=="asset")
      m_asset_info.parse_asset_properties(xml_stream, item_name);
    else if(item_name=="library_animations")
    {
      // parse "library_animations" sub-tags
      while(xml_stream.parse_element(item_name, true))
      {
        if(item_name=="animation")
          parse_animation(xml_stream, item_name);
        else
          xml_stream.skip_element();
      }
    }
    else if(item_name=="library_visual_scenes")
    {
      // parse "library_visual_scenes" sub-tags
      while(xml_stream.parse_element(item_name, true))
      {
        if(item_name=="visual_scene")
        {
          // parse "visual_scene" sub-tags
          m_num_joints=0;
          while(xml_stream.parse_element(item_name))
          {
            if(item_name=="node")
              parse_scene_node(xml_stream, item_name, -1);
            else
              xml_stream.skip_element();
          }
        }
        else
          xml_stream.skip_element();
      }
    }
    else
      xml_stream.skip_element();
  }

  // generate track set from parsed data
  m_sampling_fps=30.0f;
  m_global_start_time=numeric_type<float>::range_max();
  generate_track_set(tset_);
}
//----------------------------------------------------------------------------

void track_set_loader_collada::parse_animation(xml_input_stream &stream_, string_t &item_name_)
{
  // parse "animation" sub-tags
  while(stream_.parse_element(item_name_))
  {
    if(item_name_=="source")
      m_data.parse_data_source(stream_, item_name_);
    else if(item_name_=="sampler")
    {
      // parse sampler ID and sub-tags
      sampler &s=m_samplers.push_back();
      stream_.find_attrib_str("id", s.id);
      while(stream_.parse_element(item_name_))
      {
        if(item_name_=="input")
          m_data.parse_source_input_attribs(s.inputs, stream_, item_name_);
        stream_.skip_element();
      }
    }
    else if(item_name_=="channel")
    {
      // parse "channel" attributes
      anim_channel &chl=m_output_channels.push_back();
      while(stream_.start_attrib_parsing(item_name_))
      {
        if(item_name_=="source")
        {
          stream_.read_word(item_name_);
          item_name_.remove_front(1);
          deque<sampler>::reverse_iterator it=linear_search(m_samplers.rbegin(), m_samplers.rend(), item_name_);
          if(is_valid(it))
            chl.sampler_idx=(unsigned)it.index();
        }
        else if(item_name_=="target")
        {
          // read channel target and split it to target, channel and member names
          stream_.read_word(item_name_);
          char *chl_name=str_find(item_name_.c_str(), '/');
          PFC_CHECK_MSG(chl_name, ("Invalid animation channel target \"%s\"\r\n", item_name_.c_str()));
          *chl_name++=0;
          char *chl_member=str_find(chl_name, '.'); /*todo: support for ()-members*/
          if(chl_member)
          {
            *chl_member++=0;
            if(str_size(chl_member)==1)
            {
              switch(*chl_member)
              {
                case 'X': case 'R': case 'S': case 'U': chl.target_member_idx=0; break;
                case 'Y': case 'G': case 'T': case 'V': chl.target_member_idx=1; break;
                case 'Z': case 'B': case 'P': chl.target_member_idx=2; break;
                case 'W': case 'A': case 'Q': chl.target_member_idx=3; break;
                default: PFC_ERRORF("Unsupported channel member \"%s\"\r\n", chl_member);
              }
            }
            else if(str_eq(chl_member, "ANGLE"))
              chl.target_member_idx=3;
            else
              PFC_ERRORF("Unsupported channel member \"%s\"\r\n", chl_member);
          }
          chl.channel_name_idx=add_channel_name(chl_name);

          // init channel anim target
          string_t target_id=item_name_.c_str();
          array<anim_target>::iterator target_it=linear_search(m_anim_targets.begin(), m_anim_targets.end(), target_id);
          if(target_it)
          {
            chl.next=target_it->channel_list;
            target_it->channel_list=&chl;
          }
          else
          {
            anim_target &target=m_anim_targets.push_back();
            target.id=target_id;
            target.channel_list=&chl;
          }
        }
        stream_.end_attrib_parsing();
      }
      stream_.skip_element();
    }
    else if(item_name_=="animation")
    {
      // recursively parse animations
      stream_.skip_attribs();
      parse_animation(stream_, item_name_);
    }
    else
      stream_.skip_element();
  }
}
//----

void track_set_loader_collada::parse_scene_node(xml_input_stream &stream_, string_t &item_name_, int parent_idx_)
{
  // add node and read node attributes
  unsigned node_idx=(unsigned)m_scene_nodes.size();
  scene_node *node=&m_scene_nodes.push_back();
  node->parent_idx=parent_idx_;
  while(stream_.start_attrib_parsing(item_name_))
  {
    if(item_name_=="id")
      stream_.read_word(node->id);
    else if(item_name_=="sid")
      stream_.read_word(node->sid);
    else if(item_name_=="type")
    {
      stream_.read_word(item_name_);
      if(item_name_=="JOINT")
        node->type=nodetype_joint;
    }
    stream_.end_attrib_parsing();
  }

  // parse "node" sub-tags
  while(stream_.parse_element(item_name_))
  {
    if(item_name_=="rotate")
      parse_scene_node_input(stream_, item_name_, *node, channeltype_rotate, 4);
    else if(item_name_=="scale")
      parse_scene_node_input(stream_, item_name_, *node, channeltype_scale, 3);
    else if(item_name_=="translate")
      parse_scene_node_input(stream_, item_name_, *node, channeltype_translate, 3);
    else if(item_name_=="matrix")
      parse_scene_node_input(stream_, item_name_, *node, channeltype_matrix, 16);
    else if(item_name_=="node")
    {
      parse_scene_node(stream_, item_name_, node_idx);
      node=&m_scene_nodes[node_idx];
    }
    else
      stream_.skip_element();
  }
}
//----

void track_set_loader_collada::parse_scene_node_input(xml_input_stream &stream_, string_t &item_name_, scene_node &node_, e_channel_type type_, unsigned num_floats_)
{
  // setup input channel for the node
  PFC_VERIFY_MSG(stream_.find_attrib_str("sid", item_name_), ("no SID found for node input channel\r\n"));
  node_input_channel &channel=m_input_channels.push_back();
  channel.type=type_;
  channel.channel_name_idx=add_channel_name(item_name_);
  channel.num_floats=num_floats_;
  channel.next=node_.input_list;
  node_.input_list=&channel;
  channel.init_data_idx=(unsigned)m_channel_init_data.size();
  m_channel_init_data.insert_back(num_floats_);
  stream_.read(m_channel_init_data.data()+channel.init_data_idx, num_floats_);
  stream_.skip_element();
}
//----

unsigned track_set_loader_collada::add_channel_name(const string_t &channel_name_)
{
  // add channel name if it doesn't exist and return index to the channel name
  array<heap_str>::const_iterator channel_it=linear_search(m_channel_names.begin(), m_channel_names.end(), channel_name_);
  if(channel_it)
    return unsigned(channel_it-m_channel_names.data());
  m_channel_names.push_back(channel_name_);
  return (unsigned)m_channel_names.size()-1;
}
//----

void track_set_loader_collada::generate_track_set(track_set &tset_)
{
  // get time range for animation targets and global animation range
  bool has_anim=false;
  float global_start_time=0, global_end_time=0;
  for(unsigned i=0; i<m_anim_targets.size(); ++i)
  {
    // process all animation channels for the animation target
    anim_target &target=m_anim_targets[i];
    const anim_channel *achl=target.channel_list;
    bool first_achl=true;
    while(achl)
    {
      // get channel input (time) data
      typedef array<collada_data::source_input>::const_iterator input_iterator_t;
      const sampler &smp=m_samplers[achl->sampler_idx];
      input_iterator_t input_it=linear_search(smp.inputs.begin(), smp.inputs.end(), collsemantic_input);
      PFC_CHECK_MSG(input_it, ("No input data available for the channel\r\n"));
      unsigned num_inputs=(unsigned)m_data.float_array(input_it->array_index).data.size();
      if(num_inputs)
      {
        // expand target start & end times with channel start & end times
        const float *inputs=m_data.float_array(input_it->array_index).data.data();
        target.start_time=first_achl?*inputs:min(*inputs, target.start_time);
        target.end_time=first_achl?inputs[num_inputs-1]:max(inputs[num_inputs-1], target.end_time);
        first_achl=false;
      }
      achl=achl->next;
    }

    // update global start & end times with target start & end times
    if(target.start_time!=target.end_time)
    {
      global_start_time=has_anim?min(global_start_time, target.start_time):target.start_time;
      global_end_time=has_anim?max(global_end_time, target.end_time):target.end_time;
      has_anim=true;
    }
  }

  // return if no animated nodes
  if(!has_anim)
    return;

  // generate uniformly sampled node transformation sequences
  int global_start_frame=int(global_start_time*m_sampling_fps);
  int global_end_frame=int(global_end_time*m_sampling_fps+0.5f);
  unsigned num_global_frames=global_end_frame-global_start_frame+1;
  unsigned num_animated_joints=0;
  unsigned num_total_channels=0;
  unsigned total_channel_data_size=0;
  array<float> channel_data_sp;
  for(unsigned node_idx=0; node_idx<m_scene_nodes.size(); ++node_idx)
  {
    // setup node transforms and get animation target for the node
    scene_node &node=m_scene_nodes[node_idx];
    node.tforms_n2p.resize(num_global_frames);
    tform3f *tforms_n2p=node.tforms_n2p.data();
    node.target=linear_search(m_anim_targets.data(), m_anim_targets.size(), node.id);

    // apply animation channels to node input channels
    unsigned start_frame=node.target?int(node.target->start_time*m_sampling_fps)-global_start_frame:0;
    const node_input_channel *nchl=node.input_list;
    while(nchl)
    {
      // initialize animation data for the channel with default values
      channel_data_sp.resize(nchl->num_floats*num_global_frames);
      float *channel_data=channel_data_sp.data();
      for(unsigned i=0; i<num_global_frames; ++i)
        mem_copy(channel_data+i*nchl->num_floats, m_channel_init_data.data()+nchl->init_data_idx, sizeof(float)*nchl->num_floats);

      // apply matching animation channels to the input channel
      const anim_channel *achl=node.target?node.target->channel_list:0;
      while((achl=ptr(linear_search(slist_const_iterator<anim_channel>(achl), slist_const_iterator<anim_channel>(), nchl->channel_name_idx)))!=0)
      {
        // apply animation channel
        if(achl->target_member_idx==unsigned(-1))
        {
          // switch to full channel handling
          switch(nchl->type)
          {
            case channeltype_rotate: apply_uniform_samples((vec4f*)channel_data, 4, *achl, start_frame, num_global_frames); break;
            case channeltype_scale: apply_uniform_samples((vec3f*)channel_data, 3, *achl, start_frame, num_global_frames); break;
            case channeltype_translate: apply_uniform_samples((vec3f*)channel_data, 3, *achl, start_frame, num_global_frames); break;
            case channeltype_matrix: apply_uniform_samples((mat44f*)channel_data, 16, *achl, start_frame, num_global_frames); break;
            case channeltype_none: PFC_ERROR("Channel type not specified\r\n"); break;
          }
        }
        else
        {
          // switch to channel member handling
          switch(nchl->type)
          {
            case channeltype_rotate: apply_uniform_samples(channel_data+achl->target_member_idx, 4, *achl, start_frame, num_global_frames); break;
            case channeltype_scale: apply_uniform_samples(channel_data+achl->target_member_idx, 3, *achl, start_frame, num_global_frames); break;
            case channeltype_translate: apply_uniform_samples(channel_data+achl->target_member_idx, 3, *achl, start_frame, num_global_frames); break;
            case channeltype_matrix: apply_uniform_samples(channel_data+achl->target_member_idx, 16, *achl, start_frame, num_global_frames); break;
            case channeltype_none: PFC_ERROR("Channel type not specified\r\n"); break;
          }
        }

        // proceed to the next animation channel
        achl=achl->next;
      }

      // apply input channel to the node transformation sequence
      switch(nchl->type)
      {
        // apply initial rotation and animated rotation sequence to the node transform
        case channeltype_rotate:
        {
          const float *init_data=m_channel_init_data.data()+nchl->init_data_idx;
          node.init_tform_n2p*=axis_rot(vec3f(init_data[0], init_data[1], init_data[2]), init_data[3]*mathf::deg_to_rad);
          for(unsigned i=0; i<num_global_frames; ++i)
          {
            tforms_n2p[i]*=axis_rot(vec3f(channel_data[0], channel_data[1], channel_data[2]), channel_data[3]*mathf::deg_to_rad);
            channel_data+=4;
          }
        } break;

        // apply initial scaling and animated scaling sequence to the node transform
        case channeltype_scale:
        {
          const float *init_data=m_channel_init_data.data()+nchl->init_data_idx;
          node.init_tform_n2p*=tform3f(init_data[0], init_data[1], init_data[2]);
          for(unsigned i=0; i<num_global_frames; ++i)
          {
            tforms_n2p[i]*=tform3f(channel_data[0], channel_data[1], channel_data[2]);
            channel_data+=3;
          }
        } break;

        // apply initial translation and animated translation sequence to the node transform
        case channeltype_translate:
        {
          const float *init_data=m_channel_init_data.data()+nchl->init_data_idx;
          node.init_tform_n2p*=tform3f(vec3f(init_data[0], init_data[1], init_data[2]));
          for(unsigned i=0; i<num_global_frames; ++i)
          {
            tforms_n2p[i]*=tform3f(vec3f(channel_data[0], channel_data[1], channel_data[2]));
            channel_data+=3;
          }
        } break;

        // apply initial matrix and animated matrix sequence to the node transform
        case channeltype_matrix:
        {
          const float *init_data=m_channel_init_data.data()+nchl->init_data_idx;
          node.init_tform_n2p*=tform3f(init_data[0], init_data[4], init_data[8], init_data[3],
                                       init_data[1], init_data[5], init_data[9], init_data[7],
                                       init_data[2], init_data[6], init_data[10], init_data[11]);
          for(unsigned i=0; i<num_global_frames; ++i)
          {
            tforms_n2p[i]*=tform3f(channel_data[0], channel_data[4], channel_data[8], channel_data[3],
                                   channel_data[1], channel_data[5], channel_data[9], channel_data[7],
                                   channel_data[2], channel_data[6], channel_data[10], channel_data[11]);
            channel_data+=16;
          }
        } break;

        case channeltype_none: PFC_ERROR("Channel type not specified\r\n"); break;
      }

      // proceed to the next node channel
      nchl=nchl->next;
    }

    {
      // allocate transformations and check for mirrored animation
      node.tforms_n2p_rt.resize(num_global_frames);
      tform3f *tforms_l2o=node.tforms_n2p.data();
      tform_rt3f *tforms_n2p_rt=node.tforms_n2p_rt.data();
      tform3f *parent_l2o=node.parent_idx>=0?m_scene_nodes[node.parent_idx].tforms_n2p.data():0;
      bool is_mirrored=(det(node.init_tform_n2p)>0.0f)!=(det(tforms_l2o[0])>0.0f);

      // generate transformations
      for(unsigned i=0; i<num_global_frames; ++i)
      {
        if(is_mirrored)
        {
          tforms_l2o[i].y.x*=-1.0f;
          tforms_l2o[i].y.y*=-1.0f;
          tforms_l2o[i].y.z*=-1.0f;
        }
        tforms_l2o[i]=parent_l2o?tforms_n2p[i]*parent_l2o[i]:tforms_n2p[i]*m_asset_info.basis_tform();
        tforms_n2p_rt[i]=tforms_l2o[i];
        if(parent_l2o)
          tforms_n2p_rt[i]*=inv(tform_rt3f(parent_l2o[i]));
      }
    }

    if(node.type==nodetype_joint)
    {
      // apply non-joint parent transforms to the joint-node
      tform_rt3f *tforms_n2p_rt=node.tforms_n2p_rt.data();
      scene_node *cur_node=&node;
      while(cur_node->parent_idx>=0 && m_scene_nodes[cur_node->parent_idx].type==nodetype_node)
      {
        // apply parent node transform sequence to the node transform sequence
        scene_node &parent=m_scene_nodes[cur_node->parent_idx];
        const tform_rt3f *parent_n2p_rt=parent.tforms_n2p_rt.data();
        for(unsigned i=0; i<num_global_frames; ++i)
          tforms_n2p_rt[i]*=parent_n2p_rt[i];
        cur_node=&parent;
      }

      // check for animated rotation sequence
      node.rotation_chl_format=trackchannelformat_constant;
      const quatf &ref_rotation=tforms_n2p_rt[0].rotation;
      for(unsigned i=1; i<num_global_frames; ++i)
        if(dot(tforms_n2p_rt[i].rotation, ref_rotation)<0.999f)
        {
          node.rotation_chl_format=trackchannelformat_sample;
          break;
        }

      // check for animated translation sequence
      node.translation_chl_format=trackchannelformat_none;
      const vec3f &ref_translation=tforms_n2p_rt[0].translation;
      for(unsigned i=1; i<num_global_frames; ++i)
        if(norm2(tforms_n2p_rt[i].translation-ref_translation)>0.0001f)
        {
          node.translation_chl_format=trackchannelformat_sample;
          break;
        }

      // update animation channel & joint stats
      num_total_channels+=(node.rotation_chl_format!=trackchannelformat_none)+(node.translation_chl_format!=trackchannelformat_none);
      total_channel_data_size+= ( (node.rotation_chl_format==trackchannelformat_sample?sizeof(quatf):0)
                                 +(node.translation_chl_format==trackchannelformat_sample?sizeof(vec3f):0))*num_global_frames
                               +(node.rotation_chl_format==trackchannelformat_constant?sizeof(quatf):0)
                               +(node.translation_chl_format==trackchannelformat_constant?sizeof(vec3f):0);
      if(node.rotation_chl_format!=trackchannelformat_none || node.translation_chl_format!=trackchannelformat_none)
        ++num_animated_joints;
    }
  }

  // generate track set from sampled transformation data
  tset_.init(m_sampling_fps, num_animated_joints, num_total_channels, total_channel_data_size);
  array<char> track_names;
  track_info *track_inf=tset_.track_infos();
  track_channel_info *channel_inf=tset_.channel_infos();
  unsigned channel_idx=0, data_offset=0;
  for(unsigned node_idx=0; node_idx<m_scene_nodes.size(); ++node_idx)
  {
    // check for animated joint node
    const scene_node &node=m_scene_nodes[node_idx];
    if(node.type==nodetype_joint)
    {
      unsigned num_channels=(node.rotation_chl_format!=trackchannelformat_none)+(node.translation_chl_format!=trackchannelformat_none);
      if(num_channels)
      {
        // setup track info
        track_names.insert_back(node.sid.size()+1, node.sid.c_str());
        unsigned num_keys=(unsigned)node.tforms_n2p.size();
        track_inf->start_frame=0;
        track_inf->num_frames=uint16_t(num_keys-1);
        track_inf->num_channels=uint8_t(num_channels);
        track_inf->channel_offset_start=uint16_t(channel_idx);
        ++track_inf;
        channel_idx+=num_channels;

        // setup rotation channel
        if(node.rotation_chl_format!=trackchannelformat_none)
        {
          channel_inf->channel=trackchannel_rotation;
          channel_inf->format=node.rotation_chl_format;
          channel_inf->data_offset=data_offset;
          quatf *data=(quatf*)((uint8_t*)tset_.channel_data()+data_offset);
          unsigned num_chl_keys=node.rotation_chl_format==trackchannelformat_sample?num_keys:1;
          for(unsigned i=0; i<num_chl_keys; ++i)
          {
            // convert transform to quaternion
            data[i]=node.tforms_n2p_rt[i].rotation;
            if(i>0 && dot(data[i], data[i-1])<0.0f)
              neg(data[i]);
          }

          data_offset+=sizeof(quatf)*num_chl_keys;
          ++channel_inf;
        }

        // setup translation channel
        if(node.translation_chl_format!=trackchannelformat_none)
        {
          channel_inf->channel=trackchannel_position;
          channel_inf->format=node.translation_chl_format;
          channel_inf->data_offset=data_offset;
          vec3f *data=(vec3f*)((uint8_t*)tset_.channel_data()+data_offset);
          unsigned num_chl_keys=node.translation_chl_format==trackchannelformat_sample?num_keys:1;
          for(unsigned i=0; i<num_chl_keys; ++i)
            data[i]=node.tforms_n2p_rt[i].translation;
          data_offset+=sizeof(vec3f)*num_chl_keys;
          ++channel_inf;
        }
      }
    }
  }

  // setup track names and finish track set initialization
  tset_.swap_track_names(track_names);
  tset_.finish_init();
}
//----

template<typename T>
void track_set_loader_collada::apply_uniform_samples(T *channel_data_, unsigned stride_, const anim_channel &achl_, unsigned start_frame_, unsigned num_frames_)
{
  // access animation channel data
  typedef array<collada_data::source_input>::const_iterator input_iterator_t;
  const sampler &smp=m_samplers[achl_.sampler_idx];
  input_iterator_t input_it=linear_search(smp.inputs.begin(), smp.inputs.end(), collsemantic_input);
  PFC_CHECK_MSG(input_it, ("No input data available for the channel\r\n"));
  unsigned num_inputs=(unsigned)m_data.float_array(input_it->array_index).data.size();
  if(!num_inputs)
    return;
  if(num_inputs==1)
    start_frame_=num_frames_;
  input_iterator_t output_it=linear_search(smp.inputs.begin(), smp.inputs.end(), collsemantic_output);
  PFC_CHECK_MSG(output_it, ("No output data available for the channel\r\n"));
  input_iterator_t interpolation_it=linear_search(smp.inputs.begin(), smp.inputs.end(), collsemantic_interpolation);
  input_iterator_t in_tangent_it=linear_search(smp.inputs.begin(), smp.inputs.end(), collsemantic_in_tangent);
  input_iterator_t out_tangent_it=linear_search(smp.inputs.begin(), smp.inputs.end(), collsemantic_out_tangent);
  const float *inputs=m_data.float_array(input_it->array_index).data.data();
  const T *outputs=(const T*)m_data.float_array(output_it->array_index).data.data();
  const heap_str *interpolations=interpolation_it?m_data.name_array(interpolation_it->array_index).data.data():0;
  const T *in_tangents=(const T*)(in_tangent_it?m_data.float_array(in_tangent_it->array_index).data.data():0);
  const T *out_tangents=(const T*)(out_tangent_it?m_data.float_array(out_tangent_it->array_index).data.data():0);

  // fill values before start frame with the first key value
  for(unsigned i=0; i<start_frame_; ++i)
  {
    *channel_data_=*outputs;
    (float*&)channel_data_+=stride_;
  }
  if(start_frame_==num_frames_)
    return;

  // setup data output
  unsigned frame=start_frame_;
  float sampling_spf=rcp_z(m_sampling_fps);
  const float *inputs_end=inputs+num_inputs-1;
  e_segment_type seg_type=interpolations?segment_type(*interpolations):segmenttype_linear;
  float time=float(frame*sampling_spf);
  while(true)
  {
    // switch to proper output value interpolation for the segment type
    ufloat_t rcp_seg_time=1.0f/(inputs[1]-inputs[0]);
    switch(seg_type)
    {
      // apply linear segment samples
      case segmenttype_linear:
      {
        do
        {
          *channel_data_=lerp(outputs[0], outputs[1], (time-inputs[0])*rcp_seg_time);
          if(++frame==num_frames_)
            return;
          (float*&)channel_data_+=stride_;
          time=float(frame*sampling_spf);
        } while(time<=inputs[1]);
      } break;

      // apply cubic Bezier spline segment samples
      case segmenttype_bezier:
      {
        cubic_spline<T> spline;
        make_bezier_spline(spline, outputs[0], *out_tangents, *in_tangents, outputs[1]);
        do
        {
          *channel_data_=evaluate(spline, (time-inputs[0])*rcp_seg_time);
          if(++frame==num_frames_)
            return;
          (float*&)channel_data_+=stride_;
          time=float(frame*sampling_spf);
        } while(time<=inputs[1]);
      } break;

      // apply cubic Hermite spline segment samples
      case segmenttype_hermite:
      {
        cubic_spline<T> spline;
        make_hermite_spline(spline, outputs[0], outputs[1], *out_tangents, *in_tangents);
        do
        {
          *channel_data_=evaluate(spline, (time-inputs[0])*rcp_seg_time);
          if(++frame==num_frames_)
            return;
          (float*&)channel_data_+=stride_;
          time=float(frame*sampling_spf);
        } while(time<=inputs[1]);
      } break;

      // apply cubic B-spline segment samples
      case segmenttype_bspline:
      {
        cubic_spline<T> spline;
        make_bspline(spline, outputs[0], *out_tangents, *in_tangents, outputs[1]);
        do
        {
          *channel_data_=evaluate(spline, (time-inputs[0])*rcp_seg_time);
          if(++frame==num_frames_)
            return;
          (float*&)channel_data_+=stride_;
          time=float(frame*sampling_spf);
        } while(time<=inputs[1]);
      } break;

      // unsupported segment type
      default: PFC_ERRORF("Unsupported segment type \"%s\"\r\n", interpolations->c_str());
    }

    // advance input & output keys
    while(time>inputs[1])
    {
      // check for the end of the channel data
      ++outputs;
      if(++inputs==inputs_end)
      {
        // fill the end of the sequence with the last key value
        for(unsigned i=frame; i<num_frames_; ++i)
        {
          *channel_data_=*outputs;
          (float*&)channel_data_+=stride_;
        }
        return;
      }

      // advance tangents for non-linear segment and proceed to the next segment
      if(seg_type!=segmenttype_linear)
      {
        PFC_CHECK(in_tangents && out_tangents);
        ++in_tangents;
        ++out_tangents;
      }
      if(interpolations)
        seg_type=segment_type(*++interpolations);
    }
  }
}
//----

track_set_loader_collada::e_segment_type track_set_loader_collada::segment_type(const heap_str &s_)
{
  // map interpolation string to enum value
  if(s_=="LINEAR")
    return segmenttype_linear;
  if(s_=="BEZIER")
    return segmenttype_bezier;
  if(s_=="HERMITE")
    return segmenttype_hermite;
  if(s_=="BSPLINE")
    return segmenttype_bspline;
  PFC_ERRORF("Unsupported segment type \"%s\"\r\n", s_.c_str());
  return segmenttype_none;
}
//----------------------------------------------------------------------------


//============================================================================
// load_track_set_collada
//============================================================================
namespace pfc
{
  bool load_track_set_collada(track_set &tset_, bin_input_stream_base &s_)
  {
    {
      // check for COLLADA file format
      auto_stream_seek<bin_input_stream_base> aseek(s_);
      text_input_stream txt_stream(s_);
      char sig_str[8];
      txt_stream.read_word(sig_str, sizeof(sig_str));
      if(!str_eq(sig_str, "<?xml"))
        return false;
      txt_stream.skip_to('<', true);
      txt_stream.read_word(sig_str, sizeof(sig_str));
      if(!str_eq(sig_str, "COLLADA"))
        return false;
    }

    // load track set
    track_set_loader_collada loader;
    loader.load(tset_, s_);
    return true;
  }
} // namespace pfc
//----------------------------------------------------------------------------

#else // PFC_ENGINEOP_COLLADA
namespace pfc
{
  bool load_track_set_collada(track_set &ts_, bin_input_stream_base &stream_)
  {
    return false;
  }
} // namespace pfc
//----------------------------------------------------------------------------
#endif // !PFC_ENGINEOP_COLLADA
