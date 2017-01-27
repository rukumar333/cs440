#include "Deque.hpp"

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
    Deque_MyClass deq1, deq2;
    Deque_MyClass_ctor(&deq1, MyClass_less_by_id);
    Deque_MyClass_ctor(&deq2, MyClass_less_by_id);

    deq1.push_back(&deq1, MyClass{1, "Joe"});
    deq1.push_back(&deq1, MyClass{2, "Jane"});
    deq1.push_back(&deq1, MyClass{3, "Mary"});
    deq2.push_back(&deq2, MyClass{1, "Joe"});
    deq2.push_back(&deq2, MyClass{2, "Jane"});
    deq2.push_back(&deq2, MyClass{3, "Mary"});
	    
    assert(Deque_MyClass_equal(deq1, deq2));
    deq1.pop_back(&deq1);
    assert(!Deque_MyClass_equal(deq1, deq2));
    deq1.push_back(&deq1, MyClass{4, "Mary"});
    assert(!Deque_MyClass_equal(deq1, deq2));

    deq1.dtor(&deq1);
    deq2.dtor(&deq2);
  }
  return 0;
}
