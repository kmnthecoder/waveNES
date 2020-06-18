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
    void reset();

    bool nmi = false;

private:
    std::shared_ptr<Cartridge> cartridge;

    uint8_t paletteTable[32];
    uint8_t patternTable[2][4096];

public:
    uint8_t nameTable[2][1024];

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

    union {
        struct
        {
            uint8_t unused : 5;
            uint8_t sprite_overflow : 1;
            uint8_t sprite_zero_hit : 1;
            uint8_t vertical_blank : 1;
        };
        uint8_t reg;
    } status;

    union {
        struct
        {
            uint8_t grayscake : 1;
            uint8_t render_bg_left : 1;
            uint8_t render_sprites_left : 1;
            uint8_t render_bg : 1;
            uint8_t render_sprites : 1;
            uint8_t enhance_red : 1;
            uint8_t enhance_green : 1;
            uint8_t enhance_blue : 1;
        };
        uint8_t reg;
    } mask;

    union PPUCTRL {
        struct
        {
            uint8_t nametable_x : 1;
            uint8_t nametable_y : 1;
            uint8_t increment_mode : 1;
            uint8_t pattern_sprite : 1;
            uint8_t pattern_background : 1;
            uint8_t sprite_size : 1;
            uint8_t slave_mode : 1;
            uint8_t enable_nmi : 1;
        };
        uint8_t reg;
    } control;

    uint8_t addr_latch = 0x00;
    uint8_t ppu_data_buffer = 0x00;
    uint16_t ppu_addr = 0x0000;
};

#endif