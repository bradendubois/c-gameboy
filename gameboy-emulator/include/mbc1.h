#ifndef MBC1_H
#define MBC1_H

class MBC1: public MBC {

    public:
        MBC1(std::vector<uint8_t> *data);
        ~MBC1() = default;
        uint8_t read(uint16_t address) override;
        void write(uint16_t address, uint8_t value) override;

    private:
        std::vector<uint8_t> ram;
        bool ramEnable;
        uint8_t bank1, bank2, bankingMode;
        // get this from cartridge
        uint8_t bankMask;
};

#endif
