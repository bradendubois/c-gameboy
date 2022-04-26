#include "include/mbcs/mbc1.h"

#include <iostream>

#include <iomanip>
#include <sstream>

MBC1::MBC1(std::vector<uint8_t> *data): MBC(data)
{
    ram = std::vector<uint8_t>(getRam((uint8_t) data->at(0x149)), 0);
    mode = false;
    bank1 = 0x01;
    bank2 = 0x00;
    ramg = false;
    computeRomOffset();
    computeRamOffset();
}

uint8_t MBC1::read(uint16_t address) {
    return MBC::_read(address);
}

void MBC1::write(uint16_t address, uint8_t value) {
    switch (address) {
        case 0x0000 ... 0x1FFF:
            ramg = (value & 0x0F) == 0x0A;
            break;
        case 0x2000 ... 0x3FFF:
            bank1 = value & 0x1F;
            if (bank1 == 0) bank1 = 0x01;
            computeRomOffset();
            break;
        case 0x4000 ... 0x5FFF:
            bank2 = value & 0x03;
            computeRomOffset();
            computeRamOffset();
            break;
        case 0x6000 ... 0x7FFF:
            mode = (value & 0x01) == 0x01;
            computeRomOffset();
            computeRamOffset();
            break;
        case 0xA000 ... 0xBFFF: {
            if (!ramg) {
                return;
            }
            ram[(ram_offset | (address & (RAM_BANK_SIZE - 1))) & (ram.size() - 1)] = value;
            break;
        }
            
        default:
            throw std::invalid_argument("Impossible cartridge write address: " + std::to_string(address));
    }
}


void MBC1::computeRomOffset() {
    bank1_offset = (mode ? (bank2 << 5) : 0x00) * ROM_BANK_SIZE;
    bank2_offset = ((bank2 << 5) | bank1) * ROM_BANK_SIZE;
}

void MBC1::computeRamOffset() {
    ram_offset = mode ? (bank2 * RAM_BANK_SIZE) : 0x00;
}