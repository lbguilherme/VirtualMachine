
#include <vm.hpp>

void VirtualMachine::_cmp8(uint8_t arg1, uint8_t arg2)
{
    _sub8(arg1, arg2);
}

void VirtualMachine::_cmp16(uint16_t arg1, uint16_t arg2)
{
    _sub16(arg1, arg2);
}

void VirtualMachine::_cmp32(uint32_t arg1, uint32_t arg2)
{
    _sub32(arg1, arg2);
}
