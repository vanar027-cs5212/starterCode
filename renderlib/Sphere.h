#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"

class Sphere : public Shape {
  public:
    Sphere() {}
    Sphere(const Point3 &center, double radius) : center(center), radius(radius) {};

    bool hit(const Ray &r, double ray_tmin, double ray_tmax, HitRecord &rec) const override;

  public:
    Point3 center;
    double radius;
};

#endif// SPHERE_H
