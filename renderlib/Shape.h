#ifndef SHAPE_H
#define SHAPE_H

#include "Ray.h"

struct HitRecord {
    Point3 p;// the point in space where the ray hit
    Vec3 normal;// the surface normal at the hit point
    double t;// the ray parameter at which the hit occurred
};

// Abstract base class for anything a ray can intersect.
class Shape {
  public:
    // Returns true if r hits this shape for some t in [t_min, t_max].
    // On a hit, fills in rec with the closest such intersection.
    virtual bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const = 0;
};

#endif// SHAPE_H
