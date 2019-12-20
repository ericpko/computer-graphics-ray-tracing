#include "Sphere.h"
#include "Ray.h"

bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  bool hit = false;                             // return flag

  Eigen::Vector3d c = Sphere::center;
  Eigen::Vector3d d = ray.direction;
  Eigen::Vector3d e = ray.origin;

  double A = d.dot(d);
  double B = 2 * d.dot(e - c);
  double C = (e - c).dot(e - c) - pow(Sphere::radius, 2.0);

  double discriminant = pow(B, 2.0) - (4 * A * C);
  if (discriminant < 0) {
    // Then there is no solution
    return false;

  } else if (discriminant == 0) {
    // Then there is one solution
    t = -B / (2 * A);
    if (t >= min_t) {
      // The normal vector is the gradient of the sphere (pg 77) n = (p - c) / r
      n = ((e + t * d) - c) / radius;
      hit = true;
    }

  } else if (discriminant > 0) {
    // Then there are two solutions. First calculate t
    double t_plus = (-B + sqrt(discriminant)) / (2 * A);
    double t_minus = (-B - sqrt(discriminant)) / (2 * A);
    double t_min = fmin(t_plus, t_minus);
    double t_max = fmax(t_plus, t_minus);
    if (t_min >= min_t) {
      t = t_min;
      hit = true;
    } else if (t_max >= min_t) {
      t = t_max;
      hit = true;
    }

    // Calculate the norm at the closest point of intersection
    n = ((e + t * d) - c) / radius;       // or just normalize the vector
  }

  return hit;
  ////////////////////////////////////////////////////////////////////////////
}
