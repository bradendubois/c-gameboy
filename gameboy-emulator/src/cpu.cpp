#include "include/cpu.h"
#include <iostream>


CPU::CPU(MMU *mmu): r(Registers()), mmu(mmu), cb(false), t(0), ime(IME::Disabled), hit(NOT_TRIGGERED) {

    update();

    connect(mmu, &MMU::accessHalt, this, &CPU::accessHaltSlot);
}

uint64_t CPU::cycle() {
    auto v = opcode(byte());
    update();
    return v;
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

void CPU::accessHaltSlot(ADDRESS_ACCESS r, uint16_t address) {
    std::cout << "Halted on address " << address << " " << r << std::endl;
    emit accessHaltSignal(r, address);
}
