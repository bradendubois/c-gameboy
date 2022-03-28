#ifndef MMU_H
#define MMU_H

#include <stdint.h>
#include <vector>

class MMU {

    public:
        MMU(std::vector<int> & cartridge): cartridge(cartridge) {};

        uint8_t  byte(uint16_t address);
        uint16_t word(uint16_t address);

        uint8_t read(uint16_t address);
        uint16_t read_word(uint16_t address);

        void write(uint16_t address, uint8_t value);
        void write(uint16_t address, uint16_t value);

    private:
        // CPU & cpu;
        std::vector<int> cartridge;
};

#endif
