/*
 * @file Controller.h
 * @brief Declaration of the Controller class which is responsible for
 * interaction with GameObjects and input handling
 *
 * @version
 * - 1.0: Initial implementation (dexter@nekocake.cafe) (2024-02-09)
 * - 1.1: Add features for associating GameObjects with
 * GameAction::GameAction<int>s (dexter@nekocake.cafe) (2024-02-14)
 * - 1.2: Add event handler as better alternative. Delegate the responsibilities
 * of manipulation to the event system (dexter@nekocake.cafe) (2024-02-15)
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "EventHandler.h"
#include "GameAction.h"
#include "GameObject.h"
#include "Map.h"

namespace Controller {
class Controller {
public:
  Controller();
  ~Controller();

  EventHandler::EventHandler<GameObject::GameObject> *getEventHandler();
  void addGameAction(GameAction::GameAction<int> *gameAction);

  void update(SDL_Event &e);

private:
  Map::Map<GameAction::GameAction<int>> *gameActions;
  EventHandler::EventHandler<GameObject::GameObject> *eventHandler;
  std::vector<int> ckeys;

  std::vector<int> getCKeys();
  void addCKeys(int key);
  void removeCKeys(int key);
  Map::Map<GameAction::GameAction<int>> *getGameActions();
  GameAction::GameAction<int> *getApplicableGameAction(std::vector<int> ckeys);
  bool Keys(std::vector<int> keys, std::vector<int> ckeys);
  bool cmpKeys(std::vector<int> keys, std::vector<int> ckeys);
  void cleanup();
};
} // namespace Controller

#endif
