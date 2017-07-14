#include <iostream>
#include <tuple>
#include <type_traits>
#include <stdexcept>
#include <cstring>

#ifndef ARRAY_CS_440
#define ARRAY_CS_440

namespace cs540 {
  class OutOfRange : public std::runtime_error {
   public:
	OutOfRange(char const* const message) throw() : std::runtime_error(message) {}
	virtual const char* what() const throw() {
	  return exception::what();
	}
  };
  
  
  template <typename T, size_t... Dims> class Array;
  template <typename T, size_t DIM_T, size_t... Dims>
  class Array<T, DIM_T, Dims...> {
   public:
	typedef T ValueType;
	typedef Array<T, Dims...> NextArray;
	NextArray array[DIM_T];
	class FirstDimensionMajorIterator;
	class LastDimensionMajorIterator;
	typedef FirstDimensionMajorIterator FMIterator;
	typedef LastDimensionMajorIterator LMIterator;

	class FirstDimensionMajorIterator {
     #define num_dims sizeof...(Dims) + 1
	 public:
	  size_t indices[num_dims];
	  size_t max_dimensions[num_dims];
	  bool end;
	  Array<T, DIM_T, Dims...> *outer_ptr;
	  
	  FirstDimensionMajorIterator() {
		fill_max_dimensions(0, DIM_T, Dims...);
		for (unsigned int i = 0; i < num_dims; ++ i) {
		  indices[i] = 0;
		}
		outer_ptr = nullptr;
		end = false;
	  }

	  FirstDimensionMajorIterator(Array<T, DIM_T, Dims...> &outer, bool begin) {
		fill_max_dimensions(0, DIM_T, Dims...);
		if (begin) {
		  for (unsigned int i = 0; i < num_dims; ++ i) {
			indices[i] = 0;
		  }
		  end = false;
		} else {
		  end = true;
		  for (unsigned int i = 0; i < num_dims; ++ i) {
			indices[i] = 0;
		  }
		}
		outer_ptr = &outer;
	  }

	  FirstDimensionMajorIterator(const FMIterator &other) {
		std::memcpy(indices, other.indices, sizeof(size_t) * num_dims);
		std::memcpy(max_dimensions, max_dimensions, sizeof(size_t) * num_dims);
		outer_ptr = other.outer_ptr;
		end = other.end;
	  }

	  FirstDimensionMajorIterator &operator=(const FMIterator &other) {
		if (this == &other)
		  return *this;
		std::memcpy(indices, other.indices, sizeof(size_t) * num_dims);
		std::memcpy(max_dimensions, max_dimensions, sizeof(size_t) * num_dims);
		outer_ptr = other.outer_ptr;
		end = other.end;
		return *this;
	  }

	  friend bool operator==(const FMIterator &first, const FMIterator &second) {
		if (!first.end && !second.end){
		  bool result = false;
		  result = first.outer_ptr == second.outer_ptr;
		  for(unsigned int i = 0; i < num_dims; ++ i) {
			result = result && (first.indices[i] == second.indices[i]);
			result = result && (first.max_dimensions[i] == second.max_dimensions[i]);
		  }
		  return result;
		}
		if (first.end && second.end)
		  return true; 
		else
		  return false;
	  }

	  friend bool operator!=(const FMIterator &first, const FMIterator &second) {
		return !(first == second);
	  }

	  template <typename ...Dimensions>
	  void fill_max_dimensions(size_t index, size_t FIRST_DIM, Dimensions... dimensions) {
		max_dimensions[index] = FIRST_DIM;
		fill_max_dimensions(index + 1, dimensions...);
	  }

	  void fill_max_dimensions(size_t index, size_t FIRST_DIM) {
		max_dimensions[index] = FIRST_DIM;
	  }

	  void increment(size_t index) {
		if (index == 0) {
		  if (indices[index] < max_dimensions[index]){
			++ indices[index];
			if (indices[index] == max_dimensions[index])
			  end = true;
		  }
		  
		} else {
		  ++ indices[index];
		  if (indices[index] == max_dimensions[index]) {
			increment(index - 1);
			if (indices[index - 1] < max_dimensions[index - 1]) {
			  indices[index] = 0;
			}
		  }
		}
	  }
	  
	  FirstDimensionMajorIterator &operator++() {
		increment(num_dims - 1);
		return *this;
	  }

	  FirstDimensionMajorIterator operator++(int) {
		FMIterator it(*this);
		increment(num_dims - 1);
		return it;
	  }

	  T &operator*() {
		return outer_ptr->get_data(0, (size_t *)indices);
	  }
	};

	class LastDimensionMajorIterator {
     #define num_dims sizeof...(Dims) + 1
	 public:
	  size_t indices[num_dims];
	  size_t max_dimensions[num_dims];
	  bool end;
	  Array<T, DIM_T, Dims...> *outer_ptr;
	  
	  LastDimensionMajorIterator() {
		fill_max_dimensions(0, DIM_T, Dims...);
		for (unsigned int i = 0; i < num_dims; ++ i) {
		  indices[i] = 0;
		}
		outer_ptr = nullptr;
		end = false;
	  }

	  LastDimensionMajorIterator(Array<T, DIM_T, Dims...> &outer, bool begin) {
		fill_max_dimensions(0, DIM_T, Dims...);
		if (begin) {
		  for (unsigned int i = 0; i < num_dims; ++ i) {
			indices[i] = 0;
		  }
		  end = false;
		} else {
		  end = true;
		  for (unsigned int i = 0; i < num_dims; ++ i) {
			indices[i] = 0;
		  }
		}
		outer_ptr = &outer;
	  }

	  LastDimensionMajorIterator(const LMIterator &other) {
		std::memcpy(indices, other.indices, sizeof(size_t) * num_dims);
		std::memcpy(max_dimensions, max_dimensions, sizeof(size_t) * num_dims);
		outer_ptr = other.outer_ptr;
		end = other.end;
	  }

	  LastDimensionMajorIterator &operator=(const LMIterator &other) {
		if (this == &other)
		  return *this;
		std::memcpy(indices, other.indices, sizeof(size_t) * num_dims);
		std::memcpy(max_dimensions, max_dimensions, sizeof(size_t) * num_dims);
		outer_ptr = other.outer_ptr;
		end = other.end;
		return *this;
	  }

	  friend bool operator==(const LMIterator &first, const LMIterator &second) {
		if (!first.end && !second.end){
		  bool result = false;
		  result = first.outer_ptr == second.outer_ptr;
		  for(unsigned int i = 0; i < num_dims; ++ i) {
			result = result && (first.indices[i] == second.indices[i]);
			result = result && (first.max_dimensions[i] == second.max_dimensions[i]);
		  }
		  return result;
		}
		if (first.end && second.end)
		  return true; 
		else
		  return false;
	  }

	  friend bool operator!=(const LMIterator &first, const LMIterator &second) {
		return !(first == second);
	  }

	  template <typename ...Dimensions>
	  void fill_max_dimensions(size_t index, size_t FIRST_DIM, Dimensions... dimensions) {
		max_dimensions[index] = FIRST_DIM;
		fill_max_dimensions(index + 1, dimensions...);
	  }

	  void fill_max_dimensions(size_t index, size_t FIRST_DIM) {
		max_dimensions[index] = FIRST_DIM;
	  }

	  void increment(size_t index) {
		if (index == num_dims - 1) {
		  if (indices[index] < max_dimensions[index]){
			++ indices[index];
			if (indices[index] == max_dimensions[index])
			  end = true;
		  }
		} else {
		  ++ indices[index];
		  if (indices[index] == max_dimensions[index]) {
			increment(index + 1);
			if (indices[index + 1] < max_dimensions[index + 1]) {
			  indices[index] = 0;
			}
		  }
		}
	  }
	  
	  LastDimensionMajorIterator &operator++() {
		increment(0);
		return *this;
	  }

	  LastDimensionMajorIterator operator++(int) {
		LMIterator it(*this);
		increment(0);
		return it;
	  }

	  T &operator*() {
		return outer_ptr->get_data(0, (size_t *)indices);
	  }
	};

	T &get_data(size_t index, size_t *indices) {
	  return array[*(indices + index)].get_data(index + 1, indices);
	}
	
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
	Array(const Array<U, DIM_T, Dims...> &other) {
	  static_assert(DIM_T != 0);
	  for(size_t i = 0; i < DIM_T; ++ i) {
		array[i] = other.array[i];
	  }
	}

	Array &operator=(const Array &other) {
	  if (this == &other)
		return *this;
	  for(size_t i = 0; i < DIM_T; ++ i) {
		array[i] = other.array[i];
	  }
	  return *this;
	}

	template <typename U>
	Array &operator=(const Array<U, DIM_T, Dims...> &other) {
	  for(size_t i = 0; i < DIM_T; ++ i) {
		array[i] = other.array[i];
	  }
	  return *this;
	}
	
	Array<T, Dims...> &operator[](size_t index) {
	  if (index < 0 || index >= DIM_T) {
		throw OutOfRange("Index out of range!\n");
	  }
	  return array[index];
	}

	const Array<T, Dims...> &operator[](size_t index) const {
	  if (index < 0 || index >= DIM_T) {
		throw OutOfRange("Index out of range!\n");
	  }
	  return array[index];
	}

	FMIterator fmbegin() {
	  return FMIterator(*this, true);
	}

	FMIterator fmend() {
	  return FMIterator(*this, false);	  
	}

	LMIterator lmbegin() {
	  return LMIterator(*this, true);
	}

	LMIterator lmend() {
	  return LMIterator(*this, false);
	}
  };

  template <typename T, size_t DIM_T>
  class Array<T, DIM_T> {
   public:
	typedef T ValueType;
	T array[DIM_T];
	class FirstDimensionMajorIterator;
	class LastDimensionMajorIterator;
	typedef FirstDimensionMajorIterator FMIterator;
	typedef LastDimensionMajorIterator LMIterator;

	class FirstDimensionMajorIterator {
	 public:
	  size_t current_index;
	  bool end;
	  Array<T, DIM_T> *outer_ptr;
	  
	  FirstDimensionMajorIterator() {
		current_index = 0;
		outer_ptr = nullptr;
		end = false;
	  }

	  FirstDimensionMajorIterator(Array<T, DIM_T> &outer, bool begin) {
		if (begin) {
		  current_index = 0;
		  end = false;
		} else {
		  end = true;
		  current_index = 0;
		}
		outer_ptr = &outer;
	  }

	  FirstDimensionMajorIterator(const FMIterator &other) {
		current_index = other.current_index;
		outer_ptr = other.outer_ptr;
		end = other.end;
	  }

	  FirstDimensionMajorIterator &operator=(const FMIterator &other) {
		if (this == &other)
		  return *this;
		current_index = other.current_index;
		outer_ptr = other.outer_ptr;
		end = other.end;
		return *this;
	  }

	  friend bool operator==(const FMIterator &first, const FMIterator &second) {
		if (!first.end && !second.end){
		  bool result = (first.outer_ptr == second.outer_ptr) &&
			(first.current_index == second.current_index);
		  return result;		  
		}
		if (first.end && second.end)
		  return true; 
		else
		  return false;

	  }

	  friend bool operator!=(const FMIterator &first, const FMIterator &second) {
		return !(first == second);
	  }
	  
	  FirstDimensionMajorIterator &operator++() {
		if (current_index < DIM_T) {
		  ++ current_index;
		  if (current_index == DIM_T) {
			end = true;
		  }
		}
		return *this;
	  }

	  FirstDimensionMajorIterator operator++(int) {
		FMIterator it(*this);
		if (current_index < DIM_T) {
		  ++ current_index;
		  if (current_index == DIM_T) {
			end = true;
		  }
		}
		return it;
	  }

	  T &operator*() {
		return outer_ptr->array[current_index];
	  }
	};

	class LastDimensionMajorIterator {
	 public:
	  size_t current_index;
	  bool end;
	  Array<T, DIM_T> *outer_ptr;
	  
	  LastDimensionMajorIterator() {
		current_index = 0;
		outer_ptr = nullptr;
		end = false;
	  }

	  LastDimensionMajorIterator(Array<T, DIM_T> &outer, bool begin) {
		if (begin) {
		  current_index = 0;
		  end = false;
		} else {
		  end = true;
		  current_index = 0;
		}
		outer_ptr = &outer;
	  }

	  LastDimensionMajorIterator(const LMIterator &other) {
		current_index = other.current_index;
		outer_ptr = other.outer_ptr;
		end = other.end;
	  }

	  LastDimensionMajorIterator &operator=(const LMIterator &other) {
		if (this == &other)
		  return *this;
		current_index = other.current_index;
		outer_ptr = other.outer_ptr;
		end = other.end;
		return *this;
	  }

	  friend bool operator==(const LMIterator &first, const LMIterator &second) {
		if (!first.end && !second.end){
		  bool result = (first.outer_ptr == second.outer_ptr) &&
			(first.current_index == second.current_index);
		  return result;		  
		}
		if (first.end && second.end)
		  return true; 
		else
		  return false;

	  }

	  friend bool operator!=(const LMIterator &first, const LMIterator &second) {
		return !(first == second);
	  }
	  
	  LastDimensionMajorIterator &operator++() {
		if (current_index < DIM_T) {
		  ++ current_index;
		  if (current_index == DIM_T) {
			end = true;
		  }
		}
		return *this;
	  }

	  LastDimensionMajorIterator operator++(int) {
		LMIterator it(*this);
		if (current_index < DIM_T) {
		  ++ current_index;
		  if (current_index == DIM_T) {
			end = true;
		  }
		}
		return it;
	  }

	  T &operator*() {
		return outer_ptr->array[current_index];
	  }
	};

	T &get_data(size_t index, size_t *indices) {
	  return array[*(indices + index)];
	}
	
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
	  if (this == &other)
		return *this;
	  for(size_t i = 0; i < DIM_T; ++ i) {
		array[i] = other.array[i];
	  }
	  return *this;
	}

	template <typename U>
	Array &operator=(const Array<U, DIM_T> &other) {
	  for(size_t i = 0; i < DIM_T; ++ i) {
		array[i] = other.array[i];
	  }
	  return *this;
	}
	
	T &operator[](size_t index) {
	  if (index < 0 || index >= DIM_T) {
		throw OutOfRange("Index out of range!\n");
	  }
	  return array[index];
	}

	const T &operator[](size_t index) const {
	  if (index < 0 || index >= DIM_T) {
		throw OutOfRange("Index out of range!\n");
	  }
	  return array[index];
	}
	
	FMIterator fmbegin() {
	  return FMIterator(*this, true);
	}

	FMIterator fmend() {
	  return FMIterator(*this, false);
	}
		
	LMIterator lmbegin() {
	  return LMIterator(*this, true);
	}

	LMIterator lmend() {
	  return LMIterator(*this, false);
	}
  };
}

#endif
