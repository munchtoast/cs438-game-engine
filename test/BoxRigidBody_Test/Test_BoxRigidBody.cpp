#include "Animation.h"
#include "BoxRigidBody.h"
#include "GameObject.h"
#include "MemoryManagement.h"
#include "Util.h"
#include "gtest/gtest.h"

class BoxRigidBodyTest : public ::testing::Test {
protected:
  BoxRigidBody::BoxRigidBody *gameObject;
  void SetUp() override {
    gameObject =
        new (MemoryManagement::MemoryManagement::allocate<
             BoxRigidBody::BoxRigidBody>(sizeof(BoxRigidBody::BoxRigidBody)))
            BoxRigidBody::BoxRigidBody(100, 100, 100, 100, 0);
  }

  void TearDown() override {
    gameObject = MemoryManagement::MemoryManagement::deallocate<
        BoxRigidBody::BoxRigidBody>(gameObject);
  }
};

TEST_F(BoxRigidBodyTest, CheckRectStructExists) {
  ASSERT_TRUE(gameObject->getRectProperties() != nullptr);
}

TEST_F(BoxRigidBodyTest, CheckBodySetValues) {
  gameObject->setVX(50);
  gameObject->setVY(75);

  ASSERT_TRUE(gameObject->getVX() == 50);
  ASSERT_TRUE(gameObject->getVY() == 75);
}
