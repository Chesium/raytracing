#pragma once

#include <cmath>
#include <functional>
#include <iostream>
#include <limits>
#include <memory>

using std::make_shared;
using std::shared_ptr;

using uint = unsigned int;

const double inf = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double deg2rad(double deg) { return deg * pi / 180.0; }

#include "color.hpp"
#include "ray.hpp"
#include "v3.hpp"