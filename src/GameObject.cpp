#include "GameObject.h"
#include "Map.h"
#include "MemoryManagement.h"
#include "RectStruct.h"
#include "Util.h"
#include <SDL.h>
#include <mimalloc.h>
#include <spdlog/spdlog.h>

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
  GameObject::setRectProperties(static_cast<RectStruct::Rect *>(
      MemoryManagement::MemoryManagement::allocate<RectStruct::Rect>(
          sizeof(RectStruct::Rect))));

  GameObject::setSubGameObjects(
      new (MemoryManagement::MemoryManagement::allocate<Map::Map<GameObject>>(
          sizeof(Map::Map<GameObject>))) Map::Map<GameObject>());

  GameObject::setX(x);
  GameObject::setY(y);
  GameObject::setW(width);
  GameObject::setH(height);
}

GameObject::~GameObject() { GameObject::cleanup(); }

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

float GameObject::getX() { return GameObject::getRectProperties()->position.x; }
float GameObject::getY() { return GameObject::getRectProperties()->position.y; }
float GameObject::getW() { return GameObject::getRectProperties()->size.width; }
float GameObject::getH() {
  return GameObject::getRectProperties()->size.height;
}

RectStruct::Rect *GameObject::getRectProperties() {
  return GameObject::rectProperties;
}

void GameObject::setRectProperties(RectStruct::Rect *ptr) {
  rectProperties = ptr;
}

Map::Map<GameObject> *GameObject::getSubGameObjects() { return subGameObjects; }

void GameObject::addSubGameObject(GameObject *subGameObject) {
  getSubGameObjects()->add(subGameObject);
}

void GameObject::handleEvent() { spdlog::info("GameObject handled an event"); }

void GameObject::setSubGameObjects(Map::Map<GameObject> *nSubGameObjects) {
  subGameObjects = nSubGameObjects;
}

void GameObject::cleanup() {
  GameObject::setRectProperties(static_cast<RectStruct::Rect *>(
      MemoryManagement::MemoryManagement::deallocate<RectStruct::Rect>(
          GameObject::getRectProperties())));
  Util::Util::checkIfMemFreeSuccess(GameObject::getRectProperties());

  GameObject::setSubGameObjects(static_cast<Map::Map<GameObject> *>(
      MemoryManagement::MemoryManagement::deallocate<Map::Map<GameObject>>(
          GameObject::getSubGameObjects())));
}
} // namespace GameObject
