#include <iostream>
#include <string>
#include <map>
#include <random>
#include <cassert>
#include "Map.hpp"

#define UPPER_LIMIT 10000
#define LOWER_LIMIT 0

#define TEST_2_COUNT 10000

std::random_device rand_dev_;
std::mt19937_64 gen_(rand_dev_());
std::uniform_int_distribution<int> dist_(LOWER_LIMIT, UPPER_LIMIT);

class MyClass {
 private:
  MyClass();
  MyClass &operator=(const MyClass &other);
 public:
  int data;
  MyClass(int a) {
	data = a;
  }
  MyClass(const MyClass &other) {
	this->data = other.data;
  }
  friend bool operator<(const MyClass &a, const MyClass &b) { return a.data < b.data; }
  friend bool operator==(const MyClass &a, const MyClass &b) { return a.data == b.data; }
};

class Foo {
 private:
  Foo();
  Foo &operator=(const Foo &other);
 public:
  int data;
  Foo(int a) { data = a; }
  friend bool operator==(const Foo &a, const Foo &b) { return a.data == b.data; }
  Foo &operator++() {
	++ data;
	return *this;
  }
  Foo operator++(int) {
	++ data;
	return *this;
  }
};

template <typename Map_One_T, typename Map_Two_T>
void assert_maps_const(const Map_One_T &my_map, const Map_Two_T &their_map);

template <typename Map_One_T, typename Map_Two_T>
void assert_maps(Map_One_T &my_map, Map_Two_T &their_map) {
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

template <typename Map_One_T, typename Map_Two_T>
void assert_maps_const(const Map_One_T &my_map, const Map_Two_T &their_map) {
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

void test_2(cs540::Map<int, int> &my_map, std::map<int, int> &their_map);
void test_3();
void test_4(cs540::Map<int, int> &my_map);
void test_5(cs540::Map<int, int> &my_map);
void test_6(cs540::Map<int, int> &my_map, std::map<int, int> &their_map);
void test_class_2(cs540::Map<MyClass, Foo> &my_map, std::map<MyClass, Foo> &their_map);
void test_class_3();
void test_class_4(cs540::Map<MyClass, Foo> &my_map);
void test_class_5(cs540::Map<MyClass, Foo> &my_map);

template <typename Map_One_T, typename Map_Two_T>
void create_equal_maps(Map_One_T &my_map, Map_Two_T &their_map, int num_elements) {
  assert(my_map.empty());
  assert(their_map.empty());
  for (int i = 0; i < num_elements; ++ i) {
	std::pair<int, int> to_insert(dist_(gen_), dist_(gen_));
	auto my_it = my_map.insert(to_insert);
	auto their_it = their_map.insert(to_insert);
	assert(my_it.second == their_it.second);
  }
  assert(!my_map.empty());
  assert(!their_map.empty());
  assert_maps(my_map, their_map);
}

template <typename Map_One_T, typename Map_Two_T>
void myclass_create_equal_maps(Map_One_T &my_map, Map_Two_T &their_map, int num_elements) {
  assert(my_map.empty());
  assert(their_map.empty());
  for (int i = 0; i < num_elements; ++ i) {
	std::pair<MyClass, int> to_insert(MyClass(dist_(gen_)), dist_(gen_));
	auto my_it = my_map.insert(to_insert);
	auto their_it = their_map.insert(to_insert);
	assert(my_it.second == their_it.second);
  }
  assert(!my_map.empty());
  assert(!their_map.empty());
  assert_maps(my_map, their_map);
}

template <typename Map_One_T, typename Map_Two_T>
void foo_create_equal_maps(Map_One_T &my_map, Map_Two_T &their_map, int num_elements) {
  assert(my_map.empty());
  assert(their_map.empty());
  for (int i = 0; i < num_elements; ++ i) {
	std::pair<MyClass, Foo> to_insert(MyClass(dist_(gen_)), Foo(dist_(gen_)));
	auto my_it = my_map.insert(to_insert);
	auto their_it = their_map.insert(to_insert);
	assert(my_it.second == their_it.second);
  }
  assert(!my_map.empty());
  assert(!their_map.empty());
  assert_maps(my_map, their_map);
}


void test_1() {
  /*
	Test element access
   */
  cs540::Map<int, int> my_map;
  std::map<int, int> their_map;
  create_equal_maps(my_map, their_map, TEST_2_COUNT);
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
  test_2(my_map, their_map);
}

void test_2(cs540::Map<int, int> &my_map, std::map<int, int> &their_map) {
  /*
	Test modifier
   */
  std::uniform_int_distribution<int> dist_test_two(LOWER_LIMIT * 2, UPPER_LIMIT * 2);
  std::uniform_int_distribution<int> dist_test_four(LOWER_LIMIT * 4, UPPER_LIMIT * 4);
  std::uniform_int_distribution<int> dist_test_half(LOWER_LIMIT / 2, UPPER_LIMIT / 2);
  for (int i = 0; i < TEST_2_COUNT / 2; ++ i) {
	std::pair<int, int> to_insert(dist_test_two(gen_), dist_test_two(gen_));
	auto my_ret = my_map.insert(to_insert);
	auto their_ret = their_map.insert(to_insert);
	assert(my_ret.second == their_ret.second);
	assert(my_ret.first->first == their_ret.first->first);
	assert(my_ret.first->second == their_ret.first->second);
  }
  assert_maps(my_map, their_map);
  std::vector<std::pair<int, int> > vec;
  for (int i = 0; i < TEST_2_COUNT / 2; ++ i) {
	vec.push_back(std::make_pair(dist_test_four(gen_), dist_test_four(gen_)));
  }
  /*
	Should not insert anything;
   */
  my_map.insert(vec.end(), vec.end());
  assert(my_map.size() == their_map.size());
  my_map.insert(vec.begin(), vec.end());
  assert(my_map.size() != their_map.size());
  their_map.insert(vec.begin(), vec.end());
  assert_maps(my_map, their_map);
  for (int i = 0; i < TEST_2_COUNT; ++ i) {
  	int key = dist_test_half(gen_);
  	auto my_it = my_map.find(key);
  	auto their_it = their_map.find(key);
	assert((my_it == my_map.end()) == (their_it == their_map.end()));
  	if (key % 2 == 0) {
  	  if (my_it != my_map.end()) {
  		my_map.erase(my_it);
		their_map.erase(their_it);
  	  }
  	} else {
  	  if (my_it != my_map.end()) {
  		my_map.erase(key);
		their_map.erase(key);
  	  } else {
		try {
		  my_map.erase(key);
		  /*
			Should never get here
		   */
		  assert(false);
		} catch (const std::out_of_range &e) {
		  
		} catch (...) {
		  /*
			Should be throwing out_of_range exception
		  */
		  assert(false);
		}
	  }
	}
  }
  my_map.clear();
  assert(my_map.size() == 0);
  assert(my_map.empty());
  auto it = their_map.begin();
  while (it != their_map.end()) {
	my_map.insert(*it);
	++ it;
  }
  assert_maps(my_map, their_map);
  test_3();
  test_4(my_map);
  test_6(my_map, their_map);
}

void test_3() {
  /*
	Test Map comparison
   */
  cs540::Map<int, int> my_first;
  cs540::Map<int, int> my_second;
  std::map<int, int> their_first;
  std::map<int, int> their_second;
  for (int i = 0; i < 5; ++ i) {
	create_equal_maps(my_first, their_first, TEST_2_COUNT / 2);
	create_equal_maps(my_second, their_second, TEST_2_COUNT / 2);
	assert((my_first == my_second) == (their_first == their_second));
	assert((my_first != my_second) == (their_first != their_second));
	assert((my_first < my_second) == (their_first < their_second));
	my_first.clear();
	my_second.clear();
	their_first.clear();
	their_second.clear();
  }
  for (int i = 0; i < 50; ++ i) {
	create_equal_maps(my_first, my_second, TEST_2_COUNT / 2);
	assert(my_first == my_second);
	assert(!(my_first != my_second));
	auto it = my_first.rbegin();
	switch (i % 3) {
	case 0:
	  my_first.insert(std::make_pair(UPPER_LIMIT + 10, UPPER_LIMIT + 10));
	  assert(my_second < my_first);
	  assert(!(my_first < my_second));
	  break;
	case 1:
	  ++ it;
	  it->second = UPPER_LIMIT + 10;
	  assert(my_second < my_first);
	  assert(my_second != my_first);
	  break;
	case 2:
	  ++ it;
	  it->second = LOWER_LIMIT - 10;
	  assert(my_first < my_second);
	  assert(my_first != my_second);
	  break;
	}
	my_first.clear();
	my_second.clear();
  }
}

void test_4(cs540::Map<int, int> &my_map) {
  /*
	Test ctors
   */
  auto first_map = my_map;
  assert(first_map == my_map);
  auto second_map(my_map);
  my_map = my_map;
  assert(second_map == first_map);
  assert(second_map == my_map);
  assert(my_map == my_map);
  cs540::Map<int, int> init_map{{1, 2}, {10, 5}, {-90, -10}};
  auto init_it = init_map.begin();
  assert(init_it->first == -90);
  assert(init_it->second == -10);
  ++ init_it;
  assert(init_it->first == 1);
  assert(init_it->second == 2);
  ++ init_it;
  assert(init_it->first == 10);
  assert(init_it->second == 5);
  ++ init_it;
  assert(init_it == init_map.end());
  assert(init_map.size() == 3);
  /* 
	 Check to make sure default constructed map followed by dtro
	 doesn't lead to leaked memory
   */
  cs540::Map<int, int> map();
  test_5(my_map);
}

void test_5(cs540::Map<int, int> &my_map) {
  auto &other_map = my_map;
  auto my_it = my_map.begin();
  auto other_it = other_map.begin();
  while (my_it != my_map.end()) {
	assert(my_it == other_it);
	++ other_it;
	++ my_it;
  }
  assert(my_it == other_it);
  cs540::Map<int, int>::ConstIterator my_it_const = my_map.begin();
  cs540::Map<int, int>::ConstIterator other_it_const = other_map.begin();
  my_it = my_map.begin();
  while (my_it_const != my_map.end()) {
	assert(my_it_const == other_it_const);
	assert(my_it == other_it_const);
	++ other_it_const;
	++ my_it_const;
	++ my_it;
  }
  auto diff_map(my_map);
  assert(my_map.begin() != diff_map.begin());
  assert(my_map.rbegin() != diff_map.rbegin());
  assert(my_it_const == other_it_const);
  auto r_my_it = my_map.rbegin();
  auto r_other_it = other_map.rbegin();
  while (r_my_it != my_map.rend()) {
	assert(r_my_it == r_other_it);
	++ r_my_it;
	++ r_other_it;
  }
}

void test_6(cs540::Map<int, int> &my_map, std::map<int, int> &their_map) {
  {
	auto my_it = my_map.begin();
	auto their_it = their_map.begin();
	assert(my_map.begin() == (my_it ++));
	assert(their_map.begin() == (their_it ++));
	assert(my_map.begin() == (-- my_it));
	assert(their_map.begin() == (-- their_it));
	assert(my_map.begin() != (++ my_it));
	assert(their_map.begin() != (++ their_it));
	assert(my_map.begin() != (my_it --));
	assert(their_map.begin() != (their_it --));
  }

  {
	cs540::Map<int, int>::ConstIterator my_it = my_map.begin();
	std::map<int, int>::const_iterator their_it = their_map.begin();
	assert(my_map.begin() == (my_it ++));
	assert(their_map.begin() == (their_it ++));
	assert(my_map.begin() == (-- my_it));
	assert(their_map.begin() == (-- their_it));
	assert(my_map.begin() != (++ my_it));
	assert(their_map.begin() != (++ their_it));
	assert(my_map.begin() != (my_it --));
	assert(their_map.begin() != (their_it --));
  }

  {
	auto my_it = my_map.rbegin();
	auto their_it = their_map.rbegin();
	assert(my_map.rbegin() == (my_it ++));
	assert(their_map.rbegin() == (their_it ++));
	assert(my_map.rbegin() == (-- my_it));
	assert(their_map.rbegin() == (-- their_it));
	assert(my_map.rbegin() != (++ my_it));
	assert(their_map.rbegin() != (++ their_it));
	assert(my_map.rbegin() != (my_it --));
	assert(their_map.rbegin() != (their_it --));
  }
}

void test_class() {
  /*
	Test element access
   */
  cs540::Map<MyClass, Foo> my_map;
  std::map<MyClass, Foo> their_map;
  foo_create_equal_maps(my_map, their_map, TEST_2_COUNT);
  for (int i = 0; i < TEST_2_COUNT; ++ i) {
  	MyClass key(dist_(gen_));
  	auto my_it = my_map.find(key);
  	auto their_it = their_map.find(key);
  	assert((my_it == my_map.end()) == (their_it == their_map.end()));
  	if (my_it != my_map.end()) {
  	  assert(my_it->second == their_it->second);
	  Foo &my_int = my_map.at(key);
	  Foo &their_int = their_map.at(key);
	  assert(my_int == their_int);
	  ++ my_int;
	  assert(my_map.at(key).data == their_map.at(key).data + 1);
	  ++ their_int;
	  assert(my_map.at(key) == their_map.at(key));
  	} else {
	  try {
		Foo x = my_map.at(key);
		/*
		  Code should never get here
		 */
		++ x;
		assert(false);
	  } catch (const std::out_of_range &e) {
		
	  } catch (...) {
		/*
		  Should be throwing out_of_range exception
		 */
		assert(false);
	  }
	}
	cs540::Map<MyClass, Foo>::ConstIterator const_my_it = my_map.find(key);
	std::map<MyClass, Foo>::const_iterator const_their_it = their_map.find(key);
	assert((const_my_it == my_map.end()) == (const_their_it == their_map.end()));
	if (const_my_it != my_map.end()) {
  	  assert(const_my_it->second == const_their_it->second);
  	}
  }
  assert_maps(my_map, their_map);
  test_class_2(my_map, their_map);
}

void test_class_2(cs540::Map<MyClass, Foo> &my_map, std::map<MyClass, Foo> &their_map) {
  /*
	Test modifier
  */
  std::uniform_int_distribution<int> dist_test_two(LOWER_LIMIT * 2, UPPER_LIMIT * 2);
  std::uniform_int_distribution<int> dist_test_four(LOWER_LIMIT * 4, UPPER_LIMIT * 4);
  std::uniform_int_distribution<int> dist_test_half(LOWER_LIMIT / 2, UPPER_LIMIT / 2);
  for (int i = 0; i < TEST_2_COUNT / 2; ++ i) {
	std::pair<MyClass, Foo> to_insert(MyClass(dist_test_two(gen_)), Foo(dist_test_two(gen_)));
	auto my_ret = my_map.insert(to_insert);
	auto their_ret = their_map.insert(to_insert);
	assert(my_ret.second == their_ret.second);
	assert(my_ret.first->first == their_ret.first->first);
	assert(my_ret.first->second == their_ret.first->second);
  }
  assert_maps(my_map, their_map);
  std::vector<std::pair<MyClass, Foo> > vec;
  for (int i = 0; i < TEST_2_COUNT / 2; ++ i) {
	vec.push_back(std::make_pair(MyClass(dist_test_four(gen_)), Foo(dist_test_four(gen_))));
  }
  /*
	Should not insert anything;
  */
  my_map.insert(vec.end(), vec.end());
  assert(my_map.size() == their_map.size());
  my_map.insert(vec.begin(), vec.end());
  assert(my_map.size() != their_map.size());
  their_map.insert(vec.begin(), vec.end());
  assert_maps(my_map, their_map);
  for (int i = 0; i < TEST_2_COUNT; ++ i) {
  	MyClass key(dist_test_half(gen_));
  	auto my_it = my_map.find(key);
  	auto their_it = their_map.find(key);
	assert((my_it == my_map.end()) == (their_it == their_map.end()));
  	if (key.data % 2 == 0) {
  	  if (my_it != my_map.end()) {
  		my_map.erase(my_it);
		their_map.erase(their_it);
  	  }
  	} else {
  	  if (my_it != my_map.end()) {
  		my_map.erase(key);
		their_map.erase(key);
  	  } else {
		try {
		  my_map.erase(key);
		  /*
			Should never get here
		  */
		  assert(false);
		} catch (const std::out_of_range &e) {
		  
		} catch (...) {
		  /*
			Should be throwing out_of_range exception
		  */
		  assert(false);
		}
	  }
	}
  }
  my_map.clear();
  assert(my_map.size() == 0);
  assert(my_map.empty());
  auto it = their_map.begin();
  while (it != their_map.end()) {
	my_map.insert(*it);
	++ it;
  }
  assert_maps(my_map, their_map);
  test_class_3();
  test_class_4(my_map);
}

void test_class_3() {
  /*
	Test Map comparison
   */
  cs540::Map<MyClass, int> my_first;
  cs540::Map<MyClass, int> my_second;
  std::map<MyClass, int> their_first;
  std::map<MyClass, int> their_second;
  for (int i = 0; i < 5; ++ i) {
	myclass_create_equal_maps(my_first, their_first, TEST_2_COUNT / 2);
	myclass_create_equal_maps(my_second, their_second, TEST_2_COUNT / 2);
	assert((my_first == my_second) == (their_first == their_second));
	assert((my_first != my_second) == (their_first != their_second));
	assert((my_first < my_second) == (their_first < their_second));
	my_first.clear();
	my_second.clear();
	their_first.clear();
	their_second.clear();
  }
  for (int i = 0; i < 50; ++ i) {
	myclass_create_equal_maps(my_first, my_second, TEST_2_COUNT / 2);
	assert(my_first == my_second);
	assert(!(my_first != my_second));
	auto it = my_first.rbegin();
	switch (i % 3) {
	case 0:
	  my_first.insert(std::make_pair(MyClass(UPPER_LIMIT + 10), UPPER_LIMIT + 10));
	  assert(my_second < my_first);
	  assert(!(my_first < my_second));
	  break;
	case 1:
	  ++ it;
	  it->second = UPPER_LIMIT + 10;
	  assert(my_second < my_first);
	  assert(my_second != my_first);
	  break;
	case 2:
	  ++ it;
	  it->second = LOWER_LIMIT - 10;
	  assert(my_first < my_second);
	  assert(my_first != my_second);
	  break;
	}
	my_first.clear();
	my_second.clear();
  }
}

void test_class_4(cs540::Map<MyClass, Foo> &my_map) {
  /*
	Test ctors
   */
  auto first_map = my_map;
  assert(first_map == my_map);
  auto second_map(my_map);
  my_map = my_map;
  assert(second_map == first_map);
  assert(second_map == my_map);
  assert(my_map == my_map);
  cs540::Map<MyClass, Foo> init_map{{MyClass(1), Foo(2)}, {MyClass(10), Foo(5)}, {MyClass(-90), Foo(-10)}};
  auto init_it = init_map.begin();
  assert(init_it->first == MyClass(-90));
  assert(init_it->second == Foo(-10));
  ++ init_it;
  assert(init_it->first == MyClass(1));
  assert(init_it->second == Foo(2));
  ++ init_it;
  assert(init_it->first == MyClass(10));
  assert(init_it->second == Foo(5));
  ++ init_it;
  assert(init_it == init_map.end());
  assert(init_map.size() == 3);
  /* 
	 Check to make sure default constructed map followed by dtro
	 doesn't lead to leaked memory
   */
  cs540::Map<MyClass, Foo> map();
  test_class_5(my_map);
}

void test_class_5(cs540::Map<MyClass, Foo> &my_map) {
  auto &other_map = my_map;
  auto my_it = my_map.begin();
  auto other_it = other_map.begin();
  while (my_it != my_map.end()) {
	assert(my_it == other_it);
	++ other_it;
	++ my_it;
  }
  assert(my_it == other_it);
  cs540::Map<MyClass, Foo>::ConstIterator my_it_const = my_map.begin();
  cs540::Map<MyClass, Foo>::ConstIterator other_it_const = other_map.begin();
  my_it = my_map.begin();
  while (my_it_const != my_map.end()) {
	assert(my_it_const == other_it_const);
	assert(my_it == other_it_const);
	++ other_it_const;
	++ my_it_const;
	++ my_it;
  }
  auto diff_map(my_map);
  assert(my_map.begin() != diff_map.begin());
  assert(my_map.rbegin() != diff_map.rbegin());
  assert(my_it_const == other_it_const);
  auto r_my_it = my_map.rbegin();
  auto r_other_it = other_map.rbegin();
  while (r_my_it != my_map.rend()) {
	assert(r_my_it == r_other_it);
	++ r_my_it;
	++ r_other_it;
  }
}

int main() {
  test_class();
  test_1();
}
