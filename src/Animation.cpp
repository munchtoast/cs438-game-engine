#include "Animation.h"
#include "Map.h"
#include "MemoryManagement.h"
#include "Util.h"
#include "spdlog/spdlog.h"

namespace Animation {
Cel::Cel() { pixels = nullptr; }
Cel::~Cel() { cleanup(); }

void Cel::setRenderable(bool r) { renderable = r; }

bool Cel::getRenderable() { return renderable; }

Map::Map<RectStruct::Rect> *Cel::getPixels() { return pixels; }

void Cel::setSprite() {}

/**
 * @brief Set the memory address of pixels associated with the cel
 *
 * @param npixels - Pixels to set
 **/
void Cel::setPixels(Map::Map<RectStruct::Rect> *npixels) { pixels = npixels; }

void Cel::cleanup() {
  if (!Util::Util::checkIfNullPtr(pixels))
    pixels = static_cast<Map::Map<RectStruct::Rect> *>(
        MemoryManagement::MemoryManagement::deallocate<
            Map::Map<RectStruct::Rect>>(pixels));
}

Animation::Animation() {
  animationList = new (
      MemoryManagement::MemoryManagement::allocate<Map::Map<Map::Map<Cel>>>(
          sizeof(Map::Map<Map::Map<Cel>>))) Map::Map<Map::Map<Cel>>();

  state = 0;
}

Animation::~Animation() { cleanup(); }

void Animation::addCels(Map::Map<Cel> *cels) { animationList->add(cels); }

void Animation::setAnimationState(int nstate) { state = nstate; }

int Animation::getAnimationState() { return state; }

Map::Map<Cel> *Animation::getCelsToRender() {
  if (!(state < 0) && state < animationList->getSize())
    return animationList->getMap()[state];
  return nullptr;
}

/**
 * @note This is expected to be handled by a Handler instance exclusively
 *
 */
void Animation::handleEvent() {
  spdlog::info("Event handled by animation engine");
}

void Animation::cleanup() {
  if (!Util::Util::checkIfNullPtr(animationList))
    animationList = static_cast<Map::Map<Map::Map<Cel>> *>(
        MemoryManagement::MemoryManagement::deallocate<Map::Map<Map::Map<Cel>>>(
            animationList));
}
} // namespace Animation
