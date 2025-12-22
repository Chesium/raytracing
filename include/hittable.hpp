#pragma once

#include "RTweekend.hpp"

class HitRecord {
public:
  point3 p;
  v3 n; // normal vector
  double t;
  bool frontFace; // true, say, if the ray is outside of the sphere

  void setNormal(const ray &ra, const v3 &outwardN) {
    // NOTE: the parameter `outwardN` is assumed to have unit length.
    frontFace = dot(ra.direction(), outwardN) < 0; // angle > 90° (outside)
    n = frontFace ? outwardN : -outwardN;
  }
};

class Hittable {
public:
  virtual ~Hittable() = default;
  virtual bool hit(const ray &r, Interval rayt, HitRecord &rec) const = 0;
};