#include "Util.h"
#include <new>
#include <spdlog/spdlog.h>

namespace Util {
/**
 * @brief Checks if Memory Allocation is successful. If the Memory Allocation is
 * not successful then the program should throw an error. This prevents the
 * program from accessing unsafe memory addresses.
 *
 * @param ptr - Pointer to address
 */
void Util::checkIfMemAllocSuccess(void *ptr) {
  if (Util::checkIfNullPtr(ptr)) {
    spdlog::error("Unable to allocate sufficient resources");
    throw std::bad_alloc();
  }
}

/**
 * @brief Checks if Memory Deallocation is successful. If the Memory
 * Deallocation is not successful then the program should throw an error. This
 * prevents memory leaks that otherwise would continue.
 *
 * @note This utility function may not even be worth keeping but would be
 * helpful at a DEBUG level to check for mem leaks.
 * @param ptr - Pointer to address
 */
void Util::checkIfMemFreeSuccess(void *ptr) {
  if (!Util::checkIfNullPtr(ptr)) {
    spdlog::error("Unable to free allocated resources");
    throw std::runtime_error("Memory deallocation failed.");
  }
}

void Util::checkIfMemReallocSuccess(void *ptr, void *nptr) {
  if (!Util::checkIfNullPtr(ptr) && !Util::checkIfNullPtr(nptr)) {
    spdlog::error("Unable to reallocate resources");
    throw std::runtime_error("Memory reallocation failed.");
  }
}

bool Util::checkIfNullPtr(void *ptr) { return (ptr == nullptr); }

void checkIfMemAllocSuccess(void *ptr) { Util::checkIfMemAllocSuccess(ptr); }

void checkIfMemFreeSuccess(void *ptr) { Util::checkIfMemFreeSuccess(ptr); }

void checkIfMemReallocSuccess(void *ptr, void *nptr) {
  Util::checkIfMemReallocSuccess(ptr, nptr);
}
} // namespace Util
