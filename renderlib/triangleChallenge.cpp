#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include "PointLight.h"
#include "Scene.h"
#include "Triangle.h"
#include "SolidShader.h"
#include "Framebuffer.h"
#include "Camera.h"

using namespace std;
string fpath(const string &filename) { return filesystem::absolute(filename).string(); }

void readFloatsFromFile(const std::string &filename, std::vector<float> &allFloats) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "Failed to open file\n";
    return;
  }

  float value;
  char c;

  while (file >> value) {
    allFloats.push_back(value);

    // Consume comma if there
    if (file.peek() == ',') file.get(c);
  }
}

int main(int argc, char *argv[]) {
  std::vector<float> allFloats;
  readFloatsFromFile("trilist.dat", allFloats);

  std::cout << std::endl;
  std::cout << "Number of floats: " << allFloats.size() << std::endl;
  int numVertices = allFloats.size() / 3;
  std::cout << "Interpreted as Vertices: " << numVertices << std::endl;
  int numTriangles = numVertices / 3;
  std::cout << "Interpreted as Triangles: " << numTriangles << std::endl;

  Scene *solidScene = new Scene();
  Scene *normalScene = new Scene();
  solidScene
    ->setAntialiasSampleCount(1)
    ->addLight(PointLight(Point3(0, 0, 0), Color(1, 1, 1)));
  normalScene
    ->setAntialiasSampleCount(1)
    ->addLight(PointLight(Point3(0, 0, 0), Color(1, 1, 1)));
  for (int i = 0; i < allFloats.size(); i += 9) {
    /*printf(
      "Adding triangle with vertices: "
      "(%.3f, %.3f, %.3f), "
      "(%.3f, %.3f, %.3f), "
      "(%.3f, %.3f, %.3f)\n",
      allFloats[i],
      allFloats[i + 1],
      allFloats[i + 2],
      allFloats[i + 3],
      allFloats[i + 4],
      allFloats[i + 5],
      allFloats[i + 6],
      allFloats[i + 7],
      allFloats[i + 8]);*/
    // srand(static_cast<unsigned int>(std::time(nullptr)));

    auto a = Point3(allFloats[i], allFloats[i + 1], allFloats[i + 2]),
         b = Point3(allFloats[i + 3], allFloats[i + 4], allFloats[i + 5]),
         c = Point3(allFloats[i + 6], allFloats[i + 7], allFloats[i + 8]);
    solidScene->addShape(make_shared<Triangle>(a, b, c, make_shared<SolidShader>(Color::random())));
    normalScene->addShape(make_shared<Triangle>(a, b, c));
  }

  Framebuffer fb(1080, 1080);
  PerspectiveCamera *cam = new PerspectiveCamera(Vec3(0, 0, 3), Vec3(1, 0, 0), Vec3(0, -1, 0), Vec3(0, 0, 1), fb.getWidth(), fb.getHeight(), 1.0f, 1.0f);

  std::cout << "rendering solidScene" << endl;
  solidScene->render(fb, cam, 1);
  fb.exportAsPNG(fpath("solidTriangleChallenge.png"));
  std::cout << "Framebuffer with triangle challenge scene exported to " << fpath("solidTriangleChallenge.png") << endl;

  std::cout << "rendering normalScene" << endl;
  normalScene->render(fb, cam, 1);
  fb.exportAsPNG(fpath("normalTriangleChallenge.png"));
  std::cout << "Framebuffer with triangle challenge scene exported to " << fpath("normalTriangleChallenge.png") << endl;
}
