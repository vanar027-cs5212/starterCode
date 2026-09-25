#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "Ray.h"

TEST_CASE("ray") {
  Point3 origin(1.1, 2.0, 3.4);
  Vec3 dir(0.1, 3.5, 5.3);
  Ray r(origin, dir);

  float t = 0.3;

  Point3 newpoint = r.at(t);

  // should be origin + t * direction
  REQUIRE(newpoint.x() == origin.x() + t * dir.x());
  REQUIRE(newpoint.y() == origin.y() + t * dir.y());
  REQUIRE(newpoint.z() == origin.z() + t * dir.z());
}

