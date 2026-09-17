#include "Framebuffer.h"
#include <png++/png.hpp>

Framebuffer::Framebuffer() : Framebuffer(1000, 1000) {};

Framebuffer::Framebuffer(int width, int height) : width(width), height(height),
                                                  fbStorage(width * height) {}


int Framebuffer::getWidth() { return width; }

int Framebuffer::getHeight() { return height; }

int Framebuffer::getLength() { return width * height; }

void Framebuffer::clear() { clearToColor(color(0, 0, 0)); }

void Framebuffer::clearToColor(const color &clr) {
  for (int i = 0; i < fbStorage.size(); i++)
    setPixelColor(i, clr);
}

void Framebuffer::clearToGradient(const color &gradientStart, const color &gradientEnd) {
  for (int y = 0; y < height; y++) {
    float t = y / height;
    color clr = t * gradientStart + (1 - t) * gradientEnd;
    for (int x = 0; x < width; x++) setPixelColor(x, y, clr);
  }
}

// Set the color of a pixel at (i, j) in the framebuffer.
void Framebuffer::setPixelColor(int i, int j, const color &c) { fbStorage[j * width + i] = c; }

// Set the color of a pixel at the given index in the framebuffer.
void Framebuffer::setPixelColor(int idx, const color &c) { fbStorage[idx] = c; }

void Framebuffer::exportAsPNG(const std::string &filename) {
  png::image<png::rgb_pixel> imData(width, height);
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      color clr = fbStorage[i * width + j];

      png::byte r = static_cast<png::byte>(clr.x() * 255.0);
      png::byte g = static_cast<png::byte>(clr.y() * 255.0);
      png::byte b = static_cast<png::byte>(clr.z() * 255.0);

      imData[i][j] = png::rgb_pixel(r, g, b);
    }
  }
  imData.write(filename);
}
