#include "ray.h"

class Camera {
  public:
    Camera();
    Camera(int width, int height);
    Camera(const vec3 &origin, const vec3 &U, const vec3 &V, const vec3 &W, float focalLength, int width, int height);
    // virtual ~Camera();

    virtual ray generateRay(float i, float j) = 0;

    int getWidth() const { return width; };
    int getHeight() const { return height; };
    int getLeftBound() const { return -width / 2; };
    int getRightBound() const { return width / 2; };
    int getTopBound() const { return height / 2; };
    int getBottomBound() const { return -height / 2; };
    vec3 getPosition() const { return origin; }

  protected:
    vec3 U, V, W;
    vec3 origin;
    int width, height;
    float focalLength;
};

class PerspectiveCamera : public Camera {
  public:
    /// @brief
    PerspectiveCamera();
    /// @brief
    /// @param width
    /// @param height
    PerspectiveCamera(int width, int height);
    /// @brief
    /// @param origin
    /// @param U
    /// @param V
    /// @param W
    /// @param focalLength
    /// @param width
    /// @param height
    PerspectiveCamera(const vec3 &origin, const vec3 &U, const vec3 &V, const vec3 &W, float focalLength, int width, int height);
    // ~PerspectiveCamera();

    ray generateRay(float i, float j) override;
};

// Camera *cameraPtr = new PerspectiveCamera();
// cameraPtr->generateRay(...);
