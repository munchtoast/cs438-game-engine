#include "Tile.h"
#include "gtest/gtest.h"

class TileTest : public ::testing::Test {
protected:
  Tile::Tile *tile;
  void SetUp() override {
    tile = new (MemoryManagement::MemoryManagement::allocate<Tile::Tile>(
        sizeof(Tile::Tile))) Tile::Tile(100, 100, 100, 100);
  }

  void TearDown() override {
    tile = MemoryManagement::MemoryManagement::deallocate<Tile::Tile>(tile);
  }
};

TEST_F(TileTest, CheckColorStructExists) {
  ASSERT_TRUE(tile->getColor() != nullptr);
}

TEST_F(TileTest, CheckSetColorStruct) {
  tile->setColorChoice(255, 200, 100, 240);
  ASSERT_TRUE(tile->getColor()->r == 255);
  ASSERT_TRUE(tile->getColor()->g == 200);
  ASSERT_TRUE(tile->getColor()->b == 100);
  ASSERT_TRUE(tile->getColor()->a == 240);
}

TEST_F(TileTest, CheckRectStructExists) {
  ASSERT_TRUE(tile->getRectProperties() != nullptr);
}
