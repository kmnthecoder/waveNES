#include "cpu.hpp"
#include "bus.hpp"
#include "opcodes.cpp"

CPU::CPU()
{
    LookupTable =
        {
            {"BRK", &CPU::OP_BRK, &CPU::ADDR_IMM, 7},
            {"ORA", &CPU::OP_ORA, &CPU::ADDR_IZX, 6},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 2},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 8},
            {"UOF", &CPU::OP_NOP, &CPU::ADDR_IMP, 3},
            {"ORA", &CPU::OP_ORA, &CPU::ADDR_ZP0, 3},
            {"ASL", &CPU::OP_ASL, &CPU::ADDR_ZP0, 5},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 5},
            {"PHP", &CPU::OP_PHP, &CPU::ADDR_IMP, 3},
            {"ORA", &CPU::OP_ORA, &CPU::ADDR_IMM, 2},
            {"ASL", &CPU::OP_ASL, &CPU::ADDR_IMP, 2},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 2},
            {"UOF", &CPU::OP_NOP, &CPU::ADDR_IMP, 4},
            {"ORA", &CPU::OP_ORA, &CPU::ADDR_ABS, 4},
            {"ASL", &CPU::OP_ASL, &CPU::ADDR_ABS, 6},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 6},
            {"BPL", &CPU::OP_BPL, &CPU::ADDR_REL, 2},
            {"ORA", &CPU::OP_ORA, &CPU::ADDR_IZY, 5},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 2},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 8},
            {"UOF", &CPU::OP_NOP, &CPU::ADDR_IMP, 4},
            {"ORA", &CPU::OP_ORA, &CPU::ADDR_ZPX, 4},
            {"ASL", &CPU::OP_ASL, &CPU::ADDR_ZPX, 6},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 6},
            {"CLC", &CPU::OP_CLC, &CPU::ADDR_IMP, 2},
            {"ORA", &CPU::OP_ORA, &CPU::ADDR_ABY, 4},
            {"UOF", &CPU::OP_NOP, &CPU::ADDR_IMP, 2},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 7},
            {"UOF", &CPU::OP_NOP, &CPU::ADDR_IMP, 4},
            {"ORA", &CPU::OP_ORA, &CPU::ADDR_ABX, 4},
            {"ASL", &CPU::OP_ASL, &CPU::ADDR_ABX, 7},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 7},
            {"JSR", &CPU::OP_JSR, &CPU::ADDR_ABS, 6},
            {"AND", &CPU::OP_AND, &CPU::ADDR_IZX, 6},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 2},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 8},
            {"BIT", &CPU::OP_BIT, &CPU::ADDR_ZP0, 3},
            {"AND", &CPU::OP_AND, &CPU::ADDR_ZP0, 3},
            {"ROL", &CPU::OP_ROL, &CPU::ADDR_ZP0, 5},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 5},
            {"PLP", &CPU::OP_PLP, &CPU::ADDR_IMP, 4},
            {"AND", &CPU::OP_AND, &CPU::ADDR_IMM, 2},
            {"ROL", &CPU::OP_ROL, &CPU::ADDR_IMP, 2},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 2},
            {"BIT", &CPU::OP_BIT, &CPU::ADDR_ABS, 4},
            {"AND", &CPU::OP_AND, &CPU::ADDR_ABS, 4},
            {"ROL", &CPU::OP_ROL, &CPU::ADDR_ABS, 6},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 6},
            {"BMI", &CPU::OP_BMI, &CPU::ADDR_REL, 2},
            {"AND", &CPU::OP_AND, &CPU::ADDR_IZY, 5},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 2},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 8},
            {"UOF", &CPU::OP_NOP, &CPU::ADDR_IMP, 4},
            {"AND", &CPU::OP_AND, &CPU::ADDR_ZPX, 4},
            {"ROL", &CPU::OP_ROL, &CPU::ADDR_ZPX, 6},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 6},
            {"SEC", &CPU::OP_SEC, &CPU::ADDR_IMP, 2},
            {"AND", &CPU::OP_AND, &CPU::ADDR_ABY, 4},
            {"UOF", &CPU::OP_NOP, &CPU::ADDR_IMP, 2},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 7},
            {"UOF", &CPU::OP_NOP, &CPU::ADDR_IMP, 4},
            {"AND", &CPU::OP_AND, &CPU::ADDR_ABX, 4},
            {"ROL", &CPU::OP_ROL, &CPU::ADDR_ABX, 7},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 7},
            {"RTI", &CPU::OP_RTI, &CPU::ADDR_IMP, 6},
            {"EOR", &CPU::OP_EOR, &CPU::ADDR_IZX, 6},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 2},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 8},
            {"UOF", &CPU::OP_NOP, &CPU::ADDR_IMP, 3},
            {"EOR", &CPU::OP_EOR, &CPU::ADDR_ZP0, 3},
            {"LSR", &CPU::OP_LSR, &CPU::ADDR_ZP0, 5},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 5},
            {"PHA", &CPU::OP_PHA, &CPU::ADDR_IMP, 3},
            {"EOR", &CPU::OP_EOR, &CPU::ADDR_IMM, 2},
            {"LSR", &CPU::OP_LSR, &CPU::ADDR_IMP, 2},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 2},
            {"JMP", &CPU::OP_JMP, &CPU::ADDR_ABS, 3},
            {"EOR", &CPU::OP_EOR, &CPU::ADDR_ABS, 4},
            {"LSR", &CPU::OP_LSR, &CPU::ADDR_ABS, 6},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 6},
            {"BVC", &CPU::OP_BVC, &CPU::ADDR_REL, 2},
            {"EOR", &CPU::OP_EOR, &CPU::ADDR_IZY, 5},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 2},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 8},
            {"UOF", &CPU::OP_NOP, &CPU::ADDR_IMP, 4},
            {"EOR", &CPU::OP_EOR, &CPU::ADDR_ZPX, 4},
            {"LSR", &CPU::OP_LSR, &CPU::ADDR_ZPX, 6},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 6},
            {"CLI", &CPU::OP_CLI, &CPU::ADDR_IMP, 2},
            {"EOR", &CPU::OP_EOR, &CPU::ADDR_ABY, 4},
            {"UOF", &CPU::OP_NOP, &CPU::ADDR_IMP, 2},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 7},
            {"UOF", &CPU::OP_NOP, &CPU::ADDR_IMP, 4},
            {"EOR", &CPU::OP_EOR, &CPU::ADDR_ABX, 4},
            {"LSR", &CPU::OP_LSR, &CPU::ADDR_ABX, 7},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 7},
            {"RTS", &CPU::OP_RTS, &CPU::ADDR_IMP, 6},
            {"ADC", &CPU::OP_ADC, &CPU::ADDR_IZX, 6},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 2},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 8},
            {"UOF", &CPU::OP_NOP, &CPU::ADDR_IMP, 3},
            {"ADC", &CPU::OP_ADC, &CPU::ADDR_ZP0, 3},
            {"ROR", &CPU::OP_ROR, &CPU::ADDR_ZP0, 5},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 5},
            {"PLA", &CPU::OP_PLA, &CPU::ADDR_IMP, 4},
            {"ADC", &CPU::OP_ADC, &CPU::ADDR_IMM, 2},
            {"ROR", &CPU::OP_ROR, &CPU::ADDR_IMP, 2},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 2},
            {"JMP", &CPU::OP_JMP, &CPU::ADDR_IND, 5},
            {"ADC", &CPU::OP_ADC, &CPU::ADDR_ABS, 4},
            {"ROR", &CPU::OP_ROR, &CPU::ADDR_ABS, 6},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 6},
            {"BVS", &CPU::OP_BVS, &CPU::ADDR_REL, 2},
            {"ADC", &CPU::OP_ADC, &CPU::ADDR_IZY, 5},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 2},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 8},
            {"UOF", &CPU::OP_NOP, &CPU::ADDR_IMP, 4},
            {"ADC", &CPU::OP_ADC, &CPU::ADDR_ZPX, 4},
            {"ROR", &CPU::OP_ROR, &CPU::ADDR_ZPX, 6},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 6},
            {"SEI", &CPU::OP_SEI, &CPU::ADDR_IMP, 2},
            {"ADC", &CPU::OP_ADC, &CPU::ADDR_ABY, 4},
            {"UOF", &CPU::OP_NOP, &CPU::ADDR_IMP, 2},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 7},
            {"UOF", &CPU::OP_NOP, &CPU::ADDR_IMP, 4},
            {"ADC", &CPU::OP_ADC, &CPU::ADDR_ABX, 4},
            {"ROR", &CPU::OP_ROR, &CPU::ADDR_ABX, 7},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 7},
            {"UOF", &CPU::OP_NOP, &CPU::ADDR_IMP, 2},
            {"STA", &CPU::OP_STA, &CPU::ADDR_IZX, 6},
            {"UOF", &CPU::OP_NOP, &CPU::ADDR_IMP, 2},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 6},
            {"STY", &CPU::OP_STY, &CPU::ADDR_ZP0, 3},
            {"STA", &CPU::OP_STA, &CPU::ADDR_ZP0, 3},
            {"STX", &CPU::OP_STX, &CPU::ADDR_ZP0, 3},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 3},
            {"DEY", &CPU::OP_DEY, &CPU::ADDR_IMP, 2},
            {"UOF", &CPU::OP_NOP, &CPU::ADDR_IMP, 2},
            {"TXA", &CPU::OP_TXA, &CPU::ADDR_IMP, 2},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 2},
            {"STY", &CPU::OP_STY, &CPU::ADDR_ABS, 4},
            {"STA", &CPU::OP_STA, &CPU::ADDR_ABS, 4},
            {"STX", &CPU::OP_STX, &CPU::ADDR_ABS, 4},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 4},
            {"BCC", &CPU::OP_BCC, &CPU::ADDR_REL, 2},
            {"STA", &CPU::OP_STA, &CPU::ADDR_IZY, 6},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 2},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 6},
            {"STY", &CPU::OP_STY, &CPU::ADDR_ZPX, 4},
            {"STA", &CPU::OP_STA, &CPU::ADDR_ZPX, 4},
            {"STX", &CPU::OP_STX, &CPU::ADDR_ZPY, 4},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 4},
            {"TYA", &CPU::OP_TYA, &CPU::ADDR_IMP, 2},
            {"STA", &CPU::OP_STA, &CPU::ADDR_ABY, 5},
            {"TXS", &CPU::OP_TXS, &CPU::ADDR_IMP, 2},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 5},
            {"UOF", &CPU::OP_NOP, &CPU::ADDR_IMP, 5},
            {"STA", &CPU::OP_STA, &CPU::ADDR_ABX, 5},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 5},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 5},
            {"LDY", &CPU::OP_LDY, &CPU::ADDR_IMM, 2},
            {"LDA", &CPU::OP_LDA, &CPU::ADDR_IZX, 6},
            {"LDX", &CPU::OP_LDX, &CPU::ADDR_IMM, 2},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 6},
            {"LDY", &CPU::OP_LDY, &CPU::ADDR_ZP0, 3},
            {"LDA", &CPU::OP_LDA, &CPU::ADDR_ZP0, 3},
            {"LDX", &CPU::OP_LDX, &CPU::ADDR_ZP0, 3},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 3},
            {"TAY", &CPU::OP_TAY, &CPU::ADDR_IMP, 2},
            {"LDA", &CPU::OP_LDA, &CPU::ADDR_IMM, 2},
            {"TAX", &CPU::OP_TAX, &CPU::ADDR_IMP, 2},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 2},
            {"LDY", &CPU::OP_LDY, &CPU::ADDR_ABS, 4},
            {"LDA", &CPU::OP_LDA, &CPU::ADDR_ABS, 4},
            {"LDX", &CPU::OP_LDX, &CPU::ADDR_ABS, 4},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 4},
            {"BCS", &CPU::OP_BCS, &CPU::ADDR_REL, 2},
            {"LDA", &CPU::OP_LDA, &CPU::ADDR_IZY, 5},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 2},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 5},
            {"LDY", &CPU::OP_LDY, &CPU::ADDR_ZPX, 4},
            {"LDA", &CPU::OP_LDA, &CPU::ADDR_ZPX, 4},
            {"LDX", &CPU::OP_LDX, &CPU::ADDR_ZPY, 4},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 4},
            {"CLV", &CPU::OP_CLV, &CPU::ADDR_IMP, 2},
            {"LDA", &CPU::OP_LDA, &CPU::ADDR_ABY, 4},
            {"TSX", &CPU::OP_TSX, &CPU::ADDR_IMP, 2},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 4},
            {"LDY", &CPU::OP_LDY, &CPU::ADDR_ABX, 4},
            {"LDA", &CPU::OP_LDA, &CPU::ADDR_ABX, 4},
            {"LDX", &CPU::OP_LDX, &CPU::ADDR_ABY, 4},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 4},
            {"CPY", &CPU::OP_CPY, &CPU::ADDR_IMM, 2},
            {"CMP", &CPU::OP_CMP, &CPU::ADDR_IZX, 6},
            {"UOF", &CPU::OP_NOP, &CPU::ADDR_IMP, 2},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 8},
            {"CPY", &CPU::OP_CPY, &CPU::ADDR_ZP0, 3},
            {"CMP", &CPU::OP_CMP, &CPU::ADDR_ZP0, 3},
            {"DEC", &CPU::OP_DEC, &CPU::ADDR_ZP0, 5},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 5},
            {"INY", &CPU::OP_INY, &CPU::ADDR_IMP, 2},
            {"CMP", &CPU::OP_CMP, &CPU::ADDR_IMM, 2},
            {"DEX", &CPU::OP_DEX, &CPU::ADDR_IMP, 2},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 2},
            {"CPY", &CPU::OP_CPY, &CPU::ADDR_ABS, 4},
            {"CMP", &CPU::OP_CMP, &CPU::ADDR_ABS, 4},
            {"DEC", &CPU::OP_DEC, &CPU::ADDR_ABS, 6},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 6},
            {"BNE", &CPU::OP_BNE, &CPU::ADDR_REL, 2},
            {"CMP", &CPU::OP_CMP, &CPU::ADDR_IZY, 5},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 2},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 8},
            {"UOF", &CPU::OP_NOP, &CPU::ADDR_IMP, 4},
            {"CMP", &CPU::OP_CMP, &CPU::ADDR_ZPX, 4},
            {"DEC", &CPU::OP_DEC, &CPU::ADDR_ZPX, 6},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 6},
            {"CLD", &CPU::OP_CLD, &CPU::ADDR_IMP, 2},
            {"CMP", &CPU::OP_CMP, &CPU::ADDR_ABY, 4},
            {"NOP", &CPU::OP_NOP, &CPU::ADDR_IMP, 2},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 7},
            {"UOF", &CPU::OP_NOP, &CPU::ADDR_IMP, 4},
            {"CMP", &CPU::OP_CMP, &CPU::ADDR_ABX, 4},
            {"DEC", &CPU::OP_DEC, &CPU::ADDR_ABX, 7},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 7},
            {"CPX", &CPU::OP_CPX, &CPU::ADDR_IMM, 2},
            {"SBC", &CPU::OP_SBC, &CPU::ADDR_IZX, 6},
            {"UOF", &CPU::OP_NOP, &CPU::ADDR_IMP, 2},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 8},
            {"CPX", &CPU::OP_CPX, &CPU::ADDR_ZP0, 3},
            {"SBC", &CPU::OP_SBC, &CPU::ADDR_ZP0, 3},
            {"INC", &CPU::OP_INC, &CPU::ADDR_ZP0, 5},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 5},
            {"INX", &CPU::OP_INX, &CPU::ADDR_IMP, 2},
            {"SBC", &CPU::OP_SBC, &CPU::ADDR_IMM, 2},
            {"NOP", &CPU::OP_NOP, &CPU::ADDR_IMP, 2},
            {"UOF", &CPU::OP_SBC, &CPU::ADDR_IMP, 2},
            {"CPX", &CPU::OP_CPX, &CPU::ADDR_ABS, 4},
            {"SBC", &CPU::OP_SBC, &CPU::ADDR_ABS, 4},
            {"INC", &CPU::OP_INC, &CPU::ADDR_ABS, 6},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 6},
            {"BEQ", &CPU::OP_BEQ, &CPU::ADDR_REL, 2},
            {"SBC", &CPU::OP_SBC, &CPU::ADDR_IZY, 5},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 2},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 8},
            {"UOF", &CPU::OP_NOP, &CPU::ADDR_IMP, 4},
            {"SBC", &CPU::OP_SBC, &CPU::ADDR_ZPX, 4},
            {"INC", &CPU::OP_INC, &CPU::ADDR_ZPX, 6},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 6},
            {"SED", &CPU::OP_SED, &CPU::ADDR_IMP, 2},
            {"SBC", &CPU::OP_SBC, &CPU::ADDR_ABY, 4},
            {"NOP", &CPU::OP_NOP, &CPU::ADDR_IMP, 2},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 7},
            {"UOF", &CPU::OP_NOP, &CPU::ADDR_IMP, 4},
            {"SBC", &CPU::OP_SBC, &CPU::ADDR_ABX, 4},
            {"INC", &CPU::OP_INC, &CPU::ADDR_ABX, 7},
            {"UOF", &CPU::OP_UOF, &CPU::ADDR_IMP, 7},
        };
}

CPU::~CPU() {}

uint8_t CPU::read(int16_t addr)
{
    return bus->cpuRead(addr, false);
}

void CPU::write(uint16_t addr, uint8_t data)
{
    bus->cpuWrite(addr, data);
}

uint8_t CPU::GetFlag(PFLAGS f)
{
    return ((p_flag & f) > 0) ? 1 : 0;
}

void CPU::SetFlag(PFLAGS f, bool v)
{
    if (v)
    {
        p_flag |= f;
    }
    else
    {
        p_flag &= ~f;
    }
}

void CPU::tick()
{
    if (cycles == 0)
    {
        opcode = read(pc);
        pc++;

        cycles = LookupTable[opcode].cycles;

        // function calls
        uint8_t addCycle1 = (this->*LookupTable[opcode].addrmode)();
        uint8_t addCycle2 = (this->*LookupTable[opcode].execute)();

        cycles += (addCycle1 & addCycle2);
    }

    cycles--;
}

uint8_t CPU::fetch()
{
    if (!(LookupTable[opcode].addrmode == &CPU::ADDR_IMP))
    {
        fetched = read(addr_abs);
    }
    return fetched;
}

void CPU::reset()
{
    reg_a = 0;
    reg_x = 0;
    reg_y = 0;
    sp = 0xFD;
    p_flag = 0x00 | U;

    addr_abs = 0xFFFC;
    uint16_t lo = read(addr_abs + 0);
    uint16_t hi = read(addr_abs + 1);

    pc = (hi << 8) | lo;

    addr_rel = 0x0000;
    addr_abs = 0x0000;
    fetched = 0x00;

    cycles = 8;
}

void CPU::InterruptReq()
{
    if (GetFlag(I) == 0)
    {
        write(0x0100 + sp, (pc >> 8) & 0x00FF);
        sp--;
        write(0x0100 + sp, pc & 0x00FF);
        sp--;

        SetFlag(B, 0);
        SetFlag(U, 1);
        SetFlag(I, 1);
        write(0x0100 + sp, p_flag);
        sp--;

        addr_abs = 0xFFFE;
        uint16_t lo = read(addr_abs + 0);
        uint16_t hi = read(addr_abs + 1);
        pc = (hi << 8) | lo;

        cycles = 7;
    }
}

void CPU::NonMaskInterrupt()
{
    write(0x0100 + sp, (pc >> 8) & 0x00FF);
    sp--;
    write(0x0100 + sp, pc & 0x00FF);
    sp--;

    SetFlag(B, 0);
    SetFlag(U, 1);
    SetFlag(I, 1);
    write(0x0100 + sp, p_flag);
    sp--;

    addr_abs = 0xFFFA;
    uint16_t lo = read(addr_abs + 0);
    uint16_t hi = read(addr_abs + 1);
    pc = (hi << 8) | lo;

    cycles = 8;
}

uint8_t CPU::ADDR_IMP()
{
    fetched = reg_a;
    return 0;
}

uint8_t CPU::ADDR_IMM()
{
    addr_abs = pc++;
    return 0;
}

uint8_t CPU::ADDR_ZP0()
{
    addr_abs = read(pc);
    pc++;
    addr_abs &= 0x00FF;
    return 0;
}

uint8_t CPU::ADDR_ZPX()
{
    addr_abs = (read(pc) + reg_x);
    pc++;
    addr_abs &= 0x00FF;
    return 0;
}

uint8_t CPU::ADDR_ZPY()
{
    addr_abs = (read(pc) + reg_y);
    pc++;
    addr_abs &= 0x00FF;
    return 0;
}

uint8_t CPU::ADDR_REL()
{
    addr_rel = read(pc);
    pc++;

    if (addr_rel & 0x80)
    {
        addr_rel |= 0xFF00;
    }
    return 0;
}

uint8_t CPU::ADDR_ABS()
{
    uint16_t lo = read(pc);
    pc++;
    uint16_t hi = read(pc);
    pc++;

    addr_abs = (hi << 8) | lo;

    return 0;
}

uint8_t CPU::ADDR_ABX()
{
    uint16_t lo = read(pc);
    pc++;
    uint16_t hi = read(pc);
    pc++;

    addr_abs = (hi << 8) | lo;
    addr_abs += reg_x;

    if ((addr_abs & 0xFF00) != (hi << 8))
    {
        return 1;
    }
    else
    {
        return 0;
    }

    return 0;
}

uint8_t CPU::ADDR_ABY()
{
    uint16_t lo = read(pc);
    pc++;
    uint16_t hi = read(pc);
    pc++;

    addr_abs = (hi << 8) | lo;
    addr_abs += reg_y;

    if ((addr_abs & 0xFF00) != (hi << 8))
    {
        return 1;
    }
    else
    {
        return 0;
    }

    return 0;
}

uint8_t CPU::ADDR_IND()
{
    uint16_t ptr_lo = read(pc);
    pc++;
    uint16_t ptr_hi = read(pc);
    pc++;

    uint16_t ptr = (ptr_hi << 8) | ptr_lo;

    if (ptr_lo == 0x00FF)
    {
        addr_abs = (read(ptr & 0xFF00) << 8) | read(ptr + 0);
    }
    else
    {
        addr_abs = (read(ptr + 1) << 8) | read(ptr + 0);
    }

    return 0;
}

uint8_t CPU::ADDR_IZX()
{
    uint16_t t = read(pc);
    pc++;

    uint16_t lo = read((uint16_t)(t + (uint16_t)reg_x) & 0x00FF);
    uint16_t hi = read((uint16_t)(t + (uint16_t)reg_x + 1) & 0x00FF);

    addr_abs = (hi << 8) | lo;

    return 0;
}

uint8_t CPU::ADDR_IZY()
{
    uint16_t t = read(pc);
    pc++;

    uint16_t lo = read(t & 0x00FF);
    uint16_t hi = read((t + 1) & 0x00FF);

    addr_abs = (hi << 8) | lo;
    addr_abs += reg_y;

    if ((addr_abs & 0xFF00) != (hi << 8))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}