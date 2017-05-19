#include <iostream>
#include <tuple>
#include <type_traits>
#include <stdexcept>

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
	 private:
	  typedef typename NextArray::FirstDimensionMajorIterator NextIterator;
	  friend class Array<T, DIM_T, Dims...>;
	  size_t index;
	  NextIterator next_iterator;
	  Array<T, DIM_T, Dims...> *outer_ptr;
	 public:
	  bool at_end;
	  FirstDimensionMajorIterator(Array<T, DIM_T, Dims...> &outer_class) {
		at_end = false;
		index = 0;
		outer_ptr = &outer_class;
		next_iterator = outer_ptr->array[index].fmbegin();
	  }
	  
	  FirstDimensionMajorIterator() {
		at_end = false;
		index = 0;
		outer_ptr = nullptr;
	  }
	  
	  FirstDimensionMajorIterator(const FMIterator &other) {
		at_end = other.at_end;
		next_iterator = other.next_iterator;
		index = other.index;
		outer_ptr = other.outer_ptr;
	  }
	  
	  FirstDimensionMajorIterator &operator=(const FMIterator &other) {
		at_end = other.at_end;
		next_iterator = other.next_iterator;
		index = other.index;
		outer_ptr = other.outer_ptr;
		return *this;
	  }

	  friend bool operator==(const FMIterator &first, const FMIterator &second) {
		return (first.index == second.index) && (first.outer_ptr == second.outer_ptr)
		  && (first.next_iterator == second.next_iterator);
	  }

	  friend bool operator!=(const FMIterator &first, const FMIterator &second) {
		return !(first == second);
	  }
	  
	  FirstDimensionMajorIterator &operator++() {
		if (next_iterator.at_end != true) {
		  ++ next_iterator;
		} else {
		  if (at_end != true) {
			++ index;
			if (index == DIM_T) {
			  at_end = true;
			} else {
			  next_iterator = outer_ptr->array[index].fmbegin();
			}
		  }
		}
		return *this;
	  }
	  
	  FirstDimensionMajorIterator operator++(int) {
		auto it = *this;
		if (next_iterator.at_end != true) {
		  ++ next_iterator;
		} else {
		  if (at_end != true) {
			++ index;
			if (index == DIM_T) {
			  at_end = true;
			} else {
			  next_iterator = outer_ptr->array[index].fmbegin();
			}
		  }
		}
		return it;	
	  }
	  
	  T &operator*() const {
		return *next_iterator;
	  }
	  
	};

	class LastDimensionMajorIterator {
	 private:
	  typedef typename NextArray::LastDimensionMajorIterator NextIterator;
	  friend class Array<T, DIM_T, Dims...>;
	  size_t index;
	  NextIterator next_iterator;
	  Array<T, DIM_T, Dims...> *outer_ptr;
	 public:
	  bool at_end;
	  LastDimensionMajorIterator(Array<T, DIM_T, Dims...> &outer_class) {
		at_end = false;
		index = DIM_T - 1;
		outer_ptr = &outer_class;
		next_iterator = outer_ptr->array[index].lmbegin();
	  }
	  
	  LastDimensionMajorIterator() {
		at_end = false;
		index = DIM_T - 1;
		outer_ptr = nullptr;
	  }
	  
	  LastDimensionMajorIterator(const FMIterator &other) {
		at_end = other.at_end;
		next_iterator = other.next_iterator;
		index = other.index;
		outer_ptr = other.outer_ptr;
	  }
	  
	  LastDimensionMajorIterator &operator=(const FMIterator &other) {
		at_end = other.at_end;
		next_iterator = other.next_iterator;
		index = other.index;
		outer_ptr = other.outer_ptr;
		return *this;
	  }

	  friend bool operator==(const LMIterator &first, const LMIterator &second) {
		return (first.index == second.index) && (first.outer_ptr == second.outer_ptr)
		  && (first.next_iterator == second.next_iterator);
	  }

	  friend bool operator!=(const LMIterator &first, const LMIterator &second) {
		return !(first == second);
	  }
	  
	  LastDimensionMajorIterator &operator++() {
		if (next_iterator.at_end != true) {
		  ++ next_iterator;
		} else {
		  if (at_end != true) {
			if (index == 0) {
			  at_end = true;
			} else {
			  -- index;
			  next_iterator = outer_ptr->array[index].lmbegin();
			}
		  }
		}
		return *this;
	  }
	  
	  LastDimensionMajorIterator operator++(int) {
		auto it = *this;
		if (next_iterator.at_end != true) {
		  ++ next_iterator;
		} else {
		  if (at_end != true) {
			if (index == 0) {
			  at_end = true;
			} else {
			  -- index;
			  next_iterator = outer_ptr->array[index].lmbegin();
			}
		  }
		}
		return it;	
	  }
	  
	  T &operator*() const {
		return *next_iterator;
	  }
	  
	};
	
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
	  return *this;
	}

	template <typename U>
	Array &operator=(const Array<U, Dims...> &other) {
	  for(size_t i = 0; i < DIM_T; ++ i) {
		array[i] = other.array[i];
	  }
	}
	
	Array<T, Dims...> &operator[](size_t index) {
	  if (index < 0 || index >= DIM_T) {
		throw OutOfRange("Index out of range!\n");
	  }
	  return array[index];
	}

	FMIterator fmbegin() {
	  return FMIterator(*this);
	}

	FMIterator fmend() {
	  return FMIterator(*this);
	}

	FMIterator lmbegin() {
	  return LMIterator(*this);
	}

	FMIterator lmend() {
	  return FMIterator(*this);
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
	 private:
	  friend class Array<T, DIM_T>;
	  Array<T, DIM_T> *outer_ptr;
	  size_t index;
	 public:
	  bool at_end;
	  FirstDimensionMajorIterator(Array<T, DIM_T> &outer_class) {
		at_end = false;
		index = 0;
		outer_ptr = &outer_class;
	  }
	  
	  FirstDimensionMajorIterator() {
		at_end = false;
		index = 0;
		outer_ptr = nullptr;
	  }

	  FirstDimensionMajorIterator(const FMIterator &other) {
		at_end = other.at_end;
		index = other.index;
		outer_ptr = other.outer_ptr;
	  }

	  FirstDimensionMajorIterator &operator=(const FMIterator &other) {
		at_end = other.at_end;
		index = other.index;
		outer_ptr = other.outer_ptr;
		return *this;
	  }

	  friend bool operator==(const FMIterator &first, const FMIterator &second) {
		return (first.index == second.index) && (first.outer_ptr == second.outer_ptr);
	  }

	  friend bool operator!=(const FMIterator &first, const FMIterator &second) {
		return !(first == second);
	  }

	  FirstDimensionMajorIterator &operator++() {
		if (at_end != true) {
		  ++ index;
		  if (index == DIM_T) {
			at_end = true;
		  }
		}
		return *this;
	  }

	  FirstDimensionMajorIterator operator++(int) {
		auto it = *this;
		if (at_end != true) {
		  ++ index;
		  if (index == DIM_T) {
			at_end = true;
		  }
		}
		return it;
	  }

	  T &operator*() const {
		return outer_ptr->array[index];
	  }
	};

	class LastDimensionMajorIterator {
	 private:
	  friend class Array<T, DIM_T>;
	  Array<T, DIM_T> *outer_ptr;
	  size_t index;
	 public:
	  bool at_end;
	  LastDimensionMajorIterator(Array<T, DIM_T> &outer_class) {
		at_end = false;
		index = DIM_T - 1;
		outer_ptr = &outer_class;
	  }
	  
	  LastDimensionMajorIterator() {
		at_end = false;
		index = DIM_T - 1;
		outer_ptr = nullptr;
	  }

	  LastDimensionMajorIterator(const FMIterator &other) {
		at_end = other.at_end;
		index = other.index;
		outer_ptr = other.outer_ptr;
	  }

	  LastDimensionMajorIterator &operator=(const FMIterator &other) {
		at_end = other.at_end;
		index = other.index;
		outer_ptr = other.outer_ptr;
		return *this;
	  }

	  friend bool operator==(const LMIterator &first, const LMIterator &second) {
		return (first.index == second.index) && (first.outer_ptr == second.outer_ptr);
	  }

	  friend bool operator!=(const LMIterator &first, const LMIterator &second) {
		return !(first == second);
	  }

	  LastDimensionMajorIterator &operator++() {
		if (at_end != true) {
		  -- index;
		  if (index == -1) {
			at_end = true;
		  }
		}
		return *this;
	  }

	  LastDimensionMajorIterator operator++(int) {
		auto it = *this;
		if (at_end != true) {
		  -- index;
		  if (index == -1) {
			at_end = true;
		  }
		}
		return it;
	  }

	  T &operator*() const {
		return outer_ptr->array[index];
	  }
	};
	
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
	  return *this;
	}

	template <typename U>
	Array &operator=(const Array<U, DIM_T> &other) {
	  for(size_t i = 0; i < DIM_T; ++ i) {
		array[i] = other.array[i];
	  }
	}
	
	T &operator[](size_t index) {
	  if (index < 0 || index >= DIM_T) {
		throw OutOfRange("Index out of range!\n");
	  }
	  return array[index];
	}
	
	FMIterator fmbegin() {
	  return FMIterator(*this);
	}

	FMIterator fmend() {
	  return FMIterator(*this);
	}
		
	FMIterator lmbegin() {
	  return LMIterator(*this);
	}

	FMIterator lmend() {
	  return LMIterator(*this);
	}
  };
}

#endif
