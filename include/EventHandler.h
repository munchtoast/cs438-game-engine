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
class EventHandler {
public:
  EventHandler();
  virtual ~EventHandler();

  void addHandler(Handler::Handler *handler);
  void handleEvent(int actionCode);
  Map::Map<Handler::Handler> *getHandlers();

private:
  Map::Map<Handler::Handler> *handlers;

  void setHandlers(Map::Map<Handler::Handler> *handler);

  void cleanup();
};
} // namespace EventHandler

#endif
