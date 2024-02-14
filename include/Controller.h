/*
 * @file Controller.h
 * @brief Declaration of the Controller class which is responsible for
 * interaction with GameObjects and input handling
 *
 * @version
 * - 1.0: Initial implementation (dexter@nekocake.cafe) (2024-02-09)
 * - 1.1: Add features for associating GameObjects with GameActions
 * (dexter@nekocake.cafe) (2024-02-14)
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "GameObject.h"
#include "Map.h"

namespace Controller {
typedef struct {
  int *key;
  int actionCode;
} Action;

typedef struct {
  Action action;
  Map::Map<GameObject::GameObject> *gameObjects;
} GameAction;

class Controller {
public:
  Controller();
  ~Controller();

  void createGameAction(int key, int actionCode,
                        Map::Map<GameObject::GameObject> *gameObject);
  void update();

private:
  Map::Map<GameAction> *gameActions;

  void addGameAction(GameAction *gameAction);
  Map::Map<GameAction> *getGameActions();
  GameAction *getApplicableGameAction(int key);
  void cleanup();
};
} // namespace Controller

#endif
