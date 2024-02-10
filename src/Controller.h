/*
 * @file Controller.h
 * @brief Declaration of the Controller class which is responsible for
 * interaction with GameObjects and input handling
 *
 * @version
 * - 1.0: Initial implementation (dexter@nekocake.cafe) (2024-02-09)
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Map.h"

namespace Controller {
typedef struct {
  int key;
  int actionCode;
  int objectID;
} GameAction;

class Controller {
public:
  Controller();
  ~Controller();

  void addGameAction(GameAction *gameAction);
  Map::Map<GameAction> *getGameActions();

private:
  Map::Map<GameAction> *gameActions;
  void cleanup();
};
} // namespace Controller

#endif
