
#include <vm.hpp>

void VirtualMachine::_leave32()
{
    esp = ebp;
    _pop32(ebp);
}
