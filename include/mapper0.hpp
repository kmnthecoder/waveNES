#ifndef MAPPER0_HPP
#define MAPPER0_HPP

#include "mapper.hpp"

class Mapper0 : public Mapper
{
public:
    Mapper0(uint8_t prgBanks, uint8_t chrBanks);
    ~Mapper0();

    bool cpuMapRead(uint16_t addr, uint32_t &mapped_addr) override;
    bool cpuMapWrite(uint16_t addr, uint32_t &mapped_addr, uint8_t data = 0) override;
    bool ppuMapRead(uint16_t addr, uint32_t &mapped_addr) override;
    bool ppuMapWrite(uint16_t addr, uint32_t &mapped_addr) override;
    void reset() override;
};

#endif