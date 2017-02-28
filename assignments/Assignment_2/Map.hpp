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
#include <stdexcept>

#ifndef CS440_MAP_HPP_
#define CS440_MAP_HPP_

namespace cs540 {
  template <typename Key_T, typename Mapped_T>
  class Map {
   public:
	class ReverseIterator;	
   private:
	/*
	  Private Node class
	 */
	class Node {
	 public:
	  // const Key_T key_;
	  // Mapped_T value_;
	  std::pair<const Key_T, Mapped_T> pair_val_;
	  std::vector<Node *> next_;
	  std::vector<Node *> prev_;
	  Node(Key_T key, Mapped_T value, size_t num_levels)
		: pair_val_(key, value), next_(num_levels + 1, nullptr),
		  prev_(num_levels + 1, nullptr){}
	  ~Node() {
		if (next_.size() != 0) {
		  delete next_[0];
		}
	  }
	};

	/*
	  Private methods for Map
	 */	
	size_t get_number_levels(double rand_dbl) {
	  size_t levels = 0;
	  while (rand_dbl < 0.5) {
		++ levels;
		rand_dbl = rand_dbl * 2;
	  }
	  return levels;
	}

	bool insert_node(Node *element, Node *current_element, size_t current_level) {
	  if (element->pair_val_.first == current_element->pair_val_.first) return false;
	  if (element->pair_val_.first < current_element->pair_val_.first) {
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
		  } else {
			end_.node_ = element;
		  }
		  current_element->next_[current_level] = element;
		} else {
		  if (!insert_node(element, current_element->next_[current_level], current_level)) {
			return false;
		  }
		}
	  }
	  return true;
	}

	Node *find_node(const Key_T &key, Node *current_element, size_t current_level) {
	  if (key == current_element->pair_val_.first) return current_element;
	  if (key < current_element->pair_val_.first) {
		// Searching element before current_element
		if (current_element == skip_list_[current_level]) {
		  // Searching at head
		  if (current_level != 0) {
			return find_node(key, skip_list_[current_level - 1], current_level - 1);
		  } else {
			return nullptr;
		  }
		} else {
		  // Searching not at head
		  if (current_level != 0) {
			return find_node(key, current_element->prev_[current_level], current_level - 1);
		  } else {
			return nullptr;
		  }
		}
	  } else {
		// Search element after current_element
		if (current_element->next_[current_level] == nullptr) {
		  // Next is null
		  if (current_level != 0) {
			return find_node(key, current_element, current_level - 1);
		  } else {
			return nullptr;
		  }
		} else {
		  return find_node(key, current_element->next_[current_level], current_level);
		}
	  }
	}
	
	void print_map() {
	  for (int i = skip_list_.size() - 1; i >=0 ; -- i) {
		std::cout << "Level: " << i << std::endl;
		Node *head = skip_list_[i];
		while (head != nullptr) {
		  std::cout << head->pair_val_.first << " ";
		  head = head->next_[i];
		}
		std::cout << std::endl;
	  }
	}

	/*
	  Private Data Members
	 */
	std::vector<Node*> skip_list_;
	size_t size_;
	std::random_device rand_dev_;
	std::mt19937_64 gen_;
	std::uniform_real_distribution<double> dist_;
	ReverseIterator end_;
   public:
	typedef std::pair<const Key_T, Mapped_T> ValueType;
	void print() {
	  print_map();
	}
	
	class Iterator {
	  friend class Map;
	  friend class ConstIterator;
	 private:
	  Node *node_;
	  Iterator() {
		node_ = nullptr;
	  }
	  Iterator(Node *other_node) {
		node_ = other_node;
	  }
	 public:
	  // Iterator(const Iterator &other); // Implicit should be ok
	  // ~Iterator(); // Implicit should be ok
	  // Iterator &operator=(const Iterator &other); // Implicit should be ok
	  Iterator &operator++() {
		node_ = node_->next_[0];
		return *this;
	  }
	  Iterator operator++(int) {
		Iterator it(*this);
		node_ = node_->next_[0];
		return it;
	  }
	  Iterator &operator--() {
		node_ = node_->prev_[0];
		return *this;
	  }
	  Iterator operator--(int) {
		Iterator it(*this);
		node_ = node_->prev_[0];
		return it;
	  }
	  ValueType &operator*() const {
		return node_->pair_val_;
	  }
	  ValueType *operator->() const {
		return &(node_->pair_val_);
	  }
	};

	class ConstIterator {
	  friend class Map;	  
	 private:
	  Node *node_;
	  ConstIterator() {
		node_ = nullptr;
	  }
	  ConstIterator(Node *other_node) {
		node_ = other_node;
	  }
	 public:
	  // ConstIterator(const ConstIterator &other); // Implicit should be ok
	  ConstIterator(const Iterator &other) {
		this->node_ = other.node_;
	  }
	  // ~ConstIterator(); // Implicit should be ok
	  // ConstIterator &operator=(const ConstIterator &other); // Implicit should be ok
	  ConstIterator &operator++() {
		node_ = node_->next_[0];
		return *this;
	  }
	  ConstIterator operator++(int) {
		ConstIterator it(*this);
		node_ = node_->next_[0];
		return it;
	  }
	  ConstIterator &operator--() {
		node_ = node_->prev_[0];
		return *this;		
	  }
	  ConstIterator operator--(int) {
		ConstIterator it(*this);
		node_ = node_->prev_[0];
		return it;		
	  }
	  const ValueType &operator*() const {
		return node_->pair_val_;
	  }
	  const ValueType *operator->() const {
		return &(node_->pair_val_);
	  }
	};

	class ReverseIterator {
	  friend class Map;
	 private:
	  Node *node_;
	  ReverseIterator() {
		node_ = nullptr;
	  }
	  ReverseIterator(Node *other_node) {
		node_ = other_node;
	  }
	 public:
	  // ReverseIterator(const ReverseIterator &other); // Implicit should be ok
	  // ~ReverseIterator(); // Implicit should be ok
	  // ReverseIterator &operator=(const ReverseIterator &other); // Implicit should be ok
	  ReverseIterator &operator++() {
		node_ = node_->prev_[0];
		return *this;
	  }
	  ReverseIterator operator++(int) {
		ReverseIterator it(*this);
		node_ = node_->next_[0];
		return it;
	  }
	  ReverseIterator &operator--() {
		node_ = node_->next_[0];
		return *this;		
	  }
	  ReverseIterator operator--(int) {
		ReverseIterator it(*this);
		node_ = node_->prev_[0];
		return it;		
	  }
	  ValueType &operator*() const {
		return node_->pair_val_;		
	  }
	  ValueType *operator->() const {
		return &(node_->pair_val_);
	  }
	};
	/*
	  Ctors, assignment, dtor
	 */
	Map() : skip_list_() , gen_(rand_dev_()), dist_(0.0, 1.0), end_() { size_ = 0; }
	Map(const Map &other) {
	  size_ = other.size_;
	}
	Map &operator=(const Map &other) {
	  skip_list_.clear();
	  size_ = other.size_;
	}
	Map(std::initializer_list<std::pair<const Key_T, Mapped_T>>);
	~Map() {
	  if(skip_list_.size() > 0)
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
	Iterator begin() {
	  if(skip_list_.size() > 0) return Iterator(skip_list_[0]);
	  else return Iterator();
	}
	Iterator end() {
	  return Iterator();
	}
	ConstIterator begin() const {
	  if(skip_list_.size() > 0) return ConstIterator(skip_list_[0]);
	  else return ConstIterator();	  
	}
	ConstIterator end() const {
	  return ConstIterator();
	}
	ReverseIterator rbegin() {
	  return end_;
	}
	ReverseIterator rend() {
	  return ReverseIterator();
	}
	/*
	  Element Access
	 */
	Iterator find(const Key_T &key) {
	  if (skip_list_.size() == 0) {
		return end();
	  } else {
		return Iterator(find_node(key, skip_list_.back(), skip_list_.size() - 1));
	  }
	}
	ConstIterator find(const Key_T &key) const {
	  if (skip_list_.size() == 0) {
		return end();
	  } else {
		return ConstIterator(find_node(key, skip_list_.back(), skip_list_.size() - 1));
	  }	  
	}
	Mapped_T &at(const Key_T &key) {
	  if (skip_list_.size() == 0) {
		throw std::out_of_range("Map is empty");
	  } else {
		Node *ptr = find_node(key, skip_list_.back(), skip_list_.size() - 1);
		if (ptr != nullptr) {
		  return ptr->pair_val_.second;
		} else {
		  throw std::out_of_range("Key not located in map");
		}
	  }
	}
	const Mapped_T &at(const Key_T &key) const {
	  if (skip_list_.size() == 0) {
		throw std::out_of_range("Map is empty");
	  } else {
		Node *ptr = find_node(key, skip_list_.back(), skip_list_.size() - 1);
		if (ptr != nullptr) {
		  return ptr->pair_val_.second;
		} else {
		  throw std::out_of_range("Key not located in map");
		}
	  }	  
	}
	Mapped_T &operator[](const Key_T &key) {
	  bool need_to_insert = false;
	  if (skip_list_.size() == 0) {
		need_to_insert = true;
	  }
	  Node *ptr = find_node(key, skip_list_.back(), skip_list_.size() - 1);
	  if (ptr == nullptr) {
		need_to_insert = true;
	  } else {
		return ptr->pair_val_.second;
	  }
	  if (need_to_insert) {
		ValueType to_insert(key, Mapped_T());
		std::pair<Iterator, bool> result = insert(to_insert);
		return result.first.node_->pair_val_.second;
	  }
	}
	/*
	  Modifier
	 */
	std::pair<Iterator, bool> insert(const ValueType &value) {
	// bool insert(const ValueType &value) {
	  ++ size_;
	  double rand_dbl = dist_(gen_);
	  size_t num_levels = get_number_levels(rand_dbl);
	  // std::cout << "Rand_dbl: " << rand_dbl << std::endl;
	  // std::cout << "num_levels: " << num_levels << std::endl;
	  Node *element = new Node(value.first, value.second, num_levels);
	  if (skip_list_.size() == 0) {
		// Initial inserts
		while (skip_list_.size() < num_levels + 1) {
		  skip_list_.push_back(element);
		}
		end_.node_ = element;
	  } else {
		size_t min_index = std::min((size_t)skip_list_.size() - 1, num_levels);
		// std::cout << "Min_index: " << min_index << std::endl;
		if (!insert_node(element, skip_list_[min_index], min_index)) {
		  return std::make_pair(Iterator((Node *)nullptr), false);
		}
		while (skip_list_.size() < num_levels + 1) {
		  skip_list_.push_back(element);
		}		
	  }
	  return std::make_pair(Iterator(element), true);
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
