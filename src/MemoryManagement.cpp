#include "MemoryManagement.h"
#include "Util.h"
#include "mimalloc.h"
#include <cstddef>

namespace MemoryManagement {
/**
 * @brief Allocates memory of certain size and returns the pointer to the memory
 * block
 *
 * @param size - Size of the block to allocate from memory
 */
void *MemoryManagement::allocate(std::size_t size) {
  void *ptr = mi_malloc(size);
  Util::Util::checkIfMemAllocSuccess(ptr);
  return ptr;
}
/**
 * @brief Deallocates memory given a pointer and returns a nullptr to assign
 * back
 *
 * @param ptr - Address of the memory block to be freed
 */
void *MemoryManagement::deallocate(void *ptr) {
  if (Util::Util::checkIfNullPtr(ptr))
    throw std::runtime_error("Freeing unsafe memory!");
  mi_free(ptr);
  ptr = nullptr;
  Util::Util::checkIfMemFreeSuccess(ptr);

  return ptr;
}
} // namespace MemoryManagement
