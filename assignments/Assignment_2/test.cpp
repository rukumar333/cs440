#include <iostream>
#include <string>
#include <map>
#include <random>
#include <cassert>
#include "Map.hpp"

#define UPPER_LIMIT 1000
#define LOWER_LIMIT 0

#define TEST_2_COUNT 1000

std::random_device rand_dev_;
std::mt19937_64 gen_(rand_dev_());
std::uniform_int_distribution<int> dist_(LOWER_LIMIT, UPPER_LIMIT);

class MyClass {
 private:
  int data;
  MyClass();
  MyClass &operator=(const MyClass &other);
 public:
  MyClass(int a) { data = a; }
  friend bool operator<(const MyClass &a, const MyClass &b) { return a.data < b.data; }
  friend bool operator==(const MyClass &a, const MyClass &b) { return a.data == b.data; }
};

template <typename Key_T, typename Mapped_T>
void assert_maps_const(const cs540::Map<Key_T, Mapped_T> &my_map, const std::map<Key_T, Mapped_T> &their_map);

template <typename Key_T, typename Mapped_T>
void assert_maps(cs540::Map<Key_T, Mapped_T> &my_map, std::map<Key_T, Mapped_T> &their_map) {
  /*
	Size should be the same
   */
  assert(my_map.size() == their_map.size());
  /*
	Iterate through w/ forward pointers
  */
  auto my_it = my_map.begin();
  auto their_it = their_map.begin();
  while (my_it != my_map.end() && their_it != their_map.end()) {
	assert(my_it->first == their_it->first);
	assert(my_it->second == their_it->second);
	assert((*my_it).first == (*their_it).first);
	assert((*my_it).second == (*their_it).second);
	++ my_it;
	++ their_it;
  }
  assert(my_it == my_map.end());
  assert(their_it == their_map.end());
  /*
	Iterate through w/ reverse pointers
  */  
  auto r_my_it = my_map.rbegin();
  auto r_their_it= their_map.rbegin();
  while (r_my_it != my_map.rend() && r_their_it != their_map.rend()) {
  	assert(r_my_it->first == r_their_it->first);
  	assert(r_my_it->second == r_their_it->second);
  	++ r_my_it;
  	++ r_their_it;
  }
  assert(r_my_it == my_map.rend() && r_their_it == their_map.rend());
  assert_maps_const(my_map, their_map);
}

template <typename Key_T, typename Mapped_T>
void assert_maps_const(const cs540::Map<Key_T, Mapped_T> &my_map, const std::map<Key_T, Mapped_T> &their_map) {
  /*
	Size should be the same
   */
  assert(my_map.size() == their_map.size());
  /*
	Iterate through w/ forward pointers
  */
  auto my_it = my_map.begin();
  auto their_it = their_map.begin();
  while (my_it != my_map.end() && their_it != their_map.end()) {
	assert(my_it->first == their_it->first);
	assert(my_it->second == their_it->second);
	assert((*my_it).first == (*their_it).first);
	assert((*my_it).second == (*their_it).second);
	++ my_it;
	++ their_it;
  }
  assert(my_it == my_map.end());
  assert(their_it == their_map.end());
}

void test_1() {
  cs540::Map<int, int> my_map;
  std::map<int, int> their_map;
  my_map.insert(std::make_pair(1, 1));
  their_map.insert(std::make_pair(1, 1));
  assert_maps(my_map, their_map);
}

void test_2() {
  /*
	Randomly generate ints to insert into map
	Compare equality to std::map
   */
  cs540::Map<int, int> my_map;
  std::map<int, int> their_map;
  assert(my_map.empty());
  assert(their_map.empty());
  for (int i = 0; i < TEST_2_COUNT; ++ i) {
	std::pair<int, int> to_insert(dist_(gen_), dist_(gen_));
	my_map.insert(to_insert);
	their_map.insert(to_insert);
  }
  assert(!my_map.empty());
  assert(!their_map.empty());
  assert_maps(my_map, their_map);
}

void test_3() {
  cs540::Map<int, int> my_map;
  my_map.insert(std::make_pair(0, 0), 0);
  my_map.insert(std::make_pair(10, 0), 3);
  my_map.insert(std::make_pair(2, 0), 0);
  my_map.insert(std::make_pair(8, 0), 1);
  my_map.insert(std::make_pair(3, 0), 1);
  my_map.print();
  // std::map<int, int> their_map;
}

void test_4() {
  /*
	Test element access
   */
  cs540::Map<int, int> my_map;
  std::map<int, int> their_map;
  for (int i = 0; i < TEST_2_COUNT; ++ i) {
	std::pair<int, int> to_insert(dist_(gen_), dist_(gen_));
	my_map.insert(to_insert);
	their_map.insert(to_insert);
  }
  for (int i = 0; i < TEST_2_COUNT; ++ i) {
  	int key = dist_(gen_);
  	auto my_it = my_map.find(key);
  	auto their_it = their_map.find(key);
  	assert((my_it == my_map.end()) == (their_it == their_map.end()));
  	if (my_it != my_map.end()) {
  	  assert(my_it->second == their_it->second);
	  int &my_int = my_map.at(key);
	  int &their_int = their_map.at(key);
	  assert(my_int == their_int);
	  ++ my_int;
	  assert(my_map.at(key) == their_map.at(key) + 1);
	  ++ their_int;
	  assert(my_map.at(key) == their_map.at(key));
	  assert(my_map[key] == their_map[key]);
  	} else {
	  try {
		int x = my_map.at(key);
		/*
		  Code should never get here
		 */
		++ x;
		assert(false);
	  } catch (const std::out_of_range &e) {
		my_map[key] = 63;
		assert(my_map[key] == 63);
		assert(my_map.size() == their_map.size() + 1);
		their_map[key] = 63;
	  } catch (...) {
		/*
		  Should be throwing out_of_range exception
		 */
		assert(false);
	  }
	}
	cs540::Map<int, int>::ConstIterator const_my_it = my_map.find(key);
	std::map<int, int>::const_iterator const_their_it = their_map.find(key);
	assert((const_my_it == my_map.end()) == (const_their_it == their_map.end()));
	if (const_my_it != my_map.end()) {
  	  assert(const_my_it->second == const_their_it->second);
  	}
  }
  assert_maps(my_map, their_map);
  // std::cout << "Completed test 4" << std::endl;
  // if (int i = 0; i < TEST_2_COUNT / 2; ++ i) {
  // 	unsigned int index = dist_(gen_); 
	
  // }
}

void test_class() {
  cs540::Map<MyClass, int> my_map;
  std::map<MyClass, int> their_map;
  for (int i = 0; i < TEST_2_COUNT; ++ i) {
  	std::pair<MyClass, int> to_insert(MyClass(dist_(gen_)), dist_(gen_));
  	// std::cout << to_insert.first << " " << to_insert.second << std::endl;
  	my_map.insert(to_insert);
  	their_map.insert(to_insert);	
  }
  assert_maps(my_map, their_map);
  // assert_maps_const(my_map, their_map);
}

int main() {
  // test_class();
  // test_2();
  // test_3();
  test_4();
}

