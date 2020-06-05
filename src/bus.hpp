#ifndef BUS_HPP
#define BUS_HPP

#include "cpu.hpp"

#include <cstdint>
#include <array>

class Bus
{
public:
    Bus();
    ~Bus();

    std::array<uint8_t, 64 * 1024> ram; // 64Kb
    CPU cpu;

    uint8_t read(int16_t addr, bool readOnly = false);
    void write(uint16_t addr, uint8_t data);
};

#endif