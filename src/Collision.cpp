#include "Collision.h"
#include "GameObject.h"

namespace Collision {
/**
 * @brief Handles collisions between game objects
 *
 */

Collision::Collision() {}

Collision::~Collision() { Collision::cleanup(); }

bool Collision::detectCollision(GameObject *obj1, GameObject *obj2) {
  // Check for collision along x-axis
  bool xCollision =
      obj1.getRect()->x < obj2.getRect()->x + obj2.getRect()->w && obj1.getRect()->x + obj1.getRect()->w > obj2.getRect()->x;

  // Check for collision along y-axis
  bool yCollision =
      obj1.getRect()->y < obj2.getRect()->y + obj2.getRect()->h && obj1.getRect()->y + obj1.getRect()->h > obj2.getRect()->y;

  return xCollision && yCollision;
}
void Collision::handleCollision(GameObject *obj1, GameObject *obj2) {
  // assuming that obj1 is the object that is moving into obj2
  while !(detectCollision(obj1, obj2) {
      if (obj1.getRect()->x < obj2.getRect()->x + obj2.getRect()->w) {
        obj1.setX(obj1.getRect()->x + 1);
      } else if (obj1.getRect()->x + obj1.getRect()->w > obj2.getRect()->x) {
        obj1.setX(obj1.getRect()->x - 1);
      }
      if (obj1.getRect()->y < obj2.getRect()->y + obj2.getRect()->h) {
        obj1.setY(obj1.getRect()->y + 1);
      } else if (obj1.getRect()->y + obj1.getRect()->h > obj2.getRect()->y) {
        obj1.setY(obj1.getRect()->y - 1);
      }
        }
}

void Collision::cleanup() { return; }

} // namespace Collision