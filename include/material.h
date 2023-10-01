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
        Reflect(UnitVector(ray_in.direction()), hit_record.normal_);
    auto direction = reflected + fuzz_ * RandomUnitVector();
    scattered = Ray(hit_record.point_, direction);
    attenuation = albedo_;
    return (dot(direction, hit_record.normal_) > 0);
  }
};

class Dielectric : public Material {
private:
  double refractiveIndex_;

public:
  Dielectric(double refractiveIndex) : refractiveIndex_(refractiveIndex) {}

  bool Scatter(const Ray &ray_in, const HitRecord &hit_record,
               Color &attenuation, Ray &scattered) const override {
    attenuation = Color(1.0, 1.0, 1.0);
    double refractiveIndexRatio =
        hit_record.front_face_ ? (1.0 / refractiveIndex_) : refractiveIndex_;

    Vec3 directionUnitVec = UnitVector(ray_in.direction());
    double cosineTheta = fmin(dot(-directionUnitVec, hit_record.normal_), 1.0);
    double sinTheta = sqrt(1.0 - cosineTheta * cosineTheta);

    bool isTotalInternalReflection = refractiveIndexRatio * sinTheta > 1.0;

    Vec3 scatteredDirection;

    if (isTotalInternalReflection) {
      scatteredDirection = Reflect(directionUnitVec, hit_record.normal_);
    } else {
      scatteredDirection =
          Refract(directionUnitVec, hit_record.normal_, refractiveIndexRatio);
    }
    scattered = Ray(hit_record.point_, scatteredDirection);
    return true;
  }
};