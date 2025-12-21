#include <functional>
#include <iostream>

#include "color.hpp"
#include "ray.hpp"
#include "v3.hpp"

using uint = unsigned int;

class RayTracer {
public:
  RayTracer() {
    targetAspectRatio = 16.0 / 9.0;
    imageWidth = 400;
    focalLength = 1.0;
    viewportHeight = 2.0;
    cameraCenter = point3(0, 0, 0);
    rayColor = [](const ray &r) -> color {
      v3 unit_direction = unit(r.direction());
      auto a = 0.5 * (unit_direction.y() + 1.0);
      return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
    };
    calcOtherParameters();
  }

  void render() {
    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";
    for(int j = 0; j < imageHeight; j++) {
      std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
      for(int i = 0; i < imageWidth; i++) {
        point3 pixelCenter = pixel00 + (i * pixelU) + (j * pixelV);
        v3 rayDirection = pixelCenter - cameraCenter;
        ray r(pixelCenter, rayDirection);
        color c = rayColor(r);
        writeColor(std::cout, c);
      }
    }
    std::clog << "\rDone.                 \n";
  }

private:
  void calcOtherParameters() {
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

  // init
  double targetAspectRatio;
  uint imageWidth;
  double focalLength;
  double viewportHeight;
  point3 cameraCenter;
  std::function<color(const ray &)> rayColor;
  // calculated
  uint imageHeight;
  double realAspectRatio;
  double viewportWidth;
  // aux vectors
  v3 viewportU, viewportV;
  v3 pixelU, pixelV;
  point3 viewpointUpperLeft;
  point3 pixel00;
};

int main() {
  RayTracer rayTracer;
  rayTracer.render();
}