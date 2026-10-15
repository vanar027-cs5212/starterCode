#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <vector>
#include "Color.h"

class Framebuffer {

  public:
    Framebuffer(int width, int height);
    Framebuffer();

    int getWidth() const;
    int getHeight() const;
    int getLength() const;

    void clear();
    void clearToColor(const Color &color);
    void clearToGradient(const Color &gradientStart, const Color &gradientEnd);
    void clearToTricolor(const Color &c1, const Color &c2, const Color &c3, bool vertical = false);
    void clearToStripes(const std::vector<Color> &colors, bool vertical = false);
    void clearToStripes(const std::vector<Color> &colors, const std::vector<int> &stripeWidths, bool vertical = false);
    void clearToRepeatingStripes(const std::vector<Color> &colors, int stripeWidth, bool vertical = false);

    void setPixelColor(int x, int y, const Color &c);
    void setPixelColor(int idx, const Color &c);

    void exportAsPNG(const std::string &filename) const;

  private:
    std::vector<Color> fbStorage;
    int width, height;
};
#endif// FRAMEBUFFER_H
