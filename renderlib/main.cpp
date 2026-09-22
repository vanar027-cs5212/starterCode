#include <filesystem>
#include "Framebuffer.h"
#include "Camera.h"


using namespace std;

int main(int argc, char **argv) {
  Framebuffer fb(200, 200);

  cout << "Framebuffer size: " << fb.getWidth() << "x" << fb.getHeight() << endl;

  const string outputPath = filesystem::absolute("output.png").string();
  fb.clearToGradient(color(1, 0, 0), color(0, 0, 1));
  fb.exportAsPNG(outputPath);

  cout << "Framebuffer exported to " << outputPath << endl;

  Camera *cameraPtr = new PerspectiveCamera(vec3(0, 0, 0), vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 1), 0.1, fb.getWidth(), fb.getHeight());

  for (int j = 0; j < fb.getHeight(); ++j) {
    for (int i = 0; i < fb.getWidth(); ++i) {
      ray r = cameraPtr->generateRay(i, j);
      // normalize ray direction
      color clr = r.direction() / r.direction().length();
      cout << "Color: " << clr.toString() << endl;
      // shift into color space
      clr = (clr + vec3(1, 1, 1)) * 0.5;
      fb.setPixelColor(i, j, color(clr.x(), clr.y(), clr.z()));
    }
  }

  fb.exportAsPNG("output_with_rays.png");
  cout << "Framebuffer with rays exported to output_with_rays.png" << endl;

  return 0;
}
