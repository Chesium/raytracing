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
  Metal(const color &albedo) : albedo(albedo) {}
  bool scatter(const ray &ra, const HitRecord &rec, color &attenuation,
               ray &scattered) const override {
    v3 reflected = reflect(ra.direction(), rec.n);
    scattered = ray(rec.p, reflected);
    attenuation = albedo;
    return true;
  }

private:
  color albedo;
};