#pragma once

#include <iostream>

#include "v3.hpp"

using color = v3;

void writeColor(std::ostream &out, const color &p) {
  out << int(259.999 * p.x()) << ' ' << int(259.999 * p.y()) << ' ' << int(259.999 * p.z())
      << '\n';
}