#pragma once

#include "constants.h"
#include <random>

inline double DegreeToRadian(double degrees) {
  return degrees * pi / 180.0;
}

// Returns a random real in [0,1).
inline double RandomDouble() {
    return rand() / (RAND_MAX + 1.0);
}

inline double RandomDouble(double min, double max) {
    return min + (max-min)*RandomDouble();
}