
#include <vm.hpp>

void VirtualMachine::_movs8()
{
    mem<uint8_t>(toNative(edi)) = mem<uint8_t>(toNative(esi));
    esi = fromNative(toNative(esi) + (_DF ? 1 : -1));
    edi = fromNative(toNative(edi) + (_DF ? 1 : -1));
}

void VirtualMachine::_movs16()
{
    mem<uint16_t>(toNative(edi)) = mem<uint16_t>(toNative(esi));
    esi = fromNative(toNative(esi) + (_DF ? 2 : -2));
    edi = fromNative(toNative(edi) + (_DF ? 2 : -2));
}

void VirtualMachine::_movs32()
{
    mem<uint32_t>(toNative(edi)) = mem<uint32_t>(toNative(esi));
    esi = fromNative(toNative(esi) + (_DF ? 4 : -4));
    edi = fromNative(toNative(edi) + (_DF ? 4 : -4));
}

void VirtualMachine::_rep_movs8()
{
    uint32_t times = toNative(ecx);
    for (; times > 0; --times)
    {
        clocks += 2;
        _movs8();
    }
}

void VirtualMachine::_rep_movs16()
{
    uint32_t times = toNative(ecx);
    for (; times > 0; --times)
    {
        clocks += 2;
        _movs16();
    }
}

void VirtualMachine::_rep_movs32()
{
    uint32_t times = toNative(ecx);
    for (; times > 0; --times)
    {
        clocks += 2;
        _movs32();
    }
}
