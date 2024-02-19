#include "UI.h"
#include "Util.h"
#include <SDL.h>

namespace UI {
UI::UI(float x, float y, float width, float height)
    : GameObject(x, y, width, height) {}

UI::~UI() { UI::cleanup(); }

void UI::move(int deltaX, int deltaY) {
  UI::setX(UI::getX() + deltaX);
  UI::setY(UI::getY() + deltaY);
}

void UI::apply(SDL_Renderer *renderer) {
  if (!Util::Util::checkIfNullPtr(renderer)) {

    SDL_SetRenderViewport(renderer, (SDL_Rect *)UI::getRect());
  }
}

void UI::cleanup() { return; }
} // namespace UI
