#include "Animation.h"
#include "Map.h"
#include "MemoryManagement.h"
#include "RectStruct.h"
#include "gtest/gtest.h"

class CelTest : public ::testing::Test {
protected:
  Animation::Cel *c;

  void SetUp() override {
    c = new (MemoryManagement::MemoryManagement::allocate<Animation::Cel>(
        sizeof(Animation::Cel))) Animation::Cel();
  }

  void TearDown() override {
    c = static_cast<Animation::Cel *>(
        MemoryManagement::MemoryManagement::deallocate<Animation::Cel>(c));
  }
};

TEST_F(CelTest, CheckSetPixels) {
  c->setPixels(new (
      MemoryManagement::MemoryManagement::allocate<Map::Map<RectStruct::Rect>>(
          sizeof(Map::Map<RectStruct::Rect>))) Map::Map<RectStruct::Rect>());
  ASSERT_TRUE(c->getPixels() != nullptr);
}

TEST_F(CelTest, CheckSetRenderable) {
  c->setRenderable(false);
  ASSERT_TRUE(c->getRenderable() == false);
}
