
#include <vm.hpp>

void VirtualMachine::_cbtw8()
{
    (int16_t&)ax = fromNative((int16_t)toNative((int8_t&)al));
}

void VirtualMachine::_cwtl16()
{
    (int32_t&)eax = fromNative((int32_t)toNative((int16_t&)ax));
}

void VirtualMachine::_cwtd16()
{
    int32_t value = toNative((int16_t&)ax);
    (int16_t&)dx = fromNative((int16_t)(value >> 16));
    (int16_t&)ax = fromNative((int16_t)value);
}

void VirtualMachine::_cltd32()
{
    int64_t value = toNative((int32_t&)eax);
    (int32_t&)edx = fromNative((int32_t)(value >> 32));
    (int32_t&)eax = fromNative((int32_t)value);
}
