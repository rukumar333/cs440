#include <cassert>
#include <cstdlib>
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
	class Iterator;
	class ConstIterator;
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

	bool insert_node(Node *element, Node *current_element, size_t current_level);
	
	Node *find_node(const Key_T &key) {
	  return find_node(key, skip_list_.back(), skip_list_.size() - 1);
	}
	Node *find_node(const Key_T &key, Node *current_element, size_t current_level);
	
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

	class Iterator : public ConstIterator{
	  friend class Map;
	  friend class ConstIterator;
	 private:
	  Iterator() {
	  	this->node_ = nullptr;
	  }
	  Iterator(Node *other_node) {
	  	this->node_ = other_node;
	  }
	 public:
	  ValueType &operator*() const {
		return this->node_->pair_val_;
	  }
	  ValueType *operator->() const {
		return &(this->node_->pair_val_);
	  }
	};

	class ConstIterator{
	  friend class Map;
	  friend class Iterator;
	 protected:
	  Node *node_;
	  ConstIterator() {
	  	node_ = nullptr;
	  }
	  ConstIterator(Node *other_node) {
	  	node_ = other_node;
	  }
	 public:
	  ConstIterator(const Iterator &other) {
	  	this->node_ = other.node_;
	  }
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
	  friend bool operator==(const ConstIterator first, const ConstIterator second) {
		return first.node_ == second.node_;
	  }
	  friend bool operator!=(const ConstIterator first, const ConstIterator second) {
		return first.node_ != second.node_;
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
	  friend bool operator==(const ReverseIterator first, const ReverseIterator second) {
		return first.node_ == second.node_;
	  }
	  friend bool operator!=(const ReverseIterator first, const ReverseIterator second) {
		return first.node_ != second.node_;
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
		return Iterator(find_node(key));
	  }
	}
	ConstIterator find(const Key_T &key) const {
	  if (skip_list_.size() == 0) {
		return end();
	  } else {
		return ConstIterator(find_node(key));
	  }	  
	}
	Mapped_T &at(const Key_T &key) {
	  if (skip_list_.size() == 0) {
		throw std::out_of_range("Map is empty");
	  } else {
		Node *ptr = find_node(key);
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
		Node *ptr = find_node(key);
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
	  Node *ptr = find_node(key);
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
	  ++ size_;
	  return std::make_pair(Iterator(element), true);
	}
	
	template <typename IT_T>
	void insert(IT_T range_beg, IT_T range_end) {
	  while (range_beg != range_end) {
		insert(ValueType(*range_beg));
		++ range_beg;
	  }
	}
	void erase(Iterator pos) {
	  if (pos.node_ != nullptr) {
	  	Node *node = pos.node_;
	  	for(unsigned int i = 0; i < node->prev_.size(); ++ i){
	  	  if (node->next_[i] != nullptr) {
	  	  	// Next is not null
	  	  	if (node->prev_[i] != nullptr) {
	  	  	  // Prev is not null
			  // std::cout << "Case 1" << std::endl;
	  	  	  node->prev_[i]->next_[i] = node->next_[i];
			  node->next_[i]->prev_[i] = node->prev_[i];
	  	  	} else {
	  	  	  // Prev is null
			  // std::cout << "Case 2" << std::endl;
			  skip_list_[i] = node->next_[i];
			  node->next_[i]->prev_[i] = nullptr;
	  	  	}
	  	  } else {
	  	  	// Next is null
	  	  	if (node->prev_[i] != nullptr) {
	  	  	  // Prev is not null
			  // std::cout << "Case 3" << std::endl;
			  node->prev_[i]->next_[i] = nullptr;
	  	  	} else {
	  	  	  // Prev is null
			  // std::cout << "Case 4" << std::endl;
			  skip_list_.pop_back();
			  // skip_list_[i] = nullptr;
	  	  	}
	  	  }
	  	}
		node->prev_.clear();
		node->next_.clear();
		delete node;
	  }
	}
	void erase(const Key_T &key) {
	  Node *ptr = find_node(key);
	  if (ptr == nullptr) {
		throw std::out_of_range("Key not located in map");
	  } else {
		erase(Iterator(ptr));
	  }
	}
	void clear() {
	  if (skip_list_.size() != 0) {
		delete skip_list_[0];
		skip_list_.clear();
		size_ = 0;
		end_.node_ = nullptr;
	  }
	}
	/*
	  Comparison
	*/
  };
}

// template <typename Key_T, typename Mapped_T>
// bool operator==(const cs540::Map<Key_T, Mapped_T> &first,
//                 const cs540::Map<Key_T, Mapped_T> &second);
// template <typename Key_T, typename Mapped_T>
// bool operator!=(const cs540::Map<Key_T, Mapped_T> &first,
//                 const cs540::Map<Key_T, Mapped_T> &second);
// template <typename Key_T, typename Mapped_T>
// bool operator<(const cs540::Map<Key_T, Mapped_T> &first,
//                const cs540::Map<Key_T, Mapped_T> &second);

// template <typename Key_T, typename Mapped_T>
// bool operator==(const typename cs540::Map<Key_T, Mapped_T>::Iterator first,
//                 const typename cs540::Map<Key_T, Mapped_T>::Iterator second) {
//   return first->node_ == second->node_;
//   // return true;
// }

// template <typename Key_T, typename Mapped_T>
// bool operator==(
//     const typename cs540::Map<Key_T, Mapped_T>::ConstIterator &first,
//     const typename cs540::Map<Key_T, Mapped_T>::ConstIterator &second);
// template <typename Key_T, typename Mapped_T>
// bool operator==(
//     const typename cs540::Map<Key_T, Mapped_T>::Iterator &first,
//     const typename cs540::Map<Key_T, Mapped_T>::ConstIterator &second);
// template <typename Key_T, typename Mapped_T>
// bool operator==(
//     const typename cs540::Map<Key_T, Mapped_T>::ConstIterator &first,
//     const typename cs540::Map<Key_T, Mapped_T>::Iterator &second);

// template <typename Key_T, typename Mapped_T>
// bool operator!=(const typename cs540::Map<Key_T, Mapped_T>::Iterator &first,
//                 const typename cs540::Map<Key_T, Mapped_T>::Iterator &second) {
//   return !(first == second);
// }

// template <typename Key_T, typename Mapped_T>
// bool operator!=(
//     const typename cs540::Map<Key_T, Mapped_T>::ConstIterator &first,
//     const typename cs540::Map<Key_T, Mapped_T>::ConstIterator &second);
// template <typename Key_T, typename Mapped_T>
// bool operator!=(
//     const typename cs540::Map<Key_T, Mapped_T>::Iterator &first,
//     const typename cs540::Map<Key_T, Mapped_T>::ConstIterator &second);
// template <typename Key_T, typename Mapped_T>
// bool operator!=(
//     const typename cs540::Map<Key_T, Mapped_T>::ConstIterator &first,
//     const typename cs540::Map<Key_T, Mapped_T>::Iterator &second);
// template <typename Key_T, typename Mapped_T>
// bool operator==(
//     const typename cs540::Map<Key_T, Mapped_T>::ReverseIterator &first,
//     const typename cs540::Map<Key_T, Mapped_T>::ReverseIterator &second);
// template <typename Key_T, typename Mapped_T>
// bool operator!=(
//     const typename cs540::Map<Key_T, Mapped_T>::ReverseIterator &first,
//     const typename cs540::Map<Key_T, Mapped_T>::ReverseIterator &second);

template <typename Key_T, typename Mapped_T>
bool cs540::Map<Key_T, Mapped_T>::insert_node(
    cs540::Map<Key_T, Mapped_T>::Node *element,
    cs540::Map<Key_T, Mapped_T>::Node *current_element, size_t current_level) {
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
	  element->prev_[current_level] = current_element;
	} else {
	  if (!insert_node(element, current_element->next_[current_level], current_level)) {
		return false;
	  }
	}
  }
  return true;
}

template <typename Key_T, typename Mapped_T>
typename cs540::Map<Key_T, Mapped_T>::Node* cs540::Map<Key_T, Mapped_T>::find_node(
    const Key_T &key, cs540::Map<Key_T, Mapped_T>::Node *current_element,
    size_t current_level) {
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

#endif
