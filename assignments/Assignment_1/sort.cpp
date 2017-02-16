#include <dlfcn.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <random>
#include <unistd.h>
#include "Deque.hpp"

/*
 * Test for class MyClass.
 */

struct MyClass {
    int id;
    char name[10];
};

bool
MyClass_less_by_name(const MyClass &o1, const MyClass &o2) {
    return (o1.name[0] > o2.name[0]);
}

void
MyClass_print(const MyClass *o) {
    printf("%d ", o->id);
    printf("%s\n", o->name);
}

Deque_DEFINE(MyClass)

/*
 * Test for int.
 */

    bool
    int_less(const int &o1, const int &o2) {
        return o1 < o2;
    }
Deque_DEFINE(int)

int
main() {
    FILE *devnull = fopen("/dev/null", "w");
    assert(devnull != 0);

    // Sorting with correct function
    {
        Deque_MyClass deq;
        Deque_MyClass_ctor(&deq, MyClass_less_by_name);

        deq.push_front(&deq, MyClass{1, "zzz"});
        deq.push_front(&deq, MyClass{2, "aaa"});
        deq.push_front(&deq, MyClass{3, "fdr"});
        deq.push_front(&deq, MyClass{0, "ccc"});
        deq.push_front(&deq, MyClass{-1, "ddd"});

        deq.sort(&deq, deq.begin(&deq), deq.end(&deq));

        for (Deque_MyClass_Iterator it = deq.begin(&deq);
         !Deque_MyClass_Iterator_equal(it, deq.end(&deq)); it.inc(&it)) {
            MyClass_print(&it.deref(&it));
        }

        deq.dtor(&deq);
    }

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
       iter1.dec(&iter1);   
       
       auto iter2 = deq1.begin(&deq1);
       
       for (int i=0;i<10000;i++) {
           iter2.inc(&iter2);
       }

       deq1.sort(&deq1, iter2,iter1);

       Deque_int deq2;
       Deque_int_ctor(&deq2 , int_less);

       for(int i=0;i<=20001;i++) {
           deq2.push_back(&deq2,i);
       }

      assert(Deque_int_equal(deq1, deq2)); 

      deq1.dtor(&deq1);
      deq2.dtor(&deq2);
    }
}
