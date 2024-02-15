#include "EventHandler.h"
#include "Handler.h"
#include "MemoryManagement.h"
#include "Util.h"
#include "gtest/gtest.h"

class EventHandlerTest : public ::testing::Test {
protected:
  EventHandler::EventHandler *eventHandler;
  Handler::Handler *t;

  void SetUp() override {
    eventHandler =
        new (MemoryManagement::MemoryManagement::allocate<
             EventHandler::EventHandler>(sizeof(EventHandler::EventHandler)))
            EventHandler::EventHandler();
    t = new (MemoryManagement::MemoryManagement::allocate<Handler::Handler>(
        sizeof(Handler::Handler))) Handler::Handler(1);
  }

  void TearDown() override {
    eventHandler = MemoryManagement::MemoryManagement::deallocate<
        EventHandler::EventHandler>(eventHandler);
  }
};

TEST_F(EventHandlerTest, CheckHandlerAddOne) {
  eventHandler->addHandler(t);
  ASSERT_TRUE(eventHandler->getHandlers() != nullptr);
}

TEST_F(EventHandlerTest, CheckHandlerAddMany) {
  Handler::Handler *t1 =
      new (MemoryManagement::MemoryManagement::allocate<Handler::Handler>(
          sizeof(Handler::Handler))) Handler::Handler(2);
  eventHandler->addHandler(t);
  eventHandler->addHandler(t1);
  ASSERT_TRUE(eventHandler->getHandlers() != nullptr);
}

TEST_F(EventHandlerTest, CheckHandleForMany) {
  Handler::Handler *t1 =
      new (MemoryManagement::MemoryManagement::allocate<Handler::Handler>(
          sizeof(Handler::Handler))) Handler::Handler(2);
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