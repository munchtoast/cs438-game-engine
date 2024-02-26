#include "Animation.h"
#include "Controller.h"
#include "EventHandler.h"
#include "GameObject.h"
#include "Handler.h"
#include "MemoryManagement.h"
#include "Util.h"
#include "gtest/gtest.h"

class ControllerTest : public ::testing::Test {
protected:
  Controller::Controller *c;

  void SetUp() override {
    c = new (
        MemoryManagement::MemoryManagement::allocate<Controller::Controller>(
            sizeof(Controller::Controller))) Controller::Controller();
  }

  void TearDown() override {
    c = static_cast<Controller::Controller *>(
        MemoryManagement::MemoryManagement::deallocate<Controller::Controller>(
            c));
  }
};

TEST_F(ControllerTest, CheckAddOneHandler) {
  Handler::Handler<GameObject::GameObject> *h =
      new (MemoryManagement::MemoryManagement::allocate<
           Handler::Handler<GameObject::GameObject>>(
          sizeof(Handler::Handler<GameObject::GameObject>)))
          Handler::Handler<GameObject::GameObject>(1);
  h->setEventCallBack(
      new (MemoryManagement::MemoryManagement::allocate<Handler::EventCallBack>(
          sizeof(Handler::EventCallBack)))
          Handler::EventCallBack([]() { throw std::runtime_error("FAIL"); }));

  c->getEventHandler()->addHandler(h);
  ASSERT_THROW(c->getEventHandler()->handleEvent(1), std::runtime_error);
}

TEST_F(ControllerTest, CheckAddManyHandler) {
  Handler::Handler<GameObject::GameObject> *h1 =
      new (MemoryManagement::MemoryManagement::allocate<
           Handler::Handler<GameObject::GameObject>>(
          sizeof(Handler::Handler<GameObject::GameObject>)))
          Handler::Handler<GameObject::GameObject>(1);
  h1->setEventCallBack(
      new (MemoryManagement::MemoryManagement::allocate<Handler::EventCallBack>(
          sizeof(Handler::EventCallBack)))
          Handler::EventCallBack([]() { throw std::runtime_error("FAIL"); }));

  Handler::Handler<GameObject::GameObject> *h2 =
      new (MemoryManagement::MemoryManagement::allocate<
           Handler::Handler<GameObject::GameObject>>(
          sizeof(Handler::Handler<GameObject::GameObject>)))
          Handler::Handler<GameObject::GameObject>(2);
  h2->setEventCallBack(
      new (MemoryManagement::MemoryManagement::allocate<Handler::EventCallBack>(
          sizeof(Handler::EventCallBack)))
          Handler::EventCallBack([]() { throw std::runtime_error("FAIL"); }));

  c->getEventHandler()->addHandler(h1);
  c->getEventHandler()->addHandler(h2);

  ASSERT_THROW(c->getEventHandler()->handleEvent(1), std::runtime_error);
  ASSERT_THROW(c->getEventHandler()->handleEvent(2), std::runtime_error);
}
