#include "GameObject.h"
#include "Map.h"
#include "MemoryManagement.h"
#include "Util.h"
#include "mimalloc.h"
#include "gtest/gtest.h"

class MapTest : public ::testing::Test {
protected:
  Map::Map<GameObject::GameObject> *gameObjectMap =
      new (MemoryManagement::MemoryManagement::allocate<
           Map::Map<GameObject::GameObject> *>(sizeof(GameObject::GameObject)))
          Map::Map<GameObject::GameObject>();
};

TEST_F(MapTest, CheckIfMemAllocSuccess) {
  ASSERT_TRUE(!Util::Util::checkIfNullPtr(gameObjectMap));
  MemoryManagement::MemoryManagement::deallocate<
      Map::Map<GameObject::GameObject>>(gameObjectMap);
}

TEST_F(MapTest, checkIfMemFreeSuccess) {
  gameObjectMap = static_cast<Map::Map<GameObject::GameObject> *>(
      MemoryManagement::MemoryManagement::deallocate<
          Map::Map<GameObject::GameObject>>(gameObjectMap));
  ASSERT_TRUE(Util::Util::checkIfNullPtr(gameObjectMap));
}

TEST_F(MapTest, failDoubleFree) {
  gameObjectMap = static_cast<Map::Map<GameObject::GameObject> *>(
      MemoryManagement::MemoryManagement::deallocate<
          Map::Map<GameObject::GameObject>>(gameObjectMap));
  ASSERT_THROW(MemoryManagement::MemoryManagement::deallocate<
                   Map::Map<GameObject::GameObject>>(gameObjectMap),
               std::runtime_error);
}
