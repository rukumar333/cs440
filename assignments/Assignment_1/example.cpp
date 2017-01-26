#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Array_DEFINE(t)                                                        \
    struct Array_##t {                                                         \
        t data[10];                                                            \
        t &(*at)(Array_##t *, int i);                                          \
        void (*delet)(Array_##t *);                                            \
    };                                                                         \
    t &Array_##t##_at(Array_##t *ap, int i) {                                  \
        assert(i < 10);                                                        \
        return ap->data[i];                                                    \
    }                                                                          \
    void Array_##t##_delete(Array_##t *ap) {                                   \
        free(ap);                                                              \
    }                                                                          \
    Array_##t *Array_##t##_new() {                                             \
        Array_##t *ap = (Array_##t *) malloc(sizeof(Array_##t));               \
        ap->at = &Array_##t##_at;                                              \
        ap->delet = &Array_##t##_delete;                                       \
        return ap;                                                             \
    }

Array_DEFINE(int)
struct MyClass {
    char str[20];
};
Array_DEFINE(MyClass)

int main() {

    Array_int *a1 = Array_int_new();
    a1->at(a1, 0) = 1234;
    printf("%d\n", a1->at(a1, 0));
    // a1->at(10) = 1234; // Will assert.
    a1->delet(a1);

    Array_MyClass *a2 = Array_MyClass_new();
    strcpy(a2->at(a2, 0).str, "John");
    printf("%s\n", a2->at(a2, 0).str);
    a2->delet(a2);
}
    
