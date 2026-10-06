#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"

class Sphere : public Shape {
  public:
    Sphere(const Point3 &center, double radius) : center(center), radius(radius), Shape(nullptr) {};
    Sphere(const Point3 &center, double radius, std::shared_ptr<Shader> shader) : center(center), radius(radius), Shape(shader) {};

    bool hit(const Ray &r, double ray_tmin, double ray_tmax, HitRecord &hitRecord) const override;

  public:
    Point3 center;
    double radius;
};

#endif// SPHERE_H
