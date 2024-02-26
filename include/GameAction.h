/**
 * @file GameAction.h
 * @brief Declaration of the GameAction class which features core component for
 * recognizing events
 *
 * @version
 * - 1.0: Initial implementation (dexter@nekocake.cafe) (2024-02-15)
 */

#ifndef GAME_ACTION_H
#define GAME_ACTION_H

#include "Map.h"

namespace GameAction {
template <typename T> class GameAction {
public:
  GameAction(int actionCode) : actionCode(actionCode) {}

  virtual ~GameAction() { cleanup(); }

  int getActionCode() { return actionCode; }

  std::vector<T> getKeys() { return keys; }

  void addKey(T t) { keys.push_back(t); }

private:
  std::vector<T> keys;
  int actionCode;

  void cleanup() {}
};
} // namespace GameAction

#endif
