#ifndef MBC5_H
#define MBC5_H

#include "include/mbcs/mbc.h"

class MBC5: public MBC {

    public:
        MBC5(std::vector<uint8_t> *data);
        ~MBC5() = default;
        uint8_t read(uint16_t address) override;
        void write(uint16_t address, uint8_t value) override;
        void computeRomOffset() override;
        void computeRamOffset() override;

    private:
        uint64_t ram_offset, ram_bank;
};

#endif
