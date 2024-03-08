#include "Animation.h"
#include "GameObject.h"
#include "BoxRigidBody.h"
#include "MemoryManagement.h"
#include "Util.h"
#include "gtest/gtest.h"

class BoxRigidBodyTest : public ::testing::Test {
protected:
  GameObject::GameObject *gameObject;
  void SetUp() override {
    gameObject = new (
        MemoryManagement::MemoryManagement::allocate<GameObject::GameObject>(
            sizeof(GameObject::GameObject)))
        GameObject::GameObject(100, 100, 100, 100, 0);
  }

  void TearDown() override {
    gameObject =
        MemoryManagement::MemoryManagement::deallocate<GameObject::GameObject>(
            gameObject);
  }
};

TEST_F(BoxRigidBodyTest, BodyNullOnInitialization) {
  ASSERT_TRUE(gameObject->getBodyProperties() == nullptr);
}

TEST_F(BoxRigidBodyTest, CheckBodySetValues) {
  BoxRigidBody::BoxRigidBody *box = new(
      MemoryManagement::MemoryManagement::allocate<BoxRigidBody::BoxRigidBody>(
          sizeof(BoxRigidBody::BoxRigidBody)))
      BoxRigidBody::BoxRigidBody(100, 150, 200, 250, 30);
  gameObject->setBodyProperties(box);
  gameObject->getBodyProperties()->setVX(50);
  gameObject->getBodyProperties()->setVY(75);

  ASSERT_TRUE(gameObject->getBodyProperties()->getX() == 100);
  ASSERT_TRUE(gameObject->getBodyProperties()->getY() == 150);
  ASSERT_TRUE(gameObject->getBodyProperties()->getW() == 200);
  ASSERT_TRUE(gameObject->getBodyProperties()->getH() == 250);
  ASSERT_TRUE(gameObject->getBodyProperties()->getA() == 30);
  ASSERT_TRUE(gameObject->getBodyProperties()->getVX() == 50);
  ASSERT_TRUE(gameObject->getBodyProperties()->getVY() == 75);
}
