#include "bus.hpp"

Bus::Bus()
{
    cpu.BusConnection(this);
    //cpuRam.fill(0x00);
}

Bus::~Bus() {}

uint8_t Bus::cpuRead(uint16_t addr, bool readOnly)
{
    uint8_t data = 0x00;

    if (cart->cpuRead(addr, data))
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
    else if (addr >= 0x4016 && addr <= 0x4017)
	{
		data = (controller_state[addr & 0x0001] & 0x80) > 0;
		controller_state[addr & 0x0001] <<= 1;
	}
    return data;
}

void Bus::cpuWrite(uint16_t addr, uint8_t data)
{
    if (cart->cpuWrite(addr, data))
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
    this->cart = cartridge;
    ppu.ConnectCartridge(cartridge);
}

void Bus::reset()
{   
    cart->reset();
    cpu.reset();
    ppu.reset();
    clockCount = 0;
}

void Bus::tick()
{
    ppu.tick();
    if (clockCount % 3 == 0)
    {
        cpu.tick();
    }

    if (ppu.nmi)
    {
        ppu.nmi = false;
        cpu.NonMaskInterrupt();
    }

    clockCount++;
}
