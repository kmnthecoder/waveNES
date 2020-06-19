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
    //uint8_t cpuRam[2048];
    uint8_t controller[2];

public:
    uint8_t cpuRead(uint16_t addr, bool readOnly = false);
    void cpuWrite(uint16_t addr, uint8_t data);

private:
    uint32_t clockCount = 0;
    uint8_t controller_state[2];

public:
    void insertCartridge(const std::shared_ptr<Cartridge> &cartridge);
    void reset();
    void tick();
};

#endif