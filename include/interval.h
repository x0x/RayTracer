#pragma once

#include "constants.h"

class Interval {
public:
  double min_, max_;

public:
  Interval() : min_(+infinity), max_(-infinity) {}

  Interval(double min, double max) : min_(min), max_(max){};

  bool contains(double x) const { return (min_ <= x) && (x <= max_); }

  bool surrounds(double x) const { return (min_ < x) && (x < max_); }

  const static Interval empty, universe;
};

const static Interval empty(+infinity, -infinity);
const static Interval universe(-infinity, +infinity);
