#include "UI.h"
#include "MemoryManagement.h"
#include "Util.h"
#include <SDL.h>

namespace UI {
UI::UI(float x, float y, float width, float height)
    : GameObject(x, y, width, height, angle) {}

UI::~UI() { UI::cleanup(); }

void UI::move(int deltaX, int deltaY) {
  UI::setX(UI::getX() + deltaX);
  UI::setY(UI::getY() + deltaY);
}

void UI::apply(SDL_Renderer *renderer) {
  if (!Util::Util::checkIfNullPtr(renderer)) {
    SDL_Rect *rect =
        new (MemoryManagement::MemoryManagement::allocate<SDL_Rect>(
            sizeof(SDL_Rect))) SDL_Rect;

    rect->x = getRectProperties()->position.x;
    rect->y = getRectProperties()->position.y;
    rect->w = getRectProperties()->size.width;
    rect->h = getRectProperties()->size.height;

    // This is a temporary measure and should be removed in the future...

    SDL_SetRenderViewport(renderer, rect);
  }
}

void UI::cleanup() { return; }
} // namespace UI
