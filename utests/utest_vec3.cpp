#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "Vec3.h"

TEST_CASE("vec3") {
  float eps = 1.0e-3;
  SECTION("xyz") {
    Vec3 v1(0.0f, 0.5f, 1.0f);

    REQUIRE_THAT(v1.x(), Catch::Matchers::WithinAbs(0.0f, eps));
    REQUIRE_THAT(v1.y(), Catch::Matchers::WithinAbs(0.5f, eps));
    REQUIRE_THAT(v1.z(), Catch::Matchers::WithinAbs(1.0f, eps));
  }

  SECTION("do addition") {
    Vec3 v1(0.0f, 0.5f, 1.0f);
    Vec3 v2(1.0f, 0.5f, 0.0f);
    Vec3 sum = v1 + v2;

    REQUIRE_THAT(sum.x(), Catch::Matchers::WithinAbs(1.0f, eps));
    REQUIRE_THAT(sum.y(), Catch::Matchers::WithinAbs(1.0f, eps));
    REQUIRE_THAT(sum.z(), Catch::Matchers::WithinAbs(1.0f, eps));
  }

  SECTION("do subtraction") {
    Vec3 v1(0.0f, 0.5f, 1.0f);
    Vec3 v2(1.0f, 0.5f, 0.0f);
    Vec3 diff = v1 - v2;

    REQUIRE_THAT(diff.x(), Catch::Matchers::WithinAbs(-1.0f, eps));
    REQUIRE_THAT(diff.y(), Catch::Matchers::WithinAbs(0.0f, eps));
    REQUIRE_THAT(diff.z(), Catch::Matchers::WithinAbs(1.0f, eps));
  }

  SECTION("do multiplication") {
    Vec3 v1(0.0f, 0.5f, 1.0f);
    float factor = 2.0f;
    Vec3 product = v1 * factor;

    REQUIRE_THAT(product.x(), Catch::Matchers::WithinAbs(0.0f, eps));
    REQUIRE_THAT(product.y(), Catch::Matchers::WithinAbs(1.0f, eps));
    REQUIRE_THAT(product.z(), Catch::Matchers::WithinAbs(2.0f, eps));
  }

  SECTION("make negative") {
    Vec3 v1(0.0f, 0.5f, 1.0f);
    Vec3 neg = -v1;

    REQUIRE_THAT(neg.x(), Catch::Matchers::WithinAbs(0.0f, eps));
    REQUIRE_THAT(neg.y(), Catch::Matchers::WithinAbs(-0.5f, eps));
    REQUIRE_THAT(neg.z(), Catch::Matchers::WithinAbs(-1.0f, eps));
  }

  SECTION("check length") {
    Vec3 v(3.0f, 4.0f, 0.0f);

    REQUIRE_THAT(v.length(), Catch::Matchers::WithinAbs(5.0f, eps));
  }
}
