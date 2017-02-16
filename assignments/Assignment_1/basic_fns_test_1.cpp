// Test code to check :
// 1. push_back
// 2. push_front
// 3. pop_front
// 4. front
// 5. back
// 6. at
// 7. ctor
// 8. dtor
// 9. size
// 10 .empty

#include <dlfcn.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <random>
#include <unistd.h>
#include "Deque.hpp"
#include<iostream>

bool
char_less(const char &o1, const char &o2) {
    return o1 < o2;
}
Deque_DEFINE(char)

int
main() {

    {
        Deque_char deq;
        Deque_char_ctor(&deq, char_less);

        assert(deq.size(&deq) == 0);
        assert(deq.empty(&deq));

        printf("%s\n", deq.type_name);
        assert(sizeof deq.type_name == 11);

        deq.push_back(&deq, 'c');

        assert(!deq.empty(&deq));

        deq.push_back(&deq, 'd');
        deq.push_back(&deq, 'e');
        deq.push_front(&deq, 'b');
        deq.push_front(&deq, 'a');

        assert(deq.front(&deq) == 'a');
        assert(deq.back(&deq) == 'e');

        deq.pop_front(&deq);
        deq.pop_back(&deq);
        assert(deq.front(&deq) == 'b');

        assert(deq.back(&deq) == 'd');

        assert(deq.size(&deq) == 3);

        for (size_t i = 0; i < 3; i++) {
            char temp = deq.at(&deq,i);
            assert(int(temp) == 98+i);
        }

        deq.clear(&deq);
        deq.dtor(&deq);
    }

}

