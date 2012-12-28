
#include <vm.hpp>

void VirtualMachine::_or8(uint8_t arg1, uint8_t& arg2)
{
    asm (
    "orb        %[a], (%[b])\n"
    :
    : [a] "r"(arg1), [b] "r"(&arg2)
    );
    asm (
    "setc       %[CF]\n"
    "seto       %[OF]\n"
    "setz       %[ZF]\n"
    "sets       %[SF]\n"
    "setp       %[PF]\n"
    :
    : [CF] "m"(_CF), [OF] "m"(_OF), [ZF] "m"(_ZF), [SF] "m"(_SF), [PF] "m"(_PF)
    );
}

void VirtualMachine::_or16(uint16_t arg1, uint16_t& arg2)
{
    asm (
    "orw        %[a], (%[b])\n"
    :
    : [a] "r"(arg1), [b] "r"(&arg2)
    );
    asm (
    "setc       %[CF]\n"
    "seto       %[OF]\n"
    "setz       %[ZF]\n"
    "sets       %[SF]\n"
    "setp       %[PF]\n"
    :
    : [CF] "m"(_CF), [OF] "m"(_OF), [ZF] "m"(_ZF), [SF] "m"(_SF), [PF] "m"(_PF)
    );
}

void VirtualMachine::_or32(uint32_t arg1, uint32_t& arg2)
{
    asm (
    "orl        %[a], (%[b])\n"
    :
    : [a] "r"(arg1), [b] "r"(&arg2)
    );
    asm (
    "setc       %[CF]\n"
    "seto       %[OF]\n"
    "setz       %[ZF]\n"
    "sets       %[SF]\n"
    "setp       %[PF]\n"
    :
    : [CF] "m"(_CF), [OF] "m"(_OF), [ZF] "m"(_ZF), [SF] "m"(_SF), [PF] "m"(_PF)
    );
}
