#include "ray.h"

class Camera {
  public:
    Camera();
    Camera(int width, int height);
    virtual ~Camera();

    virtual void generateRay(int i, int j, ray &r) = 0;

    int getWidth() const { return width; };
    int getHeight() const { return height; };
    int getLeftBound() const { return -width / 2; };
    int getRightBound() const { return width / 2; };
    int getTopBound() const { return height / 2; };
    int getBottomBound() const { return -height / 2; };

  protected:
    vec3 U, V, W;
    vec3 origin;
    int width, height;
};

class PerspectiveCamera : public Camera {
  public:
    PerspectiveCamera();
    PerspectiveCamera(int width, int height);
    ~PerspectiveCamera();

    void generateRay(int i, int j, ray &r) override;
};

// Camera *cameraPtr = new PerspectiveCamera();
// cameraPtr->generateRay(...);
