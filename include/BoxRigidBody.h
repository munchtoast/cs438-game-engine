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

#include "BoxBody.h"
#include "Map.h"

namespace BoxRigidBody {
class BoxRigidBody {
public:
	BoxRigidBody(float x, float y, float width, float height, float angle);
  ~BoxRigidBody();

  void setX(float x);
  void setY(float y);
  void setW(float width);
  void setH(float height);
  void setA(float angle);
  void setVX(float velx);
  void setVY(float vely);

  float getX();
  float getY();
  float getW();
  float getH();
  float getA();
  float getVX();
  float getVY();

  BoxBody::Box* getBoxProperties();
  void setBoxProperties(BoxBody::Box* ptr);

private:
	BoxBody::Box* boxProperties;


  void cleanup();
};
} // namespace BoxRigidBody

#endif
