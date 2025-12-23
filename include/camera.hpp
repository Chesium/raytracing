#pragma once

#include "RTweekend.hpp"
#include "hittable.hpp"
#include "material.hpp"

// sample ([-.5,+.5],[-.5,+.5])
inline v3 sampleSquare() { return v3(randDouble() - 0.5, randDouble() - 0.5, 0); }

const double reflectanceList[10] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
const uint reflectanceListN = 10;

class Camera {
public:
  double targetAspectRatio{1.0};
  uint imageWidth{200};
  uint samplesPerPixel{10};
  uint maxDepth{10};
  double focalLength{1.0};
  double verticalFOVdeg{90};

  void render(const Hittable &world) {
    init();
    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";
    for(uint j = 0; j < imageHeight; j++) {
      std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
      for(uint i = 0; i < imageWidth; i++) {
        // traverse the reflectance list to generate the "gamut" of the scene
        reflectance = reflectanceList[uint((double)i / imageWidth * reflectanceListN)];
        color c(0, 0, 0);
        for(uint s = 0; s < samplesPerPixel; s++) {
          c += rayColor(getRandomPixelRay(i, j), maxDepth, world);
        }
        writeColor(std::cout, c / samplesPerPixel);
      }
    }
    std::clog << "\rDone.                 \n";
  }

private:
  // init
  point3 cameraCenter{point3(0, 0, 0)};
  // calculated
  uint imageHeight;
  double realAspectRatio;
  double verticalFOVrad;
  double viewportWidth;
  double viewportHeight;
  // aux vectors
  v3 viewportU, viewportV;
  v3 pixelU, pixelV;
  point3 viewpointUpperLeft;
  point3 pixel00;
  void init() {
    imageHeight = uint(imageWidth / targetAspectRatio);
    imageHeight = imageHeight < 1 ? 1 : imageHeight;
    realAspectRatio = (double)imageWidth / imageHeight;
    verticalFOVrad = deg2rad(verticalFOVdeg);
    viewportHeight = 2 * focalLength * std::tan(verticalFOVrad / 2);
    viewportWidth = viewportHeight * realAspectRatio;
    // aux vectors:
    viewportU = v3(viewportWidth / 2, 0, 0);
    viewportV = v3(0, -viewportHeight / 2, 0);
    pixelU = viewportU / imageWidth;
    pixelV = viewportV / imageHeight;
    viewpointUpperLeft = cameraCenter - v3(0, 0, focalLength) - viewportU / 2 - viewportV / 2;
    pixel00 = viewpointUpperLeft + pixelU / 2 + pixelV / 2;
  }

  ray getRandomPixelRay(uint i, uint j) {
    v3 randOffset = sampleSquare();
    point3 pixelSample =
        pixel00 + ((i + randOffset.x()) * pixelU) + ((j + randOffset.y()) * pixelV);
    v3 rayDirection = pixelSample - cameraCenter;
    return ray(pixelSample, rayDirection);
  }

  double reflectance = 0.5;
  color rayColor(const ray &ra, uint depth, const Hittable &world) {
    if(depth <= 0) return color(0, 0, 0);
    HitRecord rec;
    // hittable list processing
    if(world.hit(ra, Interval(0.001, inf), rec)) {
      // return 0.5 * (rec.n + v3(1, 1, 1)); // Norm-colored

      // diffuse (recursive)
      // v3 reflecDir = randUnitOnHemisphere(rec.n); // uniform distribution
      // v3 reflecDir = randUnit() + rec.n; // Lambertian distribution
      // return reflectance * rayColor(ray(rec.p, reflecDir), depth - 1, world);

      ray scattered;
      color attenuation;
      if(rec.mat->scatter(ra, rec, attenuation, scattered)) { // scattered / reflected
        return attenuation * rayColor(scattered, depth - 1, world);
      } else { // absorbed
        return color(0, 0, 0);
      }
    }
    // background gradient
    v3 unit_direction = unit(ra.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
  }
};