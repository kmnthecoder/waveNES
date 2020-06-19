#include "cpu.hpp"
#include "bus.hpp"
#include "opcodes.cpp"

CPU::CPU()
{
    using a = CPU;
    LookupTable =
        {
            {"BRK", &a::OP_BRK, &a::ADDR_IMM, 7},
			{"ORA", &a::OP_ORA, &a::ADDR_IZX, 6},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 2},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 8},
			{"???", &a::OP_NOP, &a::ADDR_IMP, 3},
			{"ORA", &a::OP_ORA, &a::ADDR_ZP0, 3},
			{"ASL", &a::OP_ASL, &a::ADDR_ZP0, 5},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 5},
			{"PHP", &a::OP_PHP, &a::ADDR_IMP, 3},
			{"ORA", &a::OP_ORA, &a::ADDR_IMM, 2},
			{"ASL", &a::OP_ASL, &a::ADDR_IMP, 2},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 2},
			{"???", &a::OP_NOP, &a::ADDR_IMP, 4},
			{"ORA", &a::OP_ORA, &a::ADDR_ABS, 4},
			{"ASL", &a::OP_ASL, &a::ADDR_ABS, 6},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 6},
			{"BPL", &a::OP_BPL, &a::ADDR_REL, 2},
			{"ORA", &a::OP_ORA, &a::ADDR_IZY, 5},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 2},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 8},
			{"???", &a::OP_NOP, &a::ADDR_IMP, 4},
			{"ORA", &a::OP_ORA, &a::ADDR_ZPX, 4},
			{"ASL", &a::OP_ASL, &a::ADDR_ZPX, 6},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 6},
			{"CLC", &a::OP_CLC, &a::ADDR_IMP, 2},
			{"ORA", &a::OP_ORA, &a::ADDR_ABY, 4},
			{"???", &a::OP_NOP, &a::ADDR_IMP, 2},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 7},
			{"???", &a::OP_NOP, &a::ADDR_IMP, 4},
			{"ORA", &a::OP_ORA, &a::ADDR_ABX, 4},
			{"ASL", &a::OP_ASL, &a::ADDR_ABX, 7},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 7},
			{"JSR", &a::OP_JSR, &a::ADDR_ABS, 6},
			{"AND", &a::OP_AND, &a::ADDR_IZX, 6},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 2},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 8},
			{"BIT", &a::OP_BIT, &a::ADDR_ZP0, 3},
			{"AND", &a::OP_AND, &a::ADDR_ZP0, 3},
			{"ROL", &a::OP_ROL, &a::ADDR_ZP0, 5},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 5},
			{"PLP", &a::OP_PLP, &a::ADDR_IMP, 4},
			{"AND", &a::OP_AND, &a::ADDR_IMM, 2},
			{"ROL", &a::OP_ROL, &a::ADDR_IMP, 2},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 2},
			{"BIT", &a::OP_BIT, &a::ADDR_ABS, 4},
			{"AND", &a::OP_AND, &a::ADDR_ABS, 4},
			{"ROL", &a::OP_ROL, &a::ADDR_ABS, 6},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 6},
			{"BMI", &a::OP_BMI, &a::ADDR_REL, 2},
			{"AND", &a::OP_AND, &a::ADDR_IZY, 5},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 2},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 8},
			{"???", &a::OP_NOP, &a::ADDR_IMP, 4},
			{"AND", &a::OP_AND, &a::ADDR_ZPX, 4},
			{"ROL", &a::OP_ROL, &a::ADDR_ZPX, 6},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 6},
			{"SEC", &a::OP_SEC, &a::ADDR_IMP, 2},
			{"AND", &a::OP_AND, &a::ADDR_ABY, 4},
			{"???", &a::OP_NOP, &a::ADDR_IMP, 2},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 7},
			{"???", &a::OP_NOP, &a::ADDR_IMP, 4},
			{"AND", &a::OP_AND, &a::ADDR_ABX, 4},
			{"ROL", &a::OP_ROL, &a::ADDR_ABX, 7},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 7},
			{"RTI", &a::OP_RTI, &a::ADDR_IMP, 6},
			{"EOR", &a::OP_EOR, &a::ADDR_IZX, 6},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 2},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 8},
			{"???", &a::OP_NOP, &a::ADDR_IMP, 3},
			{"EOR", &a::OP_EOR, &a::ADDR_ZP0, 3},
			{"LSR", &a::OP_LSR, &a::ADDR_ZP0, 5},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 5},
			{"PHA", &a::OP_PHA, &a::ADDR_IMP, 3},
			{"EOR", &a::OP_EOR, &a::ADDR_IMM, 2},
			{"LSR", &a::OP_LSR, &a::ADDR_IMP, 2},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 2},
			{"JMP", &a::OP_JMP, &a::ADDR_ABS, 3},
			{"EOR", &a::OP_EOR, &a::ADDR_ABS, 4},
			{"LSR", &a::OP_LSR, &a::ADDR_ABS, 6},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 6},
			{"BVC", &a::OP_BVC, &a::ADDR_REL, 2},
			{"EOR", &a::OP_EOR, &a::ADDR_IZY, 5},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 2},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 8},
			{"???", &a::OP_NOP, &a::ADDR_IMP, 4},
			{"EOR", &a::OP_EOR, &a::ADDR_ZPX, 4},
			{"LSR", &a::OP_LSR, &a::ADDR_ZPX, 6},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 6},
			{"CLI", &a::OP_CLI, &a::ADDR_IMP, 2},
			{"EOR", &a::OP_EOR, &a::ADDR_ABY, 4},
			{"???", &a::OP_NOP, &a::ADDR_IMP, 2},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 7},
			{"???", &a::OP_NOP, &a::ADDR_IMP, 4},
			{"EOR", &a::OP_EOR, &a::ADDR_ABX, 4},
			{"LSR", &a::OP_LSR, &a::ADDR_ABX, 7},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 7},
			{"RTS", &a::OP_RTS, &a::ADDR_IMP, 6},
			{"ADC", &a::OP_ADC, &a::ADDR_IZX, 6},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 2},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 8},
			{"???", &a::OP_NOP, &a::ADDR_IMP, 3},
			{"ADC", &a::OP_ADC, &a::ADDR_ZP0, 3},
			{"ROR", &a::OP_ROR, &a::ADDR_ZP0, 5},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 5},
			{"PLA", &a::OP_PLA, &a::ADDR_IMP, 4},
			{"ADC", &a::OP_ADC, &a::ADDR_IMM, 2},
			{"ROR", &a::OP_ROR, &a::ADDR_IMP, 2},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 2},
			{"JMP", &a::OP_JMP, &a::ADDR_IND, 5},
			{"ADC", &a::OP_ADC, &a::ADDR_ABS, 4},
			{"ROR", &a::OP_ROR, &a::ADDR_ABS, 6},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 6},
			{"BVS", &a::OP_BVS, &a::ADDR_REL, 2},
			{"ADC", &a::OP_ADC, &a::ADDR_IZY, 5},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 2},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 8},
			{"???", &a::OP_NOP, &a::ADDR_IMP, 4},
			{"ADC", &a::OP_ADC, &a::ADDR_ZPX, 4},
			{"ROR", &a::OP_ROR, &a::ADDR_ZPX, 6},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 6},
			{"SEI", &a::OP_SEI, &a::ADDR_IMP, 2},
			{"ADC", &a::OP_ADC, &a::ADDR_ABY, 4},
			{"???", &a::OP_NOP, &a::ADDR_IMP, 2},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 7},
			{"???", &a::OP_NOP, &a::ADDR_IMP, 4},
			{"ADC", &a::OP_ADC, &a::ADDR_ABX, 4},
			{"ROR", &a::OP_ROR, &a::ADDR_ABX, 7},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 7},
			{"???", &a::OP_NOP, &a::ADDR_IMP, 2},
			{"STA", &a::OP_STA, &a::ADDR_IZX, 6},
			{"???", &a::OP_NOP, &a::ADDR_IMP, 2},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 6},
			{"STY", &a::OP_STY, &a::ADDR_ZP0, 3},
			{"STA", &a::OP_STA, &a::ADDR_ZP0, 3},
			{"STX", &a::OP_STX, &a::ADDR_ZP0, 3},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 3},
			{"DEY", &a::OP_DEY, &a::ADDR_IMP, 2},
			{"???", &a::OP_NOP, &a::ADDR_IMP, 2},
			{"TXA", &a::OP_TXA, &a::ADDR_IMP, 2},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 2},
			{"STY", &a::OP_STY, &a::ADDR_ABS, 4},
			{"STA", &a::OP_STA, &a::ADDR_ABS, 4},
			{"STX", &a::OP_STX, &a::ADDR_ABS, 4},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 4},
			{"BCC", &a::OP_BCC, &a::ADDR_REL, 2},
			{"STA", &a::OP_STA, &a::ADDR_IZY, 6},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 2},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 6},
			{"STY", &a::OP_STY, &a::ADDR_ZPX, 4},
			{"STA", &a::OP_STA, &a::ADDR_ZPX, 4},
			{"STX", &a::OP_STX, &a::ADDR_ZPY, 4},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 4},
			{"TYA", &a::OP_TYA, &a::ADDR_IMP, 2},
			{"STA", &a::OP_STA, &a::ADDR_ABY, 5},
			{"TXS", &a::OP_TXS, &a::ADDR_IMP, 2},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 5},
			{"???", &a::OP_NOP, &a::ADDR_IMP, 5},
			{"STA", &a::OP_STA, &a::ADDR_ABX, 5},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 5},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 5},
			{"LDY", &a::OP_LDY, &a::ADDR_IMM, 2},
			{"LDA", &a::OP_LDA, &a::ADDR_IZX, 6},
			{"LDX", &a::OP_LDX, &a::ADDR_IMM, 2},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 6},
			{"LDY", &a::OP_LDY, &a::ADDR_ZP0, 3},
			{"LDA", &a::OP_LDA, &a::ADDR_ZP0, 3},
			{"LDX", &a::OP_LDX, &a::ADDR_ZP0, 3},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 3},
			{"TAY", &a::OP_TAY, &a::ADDR_IMP, 2},
			{"LDA", &a::OP_LDA, &a::ADDR_IMM, 2},
			{"TAX", &a::OP_TAX, &a::ADDR_IMP, 2},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 2},
			{"LDY", &a::OP_LDY, &a::ADDR_ABS, 4},
			{"LDA", &a::OP_LDA, &a::ADDR_ABS, 4},
			{"LDX", &a::OP_LDX, &a::ADDR_ABS, 4},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 4},
			{"BCS", &a::OP_BCS, &a::ADDR_REL, 2},
			{"LDA", &a::OP_LDA, &a::ADDR_IZY, 5},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 2},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 5},
			{"LDY", &a::OP_LDY, &a::ADDR_ZPX, 4},
			{"LDA", &a::OP_LDA, &a::ADDR_ZPX, 4},
			{"LDX", &a::OP_LDX, &a::ADDR_ZPY, 4},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 4},
			{"CLV", &a::OP_CLV, &a::ADDR_IMP, 2},
			{"LDA", &a::OP_LDA, &a::ADDR_ABY, 4},
			{"TSX", &a::OP_TSX, &a::ADDR_IMP, 2},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 4},
			{"LDY", &a::OP_LDY, &a::ADDR_ABX, 4},
			{"LDA", &a::OP_LDA, &a::ADDR_ABX, 4},
			{"LDX", &a::OP_LDX, &a::ADDR_ABY, 4},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 4},
			{"CPY", &a::OP_CPY, &a::ADDR_IMM, 2},
			{"CMP", &a::OP_CMP, &a::ADDR_IZX, 6},
			{"???", &a::OP_NOP, &a::ADDR_IMP, 2},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 8},
			{"CPY", &a::OP_CPY, &a::ADDR_ZP0, 3},
			{"CMP", &a::OP_CMP, &a::ADDR_ZP0, 3},
			{"DEC", &a::OP_DEC, &a::ADDR_ZP0, 5},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 5},
			{"INY", &a::OP_INY, &a::ADDR_IMP, 2},
			{"CMP", &a::OP_CMP, &a::ADDR_IMM, 2},
			{"DEX", &a::OP_DEX, &a::ADDR_IMP, 2},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 2},
			{"CPY", &a::OP_CPY, &a::ADDR_ABS, 4},
			{"CMP", &a::OP_CMP, &a::ADDR_ABS, 4},
			{"DEC", &a::OP_DEC, &a::ADDR_ABS, 6},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 6},
			{"BNE", &a::OP_BNE, &a::ADDR_REL, 2},
			{"CMP", &a::OP_CMP, &a::ADDR_IZY, 5},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 2},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 8},
			{"???", &a::OP_NOP, &a::ADDR_IMP, 4},
			{"CMP", &a::OP_CMP, &a::ADDR_ZPX, 4},
			{"DEC", &a::OP_DEC, &a::ADDR_ZPX, 6},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 6},
			{"CLD", &a::OP_CLD, &a::ADDR_IMP, 2},
			{"CMP", &a::OP_CMP, &a::ADDR_ABY, 4},
			{"NOP", &a::OP_NOP, &a::ADDR_IMP, 2},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 7},
			{"???", &a::OP_NOP, &a::ADDR_IMP, 4},
			{"CMP", &a::OP_CMP, &a::ADDR_ABX, 4},
			{"DEC", &a::OP_DEC, &a::ADDR_ABX, 7},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 7},
			{"CPX", &a::OP_CPX, &a::ADDR_IMM, 2},
			{"SBC", &a::OP_SBC, &a::ADDR_IZX, 6},
			{"???", &a::OP_NOP, &a::ADDR_IMP, 2},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 8},
			{"CPX", &a::OP_CPX, &a::ADDR_ZP0, 3},
			{"SBC", &a::OP_SBC, &a::ADDR_ZP0, 3},
			{"INC", &a::OP_INC, &a::ADDR_ZP0, 5},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 5},
			{"INX", &a::OP_INX, &a::ADDR_IMP, 2},
			{"SBC", &a::OP_SBC, &a::ADDR_IMM, 2},
			{"NOP", &a::OP_NOP, &a::ADDR_IMP, 2},
			{"???", &a::OP_SBC, &a::ADDR_IMP, 2},
			{"CPX", &a::OP_CPX, &a::ADDR_ABS, 4},
			{"SBC", &a::OP_SBC, &a::ADDR_ABS, 4},
			{"INC", &a::OP_INC, &a::ADDR_ABS, 6},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 6},
			{"BEQ", &a::OP_BEQ, &a::ADDR_REL, 2},
			{"SBC", &a::OP_SBC, &a::ADDR_IZY, 5},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 2},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 8},
			{"???", &a::OP_NOP, &a::ADDR_IMP, 4},
			{"SBC", &a::OP_SBC, &a::ADDR_ZPX, 4},
			{"INC", &a::OP_INC, &a::ADDR_ZPX, 6},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 6},
			{"SED", &a::OP_SED, &a::ADDR_IMP, 2},
			{"SBC", &a::OP_SBC, &a::ADDR_ABY, 4},
			{"NOP", &a::OP_NOP, &a::ADDR_IMP, 2},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 7},
			{"???", &a::OP_NOP, &a::ADDR_IMP, 4},
			{"SBC", &a::OP_SBC, &a::ADDR_ABX, 4},
			{"INC", &a::OP_INC, &a::ADDR_ABX, 7},
			{"???", &a::OP_UOF, &a::ADDR_IMP, 7},
        };
}

CPU::~CPU() {}

uint8_t CPU::read(uint16_t addr)
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
        SetFlag(U, true);
        pc++;

        cycles = LookupTable[opcode].cycles;

        // function calls
        uint8_t addCycle1 = (this->*LookupTable[opcode].addrmode)();
        uint8_t addCycle2 = (this->*LookupTable[opcode].execute)();

        cycles += (addCycle1 & addCycle2);
        SetFlag(U, true);
    }

    clock_count++;

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
    addr_abs = 0xFFFC;
    uint16_t lo = read(addr_abs + 0);
    uint16_t hi = read(addr_abs + 1);

    pc = (hi << 8) | lo;

    reg_a = 0;
    reg_x = 0;
    reg_y = 0;
    sp = 0xFD;
    p_flag = 0x00 | U;

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

bool CPU::complete()
{
    return cycles == 0;
}

std::map<uint16_t, std::string> CPU::disassemble(uint16_t nStart, uint16_t nStop)
{
	uint32_t addr = nStart;
	uint8_t value = 0x00, lo = 0x00, hi = 0x00;
	std::map<uint16_t, std::string> mapLines;
	uint16_t line_addr = 0;

	// A convenient utility to convert variables into
	// hex strings because "modern C++"'s method with 
	// streams is atrocious
	auto hex = [](uint32_t n, uint8_t d)
	{
		std::string s(d, '0');
		for (int i = d - 1; i >= 0; i--, n >>= 4)
			s[i] = "0123456789ABCDEF"[n & 0xF];
		return s;
	};

	// Starting at the specified address we read an instruction
	// byte, which in turn yields information from the lookup table
	// as to how many additional bytes we need to read and what the
	// addressing mode is. I need this info to assemble human readable
	// syntax, which is different depending upon the addressing mode

	// As the instruction is decoded, a std::string is assembled
	// with the readable output
	while (addr <= (uint32_t)nStop)
	{
		line_addr = addr;

		// Prefix line with instruction address
		std::string sInst = "$" + hex(addr, 4) + ": ";

		// Read instruction, and get its readable name
		uint8_t opcode = bus->cpuRead(addr, true); addr++;
		sInst += LookupTable[opcode].name + " ";

		// Get oprands from desired locations, and form the
		// instruction based upon its addressing mode. These
		// routines mimmick the actual fetch routine of the
		// 6502 in order to get accurate data as part of the
		// instruction
		if (LookupTable[opcode].addrmode == &CPU::ADDR_IMP)
		{
			sInst += " {IMP}";
		}
		else if (LookupTable[opcode].addrmode == &CPU::ADDR_IMM)
		{
			value = bus->cpuRead(addr, true); addr++;
			sInst += "#$" + hex(value, 2) + " {IMM}";
		}
		else if (LookupTable[opcode].addrmode == &CPU::ADDR_ZP0)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = 0x00;												
			sInst += "$" + hex(lo, 2) + " {ZP0}";
		}
		else if (LookupTable[opcode].addrmode == &CPU::ADDR_ZPX)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = 0x00;														
			sInst += "$" + hex(lo, 2) + ", X {ZPX}";
		}
		else if (LookupTable[opcode].addrmode == &CPU::ADDR_ZPY)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = 0x00;														
			sInst += "$" + hex(lo, 2) + ", Y {ZPY}";
		}
		else if (LookupTable[opcode].addrmode == &CPU::ADDR_IZX)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = 0x00;								
			sInst += "($" + hex(lo, 2) + ", X) {IZX}";
		}
		else if (LookupTable[opcode].addrmode == &CPU::ADDR_IZY)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = 0x00;								
			sInst += "($" + hex(lo, 2) + "), Y {IZY}";
		}
		else if (LookupTable[opcode].addrmode == &CPU::ADDR_ABS)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = bus->cpuRead(addr, true); addr++;
			sInst += "$" + hex((uint16_t)(hi << 8) | lo, 4) + " {ABS}";
		}
		else if (LookupTable[opcode].addrmode == &CPU::ADDR_ABX)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = bus->cpuRead(addr, true); addr++;
			sInst += "$" + hex((uint16_t)(hi << 8) | lo, 4) + ", X {ABX}";
		}
		else if (LookupTable[opcode].addrmode == &CPU::ADDR_ABY)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = bus->cpuRead(addr, true); addr++;
			sInst += "$" + hex((uint16_t)(hi << 8) | lo, 4) + ", Y {ABY}";
		}
		else if (LookupTable[opcode].addrmode == &CPU::ADDR_IND)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = bus->cpuRead(addr, true); addr++;
			sInst += "($" + hex((uint16_t)(hi << 8) | lo, 4) + ") {IND}";
		}
		else if (LookupTable[opcode].addrmode == &CPU::ADDR_REL)
		{
			value = bus->cpuRead(addr, true); addr++;
			sInst += "$" + hex(value, 2) + " [$" + hex(addr + (int8_t)value, 4) + "] {REL}";
		}

		// Add the formed string to a std::map, using the instruction's
		// address as the key. This makes it convenient to look for later
		// as the instructions are variable in length, so a straight up
		// incremental index is not sufficient.
		mapLines[line_addr] = sInst;
	}

	return mapLines;
}
