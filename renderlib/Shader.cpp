#include "Shader.h"

const Color NormalShader::getColor(const Vec3 &direction) const {
  // normalize ray direction
  Color clr = direction.normalized();

  // shift into color space
  clr = (clr + Vec3(1, 1, 1)) * 0.5;

  // return for use
  return clr;
};

const Color SolidColor::getColor(const Vec3 &) const { return color; };

