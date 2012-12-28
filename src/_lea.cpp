
#include <vm.hpp>

void VirtualMachine::_lea8(uint8_t& arg1, uint32_t& arg2)
{
    arg2 = fromNative((char*)&arg1 - (char*)memory);
}

void VirtualMachine::_lea16(uint16_t& arg1, uint32_t& arg2)
{
    arg2 = fromNative((char*)&arg1 - (char*)memory);
}

void VirtualMachine::_lea32(uint32_t& arg1, uint32_t& arg2)
{
    arg2 = fromNative((char*)&arg1 - (char*)memory);
}
