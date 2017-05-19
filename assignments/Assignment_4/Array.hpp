#include <iostream>
#include <tuple>

#ifndef ARRAY_CS_440
#define ARRAY_CS_440

namespace cs540 {
  template <typename T, size_t... Dims>
  class Array {
   private:
	
	// template <size_t DIM_T, std::tuple<size_t>
	// class ArrayRecursive {
	//  public:
	//   ArrayRecursive<Dims_Inner...> array;
	  
	// };

	// template <size_t FIRST_DIM_T>
	// class ArrayRecursive {
	//  public:
	//   // T array[DIM_T];
	  
	// };
	
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
	
  };
}

#endif
