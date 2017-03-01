#include <iostream>
#include <string>
#include <map>
#include <random>
#include <cassert>
#include "Map.hpp"

#define UPPER_LIMIT 10000
#define LOWER_LIMIT -10000

#define TEST_2_COUNT 10000

std::random_device rand_dev_;
std::mt19937_64 gen_(rand_dev_());
std::uniform_int_distribution<int> dist_(LOWER_LIMIT, UPPER_LIMIT);

template <typename Key_T, typename Mapped_T>
void assert_maps(const cs540::Map<Key_T, Mapped_T> &my_map, const std::map<Key_T, Mapped_T> &their_map) {
  assert(my_map.size() == their_map.size());
  auto my_it = my_map.begin();
  auto their_it = their_map.begin();
  while (my_it != my_map.end() && their_it != their_map.end()) {
	assert(my_it->first == their_it->first);
	assert(my_it->second == their_it->second);
	++ my_it;
	++ their_it;
  }
  assert(my_it == my_map.end() && their_it == their_map.end());
}

void test_1() {
  cs540::Map<int, int> my_map;
  std::map<int, int> their_map;
  my_map.insert(std::make_pair(1, 1));
  their_map.insert(std::make_pair(1, 1));
  assert_maps(my_map, their_map);
}

void test_2() {
  cs540::Map<int, int> my_map;
  std::map<int, int> their_map;
  for (int i = 0; i < TEST_2_COUNT; ++ i) {
	std::pair<int, int> to_insert(dist_(gen_), dist_(gen_));
	// std::cout << to_insert.first << " " << to_insert.second << std::endl;
	my_map.insert(to_insert);
	their_map.insert(to_insert);	
  }
  assert_maps(my_map, their_map);
}

int main() {
  test_2();
}

