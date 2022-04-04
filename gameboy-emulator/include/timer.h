#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

class Timer {

    public:
        Timer(): ff04(0x00), ff05(0x00), ff06(0x00), ff07(0x00) {};
        uint8_t read(uint16_t address);
        void write(uint16_t address, uint8_t value);

    private:
        uint8_t ff04, ff05, ff06, ff07;
};

#endif
