#include "sphere.h"
#include <cmath>
//Sphere Class

//Default Constructor
sphere::sphere() {}

/*
Specific Constructor:
@param sphere_center: center of the sphere_center
@param sphere_radius: float radius of the sphere
@param geo_base_color: base color of the geometry
*/
sphere::sphere(point sphere_center, float sphere_radius, color geo_base_color) {
  this->center = sphere_center;
  this->radius = sphere_radius;
  this->base_color = geo_base_color;
  float r = this->radius;
  vec radius_vec = vec(r,r,r);
  this->bb = aabb(this->center-radius_vec,this->center+radius_vec);
}

/*
Hit Function for Sphere:
@param casted_ray: ray casted at geometry
@return: -1 for no hit, and t (parametric value on ray) for a hit
*/
bool sphere::hit(ray &casted_ray, double t_min, double t_max, hit_record &rec) const {
  vec ac = casted_ray.origin-this->center;
  float a = casted_ray.direction.dot(casted_ray.direction);
  float b = 2*casted_ray.direction.dot(ac);
  float c = ac.dot(ac) - (this->radius*this->radius);
  float discriminant = (b*b)-(4*a*c);
  float t = 0.0;
  if (discriminant > 0.0)  {
    rec.t = ((-b-sqrt(discriminant))/(2*a));
    rec.object = this;
    return true;
  }
  return false;
}

/*
Getting the Normal Vector of the Point on the Sphere
@param point_on_sphere: point to get normal vector at
@return: normal vector
*/
vec sphere::get_normal_vector(point &point_on_sphere) const {
  return point_on_sphere-this->center;
}

/*
@return the base color of the sphere
*/
color sphere::get_base_color() const {
  return this->base_color;
}

aabb sphere::bounding_box() const {
  return this->bb;
}
