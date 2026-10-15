#include <filesystem>
#include <format>
#include "Framebuffer.h"
#include "Camera.h"
#include "Sphere.h"
#include "Shader.h"
#include "Scene.h"
#include "Triangle.h"
#include "SolidShader.h"
#include "NormalShader.h"
#include "LambertianShader.h"
#include "BlinnPhongShader.h"


using namespace std;

string fpath(const string &filename) { return filesystem::absolute(filename).string(); }

void createAnimation(Framebuffer &fb);
void visualizeRay(Framebuffer &fb, float focal_length, float viewport_width);
void drawSphere(Framebuffer &fb);
void drawOverlappingSpheres(Framebuffer &fb, const Color &innerClr, const Color &outerClr);
void drawStripes(Framebuffer &fb);
void drawFlag(Framebuffer &fb);
void drawScene(Framebuffer &fb);
void zach();
void aaa();

int main(int argc, char **argv) {
  auto fb = Framebuffer(200, 200);
  cout << "Framebuffer size: " << fb.getWidth() << "x" << fb.getHeight() << endl;

  fb.clearToGradient(Color(1.f, 0.f, 0.f), Color(0.f, 0.f, 1.f));
  fb.exportAsPNG(fpath("output_gradient.png"));
  cout << "Gradient exported to " << fpath("output_gradient.png") << endl;
  fb.clearToColor(Color(0, 0, 0, 0));
  visualizeRay(fb, 100.f, 1.f);
  fb.exportAsPNG(fpath("output_rays.png"));
  // createAnimation(fb);
  drawSphere(fb);
  drawOverlappingSpheres(fb, Color(0.f, 1.f, 0.f), Color(1.f, 0.f, 0.f));
  // drawStripes(fb);

  // drawScene(fb);

  // zach();
  aaa();

  return 0;
}

void createAnimation(Framebuffer &fb) {
  float viewport_width = 0.1f;
  while (viewport_width <= 100.0f + 1e-5f) {
    visualizeRay(fb, viewport_width, 1.0f);
    string fp = fpath(format("rays/anim_rays_{:04.1f}.png", viewport_width));
    fb.exportAsPNG(fp);
    cout << "Framebuffer with rays exported to " << fp << endl;
    if (viewport_width < 5.0f)
      viewport_width += 0.1f;
    else
      viewport_width += 1.0f;
  }
}

void visualizeRay(Framebuffer &fb, float viewport_width, float focal_length) {
  auto *rayCam = new PerspectiveCamera(fb.getWidth(), fb.getHeight(), viewport_width, focal_length);
  auto *rayVis = new NormalShader();

  for (int y = 0; y < fb.getHeight(); ++y) {
    for (int x = 0; x < fb.getWidth(); ++x) {
      Ray r = rayCam->generateRay(x, y);
      fb.setPixelColor(x, y, rayVis->getColor(r.direction()));
    }
  }
}

void drawSphere(Framebuffer &fb) {
  Camera *sphereCam = new PerspectiveCamera(fb.getWidth(), fb.getHeight(), 1.0f, 1.0f);

  shared_ptr<Shape>
    s = make_shared<Sphere>(Point3(0, 0, -5), 1.0);
  Shader *sphereShader = new SolidShader(Color(1.f, 0.f, 1.f));
  for (int y = 0; y < fb.getHeight(); ++y) {
    for (int x = 0; x < fb.getWidth(); ++x) {
      Ray r = sphereCam->generateRay(x, y);
      HitRecord hr = HitRecord();

      if (s->hit(r, 0.001, numeric_limits<double>::infinity(), hr)) {
        fb.setPixelColor(x, y, sphereShader->getColor(hr));
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
  Shader *outerShader = new SolidShader(Color(outerClr));
  Shader *innerShader = new SolidShader(Color(innerClr));
  for (int y = 0; y < fb.getHeight(); ++y) {
    for (int x = 0; x < fb.getWidth(); ++x) {
      Ray r = sphereCam->generateRay(x, y);
      HitRecord hr = HitRecord();

      if (innerSphere->hit(r, 0.001, numeric_limits<double>::infinity(), hr))
        fb.setPixelColor(x, y, innerShader->getColor(hr));
      else if (outerSphere->hit(r, 0.001, numeric_limits<double>::infinity(), hr))
        fb.setPixelColor(x, y, outerShader->getColor(hr));
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
  Shader *flagShader = new SolidShader(Color(1.f, 1.f, 1.f));
  for (int y = 0; y < fb.getHeight(); ++y) {
    for (int x = 0; x < fb.getWidth(); ++x) {
      Ray r = cam->generateRay(x, y);
      HitRecord hr = HitRecord();

      if (flagSphere->hit(r, 0.001, numeric_limits<double>::infinity(), hr)) {
        fb.setPixelColor(x, y, flagShader->getColor(hr));
      }
    }
  }
  fb.exportAsPNG(fpath("output_flag_sphere.png"));
  cout << "Framebuffer with flag sphere exported to " << fpath("output_flag_sphere.png") << endl;
}

void drawScene(Framebuffer &fb) {
  Camera *cam = new PerspectiveCamera(fb.getWidth(), fb.getHeight(), 1.0f, 1.0f);
  fb.clearToColor(Color(.1f, .6f, .3f));
  // printf("clearToColor: %s\n", Color(.1f, .6f, .3f).toString().c_str());
  Scene *testScene = new Scene();
  testScene
    ->addShape(make_shared<Sphere>(Point3(0, 0, -5), 1.5))
    // .addShape(make_shared<Sphere>(Point3(1, 0, -5), 0.75))
    // .addShape(make_shared<Sphere>(Point3(-2, 0, -5), 0.75))
    // .addShape(make_shared<Triangle>(Point3(-1, -1, -4), Point3(1, -1, -4), Point3(0, 1, -4)));
    ->addLight(PointLight(Point3(5, 5, 0), Color(1.f, 1.f, 1.f)));
  vector<shared_ptr<Shape>> shapes = testScene->getShapeList();
  shapes[0]->setShader(make_shared<BlinnPhongShader>(Color(1.f, 0.f, 0.f), 1.f));
  // shapes[0]->setShader(make_shared<BlinnPhongShader>(Color(1.f, 1.f, 0.f), 32));
  printf("Scene created with %zu shapes and %zu lights\n", testScene->getShapeList().size(), testScene->getLightList().size());

  for (int y = 0; y < fb.getHeight(); ++y) {
    for (int x = 0; x < fb.getWidth(); ++x) {
      // printf("Generating ray for pixel x: %d, y: %d\n", x, y);
      Ray r = cam->generateRay(x, y);
      // printf("x: %d, y: %d, ray origin: %s, ray direction: %s\n", x, y, r.origin().toString().c_str(), r.direction().toString().c_str());
      // printf("Computing color for pixel x: %d, y: %d\n", x, y);
      Color c = testScene->computeRayColor(r, 0);
      // printf("x: %d, y: %d, computed color: %s\n", x, y, c.toString().c_str());
      fb.setPixelColor(x, y, c);
      // printf("succeeded x: %d, y: %d, color: %s\n", x, y, c.toString().c_str());
    }
  }
  fb.exportAsPNG(fpath("output_scene.png"));
  cout << "Framebuffer with scene exported to " << fpath("output_scene.png") << endl;
}

void zach() {
  Framebuffer fb(2000, 2000);
  // Vec3 viewdir(0, -.3, 1);
  // Point3 origin(0, 2, 1);
  double ipw = 1, fl = 1;
  // auto p = PerspectiveCamera(origin, Vec3(1, 0, 0), Vec3(0, 1, 0), viewdir, fb.getWidth(), fb.getHeight(), ipw, fl);
  auto p = PerspectiveCamera(fb.getWidth(), fb.getHeight(), ipw, fl);

  Color sphereClr(0.f, .8f, .8f);
  auto matte = make_shared<LambertianShader>(sphereClr);
  auto satin = make_shared<BlinnPhongShader>(sphereClr, Color(.6f, .6f, .6f), 16);
  auto glossy = make_shared<BlinnPhongShader>(sphereClr, 200);

  auto floorShader = make_shared<LambertianShader>(Color(.5f, .5f, .5f));

  auto warmLight = PointLight(Point3(4, 4, 0), Color(1.f, .85f, .7f));
  auto coolLight = PointLight(Point3(-4, 2, -1), Color(.4f, .6f, 1.f));

  Scene *scene = new Scene();
  scene
    // .addLight(warmLight)
    //   .addLight(coolLight)
    // .addShape(make_shared<Sphere>(Point3(0, -100.5, -5), 100, floorShader))
    // .addShape(make_shared<Sphere>(Point3(-1.2, 0, -4), 0.5, matte))
    // .addShape(make_shared<Sphere>(Point3(0, 0, -4), 0.5, satin))
    // .addShape(make_shared<Sphere>(Point3(1.2, 0, -4), 0.5, glossy));

    ->addShape(make_shared<Sphere>(Point3(0, -100.5, -5), 100))
    ->addShape(make_shared<Sphere>(Point3(-1.2, 0, -4), 5))
    ->addShape(make_shared<Sphere>(Point3(0, 0, -4), 5))
    ->addShape(make_shared<Sphere>(Point3(1.2, 0, -4), 5));

  scene->render(fb, p, 0);

  fb.exportAsPNG(fpath("output_zach.png"));
  printf("Framebuffer with zach scene exported to %s\n", fpath("output_zach.png").c_str());
}

void aaa() {
  Framebuffer fb(2000, 2000);
  auto p = PerspectiveCamera(fb.getWidth(), fb.getHeight(), 1.0f, 1.0f);
  Scene *scene = new Scene();
  scene
    ->addLight(PointLight(Point3(1000, 1000, 1000), Color(1.f, 1.f, 1.f)))
    ->addShape(make_shared<Sphere>(Point3(0, 0, -5), 1.5, make_shared<LambertianShader>(Color(1.f, 0.f, 0.f))));//, Color(1.f, 1.f, 1.f), 1.f)));
  printf("Created scene with %zu shapes and %zu lights\n", scene->getShapeList().size(), scene->getLightList().size());
  scene->render(fb, p, 0);
  fb.exportAsPNG(fpath("output_aaa.png"));
  printf("Framebuffer with aaa scene exported to %s\n", fpath("output_aaa.png").c_str());
}
