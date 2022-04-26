#ifndef MBC1_H
#define MBC1_H

#include "include/mbcs/mbc.h"

class MBC1: public MBC {

    public:
        MBC1(std::vector<uint8_t> *data);
        ~MBC1() = default;
        uint8_t read(uint16_t address) override;
        void write(uint16_t address, uint8_t value) override;
        void computeRomOffset() override;
        void computeRamOffset() override;
};

#endif
