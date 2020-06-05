#include "cpu.hpp"

inline uint8_t CPU::OP_ADC()
{
    fetch();
    uint16_t temp = (uint16_t)reg_a + (uint16_t)fetched + (uint16_t)GetFlag(C);
    SetFlag(C, temp > 255);
    SetFlag(Z, (temp & 0x00FF) == 0);
    SetFlag(V, (~((uint16_t)reg_a ^ (uint16_t)fetched) & ((uint16_t)reg_a ^ (uint16_t)temp)) & 0x0080);
    SetFlag(N, temp & 0x80);
    reg_a = temp & 0x00FF;
    return 1;
}

inline uint8_t CPU::OP_AND()
{
    fetch();
    reg_a &= fetched;
    SetFlag(Z, reg_a == 0x00);
    SetFlag(N, reg_a & 0x80);
    return 1;
}

inline uint8_t CPU::OP_ASL() { return 0; }

inline uint8_t CPU::OP_BCC() { return 0; }

inline uint8_t CPU::OP_BCS()
{
    if (GetFlag(C) == 1)
    {
        cycles++;
        addr_abs = pc + addr_rel;

        if ((addr_abs & 0xFF00) != (pc & 0xFF00))
        {
            cycles++;
        }

        pc = addr_abs;
    }
    return 0;
}

inline uint8_t CPU::OP_BEQ() { return 0; }

inline uint8_t CPU::OP_BIT() { return 0; }

inline uint8_t CPU::OP_BMI() { return 0; }

inline uint8_t CPU::OP_BNE() { return 0; }

inline uint8_t CPU::OP_BPL() { return 0; }

inline uint8_t CPU::OP_BRK() { return 0; }

inline uint8_t CPU::OP_BVC() { return 0; }

inline uint8_t CPU::OP_BVS() { return 0; }

inline uint8_t CPU::OP_CLC()
{
    SetFlag(C, false);
    return 0;
}

inline uint8_t CPU::OP_CLD() { return 0; }

inline uint8_t CPU::OP_CLI() { return 0; }

inline uint8_t CPU::OP_CLV() { return 0; }

inline uint8_t CPU::OP_CMP() { return 0; }

inline uint8_t CPU::OP_CPX() { return 0; }

inline uint8_t CPU::OP_CPY() { return 0; }

inline uint8_t CPU::OP_DEC() { return 0; }

inline uint8_t CPU::OP_DEX() { return 0; }

inline uint8_t CPU::OP_DEY() { return 0; }

inline uint8_t CPU::OP_EOR() { return 0; }

inline uint8_t CPU::OP_INC() { return 0; }

inline uint8_t CPU::OP_INX() { return 0; }

inline uint8_t CPU::OP_INY() { return 0; }

inline uint8_t CPU::OP_JMP() { return 0; }

inline uint8_t CPU::OP_JSR() { return 0; }

inline uint8_t CPU::OP_LDA() { return 0; }

inline uint8_t CPU::OP_LDX() { return 0; }

inline uint8_t CPU::OP_LDY() { return 0; }

inline uint8_t CPU::OP_LSR() { return 0; }

inline uint8_t CPU::OP_NOP() { return 0; }

inline uint8_t CPU::OP_ORA() { return 0; }

inline uint8_t CPU::OP_PHA() { return 0; }

inline uint8_t CPU::OP_PHP()
{
    write(0x0100 + sp, reg_a);
    sp--;
    return 0;
}

inline uint8_t CPU::OP_PLA()
{
    sp++;
    reg_a = read(0x0100 + sp);
    SetFlag(Z, reg_a == 0x00);
    SetFlag(N, reg_a & 0x80);
    return 0;
}

inline uint8_t CPU::OP_PLP() { return 0; }

inline uint8_t CPU::OP_ROL() { return 0; }

inline uint8_t CPU::OP_ROR() { return 0; }

inline uint8_t CPU::OP_RTI() { return 0; }

inline uint8_t CPU::OP_RTS() { return 0; }

inline uint8_t CPU::OP_SBC()
{
    fetch();
    uint16_t value = ((uint16_t)fetched) ^ 0x00FF;
    uint16_t temp = (uint16_t)reg_a + value + (uint16_t)GetFlag(C);
    SetFlag(C, temp & 255);
    SetFlag(Z, ((temp & 0x00FF) == 0));
    SetFlag(V, (temp ^ (uint16_t)reg_a) & (temp ^ value) & 0x0080);
    SetFlag(N, temp & 0x0080);
    reg_a = temp & 0x00FF;
    return 1;
}

inline uint8_t CPU::OP_SEC() { return 0; }

inline uint8_t CPU::OP_SED() { return 0; }

inline uint8_t CPU::OP_SEI() { return 0; }

inline uint8_t CPU::OP_STA() { return 0; }

inline uint8_t CPU::OP_STX() { return 0; }

inline uint8_t CPU::OP_STY() { return 0; }

inline uint8_t CPU::OP_TAX() { return 0; }

inline uint8_t CPU::OP_TAY() { return 0; }

inline uint8_t CPU::OP_TSX() { return 0; }

inline uint8_t CPU::OP_TXA() { return 0; }

inline uint8_t CPU::OP_TXS() { return 0; }

inline uint8_t CPU::OP_TYA() { return 0; }

inline uint8_t CPU::OP_UOF() { return 0; }