#ifndef MAPPER_HPP
#define MAPPER_HPP

#include <cstdint>

class Mapper
{
public:
    Mapper(uint8_t prgBanks, uint8_t chrBanks);
    ~Mapper();

    virtual bool cpuMapRead(uint16_t addr, uint32_t &mapped_addr) = 0;
    virtual bool cpuMapWrite(uint16_t addr, uint32_t &mapped_addr, uint8_t data = 0) = 0;
    virtual bool ppuMapRead(uint16_t addr, uint32_t &mapped_addr) = 0;
    virtual bool ppuMapWrite(uint16_t addr, uint32_t &mapped_addr) = 0;

    virtual void reset() = 0;

protected:
    // stored locally
    uint8_t PRGBanks = 0;
    uint8_t CHRBanks = 0;

private:
};

#endif