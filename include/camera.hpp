#pragma once

#include "RTweekend.hpp"
#include "hittable.hpp"

// sample ([-.5,+.5],[-.5,+.5])
inline v3 sampleSquare() { return v3(randDouble() - 0.5, randDouble() - 0.5, 0); }

class Camera {
public:
  double targetAspectRatio{1.0};
  uint imageWidth{200};
  uint samplesPerPixel{10};
  uint maxDepth{10};

  void render(const Hittable &world) {
    init();
    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";
    for(uint j = 0; j < imageHeight; j++) {
      std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
      for(uint i = 0; i < imageWidth; i++) {
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
  double focalLength{1.0};
  double viewportHeight{2.0};
  point3 cameraCenter{point3(0, 0, 0)};
  // calculated
  uint imageHeight;
  double realAspectRatio;
  double viewportWidth;
  // aux vectors
  v3 viewportU, viewportV;
  v3 pixelU, pixelV;
  point3 viewpointUpperLeft;
  point3 pixel00;
  void init() {
    imageHeight = uint(imageWidth / targetAspectRatio);
    imageHeight = imageHeight < 1 ? 1 : imageHeight;
    realAspectRatio = (double)imageWidth / imageHeight;
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

  color rayColor(const ray &ra, uint depth, const Hittable &world) {
    if(depth <= 0) return color(0, 0, 0);
    HitRecord rec;
    // hittable list processing
    if(world.hit(ra, Interval(0, inf), rec)) {
      // return 0.5 * (rec.n + v3(1, 1, 1)); // Norm-colored

      // diffuse (recursive)
      const double reflectivity = 0.5;
      v3 reflecDir = randUnitOnHemisphere(rec.n);
      return reflectivity * rayColor(ray(rec.p, reflecDir), depth - 1, world);
    }
    // background gradient
    v3 unit_direction = unit(ra.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
  }
};