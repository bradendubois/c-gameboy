#include "../include/cpu.h"
#include <iostream>

void CPU::run() {

    uint8_t code = 0, prev = 0;
    int cycles = 0;
    std::cout << std::hex;
    // std::cout << r.toString();

    while (1) {

        prev = code;
        code = byte();
        
        if (cycles == 16450) {
            exit(0);
        }

        if (code == 0x40) {
            std::cout << "DONE" << std::endl;
            exit(0);
        }

        std::cout << "#" << std::dec << (int) cycles << std::endl;
        std::ostringstream ss;
        ss << std::setfill('0') << std::setw(4) << std::hex << (int) code;
        std::cout << "Executing 0x" << ss.str() << std::endl;
        std::cout << r.toString() << std::endl;;        
        opcode(code);
        std::cout << r.toString() << "\n\n\n" << std::endl;;        
        cycles++;

    }
}
