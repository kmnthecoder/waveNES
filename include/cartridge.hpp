#ifndef CARTRIDGE_HPP
#define CARTRIDGE_HPP

#include "mapper0.hpp"

#include <cstdint>
#include <vector>
#include <string>
#include <memory>

class Cartridge
{
public:
    Cartridge(const std::string &file);
    ~Cartridge();

    bool cpuRead(int16_t addr, uint8_t &data);
    bool cpuWrite(uint16_t addr, uint8_t data);

    bool ppuRead(int16_t addr, uint8_t &data);
    bool ppuWrite(uint16_t addr, uint8_t data);

    // REMOVE
    bool ImageValid();

private:
    std::vector<uint8_t> PRGMemory;
    std::vector<uint8_t> CHRMemory;

    uint8_t mapperID = 0;
    uint8_t PRGBanks = 0;
    uint8_t CHRBanks = 0;

    std::shared_ptr<Mapper> mapper;

    // REMOVE
    bool bImageValid = false;
};

#endif