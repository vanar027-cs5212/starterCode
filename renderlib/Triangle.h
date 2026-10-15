#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Shape.h"

class Triangle : public Shape {
  public:
    Triangle(const Point3 &a, const Point3 &b, const Point3 &c) : a(a), b(b), c(c), Shape(nullptr) {}
    Triangle(const Point3 &a, const Point3 &b, const Point3 &c, std::shared_ptr<Shader> shader) : a(a), b(b), c(c), Shape(shader) {}

    bool hit(const Ray &r, double ray_tmin, double ray_tmax, HitRecord &hitRecord) const override;

  private:
    // float a, b, c;
    Point3 a, b, c;
};

#endif// TRIANGLE_H
