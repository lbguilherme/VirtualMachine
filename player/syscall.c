
#include <syscall.h>

static long syscall(long, long, long, long, long, long) __attribute__((noinline));
static long syscall(long id, long arg1, long arg2, long arg3, long arg4, long arg5)
{
    asm volatile ("int\t$0" ::
                  "a"(id), "b"(arg1), "c"(arg2), "d"(arg3), "S"(arg4), "D"(arg5));
}

void print(const char* message)
{
    syscall(0x0000, (long)message, 0, 0, 0, 0);
}

void shutdown(long status)
{
    syscall(0x0001, status, 0, 0, 0, 0);
}

void test(long a, long b)
{
    syscall(0x0002, a, b, 0, 0, 0);
}
