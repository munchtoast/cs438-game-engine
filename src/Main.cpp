#include "Camera.h"
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

  void *tileMemory =
      MemoryManagement::MemoryManagement::allocate(sizeof(Tile::Tile));
  Tile::Tile *tile = new (tileMemory) Tile::Tile(50, 50, 50, 50);

  void *cameraMemory =
      MemoryManagement::MemoryManagement::allocate(sizeof(Camera::Camera));
  Camera::Camera *camera = new (cameraMemory) Camera::Camera(0, 0, 640, 480);

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
    // camera->apply(gameWindow.getRenderer());

    gameWindow.setRenderDrawColor(tile->getColor()->r, tile->getColor()->g,
                                  tile->getColor()->b, tile->getColor()->a);

    tile->update();
    camera->update();
    gameWindow.drawRect(
        MemoryManagement::MemoryManagement::DeepCopy<SDL_FRect *>(
            tile->getRect())
            .getValue());

    gameWindow.present();

    spdlog::info("Tile position: {}, {}", tile->getRect()->x,
                 tile->getRect()->y);
    spdlog::info("Camera position: {}, {}", camera->getRect()->x,
                 camera->getRect()->y);
  }
  SDL_Quit();

  tileMemory = MemoryManagement::MemoryManagement::deallocate(tileMemory);
  cameraMemory = MemoryManagement::MemoryManagement::deallocate(cameraMemory);
  return 0;
}
