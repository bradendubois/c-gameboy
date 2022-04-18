#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>

#include "include/mmu.h"

class Serial {

    public:
        Serial(MMU *mmu): ff01(0x00), ff02(0x01), mmu(mmu) {};
        ~Serial() = default;
        uint8_t read(uint16_t address);
        void write(uint16_t address, uint8_t value);

    private:
        uint8_t ff01, ff02;
        MMU *mmu;
};

#endif
