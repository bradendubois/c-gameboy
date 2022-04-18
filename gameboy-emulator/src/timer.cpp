#include "../include/timer.h"

Timer::Timer(MMU *mmu): ff04(0x00), ff05(0x00), ff06(0x00), ff07(0x00), step(0), divtank(0), timtank(0), enabled(false) {
    mmu->timer = this;
}

void Timer::advanceCycles(uint64_t cycles) {
    
    divtank += cycles;
    if (divtank < 256) {
        ff04 += divtank / 256;
        divtank %= 256;
    }

    if (enabled) {
        timtank += cycles;
        while (timtank > step) {
            ff05 += timtank / step;
            timtank %= step;
            if (ff05 == 0) {
                mmu->ffff |= 0x04;
            }
        }
    }
}

void Timer::write(uint16_t address, uint8_t value) {
    switch (address) {
        case 0xFF04:
            ff04 = value;
            return;
        case 0xFF05:
            ff05 = value;
            return;
        case 0xFF06:
            ff06 = value;
            return;
        case 0xFF07: {
            ff07 = value;
            enabled = (value & 0x04) != 0;
            switch (value & 0x03) {
                case 0b00:
                    step = 1024;
                    return;
                case 0b01:
                    step = 16;
                    return;
                case 0b10:
                    step = 64;
                    return;
                case 0b11:
                    step = 256;
                    return;
            }
        };
        default:
            std::cerr << "Impossible Timer address " << std::hex << (int) address << std::dec << std::endl;
            return;
    };
}

uint8_t Timer::read(uint16_t address) {
    switch (address) {
        case 0xFF04:
            return ff04;
        case 0xFF05:
            return ff05;
        case 0xFF06:
            return ff06;
        case 0xFF07: {
            return ff07;
        };
        default:
            std::cerr << "Impossible Timer address " << std::hex << (int) address << std::dec << std::endl;
            return 0;
    };
}
