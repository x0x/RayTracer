#pragma once

#include "interval.h"
#include "vec3.h"
#include <iostream>

inline double LinearToGammeSpace(double linear_component)
{
    return sqrt(linear_component);
}


void WriteColor(std::ostream &out, Color pixel_color, int samples_per_pixel) {

  auto r = pixel_color.x();
  auto g = pixel_color.y();
  auto b = pixel_color.z();

  // Divide the color by the number of samples.
  auto scale = 1.0 / samples_per_pixel;
  r *= scale;
  g *= scale;
  b *= scale;

  r = LinearToGammeSpace(r);
  g = LinearToGammeSpace(g);
  b  = LinearToGammeSpace(b);

  // Write the translated [0,255] value of each color component.
  static const Interval intensity(0.000, 0.999);
  out << static_cast<int>(256 * intensity.Clamp(r)) << ' '
      << static_cast<int>(256 * intensity.Clamp(g)) << ' '
      << static_cast<int>(256 * intensity.Clamp(b)) << '\n';
}
