#ifndef SOUND_H
#define SOUND_H

#include <stdint.h>
#include "include/mmu.h"
class Sound {

    public:
        Sound(MMU *mmu): mmu(mmu) {};
        ~Sound() = default;
        uint8_t read(uint16_t address);
        void write(uint16_t address, uint8_t value);

    private:
        MMU *mmu;
};

#endif
