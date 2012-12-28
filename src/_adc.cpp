
#include <vm.hpp>

void VirtualMachine::_adc8(uint8_t arg1, uint8_t& arg2)
{
    if (_CF)
    {
        asm (
        "stc\n"
        "adcb   %[a], (%[b])\n"
        :
        : [a] "r"(arg1), [b] "r"(&arg2)
        );
    }
    else
    {
        asm (
        "addb   %[a], (%[b])\n"
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

void VirtualMachine::_adc16(uint16_t arg1, uint16_t& arg2)
{
    if (_CF)
    {
        asm (
        "stc\n"
        "adcw   %[a], (%[b])\n"
        :
        : [a] "r"(arg1), [b] "r"(&arg2)
        );
    }
    else
    {
        asm (
        "addw   %[a], (%[b])\n"
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

void VirtualMachine::_adc32(uint32_t arg1, uint32_t& arg2)
{
    if (_CF)
    {
        asm (
        "stc\n"
        "adcl   %[a], (%[b])\n"
        :
        : [a] "r"(arg1), [b] "r"(&arg2)
        );
    }
    else
    {
        asm (
        "addl   %[a], (%[b])\n"
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
