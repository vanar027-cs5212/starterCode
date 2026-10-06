#ifndef BLINNPHONGSHADER_H
#define BLINNPHONGSHADER_H
#include "Shader.h"

class BlinnPhongShader : public Shader {
  public:
    BlinnPhongShader() {};
    BlinnPhongShader(const Color &color, const Color &specClr, float shininess) : color(color), specColor(specClr), shininess(shininess) {};
    BlinnPhongShader(const Color &color, float shininess) : color(color), specColor(Color(1.f, 1.f, 1.f)), shininess(shininess) {};

    // const Color _getColor(const HitRecord &hitRecord) const {
    //   Vec3 normal = hitRecord.normal;
    //   Color result(0, 0, 0);
    //   for (const PointLight &light : *hitRecord.lights) {
    //     // direction from hitpoint to light
    //     Vec3 l = unit_vector(light.position - hitRecord.point);

    //     // cosine of angle between n and l; clamp so surfaces
    //     // facing away from the light get 0, not negative light
    //     double nDotL = std::max(0.0, dot(normal, l));

    //     // Blinn-Phong specular reflection
    //     Vec3 viewDir = unit_vector(-hitRecord.viewDirection);
    //     Vec3 halfVector = unit_vector(l + viewDir);
    //     double nDotH = std::max(0.0, dot(normal, halfVector));
    //     double specular = std::pow(nDotH, shininess);

    //     // Component-wise multiple of material color and light color
    //     result += kd * light.intensity * nDotL + specular * light.intensity;
    //   }
    //   return result;
    // }
    // const Color getColor(const HitRecord &hitRecord) const override {
    //   Vec3 normal = unit_vector(hitRecord.normal);
    //   Color result(0, 0, 0);

    //   // Ensure viewDir points FROM the surface TOWARD the camera/viewer.
    //   // Adjust the sign depending on your ray tracer's HitRecord convention:
    //   Vec3 viewDir = unit_vector(-hitRecord.viewDirection);

    //   for (const PointLight &light : *hitRecord.lights) {
    //     // Direction from hit point to light source
    //     Vec3 l = unit_vector(light.position - hitRecord.point);

    //     // Diffuse factor (cosine of angle between N and L)
    //     double nDotL = std::max(0.0, dot(normal, l));

    //     // Calculate specular ONLY if the surface faces the light
    //     double specular = 0.0;
    //     if (nDotL > 0.0) {
    //       Vec3 halfVector = unit_vector(l + viewDir);
    //       double nDotH = std::max(0.0, dot(normal, halfVector));
    //       specular = std::pow(nDotH, shininess);
    //     }

    //     // Combine Diffuse + Specular (assuming white specular highlights)
    //     Color diffuseComponent = kd * light.intensity * nDotL;
    //     Color specularComponent = Color(1.0, 1.0, 1.0) * light.intensity * specular;

    //     result += diffuseComponent + specularComponent;
    //   }

    //   return result;
    // }

    const Color getColor(const HitRecord &hitRecord) const override {
      // return Color(255, 0, 0);
      Vec3 viewDir = unit_vector(-hitRecord.viewDirection);
      Color result = Color(0, 0, 0);

      for (const auto &light : *hitRecord.lights) {
        Vec3 lightDir = unit_vector(light.position - hitRecord.point);
        double diff = std::max(0.0, dot(lightDir, hitRecord.normal.normalized()));
        Vec3 halfDir = unit_vector(lightDir + viewDir);
        double specularity = std::pow(std::max(0.0, dot(hitRecord.normal.normalized(), halfDir)), shininess);
        result += light.intensity * (diff * color + specularity * specColor);
      }
      for (int i = 0; i < 3; ++i) {
        result[i] = std::min(1.0, result[i]);
      }
      return result;
    }

  private:
    Color color;
    Color specColor;
    float shininess;
};

#endif// BLINNPHONGSHADER_H
