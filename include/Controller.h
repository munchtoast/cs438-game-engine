/*
 * @file Controller.h
 * @brief Declaration of the Controller class which is responsible for
 * interaction with GameObjects and input handling
 *
 * @version
 * - 1.0: Initial implementation (dexter@nekocake.cafe) (2024-02-09)
 * - 1.1: Add features for associating GameObjects with GameActions
 * (dexter@nekocake.cafe) (2024-02-14)
 * - 1.2: Add event handler as better alternative. Delegate the responsibilities
 * of manipulation to the event system (dexter@nekocake.cafe) (2024-02-15)
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "EventHandler.h"
#include "GameObject.h"
#include "Map.h"

namespace Controller {
typedef struct {
  Map::Map<int> *keys;
  int actionCode;
} GameAction;

class Controller {
public:
  Controller();
  ~Controller();

  void createGameAction(Map::Map<int> *keys, int actionCode);
  void setEventHandler(
      EventHandler::EventHandler<GameObject::GameObject> *neventHandler);
  EventHandler::EventHandler<GameObject::GameObject> *getEventHandler();

  void update(SDL_Event &e);

private:
  Map::Map<GameAction> *gameActions;
  EventHandler::EventHandler<GameObject::GameObject> *eventHandler;

  void addGameAction(GameAction *gameAction);
  Map::Map<GameAction> *getGameActions();
  GameAction *getApplicableGameAction(Map::Map<int> *ckeys);
  bool compKeys(Map::Map<int> *keys, Map::Map<int> *ckeys);
  void cleanup();
};
} // namespace Controller

#endif
