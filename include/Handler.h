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

#include "Map.h"
#include "MemoryManagement.h"
#include <functional>

namespace Handler {
using EventCallBack = std::function<void()>;

template <typename T> class Handler {
public:
  // We need to not use this, just use std::vector and also std::function.
  Handler(int actionCode) {

    setEventCallBack(
        new (MemoryManagement::MemoryManagement::allocate<EventCallBack>(
            sizeof(EventCallBack))) EventCallBack());

    subscribedObjects =
        new (MemoryManagement::MemoryManagement::allocate<Map::Map<T>>(
            sizeof(Map::Map<T>))) Map::Map<T>();

    Handler::setActionCode(actionCode);
  }

  virtual ~Handler() { cleanup(); }

  void setEventCallBack(EventCallBack *ncallback) { callback = ncallback; }

  void setActionCode(int nactionCode) { actionCode = nactionCode; }
  int getActionCode() { return actionCode; }
  EventCallBack *getEventCallBack() { return callback; }

  void subscribeObject(T *object) { getSubscribedObjects()->add(object); }

  void unsubscribeObject(T *object) { getSubscribedObjects()->remove(object); }

  void notifyObjects() {
    T **mem = getSubscribedObjects()->getMap();
    for (size_t i = 0; i < getSubscribedObjects()->getSize(); i++) {
      mem[i]->handleEvent();
    }
  }

private:
  EventCallBack *callback;
  Map::Map<T> *subscribedObjects;
  int actionCode;

  Map::Map<T> *getSubscribedObjects() { return subscribedObjects; }

  void cleanup() {
    if (!Util::Util::checkIfNullPtr(getEventCallBack()))
      setEventCallBack(static_cast<EventCallBack *>(
          MemoryManagement::MemoryManagement::deallocate<EventCallBack>(
              getEventCallBack())));

    subscribedObjects = static_cast<Map::Map<T> *>(
        MemoryManagement::MemoryManagement::deallocate(subscribedObjects,
                                                       false));
  }
};
} // namespace Handler

#endif
