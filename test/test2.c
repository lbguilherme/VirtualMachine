
#include <syscall.h>

void* heap;
unsigned long heapsize;

int main()
{
    {
        volatile int a = 5;
        volatile int b = 10;
        volatile int c = -5;
        test(a+c, 0);
        test(a+c == 0, 1);
        test(a+b == 15, 1);
        test(-c, a);
        test(b-a, a);
        test(a-c, b);
        test(a < b, 1);
        test(a > b, 0);
        test(a > c, 1);
        test(c < b, 1);
        test(a > a, 0);
        test(a == a, 1);
        test(a != c, 1);
        test(!(a == c), 1);
        test((a+1) >= a, 1);
        test(a <= (a+1), 1);
        test((unsigned)a > (unsigned)c, 0);
    }
    {
        volatile short a = 5;
        volatile short b = 10;
        volatile short c = -5;
        test(a+c, 0);
        test(a+c == 0, 1);
        test(a+b == 15, 1);
        test(-c, a);
        test(b-a, a);
        test(a-c, b);
        test(a < b, 1);
        test(a > b, 0);
        test(a > c, 1);
        test(c < b, 1);
        test(a > a, 0);
        test(a == a, 1);
        test(a != c, 1);
        test(!(a == c), 1);
        test((a+1) >= a, 1);
        test(a <= (a+1), 1);
        test((unsigned)a > (unsigned)c, 0);
    }
    shutdown(0);
}
