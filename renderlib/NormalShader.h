#ifndef NORMALSHADER_H
#define NORMALSHADER_H
#include "Shader.h"

class NormalShader : public Shader {
  public:
    NormalShader() {};
    const Color getColor(const HitRecord &hitRecord) const override {
      // normalize ray direction
      printf("NormalShader: %s\n", hitRecord.viewDirection.toString().c_str());
      Color clr = hitRecord.viewDirection.normalized();

      // shift into color space
      clr = (clr + Vec3(1, 1, 1)) * 0.5;

      // return for use
      printf("NormalShader: %s\n", clr.toString().c_str());
      return clr;
    };
};

#endif// NORMALSHADER_H
