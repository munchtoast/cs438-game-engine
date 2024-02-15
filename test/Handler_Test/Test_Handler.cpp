#include "Handler.h"
#include "MemoryManagement.h"
#include "Util.h"
#include "gtest/gtest.h"

class HandlerTest : public ::testing::Test {
protected:
  Handler::Handler *h;

  void SetUp() override {
    h = new (MemoryManagement::MemoryManagement::allocate<Handler::Handler>(
        sizeof(Handler::Handler))) Handler::Handler(1);
  }

  void TearDown() override {
    h = static_cast<Handler::Handler *>(
        MemoryManagement::MemoryManagement::deallocate<Handler::Handler>(h));
  }
};

TEST_F(HandlerTest, CheckActionCode) { ASSERT_TRUE(h->getActionCode() == 1); }

TEST_F(HandlerTest, CheckThrowHandle) {
  h->setEventCallBack(
      new (MemoryManagement::MemoryManagement::allocate<Handler::EventCallBack>(
          sizeof(Handler::EventCallBack)))
          Handler::EventCallBack([]() { throw std::runtime_error("FAIL"); }));
  Handler::EventCallBack callback = *h->getEventCallBack();
  ASSERT_THROW(callback(), std::runtime_error);
}
