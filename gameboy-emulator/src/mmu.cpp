#include <stdint.h>

#include "include/gui_breakpoints.h"
#include "include/mmu.h"

uint8_t MMU::read(uint16_t address) {
    if (watchReads.contains(address)) {
        emit accessHalt(ADDRESS_ACCESS::READ, address);
    }
    switch (address) {
        case 0x0000 ... 0x7FFF:
            return mbc.read(address);
        case 0xA000 ... 0xBFFF:
            return mbc.read(address);
        case 0xC000 ... 0xDFFF:
            return w_ram[address & (W_RAM_SIZE - 1)];
        case 0xE000 ... 0xFDFF:
            return read(address & 0xDDFF);
        case 0xFE00 ... 0xFE9F:
            return 0;
        case 0xFEA0 ... 0xFEFF:
            return 0;
        case 0xFF00 ... 0xFF7F: {
            switch (address) {
                case 0xFF00:
                    return joypad.read();
                case 0xFF01 ... 0xFF02:
                    return serial.read(address);
                case 0xFF04 ... 0xFF07:
                    return timer.read(address);
                default:
                    return 0;
            }
        }
        case 0xFF80 ... 0xFFFE:
            return 0;
        case 0xFFFF ... 0xFFFF:
            return 0;

        default:
            std::cerr << "UNAUTH RAM READ " << std::hex << address << std::dec << std::endl;
            exit(0);
    }
}

void MMU::write(uint16_t address, uint8_t value) {
    if (watchWrites.contains(address)) {
        emit accessHalt(ADDRESS_ACCESS::WRITE, address);
    }
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
        case 0xFE00 ... 0xFE9F:
            break;
        case 0xFEA0 ... 0xFEFF:
            break;
        case 0xFF00 ... 0xFF7F: {
            switch (address) {
                case 0xFF00:
                    joypad.write(value);
                    break;
                case 0xFF01 ... 0xFF02:
                    serial.write(address, value);
                    break;
                case 0xFF04 ... 0xFF07:
                    timer.write(address, value);
                    break;
                default:
                    return;
            }
            break;
        }
        case 0xFF80 ... 0xFFFE:
            break;
        case 0xFFFF ... 0xFFFF:
            break;

        default:
            std::cerr << "UNAUTH RAM WRITE " << std::hex << address << std::dec << std::endl;
            exit(0);
            return;
    }
}

void MMU::watchAddress(ADDRESS_ACCESS r, uint16_t address) {
    switch (r) {
        case ADDRESS_ACCESS::READ:
            watchReads.insert(address);
            break;
        case ADDRESS_ACCESS::WRITE:
            watchWrites.insert(address);
            break;
        default:
            break;
    }
}