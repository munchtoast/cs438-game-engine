#include "Animation.h"
#include "Map.h"
#include "MemoryManagement.h"
#include "Util.h"
#include "gtest/gtest.h"

class AnimationTest : public ::testing::Test {
protected:
  Animation::Animation *a;

  void SetUp() override {
    a = new (MemoryManagement::MemoryManagement::allocate<Animation::Animation>(
        sizeof(Animation::Animation))) Animation::Animation();
  }

  void TearDown() override {
    a = static_cast<Animation::Animation *>(
        MemoryManagement::MemoryManagement::deallocate<Animation::Animation>(
            a));
  }
};

TEST_F(AnimationTest, CheckAddOneCelMap) {
  a->addCels(new (
      MemoryManagement::MemoryManagement::allocate<Map::Map<Animation::Cel>>(
          sizeof(Map::Map<Animation::Cel>))) Map::Map<Animation::Cel>());

  ASSERT_TRUE(a->getCelsToRender() != nullptr);
}

TEST_F(AnimationTest, CheckAddManyCelMap) {
  a->addCels(new (
      MemoryManagement::MemoryManagement::allocate<Map::Map<Animation::Cel>>(
          sizeof(Map::Map<Animation::Cel>))) Map::Map<Animation::Cel>());
  a->addCels(new (
      MemoryManagement::MemoryManagement::allocate<Map::Map<Animation::Cel>>(
          sizeof(Map::Map<Animation::Cel>))) Map::Map<Animation::Cel>());

  ASSERT_TRUE(a->getCelsToRender() != nullptr);
  a->setAnimationState(1);

  ASSERT_TRUE(a->getCelsToRender() != nullptr);
}
