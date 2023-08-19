#pragma once

#include "hittable.h"
#include <memory>
#include <vector>

class HittableList : public Hittable {
public:
  std::vector<std::shared_ptr<Hittable>> objects;

  HittableList() {}

  HittableList(std::shared_ptr<Hittable> object) {
    objects.emplace_back(object);
  }

  void clear() { objects.clear(); }

  void add(std::shared_ptr<Hittable> object) { objects.emplace_back(object); }

  bool hit(const Ray &r, double tMin, double tMax,
           HitRecord &rec) const override {
    HitRecord closest_rec;
    bool did_hit = false;
    auto closest_param = tMax;

    for (const auto &object : objects) {
      if (object->hit(r, tMin, closest_param, closest_rec)) {
        did_hit = true;
        rec = closest_rec;
        closest_param = closest_rec.param_;
      }
    }

    return did_hit;
  }
};