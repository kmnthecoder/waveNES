#ifndef BUS_HPP
#define BUS_HPP

#include <cstdint>
#include <array>

#include "cpu.hpp"
#include "ppu.hpp"
#include "cartridge.hpp"

class Bus
{
public:
    Bus();
    ~Bus();

public:
    CPU cpu;
    PPU ppu;
    std::shared_ptr<Cartridge> cart;
    std::array<uint8_t, 2048> cpuRam;
    uint8_t controller[2];

public: // bus r/w
    uint8_t cpuRead(uint16_t addr, bool readOnly = false);
    void cpuWrite(uint16_t addr, uint8_t data);

private:
    uint32_t clockCount = 0;
    uint8_t controller_state[2];

public:
    void insertCartridge(const std::shared_ptr<Cartridge> &cartridge);
    void reset();
    void tick();

private:
    uint8_t dma_page = 0x00;
    uint8_t dma_addr = 0x00;
    uint8_t dma_data = 0x00;

    bool dma_transfer = false;
    bool dma_dummy = true;
};

#endif