
#include <vm.hpp>

void VirtualMachine::_div8(uint8_t& arg1)
{
    uint16_t op1 = toNative(ax);
    uint16_t op2 = toNative(arg1);
    al = fromNative(op1 / op2);
    ah = fromNative(op1 % op2);
}

void VirtualMachine::_div16(uint16_t& arg1)
{
    uint32_t op1 = ((uint32_t)toNative(dx) << 16) + toNative(ax);
    uint32_t op2 = toNative((int16_t&)arg1);
    ax = fromNative(op1 / op2);
    dx = fromNative(op1 % op2);
}

void VirtualMachine::_div32(uint32_t& arg1)
{
    uint64_t op1 = ((uint64_t)toNative(edx) << 32) + toNative(eax);
    uint64_t op2 = toNative(arg1);
    eax = fromNative(op1 / op2);
    edx = fromNative(op1 % op2);
}

void VirtualMachine::_idiv8(uint8_t& arg1)
{
    int16_t op1 = toNative((int16_t&)ax);
    int16_t op2 = toNative((int8_t&)arg1);
    al = fromNative((uint8_t)(op1 / op2));
    ah = fromNative((uint8_t)(op1 % op2));
}

void VirtualMachine::_idiv16(uint16_t& arg1)
{
    int32_t op1 = ((int32_t)toNative((int16_t&)dx) << 16) + toNative((int16_t&)ax);
    int32_t op2 = toNative((int16_t&)arg1);
    ax = fromNative((uint16_t)(op1 / op2));
    dx = fromNative((uint16_t)(op1 % op2));
}

void VirtualMachine::_idiv32(uint32_t& arg1)
{
    int64_t op1 = ((int64_t)toNative((int32_t&)edx) << 32) + toNative((int32_t&)eax);
    int64_t op2 = toNative((int32_t&)arg1);
    eax = fromNative((uint32_t)(op1 / op2));
    edx = fromNative((uint32_t)(op1 % op2));
}
