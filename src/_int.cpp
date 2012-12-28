
#include <string>
#include <stdexcept>

#include <vm.hpp>

void VirtualMachine::_int32(uint32_t)
{
    uint32_t syscall = toNative(eax);

    if (m_syscall.find(syscall) == m_syscall.end())
        throw std::runtime_error("Invalid system call code: " + std::to_string(syscall));

    int32_t arg1 = toNative((int32_t&)ebx);
    int32_t arg2 = toNative((int32_t&)ecx);
    int32_t arg3 = toNative((int32_t&)edx);
    int32_t arg4 = toNative((int32_t&)esi);
    int32_t arg5 = toNative((int32_t&)edi);

    eax = fromNative(m_syscall[syscall](arg1, arg2, arg3, arg4, arg5));
}
