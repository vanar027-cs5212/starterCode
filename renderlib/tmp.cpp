#include "Vec3.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Sphere.h"
#include <memory>

int main() {
  Framebuffer fb(600, 400);
  auto camera = new PerspectiveCamera(fb.getWidth(), fb.getHeight(), 1.f, 1.f);
  auto redSphere = std::make_shared<Sphere>(Point3(0, 0, -3), 3.f / 5.f);
  for (int y = 0; y < fb.getHeight(); ++y) {
    for (int x = 0; x < fb.getWidth(); ++x) {
      Ray r = camera->generateRay(x, y);
      HitRecord rec;
      if (redSphere->hit(r, 0.001, INFINITY, rec))
        fb.setPixelColor(x, y, Color(190, 33, 44));
      else
        fb.setPixelColor(x, y, Color(1.0f, 1.0f, 1.0f));
    }
  }
  fb.exportAsPNG("japanese_flag.png");
  return 0;
}
