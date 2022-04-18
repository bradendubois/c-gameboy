#ifndef MBC_H
#define MBC_H

#include <stdint.h>
#include <vector>

const uint16_t ROM_BANK_SIZE = 0x4000;
const uint16_t RAM_BANK_SIZE = 0x2000;

class MBC {

    public:
        MBC(std::vector<uint8_t> *data): data(data) {};
        virtual ~MBC() = default;
        virtual uint8_t read(uint16_t address) { return 0; }
        virtual void write(uint16_t address, uint8_t value) {};

    protected:
        std::vector<uint8_t> *data;
};

#endif
