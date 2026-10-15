#ifndef NORMALSHADER_H
#define NORMALSHADER_H
#include "Shader.h"

class NormalShader : public Shader {
  public:
    NormalShader() {};
    const Color getColor(const HitRecord &hitRecord) const override { return getColor(hitRecord.viewDirection); };

    const Color getColor(const Vec3 &viewDirection) const {
      // normalize ray direction
      Color clr = viewDirection.normalized();
      // printf("NormalShader::getColor: viewDirection: %s\n", viewDirection.toString().c_str());

      // shift into color space
      clr = (clr + Vec3(1.f, 1.f, 1.f)) * 0.5;

      // return for use
      // printf("NormalShader::getColor: returning color: %s\n", clr.toString().c_str());
      return clr;
    };
};

#endif// NORMALSHADER_H
