#ifndef CPU_HPP
#define CPU_HPP

#include <cstdint>
#include <vector>
#include <string>

class Bus;

class CPU
{
public:
    CPU();
    ~CPU();

    void BusConnection(Bus *b) { bus = b; }

    enum PFLAGS
    {
        C = (1 << 0), // carry
        Z = (1 << 1), // zero
        I = (1 << 2), // disable interrupts
        D = (1 << 3), // decimal (not used in NES)
        B = (1 << 4), // break
        U = (1 << 5), // unused
        V = (1 << 6), // overflow
        N = (1 << 7), // negative
    };

    // cpu registers
    uint8_t reg_a = 0x00;  // accumulator
    uint8_t reg_x = 0x00;  // x register
    uint8_t reg_y = 0x00;  // y register
    uint8_t p_flag = 0x00; // status & processor flag
    uint8_t sp = 0x00;     // stack pointer
    uint16_t pc = 0x0000;  // program counter

    void tick();  // one tick of CPU
    void reset(); // resets CPU into known state
    void InterruptReq();
    void NonMaskInterrupt(); // same as interrupt request, but can't be disabled

private:
    Bus *bus = nullptr;

    // call to bus r/w functions
    uint8_t read(int16_t addr);
    void write(uint16_t addr, uint8_t data);

    // access status register
    uint8_t GetFlag(PFLAGS flag);
    void SetFlag(PFLAGS flag, bool v);

    struct INSTRUCTION
    {
        std::string name;
        uint8_t (CPU::*execute)(void) = nullptr;
        uint8_t (CPU::*addrmode)(void) = nullptr;
        uint8_t cycles = 0;
    };

    std::vector<INSTRUCTION> LookupTable; // table for opcodes/address modes

    uint8_t fetch();

    uint8_t fetched = 0x00;
    uint16_t temp = 0x0000;
    uint16_t addr_abs = 0x0000;
    uint16_t addr_rel = 0x00;
    uint8_t opcode = 0x00;
    uint8_t cycles = 0;
    uint32_t clock_count = 0;

    // addressing modes
    uint8_t ADDR_IMP(); // implied
    uint8_t ADDR_IMM(); // immediate
    uint8_t ADDR_ZP0(); // zero page
    uint8_t ADDR_ZPX(); // zero page x offset
    uint8_t ADDR_ZPY(); // zero page y offset
    uint8_t ADDR_REL(); // relative
    uint8_t ADDR_ABS(); // absolute
    uint8_t ADDR_ABX(); // absolute x offset
    uint8_t ADDR_ABY(); // absolute y offset
    uint8_t ADDR_IND(); // indirect
    uint8_t ADDR_IZX(); // indirect zero page x offset
    uint8_t ADDR_IZY(); // indirect zero page y offset

    // opcodes
    inline uint8_t OP_ADC();
    inline uint8_t OP_AND();
    inline uint8_t OP_ASL();
    inline uint8_t OP_BCC();
    inline uint8_t OP_BCS();
    inline uint8_t OP_BEQ();
    inline uint8_t OP_BIT();
    inline uint8_t OP_BMI();
    inline uint8_t OP_BNE();
    inline uint8_t OP_BPL();
    inline uint8_t OP_BRK();
    inline uint8_t OP_BVC();
    inline uint8_t OP_BVS();
    inline uint8_t OP_CLC();
    inline uint8_t OP_CLD();
    inline uint8_t OP_CLI();
    inline uint8_t OP_CLV();
    inline uint8_t OP_CMP();
    inline uint8_t OP_CPX();
    inline uint8_t OP_CPY();
    inline uint8_t OP_DEC();
    inline uint8_t OP_DEX();
    inline uint8_t OP_DEY();
    inline uint8_t OP_EOR();
    inline uint8_t OP_INC();
    inline uint8_t OP_INX();
    inline uint8_t OP_INY();
    inline uint8_t OP_JMP();
    inline uint8_t OP_JSR();
    inline uint8_t OP_LDA();
    inline uint8_t OP_LDX();
    inline uint8_t OP_LDY();
    inline uint8_t OP_LSR();
    inline uint8_t OP_NOP();
    inline uint8_t OP_ORA();
    inline uint8_t OP_PHA();
    inline uint8_t OP_PHP();
    inline uint8_t OP_PLA();
    inline uint8_t OP_PLP();
    inline uint8_t OP_ROL();
    inline uint8_t OP_ROR();
    inline uint8_t OP_RTI();
    inline uint8_t OP_RTS();
    inline uint8_t OP_SBC();
    inline uint8_t OP_SEC();
    inline uint8_t OP_SED();
    inline uint8_t OP_SEI();
    inline uint8_t OP_STA();
    inline uint8_t OP_STX();
    inline uint8_t OP_STY();
    inline uint8_t OP_TAX();
    inline uint8_t OP_TAY();
    inline uint8_t OP_TSX();
    inline uint8_t OP_TXA();
    inline uint8_t OP_TXS();
    inline uint8_t OP_TYA();

    inline uint8_t OP_UOF(); // unofficial
};

#endif