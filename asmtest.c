
#include <syscall.h>

void* heap;
unsigned long heapsize;

int main()
{
    volatile long long a = 102;
    volatile long long b = 5;
    shutdown(a%b);
}
