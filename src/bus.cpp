#include "bus.hpp"

Bus::Bus()
{
    cpu.BusConnection(this);
    ram.fill(0x00);
}

Bus::~Bus() {}

uint8_t Bus::read(int16_t addr, bool readOnly)
{
    if (addr >= 0x0000 && addr <= 0xFFFF)
    {
        return ram[addr];
    }
    return 0x00;
}

void Bus::write(uint16_t addr, uint8_t data)
{
    if (addr >= 0x0000 && addr <= 0xFFFF)
    {
        ram[addr] = data;
    }
}
