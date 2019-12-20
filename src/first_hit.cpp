#include "first_hit.h"
#include <limits>

bool first_hit(
  const Ray & ray,
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id,
  double & t,
  Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  bool hit = false;                                   // return value

  // Make some temp variables before iterating through objects
  double _t;
  Eigen::Vector3d _n;
  Eigen::Vector3d normal;
  int _hit_id;
  double min_distance = std::numeric_limits<double>::infinity();

  for (int i = 0; i < objects.size(); i++) {
    if (objects[i]->intersect(ray, min_t, _t, _n)) {
      // Then we have an intersection of ray and object i
      // Check the distance and update if the distance is smaller
      if (_t < min_distance) {
        min_distance = _t;
        normal = _n;
        _hit_id = i;
        hit = true;
      }
    }
  }

  if (hit) {
    t = min_distance;
    n = normal;
    hit_id = _hit_id;
  }

  return hit;
  ////////////////////////////////////////////////////////////////////////////
}
