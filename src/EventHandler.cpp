#include "EventHandler.h"
#include <spdlog/spdlog.h>

namespace EventHandler {
EventHandler::EventHandler() {
  setHandlers(new (
      MemoryManagement::MemoryManagement::allocate<Map::Map<Handler::Handler>>(
          sizeof(Map::Map<Handler::Handler>))) Map::Map<Handler::Handler>());
}

EventHandler::~EventHandler() { cleanup(); }

void EventHandler::addHandler(Handler::Handler *handler) {
  getHandlers()->add(handler);
}

void EventHandler::handleEvent(int actionCode) {
  Handler::EventCallBack c;
  for (size_t i = 0; i < getHandlers()->getSize(); i++) {
    if (getHandlers()->getMap()[i]->getActionCode() == actionCode) {
      c = *getHandlers()->getMap()[i]->getEventCallBack();
      c();
    } else
      spdlog::warn("Action code does not have a valid handler");
  }
}

void EventHandler::setHandlers(Map::Map<Handler::Handler> *nhandlers) {
  handlers = nhandlers;
}

Map::Map<Handler::Handler> *EventHandler::getHandlers() { return handlers; }

void EventHandler::cleanup() {
  setHandlers(static_cast<Map::Map<Handler::Handler> *>(
      MemoryManagement::MemoryManagement::deallocate<
          Map::Map<Handler::Handler>>(getHandlers())));
}
} // namespace EventHandler
