#include <filesystem>
#include "Framebuffer.h"
#include "Camera.h"
#include "Sphere.h"
#include "Shader.h"


using namespace std;

string fpath(const string &filename) { return filesystem::absolute(filename).string(); }

void raytraceImg(Framebuffer &fb, float focal_length, float viewport_width) {
  Camera *rayCam = new PerspectiveCamera(fb.getWidth(), fb.getHeight(), viewport_width, focal_length);
  Shader *rayVis = new RayVisualizer();

  for (int y = 0; y < fb.getHeight(); ++y) {
    for (int x = 0; x < fb.getWidth(); ++x) {
      Ray r = rayCam->generateRay(x, y);
      fb.setPixelColor(x, y, rayVis->getColor(r));
    }
  }
}
float step(float current) {
  if (current < 5.0f)
    return 0.1f;
  else// if (current < 50.0f)
    return 1.0f;
  // else
  // return 5.0f;
}

int main(int argc, char **argv) {
  Framebuffer fb(800, 800);

  cout << "Framebuffer size: " << fb.getWidth() << "x" << fb.getHeight() << endl;

  fb.clearToGradient(Color(1, 0, 0), Color(0, 0, 1));

  fb.exportAsPNG(fpath("output_gradient.png"));
  cout << "Gradient exported to " << fpath("output_gradient.png") << endl;


  float viewport_width = 0.1f;
  while (viewport_width <= 100.0f + 1e-5f) {
    raytraceImg(fb, 1.0f, viewport_width);
    string fp = fpath(std::format("rays/anim_rays_{:04.1f}.png", viewport_width));
    fb.exportAsPNG(fp);
    cout << "Framebuffer with rays exported to " << fp << endl;
    viewport_width += step(viewport_width);
  }
  // Camera *rayCam = new PerspectiveCamera(fb.getWidth(), fb.getHeight(), 100.0f, 1.0f);
  // Shader *rayVis = new RayVisualizer();

  // for (int y = 0; y < fb.getHeight(); ++y) {
  //   for (int x = 0; x < fb.getWidth(); ++x) {
  //     Ray r = rayCam->generateRay(x, y);
  //     fb.setPixelColor(x, y, rayVis->getColor(r));
  //   }
  // }

  // fb.exportAsPNG(fpath("output_rays.png"));
  // cout << "Framebuffer with rays exported to " << fpath("output_rays.png") << endl;

  // fb.clear();
  fb.clearToColor(Color(0, 0, 0, 0));

  Camera *sphereCam = new PerspectiveCamera(fb.getWidth(), fb.getHeight(), 1.0f, 1.0f);

  std::shared_ptr<Shape>
    s = std::make_shared<Sphere>(Point3(0, 0, -5), 1.0);
  Shader *sphereShader = new SolidColor(Color(1, 0, 1));
  for (int y = 0; y < fb.getHeight(); ++y) {
    for (int x = 0; x < fb.getWidth(); ++x) {
      Ray r = sphereCam->generateRay(x, y);
      HitRecord hr = HitRecord();

      if (s->hit(r, 0.001, std::numeric_limits<double>::infinity(), hr)) {
        fb.setPixelColor(x, y, sphereShader->getColor(r));
      }
    }
  }

  fb.exportAsPNG(fpath("output_sphere.png"));
  cout << "Framebuffer with sphere exported to " << fpath("output_sphere.png") << endl;


  return 0;
}
