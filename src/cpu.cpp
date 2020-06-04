#include "cpu.hpp"
#include "bus.hpp"
#include "opcodes.cpp"

CPU::CPU() {}

CPU::~CPU() {}

void CPU::write(uint16_t addr, uint8_t data) {
    bus->write(addr, data);
}

uint8_t CPU::read(int16_t addr) {
    return bus->read(addr, false);
}