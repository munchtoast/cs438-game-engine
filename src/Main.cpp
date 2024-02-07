#include "GameObject.h"
#include "GameWindow.h"
#include "MemoryManagement.h"
#include "Tile.h"
#include <SDL.h>
#include <mimalloc.h>
#include <spdlog/spdlog.h>

int main() {
  const int windowWidth = 640;
  const int windowHeight = 480;

  GameWindow::GameWindow gameWindow("Game Engine", windowWidth, windowHeight,
                                    SDL_WINDOW_RESIZABLE,
                                    SDL_RENDERER_PRESENTVSYNC);

  void *screenMemory = MemoryManagement::MemoryManagement::allocate(
      sizeof(GameObject::GameObject));
  GameObject::GameObject *screen = new (screenMemory)
      GameObject::GameObject(0, 0, windowWidth, windowHeight);

  void *cameraMemory = MemoryManagement::MemoryManagement::allocate(
      sizeof(GameObject::GameObject));
  GameObject::GameObject *camera = new (cameraMemory)
      GameObject::GameObject(0, 0, windowWidth, windowHeight);

  void *tileMemory =
      MemoryManagement::MemoryManagement::allocate(sizeof(Tile::Tile));
  Tile::Tile *tile = new (tileMemory) Tile::Tile(50, 50, 50, 50);

  tile->setColorChoice(255, 0, 0, 255);

  bool quit = false;
  SDL_Event e;

  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_EVENT_KEY_DOWN) {
        switch (e.key.keysym.sym) {
        case SDLK_LEFT:
          camera->setX(camera->getX() - 1);
          break;
        case SDLK_RIGHT:
          camera->setX(camera->getX() + 1);
          break;
        case SDLK_UP:
          camera->setY(camera->getY() - 1);
          break;
        case SDLK_DOWN:
          camera->setY(camera->getY() + 1);
          break;
        }
      }

      if (e.type == SDL_EVENT_QUIT) {
        quit = true;
      }
    }

    gameWindow.setRenderDrawColor(255, 255, 255, 255);
    gameWindow.clearScreen();

    gameWindow.setRenderDrawColor(tile->getColor()->r, tile->getColor()->g,
                                  tile->getColor()->b, tile->getColor()->a);

    screen->update();
    tile->update();
    camera->update();

    if (std::abs(tile->getX()) <= std::abs(camera->getW()) &&
        std::abs(tile->getY()) <= std::abs(camera->getH())) {
      SDL_Rect *dupe = MemoryManagement::MemoryManagement::DeepCopy<SDL_Rect *>(
                           tile->getRect())
                           .getValue();

      dupe->x = (dupe->x - camera->getX());
      dupe->y = (dupe->y - camera->getY());
      gameWindow.drawRect(dupe);
    }

    gameWindow.present();

    spdlog::info("Tile position: {}, {}", tile->getRect()->x,
                 tile->getRect()->y);
    spdlog::info("Camera position: {}, {}", camera->getRect()->x,
                 camera->getRect()->y);
  }
  SDL_Quit();

  screen->~GameObject();
  tile->~Tile();
  camera->~GameObject();

  screenMemory = MemoryManagement::MemoryManagement::deallocate(screenMemory);
  tileMemory = MemoryManagement::MemoryManagement::deallocate(tileMemory);
  cameraMemory = MemoryManagement::MemoryManagement::deallocate(cameraMemory);
  return 0;
}
