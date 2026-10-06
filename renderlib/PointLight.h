#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include "Color.h"

struct PointLight {
    Point3 position;
    Color intensity = Color(1.0, 1.0, 1.0);
};

#endif// POINTLIGHT_H
