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
    std::cout << "Clearing framebuffer to gradient: " << (y + 1) << "/" << height << " rows completed.\r" << std::flush;
    float t = height > 1 ? static_cast<float>(y) / (height - 1) : 0.0f;
    Color clr = (1 - t) * gradientStart + t * gradientEnd;
    for (int x = 0; x < width; x++) setPixelColor(x, y, clr);
  }
  std::cout << std::endl
            << "done" << std::endl;
}

void Framebuffer::clearToStripes(const std::vector<Color> &colors, bool vertical) {
  int numColors = colors.size();
  if (numColors == 0) return;

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      int position = vertical ? x : y;
      int dimension = vertical ? width : height;
      int stripeIndex = position * numColors / dimension;
      setPixelColor(x, y, colors[stripeIndex]);
    }
  }
}

void Framebuffer::clearToStripes(const std::vector<Color> &colors, const std::vector<int> &stripeWidths, bool vertical) {
  int numColors = colors.size();
  int numWidths = stripeWidths.size();
  if (numColors == 0 || numWidths == 0) return;

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      int position = vertical ? x : y;
      // int dimension = vertical ? width : height;

      // Calculate the total width of all stripes
      int totalWidth = 0;
      for (int w : stripeWidths) totalWidth += w;

      // Determine the current position within the repeating pattern
      int posInPattern = position % totalWidth;

      // Find the corresponding stripe index based on the widths
      int accumulatedWidth = 0;
      int stripeIndex = 0;
      for (int i = 0; i < numWidths; i++) {
        accumulatedWidth += stripeWidths[i];
        if (posInPattern < accumulatedWidth) {
          stripeIndex = i % numColors;// Wrap around if more widths than colors
          break;
        }
      }

      setPixelColor(x, y, colors[stripeIndex]);
    }
  }
}

void Framebuffer::clearToRepeatingStripes(const std::vector<Color> &colors, int stripeWidth, bool vertical) {
  int numColors = colors.size();
  if (numColors == 0 || stripeWidth <= 0) return;

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      int stripeIndex = (vertical ? x : y) / stripeWidth;
      setPixelColor(x, y, colors[stripeIndex % numColors]);
    }
  }
}

// Set the color of a pixel at (x, y) in the framebuffer.
void Framebuffer::setPixelColor(int x, int y, const Color &c) { fbStorage[y * width + x] = c; }

// Set the color of a pixel at the given index in the framebuffer.
void Framebuffer::setPixelColor(int idx, const Color &c) { fbStorage[idx] = c; }

void Framebuffer::exportAsPNG(const std::string &filename) const {
  png::image<png::rgba_pixel> imData(width, height);
  int i = 0;
  for (Color clr : fbStorage) {
    // printf("Framebuffer pixel color: @ fbStorage[%d] = %s\n", i++, clr.toString().c_str());
  }
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      // printf("Exporting framebuffer to PNG: %d/%d pixels completed.\n", y * width + x, width * height);
      Color clr = fbStorage[y * width + x];
      // printf("clr: %s", clr.toString().c_str());
      png::byte r = static_cast<png::byte>(clr.x() * 255.0);
      // printf("r: %d\n", r);
      png::byte g = static_cast<png::byte>(clr.y() * 255.0);
      // printf("g: %d\n", g);
      png::byte b = static_cast<png::byte>(clr.z() * 255.0);
      // printf("b: %d\n", b);
      png::byte a = static_cast<png::byte>(clr.a() * 255.0);
      // printf("a: %d\n", a);
      // printf("imData[%d][%d] = png::rgba_pixel(%d, %d, %d, %d)\n", x, y, r, g, b, a);
      imData[y][x] = png::rgba_pixel(r, g, b, a);
    }
  }
  imData.write(filename);
}
