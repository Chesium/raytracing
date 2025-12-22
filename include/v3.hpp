#pragma once

#include <cmath>
#include <iostream>
#include <random>

inline double randDouble() {
  static std::uniform_real_distribution<double> distribution(0.0, 1.0);
  static std::mt19937 generator;
  return distribution(generator);
}

inline double randDouble(double mi, double mx) { return mi + randDouble() * (mx - mi); }

class v3 {
public:
  double e[3];
  // https://cppreference.cn/w/cpp/language/constructor CXX11 Member Initializer List
  v3() : e{0, 0, 0} {}
  v3(double e0, double e1, double e2) : e{e0, e1, e2} {}

  double x() const { return e[0]; }
  double y() const { return e[1]; }
  double z() const { return e[2]; }

  v3 operator-() const { return v3(-e[0], -e[1], -e[2]); }
  double operator[](size_t i) const { return e[i]; }
  double &operator[](size_t i) { return e[i]; }
  v3 &operator+=(const v3 &v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
  }
  v3 &operator*=(double t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
  }
  v3 &operator/=(double t) { return *this *= 1 / t; }
  double l() const { return std::sqrt(lsq()); }
  double lsq() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
  bool nearZero() const {
    const double s = 1e-8;
    return std::fabs(e[0]) < s && std::fabs(e[1]) < s && std::fabs(e[2]) < s;
  }
  // generate a random vector in the unit cube
  static v3 rand() { return v3(randDouble(), randDouble(), randDouble()); }
};

using point3 = v3;

inline std::ostream &operator<<(std::ostream &out, const v3 &v) {
  return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline v3 operator+(const v3 &u, const v3 &v) {
  return v3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline v3 operator-(const v3 &u, const v3 &v) {
  return v3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline v3 operator*(const v3 &u, const v3 &v) {
  return v3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline v3 operator*(double t, const v3 &v) { return v3(t * v.e[0], t * v.e[1], t * v.e[2]); }

inline v3 operator*(const v3 &v, double t) { return t * v; }

inline v3 operator/(const v3 &v, double t) { return (1 / t) * v; }

inline double dot(const v3 &u, const v3 &v) {
  return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline v3 cross(const v3 &u, const v3 &v) {
  return v3(u.e[1] * v.e[2] - u.e[2] * v.e[1], u.e[2] * v.e[0] - u.e[0] * v.e[2],
            u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline v3 unit(const v3 &v) { return v / v.l(); }

inline v3 randUnit() {
  // using rejection sampling
  // to sample vectors in a unit sphere (which is contained by a unit cube)
  while(true) {
    v3 v = v3::rand();
    double lsq = v.lsq();
    if(1e-160 < lsq && lsq <= 1) return v / std::sqrt(lsq);
  }
}

inline v3 randUnitOnHemisphere(const v3 &n) {
  v3 v = randUnit();
  return dot(v, n) > 0 ? v : -v;
}

inline v3 reflect(const v3 &v, const v3 &n) { return v - 2 * dot(v, n) * n; }

inline v3 refract(const v3 &R, const v3 &n, double etaIOverEtaT) {
  double cosTheta = std::fmin(dot(-R, n), 1.0);
  v3 RPerp = etaIOverEtaT * (R + dot(-R, n) * n);
  v3 RPara = -std::sqrt(std::fabs(1 - RPerp.lsq())) * n;
  return RPerp + RPara;
}