/**
 * @file BoxBody.h
 * @brief Defines the BoxBody namespace, encapsulating essential structs for
 * rigidbody physics and velocity.
 *
 * The BoxBody namespace provides key structures for handling collisions
 * within the game engine.
 *
 *
 * @version
 * - 1.0: Initial implementation (jyang@nekocake.cafe) (2024-03-07)
 */

#ifndef BOXBODY_H
#define BOXBODY_H

#include <SDL.h>

namespace BoxBody {
struct PositionDefault {
  float x = 0;
  float y = 0;
  float angle = 0;
};

struct SizeDefault {
  float width = 0;
  float height = 0;
};

struct VelocityDefault {
  float vx = 0;
  float vy = 0;
};

typedef PositionDefault Position;
typedef SizeDefault Size;
typedef VelocityDefault Velocity;

typedef struct {
  Position position;
  Size size;
  Velocity velocity;
} Box;

} // namespace BoxBody

#endif
