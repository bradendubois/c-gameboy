#ifndef SOUND_H
#define SOUND_H

#include <stdint.h>

class Sound {

    public:
        Sound() {};
        uint8_t read(uint16_t address);
        void write(uint16_t address, uint8_t value);
};

#endif
