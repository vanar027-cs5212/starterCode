#include <filesystem>
#include "Framebuffer.h"
#include "Camera.h"
#include "Sphere.h"
#include "Shader.h"
#include "Scene.h"
#include "Triangle.h"


using namespace std;

string fpath(const string &filename) { return filesystem::absolute(filename).string(); }

void createAnimation(Framebuffer &fb);
void visualizeRay(Framebuffer &fb, float focal_length, float viewport_width);
void drawSphere(Framebuffer &fb);
void drawOverlappingSpheres(Framebuffer &fb, const Color &innerClr, const Color &outerClr);
void drawStripes(Framebuffer &fb);
void drawFlag(Framebuffer &fb);
void drawScene(Framebuffer &fb);

int main(int argc, char **argv) {
  auto fb = Framebuffer(200, 200);
  cout << "Framebuffer size: " << fb.getWidth() << "x" << fb.getHeight() << endl;

  fb.clearToGradient(Color(1, 0, 0), Color(0, 0, 1));
  fb.exportAsPNG(fpath("output_gradient.png"));
  cout << "Gradient exported to " << fpath("output_gradient.png") << endl;
  fb.clearToColor(Color(0, 0, 0, 0));

  // createAnimation(fb);
  // drawSphere(fb);
  // drawOverlappingSpheres(fb, Color(0, 1, 0), Color(1, 0, 0));
  // drawStripes(fb);

  drawScene(fb);

  return 0;
}

void createAnimation(Framebuffer &fb) {
  float viewport_width = 0.1f;
  while (viewport_width <= 100.0f + 1e-5f) {
    visualizeRay(fb, 1.0f, viewport_width);
    string fp = fpath(std::format("rays/anim_rays_{:04.1f}.png", viewport_width));
    fb.exportAsPNG(fp);
    cout << "Framebuffer with rays exported to " << fp << endl;
    if (viewport_width < 5.0f)
      viewport_width += 0.1f;
    else
      viewport_width += 1.0f;
  }
}

void visualizeRay(Framebuffer &fb, float focal_length, float viewport_width) {
  Camera *rayCam = new PerspectiveCamera(fb.getWidth(), fb.getHeight(), viewport_width, focal_length);
  Shader *rayVis = new NormalShader();

  for (int y = 0; y < fb.getHeight(); ++y) {
    for (int x = 0; x < fb.getWidth(); ++x) {
      Ray r = rayCam->generateRay(x, y);
      fb.setPixelColor(x, y, rayVis->getColor(r.direction()));
    }
  }
}

void drawSphere(Framebuffer &fb) {
  Camera *sphereCam = new PerspectiveCamera(fb.getWidth(), fb.getHeight(), 1.0f, 1.0f);

  std::shared_ptr<Shape>
    s = std::make_shared<Sphere>(Point3(0, 0, -5), 1.0);
  Shader *sphereShader = new SolidColor(Color(1, 0, 1));
  for (int y = 0; y < fb.getHeight(); ++y) {
    for (int x = 0; x < fb.getWidth(); ++x) {
      Ray r = sphereCam->generateRay(x, y);
      HitRecord hr = HitRecord();

      if (s->hit(r, 0.001, std::numeric_limits<double>::infinity(), hr)) {
        fb.setPixelColor(x, y, sphereShader->getColor(r.direction()));
      }
    }
  }


  fb.exportAsPNG(fpath("output_sphere.png"));
  cout << "Framebuffer with sphere exported to " << fpath("output_sphere.png") << endl;
}

void drawOverlappingSpheres(Framebuffer &fb, const Color &innerClr, const Color &outerClr) {
  Camera *sphereCam = new PerspectiveCamera(fb.getWidth(), fb.getHeight(), 1.0f, 1.0f);
  fb.clearToColor(innerClr);
  Sphere *outerSphere = new Sphere(Point3(0, 0, -5), 1.7);
  Sphere *innerSphere = new Sphere(Point3(0, 0, -5), 1.3);
  Shader *outerShader = new SolidColor(Color(outerClr));
  Shader *innerShader = new SolidColor(Color(innerClr));
  for (int y = 0; y < fb.getHeight(); ++y) {
    for (int x = 0; x < fb.getWidth(); ++x) {
      Ray r = sphereCam->generateRay(x, y);
      HitRecord hr = HitRecord();

      if (innerSphere->hit(r, 0.001, std::numeric_limits<double>::infinity(), hr))
        fb.setPixelColor(x, y, innerShader->getColor(r.direction()));
      else if (outerSphere->hit(r, 0.001, std::numeric_limits<double>::infinity(), hr))
        fb.setPixelColor(x, y, outerShader->getColor(r.direction()));
    }
  }
  fb.exportAsPNG(fpath("output_sphere_overlap.png"));
  cout << "Framebuffer with overlapping spheres exported to " << fpath("output_sphere_overlap.png") << endl;
}

void drawStripes(Framebuffer &fb) {
  fb.clearToStripes({ Color(254, 99, 1), Color(254, 150, 90), Color(255, 255, 255), Color(225, 97, 158), Color(138, 7, 47) });
  fb.exportAsPNG(fpath("output_stripes.png"));
  cout << "Framebuffer with stripes exported to " << fpath("output_stripes.png") << endl;

  fb.clearToStripes({ Color(206, 17, 38), Color(0, 40, 104), Color(206, 17, 38) }, { 225, 350, 225 });
  fb.exportAsPNG(fpath("output_repeating_stripes.png"));
  cout << "Framebuffer with repeating stripes exported to " << fpath("output_repeating_stripes.png") << endl;
}

void drawFlag(Framebuffer &fb) {
  Camera *cam = new PerspectiveCamera(fb.getWidth(), fb.getHeight(), 1.0f, 1.0f);
  Sphere *flagSphere = new Sphere(Point3(0, 0, -7), 1.0);
  Shader *flagShader = new SolidColor(Color(1.f, 1.f, 1.f));
  for (int y = 0; y < fb.getHeight(); ++y) {
    for (int x = 0; x < fb.getWidth(); ++x) {
      Ray r = cam->generateRay(x, y);
      HitRecord hr = HitRecord();

      if (flagSphere->hit(r, 0.001, std::numeric_limits<double>::infinity(), hr)) {
        fb.setPixelColor(x, y, flagShader->getColor(r.direction()));
      }
    }
  }
  fb.exportAsPNG(fpath("output_flag_sphere.png"));
  cout << "Framebuffer with flag sphere exported to " << fpath("output_flag_sphere.png") << endl;
}

void drawScene(Framebuffer &fb) {
  Camera *cam = new PerspectiveCamera(fb.getWidth(), fb.getHeight(), 1.0f, 1.0f);
  fb.clearToColor(Color(.1f, .6f, .3f));
  Scene testScene = Scene()
                      .addShape(std::make_shared<Sphere>(Point3(0, 0, -5), 1.5))
                      .addShape(std::make_shared<Sphere>(Point3(1, 0, -5), 0.75))
                      .addShape(std::make_shared<Sphere>(Point3(-2, 0, -5), 0.75))
                      .addShape(std::make_shared<Triangle>(Point3(-1, -1, -4), Point3(1, -1, -4), Point3(0, 1, -4)));
  NormalShader sh;
  for (int y = 0; y < fb.getHeight(); ++y) {
    for (int x = 0; x < fb.getWidth(); ++x) {
      Ray r = cam->generateRay(x, y);
      HitRecord hr = HitRecord();

      if (testScene.hit(r, 0.001, std::numeric_limits<double>::infinity(), hr)) {
        Color c = sh.getColor(hr.normal);
        fb.setPixelColor(x, y, c);
      }
    }
  }
  fb.exportAsPNG(fpath("output_scene.png"));
  cout << "Framebuffer with scene exported to " << fpath("output_scene.png") << endl;
}
