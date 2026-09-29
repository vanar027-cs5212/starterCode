#include <catch2/catch_test_macros.hpp>

TEST_CASE("Simple Failure") {
  int i = 43;
  REQUIRE(i == 42);
}
