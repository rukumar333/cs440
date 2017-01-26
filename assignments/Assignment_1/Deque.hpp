#include <cassert>
#include <iostream>
#include <cstdio>
#include <cstring>

#ifndef DEQUE_HPP_
#define DEQUE_HPP_

static const int INITIAL_CAPACITY = 2;

struct Deque_DEFINE {
  // Deque_DEFINE() : capacity(0), queue_length(0), array(NULL), begin(0), end(0) {};
  size_t capacity;
  size_t queue_length;
  int *array;
  size_t begin;
  size_t end;
  bool (*compare_function)(const int&, const int&);
  void (*push_back)(Deque_DEFINE *deq, int item);
  void (*push_front)(Deque_DEFINE *deq, int item);
  void (*pop_front)(Deque_DEFINE *deq);
  void (*pop_back)(Deque_DEFINE *deq);
  int (*front)(Deque_DEFINE *deq);
  int (*back)(Deque_DEFINE *deq);
  size_t (*size)(Deque_DEFINE *deq);
  bool (*empty)(Deque_DEFINE *deq);
};

struct Deque_DEFINE_Iterator {
  size_t index;
  Deque_DEFINE *deq;
  int (*deref)(Deque_DEFINE_Iterator *it);
  void (*inc)(Deque_DEFINE_Iterator *it);
  void (*dec)(Deque_DEFINE_Iterator *it);  
};

void Deque_DEFINE_Iterator_ctor(Deque_DEFINE_Iterator *it, Deque_DEFINE *deq);

/* -------- Deque Functions -------- */

void resize(Deque_DEFINE *deq){
  assert(deq->end == deq->begin -1 || deq->end == deq->capacity - 1);
  // Resize
  int *array_new = new int[deq->capacity * 2];
  if (deq->begin < deq->end)
    // All elements are in order
    std::memcpy(array_new, deq->array + deq->begin, (deq->end - deq->begin) * sizeof(int));
  else {
    // All elements are not in order
    std::memcpy(array_new, deq->array + deq->begin, (deq->capacity - deq->begin) * sizeof(int));
    std::memcpy(array_new + (deq->capacity - deq->begin), deq->array, deq->end * sizeof(int));
  }
  deq->begin = 0;
  deq->end = deq->capacity - 1;
  deq->capacity = deq->capacity * 2;
  delete[] deq->array;
  deq->array = array_new;
}

void push_back(Deque_DEFINE *deq, int item) {
  if (deq->capacity - 1 == deq->queue_length) {
    resize(deq);
  }
  *(deq->array + deq->end) = item;
  deq->end = (deq->end + 1) % deq->capacity;
  ++ deq->queue_length;
}

void push_front(Deque_DEFINE *deq, int item) {
  if (deq->capacity - 1 == deq->queue_length) {
    resize(deq);
  }  
  if (deq->begin == 0)
    deq->begin = deq->capacity - 1;
  *(deq->array + deq->begin) = item;
  ++ deq->queue_length;
}

void pop_front(Deque_DEFINE *deq) {
  -- deq->queue_length;
  deq->begin = (deq->begin + 1) % deq->capacity;
}

void pop_back(Deque_DEFINE *deq) {
  -- deq->queue_length;
  if (deq->end == 0)
    deq->end = deq->capacity - 1;  
}

int front(Deque_DEFINE *deq) {
  return *(deq->array + deq->begin);  
}

int back(Deque_DEFINE *deq) {
  return *(deq->array + deq->end - 1);
}

size_t size(Deque_DEFINE *deq) {
  return deq->queue_length;
}

bool empty(Deque_DEFINE *deq) {
  return deq->queue_length == 0;
}

int at(Deque_DEFINE *deq, size_t index) {
  return *(deq->array + index % deq->capacity);
}

Deque_DEFINE_Iterator begin() {
  Deque_DEFINE_Iterator it;
  Deque_DEFINE_Iterator_ctor(&it);
  
}

Deque_DEFINE_Iterator end() {
  
}

void PrintQueue(Deque_DEFINE *deq) {
  std::cout << "--------- Print Queue --------- " << std::endl;
  std::cout << "Capacity: " << deq->capacity << std::endl;
  std::cout << "Begin: " << deq->begin << std::endl;
  std::cout << "End: " << deq->end << std::endl;
  std::cout << "Queue_Length: " << deq->queue_length << std::endl;
  std::cout << "Size: " << deq->queue_length << std::endl;
  std::cout << "Empty: " << deq->empty(deq) << std::endl;
  std::cout << "------ Elements --------" << std::endl;
  std::cout << "{";
  if (deq->begin < deq->end) {
    for(unsigned int i = deq->begin; i < deq->end; ++ i){
      std::cout << *(deq->array + i) << ", ";
    }
  } else {
    for(unsigned int i = deq->begin; i < deq->capacity; ++ i){
      std::cout << *(deq->array + i) << ", ";
    }
    for(unsigned int i = 0; i < deq->end; ++ i){
      std::cout << *(deq->array + i) << ", ";
    }
  }
  std::cout << "}" << std::endl;
  std::cout << "--------- ----------" << std::endl;
}

void Deque_DEFINE_ctor(Deque_DEFINE *deq, bool (*compare_function)(const int&, const int&)) {
  deq->compare_function = compare_function;
  deq->queue_length = 0;
  deq->begin = 0;
  deq->end = 0;
  deq->array = new int[INITIAL_CAPACITY];
  deq->capacity = INITIAL_CAPACITY;
  deq->push_back = push_back;
  deq->push_front = push_front;
  deq->pop_back = pop_back;
  deq->pop_front = pop_front;
  deq->front = front;
  deq->back = back;
  deq->size = size;
  deq->empty = empty;
}

void Deque_DEFINE_dtor(Deque_DEFINE *deq) {
  delete[] deq->array;
  deq->array = NULL;
  deq->capacity = 0;
  deq->begin = 0;
  deq->end = 0;
  deq->queue_length = 0;
}

/* -------- Deque Iterator Functions ------- */
int deref(Deque_DEFINE_Iterator *it) {
  return *(it->deq->array + it->index % it->deq->capacity);
}

void inc(Deque_DEFINE_Iterator *it) {
  it->index = it->index + 1 % it->deq->capacity;  
}

void dec(Deque_DEFINE_Iterator *it) {
  if(it->index == 0)
    it->index = it->deq->capacity - 1;
  else
    it->index = it->index - 1;
}

void Deque_DEFINE_Iterator_ctor(Deque_DEFINE_Iterator *it, Deque_DEFINE *deq) {
  it->deref = deref;
  it->inc = inc;
  it->dec = dec;
  it->deq = deq;  `
}

#endif // DEQUE_HPP_
