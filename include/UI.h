/**
 * @file UI.h
 * @brief Declaration of the UI class, a fundamental GameObject for
 * target-rendering objects
 *
 * The UI class features tools required to render specific areas within the
 * game engine
 *
 * @note Ensure that dependencies of UI class are satisfied
 *
 * @version
 * - 1.0: Initial implementation (dexter@nekocake.cafe) (2024-02-05)
 */

#ifndef UI_H
#define UI_H

#include "GameObject.h"

#include <SDL.h>

namespace UI {
class UI : public GameObject::GameObject {
public:
  UI(float x, float y, float width, float height);
  virtual ~UI();

  void move(int deltaX, int deltaY);

  void apply(SDL_Renderer *renderer);

private:
  void cleanup();
};
} // namespace UI

#endif
