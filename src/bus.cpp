#include "bus.hpp"

Bus::Bus()
{
    cpu.BusConnection(this);
    cpuRam.fill(0x00);
}

Bus::~Bus() {}

uint8_t Bus::cpuRead(int16_t addr, bool readOnly)
{
    uint8_t data = 0x00;

    if (cartridge->cpuRead(addr, data))
    {
    }
    else if (addr >= 0x0000 && addr <= 0x1FFF)
    {
        data = cpuRam[addr & 0x07FF];
    }
    else if (addr >= 0x2000 && addr <= 0x3FFF)
    {
        data = ppu.cpuRead(addr & 0x0007, readOnly);
    }
    return data;
}

void Bus::cpuWrite(uint16_t addr, uint8_t data)
{
    if (cartridge->cpuWrite(addr, data))
    {
    }
    else if (addr >= 0x0000 && addr <= 0x1FFF)
    {
        cpuRam[addr & 0x07FF] = data;
    }
    else if (addr >= 0x2000 && addr <= 0x3FFF)
    {
        ppu.cpuWrite(addr & 0x0007, data);
    }
}

void Bus::insertCartridge(const std::shared_ptr<Cartridge> &cartridge)
{
    this->cartridge = cartridge;
    ppu.ConnectCartridge(cartridge);
}

void Bus::reset()
{
    cpu.reset();
    clockCount = 0;
}

void Bus::clock()
{
    ppu.clock();
    if (clockCount % 3 == 0)
    {
        cpu.tick();
    }
    clockCount++;
}
