#include <iostream>

#include "include/mbc.h"
#include "include/mbc0.h"

uint8_t MBC0::read(uint16_t address) {
    switch (address) {
        case 0x0000 ... 0x7FFF:
            return data->at(address);
        default:
            return 0;
    }
}

void MBC0::write(uint16_t address, uint8_t value) { }
