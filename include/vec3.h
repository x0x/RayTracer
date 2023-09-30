#pragma once

#include "utility.h"
#include <cmath>
#include <iostream>

using std::sqrt;

class Vec3 {
public:
  Vec3() : e{0, 0, 0} {}
  Vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

  double x() const { return e[0]; }
  double y() const { return e[1]; }
  double z() const { return e[2]; }

  Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
  double operator[](int idx) const { return e[idx]; }

  bool near_zero() const {
          auto s = 1e-8;
          return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
  }

  static Vec3 Random() {
    return Vec3(RandomDouble(), RandomDouble(), RandomDouble());
  }

  static Vec3 Random(double min, double max) {
    return Vec3(RandomDouble(min, max), RandomDouble(min, max),
                RandomDouble(min, max));
  }

  Vec3 &operator+=(const Vec3 &v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
  }

  Vec3 &operator*=(const double t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
  }

  Vec3 &operator/=(const double t) {
    e[0] /= t * 1.0;
    e[1] /= t * 1.0;
    e[2] /= t * 1.0;
    return *this;
  }

  double LengthSquared() const {
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
  }

  double Length() const { return sqrt(LengthSquared()); }

public:
  double e[3];
};

using Point = Vec3;
using Color = Vec3;

inline std::ostream &operator<<(std::ostream &out, const Vec3 &v) {
  return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline Vec3 operator+(const Vec3 &u, const Vec3 &v) {
  return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline Vec3 operator-(const Vec3 &u, const Vec3 &v) {
  return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline Vec3 operator*(const Vec3 &u, const Vec3 &v) {
  return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline Vec3 operator*(double t, const Vec3 &v) {
  return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline Vec3 operator*(const Vec3 &v, double t) { return t * v; }

inline Vec3 operator/(Vec3 v, double t) { return (1 / t) * v; }

inline double dot(const Vec3 &u, const Vec3 &v) {
  return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline Vec3 cross(const Vec3 &u, const Vec3 &v) {
  return Vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
              u.e[2] * v.e[0] - u.e[0] * v.e[2],
              u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline Vec3 UnitVector(Vec3 v) { return v / v.Length(); }

inline Vec3 RandomInUnitSphere() {
  while (true) {
    auto p = Vec3::Random(-1, 1);
    if (p.LengthSquared() < 1)
      return p;
  }
}

inline Vec3 RandomUnitVector() {
    return UnitVector(RandomInUnitSphere());
}

inline Vec3 RandomOnHemisphere(const Vec3& normal) {
    Vec3 on_unit_sphere = RandomUnitVector();
    if (dot(on_unit_sphere, normal) > 0.0) 
        return on_unit_sphere;
    else
        return -on_unit_sphere;
}


Vec3 reflect(const Vec3& v, const Vec3& n) {
    return v - 2*dot(v,n)*n;
}
