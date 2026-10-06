#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include "Color.h"

struct PointLight {
    Point3 position;
    Color intensity = Color(1.f, 1.f, 1.f, 1.f);

    PointLight(const Point3 &position, const Color &intensity) : position(position), intensity(intensity) {}
};

#endif// POINTLIGHT_H
