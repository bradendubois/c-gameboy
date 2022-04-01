#include "../include/mmu.h"

uint8_t MMU::read(uint16_t address) {
    switch (address) {
        case 0x0000 ... 0x7FFF:
            return mbc.read(address);
        case 0xA000 ... 0xBFFF:
            return mbc.read(address);
        case 0xC000 ... 0xDFFF:
            return w_ram[address & (W_RAM_SIZE - 1)];
        case 0xE000 ... 0xFDFF:
            return read(address & 0xDDFF);
        default:
            std::cerr << "UNAUTH RAM READ " << std::hex << address << std::dec << std::endl;
            exit(0);
    }
}

void MMU::write(uint16_t address, uint8_t value) {
    switch (address) {
        case 0x0000 ... 0x7FFF:
            mbc.write(address, value);
            break;
        case 0xA000 ... 0xBFFF:
            mbc.write(address, value);
            break;
        case 0xC000 ... 0xDFFF:
            w_ram[address & (W_RAM_SIZE - 1)] = value;
            break;
        case 0xE000 ... 0xFDFF:
            write(address & 0xDDFF, value);
            break;
        default:
            std::cerr << "UNAUTH RAM WRITE " << std::hex << address << std::dec << std::endl;
            exit(0);
            return;
    }
}
