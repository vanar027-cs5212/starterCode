#ifndef SOLIDSHADER_H
#define SOLIDSHADER_H
#include "Shader.h"

class SolidShader : public Shader {
  public:
    SolidShader() {};
    SolidShader(const Color &c) : color(c) {};

    const Color getColor(const HitRecord &) const override { return color; };


  private:
    Color color;
};

#endif// SOLIDSHADER_H
