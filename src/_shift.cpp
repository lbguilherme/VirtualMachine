
#include <vm.hpp>

void VirtualMachine::_sal8(uint8_t arg1, uint8_t& arg2)
{
    if (arg1 == 0) return;
    asm (
    "salb       %[a], (%[b])\n"
    :
    : [a] "c"(arg1), [b] "r"(&arg2)
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

void VirtualMachine::_sal16(uint8_t arg1, uint16_t& arg2)
{
    if (arg1 == 0) return;
    asm (
    "salw       %[a], (%[b])\n"
    :
    : [a] "c"(arg1), [b] "r"(&arg2)
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

void VirtualMachine::_sal32(uint8_t arg1, uint32_t& arg2)
{
    if (arg1 == 0) return;
    asm (
    "sall       %[a], (%[b])\n"
    :
    : [a] "c"(arg1), [b] "r"(&arg2)
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

void VirtualMachine::_sar8(uint8_t arg1, uint8_t& arg2)
{
    if (arg1 == 0) return;
    asm (
    "sarb       %[a], (%[b])\n"
    :
    : [a] "c"(arg1), [b] "r"(&arg2)
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

void VirtualMachine::_sar16(uint8_t arg1, uint16_t& arg2)
{
    if (arg1 == 0) return;
    asm (
    "sarw       %[a], (%[b])\n"
    :
    : [a] "c"(arg1), [b] "r"(&arg2)
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

void VirtualMachine::_sar32(uint8_t arg1, uint32_t& arg2)
{
    if (arg1 == 0) return;
    asm (
    "sarl       %[a], (%[b])\n"
    :
    : [a] "c"(arg1), [b] "r"(&arg2)
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

void VirtualMachine::_shl8(uint8_t arg1, uint8_t& arg2)
{
    if (arg1 == 0) return;
    asm (
    "shlb       %[a], (%[b])\n"
    :
    : [a] "c"(arg1), [b] "r"(&arg2)
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

void VirtualMachine::_shl16(uint8_t arg1, uint16_t& arg2)
{
    if (arg1 == 0) return;
    asm (
    "shlw       %[a], (%[b])\n"
    :
    : [a] "c"(arg1), [b] "r"(&arg2)
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

void VirtualMachine::_shl32(uint8_t arg1, uint32_t& arg2)
{
    if (arg1 == 0) return;
    asm (
    "shll       %[a], (%[b])\n"
    :
    : [a] "c"(arg1), [b] "r"(&arg2)
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

void VirtualMachine::_shr8(uint8_t arg1, uint8_t& arg2)
{
    if (arg1 == 0) return;
    asm (
    "shrb       %[a], (%[b])\n"
    :
    : [a] "c"(arg1), [b] "r"(&arg2)
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

void VirtualMachine::_shr16(uint8_t arg1, uint16_t& arg2)
{
    if (arg1 == 0) return;
    asm (
    "shrw       %[a], (%[b])\n"
    :
    : [a] "c"(arg1), [b] "r"(&arg2)
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

void VirtualMachine::_shr32(uint8_t arg1, uint32_t& arg2)
{
    if (arg1 == 0) return;
    asm (
    "shrl       %[a], (%[b])\n"
    :
    : [a] "c"(arg1), [b] "r"(&arg2)
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

void VirtualMachine::_sal8(uint8_t& arg1)
{
    if (arg1 == 0) return;
    asm (
    "salb       (%[a])\n"
    :
    : [a] "r"(&arg1)
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

void VirtualMachine::_sal16(uint16_t& arg1)
{
    if (arg1 == 0) return;
    asm (
    "salw       (%[a])\n"
    :
    : [a] "r"(&arg1)
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

void VirtualMachine::_sal32(uint32_t& arg1)
{
    if (arg1 == 0) return;
    asm (
    "sall       (%[a])\n"
    :
    : [a] "r"(&arg1)
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

void VirtualMachine::_sar8(uint8_t& arg1)
{
    if (arg1 == 0) return;
    asm (
    "sarb       (%[a])\n"
    :
    : [a] "r"(&arg1)
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

void VirtualMachine::_sar16(uint16_t& arg1)
{
    if (arg1 == 0) return;
    asm (
    "sarw       (%[a])\n"
    :
    : [a] "r"(&arg1)
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

void VirtualMachine::_sar32(uint32_t& arg1)
{
    if (arg1 == 0) return;
    asm (
    "sarl       (%[a])\n"
    :
    : [a] "r"(&arg1)
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

void VirtualMachine::_shl8(uint8_t& arg1)
{
    if (arg1 == 0) return;
    asm (
    "shlb       (%[a])\n"
    :
    : [a] "r"(&arg1)
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

void VirtualMachine::_shl16(uint16_t& arg1)
{
    if (arg1 == 0) return;
    asm (
    "shlw       (%[a])\n"
    :
    : [a] "r"(&arg1)
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

void VirtualMachine::_shl32(uint32_t& arg1)
{
    if (arg1 == 0) return;
    asm (
    "shll       (%[a])\n"
    :
    : [a] "r"(&arg1)
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

void VirtualMachine::_shr8(uint8_t& arg1)
{
    if (arg1 == 0) return;
    asm (
    "shrb       (%[a])\n"
    :
    : [a] "r"(&arg1)
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

void VirtualMachine::_shr16(uint16_t& arg1)
{
    if (arg1 == 0) return;
    asm (
    "shrw       (%[a])\n"
    :
    : [a] "r"(&arg1)
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

void VirtualMachine::_shr32(uint32_t& arg1)
{
    if (arg1 == 0) return;
    asm (
    "shrl       (%[a])\n"
    :
    : [a] "r"(&arg1)
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
