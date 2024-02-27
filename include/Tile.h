/**
 * @file Tile.h
 * @brief Declaration of the Tile class, a fundamental GameObject in the TileMap
 * system.
 *
 * The Tile class represents the basic component of rendering a texture to the
 * game engine. It requires all dependencies from GameObject, and does not need
 * to interact with other GameObjects directly.
 *
 * @note Ensure that dependencies of GameObject class are satisfied
 *
 * @remark
 * This class serves as a foundational element for constructing the TileMap
 * system.
 *
 * @version
 * - 1.0: Initial implementation (dexter@nekocake.cafe) (2024-02-01)
 * - 1.1: Remove unnecessary includes that cause circular dependencies
 * (dexter@nekocake.cafe) (2024-02-09)
 */

#ifndef TILE_H
#define TILE_H

#include "GameObject.h"
#include "RectStruct.h"
#include <SDL.h>

namespace Tile {
class Tile : public GameObject::GameObject {
public:
  Tile(float x, float y, float width, float height);
  virtual ~Tile();

  RectStruct::Color *getColor();
  void setColor(RectStruct::Color *ptr);
  void setColorChoice(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

private:
  RectStruct::Color *color;

  void cleanup();
};
} // namespace Tile

#endif
