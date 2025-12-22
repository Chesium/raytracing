#pragma once

#include <cmath>
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <random>

using std::make_shared;
using std::shared_ptr;

using uint = unsigned int;

const double inf = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double deg2rad(double deg) { return deg * pi / 180.0; }

inline double randDouble() {
  static std::uniform_real_distribution<double> distribution(0.0, 1.0);
  static std::mt19937 generator;
  return distribution(generator);
}

inline double randDouble(double mi, double mx) { return mi + randDouble() * (mx - mi); }

#include "color.hpp"
#include "interval.hpp"
#include "ray.hpp"
#include "v3.hpp"
