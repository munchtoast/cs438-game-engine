/*
 * @file EventHandler.h
 * @brief Declaration of the EventHandler class responsible for holding a
 * collection of Handlers.
 *
 * @note All dependencies required from Handler.h must be fulfilled
 *
 * @version
 * - 1.0: Initial implementation (dexter@nekocake.cafe) (2024-02-15)
 */

#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "Handler.h"
#include "Map.h"

namespace EventHandler {
template <typename T> class EventHandler {
public:
  EventHandler() {
    setHandlers(new (MemoryManagement::MemoryManagement::allocate<
                     Map::Map<Handler::Handler<T>>>(sizeof(
        Map::Map<Handler::Handler<T>>))) Map::Map<Handler::Handler<T>>());
  }

  virtual ~EventHandler() { cleanup(); }

  void addHandler(Handler::Handler<T> *handler) { getHandlers()->add(handler); }

  void handleEvent(int actionCode) {
    Handler::EventCallBack c;
    for (size_t i = 0; i < getHandlers()->getSize(); i++) {
      if (getHandlers()->getMap()[i]->getActionCode() == actionCode) {
        c = *getHandlers()->getMap()[i]->getEventCallBack();
        c();
      } else
        spdlog::warn("Action code does not have a valid handler");
    }
  }

  Map::Map<Handler::Handler<T>> *getHandlers() { return handlers; }

private:
  Map::Map<Handler::Handler<T>> *handlers;

  void setHandlers(Map::Map<Handler::Handler<T>> *nhandlers) {
    handlers = nhandlers;
  }

  void cleanup() {
    setHandlers(static_cast<Map::Map<Handler::Handler<T>> *>(
        MemoryManagement::MemoryManagement::deallocate<
            Map::Map<Handler::Handler<T>>>(getHandlers())));
  }
};
} // namespace EventHandler

#endif
