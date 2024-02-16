#include "Controller.h"
#include "Map.h"
#include "spdlog/spdlog.h"

namespace Controller {
Controller::Controller() {
  gameActions =
      new (MemoryManagement::MemoryManagement::allocate<Map::Map<GameAction>>(
          sizeof(Map::Map<GameAction>))) Map::Map<GameAction>();

  // Why are you creating an event handler here and in main? Just put it in one
  // spot. Just let the controller have an event handler. Easy.
  eventHandler = new (MemoryManagement::MemoryManagement::allocate<
                      EventHandler::EventHandler<GameObject::GameObject>>(
      sizeof(EventHandler::EventHandler<GameObject::GameObject>)))
      EventHandler::EventHandler<GameObject::GameObject>();
}

Controller::~Controller() { Controller::cleanup(); }

void Controller::createGameAction(Map::Map<int> *key, int actionCode) {
  GameAction *gameAction =
      new (MemoryManagement::MemoryManagement::allocate<GameAction>(
          sizeof(GameAction))) GameAction;

  gameAction->keys = key;
  gameAction->actionCode = actionCode;
  Controller::addGameAction(gameAction);
}

void Controller::setEventHandler(
    EventHandler::EventHandler<GameObject::GameObject> *neventHandler) {
  eventHandler = neventHandler;
}

/*
 * @brief The purpose of this function is to compare all of the key inputs
 *within the map data structure. Apply any GameAction applicable based on the
 *inputs received
 *
 **/
void Controller::update(SDL_Event &e) {
  Map::Map<int> *ckeys =
      new (MemoryManagement::MemoryManagement::allocate<Map::Map<int>>(
          sizeof(Map::Map<int>))) Map::Map<int>();
  ckeys->add(&e.key.keysym.sym);
  spdlog::info(e.key.keysym.sym);
  GameAction *gameAction = Controller::getApplicableGameAction(ckeys);

  if (gameAction != nullptr)
    getEventHandler()->handleEvent(gameAction->actionCode);
}

void Controller::addGameAction(GameAction *gameAction) {
  getGameActions()->add(gameAction);
}

Map::Map<GameAction> *Controller::getGameActions() { return gameActions; }

GameAction *Controller::getApplicableGameAction(Map::Map<int> *ckeys) {
  GameAction **gameActionMap = Controller::getGameActions()->getMap();

  for (size_t i = 0; i < Controller::getGameActions()->getSize(); i++)
    if (Controller::compKeys(gameActionMap[i]->keys, ckeys))
      return gameActionMap[i];

  return nullptr;
}

bool Controller::compKeys(Map::Map<int> *keys, Map::Map<int> *ckeys) {
  bool match = false;
  int **memkey = keys->getMap();
  int **memckey = ckeys->getMap();

  if (keys->getSize() != ckeys->getSize())
    return false;

  for (size_t i = 0; i < keys->getSize(); i++) {
    match = false;
    for (size_t j = 0; j < keys->getSize(); j++) {
      if (memkey[i] == memckey[j]) {
        match = true;
        break;
      }
    }

    if (!match) {
      return false;
    }
  }
  return true;
}

EventHandler::EventHandler<GameObject::GameObject> *
Controller::getEventHandler() {
  return eventHandler;
}

void Controller::cleanup() {
  gameActions = static_cast<Map::Map<GameAction> *>(
      MemoryManagement::MemoryManagement::deallocate<Map::Map<GameAction>>(
          getGameActions()));

  eventHandler =
      static_cast<EventHandler::EventHandler<GameObject::GameObject> *>(
          MemoryManagement::MemoryManagement::deallocate<
              EventHandler::EventHandler<GameObject::GameObject>>(
              getEventHandler()));
}
} // namespace Controller
