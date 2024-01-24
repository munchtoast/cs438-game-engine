#include "window.h"
#include <SDL.h>
#include <cute_png.h>
#include <cute_sound.h>
#include <cute_tiled.h>
#include <mimalloc.h>
#include <spdlog/spdlog.h>

void drawWindow() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    // Handle initialization error
    return;
  }

  // Create a window
  SDL_Window *window =
      SDL_CreateWindow("Window", 352, 430, SDL_WINDOW_RESIZABLE);

  if (!window) {
    // Handle window creation error
    SDL_Quit();
    return;
  }

  // Main loop
  bool quit = false;
  SDL_Event e;

  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_EVENT_QUIT) {
        quit = true;
      }
    }
  }

  // Cleanup
  SDL_DestroyWindow(window);
  SDL_Quit();
}
