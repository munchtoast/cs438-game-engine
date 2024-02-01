/*
 * @file GameObject.h
 * @brief Defines the GameObject class, a fundamental component of the game
 * engine.
 *
 * The GameObject class represents a basic object within the game engine. It is
 * equipped with rectProperties, essential for rendering the object.
 * Additionally, it maintains the internal location of the object before
 * projection through the renderer.
 *
 * @note Ensure that rectProperties are properly configured for rendering.
 *
 * @remark This class serves as a foundational element for constructing
 * interactive elements in the game.
 *
 * @version
 * - 1.0: Initial implementation (dexter@nekocake.cafe) (2024-02-01)
 */

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "RectStruct.h"
#include <SDL.h>

namespace GameObject {
class GameObject {
public:
  GameObject(float x, float y, float width, float height);
  ~GameObject();

  RectStruct::Rect *rectProperties;
  RectStruct::Rect *getRectProperties();

  SDL_FRect *getRect();
  void setX(float x);
  void setY(float y);
  void setW(float width);
  void setH(float height);
  void update();

private:
  SDL_FRect rect;

  void cleanup();
};
} // namespace GameObject

#endif
