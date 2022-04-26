#include "include/mbcs/mbc.h"

#include <iomanip>
#include <iostream>
#include <sstream>

int getRam(uint8_t v) {
    // std::cout << "Val " << (int) v << std::endl;
    switch (v) {
        case 0:
            return 0x0;
        case 1:
            return 0x800;
        case 2:
            return 0x2000;
        case 3:
            return 0x8000;
        case 4:
            return 0x20000;
        case 5:
            return 0x10000;
        default:
            std::cerr << "Unknown RAM value" << std::endl;
            exit(1);
            return 0;
    }
}


uint8_t MBC::_read(uint16_t address) {
    // std::cout << "READ " << std::hex << (int) address << std::dec << " " << (int) address << std::endl;
    switch (address) {
        case 0x0000 ... 0x3FFF:
            return data->at((bank1_offset | address) & (data->size() - 1));
        case 0x4000 ... 0x7FFF:
            return data->at((bank2_offset | (address & (ROM_BANK_SIZE - 1))) & (data->size() - 1));
        case 0xA000 ... 0xBFFF: {
            if (!ramg || (ram.size() == 0)) {
                return 0xFF;
            }
            return ram[(ram_offset | (address & (RAM_BANK_SIZE - 1))) & (ram.size() - 1)];
        }
        default:
            throw std::invalid_argument("Impossible cartridge read address: " + std::to_string(address));
    }
}
