#include "../../include/mbc.h"
#include "../../include/mbc1.h"

#include <iostream>


uint8_t MBC1::read(uint16_t address) {
    switch (address) {
        case 0x0000 ... 0x3FFF:
            if (bankingMode == 0) {
                return data.at(address);
            }
            return data.at((ROM_BANK_SIZE * (ramBankNumber << 5)) | (address) & ROM_BANK_SIZE - 1);
        case 0x4000 ... 0x7FFF:
            std::cout << "LOOKUP?" << std::endl;
            return data.at((ROM_BANK_SIZE * romBankNumber) | (address) & (ROM_BANK_SIZE - 1));
        case 0xA000 ... 0xBFFF:
            if (!ramEnable) {
                return 0;
            }
            return (bankingMode == 0 ? ram[address & (RAM_BANK_SIZE - 1)] : ram[(ramBankNumber * RAM_BANK_SIZE) | address & (RAM_BANK_SIZE - 1)]);
        default:
            throw std::invalid_argument("Impossible cartridge read address: " + std::to_string(address));
    }
}

void MBC1::write(uint16_t address, uint8_t value) {
    switch (address) {
        case 0x0000 ... 0x1FFF:
            ramEnable = (value & 0x0A) != 0;
            break;
        case 0x2000 ... 0x3FFF:
            romBankNumber = value & 0x1F;
            break;
        case 0x4000 ... 0x5FFF:
            ramBankNumber = value & 0x03;
            break;
        case 0x6000 ... 0x7FFF:
            bankingMode = value & 0x01;
            break;
        case 0xA000 ... 0xBFFF:
            if (bankingMode == 0) {
                ram[address & (RAM_BANK_SIZE - 1)] = value;
            }
            break;

        default:
            throw std::invalid_argument("Impossible cartridge write address: " + std::to_string(address));
    }
}
