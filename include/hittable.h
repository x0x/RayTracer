#include "ray.h"
#include "vec3.h"

#pragma once

class hitRecord {
public:
  point3 p;
  vec3 normal;
  double t;
};

class hittable {
public:
  virtual ~hittable() = default;

  virtual bool hit(const ray &r, double tMin, double tMax,
                   hitRecord &rec) const = 0;
};
