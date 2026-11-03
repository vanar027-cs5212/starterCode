#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>
#include "Shape.h"
#include "Framebuffer.h"
#include "Camera.h"


class Scene {
  public:
    Scene() : bgColor(0, 0, 0, 1) {}
    Scene(const Color &bgColor) : bgColor(bgColor) {}

    Scene *addShape(std::shared_ptr<Shape> shape);
    Scene *addLight(const PointLight &light);
    Scene *setAntialiasSampleCount(int count);

    std::vector<std::shared_ptr<Shape>> getShapeList() const;
    std::vector<PointLight> getLightList() const;
    int getAntialiasSampleCount() const;

    bool hit(const Ray &r, double t_min, double t_max, HitRecord &hitRecord) const;
    Color computeRayColor(const Ray &r, int depth = 1) const;
    void render(Framebuffer &fb, Camera *cam, int maxDepth = 1) const;

  private:
    Color bgColor;
    std::vector<std::shared_ptr<Shape>> shapes;
    std::vector<PointLight> lights;
    int antialias_sample_count = 4;
};

#endif// SCENE_H
