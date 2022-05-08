#include <iostream>

#include "include/cartridge.h"

#include "include/mbcs/mbc.h"
#include "include/mbcs/mbc0.h"
#include "include/mbcs/mbc1.h"
#include "include/mbcs/mbc2.h"
#include "include/mbcs/mbc5.h"


static std::string stringSlice(std::vector<uint8_t> *buffer, int start, int end) {
    std::string r = "";
    for (int i = start; i <= end; ++i) {
        r += buffer->at(i);
    }
    return r;
}

MBC* createMBC(std::vector<uint8_t> *data) {
    switch (data->at(0x147)) {
        case 0x00:
            return new MBC0(data);
        case 0x01 ... 0x03:
            return new MBC1(data);
        case 0x05 ... 0x06:
            return new MBC2(data);
        case 0x19 ... 0x1E:
            return new MBC5(data);
        default:
            std::cerr << "Unknown MBC type " << (int) data->at(0x147) << std::endl;
            exit(1);
    }
}

Cartridge::Cartridge(std::vector<uint8_t> *c):
            mbc(createMBC(c)),
            _title(stringSlice(c, 0x0134, 0x0143)),
            // manufacturer(stringSlice(c, 0x013F, 0x0142)),
            cgb_flag(c->at(0x0143)),
            // new_licensee_code(stringSlice(c, 0x0144, 0x0145)),
            sgb_flag(c->at(0x0146)),
            cartridge_type(c->at(0x0147)),
            rom_size(c->at(0x0148)),
            ram_size(c->at(0x0149)),
            destination_code(c->at(0x014A)),
            old_licensee_code(c->at(0x014B)),
            mask_rom_number(c->at(0x014C)),
            header_checksum(c->at(0x014D)),
            global_checksum((c->at(0x014E) << 8) | c->at(0x014F)) {

}

bool Cartridge::containsNintendoLogo(uint16_t address)
{
    for (uint16_t o = 0; o < 48; ++o) {
        if (mbc->read(address) != NINTENDO_LOGO_BYTES[o]) {
            return false;
        }
    }

    return true;
}

uint16_t Cartridge::computeHeaderChecksum()
{
    uint16_t x = 0;
    for (uint16_t i = 0x0134; i <= 0x014C; ++i) {
        x = x - mbc->read(i) - 1;
    }
    return x;
}
