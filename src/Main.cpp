#include "Animation.h"
#include "Controller.h"
#include "EventHandler.h"
#include "GameObject.h"
#include "GameWindow.h"
#include "Handler.h"
#include "Map.h"
#include "MemoryManagement.h"
#include "RectStruct.h"
#include "Tile.h"
#include <SDL.h>
#include <mimalloc.h>
#include <spdlog/spdlog.h>

int main() {
  // Init basic GameObjects and Window
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

  // Subscribe Move Right
  Handler::EventCallBack *moveRight = new (
      MemoryManagement::MemoryManagement::allocate<Handler::EventCallBack>(
          sizeof(Handler::EventCallBack)))
      Handler::EventCallBack([&camera]() { camera->setX(camera->getX() + 5); });

  Handler::Handler<GameObject::GameObject> *handlerRight =
      new (MemoryManagement::MemoryManagement::allocate<
           Handler::Handler<GameObject::GameObject>>(
          sizeof(Handler::Handler<GameObject::GameObject>)))
          Handler::Handler<GameObject::GameObject>(1);

  handlerRight->subscribeObject(camera);

  handlerRight->setEventCallBack(moveRight);

  // Subscribe Move Left
  Handler::EventCallBack *moveLeft = new (
      MemoryManagement::MemoryManagement::allocate<Handler::EventCallBack>(
          sizeof(Handler::EventCallBack)))
      Handler::EventCallBack([&camera]() { camera->setX(camera->getX() - 5); });

  Handler::Handler<GameObject::GameObject> *handlerLeft =
      new (MemoryManagement::MemoryManagement::allocate<
           Handler::Handler<GameObject::GameObject>>(
          sizeof(Handler::Handler<GameObject::GameObject>)))
          Handler::Handler<GameObject::GameObject>(2);

  handlerLeft->subscribeObject(camera);

  handlerLeft->setEventCallBack(moveLeft);

  // Subscribe Move Up
  Handler::EventCallBack *moveUp = new (
      MemoryManagement::MemoryManagement::allocate<Handler::EventCallBack>(
          sizeof(Handler::EventCallBack)))
      Handler::EventCallBack([&camera]() { camera->setY(camera->getY() - 5); });

  Handler::Handler<GameObject::GameObject> *handlerUp =
      new (MemoryManagement::MemoryManagement::allocate<
           Handler::Handler<GameObject::GameObject>>(
          sizeof(Handler::Handler<GameObject::GameObject>)))
          Handler::Handler<GameObject::GameObject>(3);

  handlerUp->subscribeObject(camera);

  handlerUp->setEventCallBack(moveUp);

  // Subscribe Move Down
  Handler::EventCallBack *moveDown = new (
      MemoryManagement::MemoryManagement::allocate<Handler::EventCallBack>(
          sizeof(Handler::EventCallBack)))
      Handler::EventCallBack([&camera]() { camera->setY(camera->getY() + 5); });

  Handler::Handler<GameObject::GameObject> *handlerDown =
      new (MemoryManagement::MemoryManagement::allocate<
           Handler::Handler<GameObject::GameObject>>(
          sizeof(Handler::Handler<GameObject::GameObject>)))
          Handler::Handler<GameObject::GameObject>(4);

  handlerDown->subscribeObject(camera);

  handlerDown->setEventCallBack(moveDown);

  // Controller settings
  Controller::Controller *controller =
      new (MemoryManagement::MemoryManagement::allocate<Controller::Controller>(
          sizeof(Controller::Controller))) Controller::Controller();

  controller->getEventHandler()->addHandler(handlerRight);
  controller->getEventHandler()->addHandler(handlerLeft);
  controller->getEventHandler()->addHandler(handlerUp);
  controller->getEventHandler()->addHandler(handlerDown);

  // Assign Game Actions
  GameAction::GameAction<int> *gameActionMoveRight = new (
      MemoryManagement::MemoryManagement::allocate<GameAction::GameAction<int>>(
          sizeof(GameAction::GameAction<int>))) GameAction::GameAction<int>(1);

  GameAction::GameAction<int> *gameActionMoveLeft = new (
      MemoryManagement::MemoryManagement::allocate<GameAction::GameAction<int>>(
          sizeof(GameAction::GameAction<int>))) GameAction::GameAction<int>(2);

  GameAction::GameAction<int> *gameActionMoveUp = new (
      MemoryManagement::MemoryManagement::allocate<GameAction::GameAction<int>>(
          sizeof(GameAction::GameAction<int>))) GameAction::GameAction<int>(3);

  GameAction::GameAction<int> *gameActionMoveDown = new (
      MemoryManagement::MemoryManagement::allocate<GameAction::GameAction<int>>(
          sizeof(GameAction::GameAction<int>))) GameAction::GameAction<int>(4);

  controller->addGameAction(gameActionMoveRight);
  gameActionMoveRight->addKey(SDLK_RIGHT);

  controller->addGameAction(gameActionMoveLeft);
  gameActionMoveLeft->addKey(SDLK_LEFT);

  controller->addGameAction(gameActionMoveUp);
  gameActionMoveUp->addKey(SDLK_UP);

  controller->addGameAction(gameActionMoveDown);
  gameActionMoveDown->addKey(SDLK_DOWN);

  tile->setColorChoice(255, 0, 0, 255);

  Animation::Cel *cel =
      new (MemoryManagement::MemoryManagement::allocate<Animation::Cel>(
          sizeof(Animation::Cel))) Animation::Cel();

  Map::Map<Animation::Cel> *cels = new (
      MemoryManagement::MemoryManagement::allocate<Map::Map<Animation::Cel>>(
          sizeof(Map::Map<Animation::Cel>))) Map::Map<Animation::Cel>();

  Map::Map<RectStruct::Rect> *ani = new (
      MemoryManagement::MemoryManagement::allocate<Map::Map<RectStruct::Rect>>(
          sizeof(Map::Map<RectStruct::Rect>))) Map::Map<RectStruct::Rect>();

  RectStruct::Rect *block1 =
      new (MemoryManagement::MemoryManagement::allocate<RectStruct::Rect>(
          sizeof(RectStruct::Rect))) RectStruct::Rect;

  RectStruct::Rect *block2 =
      new (MemoryManagement::MemoryManagement::allocate<RectStruct::Rect>(
          sizeof(RectStruct::Rect))) RectStruct::Rect;

  block1->color.r = 255;
  block2->color.b = 255;

  ani->add(block1);
  ani->add(block2);

  cel->setPixels(ani);

  cels->add(cel);

  (tile->getAnimation())->addCels(cels);

  bool quit = false;
  SDL_Event e;

  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      controller->update(e);

      if (e.type == SDL_EVENT_QUIT) {
        quit = true;
      }
    }

    gameWindow.render(gameObjectMap, camera);
  }
  SDL_Quit();

  gameObjectMap = static_cast<Map::Map<GameObject::GameObject> *>(
      MemoryManagement::MemoryManagement::deallocate<
          Map::Map<GameObject::GameObject>>(gameObjectMap));

  controller = static_cast<Controller::Controller *>(
      MemoryManagement::MemoryManagement::deallocate<Controller::Controller>(
          controller));

  return 0;
}
