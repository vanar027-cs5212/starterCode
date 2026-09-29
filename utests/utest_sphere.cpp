#include <catch2/catch_test_macros.hpp>
#include "Sphere.h"
TEST_CASE("sphere & ray intersection") {
  SECTION("Ray intersects sphere") {
    Sphere sphere(Point3(0, 0, -5), 1.0);
    Ray ray(Point3(0, 0, 0), Vec3(0, 0, -1));
    HitRecord rec;
    REQUIRE(sphere.hit(ray, 0.001, INFINITY, rec));
    REQUIRE(rec.t > 0);
  }
  SECTION("Ray misses sphere") {
    Sphere sphere(Point3(0, 0, -5), 1.0);
    Ray ray(Point3(0, 0, 0), Vec3(0, 1, 0));
    HitRecord rec;
    REQUIRE_FALSE(sphere.hit(ray, 0.001, INFINITY, rec));
  }
}


