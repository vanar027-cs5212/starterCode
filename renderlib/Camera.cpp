#include "Camera.h"

Camera::Camera() : origin(vec3(0, 0, 0)), U(vec3(1, 0, 0)), V(vec3(0, 1, 0)), W(vec3(0, 0, 1)), width(800), height(600) {}

Camera::Camera(int width, int height) : origin(vec3(0, 0, 0)), U(vec3(1, 0, 0)), V(vec3(0, 1, 0)), W(vec3(0, 0, 1)), width(width), height(height) {}

PerspectiveCamera::PerspectiveCamera() : Camera() {}

PerspectiveCamera::PerspectiveCamera(int width, int height) : Camera(width, height) {}

void PerspectiveCamera::generateRay(int i, int j, ray &r) {
    
}
