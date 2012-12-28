
#include <vm.hpp>

void VirtualMachine::_ret32()
{
    _pop32(eip);
}
