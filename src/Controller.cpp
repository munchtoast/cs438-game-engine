#include "Controller.h"
#include "GameAction.h"
#include "GameObject.h"
#include "Map.h"
#include "spdlog/spdlog.h"

namespace Controller {
Controller::Controller() {
  gameActions = new (MemoryManagement::MemoryManagement::allocate<
                     Map::Map<GameAction::GameAction<int>>>(
      sizeof(Map::Map<GameAction::GameAction<int>>)))
      Map::Map<GameAction::GameAction<int>>();

  eventHandler = new (MemoryManagement::MemoryManagement::allocate<
                      EventHandler::EventHandler<GameObject::GameObject>>(
      sizeof(EventHandler::EventHandler<GameObject::GameObject>)))
      EventHandler::EventHandler<GameObject::GameObject>();
}

Controller::~Controller() { Controller::cleanup(); }

/**
 * @brief The purpose of this function is to compare all of the key inputs
 *within the map data structure. Apply any GameAction::GameAction<int>
 *applicable based on the inputs received
 *
 * @param e - Address of event captured in a cycle
 */
void Controller::update(SDL_Event &e) {
  if (e.type == SDL_EVENT_KEY_DOWN) {
    auto k = std::find(getCKeys().begin(), getCKeys().end(), e.key.keysym.sym);

    if (k == getCKeys().end())
      addCKeys(e.key.keysym.sym);

  } else if (e.type == SDL_EVENT_KEY_UP)
    removeCKeys(e.key.keysym.sym);

  GameAction::GameAction<int> *gameAction =
      Controller::getApplicableGameAction(ckeys);

  /**
   * @brief An applicable game action is recognized given from user input. Go
   *ahead and run the handler associated with the action code. Then make sure to
   *clear all keys to receive new inputs from user.
   *
   **/
  if (gameAction != nullptr) {
    getEventHandler()->handleEvent(gameAction->getActionCode());
    ckeys.clear();
  }
}

void Controller::addGameAction(GameAction::GameAction<int> *gameAction) {
  getGameActions()->add(gameAction);
}

Map::Map<GameAction::GameAction<int>> *Controller::getGameActions() {
  return gameActions;
}

GameAction::GameAction<int> *
Controller::getApplicableGameAction(std::vector<int> ckeys) {
  GameAction::GameAction<int> **gameActionMap =
      Controller::getGameActions()->getMap();

  for (size_t i = 0; i < Controller::getGameActions()->getSize(); i++)
    if (Controller::cmpKeys(gameActionMap[i]->getKeys(), ckeys))
      return gameActionMap[i];

  return nullptr;
}

bool Controller::cmpKeys(std::vector<int> keys, std::vector<int> ckeys) {
  if (keys.size() != ckeys.size())
    return false;

  std::sort(keys.begin(), keys.end());
  std::sort(ckeys.begin(), ckeys.end());

  return keys == ckeys;
}

EventHandler::EventHandler<GameObject::GameObject> *
Controller::getEventHandler() {
  return eventHandler;
}

std::vector<int> Controller::getCKeys() { return ckeys; }

void Controller::addCKeys(int key) { ckeys.push_back(key); }

void Controller::removeCKeys(int key) {
  ckeys.erase(std::remove(ckeys.begin(), ckeys.end(), key), ckeys.end());
}

void Controller::cleanup() {
  gameActions = static_cast<Map::Map<GameAction::GameAction<int>> *>(
      MemoryManagement::MemoryManagement::deallocate<
          Map::Map<GameAction::GameAction<int>>>(getGameActions()));

  eventHandler =
      static_cast<EventHandler::EventHandler<GameObject::GameObject> *>(
          MemoryManagement::MemoryManagement::deallocate<
              EventHandler::EventHandler<GameObject::GameObject>>(
              getEventHandler()));
}
} // namespace Controller
