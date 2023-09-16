#pragma once

#include "constants.h"

class Interval {
public:
  double min_, max_;

public:
  Interval() : min_(+infinity), max_(-infinity) {}

  Interval(double min, double max) : min_(min), max_(max){};

  bool Contains(double x) const { return (min_ <= x) && (x <= max_); }

  bool Surrounds(double x) const { return (min_ < x) && (x < max_); }

  double Clamp(double x) const {
        if (x < min_) return min_;
        if (x > max_) return max_;
        return x;
    }

  const static Interval empty, universe;
};

const static Interval empty(+infinity, -infinity);
const static Interval universe(-infinity, +infinity);
