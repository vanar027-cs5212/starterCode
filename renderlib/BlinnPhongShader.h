#ifndef BLINNPHONGSHADER_H
#define BLINNPHONGSHADER_H
#include "Shader.h"

class BlinnPhongShader : public Shader {
  public:
    BlinnPhongShader() {};
    BlinnPhongShader(const Color &c, float s) : kd(c), shininess(s) {};

    const Color getColor(const HitRecord &hitRecord) const override {
      Vec3 normal = hitRecord.normal;
      Color result(0, 0, 0);
      for (const PointLight &light : *hitRecord.lights) {
        // direction from hitpoint to light
        Vec3 l = unit_vector(light.position - hitRecord.point);

        // cosine of angle between n and l; clamp so surfaces
        // facing away from the light get 0, not negative light
        double nDotL = std::max(0.0, dot(normal, l));

        // Blinn-Phong specular reflection
        Vec3 viewDir = unit_vector(-hitRecord.viewDirection);
        Vec3 halfVector = unit_vector(l + viewDir);
        double nDotH = std::max(0.0, dot(normal, halfVector));
        double specular = std::pow(nDotH, shininess);

        // Component-wise multiple of material color and light color
        result += kd * light.intensity * nDotL + specular * light.intensity;
      }
      return result;
    }

  private:
    Color kd;
    float shininess;
};

#endif// BLINNPHONGSHADER_H
