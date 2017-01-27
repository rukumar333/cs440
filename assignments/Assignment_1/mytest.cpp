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
