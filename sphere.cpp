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
sphere::sphere(point sphere_center, float sphere_radius, material *geo_material) {
  this->center = sphere_center;
  this->radius = sphere_radius;
  this->geo_material = geo_material;
  float r = this->radius;
  vec radius_vec = vec(r,r,r);
  this->bounding_box = aabb(this->center-radius_vec,this->center+radius_vec);
}

/*
Sphere Hit Function
@param casted_ray: ray casted into the scene
@param t_min & t_max: max and min t values for parametric hit
@param rec: record to store a hit
@return true or false on hit
*/
bool sphere::hit(ray &casted_ray, double t_min, double t_max, hit_record &rec) const {
  vec ac = casted_ray.origin-this->center;
  float a = casted_ray.direction.dot(casted_ray.direction);
  float b = 2*casted_ray.direction.dot(ac);
  float c = ac.dot(ac) - (this->radius*this->radius);
  float discriminant = (b*b)-(4*a*c);
  if (discriminant > 0.0)  {
    float t = ((-b-sqrt(discriminant))/(2*a));
    if (t <= t_min || t > t_max) {
      t = ((-b+sqrt(discriminant))/(2*a));
      if (t <= t_min || t > t_max) {
        return false;
      }
    }
    rec.t = t;
    rec.hit_point = casted_ray.get_point_at(t);
    rec.normal = this->get_normal_vector(rec.hit_point);
    rec.geo_material = this->get_material();
    return true;
  }
  return false;
}

/*
Getting the Normal Vector of the Point on the Sphere
@param point_on_sphere: point to get normal vector at
@return: normal vector (as unit)
*/
vec sphere::get_normal_vector(point &point_on_sphere) const {
  vec normal = (point_on_sphere-this->center)/this->radius;
  return normal;
}

/*
@return the material of the sphere
*/
material * sphere::get_material() const {
  return this->geo_material;
}

//return bounding box of sphere
aabb sphere::get_bounding_box() const {
  return this->bounding_box;
}

//not used
geometry * sphere::get_left() const {
  return NULL;
}

//not used
geometry * sphere::get_right() const {
  return NULL;
}

//not used
bool sphere::is_leaf() const {
  return false;
}

//not used
std::vector<geometry*> sphere::get_geo() const {
  std::vector<geometry*> empty_list;
  return empty_list;
}
