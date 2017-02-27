#include <iostream>
#include <string>
#include "Map.hpp"

int main() {
  cs540::Map<int, int> map;  
  map.insert(std::make_pair(0, 1));
  map.insert(std::make_pair(-1, 1));
  map.insert(std::make_pair(2, 1));
  map.insert(std::make_pair(10, 1));
  std::cout << map.insert(std::make_pair(10, 1)) << std::endl;
  map.print();
}
