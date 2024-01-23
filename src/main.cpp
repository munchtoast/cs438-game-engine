#include "window.h"
#include <iostream>

int add(int a, int b) { return a + b; }

int main() {
  // Sample usage of the add function
  int result = add(3, 4);
  std::cout << "Result: " << result << std::endl;

  drawWindow();
  return 0;
}