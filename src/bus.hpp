#ifndef BUS_HPP
#define BUS_HPP

#include "cpu.hpp"
#include "ppu.hpp"
#include "cartridge.hpp"

#include <cstdint>
#include <array>
#include <memory>

class Bus
{
public:
    Bus();
    ~Bus();

    std::array<uint8_t, 2048> cpuRam;
    //uint8_t cpuRam[2048];
    CPU cpu;
    PPU ppu;
    std::shared_ptr<Cartridge> cartridge;

    uint8_t cpuRead(int16_t addr, bool readOnly = false);
    void cpuWrite(uint16_t addr, uint8_t data);

    void insertCartridge(const std::shared_ptr<Cartridge> &cartridge);
    void reset();
    void tick();

private:
    uint32_t clockCount = 0;
};

#endif