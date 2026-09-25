#include "Framebuffer.h"
#include <png++/png.hpp>

Framebuffer::Framebuffer() : Framebuffer(1000, 1000) {};

Framebuffer::Framebuffer(int width, int height) : width(width), height(height),
                                                  fbStorage(width * height) {}


int Framebuffer::getWidth() const { return width; }

int Framebuffer::getHeight() const { return height; }

int Framebuffer::getLength() const { return width * height; }

void Framebuffer::clear() { clearToColor(Color(0, 0, 0)); }

void Framebuffer::clearToColor(const Color &clr) {
  for (int pxl = 0; pxl < fbStorage.size(); pxl++)
    setPixelColor(pxl, clr);
}

void Framebuffer::clearToGradient(const Color &gradientStart, const Color &gradientEnd) {
  for (int y = 0; y < height; y++) {
    float t = height > 1 ? static_cast<float>(y) / (height - 1) : 0.0f;
    Color clr = (1 - t) * gradientStart + t * gradientEnd;
    for (int x = 0; x < width; x++) setPixelColor(x, y, clr);
  }
}

// Set the color of a pixel at (x, y) in the framebuffer.
void Framebuffer::setPixelColor(int x, int y, const Color &c) { fbStorage[y * width + x] = c; }

// Set the color of a pixel at the given index in the framebuffer.
void Framebuffer::setPixelColor(int idx, const Color &c) { fbStorage[idx] = c; }

void Framebuffer::exportAsPNG(const std::string &filename) const {
  png::image<png::rgba_pixel> imData(width, height);
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      Color clr = fbStorage[y * width + x];

      png::byte r = static_cast<png::byte>(clr.x() * 255.0);
      png::byte g = static_cast<png::byte>(clr.y() * 255.0);
      png::byte b = static_cast<png::byte>(clr.z() * 255.0);
      png::byte a = static_cast<png::byte>(clr.a() * 255.0);

      imData[x][y] = png::rgba_pixel(r, g, b, a);
    }
  }
  imData.write(filename);
}
