#pragma once

#include "RTweekend.hpp"
#include "hittable.hpp"

class Sphere : public Hittable {
public:
  Sphere(const point3 c, double r) : c(c), r(std::fmax(0, r)) {};

  bool hit(const ray &ra, double tmi, double tmx, HitRecord &rec) const override {
    v3 d = ra.direction(), Q = ra.origin();
    v3 QC = c - Q;
    double A = d.lsq();    // dot(d,d)
    double H = dot(d, QC); // b = -2h
    double C = dot(QC, QC) - r * r;
    double discri = H * H - A * C;
    if(discri < 0) {
      return false;
    }

    // find the nearest t s.t. ray(t) ∈ (tmi,tmx)
    double sqdiscri = std::sqrt(discri);
    double root = (H - sqdiscri) / A;
    if(root <= tmi || root >= tmx) {
      root = (H + sqdiscri) / A;
      if(root <= tmi || root >= tmx) return false;
    }

    // fill the rec:
    rec.t = root;
    rec.p = ra.at(rec.t);
    v3 outwardN = (rec.p - c) / r;
    rec.setNormal(ra, outwardN);
    return true;
  }

private:
  point3 c;
  double r;
};