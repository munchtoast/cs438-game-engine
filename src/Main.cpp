#include "GameWindow.h"
#include <SDL.h>
#include <mimalloc.h>
#include <spdlog/spdlog.h>

int main() {
  GameWindow gameWindow;

  bool quit = false;
  SDL_Event e;

  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_EVENT_QUIT) {
        quit = true;
      }
    }
  }
  return 0;
}
