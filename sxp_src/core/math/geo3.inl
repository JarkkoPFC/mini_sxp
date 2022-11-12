//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// covariance_matrix
//============================================================================
template<typename T>
mat33<T> covariance_matrix(const vec3<T> *points_, usize_t num_points_)
{
  // calculate the mean of the points
  PFC_ASSERT(points_ && num_points_);
  typedef typename math<T>::scalar_t scalar_t;
  const vec3<T> *p=points_, *end=points_+num_points_;
  vec3<T> mean(0, 0, 0);
  do
    mean+=*p;
  while(++p!=end);
  scalar_t rn=scalar_t(1)/scalar_t(num_points_);
  mean*=rn;

  // calculate covariance matrix elements
  scalar_t e[6]={0};
  do
  {
    vec3<T> d=*points_-mean;
    e[0]+=d.x*d.x;
    e[1]+=d.x*d.y;
    e[2]+=d.x*d.z;
    e[3]+=d.y*d.y;
    e[4]+=d.y*d.z;
    e[5]+=d.z*d.z;
  } while(++points_!=end);
  for(unsigned i=0; i<6; ++i)
    e[i]*=rn;

  // return the covariance matrix
  return mat33<T>(e[0], e[1], e[2],
                  e[1], e[3], e[4],
                  e[2], e[4], e[5]);
}
//----

template<typename T>
mat33<T> covariance_matrix(const vec3<T> *points_, const uint32_t *tri_indices_, usize_t num_triangles_, bool is_tri_strip_)
{
  // calculate covariance matrix elements for the mesh surface
  PFC_ASSERT(points_ && tri_indices_ && num_triangles_);
  typedef typename math<T>::scalar_t scalar_t;
  unsigned tri_idx_step=is_tri_strip_?1:3;
  const uint32_t *end=tri_indices_+num_triangles_*tri_idx_step;
  scalar_t ah2=0, e[6]={0};
  vec3<T> mh(0, 0, 0);
  do
  {
    const vec3<T> &p=points_[tri_indices_[0]];
    const vec3<T> &q=points_[tri_indices_[1]];
    const vec3<T> &r=points_[tri_indices_[2]];
    scalar_t a2=norm(cross(q-p, r-p));
    ah2+=a2;
    vec3<T> m=p+q+r;
    mh+=a2*m;
    e[0]+=a2*(m.x*m.x+p.x*p.x+q.x*q.x+r.x*r.x);
    e[1]+=a2*(m.x*m.y+p.x*p.y+q.x*q.y+r.x*r.y);
    e[2]+=a2*(m.x*m.z+p.x*p.z+q.x*q.z+r.x*r.z);
    e[3]+=a2*(m.y*m.y+p.y*p.y+q.y*q.y+r.y*r.y);
    e[4]+=a2*(m.y*m.z+p.y*p.z+q.y*q.z+r.y*r.z);
    e[5]+=a2*(m.z*m.z+p.z*p.z+q.z*q.z+r.z*r.z);
    tri_indices_+=tri_idx_step;
  } while(tri_indices_!=end);

  // finalize the element calculation
  scalar_t rah2=scalar_t(1)/ah2;
  mh*=rah2;
  scalar_t s=rah2*scalar_t(1.0/12.0);
  e[0]=e[0]*s-mh.x*mh.x;
  e[1]=e[1]*s-mh.x*mh.y;
  e[2]=e[2]*s-mh.x*mh.z;
  e[3]=e[3]*s-mh.y*mh.y;
  e[4]=e[4]*s-mh.y*mh.z;
  e[5]=e[5]*s-mh.z*mh.z;

  // return the covariance matrix
  return mat33<T>(e[0], e[1], e[2],
                  e[1], e[3], e[4],
                  e[2], e[4], e[5]);
}
//----------------------------------------------------------------------------


//============================================================================
// quickhull
//============================================================================
namespace priv
{
  template<typename T>
  struct quickhull3_tri
  {
    uint32_t pntlist, pntlist_last;
    uint32_t points[3];
    uint32_t neighbor_tris[3];
    vec3<T> normal;
    T maxd;
    uint32_t maxp_idx;
    uint32_t prev_maxp_idx;
    uint32_t prev_tri, next_tri;
  };
  //----

  template<typename T>
  struct quickhull3_hull
  {
    quickhull3_hull(quickhull3_point<T> *points_)
    {
      // initialize hull
      points=points_;
      hull_point_idx=0;
      nonempty_trilist=uint32_t(-1);
      empty_trilist=uint32_t(-1);
      free_trilist=uint32_t(-1);
      removed_trilist=uint32_t(-1);
      new_trilist=uint32_t(-1);
      orphan_pntlist=uint32_t(-1);
      num_tris=0;
    }
    //----

    deque<quickhull3_tri<T> > tris;
    quickhull3_point<T> *points;
    uint32_t hull_point_idx;
    uint32_t nonempty_trilist;
    uint32_t empty_trilist;
    uint32_t free_trilist;
    uint32_t removed_trilist;
    uint32_t new_trilist;
    uint32_t orphan_pntlist;
    uint32_t num_tris;
  };
  //----

  template<typename T>
  void quickhull3_add_hull_point(quickhull3_hull<T> &hull_, uint32_t tri_idx_)
  {
    // add triangle points to the orphan point list
    quickhull3_tri<T> &tri=hull_.tris[tri_idx_];
    if(tri.pntlist!=uint32_t(-1))
    {
      hull_.points[tri.pntlist_last].next_pnt=hull_.orphan_pntlist;
      hull_.orphan_pntlist=tri.pntlist;
      tri.pntlist=uint32_t(-1);
    }
    tri.pntlist=uint32_t(-2);

    // recursively process neighbor triangles that can be seen from the point
    const vec3<T> &hull_point=hull_.points[hull_.hull_point_idx].pos;
    for(unsigned ni=0; ni<3; ++ni)
    {
      // skip removed neighbor triangles
      unsigned ntri_idx=tri.neighbor_tris[ni];
      quickhull3_tri<T> &ntri=hull_.tris[ntri_idx];
      if(ntri.pntlist==uint32_t(-2))
        continue;

      // check if the neighbor triangle is visible to the new convex hull point
      T d=max(dot(hull_point-hull_.points[ntri.points[0]].pos, ntri.normal),
              dot(hull_point-hull_.points[ntri.points[1]].pos, ntri.normal),
              dot(hull_point-hull_.points[ntri.points[2]].pos, ntri.normal));
      if(d>=0 && dot(tri.normal, ntri.normal)>T(-0.9999))
        quickhull3_add_hull_point(hull_, ntri_idx);
      else
      {
        // allocate new triangle for the horizon edge (from the free-list or deque)
        quickhull3_tri<T> *t;
        unsigned tidx=hull_.free_trilist;
        if(tidx!=uint32_t(-1))
        {
          t=&hull_.tris[tidx];
          hull_.free_trilist=t->next_tri;
        }
        else
        {
          tidx=(unsigned)hull_.tris.size();
          t=&hull_.tris.push_back();
        }

        // setup the triangle
        t->pntlist=uint32_t(-1);
        t->points[0]=tri.points[ni];
        t->points[1]=tri.points[ni==2?0:ni+1];
        t->points[2]=hull_.hull_point_idx;
        t->neighbor_tris[0]=tri.neighbor_tris[ni];
        t->neighbor_tris[1]=0xdeadbeef;/**/
        t->neighbor_tris[2]=0xdeadbeef;/**/
        t->normal=unit_z(cross(hull_.points[t->points[0]].pos-hull_point, hull_.points[t->points[1]].pos-hull_point));
        t->maxd=-1;
        t->maxp_idx=uint32_t(-1);
        t->prev_maxp_idx=uint32_t(-1);
        t->prev_tri=0xdeadbeef;/**/
        t->next_tri=hull_.new_trilist;
        hull_.new_trilist=tidx;
        ntri.neighbor_tris[ntri.points[0]==t->points[1]?0:ntri.points[1]==t->points[1]?1:2]=tidx;
        ++hull_.num_tris;

        // check if a triangle has been added earlier for the horizon edge start-point
        quickhull3_point<T> &e2p=hull_.points[t->points[0]];
        if(e2p.next_pnt==uint32_t(-1))
          e2p.next_pnt=tidx;
        else
        {
          // triangle added earlier => setup neighbor info between the two new triangles
          quickhull3_tri<T> &e2t=hull_.tris[e2p.next_pnt];
          e2t.neighbor_tris[1]=tidx;
          t->neighbor_tris[2]=e2p.next_pnt;
          e2p.next_pnt=uint32_t(-1);
        }

        // check if a triangle has been added earlier for the horizon edge end-point
        quickhull3_point<T> &e1p=hull_.points[t->points[1]];
        if(e1p.next_pnt==uint32_t(-1))
          e1p.next_pnt=tidx;
        else
        {
          // triangle added earlier => setup neighbor info between the two new triangles
          quickhull3_tri<T> &e1t=hull_.tris[e1p.next_pnt];
          e1t.neighbor_tris[2]=tidx;
          t->neighbor_tris[1]=e1p.next_pnt;
          e1p.next_pnt=uint32_t(-1);
        }
      }
    }

    // remove the triangle from the convex hull
    if(tri.prev_tri!=uint32_t(-1))
      hull_.tris[tri.prev_tri].next_tri=tri.next_tri;
    else
      if(hull_.empty_trilist==tri_idx_)
        hull_.empty_trilist=tri.next_tri;
      else
        hull_.nonempty_trilist=tri.next_tri;
    if(tri.next_tri!=uint32_t(-1))
      hull_.tris[tri.next_tri].prev_tri=tri.prev_tri;
    tri.next_tri=hull_.removed_trilist;
    hull_.removed_trilist=tri_idx_;
    --hull_.num_tris;
}
  //----

  template<typename T>
  void quickhull3_partition_orphan_points(quickhull3_hull<T> &hull_)
  {
    // partition orphan points to new hull triangles in new_trilist
    unsigned pnt_idx=hull_.orphan_pntlist;
    while(pnt_idx!=uint32_t(-1))
    {
      // find first triangle which has the point on its front side
      quickhull3_point<T> &pnt=hull_.points[pnt_idx];
      unsigned next_pnt=pnt.next_pnt;
      unsigned tri_idx=hull_.new_trilist;
      while(tri_idx!=uint32_t(-1))
      {
        // check if the point is on or on the front side of the triangle
        quickhull3_tri<T> &tri=hull_.tris[tri_idx];
        vec3<T> a=pnt.pos-hull_.points[tri.points[0]].pos;
        vec3<T> b=pnt.pos-hull_.points[tri.points[1]].pos;
        vec3<T> c=pnt.pos-hull_.points[tri.points[2]].pos;
        T d=min(dot(tri.normal, a), dot(tri.normal, b), dot(tri.normal, c));
        if(!is_zero(a) && !is_zero(b) && !is_zero(c) && d>=0)
        {
          // check for the furthest point for the triangle
          if(d>tri.maxd)
          {
            tri.maxd=d;
            tri.maxp_idx=pnt_idx;
            tri.prev_maxp_idx=uint32_t(-1);
          }
          else if(tri.pntlist==tri.maxp_idx)
            tri.prev_maxp_idx=pnt_idx;

          // add point to the point list of the triangle
          if(tri.pntlist==uint32_t(-1))
            tri.pntlist_last=pnt_idx;
          pnt.next_pnt=tri.pntlist;
          tri.pntlist=pnt_idx;
          break;
        }
        tri_idx=tri.next_tri;
      }
      pnt_idx=next_pnt;
    }
    hull_.orphan_pntlist=uint32_t(-1);

    // move triangles in the new triangle list to empty/non-empty triangle lists
    unsigned tri_idx=hull_.new_trilist;
    while(tri_idx!=uint32_t(-1))
    {
      // check if the point list of the triangle is empty
      quickhull3_tri<T> &tri=hull_.tris[tri_idx];
      tri.prev_tri=uint32_t(-1);
      unsigned next_tri=tri.next_tri;
      if(tri.pntlist==uint32_t(-1))
      {
        // no points => add to empty_trilist
        tri.next_tri=hull_.empty_trilist;
        hull_.empty_trilist=tri_idx;
      }
      else
      {
        // has points => add to nonempty_trilist
        tri.next_tri=hull_.nonempty_trilist;
        hull_.nonempty_trilist=tri_idx;
      }

      // update previous triangle index of the next triangle
      if(tri.next_tri!=uint32_t(-1))
        hull_.tris[tri.next_tri].prev_tri=tri_idx;
      tri_idx=next_tri;
    }
    hull_.new_trilist=uint32_t(-1);

    // move removed triangles to triangle free list
    while(hull_.removed_trilist!=uint32_t(-1))
    {
      quickhull3_tri<T> &tri=hull_.tris[hull_.removed_trilist];
      uint32_t next=tri.next_tri;
      tri.next_tri=hull_.free_trilist;
      hull_.free_trilist=hull_.removed_trilist;
      hull_.removed_trilist=next;
    }
  }
  //----

  template<typename T>
  bool quickhull3_setup_initial_simplex(quickhull3_hull<T> &hull_, usize_t num_points_)
  {
    // find min and max coordinates along x, y & z axes
    typedef typename math<T>::scalar_t scalar_t;
    vec3<T> minx=hull_.points->pos, miny=minx, minz=minx, maxx=minx, maxy=minx, maxz=minz;
    unsigned minx_idx=0, miny_idx=0, minz_idx=0, maxx_idx=0, maxy_idx=0, maxz_idx=0;
    for(unsigned i=1; i<num_points_; ++i)
    {
      const vec3<T> &p=hull_.points[i].pos;
      if(p.x<minx.x || (p.x==minx.x && (p.y<minx.y || (p.y==minx.y && p.z<minx.z))))
      {
        minx=p;
        minx_idx=i;
      }
      if(p.y<miny.y || (p.y==miny.y && (p.x<miny.x || (p.x==miny.x && p.z<miny.z))))
      {
        miny=p;
        miny_idx=i;
      }
      if(p.z<minz.z || (p.z==minz.z && (p.x<minz.x || (p.x==minz.x && p.y<minz.y))))
      {
        minz=p;
        minz_idx=i;
      }
      if(p.x>maxx.x || (p.x==maxx.x && (p.y>maxx.y || (p.y==maxx.y && p.z>maxx.z))))
      {
        maxx=p;
        maxx_idx=i;
      }
      if(p.y>maxy.y || (p.y==maxy.y && (p.x>maxy.x || (p.x==maxy.x && p.z>maxy.z))))
      {
        maxy=p;
        maxy_idx=i;
      }
      if(p.z>maxz.z || (p.z==maxz.z && (p.x>maxz.x || (p.x==maxz.x && p.y>maxz.y))))
      {
        maxz=p;
        maxz_idx=i;
      }
    }

    // get points with maximum axis extension
    scalar_t dx2=norm2(maxx-minx), dy2=norm2(maxy-miny), dz2=norm2(maxz-minz);
    unsigned idx0, idx1;
    unsigned search_indices[4];
    if(dx2>dy2)
      if(dx2>dz2)
      {
        idx0=minx_idx;
        idx1=maxx_idx;
        search_indices[0]=miny_idx;
        search_indices[1]=miny_idx;
        search_indices[2]=minz_idx;
        search_indices[3]=minz_idx;
      }
      else
      {
        idx0=minz_idx;
        idx1=maxz_idx;
        search_indices[0]=minx_idx;
        search_indices[1]=minx_idx;
        search_indices[2]=miny_idx;
        search_indices[3]=miny_idx;
      }
    else
      if(dy2>dz2)
      {
        idx0=miny_idx;
        idx1=maxy_idx;
        search_indices[0]=minx_idx;
        search_indices[1]=minx_idx;
        search_indices[2]=minz_idx;
        search_indices[3]=minz_idx;
      }
      else
      {
        idx0=minz_idx;
        idx1=maxz_idx;
        search_indices[0]=minx_idx;
        search_indices[1]=minx_idx;
        search_indices[2]=miny_idx;
        search_indices[3]=miny_idx;
      }
    const vec3<T> &pnt0=hull_.points[idx0].pos;
    const vec3<T> &pnt1=hull_.points[idx1].pos;
    hull_.points[idx0].next_pnt=uint32_t(-1);
    hull_.points[idx1].next_pnt=uint32_t(-1);

    // get 3rd extreme point which maximizes the triangle area defined with the two points
    unsigned idx2=idx0;
    scalar_t max_area2=0;
    vec3<T> max_edge=pnt1-pnt0, maxp=pnt0;
    for(unsigned i=0; i<4; ++i)
    {
      unsigned idx=search_indices[i];
      const vec3<T> &p=hull_.points[idx].pos;
      scalar_t area2=norm2(cross(max_edge, p-pnt0));
      if(area2>max_area2 || (area2==max_area2 && (p.x<maxp.x || (p.x==maxp.x && (p.y<maxp.y || (p.y==maxp.y && p.z<maxp.z))))))
      {
        max_area2=area2;
        maxp=p;
        idx2=idx;
      }
    }

    // if no point found find the max triangle area point from the entire point set
    if(!max_area2)
      for(unsigned i=0; i<num_points_; ++i)
      {
        vec3<T> &p=hull_.points[i].pos;
        scalar_t area2=norm2(cross(max_edge, p-pnt0));
        if(area2>max_area2 || (area2==max_area2 && (p.x<maxp.x || (p.x==maxp.x && (p.y<maxp.y || (p.y==maxp.y && p.z<maxp.z))))))
        {
          max_area2=area2;
          maxp=p;
          idx2=i;
        }
      }
    const vec3<T> &pnt2=hull_.points[idx2].pos;
    hull_.points[idx2].next_pnt=uint32_t(-1);
    if(!max_area2)
    {
      PFC_WARN(("The input point set is degenerated\r\n"));
      return false;
    }

    // setup initial simplex: two triangles facing opposite directions
    quickhull3_tri<T> &t0=hull_.tris.push_back();
    quickhull3_tri<T> &t1=hull_.tris.push_back();
    t0.pntlist=uint32_t(-1);
    t0.points[0]=idx0;
    t0.points[1]=idx1;
    t0.points[2]=idx2;
    t0.neighbor_tris[0]=1;
    t0.neighbor_tris[1]=1;
    t0.neighbor_tris[2]=1;
    t0.normal=unit(cross(pnt1-pnt0, pnt2-pnt0));
    t0.maxd=-1;
    t0.maxp_idx=uint32_t(-1);
    t0.prev_maxp_idx=uint32_t(-1);
    t0.prev_tri=0xdeadbeef;/**/
    t0.next_tri=1;
    t1.pntlist=uint32_t(-1);
    t1.points[0]=idx0;
    t1.points[1]=idx2;
    t1.points[2]=idx1;
    t1.neighbor_tris[0]=0;
    t1.neighbor_tris[1]=0;
    t1.neighbor_tris[2]=0;
    t1.normal=-t0.normal;
    t1.maxd=-1;
    t1.maxp_idx=uint32_t(-1);
    t1.prev_maxp_idx=0xdeadbeef;/**/
    t1.prev_tri=uint32_t(-1);
    t1.next_tri=uint32_t(-1);
    hull_.new_trilist=0;
    hull_.num_tris=2;

    // partition points to the simplex triangles
    unsigned prev_idx=uint32_t(-1);
    for(unsigned i=0; i<num_points_; ++i)
      if(i!=idx0 && i!=idx1 && i!=idx2)
      {
        if(prev_idx!=uint32_t(-1))
          hull_.points[prev_idx].next_pnt=i;
        else
          hull_.orphan_pntlist=i;
        prev_idx=i;
      }
    hull_.points[prev_idx].next_pnt=uint32_t(-1);
    quickhull3_partition_orphan_points(hull_);
    return true;
  }
} // namespace priv
//----

template<typename T>
void quickhull3(quickhull3_point<T> *points_, usize_t num_points_, array<vec3<T> > &hull_points_, array<uint32_t> *tri_indices_)
{
  // clear output points and indices
  using namespace priv;
  PFC_ASSERT(points_);
  hull_points_.resize(0);
  if(tri_indices_)
    tri_indices_->resize(0);

  // setup initial simplex for the convex hull
  quickhull3_hull<T> hull(points_);
  if(!quickhull3_setup_initial_simplex(hull, num_points_))
    return;

  // refine convex hull until no triangles with points in front of them left
  unsigned num_hull_points=2;
  while(hull.nonempty_trilist!=uint32_t(-1))
  {
    // remove the new convex hull point from the triangle point list
    unsigned tri_idx=hull.nonempty_trilist;
    quickhull3_tri<T> &tri=hull.tris[tri_idx];
    hull.hull_point_idx=tri.maxp_idx;
    quickhull3_point<T> &pnt=hull.points[tri.maxp_idx];
    if(tri.prev_maxp_idx!=uint32_t(-1))
      hull.points[tri.prev_maxp_idx].next_pnt=pnt.next_pnt;
    else
      tri.pntlist=pnt.next_pnt;
    pnt.next_pnt=uint32_t(-1);

    // add new convex hull point
    quickhull3_add_hull_point(hull, tri_idx);
    quickhull3_partition_orphan_points(hull);
    ++num_hull_points;
  }

  // create convex hull points and triangles
  hull_points_.reserve(num_hull_points);
  if(tri_indices_)
    tri_indices_->reserve(hull.num_tris*3);
  unsigned tri_idx=hull.empty_trilist;
  while(tri_idx!=uint32_t(-1))
  {
    quickhull3_tri<T> &tri=hull.tris[tri_idx];
    quickhull3_point<T> &p0=hull.points[tri.points[0]];
    quickhull3_point<T> &p1=hull.points[tri.points[1]];
    quickhull3_point<T> &p2=hull.points[tri.points[2]];
    if(p0.next_pnt==uint32_t(-1))
    {
      p0.next_pnt=(unsigned)hull_points_.size();
      hull_points_.push_back(p0.pos);
    }
    if(p1.next_pnt==uint32_t(-1))
    {
      p1.next_pnt=(unsigned)hull_points_.size();
      hull_points_.push_back(p1.pos);
    }
    if(p2.next_pnt==uint32_t(-1))
    {
      p2.next_pnt=(unsigned)hull_points_.size();
      hull_points_.push_back(p2.pos);
    }
    if(tri_indices_)
    {
      uint32_t idx[3]={p0.next_pnt, p1.next_pnt, p2.next_pnt};
      tri_indices_->insert_back(3, idx);
    }
    tri_idx=tri.next_tri;
  }
}
//----------------------------------------------------------------------------


//============================================================================
// bounding_aabox3
//============================================================================
template<typename T>
aabox3<T> bounding_aabox3(const vec3<T> *points_, usize_t num_points_)
{
  // find min and max coordinates along x, y and z axes
  PFC_ASSERT(points_ && num_points_);
  typedef typename math<T>::scalar_t scalar_t;
  const vec3<T> *end=points_+num_points_;
  vec3<T> minp=*points_++, maxp=minp;
  if(num_points_>1)
    do
    {
      minp=min(minp, *points_);
      maxp=max(maxp, *points_);
    } while(++points_!=end);

  // return axis-aligned bounding box
  return aabox3<T>((maxp+minp)*scalar_t(0.5), (maxp-minp)*scalar_t(0.5));
}
//----------------------------------------------------------------------------


//============================================================================
// seed_oobox3_discrete
//============================================================================
namespace priv
{
  template<typename T>
  seed_oobox3<T> find_discrete_seedbox3(const typename math<T>::scalar_t *extremal_d_, const vec3<T> *extremal_pnts_, unsigned num_exts_, const vec3<T> *points_, usize_t num_points_, const uint32_t *point_indices_)
  {
    // predefined axes and their norms
    typedef typename math<T>::scalar_t scalar_t;
    seed_oobox3<T> seedbox;
    static const vec3<T> s_axes[]=
    {
      // 3-axes
      vec3<T>(1, 0, 0), vec3<T>(0, 1, 0), vec3<T>(0, 0, 1),
      // 7-axes
      vec3<T>(1, 1, 1), vec3<T>(1, 1, -1), vec3<T>(1, -1, 1), vec3<T>(1, -1, -1),
      // 13-axes
      vec3<T>(1, 1, 0), vec3<T>(1, -1, 0), vec3<T>(1, 0, 1), vec3<T>(1, 0, -1), vec3<T>(0, 1, 1), vec3<T>(0, 1, -1),
      // 49-axes
      vec3<T>(0, 1, 2), vec3<T>(0, 2, 1), vec3<T>(1, 0, 2), vec3<T>(2, 0, 1), vec3<T>(1, 2, 0), vec3<T>(2, 1, 0),
      vec3<T>(0, 1, -2), vec3<T>(0, 2, -1), vec3<T>(1, 0, -2), vec3<T>(2, 0, -1), vec3<T>(1, -2, 0), vec3<T>(2, -1, 0),
      vec3<T>(1, 1, 2), vec3<T>(2, 1, 1), vec3<T>(1, 2, 1), vec3<T>(1, -1, 2), vec3<T>(1, 1, -2), vec3<T>(1, -1, -2),
      vec3<T>(2, -1, 1), vec3<T>(2, 1, -1), vec3<T>(2, -1, -1), vec3<T>(1, -2, 1), vec3<T>(1, 2, -1), vec3<T>(1, -2, -1),
      vec3<T>(2, 2, 1), vec3<T>(1, 2, 2), vec3<T>(2, 1, 2), vec3<T>(2, -2, 1), vec3<T>(2, 2, -1), vec3<T>(2, -2, -1),
      vec3<T>(1, -2, 2), vec3<T>(1, 2, -2), vec3<T>(1, -2, -2), vec3<T>(2, -1, 2), vec3<T>(2, 1, -2), vec3<T>(2, -1, -2)
    };
    static const scalar_t s_rnorms[]=
    {
      scalar_t(1), scalar_t(1), scalar_t(1),
      math<T>::rsqrt3, math<T>::rsqrt3, math<T>::rsqrt3, math<T>::rsqrt3,
      math<T>::rsqrt2, math<T>::rsqrt2, math<T>::rsqrt2, math<T>::rsqrt2, math<T>::rsqrt2, math<T>::rsqrt2,
      scalar_t(0.447213595), scalar_t(0.447213595), scalar_t(0.447213595), scalar_t(0.447213595), scalar_t(0.447213595), scalar_t(0.447213595),
      scalar_t(0.447213595), scalar_t(0.447213595), scalar_t(0.447213595), scalar_t(0.447213595), scalar_t(0.447213595), scalar_t(0.447213595),
      scalar_t(0.40824829), scalar_t(0.40824829), scalar_t(0.40824829), scalar_t(0.40824829), scalar_t(0.40824829), scalar_t(0.40824829),
      scalar_t(0.40824829), scalar_t(0.40824829), scalar_t(0.40824829), scalar_t(0.40824829), scalar_t(0.40824829), scalar_t(0.40824829),
      scalar_t(0.333333333), scalar_t(0.333333333), scalar_t(0.333333333), scalar_t(0.333333333), scalar_t(0.333333333), scalar_t(0.333333333),
      scalar_t(0.333333333), scalar_t(0.333333333), scalar_t(0.333333333), scalar_t(0.333333333), scalar_t(0.333333333), scalar_t(0.333333333)
    };

    // find maximum and minimum diameter axes
    unsigned aidx=0, min_aidx=0, max_aidx=0;
    scalar_t mind=numeric_type<scalar_t>::range_max(), maxd=scalar_t(-1);
    for(unsigned i=0; i<num_exts_; i+=2, ++aidx)
    {
      scalar_t d=(extremal_d_[i+1]-extremal_d_[i])*s_rnorms[aidx];
      if(d>maxd)
      {
        maxd=d;
        max_aidx=aidx;
      }
    }
    aidx=0;
    for(unsigned i=0; i<num_exts_; i+=2, ++aidx)
    {
      scalar_t d=(extremal_d_[i+1]-extremal_d_[i])*s_rnorms[aidx];
      if(i!=max_aidx && d<mind)
      {
        mind=d;
        min_aidx=aidx;
      }
    }

    // setup min, med and max axes
    seedbox.max_ext[0]=extremal_pnts_[max_aidx*2+0];
    seedbox.max_ext[1]=extremal_pnts_[max_aidx*2+1];
    scalar_t maxp=scalar_t(0.5)*(extremal_d_[max_aidx*2+0]+extremal_d_[max_aidx*2+1]);
    maxp*=s_rnorms[max_aidx];
    const vec3<T> max_axis=s_axes[max_aidx]*s_rnorms[max_aidx];
    const vec3<T> min_axis=unit(s_axes[min_aidx]-max_axis*dot(s_axes[min_aidx], max_axis));
    const vec3<T> med_axis=cross(min_axis, max_axis);

    // calculate mesh extents on min and med axes
    scalar_t min_ext[2]={numeric_type<scalar_t>::range_max(), numeric_type<scalar_t>::range_min()};
    scalar_t med_ext[2]={numeric_type<scalar_t>::range_max(), numeric_type<scalar_t>::range_min()};
    if(point_indices_)
    {
      const uint32_t *end=point_indices_+num_points_;
      do
      {
        const vec3<T> &p=points_[*point_indices_];
        scalar_t dmin=dot(min_axis, p);
        if(dmin<min_ext[0])
          min_ext[0]=dmin;
        if(dmin>min_ext[1])
          min_ext[1]=dmin;
        scalar_t dmed=dot(med_axis, p);
        if(dmed<med_ext[0])
          med_ext[0]=dmed;
        if(dmed>med_ext[1])
          med_ext[1]=dmed;
      } while(++point_indices_!=end);
    }
    else
    {
      const vec3<T> *end=points_+num_points_;
      do
      {
        const vec3<T> &p=*points_;
        scalar_t dmin=dot(min_axis, p);
        if(dmin<min_ext[0])
          min_ext[0]=dmin;
        if(dmin>min_ext[1])
          min_ext[1]=dmin;
        scalar_t dmed=dot(med_axis, p);
        if(dmed<med_ext[0])
          med_ext[0]=dmed;
        if(dmed>med_ext[1])
          med_ext[1]=dmed;
      } while(++points_!=end);
    }
    scalar_t minp=scalar_t(0.5)*(min_ext[1]+min_ext[0]);
    mind=min_ext[1]-min_ext[0];
    scalar_t medp=scalar_t(0.5)*(med_ext[1]+med_ext[0]);
    scalar_t medd=med_ext[1]-med_ext[0];

    // calculate oobox from the max/min/med axes
    mat33<T> rot(max_axis, med_axis, min_axis);
    seedbox.oobox.pos=vec3<T>(maxp, medp, minp)*rot;
    seedbox.oobox.hsize=vec3<T>(maxd, medd, mind)*scalar_t(0.5);
    convert(seedbox.oobox.rot, rot);
    return seedbox;
  }
}
//----

template<typename T>
seed_oobox3<T> seed_oobox3_discrete(const vec3<T> *points_, usize_t num_points_, e_discrete_axes3 axes_, const uint32_t *point_indices_)
{
  // define discrete axis tests
  #define PFC_DISCRETE_AXIS_TEST(idx__, v__)\
  {\
    scalar_t v=v__;\
    if(v<extremal_d[idx__])\
    {\
      extremal_d[idx__]=v;\
      extremal_pnts[idx__]=*p;\
    }\
    if(v>extremal_d[idx__+1])\
    {\
      extremal_d[idx__+1]=v;\
      extremal_pnts[idx__+1]=*p;\
    }\
  }
  #define PFC_DISCRETE_AXES_001() PFC_DISCRETE_AXIS_TEST(0, p->x);\
                                  PFC_DISCRETE_AXIS_TEST(2, p->y);\
                                  PFC_DISCRETE_AXIS_TEST(4, p->z);
  #define PFC_DISCRETE_AXES_111() scalar_t p1xp1y=p->x+p->y, p1xn1y=p->x-p->y;\
                                  PFC_DISCRETE_AXIS_TEST(6, p1xp1y+p->z);\
                                  PFC_DISCRETE_AXIS_TEST(8, p1xp1y-p->z);\
                                  PFC_DISCRETE_AXIS_TEST(10, p1xn1y+p->z);\
                                  PFC_DISCRETE_AXIS_TEST(12, p1xn1y-p->z);
  #define PFC_DISCRETE_AXES_011() PFC_DISCRETE_AXIS_TEST(14, p1xp1y);\
                                  PFC_DISCRETE_AXIS_TEST(16, p1xn1y);\
                                  PFC_DISCRETE_AXIS_TEST(18, p->x+p->z);\
                                  PFC_DISCRETE_AXIS_TEST(20, p->x-p->z);\
                                  PFC_DISCRETE_AXIS_TEST(22, p->y+p->z);\
                                  PFC_DISCRETE_AXIS_TEST(24, p->y-p->z);
  #define PFC_DISCRETE_AXES_012() vec3<T> p2=*p+*p;\
                                  scalar_t p1xp2y=p->x+p2.y, p1xn2y=p->x-p2.y, p2xp1y=p2.x+p->y, p2xn1y=p2.x-p->y;\
                                  PFC_DISCRETE_AXIS_TEST(26, p->y+p2.z);\
                                  PFC_DISCRETE_AXIS_TEST(28, p2.y+p->z);\
                                  PFC_DISCRETE_AXIS_TEST(30, p->x+p2.z);\
                                  PFC_DISCRETE_AXIS_TEST(32, p2.x+p->z);\
                                  PFC_DISCRETE_AXIS_TEST(34, p1xp2y);\
                                  PFC_DISCRETE_AXIS_TEST(36, p2xp1y);\
                                  PFC_DISCRETE_AXIS_TEST(38, p->y-p2.z);\
                                  PFC_DISCRETE_AXIS_TEST(40, p2.y-p->z);\
                                  PFC_DISCRETE_AXIS_TEST(42, p->x-p2.z);\
                                  PFC_DISCRETE_AXIS_TEST(44, p2.x-p->z);\
                                  PFC_DISCRETE_AXIS_TEST(46, p1xn2y);\
                                  PFC_DISCRETE_AXIS_TEST(48, p2xn1y);
  #define PFC_DISCRETE_AXES_112() PFC_DISCRETE_AXIS_TEST(50, p1xp1y+p2.z);\
                                  PFC_DISCRETE_AXIS_TEST(52, p2xp1y+p->z);\
                                  PFC_DISCRETE_AXIS_TEST(54, p1xp2y+p->z);\
                                  PFC_DISCRETE_AXIS_TEST(56, p1xn1y+p2.z);\
                                  PFC_DISCRETE_AXIS_TEST(58, p1xp1y-p2.z);\
                                  PFC_DISCRETE_AXIS_TEST(60, p1xn1y-p2.z);\
                                  PFC_DISCRETE_AXIS_TEST(62, p2xn1y+p->z);\
                                  PFC_DISCRETE_AXIS_TEST(64, p2xp1y-p->z);\
                                  PFC_DISCRETE_AXIS_TEST(66, p2xn1y-p->z);\
                                  PFC_DISCRETE_AXIS_TEST(68, p1xn2y+p->z);\
                                  PFC_DISCRETE_AXIS_TEST(70, p1xp2y-p->z);\
                                  PFC_DISCRETE_AXIS_TEST(72, p1xn2y-p->z);
  #define PFC_DISCRETE_AXES_122() PFC_DISCRETE_AXIS_TEST(74, p2.x+p2.y+p->z);\
                                  PFC_DISCRETE_AXIS_TEST(76, p1xp2y+p2.z);\
                                  PFC_DISCRETE_AXIS_TEST(78, p2xp1y+p2.z);\
                                  PFC_DISCRETE_AXIS_TEST(80, p2.x-p2.y+p->z);\
                                  PFC_DISCRETE_AXIS_TEST(82, p2.x+p2.y-p->z);\
                                  PFC_DISCRETE_AXIS_TEST(84, p2.x-p2.y-p->z);\
                                  PFC_DISCRETE_AXIS_TEST(86, p1xn2y+p2.z);\
                                  PFC_DISCRETE_AXIS_TEST(88, p1xp2y-p2.z);\
                                  PFC_DISCRETE_AXIS_TEST(90, p1xn2y-p2.z);\
                                  PFC_DISCRETE_AXIS_TEST(92, p2xn1y+p2.z);\
                                  PFC_DISCRETE_AXIS_TEST(94, p2xp1y-p2.z);\
                                  PFC_DISCRETE_AXIS_TEST(96, p2xn1y-p2.z);

  // find extremal points along given predefined axes
  PFC_ASSERT(points_ && num_points_);
  typedef typename math<T>::scalar_t scalar_t;
  switch(axes_)
  {
    // 3-axes test
    case discrete_axes3_3:
    {
      // init extremal values
      enum {num_exts=6};
      vec3<T> extremal_pnts[num_exts];
      scalar_t extremal_d[num_exts];
      for(unsigned i=0; i<num_exts; i+=2)
      {
        extremal_d[i]=numeric_type<scalar_t>::range_max();
        extremal_d[i+1]=numeric_type<scalar_t>::range_min();
      }

      // find extremal values for the 3 axes
      if(point_indices_)
      {
        const uint32_t *idx=point_indices_, *end=point_indices_+num_points_;
        do
        {
          const vec3<T> *p=points_+*idx;
          PFC_DISCRETE_AXES_001();
        } while(++idx!=end);
      }
      else
      {
        const vec3<T> *p=points_, *end=points_+num_points_;
        do
        {
          PFC_DISCRETE_AXES_001();
        } while(++p!=end);
      }
      return priv::find_discrete_seedbox3(extremal_d, extremal_pnts, num_exts, points_, num_points_, point_indices_);
    } break;

    // 7-axes test
    case discrete_axes3_7:
    {
      // init extremal values
      enum {num_exts=14};
      vec3<T> extremal_pnts[num_exts];
      scalar_t extremal_d[num_exts];
      for(unsigned i=0; i<num_exts; i+=2)
      {
        extremal_d[i]=numeric_type<scalar_t>::range_max();
        extremal_d[i+1]=numeric_type<scalar_t>::range_min();
      }

      // find extremal values for the 7 axes
      if(point_indices_)
      {
        const uint32_t *idx=point_indices_, *end=point_indices_+num_points_;
        do
        {
          const vec3<T> *p=points_+*idx;
          PFC_DISCRETE_AXES_001();
          PFC_DISCRETE_AXES_111();
        } while(++idx!=end);
      }
      else
      {
        const vec3<T> *p=points_, *end=points_+num_points_;
        do
        {
          PFC_DISCRETE_AXES_001();
          PFC_DISCRETE_AXES_111();
        } while(++p!=end);
      }
      return priv::find_discrete_seedbox3(extremal_d, extremal_pnts, num_exts, points_, num_points_, point_indices_);
    } break;

    // 13-axes test
    case discrete_axes3_13:
    {
      // init extremal values
      enum {num_exts=26};
      vec3<T> extremal_pnts[num_exts];
      scalar_t extremal_d[num_exts];
      for(unsigned i=0; i<num_exts; i+=2)
      {
        extremal_d[i]=numeric_type<scalar_t>::range_max();
        extremal_d[i+1]=numeric_type<scalar_t>::range_min();
      }

      // find extremal values for the 13 axes
      if(point_indices_)
      {
        const uint32_t *idx=point_indices_, *end=point_indices_+num_points_;
        do
        {
          const vec3<T> *p=points_+*idx;
          PFC_DISCRETE_AXES_001();
          PFC_DISCRETE_AXES_111();
          PFC_DISCRETE_AXES_011();
        } while(++idx!=end);
      }
      else
      {
        const vec3<T> *p=points_, *end=points_+num_points_;
        do
        {
          PFC_DISCRETE_AXES_001();
          PFC_DISCRETE_AXES_111();
          PFC_DISCRETE_AXES_011();
        } while(++p!=end);
      }
      return priv::find_discrete_seedbox3(extremal_d, extremal_pnts, num_exts, points_, num_points_, point_indices_);
    } break;

    // 49-axes test
    case discrete_axes3_49:
    {
      // init extremal values
      enum {num_exts=98};
      vec3<T> extremal_pnts[num_exts];
      scalar_t extremal_d[num_exts];
      for(unsigned i=0; i<num_exts; i+=2)
      {
        extremal_d[i]=numeric_type<scalar_t>::range_max();
        extremal_d[i+1]=numeric_type<scalar_t>::range_min();
      }

      // find extremal values for the 49 axes
      if(point_indices_)
      {
        const uint32_t *idx=point_indices_, *end=point_indices_+num_points_;
        do
        {
          const vec3<T> *p=points_+*idx;
          PFC_DISCRETE_AXES_001();
          PFC_DISCRETE_AXES_111();
          PFC_DISCRETE_AXES_011();
          PFC_DISCRETE_AXES_012();
          PFC_DISCRETE_AXES_112();
          PFC_DISCRETE_AXES_122();
        } while(++idx!=end);
      }
      else
      {
        const vec3<T> *p=points_, *end=points_+num_points_;
        do
        {
          PFC_DISCRETE_AXES_001();
          PFC_DISCRETE_AXES_111();
          PFC_DISCRETE_AXES_011();
          PFC_DISCRETE_AXES_012();
          PFC_DISCRETE_AXES_112();
          PFC_DISCRETE_AXES_122();
        } while(++p!=end);
      }
      return priv::find_discrete_seedbox3(extremal_d, extremal_pnts, num_exts, points_, num_points_, point_indices_);
    } break;

    // unknown precision
    default: PFC_ERROR(("Unsupported discrete axis configuration\r\n"));
  }

  // undef discrete axis tests
  #undef PFC_DISCRETE_AXIS_TEST
  #undef PFC_DISCRETE_AXES_001
  #undef PFC_DISCRETE_AXES_111
  #undef PFC_DISCRETE_AXES_011
  #undef PFC_DISCRETE_AXES_012
  #undef PFC_DISCRETE_AXES_112
  #undef PFC_DISCRETE_AXES_122
  seed_oobox3<T> seedbox={oobox3<T>(vec3<T>::s_zero, vec3<T>::s_zero, quat<T>::s_identity), {vec3<T>::s_zero, vec3<T>::s_zero}};
  return seedbox;
}
//----------------------------------------------------------------------------


//============================================================================
// seed_oobox_cov
//============================================================================
template<typename T>
seed_oobox3<T> seed_oobox3_cov(const vec3<T> *points_, usize_t num_points_, const mat33<T> &cov_matrix_, const uint32_t *point_indices_)
{
  // calculate max/min/med object diameter axes using covariance matrix
  PFC_ASSERT(points_ && num_points_);
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t detcov;
  mat33<T> invcov=inv(cov_matrix_, &detcov);
  vec3<T> max_axis=eigenvector_pow(cov_matrix_);
  vec3<T> min_axis=detcov?eigenvector_pow(invcov):max_axis;
  if(abs(dot(min_axis, max_axis))>scalar_t(0.0001))
    min_axis=vec3<T>(0, 1, 0)*zrot_u(max_axis);
  vec3<T> med_axis=unit(cross(min_axis, max_axis));
  min_axis=cross(max_axis, med_axis);

  // find max/min/med diameter extents on min/max/med axes
  seed_oobox3<T> seedbox;
  scalar_t maxd_ext[2]={numeric_type<T>::range_max(), numeric_type<T>::range_min()};
  scalar_t mind_ext[2]={numeric_type<T>::range_max(), numeric_type<T>::range_min()};
  scalar_t medd_ext[2]={numeric_type<T>::range_max(), numeric_type<T>::range_min()};
  oobox3<T> ext;
  if(point_indices_)
  {
    const uint32_t *end=point_indices_+num_points_;
    do
    {
      // check for maximum diameter extreme points
      const vec3<T> &p=points_[*point_indices_];
      scalar_t maxd=dot(p, max_axis);
      if(maxd<maxd_ext[0])
      {
        maxd_ext[0]=maxd;
        seedbox.max_ext[0]=p;
      }
      if(maxd>maxd_ext[1])
      {
        maxd_ext[1]=maxd;
        seedbox.max_ext[1]=p;
      }

      // check for minimum diameter extreme points
      scalar_t mind=dot(p, min_axis);
      if(mind<mind_ext[0])
        mind_ext[0]=mind;
      if(mind>mind_ext[1])
        mind_ext[1]=mind;

      // check for medium diameter extreme points
      scalar_t medd=dot(p, med_axis);
      if(medd<medd_ext[0])
        medd_ext[0]=medd;
      if(medd>medd_ext[1])
        medd_ext[1]=medd;
    } while(++point_indices_!=end);
  }
  else
  {
    const vec3<T> *end=points_+num_points_;
    do
    {
      // check for maximum diameter extreme points
      scalar_t maxd=dot(*points_, max_axis);
      if(maxd<maxd_ext[0])
      {
        maxd_ext[0]=maxd;
        seedbox.max_ext[0]=*points_;
      }
      if(maxd>maxd_ext[1])
      {
        maxd_ext[1]=maxd;
        seedbox.max_ext[1]=*points_;
      }

      // check for minimum diameter extreme points
      scalar_t mind=dot(*points_, min_axis);
      if(mind<mind_ext[0])
        mind_ext[0]=mind;
      if(mind>mind_ext[1])
        mind_ext[1]=mind;

      // check for medium diameter extreme points
      scalar_t medd=dot(*points_, med_axis);
      if(medd<medd_ext[0])
        medd_ext[0]=medd;
      if(medd>medd_ext[1])
        medd_ext[1]=medd;
    } while(++points_!=end);
  }

  // calculate oobox from the max/min/med axes
  mat33<T> rot(max_axis, med_axis, min_axis);
  seedbox.oobox.pos=vec3<T>(maxd_ext[1]+maxd_ext[0], medd_ext[1]+medd_ext[0], mind_ext[1]+mind_ext[0])*scalar_t(0.5)*rot;
  seedbox.oobox.hsize=vec3<T>(maxd_ext[1]-maxd_ext[0], medd_ext[1]-medd_ext[0], mind_ext[1]-mind_ext[0])*scalar_t(0.5);
  convert(seedbox.oobox.rot, rot);
  return seedbox;
}
//----------------------------------------------------------------------------


//============================================================================
// optimize_oobox
//============================================================================
template<typename T>
oobox3<T> optimize_oobox3(const vec3<T> *convex_points_, usize_t num_points_, const uint32_t *convex_tris_, usize_t num_tris_, const oobox3<T> &box_)
{
  // allocate memory for triangle adjacency info
  array<uint32_t> adj_info(num_tris_*6+num_points_);
  mem_zero(adj_info.data(), sizeof(uint32_t)*adj_info.size());
  uint32_t *point_lists=adj_info.data();
  uint32_t *next_tris=point_lists+num_points_;
  uint32_t *next_pnts=next_tris+num_tris_*3;

  // build list of triangles attached to each point
  uint32_t idx=0, tvidx=0;
  for(unsigned i=0; i<num_tris_; ++i)
  {
    uint32_t pidx=convex_tris_[idx];
    next_pnts[idx++]=point_lists[pidx];
    point_lists[pidx]=tvidx|1;
    pidx=convex_tris_[idx];
    next_pnts[idx++]=point_lists[pidx];
    point_lists[pidx]=tvidx|2;
    pidx=convex_tris_[idx];
    next_pnts[idx++]=point_lists[pidx];
    point_lists[pidx]=tvidx|3;
    tvidx+=4;
  }

  // setup triangle adjacency info
  for(unsigned i=0; i<num_points_; ++i)
  {
    uint32_t tvidx=point_lists[i];
    PFC_ASSERT_MSG(tvidx, ("Point has no attached triangles\r\n"));
    while(true)
    {
      // check if there are triangles left for the point
      uint32_t tidx3=(tvidx>>2)*3, vidx=(tvidx&3)-1;
      tvidx=next_pnts[tidx3+vidx];
      if(!tvidx)
        break;

      // find triangles with matching point indices and setup adjacency
      uint32_t search_tvidx=point_lists[i];
      uint32_t vidxn=vidx==2?0:vidx+1, pidxn=convex_tris_[tidx3+vidxn];
      while(true)
      {
        uint32_t stidx3=(search_tvidx>>2)*3, svidx=(search_tvidx&3)-1, svidxp=svidx?svidx-1:2;
        if(convex_tris_[stidx3+svidxp]==pidxn)
        {
          // setup adjacency for triangles with matching indices
          next_tris[stidx3+svidxp]=tidx3;
          next_tris[tidx3+vidx]=stidx3;
          break;
        }
        search_tvidx=next_pnts[stidx3+svidx];
        PFC_ASSERT_PEDANTIC_MSG(search_tvidx, ("The mesh isn't closed\r\n"));
      }
    }
  }

  // optimize the oobox
  enum {num_iterations=6};
  oobox3<T> ob=box_;
  unsigned num_iter_exec=0;
  for(unsigned ai=0; ai<num_iterations; ++ai)
  {
    // setup rotation
    mat33<T> rot;
    convert(rot, ob.rot);
    switch(ai%3)
    {
      case 1: swap(rot.y, rot.z); neg(rot.z); break;
      case 2: swap(rot.x, rot.z); neg(rot.z); break;
    }

    // build horizon edge-loop for the given rotation
    typedef typename math<T>::scalar_t scalar_t;
    mem_zero(point_lists, sizeof(*point_lists)*num_points_);
    uint32_t tidx3=0, start_point=0, num_edges=0;
    for(unsigned ti=0; ti<num_tris_; ++ti)
    {
      // check for a front-facing triangle
      if(dot(rot.z, cross(convex_points_[convex_tris_[tidx3+1]]-convex_points_[convex_tris_[tidx3+0]],
                          convex_points_[convex_tris_[tidx3+2]]-convex_points_[convex_tris_[tidx3+0]]))>0)
      {
        // check for back-facing neighbor triangles for the horizon edge
        for(unsigned i=0; i<3; ++i)
        {
          uint32_t next_tidx3=next_tris[tidx3+i];
          if(dot(rot.z, cross(convex_points_[convex_tris_[next_tidx3+1]]-convex_points_[convex_tris_[next_tidx3+0]],
                              convex_points_[convex_tris_[next_tidx3+2]]-convex_points_[convex_tris_[next_tidx3+0]]))<=0)
          {
            // add the edge between the triangles to the edge-loop
            start_point=convex_tris_[tidx3+(i==2?0:i+1)]+1;
            point_lists[convex_tris_[tidx3+i]]=start_point;
            ++num_edges;
          }
        }
      }
      tidx3+=3;
    }

    // check for valid horizon edge-loop
    if(!start_point)
      continue;
    uint32_t spidx=--start_point, spidx2=point_lists[spidx]-1;
    do
    {
      if(spidx2!=start_point && (spidx2=point_lists[spidx2]-1)!=start_point && (spidx==(spidx2=point_lists[spidx2]-1)))
        break;
      spidx=point_lists[spidx]-1;
      --num_edges;
    } while(spidx!=start_point);
    if(spidx!=start_point || num_edges)
      continue;

    // find minimum area enclosing rectangle with rotating calipers algorithm
    uint32_t pidx=start_point;
    scalar_t min_area=numeric_type<scalar_t>::range_max(), min_hwidth=-1, min_hheight=-1;
    vec2<T> min_center, min_edgex;
    do
    {
      // setup 2d-edge -> xy-plane transform
      uint32_t next_pidx=point_lists[pidx]-1;
      PFC_ASSERT(next_pidx!=uint32_t(-1));
      vec2<T> p0(dot(rot.x, convex_points_[pidx]), dot(rot.y, convex_points_[pidx]));
      vec2<T> edgex=vec2<T>(dot(rot.x, convex_points_[next_pidx]), dot(rot.y, convex_points_[next_pidx]))-p0;
      if(norm2(edgex)<scalar_t(0.0001))
      {
        pidx=next_pidx;
        continue;
      }
      edgex=unit(edgex);
      vec2<T> edgey(-edgex.y, edgex.x);

      // find extreme points in the edge-space & check for invalid edge-loop
      scalar_t minx=numeric_type<scalar_t>::range_max();
      scalar_t maxx=numeric_type<scalar_t>::range_min();
      scalar_t maxy=numeric_type<scalar_t>::range_min();
      uint32_t spidx=start_point;
      do
      {
        // check for an extreme point
        scalar_t x=dot(edgex, vec2<T>(dot(rot.x, convex_points_[spidx]), dot(rot.y, convex_points_[spidx]))-p0);
        scalar_t y=dot(edgey, vec2<T>(dot(rot.x, convex_points_[spidx]), dot(rot.y, convex_points_[spidx]))-p0);
        if(x<minx)
          minx=x;
        if(x>maxx)
          maxx=x;
        if(y>maxy)
          maxy=y;
        spidx=point_lists[spidx]-1;
      } while(spidx!=start_point);

      // check for the smallest area enclosing rectangle
      scalar_t area=(maxx-minx)*maxy;
      if(area<min_area)
      {
        min_area=area;
        min_hwidth=scalar_t(0.5)*(maxx-minx);
        min_hheight=scalar_t(0.5)*maxy;
        min_center=p0+edgex*(minx+min_hwidth)+edgey*min_hheight;
        min_edgex=edgex;
      }

      // proceed to the next edge
      pidx=next_pidx;
    } while(pidx!=start_point);

    // adjust oobox with the minimum area enclosing rectangle
    if(min_hwidth>=0)
    {
      ob.pos+=(min_center.x-dot(ob.pos, rot.x))*rot.x+(min_center.y-dot(ob.pos, rot.y))*rot.y;
      switch(ai%3)
      {
        case 0: ob.hsize.x=min_hwidth; ob.hsize.y=min_hheight; break;
        case 1: ob.hsize.x=min_hwidth; ob.hsize.z=min_hheight; break;
        case 2: ob.hsize.z=min_hwidth; ob.hsize.y=min_hheight; break;
      }
      ob.rot=unit(axis_rot_u(rot.z, atan2(min_edgex.y, min_edgex.x))*ob.rot);
    }
    ++num_iter_exec;
  }

  // check for full optimization
  if(num_iter_exec<num_iterations)
    PFC_WARN(("Unable to fully optimize the oriented box (%i/%i)\r\n", num_iter_exec, num_iterations));

  // setup maximum box side length to oobox x-component
  if(ob.hsize.y>ob.hsize.x && ob.hsize.y>ob.hsize.z)
  {
    swap(ob.hsize.x, ob.hsize.y);
    ob.rot=unit(axis_rot_u(vec3<T>(0, 0, 1)*ob.rot, math<T>::half_pi)*ob.rot);
  }
  else if(ob.hsize.z>ob.hsize.x)
  {
    swap(ob.hsize.x, ob.hsize.z);
    ob.rot=unit(axis_rot_u(vec3<T>(0, 1, 0)*ob.rot, math<T>::half_pi)*ob.rot);
  }

  // setup minimum box side length to oobox z-component
  if(ob.hsize.y<ob.hsize.z)
  {
    swap(ob.hsize.y, ob.hsize.z);
    ob.rot=unit(axis_rot_u(vec3<T>(1, 0, 0)*ob.rot, math<T>::half_pi)*ob.rot);
  }

  // return the optimized oobox
  return ob;
}
//----------------------------------------------------------------------------


//============================================================================
// 
//============================================================================
template<typename T>
sphere3<T> bounding_sphere3(const vec3<T> &p0_, const vec3<T> &p1_)
{
  typedef typename math<T>::scalar_t scalar_t;
  return sphere3<T>((p0_+p1_)/scalar_t(2), norm(p0_-p1_));
}
//----

template<typename T>
sphere3<T> bounding_sphere3(const vec3<T> &p0_, const vec3<T> &p1_, const vec3<T> &p2_)
{
  typedef typename math<T>::scalar_t scalar_t;
  vec3<T> a=p1_-p0_;
  vec3<T> b=p2_-p0_;
  vec3<T> axb=cross(a, b);
  float d=scalar_t(2)*norm2(axb);
  vec3<T> o=(norm2(b)*cross(axb, a)+
             norm2(a)*cross(b, axb))/d;
  return sphere3f(p0_+o, norm(o));
}
//----

template<typename T>
sphere3<T> bounding_sphere3(const vec3<T> &p0_, const vec3<T> &p1_, const vec3<T> &p2_, const vec3<T> &p3_)
{
  typedef typename math<T>::scalar_t scalar_t;
  vec3<T> a=p1_-p0_;
  vec3<T> b=p2_-p0_;
  vec3<T> c=p3_-p0_;
  float d=scalar_t(2)*det(mat33<T>(a, b, c));
  vec3<T> o=(norm2(c)*cross(a, b)+
             norm2(b)*cross(c, a)+
             norm2(a)*cross(b, c))/d;
  return sphere3f(p0_+o, norm(o));
}
//----------------------------------------------------------------------------


//============================================================================
// bounding_sphere3_exp
//============================================================================
template<typename T>
sphere3<T> bounding_sphere3_exp(const vec3<T> *points_, usize_t num_points_, const seed_oobox3<T> &seed_, bool use_oobox_, const uint32_t *point_indices_)
{
  // setup initial sphere and adjust the sphere to contain all points
  PFC_ASSERT(points_ && num_points_);
  typedef typename math<T>::scalar_t scalar_t;
  sphere3<T> sphere(use_oobox_?seed_.oobox.pos:(seed_.max_ext[0]+seed_.max_ext[1])*scalar_t(0.5),
                    use_oobox_?seed_.oobox.hsize.x:norm(seed_.max_ext[0]-seed_.max_ext[1])*scalar_t(0.5));

  // expand the sphere with the next point outside the sphere
  scalar_t srad2=sphere.rad*sphere.rad;
  if(point_indices_)
  {
    const uint32_t *end=point_indices_+num_points_;
    do
    {
      // check for outside point
      const vec3<T> &p=points_[*point_indices_];
      scalar_t d2=norm2(p-sphere.pos);
      if(d2>srad2)
      {
        // adjust the sphere to contain the old sphere & outside point
        scalar_t d=sqrt(d2), old_rad=sphere.rad;
        sphere.rad=(sphere.rad+d)*scalar_t(0.5);
        srad2=sphere.rad*sphere.rad;
        sphere.pos+=(p-sphere.pos)*((sphere.rad-old_rad)/d);
      }
    } while(++point_indices_!=end);
  }
  else
  {
    const vec3<T> *p=points_, *end=points_+num_points_;
    do
    {
      // check for outside point
      scalar_t d2=norm2(*p-sphere.pos);
      if(d2>srad2)
      {
        // adjust the sphere to contain the old sphere & outside point
        scalar_t d=sqrt(d2), old_rad=sphere.rad;
        sphere.rad=(sphere.rad+d)*scalar_t(0.5);
        srad2=sphere.rad*sphere.rad;
        sphere.pos+=(*p-sphere.pos)*((sphere.rad-old_rad)/d);
      }
    } while(++p!=end);
  }

  // return the bounding sphere
  return sphere;
}
//----------------------------------------------------------------------------


//============================================================================
// bounding_sphere3_maxexp
//============================================================================
template<typename T>
sphere3<T> bounding_sphere3_maxexp(vec3<T> *points_, usize_t num_points_, const seed_oobox3<T> &seed_, bool use_oobox_)
{
  // setup initial sphere and adjust the sphere to contain all points
  PFC_ASSERT(points_ && num_points_);
  typedef typename math<T>::scalar_t scalar_t;
  sphere3<T> sphere(use_oobox_?seed_.oobox.pos:(seed_.max_ext[0]+seed_.max_ext[1])*scalar_t(0.5),
                    use_oobox_?seed_.oobox.hsize.x:norm(seed_.max_ext[0]-seed_.max_ext[1])*scalar_t(0.5));

  // expand the sphere with the point furthest from the origin
  vec3<T> *p=points_, *end=points_+num_points_;
  while(true)
  {
    vec3<T> *maxd_pnt=0;
    scalar_t srad2=sphere.rad*sphere.rad, maxd2=srad2;
    do
    {
      // check for outside point
      scalar_t d2=norm2(*p-sphere.pos);
      if(d2>srad2)
      {
        // swap point to outside point set and check for maximum distance point
        swap(*p, *--end);
        if(d2>maxd2)
        {
          maxd2=d2;
          maxd_pnt=end;
        }
        continue;
      }
      ++p;
    } while(p!=end);

    // check for outside points
    if(!maxd_pnt)
      break;

    // adjust the sphere to contain the old sphere & furthest point
    scalar_t maxd=sqrt(maxd2), old_rad=sphere.rad;
    sphere.rad=(sphere.rad+maxd)*scalar_t(0.5);
    sphere.pos+=(*maxd_pnt-sphere.pos)*((sphere.rad-old_rad)/maxd);

    // remove max distance point and proceed to the next iteration
    swap(*maxd_pnt, *p);
    end=points_+num_points_;
    if(++p==end)
      break;
  }

  // return the bounding sphere
  return sphere;
}
//----------------------------------------------------------------------------


//============================================================================
// capcyl3
//============================================================================
template<typename T> const capcyl3<T> capcyl3<T>::s_zero(capsule3<T>::s_zero, 0, 0);
//----------------------------------------------------------------------------

template<typename T>
capcyl3<T>::capcyl3()
{
}
//----

template<typename T>
capcyl3<T>::capcyl3(const capsule3<T> &cap_, typename math<T>::scalar_t cylinder_hlen_, typename math<T>::scalar_t cylinder_posd_)
  :capsule(cap_)
  ,cylinder_hlen(cylinder_hlen_)
  ,cylinder_posd(cylinder_posd_)
{
}
//----------------------------------------------------------------------------

template<typename T>
cylinder3<T> capcyl3<T>::cylinder() const
{
  return cylinder3<T>(capsule.pos+capsule.dir*cylinder_posd, capsule.dir, cylinder_hlen, capsule.rad);
}
//----------------------------------------------------------------------------


//============================================================================
// oodop3_14
//============================================================================
template<typename T> const oodop3_14<T> oodop3_14<T>::s_zero(oobox3<T>::s_zero, vec4<T>::s_zero, vec4<T>::s_zero);
//----------------------------------------------------------------------------

template<typename T>
oodop3_14<T>::oodop3_14()
{
}
//----

template<typename T>
oodop3_14<T>::oodop3_14(const oobox3<T> &oobox_, const vec4<T> &diag_axes_min_, const vec4<T> &diag_axes_max_)
  :oobox(oobox_)
  ,diag_axes_min(diag_axes_min_)
  ,diag_axes_max(diag_axes_max_)
{
}
//----------------------------------------------------------------------------


//============================================================================
// bounding_capcyl_exp
//============================================================================
template<typename T>
capcyl3<T> bounding_capcyl3_exp(const vec3<T> *points_, usize_t num_points_, const seed_oobox3<T> &seed_, bool use_oobox_)
{
  // setup initial cylinder and adjust the cylinder to contain all points
  PFC_ASSERT(points_ && num_points_);
  typedef typename math<T>::scalar_t scalar_t;
  capsule3<T> cap;
  scalar_t min_area=0;
  for(unsigned aidx=0; aidx<2; ++aidx)
  {
    cylinder3<T> cyl;
    if(use_oobox_ || aidx)
    {
      // setup initial position, length and direction from oobox
      cyl.pos=seed_.oobox.pos;
      cyl.hlen=aidx?seed_.oobox.hsize.z:seed_.oobox.hsize.x;
      cyl.dir=unit((aidx?vec3<T>(0, 0, 1):vec3<T>(1, 0, 0))*seed_.oobox.rot);
    }
    else
    {
      // setup initial position, length and direction from max extreme points
      cyl.pos=(seed_.max_ext[1]+seed_.max_ext[0])*scalar_t(0.5);
      cyl.hlen=norm(seed_.max_ext[1]-seed_.max_ext[0])*scalar_t(0.5);
      cyl.dir=unit(seed_.max_ext[1]-seed_.max_ext[0]);
    }
    if(cyl.dir.z<0)
      neg(cyl.dir);
    cyl.rad=seed_.oobox.hsize.y?seed_.oobox.hsize.y:scalar_t(0.000001);
    scalar_t srad2=cyl.rad*cyl.rad;

    // expand infinite cylinder to contain all points
    const vec3<T> *p=points_, *end=points_+num_points_;
    do
    {
      // check if the point is outside the cylinder end caps
      vec3<T> v=*p-cyl.pos;
      scalar_t ed=dot(v, cyl.dir), aed=abs(ed);
      if(aed>cyl.hlen)
      {
        // adjust the cylinder to contain the old cylinder & the outside point
        cyl.pos+=cyl.dir*((ed>0?ed-cyl.hlen:ed+cyl.hlen)*scalar_t(0.5));
        cyl.hlen=aed;
      }

      // check if the point is outside the cylinder side
      vec3<T> rv=v-dot(v, cyl.dir)*cyl.dir;
      scalar_t sd2=norm2(rv);
      if(sd2>srad2)
      {
        // adjust the cylinder to contain the old cylinder & the outside point
        scalar_t sd=sqrt(sd2), old_rad=cyl.rad;
        cyl.rad=(old_rad+sd)*scalar_t(0.5*1.000001);
        srad2=cyl.rad*cyl.rad;
        cyl.pos+=rv*((cyl.rad-old_rad)/sd);
      }
    } while(++p!=end);

    // setup initial capsule with cylinder which has smallest surface area
    scalar_t ar=area(cyl);
    if(!aidx || ar<min_area)
    {
      min_area=ar;
      cap.pos=cyl.pos;
      cap.hlen=cyl.hlen;
      cap.dir=cyl.dir;
      cap.rad=cyl.rad;
    }
  }

  // expand spherical capsule caps to contain all points
  const vec3<T> *p=points_, *end=points_+num_points_;
  const vec3<T> cyl_pos=cap.pos;
  scalar_t cylinder_hlen=cap.hlen, srad2=cap.rad*cap.rad;
  cap.hlen=max(scalar_t(0), cap.hlen-cap.rad);
  do
  {
    // check if point is outside the capsule
    vec3<T> v=*p-cap.pos;
    scalar_t d=dot(v, cap.dir);
    if(norm2(v-cap.dir*clamp(d, -cap.hlen, cap.hlen))>srad2)
    {
      // adjust capsule to contain the old capsule & outside point
      scalar_t q=cap.hlen+sqrt(max(scalar_t(0), srad2-norm2(v-cap.dir*d)));
      if(d>0)
      {
        scalar_t dhlen=(d-q)*scalar_t(0.5);
        cap.hlen+=dhlen;
        cap.pos+=cap.dir*dhlen;
      }
      else
      {
        scalar_t dhlen=(-d-q)*scalar_t(0.5);
        cap.hlen+=dhlen;
        cap.pos-=cap.dir*dhlen;
      }
    }
  } while(++p!=end);

  // return the bounding capsule-cylinder
  vec3f capcyl_posd=cyl_pos-cap.pos;
  return capcyl3<T>(cap, cylinder_hlen, dot(capcyl_posd, cap.dir)<0?-norm(capcyl_posd):norm(capcyl_posd));
}
//----------------------------------------------------------------------------


//============================================================================
// bounding_capcyl_maxexp
//============================================================================
template<typename T>
capcyl3<T> bounding_capcyl3_maxexp(vec3<T> *points_, usize_t num_points_, const seed_oobox3<T> &seed_, bool use_oobox_)
{
  // setup initial cylinder and adjust the cylinder to contain all points
  PFC_ASSERT(points_ && num_points_);
  typedef typename math<T>::scalar_t scalar_t;
  capsule3<T> cap;
  scalar_t min_area=0;
  for(unsigned aidx=0; aidx<2; ++aidx)
  {
    cylinder3<T> cyl;
    if(use_oobox_ || aidx)
    {
      // setup initial position, length and direction from oobox
      cyl.pos=seed_.oobox.pos;
      cyl.hlen=aidx?seed_.oobox.hsize.z:seed_.oobox.hsize.x;
      cyl.dir=unit((aidx?vec3<T>(0, 0, 1):vec3<T>(1, 0, 0))*seed_.oobox.rot);
    }
    else
    {
      // setup initial position, length and direction from max extreme points
      cyl.pos=(seed_.max_ext[1]+seed_.max_ext[0])*scalar_t(0.5);
      cyl.hlen=norm(seed_.max_ext[1]-seed_.max_ext[0])*scalar_t(0.5);
      cyl.dir=unit(seed_.max_ext[1]-seed_.max_ext[0]);
    }
    if(cyl.dir.z<0)
      neg(cyl.dir);
    cyl.rad=seed_.oobox.hsize.y?seed_.oobox.hsize.y:scalar_t(0.000001);
    scalar_t srad2=cyl.rad*cyl.rad;

    // expand the cylinder with the point furthest from the cylinder
    vec3<T> *p=points_, *end=points_+num_points_;
    while(true)
    {
      vec3<T> *maxd_pnt=0;
      scalar_t maxd2=srad2;
      do
      {
        // check if the point is outside the cylinder end caps
        vec3<T> v=*p-cyl.pos;
        scalar_t ed=dot(v, cyl.dir), aed=abs(ed);
        if(aed>cyl.hlen)
        {
          // adjust the cylinder to contain the old cylinder & the outside point
          cyl.pos+=cyl.dir*((ed>0?ed-cyl.hlen:ed+cyl.hlen)*scalar_t(0.5));
          cyl.hlen=aed;
        }

        // check if the point is outside the cylinder side
        vec3<T> rv=v-dot(v, cyl.dir)*cyl.dir;
        scalar_t sd2=norm2(rv);
        if(sd2>srad2)
        {
          // swap point to outside point set and check for maximum distance point
          swap(*p, *--end);
          if(sd2>maxd2)
          {
            maxd2=sd2;
            maxd_pnt=end;
          }
          continue;
        }
        ++p;
      } while(p!=end);

      // check for outside points
      if(!maxd_pnt)
        break;

      // adjust the cylinder to contain the old cylinder & the outside point
      scalar_t maxd=sqrt(maxd2), old_rad=cyl.rad;
      cyl.rad=(old_rad+maxd)*scalar_t(0.5*1.000001);
      srad2=cyl.rad*cyl.rad;
      vec3<T> v=*maxd_pnt-cyl.pos;
      cyl.pos+=(v-dot(v, cyl.dir)*cyl.dir)*((cyl.rad-old_rad)/maxd);

      // remove max distance point and proceed to the next iteration
      swap(*maxd_pnt, *p);
      end=points_+num_points_;
      if(++p==end)
        break;
    }

    // setup initial capsule with cylinder which has smallest surface area
    scalar_t ar=area(cyl);
    if(!aidx || ar<min_area)
    {
      min_area=ar;
      cap.pos=cyl.pos;
      cap.hlen=cyl.hlen;
      cap.dir=cyl.dir;
      cap.rad=cyl.rad;
    }
  }

  // expand spherical capsule caps to contain all points
  vec3<T> *p=points_, *end=points_+num_points_;
  const vec3<T> cyl_pos=cap.pos;
  scalar_t cylinder_hlen=cap.hlen, srad2=cap.rad*cap.rad;
  cap.hlen=max(scalar_t(0), cap.hlen-cap.rad);
  do
  {
    // check if point is outside the capsule
    vec3<T> v=*p-cap.pos;
    scalar_t d=dot(v, cap.dir);
    if(norm2(v-cap.dir*clamp(d, -cap.hlen, cap.hlen))>srad2)
    {
      // adjust capsule to contain the old capsule & outside point
      scalar_t q=cap.hlen+sqrt(max(scalar_t(0), srad2-norm2(v-cap.dir*d)));
      if(d>0)
      {
        scalar_t dhlen=(d-q)*scalar_t(0.5);
        cap.hlen+=dhlen;
        cap.pos+=cap.dir*dhlen;
      }
      else
      {
        scalar_t dhlen=(-d-q)*scalar_t(0.5);
        cap.hlen+=dhlen;
        cap.pos-=cap.dir*dhlen;
      }
    }
  } while(++p!=end);

  // return the bounding capsule-cylinder
  vec3f capcyl_posd=cyl_pos-cap.pos;
  return capcyl3<T>(cap, cylinder_hlen, dot(capcyl_posd, cap.dir)<0?-norm(capcyl_posd):norm(capcyl_posd));
}
//----------------------------------------------------------------------------


//============================================================================
// bounding_oodop3_14
//============================================================================
template<typename T>
oodop3_14<T> bounding_oodop3_14(const vec3<T> *points_, usize_t num_points_, const oobox3<T> &oobox_)
{
  // calculate object-oriented 14-DOP
  PFC_ASSERT(!num_points_ || points_);
  oodop3_14<T> oodop;
  oodop.oobox=oobox_;
  oodop.diag_axes_min=oodop.diag_axes_max=vec4<T>::s_zero;
  if(num_points_)
  {
    // calculate min/max extremes along diagonal axes
    const vec3<T> *end=points_+num_points_;
    mat33<T> m;
    convert_u(m, oobox_.rot);
    vec3<T> a0(m.x+m.y+m.z), a1(m.x+m.y-m.z), a2(m.x-m.y+m.z), a3(m.x-m.y-m.z);
    do
    {
      vec4<T> p(dot(a0, *points_), dot(a1, *points_), dot(a2, *points_), dot(a3, *points_));
      oodop.diag_axes_min=min(oodop.diag_axes_min, p);
      oodop.diag_axes_max=max(oodop.diag_axes_max, p);
    } while(++points_!=end);

    // adjust min/max extremes
    vec4<T> d(dot(a0, oobox_.pos), dot(a1, oobox_.pos), dot(a2, oobox_.pos), dot(a3, oobox_.pos));
    oodop.diag_axes_min+=d;
    oodop.diag_axes_min*=math<T>::rsqrt3;
    oodop.diag_axes_max-=d;
    oodop.diag_axes_max*=math<T>::rsqrt3;
  }
  return oodop;
}
//----------------------------------------------------------------------------


//============================================================================
// bounding_volume_set
//============================================================================
template<typename T>
bounding_volume_set<T>::bounding_volume_set()
{
  // init bounding volumes
  sphere=sphere3<T>::s_zero;
  capcyl=capcyl3<T>::s_zero;
  oobox=oobox3<T>::s_zero;
}
//----

template<typename T>
bounding_volume_set<T>::bounding_volume_set(const vec3<T> *points_, usize_t num_points_)
{
  init(points_, num_points_);
}
//----

template<typename T>
void bounding_volume_set<T>::init(const vec3<T> *points_, usize_t num_points_)
{
  // calculate convex hull for the input points
  array<quickhull3_point<T> > in_point_arr(num_points_);
  quickhull3_point<T> *in_points=in_point_arr.data();
  for(unsigned i=0; i<num_points_; ++i)
    in_points[i].pos=points_[i];
  array<vec3<T> > orig_hull_points;
  array<uint32_t> orig_hull_triidx;
  quickhull3(in_points, num_points_, orig_hull_points, &orig_hull_triidx);
  unsigned num_hull_points=(unsigned)orig_hull_points.size();
  unsigned num_hull_tris=unsigned(orig_hull_triidx.size()/3);
  const uint32_t *hull_triidx=orig_hull_triidx.data();
  array<vec3<T> > hull_points_tmp(num_hull_points);
  vec3<T> *hull_points=hull_points_tmp.data();

  for(unsigned i=0; i<2; ++i)
  {
    // calculate seed box
    mem_copy(hull_points, orig_hull_points.data(), num_hull_points*sizeof(*hull_points));
    seed_oobox3<T> seedbox;
    switch(i)
    {
      case 0: seedbox=seed_oobox3_discrete(hull_points, num_hull_points); break;
      case 1: seedbox=seed_oobox3_cov(hull_points, num_hull_points, covariance_matrix(hull_points, hull_triidx, num_hull_tris)); break;
    }

    // calculate object-oriented box using the seed box
    oobox3<T> ob=optimize_oobox3(hull_points, num_hull_points, hull_triidx, num_hull_tris, seedbox.oobox);
    if(!i || area(ob)<area(oobox))
      oobox=ob;

    // calculate bounding sphere and capsule-cylinder using the seed box
    seed_oobox3<T> opt_seedbox=seedbox;
    opt_seedbox.oobox=ob;
    sphere3<T> s1=bounding_sphere3_exp(hull_points, num_hull_points, seedbox);
    sphere3<T> s2=bounding_sphere3_exp(hull_points, num_hull_points, seedbox, true);
    sphere3<T> s3=bounding_sphere3_exp(hull_points, num_hull_points, opt_seedbox, true);
    capcyl3<T> cc1=bounding_capcyl3_exp(hull_points, num_hull_points, seedbox);
    capcyl3<T> cc2=bounding_capcyl3_exp(hull_points, num_hull_points, seedbox, true);
    capcyl3<T> cc3=bounding_capcyl3_exp(hull_points, num_hull_points, opt_seedbox, true);
    sphere3<T> s4=bounding_sphere3_maxexp(hull_points, num_hull_points, seedbox);
    sphere3<T> s5=bounding_sphere3_maxexp(hull_points, num_hull_points, seedbox, true);
    sphere3<T> s6=bounding_sphere3_maxexp(hull_points, num_hull_points, opt_seedbox, true);
    capcyl3<T> cc4=bounding_capcyl3_maxexp(hull_points, num_hull_points, seedbox);
    capcyl3<T> cc5=bounding_capcyl3_maxexp(hull_points, num_hull_points, seedbox, true);
    capcyl3<T> cc6=bounding_capcyl3_maxexp(hull_points, num_hull_points, opt_seedbox, true);

    // choose smallest surface area sphere
    sphere3<T> s=s1.rad<s2.rad?s1:s2;
    if(s3.rad<s.rad)
      s=s3;
    if(s4.rad<s.rad)
      s=s4;
    if(s5.rad<s.rad)
      s=s5;
    if(s6.rad<s.rad)
      s=s6;
    if(!i || s.rad<sphere.rad)
      sphere=s;

    // choose smallest surface area capsule-cylinder
    scalar_t area_cc1=min(area(cc1.capsule), area(cc1.cylinder()));
    scalar_t area_cc2=min(area(cc2.capsule), area(cc2.cylinder()));
    scalar_t area_cc3=min(area(cc3.capsule), area(cc3.cylinder()));
    scalar_t area_cc4=min(area(cc4.capsule), area(cc4.cylinder()));
    scalar_t area_cc5=min(area(cc5.capsule), area(cc5.cylinder()));
    scalar_t area_cc6=min(area(cc6.capsule), area(cc6.cylinder()));
    capcyl3<T> cc;
    if(area_cc1<area_cc2 && area_cc1<area_cc3 && area_cc1<area_cc4 && area_cc1<area_cc5 && area_cc1<area_cc6)
      cc=cc1;
    else if(area_cc2<area_cc3 && area_cc2<area_cc4 && area_cc2<area_cc5 && area_cc2<area_cc6)
      cc=cc2;
    else if(area_cc3<area_cc4 && area_cc3<area_cc5 && area_cc3<area_cc6)
      cc=cc3;
    else if(area_cc4<area_cc5 && area_cc4<area_cc6)
      cc=cc4;
    else if(area_cc5<area_cc6)
      cc=cc5;
    else
      cc=cc6;
    if(!i || min(area(cc.capsule), area(cc.cylinder()))<min(area(capcyl.capsule), area(capcyl.cylinder())))
      capcyl=cc;
  }
}
//----

template<typename T>
void bounding_volume_set<T>::scale(typename math<T>::scalar_t s_)
{
  // scale bounding volume set
  sphere.rad*=s_;
  sphere.pos*=s_;
  capcyl.capsule.pos*=s_;
  capcyl.capsule.hlen*=s_;
  capcyl.capsule.rad*=s_;
  capcyl.cylinder_hlen*=s_;
  capcyl.cylinder_posd*=s_;
  oobox.pos*=s_;
  oobox.hsize*=s_;
}
//----------------------------------------------------------------------------


//============================================================================
// triangle_mesh_topology
//============================================================================
usize_t triangle_mesh_topology::num_vertices() const
{
  return m_vertices.size();
}
//----

usize_t triangle_mesh_topology::num_edges() const
{
  return m_edges.size();
}
//----

usize_t triangle_mesh_topology::num_triangles() const
{
  return m_triangles.size();
}
//----

usize_t triangle_mesh_topology::num_clusters() const
{
  return m_clusters.size();
}
//----

usize_t triangle_mesh_topology::num_cluster_tris(uint32_t cluster_idx_) const
{
  return m_clusters[cluster_idx_].num_tris;
}
//----------------------------------------------------------------------------

uint32_t triangle_mesh_topology::add_cluster()
{
  uint32_t cid=(uint32_t)m_clusters.size();
  cluster &c=m_clusters.push_back();
  c.tri_list=0xffffffff;
  c.num_tris=0;
  return cid;
}
//----

void triangle_mesh_topology::add_cluster_tri(uint32_t tri_idx_, uint32_t cluster_idx_)
{
  triangle &tri=m_triangles[tri_idx_];
  PFC_ASSERT_PEDANTIC(tri.cidx==0xffffffff);
  cluster &c=m_clusters[cluster_idx_];
  tri.cidx=cluster_idx_;
  tri.next_cluster_tri=c.tri_list;
  c.tri_list=tri_idx_;
  ++c.num_tris;
}
//----------------------------------------------------------------------------

const uint32_t *triangle_mesh_topology::tri_vidx(uint32_t tri_idx_) const
{
  return m_triangles[tri_idx_].vidx;
}
//----

const uint32_t *triangle_mesh_topology::tri_eidx(uint32_t tri_idx_) const
{
  return m_triangles[tri_idx_].eidx;
}
//----

uint32_t triangle_mesh_topology::tri_cluster(uint32_t tri_idx_) const
{
  return m_triangles[tri_idx_].cidx;
}
//----

void triangle_mesh_topology::set_tri_cluster(uint32_t tri_idx_, uint32_t cluster_idx_)
{
  m_triangles[tri_idx_].cidx=cluster_idx_;
}
//----------------------------------------------------------------------------

// Iterates through all triangles attached to the given vertex
template<class Pred>
void triangle_mesh_topology::for_each_vtx_tri(uint32_t vtx_idx_, Pred &pred_) const
{
  // iterate through all edges attached to the vertex
  uint32_t pass_id=++m_pass_id;
  const triangle *triangles_data=m_triangles.data();
  const edge *edges_data=m_edges.data();
  const vertex *vertices_data=m_vertices.data();
  uint32_t elst=vertices_data[vtx_idx_].edge_list;
  do
  {
    // iterate through all triangles attached to the edge
    uint32_t eidx=elst>>1;
    const edge &e=edges_data[eidx];
    uint32_t tlst=e.tri_list;
    do
    {
      uint32_t tidx=tlst>>2;
      const triangle &tri=triangles_data[tidx];
      if(tri.pass_id!=pass_id)
      {
        tri.pass_id=pass_id;
        pred_(tidx);
      }
      tlst=tri.next_edge_tri[tlst&3];
    } while(tlst!=0xffffffff);
    elst=e.next_vtx_edge[elst&1];
  } while(elst!=0xffffffff);
}
//----

// Iterates through all triangles attached to the given edge
template<class Pred>
void triangle_mesh_topology::for_each_edge_tri(uint32_t edge_idx_, Pred &pred_) const
{
  const triangle *triangles_data=m_triangles.data();
  const edge *edges_data=m_edges.data();
  uint32_t tlst=edges_data[edge_idx_].tri_list;
  do
  {
    uint32_t tidx=tlst>>2;
    unsigned tvidx=tlst&3;
    pred_(tidx, tvidx);
    const triangle &tri=triangles_data[tidx];
    tlst=tri.next_edge_tri[tvidx];
  } while(tlst!=0xffffffff);
}
//----

// Iterates through all triangles attached to the 3 triangle edges (excluding
// the given triangle)
template<class Pred>
void triangle_mesh_topology::for_each_tri_vtx_tri(uint32_t tri_idx_, Pred &pred_) const
{
  // process all 3 triangle vertices
  uint32_t pass_id=++m_pass_id;
  const triangle *triangles_data=m_triangles.data();
  const edge *edges_data=m_edges.data();
  const vertex *vertices_data=m_vertices.data();
  const triangle &tri=triangles_data[tri_idx_];
  tri.pass_id=pass_id;
  for(unsigned tvi=0; tvi<3; ++tvi)
  {
    // iterate through all edges attached to the vertex
    uint32_t elst=vertices_data[tri.vidx[tvi]].edge_list;
    do
    {
      // iterate through all triangles attached to the edge
      uint32_t eidx=elst>>1;
      const edge &e=edges_data[eidx];
      if(e.pass_id!=pass_id)
      {
        e.pass_id=pass_id;
        uint32_t tlst=e.tri_list;
        do
        {
          uint32_t tidx=tlst>>2;
          const triangle &tri=triangles_data[tidx];
          if(tri.pass_id!=pass_id)
          {
            tri.pass_id=pass_id;
            pred_(tidx, tlst&3, tvi);
          }
          tlst=tri.next_edge_tri[tlst&3];
        } while(tlst!=0xffffffff);
      }
      elst=e.next_vtx_edge[elst&1];
    } while(elst!=0xffffffff);
  }
}
//----

// Iterates through all triangles attached to the 3 triangle edges (excluding
// the given triangle)
template<class Pred>
void triangle_mesh_topology::for_each_tri_edge_tri(uint32_t tri_idx_, Pred &pred_) const
{
  const triangle *triangles_data=m_triangles.data();
  const edge *edges_data=m_edges.data();
  const triangle &tri=triangles_data[tri_idx_];
  for(unsigned tei=0; tei<3; ++tei)
  {
    // iterate through triangles attached to the edge
    const edge &e=edges_data[tri.eidx[tei]];
    uint32_t tlst=e.tri_list;
    do
    {
      uint32_t tidx=tlst>>2;
      if(tidx!=tri_idx_)
        pred_(tidx, tlst&3);
      const triangle &tri=triangles_data[tidx];
      tlst=tri.next_edge_tri[tlst&3];
    } while(tlst!=0xffffffff);
  }
}
//----

// Iterates through all vertices assigned to triangles in the given cluster
template<class Pred>
void triangle_mesh_topology::for_each_cluster_vtx(uint32_t cluster_idx_, Pred &pred_) const
{
  const uint32_t pass_id=++m_pass_id;
  const triangle *triangle_data=m_triangles.data();
  const vertex *vertices_data=m_vertices.data();
  uint32_t tlst=m_clusters[cluster_idx_].tri_list;
  while(tlst!=0xffffffff)
  {
    const triangle &tri=triangle_data[tlst];
    for(unsigned tvi=0; tvi<3; ++tvi)
    {
      uint32_t vidx=tri.vidx[tvi];
      const vertex &vtx=vertices_data[vidx];
      if(vtx.pass_id!=pass_id)
      {
        vtx.pass_id=pass_id;
        pred_(vidx);
      }
    }
    tlst=tri.next_cluster_tri;
  }
}
//----

// Iterates through all triangles assigned to the given cluster
template<class Pred>
void triangle_mesh_topology::for_each_cluster_tri(uint32_t cluster_idx_, Pred &pred_) const
{
  // iterate through all triangles in the cluster
  const triangle *triangle_data=m_triangles.data();
  uint32_t tlst=m_clusters[cluster_idx_].tri_list;
  while(tlst!=0xffffffff)
  {
    pred_(tlst);
    const triangle &tri=triangle_data[tlst];
    tlst=tri.next_cluster_tri;
  }
}
//----

// Iterates through all triangles that are directly or indirectly connected to
// the given triangle via edges, including the given starting triangle. This
// effectively performs flood fill on a triangle mesh.
template<class Pred>
void triangle_mesh_topology::for_each_edge_connected_cluster_tri(uint32_t start_tri_idx_, Pred &pred_) const
{
  // setup edge-connected mesh cluster traversal
  const uint32_t pass_id=++m_pass_id;
  const triangle *triangles_data=m_triangles.data();
  const triangle &start_tri=triangles_data[start_tri_idx_];
  const uint32_t cidx=start_tri.cidx;
  const edge *edges_data=m_edges.data();
  const vertex *vertices_data=m_vertices.data();
  array<uint32_t> active_cluster_edges;
  for(unsigned i=0; i<3; ++i)
  {
    edges_data[start_tri.eidx[i]].pass_id=pass_id;
    vertices_data[start_tri.vidx[i]].pass_id=pass_id;
  }

  // process active cluster edges until none left
  uint32_t num_vtx=3, num_edge=3;
  active_cluster_edges.insert_back(3, start_tri.eidx);
  do
  {
    const edge &e=edges_data[active_cluster_edges.back()];
    active_cluster_edges.pop_back();
    uint32_t tlst=e.tri_list;
    do
    {
      uint32_t tidx=tlst>>2;
      const triangle &tri=triangles_data[tidx];
      if(tri.cidx==cidx && tri.pass_id!=pass_id)
      {
        pred_(tidx);
        tri.pass_id=pass_id;
        for(unsigned tvei=0; tvei<3; ++tvei)
        {
          const edge &e=edges_data[tri.eidx[i]];
          if(e.pass_id!=pass_id)
          {
            e.pass_id=pass_id;
            active_cluster_edges.push_back(tri.eidx[tvei]);
            ++num_edge;
          }
          const vertex &vtx=vertices_data[tri.vidx[tvei]];
          if(vtx.pass_id!=pass_id)
          {
            vtx.pass_id=pass_id;
            ++num_vtx;
          }
        }
      }
      tlst=tri.next_edge_tri[tlst&3];
    } while(tlst!=0xffffffff);
  } while(active_cluster_edges.size());
}
//----------------------------------------------------------------------------
