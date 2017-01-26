#include <cassert>
#include <iostream>
#include <cstdio>
#include <cstring>

#ifndef DEQUE_HPP_
#define DEQUE_HPP_

static const int INITIAL_CAPACITY = 1000;

struct Deque_DEFINE {
  // Deque_DEFINE() : capacity(0), queue_length(0), array(NULL), begin(0), end(0) {};
  size_t capacity;
  size_t queue_length;
  int *array;
  unsigned int begin;
  unsigned int end;
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

void push_back(Deque_DEFINE *deq, int item) {
  if (deq->capacity - 1 == deq->queue_length) {
    assert(deq->end == deq->begin -1 || deq->end == capacity - 1);
    // Resize
    int *array_new = new int[deq->capacity * 2];
    if (deq->begin < deq->end)
      // All elements are in order
      std::memcpy(array_new, deq->array + deq->begin, deq->end - deq->begin);
    else {
      // All elements are not in order
      std::memcpy(array_new, deq->array + deq->begin, deq->capacity - deq->begin);
      std::memcpy(array_new + (deq->capacity - deq->begin), deq->array, deq->end);
    }
    deq->begin = 0;
    deq->end = deq->capacity;
    deq->capacity = deq->capacity * 2;
    delete[] deq->array;
    deq->array = array_new;
  } else {
    *(deq->array + deq->end) = item;
    deq->end = (deq->end + 1) % deq->capacity;
    ++ deq->queue_length;
  }
}

void push_front(Deque_DEFINE *deq, int item) {
  if (deq->capacity - 1 == deq->queue_length) {
    assert(deq->end == deq->begin -1 || deq->end == capacity - 1);
    // Resize
    int *array_new = new int[deq->capacity * 2];
    if (deq->begin < deq->end)
      // All elements are in order
      std::memcpy(array_new, deq->array + deq->begin, deq->end - deq->begin);
    else {
      // All elements are not in order
      std::memcpy(array_new, deq->array + deq->begin, deq->capacity - deq->begin);
      std::memcpy(array_new + (deq->capacity - deq->begin), deq->array, deq->end);
    }
    deq->begin = 0;
    deq->end = deq->capacity;
    deq->capacity = deq->capacity * 2;
    delete[] deq->array;
    deq->array = array_new;
  } else {
    if (deq->begin == 0)
      deq->begin = deq->capacity - 1;
    *(deq->array + deq->begin) = item;
    ++ deq->queue_length;
  }
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

void PrintQueue(Deque_DEFINE *deq) {
  std::cout << "Capacity: " << deq->capacity << std::endl;
  std::cout << "Begin: " << deq->begin << std::endl;
  std::cout << "End: " << deq->end << std::endl;
  std::cout << "Queue_Length: " << deq->queue_length << std::endl;
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
  std::cout << "}" << std::endl;;
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

#endif // DEQUE_HPP_
