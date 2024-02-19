/*
 * @file Map.h
 * @brief Declaration of the Map class, a fundamental data structure for keeping
 * track of objects within the game state
 *
 * @version
 * - 1.0: Initial implementation (dexter@nekocake.cafe) (2024-02-07)
 * - 1.1: Remove includes that cause circular dependency (dexter@nekocake.cafe)
 * (2024-02-09)
 * - 1.2: Add Remove() and Complete Clear (CC) (dexter@nekocake.cafe)
 * (2024-02-16)
 *        @note CC is a parameter that exclusively delegates the
 * responsibilities of the deallocation to another source. Use this wisely. More
 * info in MemoryManagement.h
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
        size(0), capacity(1), cc(true) {}

  ~Map() { cleanup(); }

  void add(T *t) {
    if (getSize() == getCapacity()) {
      setCapacity(getCapacity() == 0 ? 1 : getCapacity() * 2);
      mem = static_cast<T **>(MemoryManagement::MemoryManagement::reallocate(
          mem, getCapacity() * sizeof(T)));
    }

    mem[size++] = t;
  }

  void remove(T *t) {
    for (size_t i = 0; i < getSize(); ++i) {
      if (mem[i] == t) {
        if (cc)
          MemoryManagement::MemoryManagement::deallocate(mem[i]);
        mem[i] = mem[getSize() - 1];
        --size;
        return;
      }
    }
  }

  void setCC(bool ncc) { cc = ncc; }

  size_t getSize() { return size; }

  size_t getCapacity() { return capacity; }

  void setSize(size_t nsize) { size = nsize; }

  void setCapacity(size_t cap) { capacity = cap; }

  T **getMap() { return mem; }

private:
  T **mem;
  size_t size;
  size_t capacity;
  bool cc;

  void cleanup() {
    if (cc) {
      for (size_t i = 0; i < getSize(); ++i) {
        MemoryManagement::MemoryManagement::deallocate(mem[i], cc);
      }
    }

    mem = static_cast<T **>(
        MemoryManagement::MemoryManagement::deallocate(mem, cc));
    Util::Util::checkIfMemFreeSuccess(Map::getMap());
  }
};
} // namespace Map

#endif
