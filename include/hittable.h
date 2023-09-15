#pragma once
#include "interval.h"
#include "ray.h"
#include "vec3.h"

class HitRecord {
public:
  Point point_;
  Vec3 normal_;
  double param_;
  bool front_face_;

  void setFrontFace(const Ray &r, const Vec3 &normal) {
    front_face_ = dot(r.direction(), normal) < 0.0;
  }
};

class Hittable {
public:
  virtual ~Hittable() = default;

  virtual bool hit(const Ray &r, Interval t_interval, HitRecord &rec) const = 0;
};
