#include "Shader.h"

const Color RayVisualizer::getColor(const Ray &r) const {
  // normalize ray direction
  Color clr = r.direction() / r.direction().length();

  // shift into color space
  clr = (clr + Vec3(1, 1, 1)) * 0.5;

  // return for use
  return clr;
};

const Color SolidColor::getColor(const Ray &r) const { return color; };
