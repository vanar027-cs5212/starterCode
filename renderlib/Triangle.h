#include "Shape.h"

class Triangle : public Shape {
  public:
    Triangle() {}
    // Triangle(float a, float b, float c) : a(a), b(b), c(c) {};
    Triangle(const Point3 &a, const Point3 &b, const Point3 &c) : a(a), b(b), c(c) {}

    bool hit(const Ray &r, double ray_tmin, double ray_tmax, HitRecord &hitRecord) const override;

  private:
    // float a, b, c;
    Point3 a, b, c;
};
