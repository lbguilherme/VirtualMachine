
#include <syscall.h>

void* heap;
unsigned long heapsize;

int main()
{
    volatile int a = 0b0101;
    volatile int b = 0b1011;
    volatile int c = -52;
    test(a & b, 0b0001);
    test(a | b, 0b1111);
    test(a ^ b, 0b1110);
    test(a << 1, 0b00001010);
    test(a << 2, 0b00010100);
    test(a << 3, 0b00101000);
    test(a << 4, 0b01010000);
    test(a >> 1, 0b00000010);
    test(a >> 2, 0b00000001);
    test(a >> 3, 0b00000000);
    test(a >> 4, 0b00000000);
    test(c >> 2, -13);
    test((unsigned)c >> 2, 1073741811);
    shutdown(0);
}
