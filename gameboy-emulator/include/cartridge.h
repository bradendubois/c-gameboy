#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <vector>
#include <string>
#include <stdint.h>

static std::string stringSlice(std::vector<uint8_t> *buffer, int start, int end) {
    std::string r = "";
    for (int i = start; i <= end; ++i) {
        r += buffer->at(i);
    }
    return r;
}

class Cartridge {

    public:
        Cartridge(std::vector<uint8_t> *c):
            data(c),
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
            global_checksum((c->at(0x014E) << 8) | c->at(0x014F))
        {};

        ~Cartridge() {
            // delete data;
        };

        std::string toString() {
            return "Title: " + _title;
        }

        std::string title() {
            return _title;
        }

        std::vector<uint8_t> *data;


    private:
        std::string _title;
        // std::string manufacturer;
        int cgb_flag;
        // std::string new_licensee_code;
        int sgb_flag;
        int cartridge_type;
        int rom_size;
        int ram_size;
        int destination_code;
        int old_licensee_code;
        int mask_rom_number;
        int header_checksum;
        int global_checksum;
};

#endif
