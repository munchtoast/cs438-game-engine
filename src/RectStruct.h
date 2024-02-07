/*
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
 */

#ifndef RECTSTRUCT_H
#define RECTSTRUCT_H

#include <SDL.h>

namespace RectStruct {
typedef struct {
  float x;
  float y;
} Position;

typedef struct {
  float width;
  float height;
} Size;

typedef struct {
  Position position;
  Size size;
} Rect;

typedef struct {
  Uint8 r;
  Uint8 g;
  Uint8 b;
  Uint8 a;
} Color;
} // namespace RectStruct

#endif
