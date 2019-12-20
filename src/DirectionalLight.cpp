#include "DirectionalLight.h"
#include <limits>

void DirectionalLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Set the direction of d
  d = (-this->d).normalized();
  // d = (-DirectionalLight::d).normalized();
  max_t = std::numeric_limits<double>::infinity();
  ////////////////////////////////////////////////////////////////////////////
}


/**
 * NOTE: In the Light's direction method, we MUST normalize d. This caused
 * massive bug that took ~6 hours to finally realize because everything
 * worked fine except for Triangle Soup's bunny image was significantly
 * darker.
 * Must normalize d in PointLight's direction method as well, and in
 * reflect.cpp
 */
