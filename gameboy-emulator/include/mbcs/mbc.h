#ifndef MBC_H
#define MBC_H

#include <stdint.h>
#include <vector>

const uint64_t ROM_BANK_SIZE = 0x4000;
const uint64_t RAM_BANK_SIZE = 0x2000;

int getRam(uint8_t v);

class MBC {

    public:
        MBC(std::vector<uint8_t> *data): data(data), ramg(false) { }
        virtual ~MBC() = default;
        virtual void computeRomOffset() = 0;
        virtual void computeRamOffset() = 0;
        virtual void write(uint16_t address, uint8_t value) { (void) address; (void) value; }
        virtual uint8_t read(uint16_t address) = 0;
        uint8_t _read(uint16_t address);

    protected:
        std::vector<uint8_t> *data, ram;
        uint64_t bank1, bank2, bank1_offset, bank2_offset, ram_offset;
        bool ramg, mode;
};

#endif
