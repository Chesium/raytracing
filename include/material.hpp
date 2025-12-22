#pragma once

#include "hittable.hpp"

class Material {
public:
  virtual ~Material() = default;
  virtual bool scatter(const ray &ra, const HitRecord &rec, color &attenuation,
                       ray &scattered) const {
    return false;
  }
};

class Lambertian : public Material {
public:
  Lambertian(const color &albedo) : albedo(albedo) {}
  bool scatter(const ray &ra, const HitRecord &rec, color &attenuation,
               ray &scattered) const override {
    // implement choice: always scatter and attenuate light
    v3 scatterDir = rec.n + randUnit();
    scattered = ray(rec.p, scatterDir.nearZero() ? rec.n : scatterDir);
    attenuation = albedo;
    return true;
  }

private:
  color albedo;
};

class Metal : public Material {
public:
  Metal(const color &albedo, double fuzz) : albedo(albedo), fuzz(fuzz) {}
  bool scatter(const ray &ra, const HitRecord &rec, color &attenuation,
               ray &scattered) const override {
    v3 reflected = reflect(ra.direction(), rec.n);
    reflected = unit(reflected) + randUnit() * fuzz;
    scattered = ray(rec.p, reflected);
    attenuation = albedo;
    return dot(reflected, rec.n) > 0; // same hemisphere
  }

private:
  color albedo;
  double fuzz;
};

class Dielectric : public Material {
public:
  Dielectric(double refractionIndex) : refractionIndex(refractionIndex) {}
  bool scatter(const ray &ra, const HitRecord &rec, color &attenuation,
               ray &scattered) const override {
    double ri = rec.frontFace ? (1.0 / refractionIndex) : refractionIndex;
    v3 R = unit(ra.direction()), direction;
    double cosTheta = std::fmin(dot(-R, rec.n), 1.0);
    double sinTheta = std::sqrt(1 - cosTheta * cosTheta);
    if(ri * sinTheta > 1.0) { // total reflection
      direction = reflect(R, rec.n);
    } else { // refraction
      direction = refract(R, rec.n, ri);
    }
    scattered = ray(rec.p, direction);
    attenuation = color(1.0, 1.0, 1.0);
    return true;
  }

private:
  double refractionIndex;
};