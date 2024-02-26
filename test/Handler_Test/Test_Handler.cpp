#include "Animation.h"
#include "GameObject.h"
#include "Handler.h"
#include "MemoryManagement.h"
#include "Util.h"
#include "gtest/gtest.h"

class HandlerTest : public ::testing::Test {
protected:
  Handler::Handler<GameObject::GameObject> *h;

  void SetUp() override {
    h = new (MemoryManagement::MemoryManagement::allocate<
             Handler::Handler<GameObject::GameObject>>(
        sizeof(Handler::Handler<GameObject::GameObject>)))
        Handler::Handler<GameObject::GameObject>(1);
  }

  void TearDown() override {
    h = static_cast<Handler::Handler<GameObject::GameObject> *>(
        MemoryManagement::MemoryManagement::deallocate<
            Handler::Handler<GameObject::GameObject>>(h));
  }
};

TEST_F(HandlerTest, CheckActionCode) { ASSERT_TRUE(h->getActionCode() == 1); }

TEST_F(HandlerTest, CheckThrowHandle) {
  h->setEventCallBack(
      new (MemoryManagement::MemoryManagement::allocate<Handler::EventCallBack>(
          sizeof(Handler::EventCallBack)))
          Handler::EventCallBack([]() { throw std::runtime_error("FAIL"); }));
  ASSERT_THROW(h->callBackAndNotifyObjects(), std::runtime_error);
}
