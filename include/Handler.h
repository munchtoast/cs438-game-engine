/*
 * @file Handler.h
 * @brief Declaration of the Handler class which is responsible for handling
 * events within the game engine
 *
 * @note Features an autonomous lambda function that is responsible for
 * executing a block respective to the bind of the handler
 *
 * @version
 * - 1.0: Initial implementation (dexter@nekocake.cafe) (2024-02-15)
 */

#ifndef HANDLER_H
#define HANDLER_H

#include <functional>

namespace Handler {
using EventCallBack = std::function<void()>;

class Handler {
public:
  Handler(int actionCode);
  virtual ~Handler();

  void setEventCallBack(EventCallBack *callback);
  void setActionCode(int nactionCode);
  int getActionCode();
  EventCallBack *getEventCallBack();

  void subscribeObject(GameObject *gameObject);
  void unsubscribeObject(GameObject *gameObject);
  void notifyObjects();

private:
  EventCallBack *callback;
  Map::Map<GameObject::GameObject> *subscribedGameObjects;
  int actionCode;

  void cleanup();
};
} // namespace Handler

#endif
