#include "Framebuffer.h"
#include <filesystem>

using namespace std;

int main(int argc, char **argv) {
  Framebuffer fb(200, 200);

  cout << "Framebuffer size: " << fb.getWidth() << "x" << fb.getHeight() << endl;

  const string outputPath = filesystem::absolute("output.png").string();
  fb.clearToGradient(color(1, 0, 0), color(0, 0, 1));
  fb.exportAsPNG(outputPath);

  cout << "Framebuffer exported to " << outputPath << endl;

  return 0;
}
