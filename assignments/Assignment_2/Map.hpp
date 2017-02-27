#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <utility>
#include <initializer_list>
#include <vector>
#include <array>
#include <random>

#ifndef CS440_MAP_HPP_
#define CS440_MAP_HPP_

namespace cs540 {
  template <typename Key_T, typename Mapped_T>
  class Map {
   private:

	class Node {
	 public:
	  Key_T key_;
	  Mapped_T value_;	  
	  std::vector<Node *> next_;
	  std::vector<Node *> prev_;
	  Node(Key_T key, Mapped_T value) : key_(key), value_(value), next_(), prev_() { };
	  ~Node() {
		if (next_.size() != 0) {
		  delete next_[0];
		}
	  }
	};
	
	int get_number_levels(double rand_dbl) {
	  int levels = 0;
	  while (rand_dbl < 0.5) {
		++ levels;
		rand_dbl = rand_dbl * 2;
	  }
	  return levels;
	};

	void insert(Node *element, int current_level) {
	  
	};
	
	std::vector<Node*> skip_list_;
	size_t size_;
	std::random_device rand_dev_;
	std::mt19937_64 gen_;
	std::uniform_real_distribution<double> dist_;
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
	Map() : skip_list_() , gen_(rand_dev_()), dist_(0.0, 1.0) { size_ = 0; };
	Map(const Map &other) {
	  size_ = other.size_;
	}
	Map &operator=(const Map &other) {
	  skip_list_.clear();
	  size_ = other.size_;
	}
	Map(std::initializer_list<std::pair<const Key_T, Mapped_T>>);
	~Map();
	/*
	  Size
	 */	
	size_t size() const { return size_; }
	bool empty() const { return size() == 0; }
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
	std::pair<Iterator, bool> insert(const ValueType &value) {
	  Node *element = new Node(value.first, value.second);
	  double rand_dbl = dist_(gen_);
	  int num_levels = get_number_levels(rand_dbl);
	  insert(element, skip_list_.size() - 1);
	  while (skip_list_.size() < num_levels + 1) {
		skip_list_.push_back(element);
	  }
	}
	
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
bool operator==(const cs540::Map<Key_T, Mapped_T> &first,
                const cs540::Map<Key_T, Mapped_T> &second);
template <typename Key_T, typename Mapped_T>
bool operator!=(const cs540::Map<Key_T, Mapped_T> &first,
                const cs540::Map<Key_T, Mapped_T> &second);
template <typename Key_T, typename Mapped_T>
bool operator<(const cs540::Map<Key_T, Mapped_T> &first,
               const cs540::Map<Key_T, Mapped_T> &second);

template <typename Key_T, typename Mapped_T>
bool operator==(const typename cs540::Map<Key_T, Mapped_T>::Iterator &first,
                const typename cs540::Map<Key_T, Mapped_T>::Iterator &second);
template <typename Key_T, typename Mapped_T>
bool operator==(
    const typename cs540::Map<Key_T, Mapped_T>::ConstIterator &first,
    const typename cs540::Map<Key_T, Mapped_T>::ConstIterator &second);
template <typename Key_T, typename Mapped_T>
bool operator==(
    const typename cs540::Map<Key_T, Mapped_T>::Iterator &first,
    const typename cs540::Map<Key_T, Mapped_T>::ConstIterator &second);
template <typename Key_T, typename Mapped_T>
bool operator==(
    const typename cs540::Map<Key_T, Mapped_T>::ConstIterator &first,
    const typename cs540::Map<Key_T, Mapped_T>::Iterator &second);
template <typename Key_T, typename Mapped_T>
bool operator!=(const typename cs540::Map<Key_T, Mapped_T>::Iterator &first,
                const typename cs540::Map<Key_T, Mapped_T>::Iterator &second);
template <typename Key_T, typename Mapped_T>
bool operator!=(
    const typename cs540::Map<Key_T, Mapped_T>::ConstIterator &first,
    const typename cs540::Map<Key_T, Mapped_T>::ConstIterator &second);
template <typename Key_T, typename Mapped_T>
bool operator!=(
    const typename cs540::Map<Key_T, Mapped_T>::Iterator &first,
    const typename cs540::Map<Key_T, Mapped_T>::ConstIterator &second);
template <typename Key_T, typename Mapped_T>
bool operator!=(
    const typename cs540::Map<Key_T, Mapped_T>::ConstIterator &first,
    const typename cs540::Map<Key_T, Mapped_T>::Iterator &second);
template <typename Key_T, typename Mapped_T>
bool operator==(
    const typename cs540::Map<Key_T, Mapped_T>::ReverseIterator &first,
    const typename cs540::Map<Key_T, Mapped_T>::ReverseIterator &second);
template <typename Key_T, typename Mapped_T>
bool operator!=(
    const typename cs540::Map<Key_T, Mapped_T>::ReverseIterator &first,
    const typename cs540::Map<Key_T, Mapped_T>::ReverseIterator &second);

#endif
