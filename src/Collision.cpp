#define _USE_MATH_DEFINES

#include "Collision.h"
#include "BoxRigidBody.h"

namespace Collision {
/**
 * @brief Handles collisions between game objects
 *
 */

// Function to calculate collision time between a moving and stationary object
float Collision::sweptCollision(BoxRigidBody::BoxRigidBody *obj1,
                                BoxRigidBody::BoxRigidBody *obj2) {
  float xInitEntry, yInitEntry;
  float xInitExit, yInitExit;
  float nx, ny;

  // find the distance between the objects on the near and far sides for both x
  // and y
  if (obj1->getVX() > 0.0f) {
    xInitEntry = obj2->getX() - (obj1->getX() + obj1->getW());
    xInitExit = (obj2->getX() + obj2->getW()) - obj1->getX();
  } else {
    xInitEntry = (obj2->getX() + obj2->getW()) - obj1->getX();
    xInitExit = obj2->getX() - (obj1->getX() + obj1->getW());
  }

  if (obj1->getVY() > 0.0f) {
    yInitEntry = obj2->getY() - (obj1->getY() + obj1->getH());
    yInitExit = (obj2->getY() + obj2->getH()) - obj1->getY();
  } else {
    yInitEntry = (obj2->getY() + obj2->getH()) - obj1->getY();
    yInitExit = obj2->getY() - (obj1->getY() + obj1->getH());
  }
  float xEntry, yEntry;
  float xExit, yExit;

  if (obj1->getVX() == 0.0f) {
    xEntry = -9999999;
    xExit = 9999999;
  } else {
    xEntry = xInitEntry / obj1->getVX();
    xExit = xInitExit / obj1->getVX();
  }

  if (obj1->getVY() == 0.0f) {
    yEntry = -9999999;
    yExit = 9999999;
  } else {
    yEntry = yInitEntry / obj1->getVY();
    yExit = yInitExit / obj1->getVY();
  }
  float entryTime = std::max(xEntry, yEntry);
  float exitTime = std::min(xExit, yExit);

  if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f ||
      yEntry > 1.0f) {
    nx = 0.0f;
    ny = 0.0f;
    return 1.0f;
  }

  return entryTime;
}

bool Collision::detectCollision(BoxRigidBody::BoxRigidBody *obj1,
                                BoxRigidBody::BoxRigidBody *obj2) {
  if (obj1->getA() == 0 && obj2->getA() == 0) {
    bool xCollision = obj1->getX() < obj2->getX() + obj2->getW() &&
                      obj1->getX() + obj1->getW() > obj2->getX();

    bool yCollision = obj1->getY() < obj2->getY() + obj2->getH() &&
                      obj1->getY() + obj1->getH() > obj2->getY();

    return xCollision && yCollision;
  } else {
    // Convert degrees to radians
    float rangle1 = obj1->getA() * M_PI / 180.0f;
    float rangle2 = obj2->getA() * M_PI / 180.0f;

    Vec2 axes[] = {{cos(rangle1), sin(rangle1)},
                   {cos(rangle1 + M_PI / 2), sin(rangle1 + M_PI / 2)},
                   {cos(rangle2), sin(rangle2)},
                   {cos(rangle2 + M_PI / 2), sin(rangle2 + M_PI / 2)}};

    for (const Vec2 &axis : axes) {
      float rect1Min = obj1->getX() * axis.x + obj1->getY() * axis.y;
      float rect1Max =
          rect1Min + obj1->getW() * cos(rangle1) + obj1->getH() * sin(rangle1);

      float rect2Min = obj2->getX() * axis.x + obj2->getY() * axis.y;
      float rect2Max =
          rect2Min + obj2->getW() * cos(rangle2) + obj2->getH() * sin(rangle2);

      if (rect1Max < rect2Min || rect2Max < rect1Min) {
        return false;
      }
    }
  }
  return true;
}

void Collision::handleCollision(BoxRigidBody::BoxRigidBody *obj1,
                                BoxRigidBody::BoxRigidBody *obj2) {

  float rangle1 = obj1->getA() * M_PI / 180.0f;
  float rangle2 = obj2->getA() * M_PI / 180.0f;
  Vec2 direction;
  if (obj1->getX() == obj2->getX() && obj1->getY() == obj2->getY()) {
    direction = {1.0f, 0.0f};
  } else {
    direction = {obj2->getX() - obj1->getX(), obj2->getY() - obj1->getY()};
  }

  float length = sqrt(direction.x * direction.x + direction.y * direction.y);

  direction = {direction.x / length, direction.y / length};

  // Rotate direction vector by the angle of rect1

  float rotatedX = direction.x * cos(-rangle2) - direction.y * sin(-rangle2);
  float rotatedY = direction.x * sin(-rangle2) + direction.y * cos(-rangle2);

  float collisionNormalX;
  float collisionNormalY;

  collisionNormalX = -rotatedY; // Rotate resulting vector by -90 degrees to
                                // obtain collision normal
  collisionNormalY = rotatedX;

  // Calculate overlap along the collision normal
  float rect1Min =
      obj1->getX() * collisionNormalX + obj1->getY() * collisionNormalY;
  float rect1Max =
      rect1Min + (obj1->getW() * cos(rangle1) + obj1->getH() * sin(rangle1));
  float rect2Min =
      obj2->getX() * collisionNormalX + obj2->getY() * collisionNormalY;
  float rect2Max =
      rect2Min + (obj2->getW() * cos(rangle2) + obj2->getH() * sin(rangle2));
  float overlap = fmin(rect1Max, rect2Max) - fmax(rect1Min, rect2Min);

  float resolveOverlap = overlap / 2.0f;

  // Resolve overlap
  obj1->setX(obj1->getX() - floor(collisionNormalX * overlap));
  obj1->setY(obj1->getY() - floor(collisionNormalY * overlap));
}
} // namespace Collision