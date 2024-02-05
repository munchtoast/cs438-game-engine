/*
 * @file Camera.h
 * @brief Declaration of the Camera class, a fundamental GameObject for
 * target-rendering objects
 *
 * The Camera class features tools required to render specific areas within the
 * game engine
 *
 * @note Ensure that dependencies of Camera class are satisfied
 *
 * @version
 * - 1.0: Initial implementation (dexter@nekocake.cafe) (2024-02-05)
 */

#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"

#include <SDL.h>

namespace Camera {
class Camera : public GameObject::GameObject {
public:
  Camera(float x, float y, float width, float height);
  virtual ~Camera();

  void move(int deltaX, int deltaY);

  void apply(SDL_Renderer *renderer);

private:
  void cleanup();
};
} // namespace Camera

#endif
