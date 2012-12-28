
#include <vm.hpp>

void VirtualMachine::_inc8(uint8_t& arg1)
{
    _add8(1, arg1);
}

void VirtualMachine::_inc16(uint16_t& arg1)
{
    _add16(1, arg1);
}

void VirtualMachine::_inc32(uint32_t& arg1)
{
    _add32(1, arg1);
}
