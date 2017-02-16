#include<iostream>
#include<type_traits>
#include"Deque.hpp"
#include <assert.h> 

Deque_DEFINE(int);

bool
int_less(const int &o1, const int &o2) {
        return o1 < o2;
}

int main() {

    {
        // Check if required function are pointer functions or not.

        Deque_int deq;
        Deque_int_ctor(&deq, int_less);

        std::cout<<std::boolalpha;
        std::cout<<std::is_member_function_pointer<decltype(&Deque_int::size)>::value<<"\n";
        std::cout<<std::is_member_function_pointer<decltype(&Deque_int::front)>::value<<"\n";
        std::cout<<std::is_member_function_pointer<decltype(&Deque_int::back)>::value<<"\n";
        std::cout<<std::is_member_function_pointer<decltype(&Deque_int::sort)>::value<<"\n";
        std::cout<<std::is_member_function_pointer<decltype(&Deque_int::push_back)>::value<<"\n";
        std::cout<<std::is_member_function_pointer<decltype(&Deque_int::begin)>::value<<"\n";

        Deque_int_Iterator it;
        std::cout<<std::is_member_function_pointer<decltype(&Deque_int_Iterator::deref)>::value<<"\n";
        std::cout<<std::is_member_function_pointer<decltype(&Deque_int_Iterator::inc)>::value<<"\n";
		deq.dtor(&deq);
    }
    

    // Check if standard container is used
    // Although not a very good way to check.. But this can give a idea atleast
    {
        #ifdef _GLIBCXX_VECTOR
            std::cout<<false<<"\n";
        #endif
        #ifndef _GLIBCXX_VECTOR
            std::cout<<true<<"\n";
        #endif

        
        #ifdef _GLIBCXX_MAP
            std::cout<<false<<"\n";
        #endif
        #ifndef _GLIBCXX_MAP
            std::cout<<true<<"\n";
        #endif

        #ifdef _GLIBCXX_DEQUE
            std::cout<<false<<"\n";
        #endif
        #ifndef _GLIBCXX_DEQUE
            std::cout<<true<<"\n";
        #endif

        #ifdef _GLIBCXX_ARRAY
            std::cout<<false<<"\n";
        #endif
        #ifndef _GLIBCXX_ARRAY
            std::cout<<true<<"\n";
        #endif

        #ifdef _GLIBCXX_QUEUE
            std::cout<<false<<"\n";
        #endif
        #ifndef _GLIBCXX_QUEUE
            std::cout<<true<<"\n";
        #endif
        
        #ifdef _GLIBCXX_ALGORITHM
            std::cout<<false<<"\n";
        #endif
        #ifndef _GLIBCXX_ALGORITHM
            std::cout<<true<<"\n";
        #endif

    }


    return 0;
}
