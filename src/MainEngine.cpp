#include "MainEngine.h"
#include "GameWindow.h"
#include "RectStruct.h"
#include "Tile.h"
#include <cstddef>

/**
 * @brief Initialize all objects and initializes core components such as
 * GameWindow, Tiles, and GameObjects
 *
 * @note Tile may be deprecated in the near future as everything is referenced
 * off GameObject alone
 * @param objects - Struct of all GameObjects, Tiles, and the GameWindow
 * options. The GameObjects and Tiles refers to a memory pointer that references
 * all and not just one object
 */
extern "C" void init_objects(const Objects *objects) {
  GameWindow::GameWindow gameWindow(
      objects.gameWindowOptions.title, objects.gameWindowOptions.w,
      object.gameWindowOptions.h, object.gameWindowOptions.windowFlags,
      object.gameWindowOptions.rendererFlags);

  for (int i = 0; i < tileSize; i++) {
    Tile::Tile tile(
        objects.tiles[i].rect->position.x, objects.tiles[i].rect->position.y,
        objects.tiles[i].rect->size.width, objects.tiles[i].rect->size.height);

    tile.setColorChoice(objects.tiles[i].color->r, objects.tiles[i].color->g,
                        objects.tiles[i].color->b, objects.tiles[i].color->a);
  }

  for (int i = 0; i < gameObjectSize; i++) {
    GameObject::GameObject gameObject(objects.GameObjects[i].rect->position.x,
                                      objects.GameObjects[i].rect->position.y,
                                      objects.GameObjects[i].rect->size.width,
                                      objects.GameObjects[i].rect->size.height);
  }
}

extern "C" void free_memory(void *ptr) {}
