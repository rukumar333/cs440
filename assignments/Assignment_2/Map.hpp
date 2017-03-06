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
	class SNode {
	 public:
	  std::vector<SNode *> next_;
	  std::vector<SNode *> prev_;
	  SNode(size_t num_levels)
			: next_(num_levels + 1, nullptr), prev_(num_levels + 1, nullptr) { }
	  SNode() { }
	  ~SNode() {
		if (next_.size() != 0 && next_[0] != nullptr) {
		  delete next_[0];
		}
	  }
	};
	
	/*
	  Private Node class
	 */
	class Node : public SNode {
	 public:
	  // const Key_T key_;
	  // Mapped_T value_;
	  std::pair<const Key_T, Mapped_T> pair_val_;
	  // std::vector<Node *> next_;
	  // std::vector<Node *> prev_;
	  // Node(Key_T key, Mapped_T value, size_t num_levels)
	  // 	: pair_val_(key, value), next_(num_levels + 1, nullptr),
	  // 	  prev_(num_levels + 1, nullptr){}
	  Node(Key_T key, Mapped_T value, size_t num_levels)
	  	: SNode(num_levels), pair_val_(key, value){}
	  // ~Node() {
	  // 	if (this->next_.size() != 0) {
	  // 	  delete this->next_[0];
	  // 	}
	  // }
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

	bool insert_node(Node *element, size_t current_level);
	
	SNode *find_node(const Key_T &key) {
	  SNode *current_element = begin_sent_->next_.back();
	  int current_level = begin_sent_->next_.size() - 1;
	  // return find_node(key, begin_sent_->next_.back(), begin_sent_->next_.size() - 1);
	  while (current_element != nullptr) {
		if (current_element == end_sent_) {
		  if (current_level == 0) {
			return end_sent_;
		  } else {
			current_element = current_element->prev_[current_level]->next_[current_level - 1];
			-- current_level;
		  }
		} else {
		  Key_T current_key = static_cast<Node *>(current_element)->pair_val_.first;
		  if (key == current_key) return current_element;
		  if (key < current_key) {
			if (current_level == 0) {
			  return end_sent_;
			} else {
			  current_element = current_element->prev_[current_level]->next_[current_level - 1];
			  -- current_level;
			}
		  } else {
			current_element = current_element->next_[current_level];		
		  } 
		}
	  }
	  return end_sent_;
	}
	// SNode *find_node(const Key_T &key, SNode *current_element, size_t current_level);
	
	void print_map() {
	  for (int i = begin_sent_->next_.size() - 1; i >=0 ; -- i) {
		std::cout << "Level: " << i << std::endl;
		SNode *head = begin_sent_->next_[i];
		while (head != end_sent_) {
		  std::cout << static_cast<Node *>(head)->pair_val_.first << " ";
		  head = head->next_[i];
		}
		std::cout << std::endl;
	  }
	}

	void copy_map(const Map &other);
	/*
	  Private Data Members
	 */
	// std::vector<Node*> skip_list_;
	size_t size_;
	std::random_device rand_dev_;
	std::mt19937_64 gen_;
	std::uniform_real_distribution<double> dist_;
	// ReverseIterator end_;
	SNode *begin_sent_;
	SNode *end_sent_;
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
	  Iterator(SNode *other_node) {
	  	this->node_ = other_node;
	  }
	 public:
	  ValueType &operator*() const {
		return static_cast<Node *>(this->node_)->pair_val_;
	  }
	  ValueType *operator->() const {
		return &(static_cast<Node *>(this->node_)->pair_val_);
	  }
	};

	class ConstIterator{
	  friend class Map;
	  friend class Iterator;
	 protected:
	  SNode *node_;
	  ConstIterator() {
	  	node_ = nullptr;
	  }
	  ConstIterator(SNode *other_node) {
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
		return static_cast<Node *>(node_)->pair_val_;
	  }
	  const ValueType *operator->() const {
		return &(static_cast<Node *>(node_)->pair_val_);
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
	  SNode *node_;
	  ReverseIterator() {
		node_ = nullptr;
	  }
	  ReverseIterator(SNode *other_node) {
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
		return static_cast<Node *>(node_)->pair_val_;		
	  }
	  ValueType *operator->() const {
		return &(static_cast<Node *>(node_)->pair_val_);
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
	Map() :  gen_(rand_dev_()), dist_(0.0, 1.0) {
	  size_ = 0;
	  begin_sent_ = new SNode();
	  end_sent_ = new SNode();
	}
	Map(const Map &other) {
	  size_ = other.size_;
	  
	}
	Map &operator=(const Map &other) {
	  size_ = other.size_;
	}
	Map(std::initializer_list<std::pair<const Key_T, Mapped_T>>) {
	  
	}
	~Map() {
	  delete begin_sent_;
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
	  return Iterator(begin_sent_->next_[0]);
	}
	Iterator end() {
	  return Iterator(end_sent_);
	}
	ConstIterator begin() const {
	  return ConstIterator(begin_sent_->next_[0]);
	}
	ConstIterator end() const {
	  return ConstIterator(end_sent_);
	}
	ReverseIterator rbegin() {
	  return ReverseIterator(end_sent_->prev_[0]);
	}
	ReverseIterator rend() {
	  return ReverseIterator(begin_sent_);
	}
	/*
	  Element Access
	 */
	Iterator find(const Key_T &key) {
	  return Iterator(find_node(key));
	  // if (skip_list_.size() == 0) {
	  // 	return end();
	  // } else {
	  // 	return Iterator(find_node(key));
	  // }
	}
	ConstIterator find(const Key_T &key) const {
	  return ConstIterator(find_node(key));
	}
	Mapped_T &at(const Key_T &key) {
	  SNode *ptr = find_node(key);
	  if (ptr == end_sent_) {
		throw std::out_of_range("Key not located in map");		
	  } else {
		return static_cast<Node *>(ptr)->pair_val_.second;
	  }
	}
	const Mapped_T &at(const Key_T &key) const {
	  SNode *ptr = find_node(key);
	  if (ptr == end_sent_) {
		throw std::out_of_range("Key not located in map");		
	  } else {
		return static_cast<Node *>(ptr)->pair_val_.second;
	  } 
	}
	Mapped_T &operator[](const Key_T &key) {
	  SNode *ptr = find_node(key);
	  if (ptr == end_sent_) {
		ValueType to_insert(key, Mapped_T());
		std::pair<Iterator, bool> result = insert(to_insert);
		return result.first.node_->pair_val_.second;		
	  } else {
		return static_cast<Node *>(ptr)->pair_val_.second;
	  }
	}
	/*
	  Modifier
	 */
	std::pair<Iterator, bool> insert(const ValueType &value) {
	  // std::cout << "(" << value.first << ", " << value.second << ")" << std::endl;
	  double rand_dbl = dist_(gen_);
	  size_t num_levels = get_number_levels(rand_dbl);
	  // size_t num_levels = 0;
	  // std::cout << num_levels << std::endl;
	  Node *element = new Node(value.first, value.second, num_levels);
	  // If current size of begin_sent_ and end_Sent_ is smaller than num_levels
	  while (begin_sent_->next_.size() < num_levels + 1) {
		begin_sent_->next_.push_back(end_sent_);
		end_sent_->prev_.push_back(begin_sent_);
		begin_sent_->prev_.push_back(nullptr);
		end_sent_->next_.push_back(nullptr);
	  }
	  size_t min_index = std::min((size_t)begin_sent_->next_.size() - 1, num_levels);
	  if (!insert_node(element, min_index)) {
		return std::make_pair(Iterator((Node *)nullptr), false);
	  }
	  // std::cout << "Increasing size" << std::endl;
	  ++ size_;
	  return std::make_pair(Iterator(element), true);
	}

	std::pair<Iterator, bool> insert(const ValueType &value, size_t num_levels) {
	  // std::cout << "(" << value.first << ", " << value.second << ")" << std::endl;
	  // double rand_dbl = dist_(gen_);
	  // size_t num_levels = get_number_levels(rand_dbl);
	  // size_t num_levels = 0;
	  std::cout << num_levels << std::endl;
	  Node *element = new Node(value.first, value.second, num_levels);
	  // If current size of begin_sent_ and end_Sent_ is smaller than num_levels
	  while (begin_sent_->next_.size() < num_levels + 1) {
		begin_sent_->next_.push_back(end_sent_);
		end_sent_->prev_.push_back(begin_sent_);
		begin_sent_->prev_.push_back(nullptr);
		end_sent_->next_.push_back(nullptr);
	  }
	  size_t min_index = std::min((size_t)begin_sent_->next_.size() - 1, num_levels);
	  if (!insert_node(element, min_index)) {
		return std::make_pair(Iterator((Node *)nullptr), false);
	  }
	  // std::cout << "Increasing size" << std::endl;
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
	  	SNode *node = pos.node_;
	  	for(unsigned int i = 0; i < node->prev_.size(); ++ i){
	  	  if (node->next_[i] != nullptr) {
	  	  	  node->prev_[i]->next_[i] = node->next_[i];
			  node->next_[i]->prev_[i] = node->prev_[i];
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
	  delete begin_sent_;
	  begin_sent_ = new SNode();
	  end_sent_ = new SNode();
	  // if (skip_list_.size() != 0) {
	  // 	delete skip_list_[0];
	  // 	skip_list_.clear();
	  // 	size_ = 0;
	  // }
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
	size_t current_level) {
  // std::cout << "Starting current_level: " << current_level << std::endl;
  // std::cout << "Inserting node" << std::endl;
  auto current_element = begin_sent_->next_[current_level];
  bool need_to_insert = false;
  bool reached_end = false;
  while (!reached_end && current_element != nullptr) {
	if (current_element == end_sent_) {
	  need_to_insert = true;
	} else {
	  // assert(element != nullptr);
	  // assert(element != end_sent_);
	  // assert(element != begin_sent_);
	  // assert(current_element != nullptr);
	  // assert(current_element != end_sent_);
	  // assert(current_element != begin_sent_);
	  if (element->pair_val_.first ==
		  static_cast<Node *>(current_element)->pair_val_.first) {
		erase(Iterator(element));
		return false;
	  }
	  if (element->pair_val_.first < static_cast<Node *>(current_element)->pair_val_.first) {
		need_to_insert = true;
	  } else {
		current_element = current_element->next_[current_level];
	  }
	}
	if (need_to_insert) {
		element->next_[current_level] = current_element;
		element->prev_[current_level] = current_element->prev_[current_level];
		current_element->prev_[current_level]->next_[current_level] = element;
		current_element->prev_[current_level] = element;
		if (current_level != 0) {
		  current_element = element->prev_[current_level]->next_[current_level - 1];
		  -- current_level;
		} else {
		  reached_end = true;
		}
	}
	need_to_insert = false;
  }
  return true;
}

// template <typename Key_T, typename Mapped_T>
// typename cs540::Map<Key_T, Mapped_T>::SNode *
// cs540::Map<Key_T, Mapped_T>::find_node(const Key_T &key) {
//   SNode *current_element = begin_sent_.next_.back();
//   int current_level = begin_sent_->next_.size() - 1;
//   // return find_node(key, begin_sent_->next_.back(), begin_sent_->next_.size() - 1);
//   while (current_element != nullptr) {
// 	if (current_element == end_sent_) {
// 	  if (current_level == 0) {
// 		return end_sent_;
// 	  } else {
// 		current_element = current_element->prev_[current_level]->next_[current_level - 1];
// 		-- current_level;
// 	  }
// 	} else {
// 	  current_key = static_cast<Node *>(current_element)->pair_val.first;
// 	  if (key == current_key) return current_element;
// 	  if (key < current_key) {
// 		current_element = current_element->prev_[current_level]->next_[current_level - 1];
// 		-- current_level;		
// 	  } else {
// 		current_element = current_element->next_[current_level];		
// 	  } 
// 	}
//   }
//   return end_sent_;
//   // if (key == current_element->pair_val_.first) return current_element;
//   // if (key < current_element->pair_val_.first) {
//   // 	// Searching element before current_element
//   // 	if (current_element == skip_list_[current_level]) {
//   // 	  // Searching at head
//   // 	  if (current_level != 0) {
//   // 		return find_node(key, skip_list_[current_level - 1], current_level - 1);
//   // 	  } else {
//   // 		return nullptr;
//   // 	  }
//   // 	} else {
//   // 	  // Searching not at head
//   // 	  if (current_level != 0) {
//   // 		return find_node(key, current_element->prev_[current_level], current_level - 1);
//   // 	  } else {
//   // 		return nullptr;
//   // 	  }
//   // 	}
//   // } else {
//   // 	// Search element after current_element
//   // 	if (current_element->next_[current_level] == nullptr) {
//   // 	  // Next is null
//   // 	  if (current_level != 0) {
//   // 		return find_node(key, current_element, current_level - 1);
//   // 	  } else {
//   // 		return nullptr;
//   // 	  }
//   // 	} else {
//   // 	  return find_node(key, current_element->next_[current_level], current_level);
//   // 	}
//   }
// }

// template <typename Key_T, typename Mapped_T>
// void cs540::Map<Key_T, Mapped_T>::copy_map(const Map &other) {
//   size_ = other.size_;
//   Node *current = other.skip_list_[0];
//   while (current != nullptr) {
// 	int num_levels = current->prev_.size();
// 	Node *element = new Node(current->value.first, current->value.second, current->prev_.size());
// 	if (skip_list_.size() == 0) {
// 	  // Initial inserts
// 	  while (skip_list_.size() < num_levels + 1) {
// 		skip_list_.push_back(element);
// 	  }
// 	  end_.node_ = element;
// 	} else {
// 	  size_t min_index = std::min((size_t)skip_list_.size() - 1, num_levels);
// 	  insert_node(element, skip_list_[min_index], min_index);
// 	  while (skip_list_.size() < num_levels + 1) {
// 		skip_list_.push_back(element);
// 	  }		
// 	}
// 	++ size_;
// 	return std::make_pair(Iterator(element), true);
	
//   }
// }

#endif
