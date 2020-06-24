#include "bus.hpp"

Bus::Bus()
{
    cpu.BusConnection(this);
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
        // system RAM address range
        // range covers 8KB, but only 2KB is available.
        // 2KB is mirrored throughout range
        data = cpuRam[addr & 0x07FF];
    }
    else if (addr >= 0x2000 && addr <= 0x3FFF)
    {
        // ppu address range, ppu has 8 primary registers
        // these registers are repeated throughout range
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
    else if (addr == 0x4014)
    {
        dma_page = data;
        dma_addr = 0x00;
        dma_transfer = true;
    }
    else if (addr >= 0x4016 && addr <= 0x4017)
    {
        controller_state[addr & 0x0001] = controller[addr & 0x0001];
    }
}

void Bus::insertCartridge(const std::shared_ptr<Cartridge> &cartridge)
{
    // connects cartridge to main bus and CPU bus
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
    // main componenet of an emulator (it is what makes it run)
    ppu.tick();

    // CPU is 3 times slower than PPU
    if (clockCount % 3 == 0)
    {
        if (dma_transfer)
        {
            if (dma_dummy)
            {
                if (clockCount % 2 == 1)
                {
                    dma_dummy = false;
                }
            }
            else
            {
                if (clockCount % 2 == 0)
                {
                    dma_data = cpuRead(dma_page << 8 | dma_addr);
                }
                else
                {
                    ppu.pOAM[dma_addr] = dma_data;
                    dma_addr++;

                    if (dma_addr == 0x00)
                    {
                        dma_transfer = false;
                        dma_dummy = true;
                    }
                }
            }
        }
        else
        {
            cpu.tick();
        }
    }

    // PPU can emit an interrupt, indicating vertical blanking period has entered
    if (ppu.nmi)
    {
        ppu.nmi = false;
        cpu.NonMaskInterrupt();
    }

    clockCount++;
}
