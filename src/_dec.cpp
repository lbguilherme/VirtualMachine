
#include <vm.hpp>

void VirtualMachine::_dec8(uint8_t& arg1)
{
    _sub8(1, arg1);
}

void VirtualMachine::_dec16(uint16_t& arg1)
{
    _sub16(1, arg1);
}

void VirtualMachine::_dec32(uint32_t& arg1)
{
    _sub32(1, arg1);
}
