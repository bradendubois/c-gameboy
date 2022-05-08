#include "include/cpu.h"
#include <iostream>
#include "include/other/testing.h"

CPU::CPU(): r(Registers()), t(0), ime(IME::Disabled), hit(NOT_TRIGGERED) {
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
            // std::cout << "interrupt!" << std::endl;
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

    auto code = byte();

    // std::cout << hexout(4, (uint16_t) code) << " " << hexout(4, r.af()) << std::endl;
    // if (cycles == 3000000) exit(0);
    // if (code == 0x40) {

    if (cycles == 5000000 || opcodeWatch.contains(code))
    {
        // exit(0);
        halted = true;
        return 0;
    }

    // std::cout << std::dec <<  (int) cycles << " --- " << std::hex << (int) code << std::dec << std::endl;
    // std::cout << std::hex << (int) code << std::dec << std::endl;
    // std::cout << r.toString() << std::endl;

    auto v = opcode(code);

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

void CPU::debug(Breakpoint b)
{
    switch (b.param) {
        case DEBUG_PARAMETER::OPCODE_VALUE:
            opcodeWatch.insert(b.value);
            break;
        default:
            std::cerr << "Impossible?" << std::endl;
            break;
    }
}

void CPU::initialize(GAMEBOY_MODEL model, uint16_t checksum)
{
    r.initialize(model, checksum);
}
