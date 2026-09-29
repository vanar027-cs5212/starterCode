#include <vector>
#include "Shape.h"
#include <memory>

class Scene {
  public:
    Scene() {}

    Scene addShape(std::shared_ptr<Shape> shape) {
      shapes.push_back(shape);
      return *this;
    }

    std::vector<std::shared_ptr<Shape>> getShapeList() const { return shapes; }

    bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const {
      double closestDistance = t_max;
      Shape *closestShape = nullptr;

      for (const auto &shape : shapes) {
        if (shape->hit(r, t_min, closestDistance, rec)) {
          closestDistance = rec.t;
          closestShape = shape.get();
        }
      }

      return closestShape != nullptr;
    }

  private:
    std::vector<std::shared_ptr<Shape>> shapes;
};
