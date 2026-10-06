#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <memory>
#include "Vec3.h"
#include "PointLight.h"
#include "Shader.h"
#include "Ray.h"

class Shape;

struct HitRecord {
    Point3 point;// the point in space where the ray hit
    Vec3 normal;// the surface normal at the hit point
    double t;// the ray parameter at which the hit occurred
    Vec3 viewDirection;// the direction of the incoming ray

    const Shape *shape = nullptr;// TODO: why on earth can i not make this a shared_ptr
    const std::vector<PointLight> *lights = nullptr;
};

// Abstract base class for anything a ray can intersect.
class Shape {
  public:
    // Returns true if r hits this shape for some t in [t_min, t_max].
    // On a hit, fills in hitRecord record with the closest such intersection.
    virtual bool hit(const Ray &r, double t_min, double t_max, HitRecord &hitRecord) const = 0;

    std::shared_ptr<Shader> getShader() const { return shader; }

  protected:
    std::shared_ptr<Shader> shader = nullptr;
};

#endif// SHAPE_H
