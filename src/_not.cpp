
#include <vm.hpp>

void VirtualMachine::_not8(uint8_t& arg1)
{
    arg1 = ~arg1;
}

void VirtualMachine::_not16(uint16_t& arg1)
{
    arg1 = ~arg1;
}

void VirtualMachine::_not32(uint32_t& arg1)
{
    arg1 = ~arg1;
}
