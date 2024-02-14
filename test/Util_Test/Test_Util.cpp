#include "Util.h"
#include "gtest/gtest.h"
#include <mimalloc.h>

class UtilTest : public ::testing::Test {
protected:
  int *ptr;
  void SetUp() override { ptr = (int *)mi_malloc(sizeof(int)); }
  void TearDown() override { mi_free(ptr); }
};

TEST_F(UtilTest, FailMemAllocNull) {
  ASSERT_THROW(Util::checkIfMemAllocSuccess(NULL), std::bad_alloc);
}

TEST_F(UtilTest, FailMemFreeSucc) {
  ASSERT_THROW(Util::checkIfMemFreeSuccess(ptr), std::runtime_error);
}
