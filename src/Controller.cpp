#include "Controller.h"
#include "Map.h"

namespace Controller {
Controller::Controller() {
  gameActions =
      new (MemoryManagement::MemoryManagement::allocate<Map::Map<GameAction>>(
          sizeof(Map::Map<GameAction>))) Map::Map<GameAction>();

  eventHandler = new (
      MemoryManagement::MemoryManagement::allocate<EventHandler::EventHandler>(
          sizeof(EventHandler::EventHandler))) EventHandler::EventHandler();
}

Controller::~Controller() { Controller::cleanup(); }

void Controller::createGameAction(int *key, int actionCode) {
  GameAction *gameAction =
      new (MemoryManagement::MemoryManagement::allocate<Controller::GameAction>(
          sizeof(GameAction))) Controller::GameAction;

  gameAction->key = key;
  gameAction->actionCode = actionCode;
  Controller::addGameAction(gameAction);
}

void setEventHandler(EventHandler::EventHandler *neventHandler) {
  eventHandler = neventHandler;
}

/*
 * @brief The purpose of this function is to compare all of the key inputs
 *within the map data structure. Apply any GameAction applicable based on the
 *inputs received
 *
 **/
void Controller::update(SDL_Event &e) {
  GameAction *gameAction = Controller::getApplicableGameAction(e);

  if (gameAction != nullptr)
    getEventHandler()->handleEvent(gameAction->actionCode)
}

void Controller::addGameAction(GameAction *gameAction) {
  getGameActions()->add(gameAction);
}

Map::Map<GameAction> *Controller::getGameActions() { return gameActions; }

GameAction Controller::*getApplicableGameAction(int key) {
  for (size_t i = 0; i < Controller::getGameActions().getSize(); i++) {
    if (Controller::getGameActions()[i]->key == key)
      return Controller::getGameActions()[i];
  }
  return nullptr;
}

EventHandler Controller::*getEventHandler() { return eventHandler; }

void Controller::cleanup() {
  gameActions = static_cast<Map::Map<GameAction> *>(
      MemoryManagement::MemoryManagement::deallocate<Map::Map<GameAction>>(
          getGameActions()));

  eventHandler = static_cast<EventHandler::EventHandler *>(
      MemoryManagement::MemoryManagement::deallocate<
          EventHandler::EventHandler>(getEventHandler()));
}
} // namespace Controller
