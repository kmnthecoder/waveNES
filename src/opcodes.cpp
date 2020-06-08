#include "cpu.hpp"

// Add M to A with Carry
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

// AND M with A
inline uint8_t CPU::OP_AND()
{
    fetch();
    reg_a &= fetched;
    SetFlag(Z, reg_a == 0x00);
    SetFlag(N, reg_a & 0x80);
    return 1;
}

// Shift Left One Bit (M or A)
inline uint8_t CPU::OP_ASL()
{
    fetch();
    temp = (uint16_t)fetched << 1;
    SetFlag(C, (temp & 0xFF00) > 0);
    SetFlag(N, temp & 0x80);
    SetFlag(Z, (temp & 0x00FF) == 0x00);
    if (LookupTable[opcode].addrmode == &CPU::ADDR_IMP)
    {
        reg_a = temp & 0x00FF;
    }
    else
    {
        write(addr_abs, temp & 0x00FF);
    }
    return 0;
}

// Branch on Carry Clear
inline uint8_t CPU::OP_BCC()
{
    if (GetFlag(C) == 0)
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

// Branch on Carry Set
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

// Branch on Result Zero
inline uint8_t CPU::OP_BEQ()
{
    if (GetFlag(Z) == 1)
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

// Test Bits in M with A
inline uint8_t CPU::OP_BIT()
{
    fetch();
    temp = fetched & reg_a;
    SetFlag(N, fetched & (1 << 7));
    SetFlag(Z, (temp & 0x00FF) == 0x00);
    SetFlag(V, fetched & (1 << 6));
    return 0;
}

// Branch on Result Minus
inline uint8_t CPU::OP_BMI()
{
    if (GetFlag(N) == 1)
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

// Branch on Result not Zero
inline uint8_t CPU::OP_BNE()
{
    if (GetFlag(Z) == 0)
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

// Branch on Result Plus
inline uint8_t CPU::OP_BPL()
{
    if (GetFlag(N) == 0)
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

// Force Break
inline uint8_t CPU::OP_BRK()
{
    pc++;
    SetFlag(I, 1);
    write(0x0100 + sp, (pc >> 8) & 0x00FF);
    sp--;
    write(0x0100 + sp, pc & 0x00FF);
    sp--;

    SetFlag(B, 1);
    write(0x0100 + sp, p_flag);
    sp--;
    SetFlag(B, 0);

    pc = (uint16_t)read(0xFFFE) | ((uint16_t)read(0xFFFF) << 8);
    return 0;
}

// Branch on Overflow Clear
inline uint8_t CPU::OP_BVC()
{
    if (GetFlag(V) == 0)
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

// Branch on Overflow Set
inline uint8_t CPU::OP_BVS()
{
    if (GetFlag(V) == 1)
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

// Clear Carry Flag
inline uint8_t CPU::OP_CLC()
{
    SetFlag(C, false);
    return 0;
}

// Clear Decimal Mode
inline uint8_t CPU::OP_CLD()
{
    SetFlag(D, false);
    return 0;
}

// Clear Interrupt Disable Bit
inline uint8_t CPU::OP_CLI()
{
    SetFlag(I, false);
    return 0;
}

// Clear Overflow Flag
inline uint8_t CPU::OP_CLV()
{
    SetFlag(V, false);
    return 0;
}

// Compare M and A
inline uint8_t CPU::OP_CMP()
{
    fetch();
    temp = (uint16_t)reg_a - (uint16_t)fetched;
    SetFlag(C, reg_a >= fetched);
    SetFlag(Z, (temp & 0x00FF) == 0x0000);
    SetFlag(N, temp & 0x0080);
    return 1;
}

// Compare M and X
inline uint8_t CPU::OP_CPX()
{
    fetch();
    temp = (uint16_t)reg_x - (uint16_t)fetched;
    SetFlag(C, reg_x >= fetched);
    SetFlag(Z, (temp & 0x00FF) == 0x0000);
    SetFlag(N, temp & 0x0080);
    return 1;
}

// Compare M and Y
inline uint8_t CPU::OP_CPY()
{
    fetch();
    temp = (uint16_t)reg_y - (uint16_t)fetched;
    SetFlag(C, reg_y >= fetched);
    SetFlag(Z, (temp & 0x00FF) == 0x0000);
    SetFlag(N, temp & 0x0080);
    return 1;
}

// Decerement M by One
inline uint8_t CPU::OP_DEC()
{
    fetch();
    temp = fetched - 1;
    write(addr_abs, temp & 0x00FF);
    SetFlag(Z, (temp & 0x00FF) == 0x0000);
    SetFlag(N, temp & 0x0080);
    return 0;
}

// Decrement X by One
inline uint8_t CPU::OP_DEX()
{
    reg_x--;
    SetFlag(Z, reg_x == 0x00);
    SetFlag(N, reg_x & 0x80);
    return 0;
}

// Decrement Y by One
inline uint8_t CPU::OP_DEY()
{
    reg_y--;
    SetFlag(Z, reg_y == 0x00);
    SetFlag(N, reg_y & 0x80);
    return 0;
}

// Exclusive-Or M with A
inline uint8_t CPU::OP_EOR()
{
    fetch();
    reg_a ^= fetched;
    SetFlag(Z, reg_a == 0x00);
    SetFlag(N, reg_a & 0x80);
    return 1;
}

// Increment M by One
inline uint8_t CPU::OP_INC()
{
    fetch();
    temp = fetched + 1;
    write(addr_abs, temp & 0x00FF);
    SetFlag(Z, (temp & 0x00FF) == 0x0000);
    SetFlag(N, temp & 0x0080);
    return 0;
}

// Increment X by One
inline uint8_t CPU::OP_INX()
{
    reg_x++;
    SetFlag(Z, reg_x == 0x00);
    SetFlag(N, reg_x & 0x80);
    return 0;
}

// Increment Y by One
inline uint8_t CPU::OP_INY()
{
    reg_y++;
    SetFlag(Z, reg_y == 0x00);
    SetFlag(N, reg_y & 0x80);
    return 0;
}

// Jump to Location
inline uint8_t CPU::OP_JMP()
{
    pc = addr_abs;
    return 0;
}

// Jump to Location Save Return Address
inline uint8_t CPU::OP_JSR()
{
    pc--;
    write(0x0100 + sp, (pc >> 8) & 0x00FF);
    sp--;
    write(0x0100 + sp, pc & 0x00FF);
    sp--;

    pc = addr_abs;
    return 0;
}

// Load A with M
inline uint8_t CPU::OP_LDA()
{
    fetch();
    reg_a = fetched;
    SetFlag(Z, reg_a == 0x00);
    SetFlag(N, reg_a & 0x80);
    return 0;
}

// Load X with M
inline uint8_t CPU::OP_LDX()
{
    fetch();
    reg_x = fetched;
    SetFlag(Z, reg_x == 0x00);
    SetFlag(N, reg_x & 0x80);
    return 0;
}

// Load Y with M
inline uint8_t CPU::OP_LDY()
{
    fetch();
    reg_y = fetched;
    SetFlag(Z, reg_y == 0x00);
    SetFlag(N, reg_y & 0x80);
    return 0;
}

// Shift Right One Bit (M or A)
inline uint8_t CPU::OP_LSR()
{
    fetch();
    SetFlag(C, fetched & 0x0001);
    temp = fetched >> 1;
    SetFlag(N, temp & 0x0080);
    SetFlag(Z, (temp & 0x00FF) == 0x0000);
    if (LookupTable[opcode].addrmode == &CPU::ADDR_IMP)
    {
        reg_a = temp & 0x00FF;
    }
    else
    {
        write(addr_abs, temp & 0x00FF);
    }
    return 0;
}

// No Operation
inline uint8_t CPU::OP_NOP()
{
    switch (opcode)
    {
    case 0x1C:
    case 0x3C:
    case 0x5C:
    case 0x7C:
    case 0xDC:
    case 0xFC:
        return 1;
        break;
    }
    return 0;
}

// OR M with A
inline uint8_t CPU::OP_ORA()
{
    fetch();
    reg_a |= fetched;
    SetFlag(Z, reg_a == 0x00);
    SetFlag(N, reg_a & 0x80);
    return 1;
}

// Push A on Stack
inline uint8_t CPU::OP_PHA()
{
    write(0x0100 + sp, reg_a);
    sp--;
    return 0;
}

// Push Processor Status on Stack
inline uint8_t CPU::OP_PHP()
{
    write(0x0100 + sp, p_flag | B | U);
    SetFlag(B, 0);
    SetFlag(U, 0);
    sp--;
    return 0;
}

// Pull A from Stack
inline uint8_t CPU::OP_PLA()
{
    sp++;
    reg_a = read(0x0100 + sp);
    SetFlag(Z, reg_a == 0x00);
    SetFlag(N, reg_a & 0x80);
    return 0;
}

// Pull Processor Status from Stack
inline uint8_t CPU::OP_PLP()
{
    sp++;
    p_flag = read(0x0100 + sp);
    SetFlag(U, 1);
    return 0;
}

// Rotate One Bit Left
inline uint8_t CPU::OP_ROL()
{
    fetch();
    temp = (uint16_t)(fetched << 1) | GetFlag(C);
    SetFlag(C, temp & 0xFF00);
    SetFlag(Z, (temp & 0x00FF) == 0x0000);
    SetFlag(N, temp & 0x0080);
    if (LookupTable[opcode].addrmode == &CPU::ADDR_IMP)
    {
        reg_a = temp & 0x00FF;
    }
    else
    {
        write(addr_abs, temp & 0x00FF);
    }
    return 0;
}

// Rotate One Bit Right
inline uint8_t CPU::OP_ROR()
{
    fetch();
    temp = (uint16_t)GetFlag(C) << 7 | (fetched >> 1);
    SetFlag(C, fetched & 0x01);
    SetFlag(Z, (temp & 0x00FF) == 0x00);
    SetFlag(N, temp & 0x0080);
    if (LookupTable[opcode].addrmode == &CPU::ADDR_IMP)
    {
        reg_a = temp & 0x00FF;
    }
    else
    {
        write(addr_abs, temp & 0x00FF);
    }
    return 0;
}

// Return from Interrupt
inline uint8_t CPU::OP_RTI()
{
    sp++;
    p_flag = read(0x0100 + sp);
    p_flag &= ~B;
    p_flag &= ~U;

    sp++;
    pc = (uint16_t)read(0x0100 + sp);
    sp++;
    pc |= (uint16_t)read(0x0100 + sp) << 8;
    return 0;
}

// Return from Subroutine
inline uint8_t CPU::OP_RTS()
{
    sp++;
    pc = (uint16_t)read(0x0100 + sp);
    sp++;
    pc |= (uint16_t)read(0x0100 + sp) << 8;
    pc++;
    return 0;
}

// Subtract M from A with Borrow
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

// Set Carry Flag
inline uint8_t CPU::OP_SEC()
{
    SetFlag(C, true);
    return 0;
}

// Set Decimal Mode
inline uint8_t CPU::OP_SED()
{
    SetFlag(D, true);
    return 0;
}

// Set Interrupt Disable Status
inline uint8_t CPU::OP_SEI()
{
    SetFlag(I, true);
    return 0;
}

// Store A in M
inline uint8_t CPU::OP_STA()
{
    write(addr_abs, reg_a);
    return 0;
}

// Store X in M
inline uint8_t CPU::OP_STX()
{
    write(addr_abs, reg_x);
    return 0;
}

// Store Y in M
inline uint8_t CPU::OP_STY()
{
    write(addr_abs, reg_y);
    return 0;
}

// Transfer A to X
inline uint8_t CPU::OP_TAX()
{
    reg_x = reg_a;
    SetFlag(Z, reg_x == 0x00);
    SetFlag(N, reg_x & 0x80);
    return 0;
}

// Transfer A to Y
inline uint8_t CPU::OP_TAY()
{
    reg_y = reg_a;
    SetFlag(Z, reg_y == 0x00);
    SetFlag(N, reg_y & 0x80);
    return 0;
}

// Transfer Stack Pointer to X
inline uint8_t CPU::OP_TSX()
{
    reg_x = sp;
    SetFlag(Z, reg_x == 0x00);
    SetFlag(N, reg_x & 0x80);
    return 0;
}

// Transfer X to A
inline uint8_t CPU::OP_TXA()
{
    reg_a = reg_x;
    SetFlag(Z, reg_a == 0x00);
    SetFlag(N, reg_a & 0x80);
    return 0;
}

// Transfer X to Stack Pointer
inline uint8_t CPU::OP_TXS()
{
    sp = reg_x;
    return 0;
}

// Transfer Y to A
inline uint8_t CPU::OP_TYA()
{
    reg_a = reg_y;
    SetFlag(Z, reg_a == 0x00);
    SetFlag(N, reg_a & 0x80);
    return 0;
}

// Unofficial
inline uint8_t CPU::OP_UOF() { return 0; }