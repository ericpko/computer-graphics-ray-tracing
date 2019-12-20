#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"

bool raycolor(
  const Ray & ray,
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  ////////////////////////////////////////////////////////////////////////////
  // num_recursive_calls starts at 0. Check if we have passed our limit
  if (num_recursive_calls > 4) {
    return false;
  }

  // Initialize variables
  rgb = Eigen::Vector3d(0, 0, 0);                   // Initialize/reset to black
  Eigen::Vector3d n;
  double t;
  int hit_id;

  // Check if we hit an object. If not, then return false
  if (!first_hit(ray, min_t, objects, hit_id, t, n)) {
    return false;
  }

  // If we've made it here, then the viewing ray has intersected an object (hit)
  // Now we evaluate the shading model and set pixel to that color
  rgb = blinn_phong_shading(ray, hit_id, t, n, objects, lights);

  /**
   * Now we add ideal specular reflection/mirror reflection (pg 87)
   * We need to set up a new mirror ray (mray)
   */
  Ray mray;
  // Get the real intersection point <P> of intersection between the
  // viewing ray and the surface
  Eigen::Vector3d e = ray.origin;
  Eigen::Vector3d d = ray.direction;
  mray.origin = e + t * d;                        // real intersection point <P>
  mray.direction = reflect(d.normalized(), n);    // reflection direction <r>

  /**
   * Now we recursively add to our rgb pixel color.
   * s = 1.0e-5 is our fudge factor to move off the surface
   * (min_t for first_hit)
   */
  Eigen::Vector3d mrgb;                           // mirror rgb pixel
  if (raycolor(mray, 1.0e-6, objects, lights, num_recursive_calls + 1, mrgb)) {
    // Then we can update the rgb value. Component-wise multiplication
    rgb += (objects[hit_id]->material->km.array() * mrgb.array()).matrix();
  }


  return true;
  ////////////////////////////////////////////////////////////////////////////
}
