#include "Camera.h"
#include "Color.h"
#define DEFAULT_PIXEL_WIDTH 1000
#define DEFAULT_PIXEL_HEIGHT 1000
#define DEFAULT_VIEWPORT_WIDTH 1.0f
#define DEFAULT_FOCAL_LENGTH 1.0f

Camera::Camera(const Point3 &origin, const Vec3 &U, const Vec3 &V, const Vec3 &W, int pixel_width, int pixel_height, float viewport_width) : origin(origin), U(U), V(V), W(W), pixel_width(pixel_width), pixel_height(pixel_height), viewport_width(viewport_width) { calcImplicits(); };
Camera::Camera(const Point3 &origin, const Vec3 &U, const Vec3 &V, const Vec3 &W, int pixel_width, int pixel_height) : Camera(origin, U, V, W, pixel_width, pixel_height, DEFAULT_VIEWPORT_WIDTH) {};// Default viewport_width to 1.0f
Camera::Camera(const Point3 &origin, const Vec3 &U, const Vec3 &V, const Vec3 &W) : Camera(origin, U, V, W, DEFAULT_PIXEL_WIDTH, DEFAULT_PIXEL_HEIGHT) {};// Default pixel dimensions to 1000x1000
Camera::Camera(const Point3 &origin, int pixel_width, int pixel_height, float viewport_width) : Camera(origin, Vec3(1, 0, 0), Vec3(0, 1, 0), Vec3(0, 0, 1), pixel_width, pixel_height, viewport_width) {};// Default U, V, W to standard basis vectors
Camera::Camera(int pixel_width, int pixel_height, float viewport_width) : Camera(Point3(0, 0, 0), pixel_width, pixel_height, viewport_width) {};// Default origin to (0, 0, 0)
Camera::Camera(int pixel_width, int pixel_height) : Camera(pixel_width, pixel_height, DEFAULT_VIEWPORT_WIDTH) {};// Default viewport_width to 1.0f
Camera::Camera() : Camera(DEFAULT_PIXEL_WIDTH, DEFAULT_PIXEL_HEIGHT) {};// Default pixel dimensions to 1000x1000

PerspectiveCamera::PerspectiveCamera(const Point3 &origin, const Vec3 &U, const Vec3 &V, const Vec3 &W, int pixel_width, int pixel_height, float viewport_width, float focal_length) : Camera(origin, U, V, W, pixel_width, pixel_height, viewport_width), focal_length(focal_length) {}
PerspectiveCamera::PerspectiveCamera(const Point3 &origin, const Vec3 &U, const Vec3 &V, const Vec3 &W, int pixel_width, int pixel_height, float viewport_width) : Camera(origin, U, V, W, pixel_width, pixel_height, viewport_width), focal_length(DEFAULT_FOCAL_LENGTH) {}// Default focal_length to 1.0f
PerspectiveCamera::PerspectiveCamera(const Point3 &origin, const Vec3 &U, const Vec3 &V, const Vec3 &W, int pixel_width, int pixel_height) : Camera(origin, U, V, W, pixel_width, pixel_height), focal_length(DEFAULT_FOCAL_LENGTH) {}// Default viewport_width to 1.0f
PerspectiveCamera::PerspectiveCamera(const Point3 &origin, int pixel_width, int pixel_height, float viewport_width, float focal_length) : Camera(origin, pixel_width, pixel_height, viewport_width), focal_length(focal_length) {}
PerspectiveCamera::PerspectiveCamera(int pixel_width, int pixel_height, float viewport_width, float focal_length) : Camera(pixel_width, pixel_height, viewport_width), focal_length(focal_length) {}
PerspectiveCamera::PerspectiveCamera(int pixel_width, int pixel_height, float viewport_width) : Camera(pixel_height, pixel_width, viewport_width), focal_length(DEFAULT_FOCAL_LENGTH) {}
PerspectiveCamera::PerspectiveCamera(int pixel_width, int pixel_height) : Camera(pixel_width, pixel_height), focal_length(DEFAULT_FOCAL_LENGTH) {}
PerspectiveCamera::PerspectiveCamera() : PerspectiveCamera(DEFAULT_PIXEL_WIDTH, DEFAULT_PIXEL_HEIGHT) {}


Ray PerspectiveCamera::generateRay(float x, float y) const {
  float u = getLeftBound() + (getRightBound() - getLeftBound()) * x / (float)pixel_width;
  float v = getBottomBound() + (getTopBound() - getBottomBound()) * y / (float)pixel_height;
  Vec3 rayDir = -focal_length * W + u * U + v * V;

  // std::cout << "Ray direction: " << rayDir.toString() << std::endl;

  return Ray(origin, rayDir);
}
