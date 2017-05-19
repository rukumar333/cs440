#include <iostream>
#include <string>
#include "Array.hpp"

int main() {
  cs540::Array<int, 2, 3> array;
  array[0][0] = 10;
  array[0][1] = 6;
  std::cout << array[0][1] << std::endl;
  auto it = array.fmbegin();
  std::cout << *it << std::endl;
  ++ it;
  std::cout << *it << std::endl;
  cs540::Array<long, 2, 3> array_s(array);
}
