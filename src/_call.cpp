
#include <vm.hpp>

void VirtualMachine::_call32(uint32_t arg1)
{
    _push32(eip);
    eip = arg1;
}
