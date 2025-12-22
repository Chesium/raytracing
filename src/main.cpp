#include "RTweekend.hpp"
#include "camera.hpp"
#include "hittable.hpp"
#include "hittableList.hpp"
#include "sphere.hpp"

int main() {
  HittableList world;
  world.add(make_shared<Sphere>(point3(1, 0.4, -2), 0.5));
  world.add(make_shared<Sphere>(point3(0, -100.5, -1), 100));

  Camera cam;
  cam.targetAspectRatio = 16.0 / 9.0;
  cam.imageWidth = 400;
  cam.render(world);
}