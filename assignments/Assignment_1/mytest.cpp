#include "Deque.hpp"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <random>
#include <unistd.h>

/*
 * Test for class MyClass.
 */

struct MyClass {
    int id;
  char name[10];
};

bool
MyClass_less_by_id(const MyClass &o1, const MyClass &o2) {
    return o1.id < o2.id;
}

void
MyClass_print(const MyClass *o) {
    printf("%d\n", o->id);
    printf("%s\n", o->name);
}

Deque_DEFINE(MyClass)

bool
int_less(const int &o1, const int &o2) {
    return o1 < o2;
}

Deque_DEFINE(int)

void PrintQueueInt(Deque_int *deq) {					
  std::cout << "--------- Print Queue --------- " << std::endl;	
  std::cout << "Capacity: " << deq->capacity << std::endl;		
  std::cout << "Begin_Index: " << deq->begin_index << std::endl;	
  std::cout << "End_Index: " << deq->end_index << std::endl;		
  std::cout << "Queue_Length: " << deq->queue_length << std::endl;	
  std::cout << "Size: " << deq->queue_length << std::endl;		
  std::cout << "Empty: " << deq->empty(deq) << std::endl;
  for (Deque_int_Iterator it = deq->begin(deq);
       !Deque_int_Iterator_equal(it, deq->end(deq)); it.inc(&it)) {
    std::cout << it.deref(&it) << std::endl;
  }
}									
 									
bool Deque_int_equal(Deque_int deq1, Deque_int deq2) {		
  if (deq1.queue_length == deq2.queue_length) {			
    Deque_int_Iterator it1 = deq1.begin(&deq1);			
    Deque_int_Iterator it2 = deq2.begin(&deq2);			
    while (!Deque_int_Iterator_equal(it1, deq1.end(&deq1)) &&	
	   !Deque_int_Iterator_equal(it2, deq2.end(&deq2))) {	
      if (deq1.less_than(it1.deref(&it1), it2.deref(&it2)) ||		
	  deq1.less_than(it2.deref(&it2), it1.deref(&it1)) ) {	
	return false;							
      }								
      it1.inc(&it1);							
      it2.inc(&it2);							
    }									
    return true;							
  }									
  return false;							
}									



int main(){
    // Sorting Test 2
  {
    Deque_int deq1;
    Deque_int_ctor(&deq1, int_less);

    for (int i=0;i<10000;i++) {
      deq1.push_back(&deq1, i);
    }

    for (int i=20000;i>=10000;i--) {
      deq1.push_back(&deq1,i);
    }

    deq1.push_back(&deq1,20001);
      
    auto iter1 =  deq1.end(&deq1);
    std::cout << iter1.index << std::endl;
    iter1.dec(&iter1);	
       
    auto iter2 = deq1.begin(&deq1);
       
    for (int i=0;i<10000;i++) {
      iter2.inc(&iter2);
    }
    std::cout << iter2.index << std::endl;
    std::cout << iter1.index << std::endl;
    deq1.sort(&deq1, iter2,iter1);
    // PrintQueueInt(&deq1);
    Deque_int deq2;
    Deque_int_ctor(&deq2 , int_less);

    for(int i=0;i<=20001;i++) {
      deq2.push_back(&deq2,i);
    }
    // std::cout << "----------------------------" << std::endl;
    // PrintQueueInt(&deq2);
    assert(Deque_int_equal(deq1, deq2)); 
    
    deq1.dtor(&deq1);
    deq2.dtor(&deq2);
  }
  return 0;
}
