#include "ppu.hpp"
#include "bus.hpp"

PPU::PPU() {}

PPU::~PPU() {}

uint8_t PPU::cpuRead(int16_t addr, bool readOnly)
{
    uint8_t data = 0x00;

    switch (addr)
    {
    case 0x0000: // control
        break;
    case 0x0001: // mask
        break;
    case 0x0002: // status
        break;
    case 0x0003: // oam address
        break;
    case 0x0004: // oam data
        break;
    case 0x0005: // scroll
        break;
    case 0x0006: // ppu address
        break;
    case 0x0007: // ppu data
        break;
    }

    return data;
}
void PPU::cpuWrite(uint16_t addr, uint8_t data)
{
    switch (addr)
    {
    case 0x0000: // control
        break;
    case 0x0001: // mask
        break;
    case 0x0002: // status
        break;
    case 0x0003: // oam address
        break;
    case 0x0004: // oam data
        break;
    case 0x0005: // scroll
        break;
    case 0x0006: // ppu address
        break;
    case 0x0007: // ppu data
        break;
    }
}

uint8_t PPU::ppuRead(int16_t addr, bool readOnly)
{
    uint8_t data = 0x00;
    addr &= 0x3FFF;

    if (cartridge->ppuRead(addr, data))
    {
    }

    return data;
}

void PPU::ppuWrite(uint16_t addr, uint8_t data)
{
    addr &= 0x3FFF;

    if (cartridge->ppuWrite(addr, data))
    {
    }
}

void PPU::ConnectCartridge(const std::shared_ptr<Cartridge> &cartridge)
{
    this->cartridge = cartridge;
}

void PPU::clock()
{
    cycle++;
    if (cycle >= 341)
    {
        cycle = 0;
        scanline++;
        if (scanline >= 261)
        {
            scanline = -1;
            frameComplete = true;
        }
    }
}