
#include <vm.hpp>

void VirtualMachine::_sbb8(uint8_t arg1, uint8_t& arg2)
{
    if (_CF)
    {
        asm (
        "stc\n"
        "sbbb   %[a], (%[b])\n"
        :
        : [a] "r"(arg1), [b] "r"(&arg2)
        );
    }
    else
    {
        asm (
        "subb   %[a], (%[b])\n"
        :
        : [a] "r"(arg1), [b] "r"(&arg2)
        );
    }
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

void VirtualMachine::_sbb16(uint16_t arg1, uint16_t& arg2)
{
    if (_CF)
    {
        asm (
        "stc\n"
        "sbbw   %[a], (%[b])\n"
        :
        : [a] "r"(arg1), [b] "r"(&arg2)
        );
    }
    else
    {
        asm (
        "subw   %[a], (%[b])\n"
        :
        : [a] "r"(arg1), [b] "r"(&arg2)
        );
    }
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

void VirtualMachine::_sbb32(uint32_t arg1, uint32_t& arg2)
{
    if (_CF)
    {
        asm (
        "stc\n"
        "sbbl   %[a], (%[b])\n"
        :
        : [a] "r"(arg1), [b] "r"(&arg2)
        );
    }
    else
    {
        asm (
        "subl   %[a], (%[b])\n"
        :
        : [a] "r"(arg1), [b] "r"(&arg2)
        );
    }
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
