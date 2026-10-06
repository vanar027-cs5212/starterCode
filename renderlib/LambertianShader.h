#ifndef LAMBERTIANSHADER_H
#define LAMBERTIANSHADER_H
#include "Shader.h"
#include "Shape.h"

class LambertianShader : public Shader {
  public:
    LambertianShader() {};
    LambertianShader(const Color &kd) : kd(kd) {};

    const Color getColor(const HitRecord &hitRecord) const override {
      Vec3 normal = hitRecord.normal;
      Color result(0, 0, 0);
      for (const PointLight &light : *hitRecord.lights) {
        // direction from hitpoint to light
        Vec3 l = unit_vector(light.position - hitRecord.point);

        // cosine of angle between n and l; clamp so surfaces
        // facing away from the light get 0, not negative light
        double nDotL = std::max(0.0, dot(normal, l));

        // Component-wise multiple of material color and light color
        result += kd * light.intensity * nDotL;
      }
      return result;
    };


  private:
    Color kd;// diffuse color of the material
};
#endif// LAMBERTIANSHADER_H
