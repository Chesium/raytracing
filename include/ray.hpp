#pragma once

#include "v3.hpp"

class ray {
public:
  ray() {}

  ray(const point3 &origin, const v3 &direction) : orig(origin), dir(direction) {}

  const point3 &origin() const { return orig; }
  const v3 &direction() const { return dir; }

  point3 at(double t) const { return orig + t * dir; }

private:
  point3 orig;
  v3 dir;
};