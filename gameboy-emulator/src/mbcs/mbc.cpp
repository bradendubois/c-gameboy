#include "include/mbc.h"
#include <iostream>

int getRam(uint8_t v) {
    // std::cout << "Val " << (int) v << std::endl;
    switch (v) {
        case 0:
            return 0x0;
        case 1:
            return 0x800;
        case 2:
            return 0x2000;
        case 3:
            return 0x8000;
        case 4:
            return 0x20000;
        case 5:
            return 0x10000;
        default:
            std::cerr << "Unknown RAM value" << std::endl;
            exit(1);
            return 0;
    }
}
