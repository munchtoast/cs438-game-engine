#include "../src/main.cpp" // Include the source file for testing
#include "gtest/gtest.h"

TEST(ExampleTest, Addition) {
  // Test the add function
  EXPECT_EQ(add(2, 3), 5);
  EXPECT_EQ(add(-1, 1), 0);
  EXPECT_EQ(add(0, 0), 0);
}
