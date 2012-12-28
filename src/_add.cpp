
#include <vm.hpp>

void VirtualMachine::_add8(uint8_t arg1, uint8_t& arg2)
{
    _CF = 0;
    _adc8(arg1, arg2);
}

void VirtualMachine::_add16(uint16_t arg1, uint16_t& arg2)
{
    _CF = 0;
    _adc16(arg1, arg2);
}

void VirtualMachine::_add32(uint32_t arg1, uint32_t& arg2)
{
    _CF = 0;
    _adc32(arg1, arg2);
}
