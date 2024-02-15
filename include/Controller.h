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
  int *key;
  int actionCode;
} GameAction;

class Controller {
public:
  Controller();
  ~Controller();

  void createGameAction(int key, int actionCode);
  void setEventHandler(EventHandler::EventHandler *neventHandler)

      void update();

private:
  Map::Map<GameAction> *gameActions;
  EventHandler::EventHandler *eventHandler;

  void addGameAction(GameAction *gameAction);
  Map::Map<GameAction> *getGameActions();
  GameAction *getApplicableGameAction(int key);
  EventHandler::EventHandler *getEventHandler();
  void cleanup();
};
} // namespace Controller

#endif
