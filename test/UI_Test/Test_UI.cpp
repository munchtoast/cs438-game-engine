#include "../../src/UI.h"
#include "../../src/Util.h"
#include "gtest/gtest.h"

class UITest : public ::testing::Test {
protected:
  UI::UI camera{100, 100, 100, 100};
};

TEST_F(UITest, CheckProperMove) {
  camera.move(10, 10);
  camera.update();
  ASSERT_TRUE(camera.getRect()->x == 110);
  ASSERT_TRUE(camera.getRect()->y == 110);
}
