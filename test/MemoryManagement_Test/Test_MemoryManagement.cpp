#include "../../src/MemoryManagement.h"
#include "../../src/Util.h"
#include "mimalloc.h"
#include "gtest/gtest.h"

class MemoryManagementTest : public ::testing::Test {
protected:
  int *ptr = (int *)MemoryManagement::MemoryManagement::allocate(sizeof(int));
};

TEST_F(MemoryManagementTest, CheckIfMemAllocSuccess) {
  ASSERT_TRUE(!Util::Util::checkIfNullPtr(ptr));
  MemoryManagement::MemoryManagement::deallocate(ptr);
}

TEST_F(MemoryManagementTest, checkIfMemFreeSuccess) {
  ptr = (int *)MemoryManagement::MemoryManagement::deallocate(ptr);
  ASSERT_TRUE(Util::Util::checkIfNullPtr(ptr));
}

TEST_F(MemoryManagementTest, failDoubleFree) {
  ptr = (int *)MemoryManagement::MemoryManagement::deallocate(ptr);
  ASSERT_THROW(MemoryManagement::MemoryManagement::deallocate(ptr),
               std::runtime_error);
}
