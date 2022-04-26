#include <iostream>

#include "include/mbcs/mbc0.h"

uint8_t MBC0::read(uint16_t address) {
    return MBC::_read(address);
}

void MBC0::write(uint16_t address, uint8_t value)
{
    (void) address;
    (void) value;
}

void MBC0::computeRomOffset() { }
void MBC0::computeRamOffset() { }
