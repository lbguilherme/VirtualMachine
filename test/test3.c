
#include <syscall.h>

void* heap;
unsigned long heapsize;

int main()
{
    volatile int a[] = {1, 2, 3};
    volatile short b[2][2] = {{1, 2}, {3, 4}};
    volatile char str[] = {'s', 't', 'r', '\0'};
    test(a[0], 1);
    test(a[1], 2);
    test(a[2], 3);
    test(b[0][0], 1);
    test(b[0][1], 2);
    test(b[1][0], 3);
    test(b[1][1], 4);
    test(str[0], 's');
    test(str[1], 't');
    test(str[2], 'r');
    test(str[3], '\0');
    test(a[0]+b[0][0], 2);
    test(a[0]-b[0][0], 0);
    test(a[0]-(unsigned char)(b[0][0]), 0);
    shutdown(0);
}
