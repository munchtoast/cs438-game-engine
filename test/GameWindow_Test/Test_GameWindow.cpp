#include "../../src/GameWindow.h"
#include "gtest/gtest.h"

class WindowTest : public ::testing::Test {
protected:
  GameWindow::GameWindow gameWindow{
      "Game Engine", 640, 480, SDL_WINDOW_RESIZABLE, SDL_RENDERER_PRESENTVSYNC};
};

TEST_F(WindowTest, CheckGameWindowExists) {
  ASSERT_TRUE(gameWindow.getWindow() != nullptr);
}

TEST_F(WindowTest, CheckGameRendererExists) {
  ASSERT_TRUE(gameWindow.getRenderer() != nullptr);
}
