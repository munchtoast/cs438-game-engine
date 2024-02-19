#include "GameObject.h"
#include "Util.h"
#include "gtest/gtest.h"

class GameObjectTest : public ::testing::Test {
protected:
  GameObject::GameObject gameObject{100, 100, 100, 100};
};

TEST_F(GameObjectTest, CheckRectStructExists) {
  ASSERT_TRUE(gameObject.getRect() != nullptr);
}

TEST_F(GameObjectTest, CheckRectUpdateStruct) {
  gameObject.setX(200);
  gameObject.setY(300);
  gameObject.setW(150);
  gameObject.setH(50);

  gameObject.update();
  ASSERT_TRUE(gameObject.getRect()->x == 200);
  ASSERT_TRUE(gameObject.getRect()->y == 300);
  ASSERT_TRUE(gameObject.getRect()->w == 150);
  ASSERT_TRUE(gameObject.getRect()->h == 50);
}
