#include "GameObject.h"
#include "GameWindow.h"
#include "MemoryManagement.h"
#include "Tile.h"
#include <SDL.h>
#include <mimalloc.h>
#include <spdlog/spdlog.h>

int main() {
  GameWindow::GameWindow gameWindow(
      "Game Engine", 640, 480, SDL_WINDOW_RESIZABLE, SDL_RENDERER_PRESENTVSYNC);

  std::unique_ptr<Tile::Tile> tile =
      std::make_unique<Tile::Tile>(100, 100, 100, 100);

  tile->setColorChoice(255, 0, 0, 255);

  bool quit = false;
  SDL_Event e;

  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_EVENT_QUIT) {
        quit = true;
      }
    }
    gameWindow.setRenderDrawColor(255, 255, 255, 255);
    gameWindow.clearScreen();

    gameWindow.setRenderDrawColor(tile->getColor()->r, tile->getColor()->g,
                                  tile->getColor()->b, tile->getColor()->a);

    tile->update();
    gameWindow.drawRect(
        MemoryManagement::MemoryManagement::DeepCopy<SDL_FRect *>(
            tile->getRect())
            .getValue());

    gameWindow.present();
  }
  SDL_Quit();
  return 0;
}
