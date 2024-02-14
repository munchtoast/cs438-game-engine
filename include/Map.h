/*
 * @file Map.h
 * @brief Declaration of the Map class, a fundamental data structure for keeping
 * track of objects within the game state
 *
 * @version
 * - 1.0: Initial implementation (dexter@nekocake.cafe) (2024-02-07)
 * - 1.1: Remove includes that cause circular dependency (dexter@nekocake.cafe)
 * (2024-02-09)
 */

#ifndef TILEMAP_H
#define TILEMAP_H

#include "MemoryManagement.h"
#include "Util.h"
#include <spdlog/spdlog.h>

namespace Map {
template <typename T> class Map {
public:
  Map()
      : mem(MemoryManagement::MemoryManagement::allocate<T *>(sizeof(T))),
        size(0), capacity(1) {}

  ~Map() { cleanup(); }

  void add(T *t) {
    if (getSize() == getCapacity()) {
      setCapacity(getCapacity() == 0 ? 1 : getCapacity() * 2);
      mem = static_cast<T **>(MemoryManagement::MemoryManagement::reallocate(
          mem, getCapacity() * sizeof(T)));
    }

    mem[size++] = t;
  }

  size_t getSize() { return size; }

  size_t getCapacity() { return capacity; }

  void setSize(size_t nsize) { size = nsize; }

  void setCapacity(size_t cap) { capacity = cap; }

  T **getMap() { return mem; }

private:
  T **mem;
  size_t size;
  size_t capacity;

  void cleanup() {
    for (size_t i = 0; i < getSize(); ++i) {
      MemoryManagement::MemoryManagement::deallocate(mem[i]);
    }

    mem =
        static_cast<T **>(MemoryManagement::MemoryManagement::deallocate(mem));
    Util::Util::checkIfMemFreeSuccess(Map::getMap());
  }
};
} // namespace Map

#endif
