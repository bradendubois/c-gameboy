#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <vector>
#include <string>
#include <stdint.h>

#include "include/mbc.h"

class Cartridge {

    public:
        Cartridge(std::vector<uint8_t> *c);
        ~Cartridge() {
            delete mbc;
        };

        std::string toString() {
            return "Title: " + _title;
        }

        std::string title() {
            return _title;
        }

        MBC *mbc;

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
