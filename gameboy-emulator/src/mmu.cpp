#include "../include/mmu.h"

uint8_t MMU::byte() {
    uint8_t value = cartridge.at(cpu.r._pc);
    cpu.r._pc += 1;
    return value;
}

uint16_t MMU::word() {
    return byte() | (((uint16_t) byte()) << 8);
}

uint8_t MMU::read(uint16_t address) {
    return cartridge.at(address);
}

void MMU::write(uint16_t address, uint8_t value) {
    cartridge[address] = value;
}

void MMU::write(uint16_t address, uint16_t value) {
    cartridge[address] = value;
    write(address, (uint8_t) value);
    write(address + 1, (uint8_t) (value >> 8));
}
