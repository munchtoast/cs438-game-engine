#include "Tile.h"
#include "gtest/gtest.h"

class TileTest : public ::testing::Test {
protected:
  Tile::Tile tile{100, 100, 100, 100};
};

TEST_F(TileTest, CheckColorStructExists) {
  ASSERT_TRUE(tile.getColor() != nullptr);
}

TEST_F(TileTest, CheckSetColorStruct) {
  tile.setColorChoice(255, 200, 100, 240);
  ASSERT_TRUE(tile.getColor()->r == 255);
  ASSERT_TRUE(tile.getColor()->g == 200);
  ASSERT_TRUE(tile.getColor()->b == 100);
  ASSERT_TRUE(tile.getColor()->a == 240);
}

TEST_F(TileTest, CheckRectStructExists) {
  ASSERT_TRUE(tile.getRect() != nullptr);
}
