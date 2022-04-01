#ifndef MBC1_H
#define MBC1_H

class MBC1: MBC {

    public:
        MBC1(std::vector<uint8_t> & data): MBC(data) {};
        uint8_t read(uint16_t address);
        void write(uint16_t address, uint8_t value);
};

#endif
