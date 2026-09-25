#include <memory>

#include "Ray.h"
#include "Color.h"
#include "Shape.h"

class Shader {
  public:
    Shader() {};
    virtual const Color getColor(const Ray &r) const = 0;
};

class RayVisualizer : public Shader {
  public:
    RayVisualizer() {};
    const Color getColor(const Ray &r) const override;
};

class SolidColor : public Shader {
  public:
    SolidColor() {};
    SolidColor(const Color &c) : color(c) {};

    const Color getColor(const Ray &r) const override;

  private:
    Color color;
};
