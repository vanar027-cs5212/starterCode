#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H 1

#include <vector>
#include "color.h"

class Framebuffer {

  public:
    Framebuffer(int w, int h);
    Framebuffer();

    int getWidth();
    int getHeight();
    int getLength();

    void clear();
    void clearToColor(const color &color);
    void clearToGradient(const color &gradientStart, const color &gradientEnd);
    void clearToTricolor(const color &c1, const color &c2, const color &c3, bool vertical = true);

    void setPixelColor(int i, int j, const color &c);
    void setPixelColor(int idx, const color &c);

    void exportAsPNG(const std::string &filename);

  private:
    std::vector<color> fbStorage;
    int width, height;
};
#endif// FRAMEBUFFER_H
