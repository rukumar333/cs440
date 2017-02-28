#include <iostream>
#include <string>
#include <map>
#include "Map.hpp"

void my_map_test() {
  cs540::Map<int, int> map;
  map.insert(std::make_pair(0, 1));
  map.insert(std::make_pair(-1, 1));
  map.insert(std::make_pair(2, 1));
  map.insert(std::make_pair(10, 1));
  map.print();
  std::cout << "Erasing key: 2\n" << std::endl;
  map.erase(2);
  map.print();
}

int main() {
  // cs540::Map<int, int> map;
  // std::map<int, int> std_map;
  // map.insert(std::make_pair(0, 1));
  // std_map.insert(std::make_pair(0, 1));
  // std::cout << std_map.begin()->first << ", " << std_map.begin()->second << std::endl;
  // (*std_map.begin()).second = 10;
  // std::cout << std_map.begin()->first << ", " << std_map.begin()->second << std::endl;
  // std::cout << map.begin()->first << ", " << map.begin()->second << std::endl;
  // map.begin()->second = 10;
  // std::cout << map.begin()->first << ", " << map.begin()->second << std::endl;
  // map.insert(std::make_pair(-1, 1));
  // map.insert(std::make_pair(2, 1));
  // map.insert(std::make_pair(10, 1));
  // std::cout << map.insert(std::make_pair(10, 1)).second << std::endl;
  // map.print();
  // std::cout << "Erasing\n" << std::endl;
  // map.erase(2);
  // map.print();
  my_map_test();
}


