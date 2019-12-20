#include "PointLight.h"

void PointLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  ////////////////////////////////////////////////////////////////////////////
  d = (this->p - q);        // p is the light point, q is the intersection point
  max_t = d.norm();         // length of d

  d = d.normalized();
  ////////////////////////////////////////////////////////////////////////////
}
