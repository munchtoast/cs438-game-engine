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
 * - 1.1: Convert source code to templates (dexter@nekocake.cafe) (2024-02-07)
 */

#ifndef MEMORY_MANAGEMENT_H
#define MEMORY_MANAGEMENT_H

#include "Util.h"
#include "mimalloc.h"
#include <cstddef>

namespace MemoryManagement {
class MemoryManagement {
public:
  /**
   * @brief Allocates memory of certain size and returns the pointer to the
   * memory block
   *
   * @param size - Size of the block to allocate from memory
   */
  template <typename T> static T *allocate(std::size_t size) {
    T *ptr = static_cast<T *>(mi_malloc(size));
    Util::Util::checkIfMemAllocSuccess(ptr);
    return ptr;
  }

  /**
   * @brief Deallocates memory given a pointer and returns a nullptr to assign
   * back
   *
   * @param ptr - Address of the memory block to be freed
   * @param cc - Complete Cleanup, calls destructor
   */
  template <typename T> static T *deallocate(T *ptr, bool cc = true) {
    if (Util::Util::checkIfNullPtr(ptr))
      throw std::runtime_error("Freeing unsafe memory!");

    // Call destructors for each object in the memory block
    if (cc)
      destructObjects<T>(ptr);

    mi_free(ptr);
    return nullptr;
  }

  /**
   * @brief Reallocates memory given a pointer and size to increase by. Returns
   * new pointer
   *
   * @note The old pointer is freed
   *
   * @param ptr - Address of the old memory block
   * @param size - Amount to increase current memory by
   */
  template <typename T> static T *reallocate(T *ptr, std::size_t size) {
    if (Util::Util::checkIfNullPtr(ptr))
      throw std::runtime_error("Reallocating unsafe memory!");

    T *newPtr = static_cast<T *>(mi_realloc(ptr, size));
    Util::Util::checkIfMemAllocSuccess(newPtr);

    return newPtr;
  }

  template <typename T> static void destructObjects(T *ptr) {
    T *object = reinterpret_cast<T *>(ptr);
    if (object != nullptr) {
      object->~T();
    }
  }

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

} // namespace MemoryManagement

#endif
