#ifndef BVH_H
#define BVH_H

//Header File for BVH Class
class bvh : public geometry {
  public:
    //Constructors
    bvh();
    //This is to create the leaf nodes
    bvh(std::vector <geometry*> geo, int num_geo);
    //Destructors
    ~bvh();
    //Geometry Functions
    bool hit(ray &casted_ray, double t_min, double t_max, hit_record &rec) const override;
    vec get_normal_vector(point &point_on_sphere) const override;
    material * get_material() const override;
    aabb get_bounding_box() const override;
    //Member Variables
    geometry *left;
    geometry *right;
    aabb box;
};
#endif
