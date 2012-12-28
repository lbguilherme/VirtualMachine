
#include <vm.hpp>

void VirtualMachine::_pop8(uint8_t& arg1)
{
    arg1 = mem<uint8_t>(toNative(esp));
    esp = fromNative(toNative(esp) + 1);
}

void VirtualMachine::_pop16(uint16_t& arg1)
{
    arg1 = mem<uint16_t>(toNative(esp));
    esp = fromNative(toNative(esp) + 2);
}

void VirtualMachine::_pop32(uint32_t& arg1)
{
    arg1 = mem<uint32_t>(toNative(esp));
    esp = fromNative(toNative(esp) + 4);
}
