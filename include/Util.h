/*
 * @file Util.h
 * @brief Defines the Util namespace, providing utility functions for various
 * purposes.
 *
 * The Util namespace contains utility functions that are commonly used
 * throughout the game engine. These functions cover areas such as memory
 * management checks and other general-purpose utilities.
 *
 * @remark This namespace is designed to offer essential utility functions for
 * various aspects of the game engine.
 *
 * @version
 * - 1.0: Initial implementation (dexter@nekocake.cafe) (2024-02-01)
 * - 1.1: Move checkIfNullPtr() to public access (dexter@nekocake.cafe)
 * (2024-02-02)
 */

#ifndef UTIL_H
#define UTIL_H

namespace Util {
class Util {
public:
  static void checkIfMemAllocSuccess(void *ptr);
  static void checkIfMemFreeSuccess(void *ptr);
  static void checkIfMemReallocSuccess(void *ptr, void *nptr);
  static bool checkIfNullPtr(void *ptr);

private:
  Util();
  ~Util();
};

extern void checkIfMemAllocSuccess(void *ptr);
extern void checkIfMemFreeSuccess(void *ptr);
extern void checkIfMemReallocSuccess(void *ptr, void *nptr);
} // namespace Util

#endif
