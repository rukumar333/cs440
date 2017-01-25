#include <assert.h>
#include <iostream>
#include <cstdio>
#include <cstring>

#ifndef DEQUE_HPP_
#define DEQUE_HPP_

struct Deque_DEFINE{
  size_t capacity;
  size_t queue_length;
  int *array;
  int begin;
  int end;
};

void push_back(Deque_DEFINE *deq, int item) {
  if (deq->capacity == deq->queue_length) {
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
    deq->end = capacity;
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
  if (deq->capacity == deq->queue_length) {
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
    deq->end = capacity;
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

#endif // DEQUE_HPP_
