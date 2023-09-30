#pragma once

#include "hittable.h"

class Sphere : public Hittable { 
private:
  Point centre_;
  double radius_;
  std::shared_ptr<Material> material_;

public:
  Sphere(Point centre, double radius, std::shared_ptr<Material> material) : centre_(centre), radius_(radius),
   material_(material){};

  bool hit(const Ray &r, Interval param_interval,
           HitRecord &record) const override {

    Vec3 centre_to_origin_vec = r.origin() - centre_;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(r.direction(), centre_to_origin_vec);
    auto c =
        dot(centre_to_origin_vec, centre_to_origin_vec) - radius_ * radius_;

    auto discriminant = b * b - 4.0 * a * c;

    if (discriminant < 0) {
      return false;
    }

    auto root = (-1 * b - sqrt(discriminant)) / (2.0 * a);

    if (!param_interval.Surrounds(root)) {
      root = (-1 * b + sqrt(discriminant)) / (2.0 * a);
      if (!param_interval.Surrounds(root)) {
        return false;
      }
    }
    

    record.param_ = root;
    record.point_ = r.pointAtParam(record.param_);
    record.normal_ = UnitVector((record.point_ - centre_) / radius_);
    record.setFrontFace(r , record.normal_);
    record.material_ = material_; 
    return true;
  }
};