#ifndef MBC_H
#define MBC_H

#include <stdint.h>
#include <vector>

const uint16_t ROM_BANK_SIZE = 0x4000;
const uint16_t RAM_BANK_SIZE = 0x2000;

class MBC {

    public:
        MBC(std::vector<uint8_t> *data):
            data(data),
            ram(std::vector<uint8_t>(0x2000, 0)),
            ramEnable(false),
            romBankNumber(0x01),
            ramBankNumber(0x00),
            bankingMode(0x00)
            {};
        uint8_t read(uint16_t address);
        uint8_t write(uint16_t address, uint8_t value);

    protected:
        std::vector<uint8_t> *data;
        std::vector<uint8_t> ram;
        bool ramEnable;
        uint8_t romBankNumber;
        uint8_t ramBankNumber;
        uint8_t bankingMode;
};

#endif
