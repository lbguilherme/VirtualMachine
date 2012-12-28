#pragma once

#include <cstdint>
#include <map>
#include <string>
#include <vector>
#include <functional>
#include <stdexcept>

/*!
 * A virtual machine capable of running x86 assembly. It allocates it's memory
 * dinamicaly on the constructor.
 */
class VirtualMachine
{
private:
    
    typedef std::function<long(long, long, long, long, long)> syscall_t;

public:

    /*!
     * Initializes the virtual machine and allocates its memory. Unless
     * `std::bad_alloc` be throwed, the state will be set to `NoError`.
     * After construction any function call but `start` leads to undefined behavior.
     * \param memory_size The size of the VM's memory, in bytes. Must be no more
     * than 2GB.
     */
    VirtualMachine(unsigned memory_size);

    /*!
     * Releases the allocated memory.
     */
    ~VirtualMachine();

    /*!
     * Cleans the memory and loads a new executable.
     * \param filename Path to the executable to be loaded
     */
    void exec(const std::string& filename);

    /*!
     * Sets the instruction pointer to `func` and cleans stack. Note that `func`
     * can never return, otherwise stack will underflow.
     * \param func The function name. Instruction pointer will be set to it.
     */
    void call(const std::string& func);

    /*!
     * \return Returns a list of visible global symbols.
     */
    std::vector<std::string> symbols() const;

    /*!
     * Executes the instruction pointed by the instruction pointer and set it to
     * the address of the next instruction.
     */
    void executeNext();

    /*!
     * Defines a function that will be called when the executable calls the
     * system call `id`.
     * \param id The system call id.
     * \param syscall A function corresponding to that system call.
     */
    void setSystemCall(uint32_t id, const syscall_t& syscall);
    
    /*!
     * \return The current size of the stack.
     */
    unsigned stackSize()
    {
        return memorySize - toNative(esp);
    }
    
    /*!
     * \return The current size of the heap.
     */
    unsigned heapSize()
    {
        return toNative(mem<uint32_t>(heapSizeGVar));
    }

public:

    /// The virtual memory.
    void* memory;

    /// The size of the memory (bytes).
    unsigned memorySize;
    
    /// The address of the beginning of the heap.
    unsigned heap;

    /// The number of clocks passed.
    unsigned long long clocks;

    /// The instruction pointer register.
    uint32_t eip;

    /// The accumulator register.
    uint32_t eax;

    /// The base register.
    uint32_t ebx;

    /// The counter register.
    uint32_t ecx;

    /// The data register.
    uint32_t edx;

    /// The source index register.
    uint32_t esi;

    /// The destination index register.
    uint32_t edi;

    /// The stack pointer register.
    uint32_t esp;
    
    /// The stack base pointer register.
    uint32_t ebp;
    
    /// The flags register.
    uint32_t eflags;

    /// The lower 16 bits of the eax register.
    uint16_t& ax;

    /// The lower 16 bits of the ebx register.
    uint16_t& bx;

    /// The lower 16 bits of the ecx register.
    uint16_t& cx;

    /// The lower 16 bits of the edx register.
    uint16_t& dx;

    /// The lower 16 bits of the esi register.
    uint16_t& si;

    /// The lower 16 bits of the edi register.
    uint16_t& di;

    /// The lower 16 bits of the esp register.
    uint16_t& sp;

    /// The lower 16 bits of the ebp register.
    uint16_t& bp;

    /// The higher 8 bits of the ax register.
    uint8_t& ah;

    /// The higher 8 bits of the bx register.
    uint8_t& bh;

    /// The higher 8 bits of the cx register.
    uint8_t& ch;

    /// The higher 8 bits of the dx register.
    uint8_t& dh;

    /// The lower 8 bits of the ax register.
    uint8_t& al;

    /// The lower 8 bits of the bx register.
    uint8_t& bl;

    /// The lower 8 bits of the cx register.
    uint8_t& cl;

    /// The lower 8 bits of the dx register.
    uint8_t& dl;
    
    /// The floating point register stack.
    long double st[8];
    
    /// The top of the floating point stack.
    uint8_t top;

private:

    void printMemory();

    void runInstruction();
    
    uint32_t heapSizeGVar;

    unsigned sym(const std::string& name)
    {
        if (m_symboltable.find(name) == m_symboltable.end())
            throw std::runtime_error("Unknown symbol: " + name);

        return m_symboltable[name];
    }

    template<typename T>
    T& mem(unsigned address)
    {
        return *(T*)((char*)memory + address);
    }
    
    template<typename T>
    T& reg(uint8_t reg);

    template<typename T>
    T& readRegister();

    template <typename T>
    T& readMemory();

    template <typename T>
    T readImmediate();

    template <typename T>
    T toNative(T value)
    {
        #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        return value;
        #elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
        T result;
        for (unsigned i = 0; i < sizeof(value); ++i)
            ((char*)&result)[i] = ((char*)&value)[sizeof(value)-i-1];

        return result;
        #else
        #error Native endianness not supported.
        #endif
    }

    template <typename T>
    T fromNative(T value)
    {
        #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        return value;
        #elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
        T result;
        for (unsigned i = 0; i < sizeof(value); ++i)
            ((char*)&result)[i] = ((char*)&value)[sizeof(value)-i-1];

        return result;
        #else
        #error Native endianness not supported.
        #endif
    }
    
    void seteflags();    
    void readeflags();
    
private:

    #include <instr_decl.hpp>

private:

    bool _OF;
    bool _CF;
    bool _ZF;
    bool _SF;
    bool _PF;
    bool _DF;

    bool _O()   { return _OF; }
    bool _NO()  { return !_OF; }
    bool _B()   { return _CF; }
    bool _NAE() { return _CF; }
    bool _NB()  { return !_CF; }
    bool _AE()  { return !_CF; }
    bool _E()   { return _ZF; }
    bool _Z()   { return _ZF; }
    bool _NE()  { return !_ZF; }
    bool _NZ()  { return !_ZF; }
    bool _BE()  { return _CF||_ZF; }
    bool _NA()  { return _CF||_ZF; }
    bool _NBE() { return !(_CF||_ZF); }
    bool _A()   { return !(_CF||_ZF); }
    bool _S()   { return _SF; }
    bool _NS()  { return !_SF; }
    bool _P()   { return _PF; }
    bool _PE()  { return _PF; }
    bool _NP()  { return !_PF; }
    bool _PO()  { return !_PF; }
    bool _L()   { return _SF^_OF; }
    bool _NGE() { return _SF^_OF; }
    bool _NL()  { return !(_SF^_OF); }
    bool _GE()  { return !(_SF^_OF); }
    bool _LE()  { return (_SF^_OF)|_ZF; }
    bool _NG()  { return (_SF^_OF)|_ZF; }
    bool _NLE() { return !((_SF^_OF)|_ZF); }
    bool _G()   { return !((_SF^_OF)|_ZF); }

private:

    std::map<std::string, uint32_t> m_symboltable;
    std::map<uint32_t, syscall_t> m_syscall;
};

/*!
 * \mainpage
 * \tableofcontents
 *
 * \section intro Introduction
 *   This library interprets and runs x86 assembly in a virtual 32-bit processor.
 *
 * \section processor Processor
 *   The x86 processor has 9 registers:
 *     - `eip`: Instruction Pointer Register. This is not directly accessible.
 *     - `eax`: Accumulator Register.
 *     - `ebx`: Base Register.
 *     - `ecx`: Counter Register.
 *     - `edx`: Data Register.
 *     - `esi`: Source Index Register.
 *     - `esi`: Destination Index Register.
 *     - `esp`: Stack Pointer Register. Must be higher than `heap+heapsize`.
 *     - `ebp`: Stack Base Pointer Register. The current stack frame.
 *
 * \section memory Memory Layout
 *   Memory is little endian and is split into five sections:
 *     - `data`: The read only data from the executable, like string literals
 *               and floating constants.
 *     - `text`: The actual code that will be executed. Each instruction takes
 *               from 2 to 24 bytes of space. Functions and jumps are pointers
 *               to this part of the memory.
 *     - `static`: Place where all global variables are stored. Alignment issues
 *                 are silently ignored.
 *     - `heap`: Dynamic memory used for allocations. The `heap` global variable
 *               points to the begining of this memory. This sections grows
 *               based on the global variable `heapsize`. Its end is at
 *               `heap+heapsize`.
 *     - `stack`: This memory begins at the last byte of memory and grows
 *                backwards when functions are called. `StackOverFlow` happens
 *                when the stack's end goes into the heap.
 */
