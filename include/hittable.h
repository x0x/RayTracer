#pragma once
#include "ray.h"
#include <memory>

class Material;

class HitRecord {
public:
  Point point_;
  Vec3 normal_;
  double param_;
  bool front_face_;
  std::shared_ptr<Material> material_;

  void setFrontFace(const Ray &r, const Vec3& outward_normal) {
    front_face_ = dot(r.direction(), outward_normal) < 0.0;
    normal_ = front_face_ ? outward_normal : -outward_normal;
  }
};

class Hittable {
public:
  virtual ~Hittable() = default;

  virtual bool hit(const Ray &r, Interval t_interval, HitRecord &rec) const = 0;
};
