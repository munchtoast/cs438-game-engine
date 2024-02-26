#include "Animation.h"
#include "UI.h"
#include "Util.h"
#include "gtest/gtest.h"

class UITest : public ::testing::Test {
protected:
  UI::UI *ui;
  void SetUp() override {
    ui = new (MemoryManagement::MemoryManagement::allocate<UI::UI>(
        sizeof(UI::UI))) UI::UI(100, 100, 100, 100);
  }

  void TearDown() override {
    ui = MemoryManagement::MemoryManagement::deallocate<UI::UI>(ui);
  }
};

TEST_F(UITest, CheckProperMove) {
  ui->move(10, 10);
  ASSERT_TRUE(ui->getRectProperties()->position.x == 110);
  ASSERT_TRUE(ui->getRectProperties()->position.y == 110);
}
