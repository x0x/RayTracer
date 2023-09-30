#pragma once

#include "hittable.h"

class HittableList : public Hittable {
public:
  std::vector<std::shared_ptr<Hittable>> objects;

public:
  HittableList() {}

  HittableList(std::shared_ptr<Hittable> object) {
    objects.emplace_back(object);
  }

  void clear() { objects.clear(); }

  void add(std::shared_ptr<Hittable> object) { objects.emplace_back(object); }

  bool hit(const Ray &r, Interval param_interval,
           HitRecord &rec) const override {
    HitRecord closest_rec;
    bool did_hit = false;
    auto closest_param = param_interval.max_;

    for (const auto &object : objects) {
      if (object->hit(r, Interval(param_interval.min_, closest_param) , closest_rec)) {
        did_hit = true;
        rec = closest_rec;
        closest_param = closest_rec.param_;
      }
    }

    return did_hit;
  }
};