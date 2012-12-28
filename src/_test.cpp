
#include <vm.hpp>

void VirtualMachine::_test8(uint8_t arg1, uint8_t arg2)
{
    _and8(arg1, arg2);
}

void VirtualMachine::_test16(uint16_t arg1, uint16_t arg2)
{
    _and16(arg1, arg2);
}

void VirtualMachine::_test32(uint32_t arg1, uint32_t arg2)
{
    _and32(arg1, arg2);
}
