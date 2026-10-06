#include "Scene.h"
#include "Shader.h"
#include "NormalShader.h"

Scene Scene::addShape(std::shared_ptr<Shape> shape) {
  shapes.push_back(shape);
  return *this;
}

Scene Scene::addLight(const PointLight &light) {
  lights.push_back(light);
  return *this;
}

std::vector<std::shared_ptr<Shape>> Scene::getShapeList() const { return shapes; }

std::vector<PointLight> Scene::getLightList() const { return lights; }

bool Scene::hit(const Ray &r, double t_min, double t_max, HitRecord &hitRecord) const {
  HitRecord closestHit;
  closestHit.t = t_max;
  bool _hit = false;

  for (const auto &shape : shapes) {
    HitRecord tempHit;
    if (shape->hit(r, t_min, closestHit.t, tempHit)) {
      if (tempHit.t < closestHit.t) {
        _hit = true;
        closestHit = tempHit;
        closestHit.shape = shape.get();
      }
    }
  }
  hitRecord = closestHit;
  hitRecord.lights = &lights;

  return _hit;
}

Color Scene::computeRayColor(const Ray &r, int depth) const {
  float t_min = 0.001f;// Avoid self-intersection
  float t_max = std::numeric_limits<float>::max();// No upper limit for now

  HitRecord sceneHit;
  sceneHit.viewDirection = r.direction();
  printf("Scene::computeRayColor: viewDirection: %s\n", sceneHit.viewDirection.toString().c_str());

  if (!hit(r, t_min, t_max, sceneHit)) {// If no hit, return background color
    printf("Scene::computeRayColor: no hit, returning background color\n");
    Vec3 unitDirection = r.direction().normalized();
    double t = 0.5 * (unitDirection.y() + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);// Linear interpolation between white and light blue
  }

  std::shared_ptr<Shader> shader = sceneHit.shape->getShader();
  if (shader != nullptr) {
    return shader->getColor(sceneHit);
  }
  printf("using fallback");
  printf("sceneHit.viewDirection: %s\n", sceneHit.viewDirection.toString().c_str());
  NormalShader fallbackShader;
  return fallbackShader.getColor(sceneHit);
}

