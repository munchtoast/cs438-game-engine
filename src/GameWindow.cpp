#include "GameWindow.h"
#include <SDL.h>
#include <cute_png.h>
#include <cute_sound.h>
#include <cute_tiled.h>
#include <mimalloc.h>
#include <spdlog/spdlog.h>

GameWindow::GameWindow() {
  // Handle initialization error
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    return;

  // Create a window
  GameWindow::window =
      SDL_CreateWindow("Window", 352, 430, SDL_WINDOW_RESIZABLE);

  // Handle window creation error
  if (!GameWindow::window) {
    spdlog::error("Cannot create window! Exiting...");
    cleanup();
  }

  // Create the renderer
  Uint32 flags = SDL_RENDERER_PRESENTVSYNC;

  GameWindow::renderer =
      SDL_CreateRenderer(GameWindow::window,
                         NULL, // Go ahead and use any video driver available
                         flags);

  // Handle renderer creation error
  if (!renderer) {
    spdlog::error("Cannot establish renderer! Exiting...");
    cleanup();
  }
}

// Deconstruct
GameWindow::~GameWindow() { cleanup(); }

SDL_Window *GameWindow::getWindow() { return GameWindow::window; }

SDL_Renderer *GameWindow::getRenderer() { return GameWindow::renderer; }

void GameWindow::clearScreen() { SDL_RenderClear(GameWindow::renderer); }

void GameWindow::present() { SDL_RenderPresent(GameWindow::renderer); }

void GameWindow::cleanup() {
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(GameWindow::renderer);
  SDL_Quit();
}
