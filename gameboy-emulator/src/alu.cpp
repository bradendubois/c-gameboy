#include "../include/gameboy.h"


#include "../include/cpu.h"
#include "../include/mmu.h"

#include <iostream>
#include <stdint.h>

void CPU::push(uint16_t v) {
    // if (v == 0x0169) {
        // std::cout << "Writing it too!" << std::endl;
    // }
    r._sp -= 2;
    write(r._sp, (uint16_t) v);
}

uint16_t CPU::pop() {
    uint16_t v = ((uint16_t) read(r._sp + 1)) << 8 | ((uint16_t) read(r._sp));
    r._sp += 2;
    // std::cout << "POP " << std::hex << (int) v << std::dec << std::endl;
    return v;
}

//

void CPU::call(uint16_t v) {
    push(r._pc);
    r._pc = v;
}

void CPU::ret() {
    auto v = pop();
    // std::cout << "RET " << std::hex << (int) v << std::dec << std::endl;
    r._pc = v;
}

void CPU::rst(uint8_t v) {
    call(v);
}

void CPU::jr(int8_t v) {
    r._pc = (uint16_t) (((int32_t) ((uint32_t) r._pc)) + ((uint16_t) ((int32_t) v)));
}

void CPU::jp(uint16_t v) {
    r._pc = v;
}

//

void CPU::halt() {
    // status = Status::Halted;
}

void CPU::stop() {
    mmu->write(0xFF04, (uint8_t) 0x00);
    // status = Status::Stopped;
}

//

uint8_t CPU::inc(uint8_t v) {
    uint8_t s = v + 1;
    r.flag_z(s == 0);
    r.flag_h(((v & 0x0F) + 1) > 0x0F);
    r.flag_n(false);
    return s;
}

uint8_t CPU::dec(uint8_t v) {
    uint8_t s = v - 1;
    r.flag_z(s == 0);
    r.flag_h((v & 0x0F) == 0);
    r.flag_n(true);
    return s;
}

//

void CPU::set_ime() {
    ime = IME::OneCycleDelay;
}

void CPU::unset_ime() {
    ime = IME::Disabled;
}

//

uint8_t CPU::rl(uint8_t v) {
    uint8_t s = (v << 1) | (r.flag_c() ? 0x01 : 0x00);
    r.flag_z(s == 0);
    r.flag_n(false);
    r.flag_h(false);
    r.flag_c((v & 0x80) != 0);
    return s;
}

uint8_t CPU::rr(uint8_t v) {
    uint8_t s = (v >> 1) | (r.flag_c() ? 0x80 : 0x00);
    r.flag_z(s == 0);
    r.flag_n(false);
    r.flag_h(false);
    r.flag_c((v & 0x01) != 0);
    return s;
}

uint8_t CPU::rlc(uint8_t v) {
    uint8_t s = (v << 1) | (v >> 7);
    r.flag_z(s == 0);
    r.flag_n(false);
    r.flag_h(false);
    r.flag_c((v & 0x80) != 0);
    return s;
}

uint8_t CPU::rrc(uint8_t v) {
    uint8_t s = (v >> 1) | (v << 7);
    r.flag_z(s == 0);
    r.flag_n(false);
    r.flag_h(false);
    r.flag_c((v & 0x01) != 0);
    return s;
}

//

void CPU::alu_add(uint8_t v) {
    uint8_t result = r._a + v;
    r.flag_z(result == 0);
    r.flag_n(false);
    r.flag_h(((r._a & 0x0F) + (v & 0x0F)) > 0x0F);
    r.flag_c(result < r._a);
    r._a = result;
}

void CPU::alu_add(uint16_t v) {
    uint16_t hl = r.hl();
    uint16_t result = hl + v;
    r.flag_h(((hl & 0x07FF) + (v & 0x07FF)) > 0x07FF);
    r.flag_n(false);
    r.flag_c(hl > (0xFFFF - v));
    r.hl(result);
}

uint8_t CPU::alu_sub(uint8_t v, bool carry) {
    uint8_t c = (carry && r.flag_c()) ? 0x01 : 0x00;
    uint8_t s = r._a - v - c;
    r.flag_z(s == 0);
    r.flag_n(true);
    // r.flag_h((((r._a & 0x0F) - (v & 0x0F) - c) & (0x0F + 1)) != 0);
    r.flag_h((r._a & 0x0F) < ((v & 0x0F) + c));
    r.flag_c(((uint16_t) r._a) < ((uint16_t) v + (uint16_t) c));
    return s;
}

void CPU::a_and(uint8_t v) {
    r._a &= v;
    r.flag_z(r._a == 0);
    r.flag_c(false);
    r.flag_h(true);
    r.flag_n(false);
}

void CPU::a_cp(uint8_t v) {
    alu_sub(v, false);
}

void CPU::adc(uint8_t v) {
    uint8_t carry = r.flag_c() ? 0x01 : 0x00;
    uint8_t result = r._a + v + carry;
    r.flag_z(result == 0);
    r.flag_n(false);
    r.flag_h((r._a & 0x0F) + (v & 0x0F) + carry > 0x0F);
    r.flag_c(((uint16_t) r._a + (uint16_t) v + (uint16_t) carry) > 0x00FF);
    r._a = result;
}

void CPU::a_or(uint8_t v) {
    r._a |= v;
    r.flag_z(r._a == 0);
    r.flag_n(false);
    r.flag_h(false);
    r.flag_c(false);
}

void CPU::sbc(uint8_t v) {
    r._a = alu_sub(v, true);
}

void CPU::a_xor(uint8_t v) {
    r._a ^= v;
    r.flag_z(r._a == 0);
    r.flag_n(false);
    r.flag_h(false);
    r.flag_c(false);
}

void CPU::add_16_sp(uint8_t v) {
    uint16_t x = (uint16_t) (int16_t) (int8_t) v;
    uint16_t sp = r._sp;
    r._sp += x;
    r.flag_n(false);
    r.flag_z(false);
    r.flag_h(((sp & 0x000F) + (x & 0x000F)) > 0x000F);
    r.flag_c(((sp & 0x00FF) + (x & 0x00FF)) > 0x00FF);
}

void CPU::load_16_sp_hl(uint8_t v) {
    uint16_t x = (uint16_t) (int16_t) (int8_t) v;
    uint16_t sp = r._sp;
    uint16_t result = sp + x;
    r.hl(result);
    r.flag_n(false);
    r.flag_z(false);
    r.flag_h(((sp & 0x000F) + (x & 0x000F)) > 0x000F);
    r.flag_c(((sp & 0x00FF) + (x & 0x00FF)) > 0x00FF);
}

//

uint8_t CPU::byte() {
    uint8_t value = read(r._pc);
    r._pc += 1;
    return value;
}

uint16_t CPU::word() {
    uint16_t v = ((uint16_t) byte()) | (((uint16_t) byte()) << 8);
    // std::cout << "Retrieved Word " << std::hex << (int) v << std::dec << std::endl;
    return v;
}

uint8_t CPU::read(uint16_t address) {
    uint8_t value = mmu->read(address);
    // std::cout << "Retrieved Byte " << std::hex << (int) value << std::dec << std::endl;
    return value;
}

void CPU::write(uint16_t address, uint8_t value) {
    // std::cout << "Writing value " << std::hex << (int) value << std::dec << " to address " << std::hex << address << std::dec << std::endl;
    mmu->write(address, value);
}

void CPU::write(uint16_t address, uint16_t value) {
    // std::cout << "16 bit write" << std::endl;
    write(address, (uint8_t) value);
    write(address + 1, (uint8_t) (value >> 8));
}

///

uint8_t CPU::sla(uint8_t v) {
    r.flag_c((v & 0x80) != 0);
    r.flag_z((v << 1) == 0);
    r.flag_h(false);
    r.flag_n(false);
    return v << 1;
}

uint8_t CPU::sra(uint8_t v) {
    r.flag_z((v >> 1 | (v & 0x80)) == 0);
    r.flag_h(false);
    r.flag_n(false);
    r.flag_c((v & 0x01) != 0);
    return (v >> 1) | (v & 0x80);
}

uint8_t CPU::swap(uint8_t v) {
    r.flag_z(v == 0);
    r.flag_c(false);
    r.flag_h(false);
    r.flag_n(false);
    return (v >> 4) | (v << 4);
}

uint8_t CPU::srl(uint8_t v) {
    r.flag_c((v & 0x01) != 0);
    r.flag_z((v >> 1) == 0);
    r.flag_n(false);
    r.flag_h(false);
    return v >> 1;
}

void CPU::bit(uint8_t bit, uint8_t v) {
    r.flag_z((v & (1 << bit)) == 0);
    r.flag_n(false);
    r.flag_h(true);
}

uint8_t CPU::res(uint8_t bit, uint8_t v) {
    return v & (~(1 << bit));
}

uint8_t CPU::set(uint8_t bit, uint8_t v) {
    return v | (1 << bit);
}
