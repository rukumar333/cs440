#include <iostream>
#include <tuple>

#ifndef ARRAY_CS_440
#define ARRAY_CS_440

namespace cs540 {
  template <typename T, size_t... Dims>
  class Array {
	
   private:
	// class ArrayRecursiveBase {
	//  public:
	//   virtual ~ArrayRecursiveBase() {};
	// };

	template <size_t ...DIM_T> class ArrayRecursive;
	
	template <size_t DIM_T, size_t... Dims_Inner>
	class ArrayRecursive<DIM_T, Dims_Inner...> {
	 public:
	  ArrayRecursive<Dims_Inner...> array[DIM_T];
	  ArrayRecursive<Dims_Inner...> &operator[](size_t index) {
		return array[index];
	  }
	};

	template <size_t DIM_T>
	class ArrayRecursive<DIM_T> {
	 public:
	  // ArrayRecursive<Dims_Inner...> array[DIM_T];
	  T array[DIM_T];
	  T &operator[](size_t index) {
		return array[index];
	  }
	  
	};
	
   public:
	typedef T ValueType;
	ArrayRecursive<Dims...> array;

	Array() {
	  
	}
	
	Array(const Array &other);
	
	template <typename U>
	Array(const Array<U, Dims...> &other);

	Array &operator=(const Array &other);

	template <typename U>
	Array &operator=(const Array<U, Dims...> &other);
	
	ArrayRecursive<Dims...> &operator[](size_t index) {
	  return array[index];
	}
  };
}

#endif
