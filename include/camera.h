#pragma once

#include "color.h"
#include "hittable.h"
#include "vec3.h"
#include "constants.h"

class Camera {
public:
  double aspect_ratio;
  int image_width;

  void render(const Hittable &world) {

    initialise();

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; j--) {
      std::cerr << "\rScanlines remaining: " << j << std::flush;
      for (int i = 0; i < image_width; i++) {

        auto pixel_center_point =
            pixel_00_point + i * delta_x_vec + j * delta_y_vec;
        auto ray_direction_vec = pixel_center_point - camera_position;

        Ray r = Ray(camera_position, ray_direction_vec);
        Color pixel_Color = Ray_Color(r, world);
        writeColor(std::cout, pixel_Color);
      }
    }
    std::cerr << "\nDone.\n";
  }

private:
  int image_height;
  Point camera_position;
  Vec3 delta_x_vec;
  Vec3 delta_y_vec;
  Vec3 pixel_00_point;

  void initialise() {
    image_height = static_cast<int>(image_width / aspect_ratio);
    camera_position = Vec3(0, 0, 0);

    auto focal_length = 1.0;
    auto viewport_height = 1.5;
    auto viewport_width =
        viewport_height * (static_cast<double>(image_width / image_height));

    auto viewport_x_vec = Vec3(viewport_width, 0, 0);
    auto viewport_y_vec = Vec3(0, -viewport_height, 0);

    delta_x_vec = viewport_x_vec / image_width;
    delta_y_vec = viewport_y_vec / image_height;

    auto viewport_upper_left_point = camera_position - viewport_x_vec / 2.0 -
                                     viewport_y_vec / 2.0 -
                                     Vec3(0, 0, focal_length);

    pixel_00_point =
        viewport_upper_left_point + (delta_x_vec / 2.0) + (delta_y_vec / 2.0);
  }

  Color Ray_Color(const Ray &r, const Hittable &world) {

    HitRecord rec;
    if (world.hit(r, Interval(0, infinity), rec)) {
      return 0.5 * (rec.normal_ + Color(1, 1, 1));
    };

    Vec3 unitVector = unit_vector(r.direction());
    auto temp = 0.5 * (unitVector.y() + 1.0);
    return (1 - temp) * Color(1, 1, 1) + temp * Color(0.5, 0.7, 1);
  }
};