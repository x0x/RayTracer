#include "../include/color.h"
#include "../include/constants.h"
#include "../include/hittable.h"
#include "../include/hittable_list.h"
#include "../include/ray.h"
#include "../include/sphere.h"
#include "../include/vec3.h"
#include "../include/camera.h"
#include <iostream>

using std::make_shared;
using std::shared_ptr;

int main() {

  // add objects in world
  HittableList world;
  world.add(make_shared<Sphere>(Point(0, 0, -1), 0.5));
  world.add(make_shared<Sphere>(Point(0, -100.5, -1), 100));

  Camera camera;

  camera.aspect_ratio = 16.0/9.0;
  camera.image_width = 1020;

  camera.render(world);
}
