#include "RTweekend.hpp"
#include "camera.hpp"
#include "hittable.hpp"
#include "hittableList.hpp"
#include "material.hpp"
#include "sphere.hpp"

// int main() {
//   // auto materialGround = make_shared<Lambertian>(color(0.8, 0.8, 0.0));
//   // auto materialCenter = make_shared<Lambertian>(color(0.1, 0.2, 0.5));
//   // // auto materialLeft = make_shared<Metal>(color(0.8, 0.8, 0.8), 1.0);
//   // auto materialLeft = make_shared<Dielectric>(1.5);
//   // auto materialBubble = make_shared<Dielectric>(1.0 / 1.5);
//   // auto materialRight = make_shared<Metal>(color(0.8, 0.6, 0.2), 0.3);

//   HittableList world;
//   // world.add(make_shared<Sphere>(point3(1, 0.4, -2), 0.5, materialCenter));
//   // world.add(make_shared<Sphere>(point3(0.0, -100.5, -1.0), 100.0, materialGround));
//   // world.add(make_shared<Sphere>(point3(-0.5, 0.0, -2.0), 0.5, materialLeft));
//   // world.add(make_shared<Sphere>(point3(-0.5, 0.0, -2.0), 0.4, materialBubble));
//   // world.add(make_shared<Sphere>(point3(0.4, 0.2, -3), 0.7, materialRight));

//   Camera cam;
//   // cam.targetAspectRatio = 16.0 / 9.0;
//   // cam.imageWidth = 400;
//   // cam.samplesPerPixel = 100;
//   // cam.maxDepth = 10;
//   // cam.verticalFOVdeg = 30;
//   // cam.lookFrom = point3(-2, 2, 1);
//   // cam.lookAt = point3(0, 0.6, -2);
//   // cam.vup = v3(0, 1, 0);
//   // cam.focusDist = 4;
//   // cam.defocusDeg = 0;
//   // cam.render(world);

//   auto material_ground = make_shared<Lambertian>(color(0.8, 0.8, 0.0));
//   auto material_center = make_shared<Lambertian>(color(0.1, 0.2, 0.5));
//   auto material_left = make_shared<Dielectric>(1.50);
//   auto material_bubble = make_shared<Dielectric>(1.00 / 1.50);
//   auto material_right = make_shared<Metal>(color(0.8, 0.6, 0.2), 1.0);

//   world.add(make_shared<Sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
//   world.add(make_shared<Sphere>(point3(0.0, 0.0, -1.2), 0.5, material_center));
//   world.add(make_shared<Sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
//   world.add(make_shared<Sphere>(point3(-1.0, 0.0, -1.0), 0.4, material_bubble));
//   world.add(make_shared<Sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

//   cam.targetAspectRatio = 16.0 / 9.0;
//   cam.imageWidth = 400;
//   cam.samplesPerPixel = 100;
//   cam.maxDepth = 50;

//   cam.verticalFOVdeg = 20;
//   cam.lookFrom = point3(-2, 2, 1);
//   cam.lookAt = point3(0, 0, -1);
//   cam.vup = v3(0, 1, 0);

//   cam.defocusDeg = 10.0;
//   cam.focusDist = 3.4;

//   cam.render(world);
// }

int main() {
  HittableList world;

  auto ground_material = make_shared<Lambertian>(color(0.5, 0.5, 0.5));
  world.add(make_shared<Sphere>(point3(0, -1000, 0), 1000, ground_material));

  for(int a = -11; a < 11; a++) {
    for(int b = -11; b < 11; b++) {
      auto choose_mat = randDouble();
      point3 center(a + 0.9 * randDouble(), 0.2, b + 0.9 * randDouble());

      if((center - point3(4, 0.2, 0)).l() > 0.9) {
        shared_ptr<Material> sphere_material;

        if(choose_mat < 0.8) {
          // diffuse
          auto albedo = color::rand() * color::rand();
          sphere_material = make_shared<Lambertian>(albedo);
          world.add(make_shared<Sphere>(center, 0.2, sphere_material));
        } else if(choose_mat < 0.95) {
          // metal
          auto albedo = color::rand();
          auto fuzz = randDouble(0, 0.5);
          sphere_material = make_shared<Metal>(albedo, fuzz);
          world.add(make_shared<Sphere>(center, 0.2, sphere_material));
        } else {
          // glass
          sphere_material = make_shared<Dielectric>(1.5);
          world.add(make_shared<Sphere>(center, 0.2, sphere_material));
        }
      }
    }
  }

  auto material1 = make_shared<Dielectric>(1.5);
  world.add(make_shared<Sphere>(point3(0, 1, 0), 1.0, material1));

  auto material2 = make_shared<Lambertian>(color(0.4, 0.2, 0.1));
  world.add(make_shared<Sphere>(point3(-4, 1, 0), 1.0, material2));

  auto material3 = make_shared<Metal>(color(0.7, 0.6, 0.5), 0.0);
  world.add(make_shared<Sphere>(point3(4, 1, 0), 1.0, material3));

  Camera cam;

  cam.targetAspectRatio = 16.0 / 9.0;
  cam.imageWidth = 1200;
  cam.samplesPerPixel = 10;
  cam.maxDepth = 50;

  cam.verticalFOVdeg = 20;
  cam.lookFrom = point3(13, 2, 3);
  cam.lookAt = point3(0, 0, 0);
  cam.vup = v3(0, 1, 0);

  cam.defocusDeg = 0.6;
  cam.focusDist = 10.0;

  cam.render(world);
}