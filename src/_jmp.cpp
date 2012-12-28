
#include <vm.hpp>

void VirtualMachine::_jmp32(uint32_t arg1)
{
    eip = arg1;
}

void VirtualMachine::_jcc32(bool cc, uint32_t arg1)
{
    if (cc)
        eip = arg1;
}
