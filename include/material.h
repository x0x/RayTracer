#pragma once

#include "vec3.h"
class HitRecord;

class Material {
public:
  virtual ~Material() = default;

  virtual bool Scatter(const Ray &ray, const HitRecord &hit_record,
                       Color &attenuation, Ray &scattered) const = 0;
};

class Lambertian : public Material {
private:
  Color albedo_;

public:
  Lambertian(const Color &color) : albedo_(color) {}
  bool Scatter(const Ray &ray_in, const HitRecord &hit_record,
               Color &attenuation, Ray &scattered) const override {
    auto scatter_direction = hit_record.normal_ + RandomUnitVector();

    if (scatter_direction.near_zero())
      scatter_direction = hit_record.normal_;

    scattered = Ray(hit_record.point_, scatter_direction);
    attenuation = albedo_;
    return true;
  }
};

class Metal : public Material {
private:
  Color albedo_;
  double fuzz_;
public:
  Metal(const Color &a, double fuzz) : albedo_(a), fuzz_(fuzz < 1 ? fuzz : 1) {}

  bool Scatter(const Ray &ray_in, const HitRecord &hit_record,
               Color &attenuation, Ray &scattered) const override {
    auto reflected =
        reflect(UnitVector(ray_in.direction()), hit_record.normal_);
    auto direction = reflected + fuzz_*RandomUnitVector();
    scattered = Ray(hit_record.point_, direction); 
    attenuation = albedo_;
    return (dot(direction,hit_record.normal_) > 0);
  }
};
