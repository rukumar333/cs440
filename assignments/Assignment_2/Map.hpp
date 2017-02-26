#include <iostream>
#include <string>
#include <cassert>
#include <utility>
#include <initializer_list>
#include <cstdlib>

#ifndef CS350_MAP_HPP_
#define CS350_MAP_HPP_

namespace cs540 {
  template <typename Key_T, typename Mapped_T>
  class Map {
   private:
  
   public:
	typedef std::pair<const Key_T, Mapped_T> ValueType;
	class Iterator {
	 private:
	  
	 public:
	  Iterator(const Iterator &other); // Implicit should be ok
	  ~Iterator(); // Implicit should be ok
	  Iterator &operator=(const Iterator &other); // Implicit should be ok
	  Iterator &operator++();
	  Iterator operator++(int);
	  Iterator &operator--();
	  Iterator operator--(int);
	  ValueType &operator*() const;
	  ValueType *operator->() const;
	};

	class ConstIterator {
	 private:

	 public:
	  ConstIterator(const ConstIterator &other); // Implicit should be ok
	  ConstIterator(const Iterator &other);
	  ~ConstIterator(); // Implicit should be ok
	  ConstIterator &operator=(const ConstIterator &other); // Implicit should be ok
	  ConstIterator &operator++();
	  ConstIterator operator++(int);
	  ConstIterator &operator--();
	  ConstIterator operator--(int);
	  const ValueType &operator*() const;
	  const ValueType *operator->() const;	
	};

	class ReverseIterator {
	 private:

	 public:
	  ReverseIterator(const ReverseIterator &other); // Implicit should be ok
	  ~ReverseIterator(); // Implicit should be ok
	  ReverseIterator &operator=(const ReverseIterator &other); // Implicit should be ok
	  ReverseIterator &operator++();
	  ReverseIterator operator++(int);
	  ReverseIterator &operator--();
	  ReverseIterator operator--(int);
	  ValueType &operator*() const;
	  ValueType *operator->() const;	
	};
	/*
	  Ctors, assignment, dtor
	 */
	Map();
	Map(const Map &other);
	Map &operator=(const Map &other);
	Map(std::initializer_list<std::pair<const Key_T, Mapped_T>>);
	~Map();
	/*
	  Size
	 */	
	size_t size() const;
	bool empty() const;
	/*
	  Iterator
	 */
	Iterator begin();
	Iterator end();
	ConstIterator begin() const;
	ConstIterator end() const;
	ReverseIterator rbegin();
	ReverseIterator rend();
	/*
	  Element Access
	 */
	Iterator find(const Key_T &key);
	ConstIterator find(const Key_T &key) const;
	Mapped_T &at(const Key_T &key);
	const Mapped_T &at(const Key_T &key) const;
	// Mapped_T &operator(const Key_T &key);
	/*
	  Modifier
	 */
	std::pair<Iterator, bool> insert(const ValueType &value);

	template <typename IT_T>
	void insert(IT_T range_beg, IT_T range_end);
	void erase(Iterator pos);
	void erase(const Key_T &key);
	void clear();
	/*
	  Comparison
	*/
  };
}

template <typename Key_T, typename Mapped_T>
bool operator==(const cs540::Map<Key_T, Mapped_T> &first, const cs540::Map<Key_T, Mapped_T> &second);
template <typename Key_T, typename Mapped_T>
bool operator!=(const cs540::Map<Key_T, Mapped_T> &first, const cs540::Map<Key_T, Mapped_T> &second);
template <typename Key_T, typename Mapped_T>
bool operator<(const cs540::Map<Key_T, Mapped_T> &first, const cs540::Map<Key_T, Mapped_T> &second);

template <typename Key_T, typename Mapped_T>
bool operator==(const typename cs540::Map<Key_T, Mapped_T>::Iterator &first,
                const typename cs540::Map<Key_T, Mapped_T>::Iterator &second);
template <typename Key_T, typename Mapped_T>
bool operator==(const typename cs540::Map<Key_T, Mapped_T>::ConstIterator &first,
				const typename cs540::Map<Key_T, Mapped_T>::ConstIterator &second);
template <typename Key_T, typename Mapped_T>
bool operator==(const typename cs540::Map<Key_T, Mapped_T>::Iterator &first,
				const typename cs540::Map<Key_T, Mapped_T>::ConstIterator &second);
template <typename Key_T, typename Mapped_T>
bool operator==(const typename cs540::Map<Key_T, Mapped_T>::ConstIterator &first,
				const typename cs540::Map<Key_T, Mapped_T>::Iterator &second);
template <typename Key_T, typename Mapped_T>
bool operator!=(const typename cs540::Map<Key_T, Mapped_T>::Iterator &first,
                const typename cs540::Map<Key_T, Mapped_T>::Iterator &second);
template <typename Key_T, typename Mapped_T>
bool operator!=(const typename cs540::Map<Key_T, Mapped_T>::ConstIterator &first,
				const typename cs540::Map<Key_T, Mapped_T>::ConstIterator &second);
template <typename Key_T, typename Mapped_T>
bool operator!=(const typename cs540::Map<Key_T, Mapped_T>::Iterator &first,
				const typename cs540::Map<Key_T, Mapped_T>::ConstIterator &second);
template <typename Key_T, typename Mapped_T>
bool operator!=(const typename cs540::Map<Key_T, Mapped_T>::ConstIterator &first,
				const typename cs540::Map<Key_T, Mapped_T>::Iterator &second);
template <typename Key_T, typename Mapped_T>
bool operator==(const typename cs540::Map<Key_T, Mapped_T>::ReverseIterator &first,
				const typename cs540::Map<Key_T, Mapped_T>::ReverseIterator &second);
template <typename Key_T, typename Mapped_T>
bool operator!=(const typename cs540::Map<Key_T, Mapped_T>::ReverseIterator &first,
				const typename cs540::Map<Key_T, Mapped_T>::ReverseIterator &second);

#endif
