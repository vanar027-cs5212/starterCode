#include <memory>

#include "Ray.h"
#include "Color.h"
#include "Shape.h"

class Shader {
  public:
    Shader() {};
    virtual const Color getColor(const Vec3 &) const = 0;
};

class NormalShader : public Shader {
  public:
    NormalShader() {};
    const Color getColor(const Vec3 &hitNormal) const override;
};

class SolidColor : public Shader {
  public:
    SolidColor() {};
    SolidColor(const Color &c) : color(c) {};

    const Color getColor(const Vec3 &) const override;

  private:
    Color color;
};
