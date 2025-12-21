#include <gtest/gtest.h>

#include "v3.hpp"

TEST(LibTest, DefaultConstructsToZero) {
  v3 v;
  EXPECT_DOUBLE_EQ(v.x(), 0.0);
  EXPECT_DOUBLE_EQ(v.y(), 0.0);
  EXPECT_DOUBLE_EQ(v.z(), 0.0);
}

TEST(LibTest, AddsAndSubtractsComponentWise) {
  v3 a(1.0, 2.0, 3.0);
  v3 b(4.0, 5.0, 6.0);

  v3 sum = a + b;
  v3 diff = b - a;

  EXPECT_DOUBLE_EQ(sum.x(), 5.0);
  EXPECT_DOUBLE_EQ(sum.y(), 7.0);
  EXPECT_DOUBLE_EQ(sum.z(), 9.0);

  EXPECT_DOUBLE_EQ(diff.x(), 3.0);
  EXPECT_DOUBLE_EQ(diff.y(), 3.0);
  EXPECT_DOUBLE_EQ(diff.z(), 3.0);
}

TEST(LibTest, DotAndCrossProducts) {
  v3 x_axis(1.0, 0.0, 0.0);
  v3 y_axis(0.0, 1.0, 0.0);
  v3 z_axis(0.0, 0.0, 1.0);

  EXPECT_DOUBLE_EQ(dot(x_axis, y_axis), 0.0);
  EXPECT_DOUBLE_EQ(dot(x_axis, x_axis), 1.0);

  v3 cross_xy = cross(x_axis, y_axis);
  EXPECT_DOUBLE_EQ(cross_xy.x(), z_axis.x());
  EXPECT_DOUBLE_EQ(cross_xy.y(), z_axis.y());
  EXPECT_DOUBLE_EQ(cross_xy.z(), z_axis.z());
}

TEST(LibTest, UnitVectorHasLengthOne) {
  v3 v(0.0, 3.0, 4.0);
  v3 u = unit(v);

  EXPECT_NEAR(u.l(), 1.0, 1e-12);
}

#include "ray.hpp"

TEST(LibTest, RayAtMethod) {
  point3 o(1.0, 2.0, 3.0);
  v3 d(-2.0, 3.0, 0.5);
  ray r(o, d);
  double t = 2.0;
  point3 t2 = r.at(t);
  point3 ref(-3.0, 8.0, 4.0);
  point3 err = t2 - ref;

  EXPECT_NEAR(err.l(), 0.0, 1e-12);
}