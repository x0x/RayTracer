#include "hittable.h"
#include "ray.h"
#include "vec3.h"

class Sphere : public Hittable {
private:
  Point centre_;
  double radius_;

public:
  Sphere(Point centre, double radius) : centre_(centre), radius_(radius){};

  bool hit(const Ray &r, double t_min, double t_max,
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

    if (root <= t_min || root >= t_max) {
      root = (-1 * b + sqrt(discriminant)) / (2.0 * a);
      if (root < t_min || root > t_max) {
        return false;
      }
    }

    record.param_ = root;
    record.point_ = r.pointAtParam(record.param_);
    record.normal_ = unit_vector((record.point_ - centre_) / radius_);
    record.setFrontFace(r , record.normal_);
    return true;
  }
};