#include "Handler.h"
#include "MemoryManagement.h"

namespace Handler {

Handler::Handler(int actionCode) {
  setEventCallBack(
      new (MemoryManagement::MemoryManagement::allocate<EventCallBack>(
          sizeof(EventCallBack))) EventCallBack());

  subscribedGameObjects = new (MemoryManagement::MemoryManagement::allocate<
                               Map::Map<GameObject::GameObject>>(sizeof(
                              Map::Map::<GameObject::GameObject>))) Map::Map <
                          GameObject::GameObject >> ();

  Handler::setActionCode(actionCode);
}

Handler::~Handler() { cleanup(); }

void Handler::setEventCallBack(EventCallBack *ncallback) {
  callback = ncallback;
}

void Handler::setActionCode(int nactionCode) { actionCode = nactionCode; }

int Handler::getActionCode() { return actionCode; }

EventCallBack *Handler::getEventCallBack() { return callback; }

void subscribeObject()

    void Handler::cleanup() {
  setEventCallBack(static_cast<EventCallBack *>(
      MemoryManagement::MemoryManagement::deallocate<EventCallBack>(
          getEventCallBack())));
}
} // namespace Handler
