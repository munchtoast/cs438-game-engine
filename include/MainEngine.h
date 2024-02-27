/**
 * @file MainEngine.h
 * @brief Defines the MainEngine class, a wrapper for integrating Python
 * scripting language with the game engine.
 *
 * The MainEngine class provides an interface for incorporating Python scripts
 * into the game engine. It serves as a bridge between the C++ core of the
 * engine and the Python scripting language, facilitating interactions and
 * extending the functionality of the game.
 *
 * @note Ensure proper configuration and integration of Python scripting.
 *
 * @remark This class serves as a vital component for enabling dynamic and
 * scripted interactions within the game engine.
 *
 * @version
 * - 1.0: Initial implementation (dexter@nekocake.cafe) (2024-02-01)
 */

#ifndef MAINENGINE_H
#define MAINENGINE_H

#include "RectStruct.h"
#include <cstddef>

namespace MainEngine {
typedef struct {
  const RectStruct::Rect *rect;
} GameObjects;

typedef struct {
  const RectStruct::Rect *rect;
  const RectStruct::Color *color;
} Tiles;

typedef struct {
  const char *title const int w;
  const int h;
  const Uint32 windowFlags;
  const Uint32 rendererFlags;
} GameWindowOptions;

typedef struct {
  const GameObjects *gameObjects;
  const Tile *tiles;
  const GameWindowOptions *gameWindowOptions;

  const size_t gameObjectSize;
  const size_t tileSize;
} Objects;

extern "C" void init_objects(const Objects *objects);

extern "C" void free_memory(void *ptr);
} // namespace MainEngine

#endif
