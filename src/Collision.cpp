#define _USE_MATH_DEFINES

#include "Collision.h"
#include "BoxRigidBody.h"

struct Vec2 {
  float x, y;
};

namespace Collision {
/**
 * @brief Handles collisions between game objects
 *
 */

bool Collision::detectCollision(BoxRigidBody::BoxRigidBody *obj1,
                                BoxRigidBody::BoxRigidBody *obj2) {
  // Convert degrees to radians
  float rangle1 = obj1->getA() * M_PI / 180.0f;
  float rangle2 = obj2->getA() * M_PI / 180.0f;

  Vec2 axes[] = {{cos(rangle1), sin(rangle1)},
                 {cos(rangle1 + M_PI / 2), sin(rangle1 + M_PI / 2)},
                 {cos(rangle2), sin(rangle2)},
                 {cos(rangle2 + M_PI / 2), sin(rangle2 + M_PI / 2)}};

  for (const Vec2 &axis : axes) {
    float proj1_min = obj1->getX() * axis.x + obj1->getY() * axis.y;
    float proj1_max =
        proj1_min + obj1->getW() * cos(rangle1) + obj1->getH() * sin(rangle1);

    float proj2_min = obj2->getX() * axis.x + obj2->getY() * axis.y;
    float proj2_max =
        proj2_min + obj2->getW() * cos(rangle2) + obj2->getH() * sin(rangle2);

    if (proj1_max < proj2_min || proj2_max < proj1_min) {
      return false;
    }
  }
  //}

  return true;
}

void Collision::handleCollision(BoxRigidBody::BoxRigidBody *obj1,
                                BoxRigidBody::BoxRigidBody *obj2) {
  // assuming that obj1 is the object that is moving into obj2
  while (Collision::detectCollision(obj1, obj2)) {
    if (obj1->getX() <= obj2->getX() + obj2->getW()) {
      obj1->setX(obj1->getX() + 1);
    } else if (obj1->getX() + obj1->getW() >= obj2->getX()) {
      obj1->setX(obj1->getX() - 1);
    }
    if (obj1->getY() <= obj2->getY() + obj2->getH()) {
      obj1->setY(obj1->getY() + 1);
    } else if (obj1->getY() + obj1->getH() >= obj2->getY()) {
      obj1->setY(obj1->getY() - 1);
    }
  }
}
} // namespace Collision