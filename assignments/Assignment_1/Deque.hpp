#include <cassert>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#ifndef DEQUE_HPP_
#define DEQUE_HPP_

static const int INITIAL_CAPACITY = 10;

#define Deque_DEFINE(t)							\
  struct Deque_##t##_Iterator;						\
  struct Deque_##t {							\
    size_t capacity;							\
    size_t queue_length;						\
    t *array;								\
    size_t begin_index;							\
    size_t end_index;							\
    char type_name[sizeof("Deque_" #t)] = "Deque_" #t;			\
    bool (*less_than)(const t &, const t &);				\
    void (*push_back)(Deque_##t *deq, const t item);			\
    void (*push_front)(Deque_##t *deq, const t item);			\
    void (*pop_front)(Deque_##t *deq);					\
    void (*pop_back)(Deque_##t *deq);					\
    t &(*front)(Deque_##t *deq);					\
    t &(*back)(Deque_##t *deq);						\
    size_t (*size)(Deque_##t *deq);					\
    bool (*empty)(Deque_##t *deq);					\
    void (*dtor)(Deque_##t *deq);					\
    void (*clear)(Deque_##t *deq);					\
    t &(*at)(Deque_##t *deq, size_t index);				\
    void (*sort)(Deque_##t *deq, Deque_##t##_Iterator start, Deque_##t##_Iterator last); \
    Deque_##t##_Iterator (*begin)(Deque_##t *deq);			\
    Deque_##t##_Iterator (*end)(Deque_##t *deq);			\
  };									\
									\
  struct Deque_##t##_Iterator {						\
    size_t index;							\
    Deque_##t *deq;							\
    t &(*deref)(Deque_##t##_Iterator *it);				\
    void (*inc)(Deque_##t##_Iterator *it);				\
    void (*dec)(Deque_##t##_Iterator *it);				\
  };									\
  									\
  void Deque_##t##_Iterator_ctor(Deque_##t##_Iterator *it, Deque_##t *deq); \
  bool Deque_##t##_Iterator_equal(Deque_##t##_Iterator it1, Deque_##t##_Iterator it2); \
  									\
  void resize(Deque_##t *deq){						\
    assert(deq->end_index == deq->begin_index -1 || deq->end_index == deq->capacity - 1); \
    t *array_new = new t[deq->capacity * 2];				\
    if (deq->begin_index < deq->end_index)				\
      std::memcpy(array_new, deq->array + deq->begin_index, (deq->end_index - deq->begin_index) * sizeof(t)); \
    else {								\
      std::memcpy(array_new, deq->array + deq->begin_index, (deq->capacity - deq->begin_index) * sizeof(t)); \
      std::memcpy(array_new + (deq->capacity - deq->begin_index), deq->array, deq->end_index * sizeof(t)); \
    }									\
    deq->begin_index = 0;						\
    deq->end_index = deq->capacity - 1;					\
    deq->capacity = deq->capacity * 2;					\
    delete[] deq->array;						\
    deq->array = array_new;						\
  }									\
									\
  void push_back(Deque_##t *deq, const t item) {			\
    if (deq->capacity - 1 == deq->queue_length) {			\
      resize(deq);							\
    }									\
    *(deq->array + deq->end_index) = item;				\
    deq->end_index = (deq->end_index + 1) % deq->capacity;		\
    ++ deq->queue_length;						\
  }									\
									\
  void push_front(Deque_##t *deq, const t item) {			\
    if (deq->capacity - 1 == deq->queue_length) {			\
      resize(deq);							\
    }									\
    if (deq->begin_index == 0)						\
      deq->begin_index = deq->capacity - 1;				\
    else								\
      deq->begin_index = deq->begin_index - 1;				\
    *(deq->array + deq->begin_index) = item;				\
    ++ deq->queue_length;						\
  }									\
  									\
  void pop_front(Deque_##t *deq) {					\
    -- deq->queue_length;						\
    deq->begin_index = (deq->begin_index + 1) % deq->capacity;		\
  }									\
  									\
  void pop_back(Deque_##t *deq) {					\
    -- deq->queue_length;						\
    if (deq->end_index == 0)						\
      deq->end_index = deq->capacity - 1;				\
    else								\
      deq->end_index = deq->end_index - 1;				\
  }									\
  									\
  t &front(Deque_##t *deq) {						\
    return *(deq->array + deq->begin_index);				\
  }									\
  									\
  t &back(Deque_##t *deq) {						\
    return *(deq->array + deq->end_index - 1);				\
  }									\
  									\
  size_t size(Deque_##t *deq) {						\
    return deq->queue_length;						\
  }									\
  									\
  bool empty(Deque_##t *deq) {						\
    return deq->queue_length == 0;					\
  }									\
  									\
  t &at(Deque_##t *deq, size_t index) {					\
    return *(deq->array + ((index + deq->begin_index) % deq->capacity)); \
  }									\
  									\
  Deque_##t##_Iterator begin(Deque_##t *deq) {				\
    Deque_##t##_Iterator it;						\
    Deque_##t##_Iterator_ctor(&it, deq);				\
    it.index = deq->begin_index;					\
    return it;								\
  }									\
									\
  Deque_##t##_Iterator end(Deque_##t *deq) {				\
    Deque_##t##_Iterator it;						\
    Deque_##t##_Iterator_ctor(&it, deq);				\
    it.index = deq->end_index;						\
    return it;								\
  }									\
  									\
  void clear(Deque_##t *deq){						\
    deq->begin_index = 0;						\
    deq->end_index = 0;							\
    deq->queue_length = 0;						\
  }									\
									\
  void dtor(Deque_##t *deq) {						\
    delete[] deq->array;						\
    deq->array = NULL;							\
    deq->capacity = 0;							\
    deq->clear(deq);							\
  }									\
									\
									\
  									\
  void sort(Deque_##t *deq, Deque_##t##_Iterator start, Deque_##t##_Iterator last) { \
    if (start.index > last.index) {					\
      t *array_new = new t[deq->capacity];				\
      std::memcpy(array_new, deq->array + deq->begin_index, (deq->capacity - deq->begin_index) * sizeof(t)); \
      std::memcpy(array_new + (deq->capacity - deq->begin_index), deq->array, deq->end_index * sizeof(t)); \
      start.index = start.index - deq->begin_index;			\
      last.index = ((deq->capacity - 1) - deq->begin_index) + last.index; \
      deq->begin_index = 0;						\
      deq->end_index = ((deq->capacity - 1) - deq->begin_index) + deq->end_index; \
      delete[] deq->array;						\
      deq->array = array_new;						\
    }  									\
  }									\
									\
  void PrintQueue(Deque_##t *deq) {					\
    std::cout << "--------- Print Queue --------- " << std::endl;	\
    std::cout << "Capacity: " << deq->capacity << std::endl;		\
    std::cout << "Begin_Index: " << deq->begin_index << std::endl;	\
    std::cout << "End_Index: " << deq->end_index << std::endl;		\
    std::cout << "Queue_Length: " << deq->queue_length << std::endl;	\
    std::cout << "Size: " << deq->queue_length << std::endl;		\
    std::cout << "Empty: " << deq->empty(deq) << std::endl;		\
  }									\
 									\
  bool Deque_##t##_equal(Deque_##t deq1, Deque_##t deq2) {		\
    if (deq1.queue_length == deq2.queue_length) {			\
      Deque_##t##_Iterator it1 = deq1.begin(&deq1);			\
      Deque_##t##_Iterator it2 = deq2.begin(&deq2);			\
      while (!Deque_##t##_Iterator_equal(it1, deq1.end(&deq1)) &&	\
	     !Deque_##t##_Iterator_equal(it2, deq2.end(&deq2))) {	\
	if (deq1.less_than(it1.deref(&it1), it2.deref(&it2)) ||		\
	    deq1.less_than(it2.deref(&it2), it1.deref(&it1)) ) {	\
	  return false;							\
	}								\
	it1.inc(&it1);							\
	it2.inc(&it2);							\
      }									\
      return true;							\
    }									\
    return false;							\
  }									\
									\
									\
  void Deque_##t##_ctor(Deque_##t *deq, bool (*less_than)(const t &, const t &)) { \
    deq->less_than = less_than;						\
    deq->queue_length = 0;						\
    deq->begin_index = 0;						\
    deq->end_index = 0;							\
    deq->array = new t[INITIAL_CAPACITY];				\
    deq->capacity = INITIAL_CAPACITY;					\
    deq->push_back = push_back;						\
    deq->push_front = push_front;					\
    deq->pop_back = pop_back;						\
    deq->pop_front = pop_front;						\
    deq->front = front;							\
    deq->back = back;							\
    deq->size = size;							\
    deq->empty = empty;							\
    deq->clear = clear;							\
    deq->dtor = dtor;							\
    deq->begin = begin;							\
    deq->end = end;							\
    deq->at = at;							\
    deq->sort = sort;							\
  }									\
 									\
  t &deref(Deque_##t##_Iterator *it) {					\
    return *(it->deq->array + it->index % it->deq->capacity);		\
  }									\
 									\
  void inc(Deque_##t##_Iterator *it) {					\
    it->index = (it->index + 1) % it->deq->capacity;			\
  }									\
 									\
  void dec(Deque_##t##_Iterator *it) {					\
    if (it->index == 0)							\
      it->index = it->deq->capacity - 1;				\
    else								\
      it->index = it->index - 1;					\
  }									\
 									\
  bool Deque_##t##_Iterator_equal(Deque_##t##_Iterator it1, Deque_##t##_Iterator it2) { \
    return it1.index == it2.index;					\
  }									\
 									\
  void Deque_##t##_Iterator_ctor(Deque_##t##_Iterator *it, Deque_##t *deq) { \
    it->deref = deref;							\
    it->inc = inc;							\
    it->dec = dec;							\
    it->deq = deq;							\
  }


#endif // DEQUE_HPP_
