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

  bool hit(const ray &ra, Interval rayt, HitRecord &rec) const override {
    HitRecord tmpRec;
    bool hitAny = false;
    double closestSoFar = rayt.mx;
    for(const auto &obj : objs) {
      if(obj->hit(ra, Interval(rayt.mi, closestSoFar), tmpRec)) {
        hitAny = true;
        closestSoFar = tmpRec.t;
        rec = tmpRec;
      }
    }
    return hitAny;
  }
};