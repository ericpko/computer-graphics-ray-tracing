#include "Plane.h"
#include "Ray.h"
#include <iostream>
bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  bool hit = false;

  // Set up some vectors to represent the plane and line
  Eigen::Vector3d P = Plane::point;                   // A specific point
  Eigen::Vector3d e = ray.origin;
  Eigen::Vector3d v = ray.direction;

  /**
   * First check if the direction of the line is perpendicular to the normal of
   * the plane. If this is the case, then the line does not inersect with plane
   */
  if (v.dot(Plane::normal) == 0) {
    return false;
  }

  // If we make it here, then we know that the ray intersects the plane at some
  // point t
  t = (Plane::normal.dot(P - e)) / (Plane::normal.dot(v)); // See ipad for calc
  if (t >= min_t) {
    n = Plane::normal;
    hit = true;
  }

  return hit;
  ////////////////////////////////////////////////////////////////////////////
}
