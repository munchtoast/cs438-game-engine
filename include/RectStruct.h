/**
 * @file RectStruct.h
 * @brief Defines the RectStruct namespace, encapsulating essential structs for
 * geometry and color representation.
 *
 * The RectStruct namespace provides key structures for handling geometric
 * information and color representation within the game engine. These structs
 * play a crucial role in defining the layout, size, and color of game objects.
 *
 * @note Ensure that RectStruct is utilized appropriately for geometry and color
 * management.
 *
 * @remark This namespace serves as a foundational element for constructing and
 * representing essential geometric and color data in the game engine.
 *
 * @version
 * - 1.0: Initial implementation (dexter@nekocake.cafe) (2024-02-01)
 * - 1.1: Make Rect object contain a color to represent a pixel
 * (dexter@nekocake.cafe) (2024-02-26)
 * - 1.2: Use default to prevent overflow (dexter@nekocake.cafe) (2024-02-28)
 */

#ifndef RECTSTRUCT_H
#define RECTSTRUCT_H

#include <SDL.h>

namespace RectStruct {
struct PositionDefault {
  float x = 0;
  float y = 0;
  float angle = 0;
};

struct SizeDefault {
  float width = 0;
  float height = 0;
};

struct ColorDefault {
  Uint8 r = 0;
  Uint8 g = 0;
  Uint8 b = 0;
  Uint8 a = 0;
};

struct VelocityDefault {
  float vx = 0;
  float vy = 0;
};

typedef PositionDefault Position;
typedef SizeDefault Size;
typedef ColorDefault Color;
typedef VelocityDefault Velocity;

typedef struct {
  Position position;
  Size size;
  Color color;
  Velocity velocity;
} Rect;

} // namespace RectStruct

#endif
