/*
 * @file Collision.h
 * @brief Defines the Collision class, a subcomponent of the physics engine
 *
 * The Collision class detects collisions between two game objects
 * it makes static calls to detectCollission and handleCollision.
 * This will change the position of the object based on the collision.
 *
 *
 * @version
 * - 1.0: Initial implementation (jyang@nekocake.cafe) (2024-02-26)
 * - 1.1: Detection for rotated boxes (jyang@nekocake.cafe) (2024-03-03)
 */

#ifndef COLLISION_H
#define COLLISION_H

#include <BoxRigidBody.h>
#include <SDL.h>

namespace Collision {
class Collision {
public:
  struct Vec2 {
    float x, y;
  };

  static float sweptCollision(BoxRigidBody::BoxRigidBody *obj1,
                              BoxRigidBody::BoxRigidBody *obj2);
  static bool detectCollision(BoxRigidBody::BoxRigidBody *obj1,
                              BoxRigidBody::BoxRigidBody *obj2);
  static void handleCollision(BoxRigidBody::BoxRigidBody *obj1,
                              BoxRigidBody::BoxRigidBody *obj2);

private:
  void getCorners(BoxRigidBody::BoxRigidBody *obj, Vec2 corners[]);
};
} // namespace Collision
#endif