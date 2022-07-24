#include <stdio.h>

int main(void) {
    int i = 1;
    const int * a = &i; //指针 => const int
    int * const b = &i; //const 指针 => int
    printf("a: %d\n", *a);
    printf("b: %d\n", *b);
    return 0;
}
