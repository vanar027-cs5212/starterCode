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
    Color(float r, float g, float b) : Color(r, g, b, 1.0f) {}
    Color(double r, double g, double b, double a) : Color(static_cast<float>(r), static_cast<float>(g), static_cast<float>(b), static_cast<float>(a)) {}
    Color(double r, double g, double b) : Color(static_cast<float>(r), static_cast<float>(g), static_cast<float>(b), 1.0f) {}
    Color(int r, int g, int b, float a) : Color(r / 255.0f, g / 255.0f, b / 255.0f, a) {}
    Color(int r, int g, int b) : Color(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f) {}
    Color() : Color(0, 0, 0, 1.0f) {}


    float a() const { return alpha; }

    std::string toString() const {
      return "(" + std::to_string(x()) + ", " + std::to_string(y()) + ", " + std::to_string(z()) + ", " + std::to_string(a()) + ")";
    }

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
