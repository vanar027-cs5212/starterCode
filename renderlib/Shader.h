#ifndef SHADER_H
#define SHADER_H

#include "Color.h"
#include "Shape.h"
struct HitRecord;
class Shader {
  public:
    Shader() {};
    virtual const Color getColor(const HitRecord &hitRecord) const = 0;
};

#endif// SHADER_H
