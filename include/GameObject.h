/**
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
 * - 1.1: Add sub game objects for allowing hierarchical dependency
 * (dexter@nekocake.cafe) (2024-02-09)
 * 1.2: Add custom event handler (dexter@nekocake.cafe) (2024-02-15)
 * 1.3: Add animation engine (dexter@nekocake.cafe) (2024-02-26)
 */

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Animation.h"
#include "Map.h"
#include "RectStruct.h"
#include <SDL.h>

namespace GameObject {
class GameObject {
public:
  GameObject(float x, float y, float width, float height);
  virtual ~GameObject();

  RectStruct::Rect *getRectProperties();
  void setRectProperties(RectStruct::Rect *ptr);

  Map::Map<GameObject> *getSubGameObjects();
  void addSubGameObject(GameObject *subGameObject);

  void setX(float x);
  void setY(float y);
  void setW(float width);
  void setH(float height);

  float getX();
  float getY();
  float getW();
  float getH();

  Animation::Animation *getAnimation();
  void handleEvent();

protected:
  void setSubGameObjects(Map::Map<GameObject> *subGameObjects);

private:
  Map::Map<GameObject> *subGameObjects;
  RectStruct::Rect *rectProperties;
  Animation::Animation *animation;

  void cleanup();
};
} // namespace GameObject

#endif
