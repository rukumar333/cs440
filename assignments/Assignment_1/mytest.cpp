#include "Deque.hpp"

/*
 * Test for int.
 */

bool
int_less(const int &o1, const int &o2) {
    return o1 < o2;
}

int main(){
  Deque_DEFINE deq;
  Deque_DEFINE_ctor(&deq, int_less);
  deq.push_back(&deq, 1);
  deq.push_back(&deq, 10);
  deq.push_back(&deq, 471);
  deq.push_back(&deq, -19);
  deq.push_front(&deq, 100);
  PrintQueue(&deq);
  deq.pop_front(&deq);
  PrintQueue(&deq);
  Deque_DEFINE_dtor(&deq);
  return 0;
}
