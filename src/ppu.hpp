#ifndef PPU_HPP
#define PPU_HPP

#include "cartridge.hpp"

#include <cstdint>
#include <memory>

class PPU
{
public:
    PPU();
    ~PPU();

    uint8_t cpuRead(int16_t addr, bool readOnly = false);
    void cpuWrite(uint16_t addr, uint8_t data);

    uint8_t ppuRead(int16_t addr, bool readOnly = false);
    void ppuWrite(uint16_t addr, uint8_t data);

    void ConnectCartridge(const std::shared_ptr<Cartridge> &cartridge);
    void clock();

private:
    std::shared_ptr<Cartridge> cartridge;

    uint8_t nameTable[2][1024];
    uint8_t paletteTable[32];
    //uint8_t patternTable[2][4096]; // special

    bool frameComplete = false;
    int16_t scanline = 0;
    int16_t cycle = 0;
};

#endif