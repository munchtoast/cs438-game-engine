/**
 * @file BoxRigidBody.h
 * @brief Declaration of the BoxRigidBody class which attaches a
 * rigid body for collision detection to objects.
 *
 * @version
 * - 1.0: Initial implementation (jyang@nekocake.cafe) (2024-03-06)
 */

#ifndef BOXRIGIDBODY_H
#define BOXRIGIDBODY_H

#include "GameObject.h"
#include "Map.h"
#include "RectStruct.h"

namespace BoxRigidBody {
class BoxRigidBody : public GameObject::GameObject {
public:
  BoxRigidBody(float x, float y, float width, float height, float angle);
  ~BoxRigidBody();

  void setVX(float velx);
  void setVY(float vely);
  void update();

  float getVX();
  float getVY();

private:
  void cleanup();
};
} // namespace BoxRigidBody

#endif
