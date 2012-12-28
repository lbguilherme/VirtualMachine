
#include <syscall.h>

void* heap;
unsigned long heapsize;

int main()
{
    const char* volatile str = "str";
    test(0, 0);
    test((long)str, (long)"str");
    test(str[0], 's');
    test(str[1], 't');
    test(str[2], 'r');
    test(str[3], '\0');
    ++str;
    test(str[0], 't');
    test(str[1], 'r');
    test(str[2], '\0');
    shutdown(0);
}
