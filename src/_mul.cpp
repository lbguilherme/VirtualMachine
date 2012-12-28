
#include <vm.hpp>

void VirtualMachine::_mul8(uint8_t& arg1)
{
    uint16_t op1 = toNative(al);
    uint16_t op2 = toNative(arg1);
    ax = fromNative(op1 * op2);
}

void VirtualMachine::_mul16(uint16_t& arg1)
{
    uint32_t op1 = toNative(ax);
    uint32_t op2 = toNative(arg1);
    uint32_t r = op1 * op2;
    ax = fromNative((uint16_t)r);
    dx = fromNative((uint16_t)(r >> 16));
}

void VirtualMachine::_mul32(uint32_t& arg1)
{
    uint64_t op1 = toNative(eax);
    uint64_t op2 = toNative(arg1);
    uint64_t r = op1 * op2;
    eax = fromNative((uint32_t)r);
    edx = fromNative((uint32_t)(r >> 16));
}

void VirtualMachine::_imul8(uint8_t& arg1)
{
    int16_t op1 = toNative((int8_t&)al);
    int16_t op2 = toNative((int8_t&)arg1);
    (int16_t&)ax = fromNative(op1 * op2);
}

void VirtualMachine::_imul16(uint16_t& arg1)
{
    int32_t op1 = toNative((int16_t&)ax);
    int32_t op2 = toNative((int16_t&)arg1);
    int32_t r = op1 * op2;
    (int16_t&)ax = fromNative((int16_t)r);
    (int16_t&)dx = fromNative((int16_t)(r >> 16));
}

void VirtualMachine::_imul32(uint32_t& arg1)
{
    int64_t op1 = toNative((int32_t&)eax);
    int64_t op2 = toNative((int32_t&)arg1);
    int64_t r = op1 * op2;
    (int32_t&)eax = fromNative((int32_t)r);
    (int32_t&)edx = fromNative((int32_t)(r >> 16));
}

void VirtualMachine::_imul8(uint8_t& arg1, uint8_t& arg2)
{
    (int8_t&)arg2 = fromNative(toNative((int8_t&)arg1) * toNative((int8_t&)arg2));
}

void VirtualMachine::_imul16(uint16_t& arg1, uint16_t& arg2)
{
    (int16_t&)arg2 = fromNative(toNative((int16_t&)arg1) * toNative((int16_t&)arg2));
}

void VirtualMachine::_imul32(uint32_t& arg1, uint32_t& arg2)
{
    (int32_t&)arg2 = fromNative(toNative((int32_t&)arg1) * toNative((int32_t&)arg2));
}

void VirtualMachine::_imul8(uint8_t& arg1, uint8_t& arg2, uint8_t arg3)
{
    (int8_t&)arg2 = fromNative(toNative((int8_t&)arg1) * toNative((int8_t&)arg3));
}

void VirtualMachine::_imul16(uint16_t& arg1, uint16_t& arg2, uint16_t arg3)
{
    (int16_t&)arg2 = fromNative(toNative((int16_t&)arg1) * toNative((int16_t&)arg3));
}

void VirtualMachine::_imul32(uint32_t& arg1, uint32_t& arg2, uint32_t arg3)
{
    (int32_t&)arg2 = fromNative(toNative((int32_t&)arg1) * toNative((int32_t&)arg3));
}
