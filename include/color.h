#pragma once

#include "vec3.h"

#include <iostream>

void writeColor(std::ostream &out, Color pixelColor) {
  out << static_cast<int>(255.99 * pixelColor.x()) << " "
      << static_cast<int>(255.99 * pixelColor.y()) << " "
      << static_cast<int>(255.99 * pixelColor.z()) << "\n";
}
