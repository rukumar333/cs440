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
#include <algorithm>

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
	  Node(Key_T key, Mapped_T value, size_t num_levels)
		: key_(key), value_(value), next_(num_levels + 1, nullptr),
		  prev_(num_levels + 1, nullptr){};
	  ~Node() {
		if (next_.size() != 0) {
		  delete next_[0];
		}
	  }
	};
	
	size_t get_number_levels(double rand_dbl) {
	  size_t levels = 0;
	  while (rand_dbl < 0.5) {
		++ levels;
		rand_dbl = rand_dbl * 2;
	  }
	  return levels;
	};

	bool insert_node(Node *element, Node *current_element, int current_level) {
	  if (element->key_ == current_element->key_) return false;
	  if (element->key_ < current_element->key_) {
		// Insert_Node element before current_element
		if (current_element == skip_list_[current_level]) {
		  // Insert_Nodeing at head
		  if (current_level != 0) {
			if (!insert_node(element, skip_list_[current_level - 1], current_level - 1)) {
			  return false;
			}
		  }
		  element->next_[current_level] = current_element;
		  current_element->prev_[current_level] = element;
		  assert(element->next_[current_level]->prev_[current_level] == element);
		  skip_list_[current_level] = element;
		} else {
		  // Insert_Nodeing not at head
		  if (current_level != 0) {
			if (!insert_node(element, current_element->prev_[current_level], current_level - 1)) {
			  return false;
			}
		  }
		  element->next_[current_level] = current_element;
		  element->prev_[current_level] = current_element->prev_[current_level];
		  current_element->prev_[current_level]->next_[current_level] = element;
		  current_element->prev_[current_level] = element;
		  assert(element->next_[current_level]->prev_[current_level] == element);
		  assert(element->prev_[current_level]->next_[current_level] == element);
		}
	  } else {
		// Insert_Node element after current_element
		if (current_element->next_[current_level] == nullptr) {
		  // Next is null
		  if (current_level != 0) {
			if (!insert_node(element, current_element, current_level - 1)) {
			  return false;
			}
		  }
		  current_element->next_[current_level] = element;
		} else {
		  if (!insert_node(element, current_element->next_[current_level], current_level)) {
			return false;
		  }
		}
	  }
	  return true;
	};

	void print_map() {
	  for (int i = skip_list_.size() - 1; i >=0 ; -- i) {
		std::cout << "Level: " << i << std::endl;
		Node *head = skip_list_[i];
		while (head != nullptr) {
		  std::cout << head->key_ << " ";
		  head = head->next_[i];
		}
		std::cout << std::endl;
	  }
	}
	
	std::vector<Node*> skip_list_;
	size_t size_;
	std::random_device rand_dev_;
	std::mt19937_64 gen_;
	std::uniform_real_distribution<double> dist_;
   public:
	typedef std::pair<const Key_T, Mapped_T> ValueType;
	void print() {
	  print_map();
	}
	class Iterator {
	 private:
	  Node *node_;
	  Iterator() {
		*node_ = nullptr;
	  }
	  Iterator(Node *other_node) {
		node_ = other_node;
	  }
	 public:
	  Iterator(const Iterator &other); // Implicit should be ok
	  ~Iterator(); // Implicit should be ok
	  Iterator &operator=(const Iterator &other); // Implicit should be ok
	  Iterator &operator++() {
		node_ = node_->next_[0];
		return *this;
	  };
	  Iterator operator++(int) {
		Iterator it(*this);
		node_ = node_->next_[0];
		return it;
	  };
	  Iterator &operator--() {
		node_ = node_->prev_[0];
		return *this;
	  };
	  Iterator operator--(int) {
		Iterator it(*this);
		node_ = node_->prev_[0];
		return it;
	  };
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
	~Map() {
	  delete skip_list_[0];
	}
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
	// std::pair<Iterator, bool> insert(const ValueType &value) {
	bool insert(const ValueType &value) {
	  ++ size_;
	  double rand_dbl = dist_(gen_);
	  size_t num_levels = get_number_levels(rand_dbl);
	  std::cout << "Rand_dbl: " << rand_dbl << std::endl;
	  std::cout << "num_levels: " << num_levels << std::endl;
	  Node *element = new Node(value.first, value.second, num_levels);
	  if (skip_list_.size() == 0) {
		// Initial inserts
		while (skip_list_.size() < num_levels + 1) {
		  skip_list_.push_back(element);
		}		
	  } else {
		size_t min_index = std::min((size_t)skip_list_.size() - 1, num_levels);
		std::cout << "Min_index: " << min_index << std::endl;
		if (!insert_node(element, skip_list_[min_index], min_index)) {
		  return false;
		}
		while (skip_list_.size() < num_levels + 1) {
		  skip_list_.push_back(element);
		}		
	  }
	  return true;
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
