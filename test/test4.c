
#include <syscall.h>

void* heap;
unsigned long heapsize;

int main()
{
    {
        volatile int a = 7;
        volatile int b = 9;
        test(b/b, 1);
        test(a*b, 63);
        test(a*a < a*b, 1);
        test(a/b, 0);
        test(b/a, 1);
        test(b%a, 2);
        test(a*b/b, a);
        test(2*a, 14);
        test(3*a, 21);
        test(b/-2, -4);
        test(b%8, 1);
    }
    {
        volatile unsigned a = 7;
        volatile unsigned b = 9;
        test(b/b, 1);
        test(a*b, 63);
        test(a*a < a*b, 1);
        test(a/b, 0);
        test(b/a, 1);
        test(b%a, 2);
        test(a*b/b, a);
        test(2*a, 14);
        test(3*a, 21);
        test(b/-2, 0); // Why is this zero??
        test(b%8, 1);
    }
    {
        volatile short a = 7;
        volatile short b = 9;
        test(b/b, 1);
        test(a*b, 63);
        test(a*a < a*b, 1);
        test(a/b, 0);
        test(b/a, 1);
        test(b%a, 2);
        test(a*b/b, a);
        test(2*a, 14);
        test(3*a, 21);
        test(b/-2, -4);
        test(b%8, 1);
    }
    shutdown(0);
}
