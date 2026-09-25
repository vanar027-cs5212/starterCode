#ifndef COLOR_H
#define COLOR_H 1

#include "Vec3.h"
#include <iostream>

class Color : public Vec3 {
  public:
    // Inherit assignment operators from Vec3
    using Vec3::operator=;

    Color(const Vec3 &v, float a) : Vec3(v), alpha(a) {}
    // Allow implicit conversion from Vec3 to Color
    Color(const Vec3 &v) : Color(v, 1.0f) {}

    Color(float r, float g, float b, float a) : Color(Vec3(r, g, b), a) {}
    Color(float r, float g, float b) : Color(Vec3(r, g, b), 1.0f) {}
    Color() : Color(Vec3(0, 0, 0), 1.0f) {}


    float a() const { return alpha; }

  private:
    float alpha;
};

inline void
  write_color(std::ostream &out, const Color &pixel_color) {
  auto r = pixel_color.x();
  auto g = pixel_color.y();
  auto b = pixel_color.z();

  // Translate the [0,1] component values to the byte range [0,255].
  int rbyte = int(255.999 * r);
  int gbyte = int(255.999 * g);
  int bbyte = int(255.999 * b);

  // Write out the pixel color components.
  out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif
