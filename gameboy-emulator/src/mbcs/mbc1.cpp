#include "include/mbc.h"
#include "include/mbc1.h"

#include <iostream>

int getRam(uint8_t v) {
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
            return 0;
    }
}

MBC1::MBC1(std::vector<uint8_t> *data): MBC(data),
            ramEnable(false),
            romBankNumber(0x01),
            ramBankNumber(0x00),
            bankingMode(0x00) {
    // std::cout << "TYPE" << (int) data->at(0x147) << std::endl;
    // std::cout << "RAM SIZE " << getRam(data->at(0x149)) << std::endl;
    
    auto y = getRam((uint8_t) data->at(0x0149));
    if (y != 0) {
        ram = std::vector<uint8_t>(y, 0);
    } else {
        ram = {};
    }

    bankMask = (1 << (data->at(0x148) + 1)) - 1;
}

uint8_t MBC1::read(uint16_t address) {
    // std::cout << "READ " << std::hex << (int) address << std::dec << " " << (int) address << std::endl;
    auto v = (ROM_BANK_SIZE * romBankNumber) | ((address) & ROM_BANK_SIZE - 1);

    switch (address) {
        case 0x0000 ... 0x3FFF:
            return data->at(address);
        case 0x4000 ... 0x7FFF: {
            uint16_t addr = (ROM_BANK_SIZE * romBankNumber) | ((address) & (ROM_BANK_SIZE - 1));
            return data->at(addr);
        }
        case 0xA000 ... 0xBFFF:
            if (!ramEnable) {
                return 0;
            }
            return (bankingMode == 0 ? ram[address & (RAM_BANK_SIZE - 1)] : ram[(ramBankNumber * RAM_BANK_SIZE) | (address & (RAM_BANK_SIZE - 1))]);
        default:
            throw std::invalid_argument("Impossible cartridge read address: " + std::to_string(address));
    }
}

void MBC1::write(uint16_t address, uint8_t value) {
    switch (address) {
        case 0x0000 ... 0x1FFF:
            ramEnable = (value & 0x0A) == 0x0A;
            break;
        case 0x2000 ... 0x3FFF:
            romBankNumber = ((romBankNumber & 0x60) | (value & 0x1F)) & bankMask;
            break;
        case 0x4000 ... 0x5FFF:
            if (bankingMode == 0) {
                romBankNumber = (romBankNumber & 0x1F) | ((value & 0x03) << 5); 
            } else {
                ramBankNumber = value & 0x03;
            }
            break;
        case 0x6000 ... 0x7FFF:
            bankingMode = value & 0x01;
            break;
        case 0xA000 ... 0xBFFF:
            if (ramEnable) {
                size_t x = ((bankingMode == 1 ? ramBankNumber : 0) * RAM_BANK_SIZE) | (address & (RAM_BANK_SIZE - 1));
                if (x >= ram.size()) {
                    // std::cerr << "HOLY SHIT" << (int) ram.size() <<  " v " << x << std::endl;
                    // return;
                }
                ram[(((bankingMode == 1 ? ramBankNumber : 0) * RAM_BANK_SIZE) | address & (RAM_BANK_SIZE - 1)) % ram.size()] = value;
            }
            break;

        default:
            throw std::invalid_argument("Impossible cartridge write address: " + std::to_string(address));
    }
}
