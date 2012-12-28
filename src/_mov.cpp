
#include <vm.hpp>

void VirtualMachine::_mov8(uint8_t arg1, uint8_t& arg2)
{
    arg2 = arg1;
}

void VirtualMachine::_mov16(uint16_t arg1, uint16_t& arg2)
{
    arg2 = arg1;
}

void VirtualMachine::_mov32(uint32_t arg1, uint32_t& arg2)
{
    arg2 = arg1;
}

void VirtualMachine::_movsb16(uint8_t arg1, uint16_t& arg2)
{
    (int16_t&)arg2 = (int8_t&)arg1;
}

void VirtualMachine::_movsb32(uint8_t arg1, uint32_t& arg2)
{
    (int32_t&)arg2 = (int8_t&)arg1;
}

void VirtualMachine::_movsw32(uint16_t arg1, uint32_t& arg2)
{
    (int32_t&)arg2 = (int16_t&)arg1;
}

void VirtualMachine::_movzb16(uint8_t arg1, uint16_t& arg2)
{
    arg2 = arg1;
}

void VirtualMachine::_movzb32(uint8_t arg1, uint32_t& arg2)
{
    arg2 = arg1;
}

void VirtualMachine::_movzw32(uint16_t arg1, uint32_t& arg2)
{
    arg2 = arg1;
}
