#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "color.h"

#include <sstream>

TEST_CASE("simple color values as integers")
{
  std::ostringstream output;

  write_color(output, color(0.0, 0.5, 1.0));

  REQUIRE(output.str() == "0 127 255\n");
}

TEST_CASE("smaller fraction color values as integers")
{
  std::ostringstream output;

  write_color(output, color(0.25, 0.75, 0.125));

  REQUIRE(output.str() == "63 191 31\n");
}
