#ifndef PPU_HPP
#define PPU_HPP

#include "cartridge.hpp"

#include "olcPixelGameEngine.h"

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
    void tick();

private:
    std::shared_ptr<Cartridge> cartridge;

    uint8_t nameTable[2][1024];
    uint8_t paletteTable[32];
    uint8_t patternTable[2][4096]; // special

private:
    olc::Pixel palScreen[0x40];
    olc::Sprite spriteScreen = olc::Sprite(256, 240);
    olc::Sprite spriteNameTable[2] = {olc::Sprite(256, 240), olc::Sprite(256, 240)};
    olc::Sprite spritePatternTable[2] = {olc::Sprite(128, 128), olc::Sprite(128, 128)};

public:
    olc::Sprite &GetScreen();
    olc::Sprite &GetNameTable(uint8_t i);
    olc::Sprite &GetPatternTable(uint8_t i, uint8_t palette);
    olc::Pixel &GetColourFromPaletteRam(uint8_t palette, uint8_t pixel);
    bool frameComplete = false;

private:
    int16_t scanline = 0;
    int16_t cycle = 0;
};

#endif