#include "include/cpu.h"
#include <iostream>
#include "gui/include/metaRegisters.h"

CPU::CPU(Gameboy *parent, Cartridge *cartridge): parent(parent), r(Registers()), mmu(MMU(cartridge)), cb(false), t(0), ime(IME::Disabled) {

    emit updateRegister(R_A, r._a);
    emit updateRegister(R_F, r._f);
    emit updateRegister(R_B, r._b);
    emit updateRegister(R_C, r._c);
    emit updateRegister(R_D, r._d);
    emit updateRegister(R_E, r._e);
    emit updateRegister(R_H, r._h);
    emit updateRegister(R_L, r._l);
    emit updateRegister(R_PC, r._pc);
    emit updateRegister(R_SP, r._sp);

}

void CPU::run() {

    uint8_t code = 0, prev = 0;
    int cycles = 0;
    std::cout << std::hex;
    // std::cout << r.toString();

    while (1) {

        prev = code;
        code = byte();
        
        // if (cycles == 16450) {
        //     exit(0);
        // }

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


void CPU::update() {

    emit updateRegister(R_A, r._a);
    emit updateRegister(R_F, r._f);
    emit updateRegister(R_B, r._b);
    emit updateRegister(R_C, r._c);
    emit updateRegister(R_D, r._d);
    emit updateRegister(R_E, r._e);
    emit updateRegister(R_H, r._h);
    emit updateRegister(R_L, r._l);
    emit updateRegister(R_PC, r._pc);
    emit updateRegister(R_SP, r._sp);

}