#ifndef GAMEBOY_H
#define GAMEBOY_H

#include "cpu.h"
#include "mmu.h"

#include <vector>

class Gameboy {

    public:
        Gameboy(std::vector<uint8_t> *cartridge): cpu(CPU(cartridge)) {};
        
        void run();

    private:
        CPU cpu;

};

#endif
