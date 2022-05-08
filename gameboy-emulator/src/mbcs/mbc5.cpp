#include "include/mbcs/mbc5.h"

#include <iostream>

#include <iomanip>
#include <sstream>
#include <vector>

MBC5::MBC5(std::vector<uint8_t> *data): MBC(data)
{
    ram = std::vector<uint8_t>(RAM_BANK_SIZE, 0);
    bank1 = 0x01;
    bank2 = 0x00;
    ramg = false;
    ram_bank = 0x00;

    computeRomOffset();
    computeRamOffset();
}

uint8_t MBC5::read(uint16_t address) {
    return MBC::_read(address);
}

void MBC5::write(uint16_t address, uint8_t value) {
    switch (address) {
        case 0x0000 ... 0x1FFF:
            ramg = value == 0x0A;
            break;
        case 0x2000 ... 0x2FFF:
            bank1 = value;
            computeRomOffset();
            break;
        case 0x3000 ... 0x3FFF:
            bank2 = value & 0x01;
            computeRomOffset();
            break;
        case 0x4000 ... 0x5FFF:
            ram_bank = value & 0x0F;
            computeRamOffset();
        case 0xA000 ... 0xBFFF: {
            if (!ramg) {
                return;
            }
            ram[(ram_offset | address) & (ram.size() - 1)] = value;
            break;
        }
            
        default:
            throw std::invalid_argument("Impossible cartridge write address: " + std::to_string(address));
    }
}


void MBC5::computeRomOffset() {
    bank1_offset = 0x0000;
    bank2_offset = ((bank2 << 8) | bank1) * ROM_BANK_SIZE;
}

void MBC5::computeRamOffset() {
    ram_offset = ram_bank * RAM_BANK_SIZE;
}
