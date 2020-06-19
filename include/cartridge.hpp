#ifndef CARTRIDGE_HPP
#define CARTRIDGE_HPP

#include <cstdint>
#include <vector>
#include <string>
#include <memory>
#include <fstream>

#include "mapper0.hpp"


class Cartridge
{
public:
    Cartridge(const std::string &file);
    ~Cartridge();

    bool cpuRead(uint16_t addr, uint8_t &data);
    bool cpuWrite(uint16_t addr, uint8_t data);

    bool ppuRead(uint16_t addr, uint8_t &data);
    bool ppuWrite(uint16_t addr, uint8_t data);

    bool ImageValid();

    void reset();

    enum MIRROR
    {
        HORIZONTAL,
        VERTICAL,
        ONESCREEN_LO,
        ONESCREEN_HI
    } mirror = HORIZONTAL;

private:
    std::vector<uint8_t> PRGMemory;
    std::vector<uint8_t> CHRMemory;

    uint8_t mapperID = 0;
    uint8_t PRGBanks = 0;
    uint8_t CHRBanks = 0;

    std::shared_ptr<Mapper> mapper;

    bool bImageValid = false;
};

#endif