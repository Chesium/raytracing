#pragma once

#include <vector>

#include "RTweekend.hpp"
#include "hittable.hpp"


using std::make_shared;
using std::shared_ptr;

class HittableList : public Hittable {
public:
  std::vector<shared_ptr<Hittable>> objs;

  HittableList() {}
  HittableList(shared_ptr<Hittable> obj) { add(obj); }
  void clear() { objs.clear(); }

  void add(shared_ptr<Hittable> obj) { objs.push_back(obj); }

  bool hit(const ray &ra, double tmi, double tmx, HitRecord &rec) const override {
    HitRecord tmpRec;
    bool hitAny = false;
    double closestSoFar = tmx;
    for(const auto &obj : objs) {
      if(obj->hit(ra, tmi, closestSoFar, tmpRec)) {
        hitAny = true;
        closestSoFar = tmpRec.t;
        rec = tmpRec;
      }
    }
    return hitAny;
  }
};