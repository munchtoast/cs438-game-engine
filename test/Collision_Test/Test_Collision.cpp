#include "Animation.h"
#include "Collision.h"
#include "GameObject.h"
#include "MemoryManagement.h"
#include "Util.h"
#include "gtest/gtest.h"

class CollisionTest : public ::testing::Test {
protected:
  GameObject::GameObject *gameObject;
  GameObject::GameObject *gameObject2;
  void SetUp() override {
    gameObject = new (
        MemoryManagement::MemoryManagement::allocate<GameObject::GameObject>(
            sizeof(GameObject::GameObject)))
        GameObject::GameObject(100, 100, 100, 100);
    gameObject2 = new (
        MemoryManagement::MemoryManagement::allocate<GameObject::GameObject>(
            sizeof(GameObject::GameObject)))
        GameObject::GameObject(100, 100, 100, 100);
  }

  void TearDown() override {
    gameObject =
        MemoryManagement::MemoryManagement::deallocate<GameObject::GameObject>(
            gameObject);
    gameObject2 =
        MemoryManagement::MemoryManagement::deallocate<GameObject::GameObject>(
            gameObject2);
  }
};

TEST_F(CollisionTest, CheckRectStructExists) {
  ASSERT_TRUE(gameObject->getRectProperties() != nullptr);
  ASSERT_TRUE(gameObject2->getRectProperties() != nullptr);
}

TEST_F(CollisionTest, DetectCollision) {
  ASSERT_TRUE(Collision::Collision::detectCollision(gameObject, gameObject2));
}

TEST_F(CollisionTest, HandleCollision) {
  Collision::Collision::handleCollision(gameObject, gameObject2);
  ASSERT_FALSE(Collision::Collision::detectCollision(gameObject, gameObject2));
}
