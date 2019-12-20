#include "viewing_ray.h"

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{
  ////////////////////////////////////////////////////////////////////////////
  // NOTE: The camera width and height is the dimensions of the camera frame.

  // Get the scalar (weights) for the uvw coordinates
  double u = -(camera.width / 2.0) + (camera.width * (j + 0.5) / width);
  double v = (camera.height / 2.0) - (camera.height * (i + 0.5) / height);
  double w = -camera.d;

  // Find the point <P> of (i, j) in the uvw camera frame coordinates
  // This is a projection onto the image plane
  Eigen::Vector3d P = camera.e + u * camera.u + v * camera.v + w * camera.w;

  // Set the viewing ray origin and direction
  ray.origin = camera.e;
  ray.direction = P - camera.e;
  ////////////////////////////////////////////////////////////////////////////
}
