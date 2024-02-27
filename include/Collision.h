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
 */

#ifndef COLLISION_H
#define COLLISION_H

#include <GameObject.h>
#include <SDL.h>

namespace Collision {
class Collision {
public:
  Collision();
  virtual ~Collision();

  static bool detectCollision(GameObject *obj1, GameObject *obj2);
  static void handleCollision(GameObject *obj1, GameObject *obj2);

private:
  void cleanup();

} // namespace Collision
#endif