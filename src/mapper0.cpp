#include "mapper0.hpp"

Mapper0::Mapper0(uint8_t prgBanks, uint8_t chrBanks) : Mapper(prgBanks, chrBanks) {}

Mapper0::~Mapper0() {}

bool Mapper0::cpuMapRead(uint16_t addr, uint32_t &mapped_addr)
{
    // maps to different areas if PRGROM is >16KB or >32KB
    if (addr >= 0x8000 && addr <= 0xFFFF)
    {
        mapped_addr = addr & (PRGBanks > 1 ? 0x7FFF : 0x3FFF);
        return true;
    }
    return false;
}

bool Mapper0::cpuMapWrite(uint16_t addr, uint32_t &mapped_addr, uint8_t data)
{
    if (addr >= 0x8000 && addr <= 0xFFFF)
    {
        mapped_addr = addr & (PRGBanks > 1 ? 0x7FFF : 0x3FFF);
        return true;
    }
    return false;
}

bool Mapper0::ppuMapRead(uint16_t addr, uint32_t &mapped_addr)
{
    // no mapping required for PPU
    if (addr >= 0x0000 && addr <= 0x1FFF)
    {
        mapped_addr = addr;
        return true;
    }
    return false;
}

bool Mapper0::ppuMapWrite(uint16_t addr, uint32_t &mapped_addr)
{
   if (addr >= 0x0000 && addr <= 0x1FFF)
	{
		if (CHRBanks == 0)
		{
			// treat as RAM
			mapped_addr = addr;
			return true;
		}
	}

    return false;
}

void Mapper0::reset()
{
}