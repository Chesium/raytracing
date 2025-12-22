#pragma once

#include <iostream>

#include "interval.hpp"
#include "v3.hpp"

using color = v3;

inline double lin2gamma(double lin) {
  // using gamma 2 (exponent used from gamma space to linear space)
  return lin == 0 ? 0 : std::sqrt(lin);
}

void writeColor(std::ostream &out, const color &p) {
  auto r = lin2gamma(p.x());
  auto g = lin2gamma(p.y());
  auto b = lin2gamma(p.z());

  // Translate the [0,1] component values to the byte range [0,255].
  static const Interval intensity(0.000, 0.999);
  int rbyte = int(256 * intensity.clamp(r));
  int gbyte = int(256 * intensity.clamp(g));
  int bbyte = int(256 * intensity.clamp(b));

  // Write out the pixel color components.
  out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}