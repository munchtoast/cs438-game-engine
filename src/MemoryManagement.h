/*
 * @file MemoryManagement.h
 * @brief Defines the core components for handling dynamic memory. Provides safe
 * methods to ensure that memory is allocated or deallocated.
 *
 * The MemoryManagement class features static methods which can be called
 * externally for other files. This can be done by importing this header file.
 * MemoryManagement also features a DeepCopy template such that it clones the
 * exact object.
 *
 * @note deallocate returns pointer to the result of freed
 *
 * @remark This class serves as a foundational component for managing dynamic
 * memory
 *
 * @version
 * - 1.0: Initial implementation (dexter@nekocake.cafe) (2024-02-02)
 */

#ifndef MEMORY_MANAGEMENT_H
#define MEMORY_MANAGEMENT_H

#include <cstddef>

namespace MemoryManagement {
class MemoryManagement {
public:
  static void *allocate(std::size_t size);
  static void *deallocate(void *ptr);

  /**
   * @brief DeepCopy allows for an object supplied via constructor to be copied
   * in another space of memory
   *
   * @note DeepCopy does NOT feature a destructor and is an intended function
   */
  template <typename T> class DeepCopy {
  public:
    DeepCopy(const T &target) : value(target) {}

    DeepCopy &operator=(const DeepCopy &target) {
      if (this != &target) {
        value = target.value;
      }
      return *this;
    }

    T getValue() const { return value; }

  private:
    T value;
  };

private:
  MemoryManagement();
  ~MemoryManagement();
};

extern void *allocate(std::size_t size);
extern void *deallocate(void *ptr);
} // namespace MemoryManagement

#endif
