#include <iostream>
#include <string>
#include "Array.hpp"

int main() {
  cs540::Array<int, 2, 3> array;
  array[0][1] = 10;
  std::cout << array[0][1] << std::endl;
  auto it = array.fmbegin();
}
