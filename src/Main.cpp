#include "Controller.h"
#include "EventHandler.h"
#include "GameObject.h"
#include "GameWindow.h"
#include "Handler.h"
#include "Map.h"
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

  Map::Map<GameObject::GameObject> *gameObjectMap =
      new (MemoryManagement::MemoryManagement::allocate<
           Map::Map<GameObject::GameObject>>(
          sizeof(Map::Map<GameObject::GameObject>)))
          Map::Map<GameObject::GameObject>();

  GameObject::GameObject *screen =
      new (MemoryManagement::MemoryManagement::allocate<GameObject::GameObject>(
          sizeof(GameObject::GameObject)))
          GameObject::GameObject(0, 0, windowWidth, windowHeight);

  GameObject::GameObject *camera =
      new (MemoryManagement::MemoryManagement::allocate<GameObject::GameObject>(
          sizeof(GameObject::GameObject)))
          GameObject::GameObject(0, 0, windowWidth, windowHeight);

  Tile::Tile *tile =
      new (MemoryManagement::MemoryManagement::allocate<Tile::Tile>(
          sizeof(Tile::Tile))) Tile::Tile(50, 50, 50, 50);

  Tile::Tile *hitBox =
      new (MemoryManagement::MemoryManagement::allocate<Tile::Tile>(
          sizeof(Tile::Tile))) Tile::Tile(50, 50, 50, 50);

  tile->addSubGameObject(hitBox);

  gameObjectMap->add(screen);
  gameObjectMap->add(camera);
  gameObjectMap->add(tile);

  // Creates a handler that handles an action SDLK_RIGHT:
  Handler::Handler<GameObject::GameObject> *handler =
      new (MemoryManagement::MemoryManagement::allocate<
           Handler::Handler<GameObject::GameObject>>(
          sizeof(Handler::Handler<GameObject::GameObject>)))
          Handler::Handler<GameObject::GameObject>(SDLK_RIGHT);

  // Subscribe object
  handler->subscribeObject(camera);

  // handler->setEventCallBack([&camera]() { camera->setX(camera->getX() + 5);
  // });

  // You are not freeing the inner object.
  // Controller::Controller *controller = new
  // (MemoryManagement::MemoryManagement::allocate<Controller::Controller>(sizeof(Controller::Controller)))
  // Controller::Controller();

  // Map::Map<int> *key = new
  // (MemoryManagement::MemoryManagement::allocate<Map::Map<int>>(sizeof(Map::Map<int>)))
  // Map::Map<int>();

  // key->add((int *) SDLK_RIGHT);

  // controller->createGameAction(key, 1);

  tile->setColorChoice(255, 0, 0, 255);

  bool quit = false;
  SDL_Event e;

  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      // if (e.type == SDL_EVENT_KEY_DOWN) {
      //   switch (e.key.keysym.sym) {
      //   case SDLK_LEFT:
      //     camera->setX(camera->getX() - 5);
      //     break;
      //   case SDLK_RIGHT:
      //     camera->setX(camera->getX() + 5);
      //     break;
      //   case SDLK_UP:
      //     camera->setY(camera->getY() - 5);
      //     break;
      //   case SDLK_DOWN:
      //     camera->setY(camera->getY() + 5);
      //     break;
      //   }
      // }

      if (e.type == SDL_EVENT_QUIT) {
        quit = true;
      }
    }

    gameWindow.setRenderDrawColor(255, 255, 255, 255);
    gameWindow.clearScreen();

    gameWindow.setRenderDrawColor(tile->getColor()->r, tile->getColor()->g,
                                  tile->getColor()->b, tile->getColor()->a);

    // controller->update(e);
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

    // spdlog::info("Tile position: {}, {}", tile->getRect()->x,
    //              tile->getRect()->y);
    // spdlog::info("Camera position: {}, {}", camera->getRect()->x,
    //              camera->getRect()->y);
  }
  SDL_Quit();

  gameObjectMap = static_cast<Map::Map<GameObject::GameObject> *>(
      MemoryManagement::MemoryManagement::deallocate<
          Map::Map<GameObject::GameObject>>(gameObjectMap));

  MemoryManagement::MemoryManagement::deallocate<
      Handler::Handler<GameObject::GameObject>>(handler);

  // controller = static_cast<Controller::Controller
  // *>(MemoryManagement::MemoryManagement::deallocate<Controller::Controller>(controller));

  // key = static_cast<Map::Map<int>
  // *>(MemoryManagement::MemoryManagement::deallocate<Map::Map<int>>(key));

  return 0;
}
