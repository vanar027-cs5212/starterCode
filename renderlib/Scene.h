#include <vector>
#include <memory>
#include "Shape.h"

class Scene {
  public:
    Scene() {}

    Scene addShape(std::shared_ptr<Shape> shape);
    Scene addLight(const PointLight &light);

    std::vector<std::shared_ptr<Shape>> getShapeList() const;
    std::vector<PointLight> getLightList() const;

    bool hit(const Ray &r, double t_min, double t_max, HitRecord &hitRecord) const;
    Color computeRayColor(const Ray &r, int depth) const;

  private:
    std::vector<std::shared_ptr<Shape>> shapes;
    std::vector<PointLight> lights;
};
