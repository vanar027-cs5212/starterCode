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

    std::vector<std::shared_ptr<Shape>> getShapeList() const {
      return shapes;
    }

  private:
    std::vector<std::shared_ptr<Shape>> shapes;
};
