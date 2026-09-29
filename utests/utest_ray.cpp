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
  REQUIRE_THAT(newpoint.x(), Catch::Matchers::WithinAbs(origin.x() + t * dir.x(), 1e-6));
  REQUIRE_THAT(newpoint.y(), Catch::Matchers::WithinAbs(origin.y() + t * dir.y(), 1e-6));
  REQUIRE_THAT(newpoint.z(), Catch::Matchers::WithinAbs(origin.z() + t * dir.z(), 1e-6));
}

