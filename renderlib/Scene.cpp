#include <random>
#include "Scene.h"
#include "NormalShader.h"
#include "Shader.h"

Scene *Scene::addShape(std::shared_ptr<Shape> shape) {
  shapes.push_back(shape);
  return this;
}

Scene *Scene::addLight(const PointLight &light) {
  lights.push_back(light);
  return this;
}

Scene *Scene::setAntialiasSampleCount(int count) {
  antialias_sample_count = count;
  return this;
}

std::vector<std::shared_ptr<Shape>> Scene::getShapeList() const {
  return shapes;
}

std::vector<PointLight> Scene::getLightList() const { return lights; }

int Scene::getAntialiasSampleCount() const {
  return antialias_sample_count;
}

bool Scene::hit(const Ray &r, double t_min, double t_max, HitRecord &hitRecord) const {
  // printf("n shapes: %zu, n lights: %zu\n", shapes.size(), lights.size());
  HitRecord closestHit;
  closestHit.t = t_max;
  bool _hit = false;

  for (const auto &shape : shapes) {
    HitRecord tempHit;
    // printf("checking hit for shape: %p, ray: origin: %s, direction: %s\n",
    // shape.get(), r.origin().toString().c_str(),
    // r.direction().toString().c_str());
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

Color Scene::computeRayColor(const Ray &r, int depth = 1) const {
  if (depth <= 0) {
    return bgColor;
  }

  float t_min = 0.001f;// Avoid self-intersection
  float t_max = std::numeric_limits<float>::max();// No upper limit for now

  HitRecord sceneHit;
  if (!hit(r, t_min, t_max, sceneHit)) {// If no hit, return background color
    /*
    // TODO: customizable gradient background?
    Vec3 unitDirection = r.direction().normalized();
    double t = 0.5 * (unitDirection.y() + 1.0);
    // Linear interpolation between white and light blue
    return (1.0 - t) * Color(1.f, 1.f, 1.f) + t * Color(0.5, 0.7, 1.0);*/
    return bgColor;
  }
  std::shared_ptr<Shader> shader = sceneHit.shape->getShader();
  if (shader != nullptr) {
    return shader->getColor(sceneHit);
  }
  NormalShader fallbackShader;
  return fallbackShader.getColor(sceneHit);
}


float randomOffset() {
  static std::uniform_real_distribution<double> distribution(0.0, 1.0);
  static std::mt19937 generator;
  return distribution(generator);
}

void Scene::render(Framebuffer &fb, Camera *cam, int maxDepth = 1) const {
#pragma omp parallel for
  for (int y = 0; y < fb.getHeight(); ++y) {
    for (int x = 0; x < fb.getWidth(); ++x) {
      Color c(0.f, 0.f, 0.f);
      for (int p = 0; p < antialias_sample_count; ++p) {
        for (int q = 0; q < antialias_sample_count; ++q) {

          float pOffset = (p + randomOffset()) / antialias_sample_count;
          float qOffset = (q + randomOffset()) / antialias_sample_count;

          Ray r = cam->generateRay(x + pOffset, y + qOffset);
          c += computeRayColor(r, 0);
        }
      }
      c /= (antialias_sample_count * antialias_sample_count);

      // printf("Color: %f, %f, %f\n", c.x(), c.y(), c.z());
      fb.setPixelColor(x, y, c);
    }
  }
}
