#include <iostream>
#include <string>
#include "Array.hpp"

int main() {
  // cs540::Array<int, 2> array;
  // array[0][0] = 10;
  // array[0][1] = 6;
  // std::cout << array[0][1] << std::endl;
  // auto it = array.fmbegin();
  // std::cout << *it << std::endl;
  // ++ it;
  // std::cout << *it << std::endl;
  // *it = 5;
  // std::cout << *it << std::endl;
  // std::cout << array[0][1] << std::endl;
  // cs540::Array<long, 2, 3> array_s(array);
  cs540::Array<int, 2> array;
  array[0] = 10;
  array[1] = 25;
  auto it = array.fmbegin();
  while (it != array.fmend()) {
	std::cout << *it << std::endl;
	++ it;
  }
}
