#include "mapper.hpp"

Mapper::Mapper(uint8_t prgBanks, uint8_t chrBanks)
{
    PRGBanks = prgBanks;
    CHRBanks = chrBanks;
    //reset();
}

Mapper::~Mapper() {}

void Mapper::reset()
{
}