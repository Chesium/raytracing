#include "RTweekend.hpp"
#include "camera.hpp"
#include "hittable.hpp"
#include "hittableList.hpp"
#include "material.hpp"
#include "sphere.hpp"

int main() {
  auto materialGround = make_shared<Lambertian>(color(0.8, 0.8, 0.0));
  auto materialCenter = make_shared<Lambertian>(color(0.1, 0.2, 0.5));
  // auto materialLeft = make_shared<Metal>(color(0.8, 0.8, 0.8), 1.0);
  auto materialLeft = make_shared<Dielectric>(1.5);
  auto materialBubble = make_shared<Dielectric>(1.0 / 1.5);
  auto materialRight = make_shared<Metal>(color(0.8, 0.6, 0.2), 0.3);

  HittableList world;
  world.add(make_shared<Sphere>(point3(1, 0.4, -2), 0.5, materialCenter));
  world.add(make_shared<Sphere>(point3(0.0, -100.5, -1.0), 100.0, materialGround));
  world.add(make_shared<Sphere>(point3(-0.5, 0.0, -2.0), 0.5, materialLeft));
  world.add(make_shared<Sphere>(point3(-0.5, 0.0, -2.0), 0.4, materialBubble));
  world.add(make_shared<Sphere>(point3(0.4, 0.2, -3), 0.7, materialRight));

  Camera cam;
  cam.targetAspectRatio = 16.0 / 9.0;
  cam.imageWidth = 400;
  cam.samplesPerPixel = 100;
  cam.maxDepth = 10;
  cam.verticalFOVdeg = 36;
  cam.lookFrom = point3(-2, 2, 1);
  cam.lookAt = point3(0, 0, -2);
  cam.vup = v3(1, 1, 0);
  cam.render(world);
}