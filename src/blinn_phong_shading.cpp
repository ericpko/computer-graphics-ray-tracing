#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id,
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  ////////////////////////////////////////////////////////////////////////////
  // Initialize variables for the diffuse, specular, and ambient coeffients'
  // for readability
  Eigen::Vector3d kd = objects[hit_id]->material->kd;
  Eigen::Vector3d ks = objects[hit_id]->material->ks;
  Eigen::Vector3d ka = objects[hit_id]->material->ka;

  // Initialize pixel color with intensity of ambient light <I_a>
  Eigen::Vector3d rgb(0.1, 0.1, 0.1);
  // Add the ambient component to pixel
  rgb = (ka.array() * rgb.array()).matrix();                  // component-wise

  // Set up some vectors for readability and notation
  Eigen::Vector3d e = ray.origin;
  Eigen::Vector3d d = ray.direction;
  Eigen::Vector3d v, l, h;
  double phong_exponent = objects[hit_id]->material->phong_exponent;
  // Find the point <P> of intersection between the viewing ray and the surface
  Eigen::Vector3d P = e + t * d;
  Ray sray;                                                 // shadow ray
  sray.origin = P;

  /**
   * We are going to iterate through every light and calculate all the
   * vectors needed required to set the pixel color. Since light obeys the
   * superposition principle, we sum all the light, then clip if required.
   */
  v = (P + -d).normalized(); // v only depends on the viewing ray (not on the light source)
  for (int i = 0; i < lights.size(); i++) {
    // For each light, find vectors l, and h, and set the shadow ray direction
    double max_t;
    lights[i]->direction(P, l, max_t);
    sray.direction = l;
    // l = l.normalized();            // the light's direction method normalizes

    /**
     * Now we need to check if we are in the a shadow.
     * i.e. can we see the light source from point <P>?
     */
    // We don't want to modify hit_id, t, or n since they are called from raycolor
    int s_hit_id;
    double s_t;
    Eigen::Vector3d s_n;
    if (!first_hit(sray, 1.0e-6, objects, s_hit_id, s_t, s_n) || s_t >= max_t) {
      // Then we are not in the shadow, so we can add the diffuse and specular components
      /**
       * NOTE: DO NOT forget the || s_t >= max_t because we might hit an object,
       * but that object might be above the light source, so we still want that
       * light. Without that <or> all our images are all dimmer!!
       * Remember that max(0, n dot l) is the theta angle component, and
       * that the Phong exponent <p> controls the shininess of the surface (pg 83).
       */
      h = (v + l).normalized(); // only need to compute h if we're not in a shadow
      // h = (-d.normalized() + l).normalized();
      // Add the diffuse component (Lambertian shading) to the pixel color
      rgb += (kd.array() * lights[i]->I.array()).matrix() * std::fmax(0.0, n.dot(l));
      // Add the specular component (Blinn-Phong shading) to the pixel color
      rgb += (ks.array() * lights[i]->I.array()).matrix() * std::pow(std::fmax(0.0, n.dot(h)), phong_exponent);
    }
  }

  /**
   * After suming all the light sources, we might need to clip/clamp the
   * rgb values, but since this is done in main.cpp, we don't need to do it
   * here.
   */

  return rgb;   // no matter what, the pixel is set to the ambient color
  ////////////////////////////////////////////////////////////////////////////
}
