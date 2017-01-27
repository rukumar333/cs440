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

// bool Deque_MyClass_equal(Deque_MyClass deq1, Deque_MyClass deq2) {		
//   if (deq1.queue_length == deq2.queue_length) {			
//     Deque_MyClass_Iterator it1 = deq1.begin(&deq1);			
//     Deque_MyClass_Iterator it2 = deq2.begin(&deq2);			
//     std::cout << it1.index << std::endl;				
//     std::cout << it2.index << std::endl;				
//     while (!Deque_MyClass_Iterator_equal(it1, deq1.end(&deq1)) &&	
// 	   !Deque_MyClass_Iterator_equal(it2, deq2.end(&deq2))) {	
//       // if ((deq1.less_than(it1.deref(&it1), it2.deref(&it2)) == 0) ||	
//       // 	  (deq1.less_than(it2.deref(&it2), it1.deref(&it1)) == 0)) {	
//       // 	return false;							
//       // }
//       if(deq1.less_than(it1.deref(&it1), it2.deref(&it2)) == 0){
// 	return false;
//       }
//       if(deq1.less_than(it2.deref(&it2), it1.deref(&it1)) == 0){
// 	return false;
//       }
//       it1.inc(&it1);							
//       it2.inc(&it2);							
//     }									
//     return true;							
//   }									
//   return false;
// }


int main(){
  // Test equality.  Two deques compare equal if they are of the same
  // length and all the elements compare equal.  It is undefined behavior
  // if the two deques were constructed with different comparison
  // functions.
  {
      
    Deque_int deq1;
    Deque_int_ctor(&deq1, int_less);

    std::default_random_engine e;
    using rand = std::uniform_int_distribution<int>;

    for (int i = 0; i < 1000; i++) {
      deq1.push_back(&deq1, rand(-1000000, 1000000)(e));
    }

    auto iter1 = deq1.begin(&deq1);
    auto iter2 = deq1.begin(&deq1);

    for(int i=0;i<20;i++)
      iter1.inc(&iter1);

    for(int i=0;i<20;i++)
      iter2.inc(&iter2);

    for(int i=0;i<1;i++){
      deq1.sort(&deq1, iter1,iter2); 
    }

    deq1.dtor(&deq1);
  }
  return 0;
}
