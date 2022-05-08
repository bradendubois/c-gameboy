#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <vector>
#include <string>
#include <stdint.h>

#include "include/mbcs/mbc.h"

const uint8_t NINTENDO_LOGO_BYTES[48]{0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D, 0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E, 0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E};

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
        bool containsNintendoLogo(uint16_t address = 0x0104);
        uint16_t computeHeaderChecksum();

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
