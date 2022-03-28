#include "../include/mmu.h"

uint8_t MMU::read(uint16_t address) {
    return cartridge.at(address);
}

void MMU::write(uint16_t address, uint8_t value) {
    cartridge[address] = value;
}
