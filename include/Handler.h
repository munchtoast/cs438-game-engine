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
 * - 1.1: Force Complete Clear to false for subscribed objects, and enforce
 * callback to be manually set (dexter@nekocake.cafe) (2024-02-16)
 *        @reason The responsibility of these objects are not on the handler
 * itself, but the object map, or the game state
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
  Handler(int actionCode) {
    callback = static_cast<EventCallBack *>(nullptr);

    subscribedObjects =
        new (MemoryManagement::MemoryManagement::allocate<Map::Map<T>>(
            sizeof(Map::Map<T>))) Map::Map<T>();

    subscribedObjects->setCC(false);

    Handler::setActionCode(actionCode);
  }

  virtual ~Handler() { cleanup(); }

  void setEventCallBack(EventCallBack *ncallback) { callback = ncallback; }

  void setActionCode(int nactionCode) { actionCode = nactionCode; }
  int getActionCode() { return actionCode; }

  void subscribeObject(T *object) { getSubscribedObjects()->add(object); }

  void unsubscribeObject(T *object) { getSubscribedObjects()->remove(object); }

  void callBackAndNotifyObjects() {
    EventCallBack c = *getEventCallBack();
    notifyObjects();
    c();
  }

private:
  EventCallBack *callback;
  Map::Map<T> *subscribedObjects;
  int actionCode;

  Map::Map<T> *getSubscribedObjects() { return subscribedObjects; }

  void cleanup() {
    if (!Util::Util::checkIfNullPtr(static_cast<void *>(getEventCallBack())))
      setEventCallBack(static_cast<EventCallBack *>(
          MemoryManagement::MemoryManagement::deallocate<EventCallBack>(
              getEventCallBack())));

    subscribedObjects = static_cast<Map::Map<T> *>(
        MemoryManagement::MemoryManagement::deallocate(subscribedObjects));
  }

  void notifyObjects() {
    T **mem = getSubscribedObjects()->getMap();
    for (size_t i = 0; i < getSubscribedObjects()->getSize(); i++) {
      mem[i]->handleEvent();
    }
  }

  EventCallBack *getEventCallBack() { return callback; }
};
} // namespace Handler

#endif
