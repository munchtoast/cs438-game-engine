#include "Animation.h"
#include "GameObject.h"
#include "MemoryManagement.h"
#include "Util.h"
#include "gtest/gtest.h"

class GameObjectTest : public ::testing::Test {
protected:
  GameObject::GameObject *gameObject;
  void SetUp() override {
    gameObject = new (
        MemoryManagement::MemoryManagement::allocate<GameObject::GameObject>(
            sizeof(GameObject::GameObject)))
        GameObject::GameObject(100, 100, 100, 100);
  }

  void TearDown() override {
    gameObject =
        MemoryManagement::MemoryManagement::deallocate<GameObject::GameObject>(
            gameObject);
  }
};

TEST_F(GameObjectTest, CheckRectStructExists) {
  ASSERT_TRUE(gameObject->getRectProperties() != nullptr);
}

TEST_F(GameObjectTest, CheckRectUpdateStruct) {
  gameObject->setX(200);
  gameObject->setY(300);
  gameObject->setW(150);
  gameObject->setH(50);

  ASSERT_TRUE(gameObject->getRectProperties()->position.x == 200);
  ASSERT_TRUE(gameObject->getRectProperties()->position.y == 300);
  ASSERT_TRUE(gameObject->getRectProperties()->size.width == 150);
  ASSERT_TRUE(gameObject->getRectProperties()->size.height == 50);
}
