#include<iostream>
#include<type_traits>
#include"Deque.hpp"
#include <assert.h> 

Deque_DEFINE(int)

bool
int_less(const int &o1, const int &o2) {
        return o1 < o2;
}

int main() {

    // Check if deque is actually circular-1
    {
        Deque_int deq;
        Deque_int_ctor(&deq,int_less);

        deq.push_front(&deq, 1);
        deq.push_front(&deq, 2);
        deq.push_front(&deq, 3);

        assert(deq.back(&deq) == 1);

        deq.clear(&deq);
        deq.dtor(&deq);
        
    }

    // Check if deque is actually circular-2
    {
        Deque_int deq;
        Deque_int_ctor(&deq,int_less);

        deq.push_back(&deq, 1);
        deq.push_back(&deq, 2);
        deq.push_back(&deq, 3);

        assert(deq.front(&deq) == 1);

        deq.clear(&deq);
        deq.dtor(&deq);
        
    }

    return 0;
}
