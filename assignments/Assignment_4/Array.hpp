#include <iostream>
#include <tuple>
#include <type_traits>

#ifndef ARRAY_CS_440
#define ARRAY_CS_440

namespace cs540 {
  template <typename T, size_t... Dims> class Array;
  template <typename T, size_t DIM_T, size_t... Dims>
  class Array<T, DIM_T, Dims...> {
   public:
	typedef T ValueType;
	Array<T, Dims...> array[DIM_T];
	Array() {
	  static_assert(DIM_T != 0);
	}
	
	Array(const Array &other) {
	  static_assert(DIM_T != 0);
	  for(size_t i = 0; i < DIM_T; ++ i) {
		array[i] = other.array[i];
	  }
	}
	
	template <typename U>
	Array(const Array<U, Dims...> &other) {
	  static_assert(DIM_T != 0);
	  for(size_t i = 0; i < DIM_T; ++ i) {
		array[i] = other.array[i];
	  }
	}

	Array &operator=(const Array &other) {
	  for(size_t i = 0; i < DIM_T; ++ i) {
		array[i] = other.array[i];
	  }	  
	}

	template <typename U>
	Array &operator=(const Array<U, Dims...> &other) {
	  for(size_t i = 0; i < DIM_T; ++ i) {
		array[i] = other.array[i];
	  }
	}
	
	Array<T, Dims...> &operator[](size_t index) {
	  return array[index];
	}
  };

  template <typename T, size_t DIM_T>
  class Array<T, DIM_T> {
   public:
	typedef T ValueType;
	T array[DIM_T];
	Array() {
	  static_assert(DIM_T != 0);	  
	}
	
	Array(const Array &other) {
	  static_assert(DIM_T != 0);
	  for(size_t i = 0; i < DIM_T; ++ i) {
		array[i] = other.array[i];
	  }
	}
	
	template <typename U>
	Array(const Array<U, DIM_T> &other) {
	  static_assert(DIM_T != 0);
	  for(size_t i = 0; i < DIM_T; ++ i) {
		array[i] = other.array[i];
	  }
	}

	Array &operator=(const Array &other) {
	  for(size_t i = 0; i < DIM_T; ++ i) {
		array[i] = other.array[i];
	  }
	}

	template <typename U>
	Array &operator=(const Array<U, DIM_T> &other) {
	  for(size_t i = 0; i < DIM_T; ++ i) {
		array[i] = other.array[i];
	  }
	}
	
	T &operator[](size_t index) {
	  return array[index];
	}
  };
}

#endif
