#include "GameObject.h"
#include "MemoryManagement.h"
#include "RectStruct.h"
#include "Util.h"
#include <SDL.h>
#include <mimalloc.h>

namespace GameObject {
/**
 * @brief Constructs a GameObject instance.
 *
 * @param x - X-Position of GameObject
 * @param y - Y-Position of GameObject
 * @param w - Size of the GameObject's width
 * @param h - Size of the GameObject's height
 */
GameObject::GameObject(float x, float y, float width, float height) {
  rectProperties =
      (RectStruct::Rect *)MemoryManagement::MemoryManagement::allocate(
          sizeof(RectStruct::Rect));

  GameObject::setX(x);
  GameObject::setY(y);
  GameObject::setW(width);
  GameObject::setH(height);
}

GameObject::~GameObject() { GameObject::cleanup(); }

SDL_FRect *GameObject::getRect() { return &rect; }

void GameObject::setX(float x) {
  GameObject::getRectProperties()->position.x = x;
}
void GameObject::setY(float y) {
  GameObject::getRectProperties()->position.y = y;
}
void GameObject::setW(float width) {
  GameObject::getRectProperties()->size.width = width;
}
void GameObject::setH(float height) {
  GameObject::getRectProperties()->size.height = height;
}

RectStruct::Rect *GameObject::getRectProperties() {
  return GameObject::rectProperties;
}

void GameObject::setRectProperties(RectStruct::Rect *ptr) {
  rectProperties = ptr;
}

/**
 * @brief Updates internal position to the render
 */
void GameObject::update() {
  GameObject::getRect()->x = GameObject::getRectProperties()->position.x;
  GameObject::getRect()->y = GameObject::getRectProperties()->position.y;
  GameObject::getRect()->w = GameObject::getRectProperties()->size.width;
  GameObject::getRect()->h = GameObject::getRectProperties()->size.height;
}

void GameObject::cleanup() {
  GameObject::setRectProperties(
      (RectStruct::Rect *)MemoryManagement::MemoryManagement::deallocate(
          GameObject::getRectProperties()));
  Util::Util::checkIfMemFreeSuccess(GameObject::getRectProperties());
}
} // namespace GameObject
