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
  auto material_ground = make_shared<Lambertian>(Color(0.2, 0.1, 0.9));
  auto material_center = make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
  auto material_left = make_shared<Metal>(Color(1,0,0),0);
  auto material_right = make_shared<Metal>(Color(0.33, 0.12, 0.01), 1.0);

  world.add(
      make_shared<Sphere>(Point(0.0, -100.5, -1.0), 100.0, material_ground));
  world.add(make_shared<Sphere>(Point(0.0, 0.0, -1.0), 0.5, material_center));
  world.add(make_shared<Sphere>(Point(-1.0, 0.0, -1.0), 0.5, material_left));
  world.add(make_shared<Sphere>(Point(-1.0, 0.0, -1.0), -0.4, material_left));
  world.add(make_shared<Sphere>(Point(1.0, 0.0, -1.0), 0.5, material_right));

  Camera camera;
  camera.aspect_ratio_ = 1; 
  camera.image_width_ = 800;
  camera.samples_per_pixel_ = 200;
  camera.max_depth_ = 8;
  camera.fov_ = 80;      // vertical field of view in degrees

  camera.lookFrom_ = Point(0,0,0);
  camera.lookAt_ = Point(0,0,-1);
  camera.Render(world);
}
