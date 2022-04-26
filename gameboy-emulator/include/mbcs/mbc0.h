#ifndef MBC0_H
#define MBC0_H

#include "include/mbcs/mbc.h"

class MBC0: public MBC {

    public:
        MBC0(std::vector<uint8_t> *data): MBC(data) {
            bank1_offset = 0x0000; 
            bank2_offset = 0x4000;
        };
        ~MBC0() = default;
        uint8_t read(uint16_t address) override;
        void write(uint16_t address, uint8_t value) override;
        void computeRomOffset() override;
        void computeRamOffset() override;
};

#endif
