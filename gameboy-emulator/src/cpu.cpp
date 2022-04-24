#include "include/cpu.h"
#include <iostream>


CPU::CPU(MMU *mmu): r(Registers()), mmu(mmu), t(0), ime(IME::Disabled), hit(NOT_TRIGGERED) {
    isr = ISR::INACTIVE;
    update();
    cycles = 0;
    halted = false;
    #ifndef DEBUG
    connect(mmu, &MMU::accessHalt, this, &CPU::accessHaltSlot);
    #endif
}

uint64_t CPU::cycle() {

    if (isr != ISR::INACTIVE) {
        if (isr == ISR::NOPS) {
            isr = ISR::PUSH;
            return 2;
        } else if (isr == ISR::PUSH) {
            push(r._pc);
            isr = ISR::JMP;
            return 2;
        } else {
            call(handler);
            isr = ISR::INACTIVE;
            return 1;
        }
    }

    if (ime == IME::Enabled) {
        int n;
        for (int i = 0; i < 5; ++i) {
            n = (1 << i);
            if (n & mmu->ff0f & mmu->ffff) {
                ime = IME::Disabled;
                isr = ISR::NOPS;
                mmu->ff0f &= !n;
                handler = 0x0040 | (i << 3);
                return 0;
            }
        }
    }

    if (ime == IME::OneCycleDelay) {
        ime = IME::Enabled;
    }

    cycles++;

    // if (r._pc == 0x00) {
    // if (cycles == 6300) {
        // exit(0);
    // }

    auto code = byte();

    // std::cout << std::dec <<  (int) cycles << " --- " << std::hex << (int) code << std::dec << std::endl;
    // std::cout << std::hex << (int) code << std::dec << std::endl;
    // std::cout << r.toString() << std::endl;


    auto v = opcode(code);
    if (code == 0x40) {
        halted = true;
        // std::cout << "Halted" << std::endl;
    }
    // TODO - change this to only emit the ones changed
    // update();
    return v;
}


void CPU::update() {

    // std::cout << r.toString() << std::endl;;
    #ifndef DEBUG
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
    #endif
}

#ifndef DEBUG
void CPU::accessHaltSlot(ADDRESS_ACCESS r, uint16_t address) {
    std::cout << "Halted on address " << address << " " << r << std::endl;
    emit accessHaltSignal(r, address);
}
#endif
