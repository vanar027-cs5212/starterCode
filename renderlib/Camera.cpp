#include "Camera.h"

Camera::Camera() : origin(vec3(0, 0, 0)), U(vec3(1, 0, 0)), V(vec3(0, 1, 0)), W(vec3(0, 0, 1)), focalLength(1.0), width(800), height(600) {}

Camera::Camera(int width, int height) : origin(vec3(0, 0, 0)), U(vec3(1, 0, 0)), V(vec3(0, 1, 0)), W(vec3(0, 0, 1)), focalLength(1.0), width(width), height(height) {}

Camera::Camera(const vec3 &origin, const vec3 &U, const vec3 &V, const vec3 &W, float focalLength, int width, int height)
  : origin(origin), U(U), V(V), W(W), focalLength(focalLength), width(width), height(height) {}

PerspectiveCamera::PerspectiveCamera() : Camera() {}

PerspectiveCamera::PerspectiveCamera(int width, int height) : Camera(width, height) {}

PerspectiveCamera::PerspectiveCamera(const vec3 &origin, const vec3 &U, const vec3 &V, const vec3 &W, float focalLength, int width, int height) : Camera(origin, U, V, W, focalLength, width, height) {}

ray PerspectiveCamera::generateRay(float i, float j) {
  float u = getLeftBound() + (getRightBound() - getLeftBound()) * i / (float)width;
  float v = getBottomBound() + (getTopBound() - getBottomBound()) * j / (float)height;
  vec3 rayDir = -focalLength * W + u * U + v * V;

  std::cout << "Ray direction: " << rayDir.toString() << std::endl;

  return ray(origin, rayDir);
}
