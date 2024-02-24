// File: GameWindow.cpp

#include "GameWindow.h"
#include "GameObject.h"
#include <SDL.h>
#include <spdlog/spdlog.h>

namespace GameWindow {
/**
 * @brief Constructs a GameWindow instance.
 *
 * @param title - Title of the game window.
 * @param w - Width of the game window.
 * @param h - Height of the game window.
 * @param Uint32 windowFlags - Window args to pass to SDL
 * @param Uint32 rendererFlags - Renderer args to pass to SDL
 */
GameWindow::GameWindow(const char *title, const int w, const int h,
                       const Uint32 windowFlags, const Uint32 rendererFlags) {

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    return;

  window = SDL_CreateWindow(title, w, h, windowFlags);

  if (!window) {
    spdlog::error("Cannot create window! Exiting...");
    cleanup();
  }

  // NULL uses any video driver available to the system
  renderer = SDL_CreateRenderer(window, NULL, rendererFlags);

  if (!renderer) {
    spdlog::error("Cannot establish renderer! Exiting...");
    cleanup();
  }
}

GameWindow::~GameWindow() { GameWindow::cleanup(); }

SDL_Window *GameWindow::getWindow() { return window; }

SDL_Renderer *GameWindow::getRenderer() { return renderer; }

void GameWindow::clearScreen() {
  setRenderDrawColor(255, 255, 255, 255);
  SDL_RenderClear(renderer);
}

void GameWindow::setRenderDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void GameWindow::draw(int x, int y, RectStruct::Color *c) {
  setRenderDrawColor(c->r, c->g, c->b, c->a);
  SDL_RenderPoint(getRenderer(), x, y);
}

void GameWindow::drawRect(int x, int y, int width, int height,
                          RectStruct::Color *c) {
  for (int i = x; i < x + width; i++) {
    for (int j = y; j < y + height; j++) {
      draw(i, j, c);
    }
  }
}

void GameWindow::present() { SDL_RenderPresent(renderer); }

void GameWindow::cleanup() {
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
}
} // namespace GameWindow
