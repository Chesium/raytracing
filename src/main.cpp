#include <iostream>

#include "color.hpp"
#include "v3.hpp"

int main() {
  int w = 256, h = 256;
  std::cout << "P3\n" << w << ' ' << h << "\n255\n";
  for(int j = 0; j < h; j++) {
    std::clog << "\rScanlines remaining: " << (h - j) << ' ' << std::flush;
    for(int i = 0; i < w; i++) {
      auto p = color(double(i) / (w - 1), double(j) / (h - 1), 0);
      writeColor(std::cout, p);
    }
  }
  std::clog << "\rDone.                 \n";
}