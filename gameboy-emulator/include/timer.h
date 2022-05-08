#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <stdint.h>

class MMU;

#include "include/mmu.h"

class Timer {

    public:
        Timer(MMU *mmu);
        ~Timer() = default;
        uint8_t read(uint16_t address);
        void write(uint16_t address, uint8_t value);
        void cycle(uint64_t cycles);
        void initialize(GAMEBOY_MODEL MODEL);
    
    private:
        MMU *mmu;
        uint8_t ff04, ff05, ff06, ff07;
        uint64_t divtank, timtank, step;
        bool enabled;
};

#endif
