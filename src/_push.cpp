
#include <vm.hpp>

void VirtualMachine::_push8(uint8_t arg1)
{
    esp = fromNative(toNative(esp) - 1);
    mem<uint8_t>(toNative(esp)) = arg1;
}

void VirtualMachine::_push16(uint16_t arg1)
{
    esp = fromNative(toNative(esp) - 2);
    mem<uint16_t>(toNative(esp)) = arg1;
}

void VirtualMachine::_push32(uint32_t arg1)
{
    esp = fromNative(toNative(esp) - 4);
    mem<uint32_t>(toNative(esp)) = arg1;
}
