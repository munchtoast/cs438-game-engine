#include "Collision.h"
#include "MemoryManagement.h"
#include "Util.h"
#include "gtest/gtest.h"

class CollisionTest : public ::testing::Test {
protected:
  BoxRigidBody::BoxRigidBody *box;
  BoxRigidBody::BoxRigidBody *box2;
  BoxRigidBody::BoxRigidBody *box3;
  void SetUp() override {
    box = new (MemoryManagement::MemoryManagement::allocate<
               BoxRigidBody::BoxRigidBody>(sizeof(BoxRigidBody::BoxRigidBody)))
        BoxRigidBody::BoxRigidBody(100, 100, 100, 100, 0);
    box2 = new (MemoryManagement::MemoryManagement::allocate<
                BoxRigidBody::BoxRigidBody>(sizeof(BoxRigidBody::BoxRigidBody)))
        BoxRigidBody::BoxRigidBody(100, 100, 100, 100, 0);
    box3 = new (MemoryManagement::MemoryManagement::allocate<
                BoxRigidBody::BoxRigidBody>(sizeof(BoxRigidBody::BoxRigidBody)))
        BoxRigidBody::BoxRigidBody(100, 200, 100, 100, 30);
  }

  void TearDown() override {
    box = MemoryManagement::MemoryManagement::deallocate<
        BoxRigidBody::BoxRigidBody>(box);
    box2 = MemoryManagement::MemoryManagement::deallocate<
        BoxRigidBody::BoxRigidBody>(box2);
    box3 = MemoryManagement::MemoryManagement::deallocate<
        BoxRigidBody::BoxRigidBody>(box3);
  }
};

TEST_F(CollisionTest, CheckRectStructExists) {
  ASSERT_TRUE(box->getBoxProperties() != nullptr);
  ASSERT_TRUE(box2->getBoxProperties() != nullptr);
  ASSERT_TRUE(box3->getBoxProperties() != nullptr);
}

TEST_F(CollisionTest, DetectRotatedCollision) {
  ASSERT_TRUE(Collision::Collision::detectCollision(box, box3));
}

TEST_F(CollisionTest, DetectCollision) {
  ASSERT_TRUE(Collision::Collision::detectCollision(box, box2));
}

TEST_F(CollisionTest, HandleCollision) {
  Collision::Collision::handleCollision(box, box2);
  ASSERT_FALSE(Collision::Collision::detectCollision(box, box2));
}
