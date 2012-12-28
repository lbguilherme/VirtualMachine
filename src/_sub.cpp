
#include <vm.hpp>

void VirtualMachine::_sub8(uint8_t arg1, uint8_t& arg2)
{
    _CF = 0;
    _sbb8(arg1, arg2);
}

void VirtualMachine::_sub16(uint16_t arg1, uint16_t& arg2)
{
    _CF = 0;
    _sbb16(arg1, arg2);
}

void VirtualMachine::_sub32(uint32_t arg1, uint32_t& arg2)
{
    _CF = 0;
    _sbb32(arg1, arg2);
}
