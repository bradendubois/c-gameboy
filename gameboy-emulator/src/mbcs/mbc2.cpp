#include "include/mbcs/mbc2.h"

#include <iostream>

#include <iomanip>
#include <sstream>
#include <vector>

MBC2::MBC2(std::vector<uint8_t> *data): MBC(data)
{
    ram = std::vector<uint8_t>(0x200, 0);
    bank1 = 0x01;
    ramg = false;
    computeRomOffset();
}

uint8_t MBC2::read(uint16_t address) {
    switch (address) {
        case 0x0000 ... 0x7FFF:
            return MBC::_read(address);
        case 0xA000 ... 0xBFFF:
            if (!ramg) return 0x0F;
            return ram[address & 0x01FF];
        default:
            std::cerr << "Impossible MBC address" << std::endl;
            return 0;
    }
}

void MBC2::write(uint16_t address, uint8_t value) {
    switch (address) {
        case 0x0000 ... 0x3FFF:
            if ((value & 0x80) == 0) {
                ramg = (value & 0x0F) == 0x0A;
            } else {
                bank1 = (value & 0x0F);
                if (bank1 == 0) bank1 = 0x01;
                computeRomOffset();
            }
            break;
        case 0x4000 ... 0x7FFF:
            break;
        case 0xA000 ... 0xBFFF: {
            if (!ramg) {
                return;
            }
            ram[address & 0x01FF] = value & 0x0F;
            break;
        }
            
        default:
            throw std::invalid_argument("Impossible cartridge write address: " + std::to_string(address));
    }
}


void MBC2::computeRomOffset() {
    bank1_offset = 0x0000;
    bank2_offset = bank1 * ROM_BANK_SIZE;
}

void MBC2::computeRamOffset() {}
