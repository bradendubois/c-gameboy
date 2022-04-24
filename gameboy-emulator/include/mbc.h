#ifndef MBC_H
#define MBC_H

#include <stdint.h>
#include <vector>

const uint64_t ROM_BANK_SIZE = 0x4000;
const uint64_t RAM_BANK_SIZE = 0x2000;

int getRam(uint8_t v);

class MBC {

    public:
        MBC(std::vector<uint8_t> *data): data(data) {};
        virtual ~MBC() = default;
        virtual uint8_t read(uint16_t address) { (void) address; return 0; }
        virtual void write(uint16_t address, uint8_t value) { (void) address; (void) value; };

    protected:
        std::vector<uint8_t> *data;
};

#endif
