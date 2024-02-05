#include "Camera.h"
#include "Util.h"
#include <SDL.h>

namespace Camera {
Camera::Camera(float x, float y, float width, float height)
    : GameObject(x, y, width, height) {}

Camera::~Camera() { Camera::cleanup(); }

void Camera::move(int deltaX, int deltaY) {
  Camera::setX(Camera::getX() + deltaX);
  Camera::setY(Camera::getY() + deltaY);
}

void Camera::apply(SDL_Renderer *renderer) {
  if (!Util::Util::checkIfNullPtr(renderer)) {

    SDL_SetRenderViewport(renderer, (SDL_Rect *)Camera::getRect());
  }
}

void Camera::cleanup() { return; }
} // namespace Camera
