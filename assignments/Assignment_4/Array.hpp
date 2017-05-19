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
	  NextIterator next_iterator;
	  Array<T, DIM_T, Dims...> *outer_ptr;
	 public:
	  bool at_end;
	  size_t index;
	  FirstDimensionMajorIterator(Array<T, DIM_T, Dims...> &outer_class, bool end) {
		outer_ptr = &outer_class;
		if (!end) {
		  at_end = false;
		  index = 0;
		} else {
		  at_end = true;
		  index = DIM_T;
		}
		if (!end) {
		  next_iterator = outer_ptr->array[index].fmbegin(); 
		} else {
		  next_iterator = outer_ptr->array[index].fmend();
		}
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
		if (this == &other)
		  return *this;
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
	 public:
	  size_t index;
	  NextIterator next_iterators[DIM_T];
	  Array<T, DIM_T, Dims...> *outer_ptr;
	  bool at_end;
	  LastDimensionMajorIterator(Array<T, DIM_T, Dims...> &outer_class, bool end) {
		if (!end) {
		  at_end = false;
		  index = 0;
		} else {
		  at_end = true;
		  index = DIM_T;
		}
		outer_ptr = &outer_class;
		if (!end) {
		  for (unsigned int i = 0; i < DIM_T; ++ i) {
			next_iterators[i] = outer_ptr->array[i].lmbegin();
		  }
		} else {
		  for (unsigned int i = 0; i < DIM_T; ++ i) {
			next_iterators[i] = outer_ptr->array[i].lmend();
		  }
		}
	  }
	  
	  LastDimensionMajorIterator() {
		at_end = false;
		index = 0;
		outer_ptr = nullptr;
	  }
	  
	  LastDimensionMajorIterator(const LMIterator &other) {
		at_end = other.at_end;
		index = other.index;
		outer_ptr = other.outer_ptr;
		for (unsigned int i = 0; i < DIM_T; ++ i) {
		  next_iterators[i] = other.next_iterators[i];
		}
	  }
	  
	  LastDimensionMajorIterator &operator=(const LMIterator &other) {
		if (this == &other)
		  return *this;
		at_end = other.at_end;
		index = other.index;
		outer_ptr = other.outer_ptr;
		for (unsigned int i = 0; i < DIM_T; ++ i) {
		  next_iterators[i] = other.next_iterators[i];
		}
		return *this;
	  }

	  friend bool operator==(const LMIterator &first, const LMIterator &second) {
		if (first.index == second.index && first.outer_ptr == second.outer_ptr) {
		  for (unsigned int i = 0; i < DIM_T; ++ i) {
			if (first.next_iterators[i] != second.next_iterators[i])
			  return false;
		  }
		  return true;
		}
		return false;
	  }

	  friend bool operator!=(const LMIterator &first, const LMIterator &second) {
		return !(first == second);
	  }
	  
	  LastDimensionMajorIterator &operator++() {
		// if (next_iterators[index].at_end != true) {
		//   ++ (next_iterators[index]);
		//   ++ index;
		//   index = index % DIM_T;
		// } else {
		//   if (at_end != true) {
			
		//   }
		// }
		if (at_end != true) {
		  ++ (next_iterators[index]);
		  ++ index;
		  index = index % DIM_T;
		  if (next_iterators[index].at_end == true) {
			at_end = true;
		  }
		}
		return *this;
	  }
	  
	  LastDimensionMajorIterator operator++(int) {
		auto it = *this;
		if (at_end != true) {
		  ++ (next_iterators[index]);
		  ++ index;
		  index = index % DIM_T;
		  if (next_iterators[index].at_end == true) {
			at_end = true;
		  }
		}
		return it;	
	  }
	  
	  T &operator*() const {
		return *(next_iterators[index]);
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
	  return FMIterator(*this, false);
	}

	FMIterator fmend() {
	  return FMIterator(*this, true);
	  
	}

	LMIterator lmbegin() {
	  return LMIterator(*this, false);
	}

	LMIterator lmend() {
	  return LMIterator(*this, true);
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
	 public:
	  friend class Array<T, DIM_T>;
	  Array<T, DIM_T> *outer_ptr;
	  size_t index;
	  bool at_end;
	  FirstDimensionMajorIterator(Array<T, DIM_T> &outer_class, bool end) {
		if (!end) {
		  at_end = false;
		  index = 0;
		} else {
		  at_end = true;
		  index = DIM_T;
		}
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
		if (this == &other)
		  return *this; 
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
	 public:
	  friend class Array<T, DIM_T>;
	  Array<T, DIM_T> *outer_ptr;
	  size_t index;
	  bool at_end;
	  LastDimensionMajorIterator(Array<T, DIM_T> &outer_class, bool end) {
		if (!end) {
		  at_end = false;
		  index = 0;
		} else {
		  at_end = true;
		  index = DIM_T;
		}
		outer_ptr = &outer_class;
	  }
	  
	  LastDimensionMajorIterator() {
		at_end = false;
		index = 0;
		outer_ptr = nullptr;
	  }

	  LastDimensionMajorIterator(const LMIterator &other) {
		at_end = other.at_end;
		index = other.index;
		outer_ptr = other.outer_ptr;
	  }

	  LastDimensionMajorIterator &operator=(const LMIterator &other) {
		if (this == &other)
		  return *this; 
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
		  ++ index;
		  if (index == DIM_T) {
			at_end = true;
		  }
		}
		return *this;
	  }

	  LastDimensionMajorIterator operator++(int) {
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

	// class LastDimensionMajorIterator {
	//  private:
	//   friend class Array<T, DIM_T>;
	//   Array<T, DIM_T> *outer_ptr;
	//   size_t index;
	//  public:
	//   bool at_end;
	//   LastDimensionMajorIterator(Array<T, DIM_T> &outer_class, bool end) {
	// 	if (!end) {
	// 	  at_end = false;
	// 	  index = DIM_T - 1;		  
	// 	} else {
	// 	  at_end = true;
	// 	  index = 0;
	// 	}
	// 	outer_ptr = &outer_class;
	//   }
	  
	//   LastDimensionMajorIterator() {
	// 	at_end = false;
	// 	index = DIM_T - 1;
	// 	outer_ptr = nullptr;
	//   }

	//   LastDimensionMajorIterator(const LMIterator &other) {
	// 	at_end = other.at_end;
	// 	index = other.index;
	// 	outer_ptr = other.outer_ptr;
	//   }

	//   LastDimensionMajorIterator &operator=(const LMIterator &other) {
	// 	if (this == &other)
	// 	  return *this;
	// 	at_end = other.at_end;
	// 	index = other.index;
	// 	outer_ptr = other.outer_ptr;
	// 	return *this;
	//   }

	//   friend bool operator==(const LMIterator &first, const LMIterator &second) {
	// 	return (first.index == second.index) && (first.outer_ptr == second.outer_ptr);
	//   }

	//   friend bool operator!=(const LMIterator &first, const LMIterator &second) {
	// 	return !(first == second);
	//   }

	//   LastDimensionMajorIterator &operator++() {
	// 	if (at_end != true) {
	// 	  if (index == 0) {
	// 		at_end = true;
	// 	  } else {
	// 		-- index;	
	// 	  }
	// 	}
	// 	return *this;
	//   }

	//   LastDimensionMajorIterator operator++(int) {
	// 	auto it = *this;
	// 	if (at_end != true) {
	// 	  if (index == 0) {
	// 		at_end = true;
	// 	  } else {
	// 		-- index;	
	// 	  }
	// 	}
	// 	return it;
	//   }

	//   T &operator*() const {
	// 	return outer_ptr->array[index];
	//   }
	// };
	
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
	  return FMIterator(*this, false);
	}

	FMIterator fmend() {
	  return FMIterator(*this, true);
	}
		
	LMIterator lmbegin() {
	  return LMIterator(*this, false);
	}

	LMIterator lmend() {
	  return LMIterator(*this, true);
	}
  };
}

#endif
