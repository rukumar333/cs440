#include "MyInt.hpp"
#include <cstdlib>
#include <cstring>
#include <initializer_list>
#include <utility>
#include <iostream>
#include <chrono>

#ifndef ARRAY_CS440
#define ARRAY_CS440

#define TEST_CAPACITY 100000

namespace cs540 {
  class Array {
   private:
	void insert(MyInt element) {
	  while (size_ >= capacity_) {
		resize();
	  }
	  *(data_ + size_) = element;
	  ++ size_;
	}
	void resize() {
	  MyInt *allocated_data = new MyInt[capacity_ * 2];
	  memcpy(allocated_data, data_, size_ * sizeof(MyInt));
	  delete[] data_;
	  data_ = allocated_data;
	  capacity_ = capacity_ * 2;
	}
	MyInt *data_;
	size_t capacity_;
	size_t size_;
   public:
	Array() {
	  data_ = nullptr;
	  capacity_ = 0;
	  size_ = 0;
	}

	Array(std::initializer_list<MyInt> init_list) {
	  capacity_ = init_list.size() * 2;
	  size_ = 0;
	  data_ = new MyInt[capacity_];
	  auto it = init_list.begin();
	  while (it != init_list.end()) {
		insert(*it);
		++ it;
	  }
	}

	Array(const Array& other) {
	  capacity_ = other.capacity_;
	  size_ = other.size_;
	  data_ = new MyInt[capacity_];
	  memcpy(data_, other.data_, size_ * sizeof(MyInt));
	}

	Array(Array &&other) {
	  capacity_  = std::move(other.capacity_);
	  size_ = std::move(other.size_);
	  data_ = std::move(other.data_);
	  other.data_ = nullptr;
	  other.size_ = 0;
	  other.capacity_ = 0;
	}

	Array& operator=(const Array& other) {
	  if (this != &other) {
		if (data_)
		  delete[] data_;
		capacity_ = other.capacity_;
		size_ = other.size_;
		data_ = new MyInt[capacity_];
		memcpy(data_, other.data_, size_ * sizeof(MyInt));
	  }
	  return *this;
	}

	Array& operator=(Array &&other) {
	  if (this != &other) {
		if (data_)
		  delete[] data_;
		capacity_  = std::move(other.capacity_);
		size_ = std::move(other.size_);
		data_ = std::move(other.data_);
		other.data_ = nullptr;
		other.data_ = nullptr;
		other.size_ = 0;
		other.capacity_ = 0;
	  }
	  return *this;
	}

	~Array() {
	  if (data_ != nullptr)
		delete[] data_;
	}

	friend std::ostream& operator<<(std::ostream &os, const Array &array) {
	  size_t i = 0;
	  while (i < array.size_ - 1) {
		os << *(array.data_ + i) << ", ";
		++ i;
	  }
	  os << *(array.data_ + i);
	  return os;
	}

	static void move_performance_test() {
	  using TimePoint = std::chrono::time_point<std::chrono::system_clock>;
	  using Milli = std::chrono::duration<double, std::ratio<1,1000>>;
	  using namespace std::chrono;
	  TimePoint start, end;
	  Array a1;
	  a1.data_ = new MyInt[TEST_CAPACITY];
	  a1.capacity_ = TEST_CAPACITY;
	  for (unsigned int i = 0; i < TEST_CAPACITY; ++ i) {
		*(a1.data_ + i) = i;
	  }
	  std::cerr << "Testing with Array of size " << TEST_CAPACITY << std::endl;
	  start = system_clock::now();
	  Array a2{a1};
	  end = system_clock::now();
	  Milli elapsed = end - start;
	  std::cerr << "Milliseconds for copy constructor: " << elapsed.count() << std::endl;
	  start = system_clock::now();
	  Array a3{std::move(a1)};
	  end = system_clock::now();
	  elapsed = end - start;
	  std::cerr << "Milliseconds for move constructor: " << elapsed.count() << std::endl;
	  start = system_clock::now();
	  a1 = a2;
	  end = system_clock::now();
	  elapsed = end - start;
	  std::cerr << "Milliseconds for copy assignment: " << elapsed.count() << std::endl;
	  start = system_clock::now();
	  a3 = std::move(a2);
	  end = system_clock::now();
	  elapsed = end - start;
	  std::cerr << "Milliseconds for move assignment: " << elapsed.count() << std::endl;	  
	}
  };
}

#endif
