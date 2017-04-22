#include "MyInt.hpp"
#include <cstdlib>
#include <cstring>
#include <initializer_list>
#include <utility>
#include <iostream>

#ifndef ARRAY_CS440
#define ARRAY_CS440

#define INITIAL_CAPACITY 256

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
	  data_ = new MyInt[INITIAL_CAPACITY];
	  capacity_ = INITIAL_CAPACITY;
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
  };
}

#endif
