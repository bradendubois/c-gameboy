#ifndef GAMEBOY_H
#define GAMEBOY_H

#include "cpu.h"
#include "mmu.h"

#include <vector>

class Gameboy {

    public:
        Gameboy(std::vector<int> & cartridge): cpu(CPU(cartridge)) {};

    private:
        CPU cpu;

};

#endif
