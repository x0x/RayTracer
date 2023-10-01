
#include "color.h"
#include "constants.h"
#include "hittable.h"
#include "material.h"
#include "utility.h"
#include "vec3.h"

class Camera {
public:
  double aspect_ratio_;
  int image_width_;
  int samples_per_pixel_;
  int max_depth_;

private:
  int image_height_;
  Point camera_position_;
  Vec3 delta_x_vec_;
  Vec3 delta_y_vec_;
  Vec3 pixel_00_point_;

public:
  void Render(const Hittable &world) {

    Initialise();

    std::cout << "P3\n" << image_width_ << " " << image_height_ << "\n255\n";

    for (int j = image_height_ - 1; j >= 0; j--) {
      std::cerr << "\rScanlines remaining: " << j << std::flush;
      for (int i = 0; i < image_width_; i++) {
        Color pixel_color = Color(0, 0, 0);

        for (int sample = 0; sample < samples_per_pixel_; sample++) {
          Ray ray = GetRay(i, j);
          pixel_color += RayColor(ray, world, max_depth_);
        }
        WriteColor(std::cout, pixel_color, samples_per_pixel_);
      }
    }
    std::cerr << "\nDone.\n";
  }

private:
  void Initialise() {
    image_height_ = static_cast<int>(image_width_ / aspect_ratio_);
    camera_position_ = Vec3(0, 0, 0);

    auto focal_Length = 1.0;
    auto viewport_height = 2.0*focal_Length;
    auto viewport_width =
        viewport_height * (static_cast<double>(image_width_ / image_height_));

    auto viewport_x_vec = Vec3(viewport_width, 0, 0);
    auto viewport_y_vec = Vec3(0, viewport_height, 0);

    delta_x_vec_ = viewport_x_vec / image_width_;
    delta_y_vec_ = viewport_y_vec / image_height_;

    auto viewport_upper_left_point = camera_position_ - viewport_x_vec / 2.0 -
                                     viewport_y_vec / 2.0 -
                                     Vec3(0, 0, focal_Length);

    pixel_00_point_ =
        viewport_upper_left_point + (delta_x_vec_ / 2.0) + (delta_y_vec_ / 2.0);
  }

  Ray GetRay(int i, int j) const {

    auto pixel_center_point =
        pixel_00_point_ + i * delta_x_vec_ + j * delta_y_vec_;

    auto pixel_sample = pixel_center_point + PixelSampleSqaure();
    auto ray_direction_vec = pixel_center_point - camera_position_;

    return Ray(camera_position_, ray_direction_vec);
  }

  Vec3 PixelSampleSqaure() const {

    auto p_x = -0.5 + RandomDouble();
    auto p_y = -0.5 + RandomDouble();

    return (p_x * 1.0 * delta_x_vec_ + p_y * 1.0 * delta_y_vec_);
  }

  Color RayColor(const Ray &r, const Hittable &world, int depth) {

    HitRecord hit_record;
    if (depth < 0) {
      // std::cerr<<"Yeah\n ";
      return Color(0,0,0);
    }

    if (world.hit(r, Interval(0.001, infinity), hit_record)) {
      Color attenuation;
      Ray scattered;
      if (hit_record.material_->Scatter(r, hit_record, attenuation,
                                        scattered)) {
        return attenuation * RayColor(scattered, world, depth - 1);
      } else {
        return Color(0, 0, 0);
      }
    }

    Vec3 unitVector = UnitVector(r.direction());
    auto temp = 0.5 * (unitVector.y() + 1.0);
    return (1 - temp) * Color(1, 1, 1) + temp * Color(0.5, 0.7, 1);
  }
};