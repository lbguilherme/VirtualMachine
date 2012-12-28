
#include <vm.hpp>

void VirtualMachine::_bsf16(uint16_t arg1, uint16_t& arg2)
{
    uint8_t i = 0;
    while (((arg1 >> i) & 1) == 0 && i < 16)
    {
        arg2 = ++i;
    }
    _ZF = (arg1 == 0);
}

void VirtualMachine::_bsf32(uint32_t arg1, uint32_t& arg2)
{
    uint8_t i = 0;
    while (((arg1 >> i) & 1) == 0 && i < 32)
    {
        arg2 = ++i;
    }
    _ZF = (arg1 == 0);
}

void VirtualMachine::_bsr16(uint16_t arg1, uint16_t& arg2)
{
    uint8_t i = 15;
    while (((arg1 >> i) & 1) == 0 && i)
    {
        arg2 = --i;
    }
    _ZF = (arg1 == 0);
}

void VirtualMachine::_bsr32(uint32_t arg1, uint32_t& arg2)
{
    uint8_t i = 31;
    while (((arg1 >> i) & 1) == 0 && i)
    {
        arg2 = --i;
    }
    _ZF = (arg1 == 0);
}
