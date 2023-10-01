#pragma once

#include "interval.h"
#include "vec3.h"
#include <iostream>
# include <assert.h>
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

  auto r_val = 256 * intensity.Clamp(r);
  auto g_val = 256 * intensity.Clamp(g);
  auto b_val = 256 * intensity.Clamp(b);

//   std::cerr<<b<<" "<<b_val<<"\n";

//   assert(r_val >=0 && r_val <= 255);
//   assert(g_val >=0 && g_val <= 255);
//   assert(b_val >=0 && b_val <= 255);

  out << static_cast<int>(r_val) << ' '
      << static_cast<int>(g_val) << ' '
      << static_cast<int>(b_val) << '\n';
}
