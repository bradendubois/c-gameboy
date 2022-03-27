#ifndef CPU_H
#define CPU_H

#include <stdint.h>

#include "mmu.h"
#include "registers.h"

#include <vector>

class CPU {


    public:
        CPU(std::vector<int> & cartridge): mmu(MMU(cartridge)), r(Registers()), cb(false), t(0) {};
        MMU mmu;
        Registers r;

    private:

        bool cb;
        __uint128_t t;
        __uint128_t opcode(uint8_t opcode);
        __uint128_t opcode_cb(uint8_t opcode);
};

#endif
