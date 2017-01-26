#include <cassert>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#ifndef DEQUE_HPP_
#define DEQUE_HPP_

static const int INITIAL_CAPACITY = 2;

#define Deque_DEFINE(t)							\
  struct Deque_##t {							\
    size_t capacity;							\
    size_t queue_length;						\
    t *array;								\
    size_t begin;							\
    size_t end;								\
    char type_name[sizeof(#t)] = #t;					\
    bool (*compare_function)(const t &, const t &);			\
    void (*push_back)(Deque_##t *deq, t item);				\
    void (*push_front)(Deque_##t *deq, t item);				\
    void (*pop_front)(Deque_##t *deq);					\
    void (*pop_back)(Deque_##t *deq);					\
    t (*front)(Deque_##t *deq);						\
    t (*back)(Deque_##t *deq);						\
    size_t (*size)(Deque_##t *deq);					\
    bool (*empty)(Deque_##t *deq);					\
    void (*dtor)(Deque_##t *deq);					\
    void (*clear)(Deque_##t *deq);					\
  };									\
									\
  struct Deque_##t##_Iterator {						\
    size_t index;							\
    Deque_##t *deq;							\
    t (*deref)(Deque_##t##_Iterator *it);				\
    void (*inc)(Deque_##t##_Iterator *it);				\
    void (*dec)(Deque_##t##_Iterator *it);				\
  };									\
  									\
  void Deque_##t##_Iterator_ctor(Deque_##t##_Iterator *it, Deque_##t *deq); \
  									\
  void resize(Deque_##t *deq){						\
    assert(deq->end == deq->begin -1 || deq->end == deq->capacity - 1);	\
    t *array_new = new t[deq->capacity * 2];				\
    if (deq->begin < deq->end)						\
      std::memcpy(array_new, deq->array + deq->begin, (deq->end - deq->begin) * sizeof(t)); \
    else {								\
      std::memcpy(array_new, deq->array + deq->begin, (deq->capacity - deq->begin) * sizeof(t)); \
      std::memcpy(array_new + (deq->capacity - deq->begin), deq->array, deq->end * sizeof(t)); \
    }									\
    deq->begin = 0;							\
    deq->end = deq->capacity - 1;					\
    deq->capacity = deq->capacity * 2;					\
    delete[] deq->array;						\
    deq->array = array_new;						\
  }									\
									\
  void push_back(Deque_##t *deq, t item) {				\
    if (deq->capacity - 1 == deq->queue_length) {			\
      resize(deq);							\
    }									\
    *(deq->array + deq->end) = item;					\
    deq->end = (deq->end + 1) % deq->capacity;				\
    ++ deq->queue_length;						\
  }									\
									\
  void push_front(Deque_##t *deq, t item) {				\
    if (deq->capacity - 1 == deq->queue_length) {			\
      resize(deq);							\
    }									\
    if (deq->begin == 0)						\
      deq->begin = deq->capacity - 1;					\
    *(deq->array + deq->begin) = item;					\
    ++ deq->queue_length;						\
  }									\
  									\
  void pop_front(Deque_##t *deq) {					\
    -- deq->queue_length;						\
    deq->begin = (deq->begin + 1) % deq->capacity;			\
  }									\
  									\
  void pop_back(Deque_##t *deq) {					\
    -- deq->queue_length;						\
    if (deq->end == 0)							\
      deq->end = deq->capacity - 1;					\
  }									\
  									\
  t front(Deque_##t *deq) {						\
    return *(deq->array + deq->begin);					\
  }									\
  									\
  t back(Deque_##t *deq) {						\
    return *(deq->array + deq->end - 1);				\
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
  t at(Deque_##t *deq, size_t index) {					\
    return *(deq->array + index % deq->capacity);			\
  }									\
  									\
  Deque_##t##_Iterator begin(Deque_##t *deq) {				\
    Deque_##t##_Iterator it;						\
    Deque_##t##_Iterator_ctor(&it, deq);				\
    it.index = deq->begin;						\
    return it;								\
  }									\
									\
  Deque_##t##_Iterator end(Deque_##t *deq) {				\
    Deque_##t##_Iterator it;						\
    Deque_##t##_Iterator_ctor(&it, deq);				\
    it.index = deq->end;						\
    return it;								\
  }									\
  									\
  void clear(Deque_##t *deq){						\
    deq->begin = 0;							\
    deq->end = 0;							\
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
  void PrintQueue(Deque_##t *deq) {					\
    std::cout << "--------- Print Queue --------- " << std::endl;	\
    std::cout << "Capacity: " << deq->capacity << std::endl;		\
    std::cout << "Begin: " << deq->begin << std::endl;			\
    std::cout << "End: " << deq->end << std::endl;			\
    std::cout << "Queue_Length: " << deq->queue_length << std::endl;	\
    std::cout << "Size: " << deq->queue_length << std::endl;		\
    std::cout << "Empty: " << deq->empty(deq) << std::endl;		\
  }									\
 									\
  void Deque_##t##_ctor(Deque_##t *deq, bool (*compare_function)(const t &, const t &)) { \
    deq->compare_function = compare_function;				\
    deq->queue_length = 0;						\
    deq->begin = 0;							\
    deq->end = 0;							\
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
  }									\
 									\
  t deref(Deque_##t##_Iterator *it) {					\
    return *(it->deq->array + it->index % it->deq->capacity);		\
  }									\
 									\
  void inc(Deque_##t##_Iterator *it) {					\
    it->index = it->index + 1 % it->deq->capacity;			\
  }									\
 									\
  void dec(Deque_##t##_Iterator *it) {					\
    if(it->index == 0)							\
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
