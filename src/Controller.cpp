#include "Controller.h"
#include "Map.h"

namespace Controller {
Controller::Controller() {
  gameActions =
      new (MemoryManagement::MemoryManagement::allocate<Map::Map<GameAction>>(
          sizeof(Map::Map<GameAction>))) Map::Map<GameAction>();
}

Controller::~Controller() { Controller::cleanup(); }

void Controller::addGameAction(GameAction *gameAction) {
  getGameActions()->add(gameAction);
}

Map::Map<GameAction> *Controller::getGameActions() { return gameActions; }

void Controller::cleanup() {
  gameActions = static_cast<Map::Map<GameAction> *>(
      MemoryManagement::MemoryManagement::deallocate(getGameActions()));
}
} // namespace Controller
