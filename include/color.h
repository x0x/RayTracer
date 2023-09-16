#pragma once

#include "interval.h"
#include "vec3.h"
#include <iostream>

void WriteColor(std::ostream &out, Color pixel_color, int samples_per_pixel) {

  // pixel_color = (pixel_color*1.0) / samples_per_pixel;

  // static const Interval intensity(0.000, 0.999);

  // out << static_cast<int>((256 * intensity.Clamp(pixel_color.x()))) << " "
  //     << static_cast<int>((256 * intensity.Clamp(pixel_color.y()))) << " "
  //     << static_cast<int>((256 * intensity.Clamp(pixel_color.z()))) << "\n";

  auto r = pixel_color.x();
  auto g = pixel_color.y();
  auto b = pixel_color.z();

  // Divide the color by the number of samples.
  auto scale = 1.0 / samples_per_pixel;
  r *= scale;
  g *= scale;
  b *= scale;

  // Write the translated [0,255] value of each color component.
  static const Interval intensity(0.000, 0.999);
  out << static_cast<int>(256 * intensity.Clamp(r)) << ' '
      << static_cast<int>(256 * intensity.Clamp(g)) << ' '
      << static_cast<int>(256 * intensity.Clamp(b)) << '\n';
}
