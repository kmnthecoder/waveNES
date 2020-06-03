#ifndef CPU_HPP
#define CPU_HPP

#include <cstdint>

class CPU
{
    public:
    private:
        uint8_t reg_a;
        uint8_t reg_x;
        uint8_t reg_y;

        uint8_t p_flag;
        uint8_t sp;
        uint16_t pc;
        
};

#endif