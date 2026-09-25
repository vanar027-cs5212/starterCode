#include "Shape.h"

class Triangle : public Shape {
  public:
    Triangle() {}
    Triangle(float a, float b, float c) : a(a), b(b), c(c) {};

    bool hit(const Ray &r, double ray_tmin, double ray_tmax, HitRecord &rec) const override;

  private:
    float a, b, c;
};
