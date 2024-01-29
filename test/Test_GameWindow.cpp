#include "../src/GameWindow.h"
#include "gtest/gtest.h"

class WindowTest : public ::testing::Test {
protected:
  GameWindow gameWindow;
};

TEST_F(WindowTest, CheckGameWindowExists) {
  ASSERT_TRUE(gameWindow.getWindow() != nullptr);
}

TEST_F(WindowTest, CheckGameRendererExists) {
  ASSERT_TRUE(gameWindow.getRenderer() != nullptr);
}
