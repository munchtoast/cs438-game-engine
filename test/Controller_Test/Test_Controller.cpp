#include "Controller.h"
#include "EventHandler.h"
#include "Util.h"
#include "gtest/gtest.h"

class ControllerTest : public ::testing::Test {
protected:
  Controller::Controller *c

      void
      SetUp() override {
    c = new (
        MemoryManagement::MemoryManagement::allocate<Controller::Controller>(
            sizeof(Controller))) Controller::Controller();
  }

  void TearDown() override {
    c = static_cast<Controller::Controller *>(
        MemoryManagement::MemoryManagement::deallocate < Controller
        : Controller > (c));
  }
};
