#pragma once
#include "vec3.h"

class Ray {
private:
  Vec3 A;
  Vec3 B;

public:
  Ray() {}
  Ray(const Vec3 &a, const Vec3 &b) {
    A = a;
    B = b;
  }
  Vec3 origin() const { return A; }
  Vec3 direction() const { return B; }
  Vec3 pointAtParam(double t) const { return A + t * B; }
};