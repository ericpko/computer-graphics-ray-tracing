#include "Triangle.h"
#include "Ray.h"
#include <Eigen/Geometry>
#include <iostream>

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  /**
   * NOTE: The following solution is found on page 79 in the textbook.
   */
  bool hit = false;

  // Set up some variables
  Eigen::Vector3d P = std::get<0>(Triangle::corners);       // Point P
  Eigen::Vector3d Q = std::get<1>(Triangle::corners);       // Point Q
  Eigen::Vector3d R = std::get<2>(Triangle::corners);       // Point R
  Eigen::Vector3d PQ = Q - P;                               // direction vector
  Eigen::Vector3d PR = R - P;                               // direction vector
  Eigen::Vector3d v = ray.direction;
  Eigen::Vector3d O = ray.origin;

  // Get the normal of the two vectors in the plane of the triangle
  Eigen::Vector3d normal = PQ.cross(PR);

  // Check if the ray intersects with the plane made by the triangle
  if (v.dot(normal) == 0) {
    return false;
  }

  // If we make it here, then we know that the ray intersects the plane at some
  // point t
  t = (normal.dot(P - O)) / (normal.dot(v));
  if (t < min_t) {
    return false;
  }

  /**
   * Now we need to check if the intersection point is in the triangle
   */
  // Eigen::Matrix3d A;
  // A << -PQ, -PR, v;
  // Eigen::Vector3d y = P - O;           // Ax = y, where x = <beta, gamma, t>

  // Set up the columns of matrix A
  // Column vector (P - Q)
  double a = -PQ[0];
  double b = -PQ[1];
  double c = -PQ[2];
  // Column vector (P - R)
  double d = -PR[0];
  double e = -PR[1];
  double f = -PR[2];
  // Column vector d (direction vector of ray)
  double g = v[0];
  double h = v[1];
  double i = v[2];

  // Column vector y                      Ax = y
  double j = P[0] - O[0];
  double k = P[1] - O[1];
  double l = P[2] - O[2];

  /**
   * Rather than use A.determinant(), we can reduce the number of operations
   * by reusing numbers.
   * double M = A.determinant();
   */
  double ei_minus_hf = e * i - h * f;
  double gf_minus_di = g * f - d * i;
  double dh_minus_eg = d * h - e * g;

  double ak_minus_jb = a * k - j * b;
  double jc_minus_al = j * c - a * l;
  double bl_minus_kc = b * l - k * c;

  // Get the determinant of A
  double M = a * ei_minus_hf + b * gf_minus_di + c * dh_minus_eg;

  // Solve for the values of x = <beta, gamma, t> in the system Ax = y
  double beta = (j * ei_minus_hf + k * gf_minus_di + l * dh_minus_eg) / M;
  double gamma = (i * ak_minus_jb + h * jc_minus_al + g * bl_minus_kc) / M;
  // double t_prime = -((f * ak_minus_jb + e * jc_minus_al + d * bl_minus_kc) / M);
  // assert(t == t_prime);                  // works properly

  if (beta >= 0 && gamma >= 0 && (beta + gamma) <= 1) {
    n = normal.normalized();
    hit = true;
  }

  return hit;
  ////////////////////////////////////////////////////////////////////////////
}
