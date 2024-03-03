#include "Collision.h"
#include "GameObject.h"

namespace Collision {
/**
 * @brief Handles collisions between game objects
 *
 */

bool Collision::detectCollision(GameObject::GameObject *obj1,
                                GameObject::GameObject *obj2) {
  // Check for collision along x-axis
  bool xCollision = obj1->getX() < obj2->getX() + obj2->getW() &&
                    obj1->getX() + obj1->getW() > obj2->getX();

  // Check for collision along y-axis
  bool yCollision = obj1->getY() < obj2->getY() + obj2->getH() &&
                    obj1->getY() + obj1->getH() > obj2->getY();

  return xCollision && yCollision;
}
void Collision::handleCollision(GameObject::GameObject *obj1,
                                GameObject::GameObject *obj2) {
  // assuming that obj1 is the object that is moving into obj2
  while (Collision::detectCollision(obj1, obj2)) {
    if (obj1->getX() < obj2->getX() + obj2->getW()) {
      obj1->setX(obj1->getX() + 1);
    } else if (obj1->getX() + obj1->getW() > obj2->getX()) {
      obj1->setX(obj1->getX() - 1);
    }
    if (obj1->getY() < obj2->getY() + obj2->getH()) {
      obj1->setY(obj1->getY() + 1);
    } else if (obj1->getY() + obj1->getH() > obj2->getY()) {
      obj1->setY(obj1->getY() - 1);
    }
  }
}
} // namespace Collision