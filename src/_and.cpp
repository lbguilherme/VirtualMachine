
#include <vm.hpp>

void VirtualMachine::_and8(uint8_t arg1, uint8_t& arg2)
{
    asm (
    "andb       %[a], (%[b])\n"
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

void VirtualMachine::_and16(uint16_t arg1, uint16_t& arg2)
{
    asm (
    "andw       %[a], (%[b])\n"
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

void VirtualMachine::_and32(uint32_t arg1, uint32_t& arg2)
{
    asm (
    "andl       %[a], (%[b])\n"
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
