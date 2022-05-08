#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>

#ifdef DEBUG
#include "include/other/testing.h"
#endif

#include "include/other/constants.h"

#include "include/mmu.h"

class Serial {

    public:
        Serial(MMU *mmu): ff01(0x00), ff02(0x01), rotation(0), counter(0), mmu(mmu) {};
        ~Serial() = default;
        uint8_t read(uint16_t address);
        void write(uint16_t address, uint8_t value);
        void advanceCycles(uint64_t cycles);

        // void debug(DEBUG_PARAMETER p, ACCESS_TIME t, DEBUG_RESPONSE r);

    protected:
        void debug(Breakpoint b);
        friend class MMU;

    private:
        uint8_t ff01, ff02, rotation;
        uint16_t counter;
        MMU *mmu;

        DEBUG_RESPONSE sWrite = DEBUG_RESPONSE::NONE;
        void _cycle();
};

#endif
