#include "include/mbc.h"
#include "include/mbc1.h"

#include <iostream>

MBC1::MBC1(std::vector<uint8_t> *data): MBC(data),
            ramEnable(false),
            bank1(0x01),
            bank2(0x00),
            bankingMode(0x00) {
    // std::cout << "TYPE" << (int) data->at(0x147) << std::endl;
    // std::cout << "RAM SIZE " << getRam(data->at(0x149)) << std::endl;
    
    auto y = getRam((uint8_t) data->at(0x149));
    if (y != 0) {
        ram = std::vector<uint8_t>(y, 0);
    } else {
        ram = {};
    }

    bankMask = (1 << (data->at(0x148) + 1)) - 1;
}

#include <iomanip>
#include <iostream>
#include <sstream>

std::string hexout(int digits, uint16_t value) {
std::ostringstream ss;
ss << std::setfill('0') << std::setw(digits) << std::hex << std::uppercase << value;
return "0x" + ss.str();
}

uint8_t MBC1::read(uint16_t address) {
    // std::cout << "READ " << std::hex << (int) address << std::dec << " " << (int) address << std::endl;
    switch (address) {
        case 0x0000 ... 0x3FFF: {

            int addr = address;

            if (bankingMode == 0) {
                // std::cout << "L " << hexout(8, (addr & (data->size() - 1))) << " " << hexout(8, 0) << std::endl;
                return data->at(address);
            }
            // int shift = ( ? 4 : 5);
            addr = ((bank2 << 5) * ROM_BANK_SIZE) | address;        
            int offset = (bank2 << 5) * ROM_BANK_SIZE;
            // std::cout << "L " << hexout(8, (addr & (data->size() - 1))) << " " << hexout(8, offset) << std::endl;
            
            return data->at(addr & (data->size() - 1));
        }
        case 0x4000 ... 0x7FFF: {
            uint64_t bank = (bank2 << 5) | bank1;
            uint64_t offset = bank * ROM_BANK_SIZE;
            uint64_t addr = ((ROM_BANK_SIZE * bank) | ((address) & (ROM_BANK_SIZE - 1))) & (data->size() - 1);
            // std::cout << "H " << hexout(8, addr) << " " << hexout(8, offset) << " " << (int) bank2 << " " << (int) bank1 << " " << (int) offset << std::endl;
            return data->at(addr);
        }
        case 0xA000 ... 0xBFFF: {
            if (!ramEnable) {
                return 0xFF;
            }

            int bank = bankingMode == 0 ? 0 : bank2;
            int addr = ((bank * RAM_BANK_SIZE) | (address & (RAM_BANK_SIZE - 1))) & (ram.size() -1);
            return ram[addr];
        }
        default:
            throw std::invalid_argument("Impossible cartridge read address: " + std::to_string(address));
    }
}

void MBC1::write(uint16_t address, uint8_t value) {
    if (address < 0xA000) {
        // std::cout << std::hex << (int) address << " " << (int) value << std::dec << std::endl; 
    }
    switch (address) {
        case 0x0000 ... 0x1FFF:
            ramEnable = (value & 0x0F) == 0x0A;
            break;
        case 0x2000 ... 0x3FFF:
            bank1 = value & 0x1F;
            if (bank1 == 0) bank1 = 0x01;
            // std::cout << "b1 " << (int) bank1 << std::endl;
            break;
        case 0x4000 ... 0x5FFF:
            bank2 = value & 0x03;
            // std::cout << "b2 " << (int) bank2 << std::endl;
            break;
        case 0x6000 ... 0x7FFF:
            bankingMode = (value & 0x01) == 0x01;
            // std::cout << "m " << (bankingMode ? "true" : "false") << std::endl;
            break;
        case 0xA000 ... 0xBFFF: {
            if (!ramEnable) {
                return;
            }
            int bank = bankingMode == 1 ? bank2 : 0;
            int addr = ((bank * RAM_BANK_SIZE) | (address & (RAM_BANK_SIZE - 1))) & (ram.size() - 1);
            // std::cout << std::hex << addr << " - " << (int) value << " - " << (int) bank2 << " " << (ram.size()) << std::dec << std::endl;
            ram[addr] = value;
            break;
        }
            
        default:
            throw std::invalid_argument("Impossible cartridge write address: " + std::to_string(address));
    }
}
