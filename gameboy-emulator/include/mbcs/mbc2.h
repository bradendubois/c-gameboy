#ifndef MBC2_H
#define MBC2_H

#include "include/mbcs/mbc.h"

class MBC2: public MBC {

    public:
        MBC2(std::vector<uint8_t> *data);
        ~MBC2() = default;
        uint8_t read(uint16_t address) override;
        void write(uint16_t address, uint8_t value) override;
        void computeRomOffset() override;
        void computeRamOffset() override;
};

#endif
