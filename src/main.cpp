#include "../include/camera.h"
#include "../include/color.h"
#include "../include/constants.h"
#include "../include/hittable.h"
#include "../include/hittable_list.h"
#include "../include/material.h"
#include "../include/ray.h"
#include "../include/sphere.h"
#include "../include/vec3.h"

#include <iostream>
#include <memory>

using std::make_shared;
using std::shared_ptr;

int main() {

  HittableList world;
  auto material_ground = make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
  auto material_center = make_shared<Lambertian>(Color(0.5, 0.9, 0.5));
  auto material_right = make_shared<Metal>(Color(0.8, 0.6, 0.2),0.4);
  auto material_left   = make_shared<Metal>(Color(0.8, 0.8, 0.8),0);

  world.add(
      make_shared<Sphere>(Point(0.0, -100.5, -1.0), 100.0, material_ground));
  world.add(make_shared<Sphere>(Point(0.0, 0.0, -1.0), 0.5, material_center));
  world.add(make_shared<Sphere>(Point(-1.0, 0.0, -1.0), 0.5, material_right));
  world.add(make_shared<Sphere>(Point(1.0, 0.0, -1.0), 0.5, material_left));

  Camera camera;
  camera.aspect_ratio_ = 1.0;
  camera.image_width_ = 1024;
  camera.samples_per_pixel_ = 500;
  camera.max_depth_ = 20;
  camera.Render(world);
}
