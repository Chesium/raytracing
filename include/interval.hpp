#pragma once

#include "RTweekend.hpp"

class Interval {
public:
  double mi, mx;

  Interval() : mi(+inf), mx(-inf) {} // empty Interval
  Interval(double mi, double mx) : mi(mi), mx(mx) {}

  double size() { return mx - mi; };
  bool contains(double x) { return mi <= x && x <= mx; }
  bool surrounds(double x) { return mi < x && x < mx; }
  static const Interval empty, universe;
};

const Interval Interval::empty(+inf, -inf);
const Interval Interval::universe(-inf, +inf);