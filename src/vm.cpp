
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <new>
#include <vector>
#include <functional>
#include <type_traits>
#include <stdexcept>

#include <vm.hpp>

using namespace std;

#ifndef NDEBUG
static const char* regname[] = {"",
"%eax", "%ebx", "%ecx", "%edx", "%esi", "%edi", "%esp", "%ebp",
 "%ax",  "%bx",  "%cx",  "%dx",  "%si",  "%di",  "%sp",  "%bp",
 "%ah",  "%bh",  "%ch",  "%dh",  "__",  "__",  "__",  "__",
 "%al",  "%bl",  "%cl",  "%dl",  "__",  "__",  "__",  "__"};
#endif

VirtualMachine::VirtualMachine(unsigned memory_size) :
    ax(*(uint16_t*)&eax), bx(*(uint16_t*)&ebx), cx(*(uint16_t*)&ecx), dx(*(uint16_t*)&edx),
    si(*(uint16_t*)&esi), di(*(uint16_t*)&edi), sp(*(uint16_t*)&esp), bp(*(uint16_t*)&ebp),
    ah(*((uint8_t*)&eax+1)), bh(*((uint8_t*)&ebx+1)),
    ch(*((uint8_t*)&ecx+1)), dh(*((uint8_t*)&edx+1)),
    al(*(uint8_t*)&eax), bl(*(uint8_t*)&ebx), cl(*(uint8_t*)&ecx), dl(*(uint8_t*)&edx)
{
    memorySize = memory_size;
    memory = operator new(memorySize);
    clocks = 0;
}

VirtualMachine::~VirtualMachine()
{
    operator delete(memory);
}

void VirtualMachine::exec(const string& filename)
{
    memset(memory, '\0', memorySize);
    fstream file(filename, ios_base::in);
    unsigned mem = 1;

    char header[] = ".............";
    file.read(header, sizeof(header)-1);
    if (file.eof() or string(header) != ".DRONEWARBIN.")
    { throw runtime_error("Invalid executable."); }

    uint32_t rodatalen;
    file.read((char*)&rodatalen, 4);
    if (file.eof()) { throw runtime_error("Corrupted executable."); }
    rodatalen = toNative(rodatalen);
    if (mem+rodatalen > memorySize) { throw runtime_error("Executable is bigger than memory."); }
    file.read((char*)memory+mem, rodatalen);
    mem += rodatalen;
    if (file.eof()) { throw runtime_error("Corrupted executable."); }

    uint32_t textlen;
    file.read((char*)&textlen, 4);
    if (file.eof()) { throw runtime_error("Corrupted executable."); }
    textlen = toNative(textlen);
    if (mem+textlen > memorySize) { throw runtime_error("Executable is bigger than memory."); }
    file.read((char*)memory+mem, textlen);
    mem += textlen;
    if (file.eof()) { throw runtime_error("Corrupted executable."); }

    uint32_t datalen;
    file.read((char*)&datalen, 4);
    if (file.eof()) { throw runtime_error("Corrupted executable."); }
    datalen = toNative(datalen);
    if (mem+datalen > memorySize) { throw runtime_error("Executable is bigger than memory."); }
    file.read((char*)memory+mem, datalen);
    mem += datalen;
    if (file.eof()) { throw runtime_error("Corrupted executable."); }

    uint32_t staticlen;
    file.read((char*)&staticlen, 4);
    if (file.eof()) { throw runtime_error("Corrupted executable."); }
    staticlen = toNative(staticlen);
    if (mem+staticlen > memorySize) { throw runtime_error("Executable is bigger than memory."); }
    mem += staticlen;

    uint16_t symbolcount;
    file.read((char*)&symbolcount, 2);
    if (file.eof()) { throw runtime_error("Corrupted executable."); }
    symbolcount = toNative(symbolcount);

    for (unsigned i = 0; i < symbolcount; ++i)
    {
        uint16_t namelen;
        file.read((char*)&namelen, 2);
        if (file.eof()) { throw runtime_error("Corrupted executable."); }
        namelen = toNative(namelen);

        char* name = (char*)malloc(namelen);
        file.read(name, namelen);
        if (file.eof()) { throw runtime_error("Corrupted executable."); }

        uint32_t value;
        file.read((char*)&value, 4);
        if (file.eof()) { throw runtime_error("Corrupted executable."); }
        value = toNative(value);

        m_symboltable[string(name, namelen)] = value;
        free(name);
    }

    this->mem<uint32_t>(sym("heap")) = fromNative(mem);
    this->mem<uint32_t>(sym("heapsize")) = 0;
    
    heap = mem;
    heapSizeGVar = sym("heapsize");

#ifndef NDEBUG
    cout << filename << ":" << endl;
    cout << " rodata: " << rodatalen << " bytes" << endl;
    cout << " text: " << textlen << " bytes" << endl;
    cout << " data: " << datalen << " bytes" << endl;
    cout << " static: " << staticlen << " bytes" << endl;
    cout << " heap: " << (void*)fromNative(mem) << endl;
    cout << " symbols: " << m_symboltable.size() << endl;

    for (const pair<string, uint32_t>& sym : m_symboltable)
    {
        cout << "  " << sym.first << " = " << sym.second << endl;
    }
#endif
    //printMemory();
}

void VirtualMachine::call(const string& func)
{
    eip = fromNative(m_symboltable[func]);
    eax = 0;
    ebx = 0;
    ecx = 0;
    edx = 0;
    esi = 0;
    edi = 0;
    esp = fromNative(memorySize);
    ebp = 0;
    _OF = false;
    _CF = false;
    _ZF = false;
    _SF = false;
    _PF = false;
    _DF = true;
}

vector<string> VirtualMachine::symbols() const
{
    vector<string> list;
    for (const pair<string, uint32_t>& sym : m_symboltable)
        list.push_back(sym.first);
    return list;
}

void VirtualMachine::executeNext()
{
    runInstruction();

    //printMemory();
    
    if (heap + heapSize() >= toNative(esp))
        throw runtime_error("Stack Overflow");
}

void VirtualMachine::setSystemCall(uint32_t id, const syscall_t& syscall)
{
    m_syscall[id] = syscall;
}

void VirtualMachine::printMemory()
{
    cout << endl;
    cout << "\t    %pc = " << hex << setfill('0') << setw(8) << eip;
    cout << " (" << dec << eip << ")" << endl << endl;

    for (unsigned i = 0; i < memorySize; i += 32)
    {
        cout << "\t";
        for (unsigned j = 0; j < 32; ++j)
        {
            if (j % 4 == 0) cout << " ";
            if (i+j < memorySize)
                cout << hex << setfill('0') << setw(2) << (int)((unsigned char*)memory)[i+j];
            else
                cout << "  ";
        }
        cout << "    ";
        for (unsigned j = 0; j < 32; ++j)
        {
            if (i+j < memorySize)
            {
                char c = ((char*)memory)[i+j];
                if (isprint(c)) cout << c;
                else cout << '.';
            }
        }
        cout << endl;
    }

    cout << endl;
    cout << "\t   %eax = " << hex << setfill('0') << setw(8) << eax;
    cout << "   %ebx = " << hex << setfill('0') << setw(8) << ebx;
    cout << "   %ecx = " << hex << setfill('0') << setw(8) << ecx;
    cout << "   %edx = " << hex << setfill('0') << setw(8) << edx << endl;
    cout << "\t   %esi = " << hex << setfill('0') << setw(8) << esi;
    cout << "   %edi = " << hex << setfill('0') << setw(8) << edi;
    cout << "   %esp = " << hex << setfill('0') << setw(8) << esp;
    cout << "   %ebp = " << hex << setfill('0') << setw(8) << ebp << endl;
    cout << endl;
    cout << dec;
}

template<>
uint32_t& VirtualMachine::reg<uint32_t>(uint8_t reg)
{
    switch (reg)
    {
        case 1: return eax;
        case 2: return ebx;
        case 3: return ecx;
        case 4: return edx;
        case 5: return esi;
        case 6: return edi;
        case 7: return esp;
        case 8: return ebp;
    }
    
    static uint32_t zero;
    zero = 0;
    return zero;
}

template<>
uint16_t& VirtualMachine::reg<uint16_t>(uint8_t reg)
{
    switch (reg)
    {
        case 9: return (uint16_t&)eax;
        case 10: return (uint16_t&)ebx;
        case 11: return (uint16_t&)ecx;
        case 12: return (uint16_t&)edx;
        case 13: return (uint16_t&)esi;
        case 14: return (uint16_t&)edi;
        case 15: return (uint16_t&)esp;
        case 16: return (uint16_t&)ebp;
    }
    
    static uint16_t zero;
    zero = 0;
    return zero;
}

template<>
uint8_t& VirtualMachine::reg<uint8_t>(uint8_t reg)
{
    switch (reg)
    {
        case 17: return *((uint8_t*)&eax+1);
        case 18: return *((uint8_t*)&ebx+1);
        case 19: return *((uint8_t*)&ecx+1);
        case 20: return *((uint8_t*)&edx+1);
        case 25: return (uint8_t&)eax;
        case 26: return (uint8_t&)ebx;
        case 27: return (uint8_t&)ecx;
        case 28: return (uint8_t&)edx;
    }
    
    static uint8_t zero;
    zero = 0;
    return zero;
}

template<typename T>
T& VirtualMachine::readRegister()
{
    uint8_t r = mem<uint8_t>(toNative(eip));
    eip = fromNative(toNative(eip) + 1);
#ifndef NDEBUG
    clog << regname[(int)r];
#endif
    return reg<T>(r);
}

template <typename T>
T& VirtualMachine::readMemory()
{
    clocks += 3;
    int32_t offset = mem<int32_t>(toNative(eip));
    eip = fromNative(toNative(eip) + 4);
    uint16_t data = toNative(mem<uint16_t>(toNative(eip)));
    eip = fromNative(toNative(eip) + 2);
    uint8_t base = data >> 9;
    uint8_t index = (data >> 2) & 0b1111111;
    uint8_t scale = data & 0b11;
#ifndef NDEBUG
    if (offset) clog << toNative(offset);
    if (base||index||scale)
    {
        clog << "(";
        if (base||index||scale) clog << regname[(int)base];
        if (index||scale) clog << ", " << regname[(int)index];
        if (scale) clog << "," << (1 << scale);
        clog << ")";
    }
#endif
    return mem<T>(offset + (int32_t&)reg<uint32_t>(base) + ((int32_t&)reg<uint32_t>(index) << scale));
}

template <typename T>
T VirtualMachine::readImmediate()
{
    T value = mem<T>(toNative(eip));
#ifndef NDEBUG
    clog << "$" << (int)toNative((typename make_signed<T>::type&)value);
#endif
    eip = fromNative(toNative(eip) + sizeof(T));
    return value;
}

static inline void setbit(uint32_t& src, uint8_t bit, bool value)
{
    if (value)
    {
        asm (
        "btsl   %[bit], %[src]\n"
        :
        : [src] "m" (src), [bit] "r" ((unsigned)bit)
        );
    }
    else
    {
        asm (
        "btrl   %[bit], %[src]\n"
        :
        : [src] "m" (src), [bit] "r" ((unsigned)bit)
        );
    }
}

static inline bool readbit(uint32_t& src, uint8_t bit)
{
    bool value;
    asm (
    "btl        %[bit], %[src]\n"
    "setc       %[v]\n"
    : [v] "=r" (value)
    : [src] "r" (src), [bit] "r" ((unsigned)bit)
    );
    return value;
}

void VirtualMachine::seteflags()
{
    eflags = 0;
    setbit(eflags, 0, _CF);
    setbit(eflags, 1, true);
    setbit(eflags, 2, _PF);
    //setbit(eflags, 4, _AF);
    setbit(eflags, 6, _ZF);
    setbit(eflags, 7, _SF);
    //setbit(eflags, 8, _TF);
    //setbit(eflags, 9, _IF);
    setbit(eflags, 10, _DF);
    setbit(eflags, 11, _OF);
    //setbit(eflags, 12, ?);
    //setbit(eflags, 13, ?);
    //setbit(eflags, 14, _NT);
    //setbit(eflags, 16, _RF);
    //setbit(eflags, 17, _VM);
    //setbit(eflags, 18, _AC);
    //setbit(eflags, 19, _VIF);
    //setbit(eflags, 20, _VIP);
    //setbit(eflags, 21, _ID);
    eflags = fromNative(eflags);
}

void VirtualMachine::readeflags()
{
    eflags = toNative(eflags);
    _CF = readbit(eflags, 0);
    _PF = readbit(eflags, 2);
    _ZF = readbit(eflags, 6);
    _SF = readbit(eflags, 7);
    _DF = readbit(eflags, 10);
    _OF = readbit(eflags, 11);
    eflags = fromNative(eflags);
}

template uint8_t& VirtualMachine::reg<uint8_t>(uint8_t reg);
template uint16_t& VirtualMachine::reg<uint16_t>(uint8_t reg);
template uint32_t& VirtualMachine::reg<uint32_t>(uint8_t reg);
template uint8_t& VirtualMachine::readRegister<uint8_t>();
template uint16_t& VirtualMachine::readRegister<uint16_t>();
template uint32_t& VirtualMachine::readRegister<uint32_t>();
template uint8_t& VirtualMachine::readMemory<uint8_t>();
template uint16_t& VirtualMachine::readMemory<uint16_t>();
template uint32_t& VirtualMachine::readMemory<uint32_t>();
template uint8_t VirtualMachine::readImmediate<uint8_t>();
template uint16_t VirtualMachine::readImmediate<uint16_t>();
template uint32_t VirtualMachine::readImmediate<uint32_t>();
