#include "../../src/MemoryManagement.h"
#include "../../src/Util.h"
#include "mimalloc.h"
#include "gtest/gtest.h"

class MemoryManagementTest : public ::testing::Test {
protected:
  int *ptr = static_cast<int *>(
      MemoryManagement::MemoryManagement::allocate<int>(sizeof(int)));
};

TEST_F(MemoryManagementTest, CheckIfMemAllocSuccess) {
  ASSERT_TRUE(!Util::Util::checkIfNullPtr(ptr));
  MemoryManagement::MemoryManagement::deallocate<int>(ptr);
}

TEST_F(MemoryManagementTest, checkIfMemFreeSuccess) {
  ptr = static_cast<int *>(
      MemoryManagement::MemoryManagement::deallocate<int>(ptr));
  ASSERT_TRUE(Util::Util::checkIfNullPtr(ptr));
}

TEST_F(MemoryManagementTest, failDoubleFree) {
  ptr = static_cast<int *>(
      MemoryManagement::MemoryManagement::deallocate<int>(ptr));
  ASSERT_THROW(MemoryManagement::MemoryManagement::deallocate<int>(ptr),
               std::runtime_error);
}
