#include "../../src/Camera.h"
#include "../../src/Util.h"
#include "gtest/gtest.h"

class CameraTest : public ::testing::Test {
protected:
  Camera::Camera camera{100, 100, 100, 100};
};

TEST_F(CameraTest, CheckProperMove) {
  camera.move(10, 10);
  camera.update();
  ASSERT_TRUE(camera.getRect()->x == 110);
  ASSERT_TRUE(camera.getRect()->y == 110);
}
