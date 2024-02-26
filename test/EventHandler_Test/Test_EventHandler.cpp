#include "Animation.h"
#include "EventHandler.h"
#include "GameObject.h"
#include "Handler.h"
#include "MemoryManagement.h"
#include "Util.h"
#include "gtest/gtest.h"

class EventHandlerTest : public ::testing::Test {
protected:
  EventHandler::EventHandler<GameObject::GameObject> *eventHandler;
  Handler::Handler<GameObject::GameObject> *t;

  void SetUp() override {
    eventHandler = new (MemoryManagement::MemoryManagement::allocate<
                        EventHandler::EventHandler<GameObject::GameObject>>(
        sizeof(EventHandler::EventHandler<GameObject::GameObject>)))
        EventHandler::EventHandler<GameObject::GameObject>();
    t = new (MemoryManagement::MemoryManagement::allocate<
             Handler::Handler<GameObject::GameObject>>(
        sizeof(Handler::Handler<GameObject::GameObject>)))
        Handler::Handler<GameObject::GameObject>(1);
  }

  void TearDown() override {
    eventHandler = MemoryManagement::MemoryManagement::deallocate<
        EventHandler::EventHandler<GameObject::GameObject>>(eventHandler);
  }
};

TEST_F(EventHandlerTest, CheckHandlerAddOne) {
  eventHandler->addHandler(t);
  ASSERT_TRUE(eventHandler->getHandlers() != nullptr);
}

TEST_F(EventHandlerTest, CheckHandlerAddMany) {
  Handler::Handler<GameObject::GameObject> *t1 =
      new (MemoryManagement::MemoryManagement::allocate<
           Handler::Handler<GameObject::GameObject>>(
          sizeof(Handler::Handler<GameObject::GameObject>)))
          Handler::Handler<GameObject::GameObject>(2);
  eventHandler->addHandler(t);
  eventHandler->addHandler(t1);
  ASSERT_TRUE(eventHandler->getHandlers() != nullptr);
}

TEST_F(EventHandlerTest, CheckHandleForMany) {
  Handler::Handler<GameObject::GameObject> *t1 =
      new (MemoryManagement::MemoryManagement::allocate<
           Handler::Handler<GameObject::GameObject>>(
          sizeof(Handler::Handler<GameObject::GameObject>)))
          Handler::Handler<GameObject::GameObject>(2);
  eventHandler->addHandler(t);
  eventHandler->addHandler(t1);

  t->setEventCallBack(
      new (MemoryManagement::MemoryManagement::allocate<Handler::EventCallBack>(
          sizeof(Handler::EventCallBack)))
          Handler::EventCallBack([]() { throw std::runtime_error("FAIL"); }));

  t1->setEventCallBack(
      new (MemoryManagement::MemoryManagement::allocate<Handler::EventCallBack>(
          sizeof(Handler::EventCallBack)))
          Handler::EventCallBack([]() { throw std::runtime_error("FAIL"); }));

  ASSERT_TRUE(eventHandler->getHandlers() != nullptr);
  ASSERT_THROW(eventHandler->handleEvent(1), std::runtime_error);
  ASSERT_THROW(eventHandler->handleEvent(2), std::runtime_error);
}
