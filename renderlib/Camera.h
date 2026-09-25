#include "Ray.h"
#include "Framebuffer.h"

class Camera {
  public:
    Camera(const Point3 &origin, const Vec3 &U, const Vec3 &V, const Vec3 &W, int pixel_width, int pixel_height, float viewport_width);
    Camera(const Point3 &origin, const Vec3 &U, const Vec3 &V, const Vec3 &W, int pixel_width, int pixel_height);
    Camera(const Point3 &origin, const Vec3 &U, const Vec3 &V, const Vec3 &W);
    Camera(const Point3 &origin, int pixel_width, int pixel_height, float viewport_width);
    Camera(int pixel_width, int pixel_height, float viewport_width);
    Camera(int pixel_width, int pixel_height);
    Camera();
    // virtual ~Camera();

    virtual Ray generateRay(float x, float y) const = 0;

    Point3 getOrigin() const { return origin; }
    Vec3 getU() const { return U; };
    Vec3 getV() const { return V; };
    Vec3 getW() const { return W; };
    int getPixelWidth() const { return pixel_width; };
    int getPixelHeight() const { return pixel_height; };
    float getViewportWidth() const { return viewport_width; };
    float getViewportHeight() const { return viewport_height; };
    float getLeftBound() const { return left; };
    float getRightBound() const { return right; };
    float getTopBound() const { return top; };
    float getBottomBound() const { return bottom; };

    Camera setOrigin(const Point3 &new_origin);
    Camera setU(const Vec3 &new_U);
    Camera setV(const Vec3 &new_V);
    Camera setW(const Vec3 &new_W);
    Camera setPixelWidth(int new_pixel_width);
    Camera setPixelHeight(int new_pixel_height);
    Camera setViewportWidth(float new_viewport_width);
    Camera setViewportHeight(float new_viewport_height);

  protected:
    Vec3 origin;
    Vec3 U, V, W;
    int pixel_width, pixel_height;
    float viewport_width, viewport_height;
    float left, right, top, bottom;

  private:
    void calcImplicits() {
      viewport_height = viewport_width * pixel_height / pixel_width;
      left = -viewport_width / 2.0f;
      right = viewport_width / 2.0f;
      top = viewport_height / 2.0f;
      bottom = -viewport_height / 2.0f;
    }
};

class PerspectiveCamera : public Camera {
  public:
    PerspectiveCamera(const Point3 &origin, const Vec3 &U, const Vec3 &V, const Vec3 &W, int pixel_width, int pixel_height, float viewport_width, float focal_length);
    PerspectiveCamera(const Point3 &origin, const Vec3 &U, const Vec3 &V, const Vec3 &W, int pixel_width, int pixel_height, float viewport_width);
    PerspectiveCamera(const Point3 &origin, const Vec3 &U, const Vec3 &V, const Vec3 &W, int pixel_width, int pixel_height);
    PerspectiveCamera(const Point3 &origin, int pixel_width, int pixel_height, float viewport_width, float focal_length);
    PerspectiveCamera(int pixel_width, int pixel_height, float viewport_width, float focal_length);
    PerspectiveCamera(int pixel_width, int pixel_height, float viewport_width);
    PerspectiveCamera(int pixel_width, int pixel_height);
    PerspectiveCamera();
    // ~PerspectiveCamera();

    float getFocalLength() const { return focal_length; };

    PerspectiveCamera setFocalLength(float new_focal_length);

    Ray generateRay(float x, float y) const override;

    void visualizeRays(const Framebuffer &fb);

  protected:
    float focal_length;
};

// Camera *cameraPtr = new PerspectiveCamera();
// cameraPtr->generateRay(...);
