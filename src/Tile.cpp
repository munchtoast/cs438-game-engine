#include "Tile.h"
#include "GameObject.h"
#include "MemoryManagement.h"
#include "RectStruct.h"
#include "Util.h"
#include <mimalloc.h>
#include <spdlog/spdlog.h>

namespace Tile {
/**
 * @brief Constructs a Tile GameObject
 *
 * @note Color is not required to be set and will initialize to white
 * @param x - X-Position of GameObject
 * @param y - Y-Position of GameObject
 * @param width - Size of the GameObject's width
 * @param height - Size of the GameObject's height
 */
Tile::Tile(float x, float y, float width, float height)
    : GameObject(x, y, width, height) {
  color = static_cast<RectStruct::Color *>(
      MemoryManagement::MemoryManagement::allocate<RectStruct::Color>(
          sizeof(RectStruct::Color)));

  Util::Util::checkIfMemAllocSuccess(getColor());
  Tile::setColorChoice(255, 255, 255, 255);
}

Tile::~Tile() { Tile::cleanup(); }

RectStruct::Color *Tile::getColor() { return Tile::color; }

void Tile::setColor(RectStruct::Color *ptr) { color = ptr; }

void Tile::setColorChoice(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
  Tile::color->r = r;
  Tile::color->g = g;
  Tile::color->b = b;
  Tile::color->a = a;
}

void Tile::cleanup() {
  if (!Util::Util::checkIfNullPtr(getColor()))
    Tile::setColor(static_cast<RectStruct::Color *>(
        MemoryManagement::MemoryManagement::deallocate<RectStruct::Color>(
            getColor())));
  Util::Util::checkIfMemFreeSuccess(Tile::getColor());
}
} // namespace Tile
