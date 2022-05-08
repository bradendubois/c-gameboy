#include <stdint.h>

#include "include/cpu.h"
#include "include/registers.h"

__uint128_t CPU::opcode(uint8_t opcode) {

    switch (opcode) {

        // Row 0x00-0x0F
        case 0x00:
            return 4;
        case 0x01:
            r.bc(word());
            return 12;
        case 0x02:
            write(r.bc(), r._a);
            return 8;
        case 0x03:
            r.bc(r.bc() + 1);
            return 8;
        case 0x04:
            r._b = inc(r._b);
            return 4;
        case 0x05:
            r._b = dec(r._b);
            return 4;
        case 0x06:
            r._b = byte();
            return 8;
        case 0x07:
            r._a = rlc(r._a);
            r.flag_z(false);
            return 4;
        case 0x08:
            write(word(), r._sp);
            return 20;
        case 0x09:
            alu_add(r.bc());
            return 8;
        case 0x0A:
            r._a = read(r.bc());
            return 8;
        case 0x0B:
            r.bc(r.bc() - 1);
            return 8;
        case 0x0C:
            r._c = inc(r._c);
            return 4;
        case 0x0D:
            r._c = dec(r._c);
            return 4;
        case 0x0E:
            r._c = byte();
            return 8;
        case 0x0F:
            r._a = rrc(r._a);
            return 4;

        /// Row 0x10-0x1F
        case 0x10:
            stop();
            return 4;
        case 0x11:
            r.de(word());
            return 12;
        case 0x12:
            write(r.de(), r._a);
            return 8;
        case 0x13:
            r.de(r.de() + 1);
            return 8;
        case 0x14:
            r._d = inc(r._d);
            return 4;
        case 0x15:
            r._d = dec(r._d);
            return 4;
        case 0x16:
            r._d = byte();
            return 8;
        case 0x17:
            r._a = rl(r._a);
            r.flag_z(false);
            return 4;
        case 0x18:
            jr((int8_t) byte());
            return 12;
        case 0x19:
            alu_add(r.de());
            return 8;
        case 0x1A:
            r._a = read(r.de());
            return 8;
        case 0x1B:
            r.de(r.de() - 1);
            return 8;
        case 0x1C:
            r._e = inc(r._e);
            return 4;
        case 0x1D:
            r._e = dec(r._e);
            return 4;
        case 0x1E:
            r._e = byte();
            return 8;
        case 0x1F:
            r._a = rr(r._a);
            return 4;

        /// Row 0x20-0x2F
        case 0x20: {
            int8_t s8 = byte();
            if (!r.flag_z()) {
                jr(s8);
                return 12;
            }
            return 8;
        }
        case 0x21:
            r.hl(word());
            return 12;
        case 0x22:
            write(r.hl(), r._a);
            r.hl(r.hl() + 1);
            return 8;
        case 0x23:
            r.hl(r.hl() + 1);
            return 8;
        case 0x24:
            r._h = inc(r._h);
            return 4;
        case 0x25:
            r._h = dec(r._h);
            return 4;
        case 0x26:
            r._h = byte();
            return 8;
        case 0x27: {
            bool carry = false;
            if (!r.flag_n()) {
                if (r.flag_c() || (r._a > 0x99)) {
                    r._a += 0x60;
                    carry = true;
                }
                if (r.flag_h() || ((r._a & 0x0F) > 0x09)) {
                    r._a += 0x06;
                }
            } else if (r.flag_c()) {
                carry = true;
                r._a += r.flag_h() ? 0x9A : 0xA0;
            
            } else if (r.flag_h()) {
                r._a += 0xFA;
            }
            r.flag_z(r._a == 0);
            r.flag_h(false);
            r.flag_c(carry);
            return 4;
        }
        case 0x28: {
            int8_t s8 = byte();
            if (r.flag_z()) {
                jr(s8);
                return 12;
            }
            return 8;
        }
        case 0x29:
            alu_add(r.hl());
            return 8;
        case 0x2A:
            r._a = read(r.hl());
            r.hl(r.hl() + 1);
            return 8;
        case 0x2B:
            r.hl(r.hl() - 1);
            return 8;
        case 0x2C:
            r._l = inc(r._l);
            return 4;
        case 0x2D:
            r._l = dec(r._l);
            return 4;
        case 0x2E:
            r._l = byte();
            return 8;
        case 0x2F:
            r._a = !r._a;
            r.flag_h(true);
            r.flag_n(true);
            return 4;

        /// Row 0x30-0x3F
        case 0x30: {
            int8_t s8 = (int8_t) byte();
            if (!r.flag_c()) {
                jr(s8);
                return 12;
            }
            return 8;
        }
        case 0x31:
            r._sp = word();
            return 12;
        case 0x32:
            write(r.hl(), r._a);
            r.hl(r.hl() - 1);
            return 8;
        case 0x33:
            r._pc += 1;
            return 8;
        case 0x34:
            write(r.hl(), inc(read(r.hl())));
            return 12;
        case 0x35:
            write(r.hl(), dec(read(r.hl())));
            return 12;
        case 0x36:
            write(r.hl(), byte());
            return 12;
        case 0x37:
            r.flag_c(true);
            r.flag_h(false);
            r.flag_n(false);
            return 4;
        case 0x38: {
            int8_t s8 = (int8_t) byte();
            if (r.flag_c()) {
                jr(s8);
                return 12;
            }
            return 8;
        }
        case 0x39:
            alu_add(r._sp);
            return 8;
        case 0x3A:
            r._a = read(r.hl());
            r.hl(r.hl() - 1);
            return 8;
        case 0x3B:
            r._sp -= 1;
            return 8;
        case 0x3C:
            r._a = inc(r._a);
            return 4;
        case 0x3D:
            r._a = dec(r._a);
            return 4;
        case 0x3E:
            r._a = byte();
            return 8;
        case 0x3F:
            r.flag_c(!r.flag_c());
            r.flag_n(false);
            r.flag_h(false);
            return 4;

        /// Row 0x40-0x4F
        case 0x40:
            r._b = r._b;
            return 4;
        case 0x41:
            r._b = r._c;
            return 4;
        case 0x42:
            r._b = r._d;
            return 4;
        case 0x43:
            r._b = r._e;
            return 4;
        case 0x44:
            r._b = r._h;
            return 4;
        case 0x45:
            r._b = r._l;
            return 4;
        case 0x46:
            r._b = read(r.hl());
            return 8;
        case 0x47:
            r._b = r._a;
            return 4;
        case 0x48:
            r._c = r._b;
            return 4;
        case 0x49:
            r._c = r._c;
            return 4;
        case 0x4A:
            r._c = r._d;
            return 4;
        case 0x4B:
            r._c = r._e;
            return 4;
        case 0x4C:
            r._c = r._h;
            return 4;
        case 0x4D:
            r._c = r._l;
            return 4;
        case 0x4E:
            r._c = read(r.hl());
            return 8;
        case 0x4F:
            r._c = r._a;
            return 4;

        /// Row 0x50-0x5F
        case 0x50:
            r._d = r._b;
            return 4;
        case 0x51:
            r._d = r._c;
            return 4;
        case 0x52:
            r._d = r._d;
            return 4;
        case 0x53:
            r._d = r._e;
            return 4;
        case 0x54:
            r._d = r._h;
            return 4;
        case 0x55:
            r._d = r._l;
            return 4;
        case 0x56:
            r._d = read(r.hl());
            return 8;
        case 0x57:
            r._d = r._a;
            return 4;
        case 0x58:
            r._e = r._b;
            return 4;
        case 0x59:
            r._e = r._c;
            return 4;
        case 0x5A:
            r._e = r._d;
            return 4;
        case 0x5B:
            r._e = r._e;
            return 4;
        case 0x5C:
            r._e = r._h;
            return 4;
        case 0x5D:
            r._e = r._l;
            return 4;
        case 0x5E:
            r._e = read(r.hl());
            return 8;
        case 0x5F:
            r._e = r._a;
            return 4;

        /// Row 0x60-0x6F
        case 0x60:
            r._h = r._b;
            return 4;
        case 0x61:
            r._h = r._c;
            return 4;
        case 0x62:
            r._h = r._d;
            return 4;
        case 0x63:
            r._h = r._e;
            return 4;
        case 0x64:
            r._h = r._h;
            return 4;
        case 0x65:
            r._h = r._l;
            return 4;
        case 0x66:
            r._h = read(r.hl());
            return 8;
        case 0x67:
            r._h = r._a;
            return 4;
        case 0x68:
            r._l = r._b;
            return 4;
        case 0x69:
            r._l = r._c;
            return 4;
        case 0x6A:
            r._l = r._d;
            return 4;
        case 0x6B:
            r._l = r._e;
            return 4;
        case 0x6C:
            r._l = r._h;
            return 4;
        case 0x6D:
            r._l = r._l;
            return 4;
        case 0x6E:
            r._l = read(r.hl());
            return 8;
        case 0x6F:
            r._l = r._a;
            return 4;

        /// Row 0x70-0x7F
        case 0x70:
            write(r.hl(), r._b);
            return 8;
        case 0x71:
            write(r.hl(), r._c);
            return 8;
        case 0x72:
            write(r.hl(), r._d);
            return 8;
        case 0x73:
            write(r.hl(), r._e);
            return 8;
        case 0x74:
            write(r.hl(), r._h);
            return 8;
        case 0x75:
            write(r.hl(), r._l);
            return 8;
        case 0x76:
            halt();
            return 4;
        case 0x77:
            write(r.hl(), r._a);
            return 8;
        case 0x78:
            r._a = r._b;
            return 4;
        case 0x79:
            r._a = r._c;
            return 4;
        case 0x7A:
            r._a = r._d;
            return 4;
        case 0x7B:
            r._a = r._e;
            return 4;
        case 0x7C:
            r._a = r._h;
            return 4;
        case 0x7D:
            r._a = r._l;
            return 4;
        case 0x7E:
            r._a = read(r.hl());
            return 8;
        case 0x7F:
            r._a = r._a;
            return 4;
        
        /// Row 0x80-0x8F
        case 0x80:
            alu_add(r._b);
            return 4;
        case 0x81:
            alu_add(r._c);
            return 4;
        case 0x82:
            alu_add(r._d);
            return 4;
        case 0x83:
            alu_add(r._e);
            return 4;
        case 0x84:
            alu_add(r._h);
            return 4;
        case 0x85:
            alu_add(r._l);
            return 4;
        case 0x86:
            alu_add(read(r.hl()));
            return 8;
        case 0x87:
            alu_add(r._a);
            return 4;
        case 0x88:
            adc(r._b);
            return 4;
        case 0x89:
            adc(r._c);
            return 4;
        case 0x8A:
            adc(r._d);
            return 4;
        case 0x8B:
            adc(r._e);
            return 4;
        case 0x8C:
            adc(r._h);
            return 4;
        case 0x8D:
            adc(r._l);
            return 4;
        case 0x8E:
            adc(read(r.hl()));
            return 8;
        case 0x8F:
            adc(r._a);
            return 4;

        /// Row 0x90-0x9F
        case 0x90:
            r._a = alu_sub(r._b, false);
            return 4;
        case 0x91:
            r._a = alu_sub(r._c, false);
            return 4;
        case 0x92:
            r._a = alu_sub(r._d, false);
            return 4;
        case 0x93:
            r._a = alu_sub(r._e, false);
            return 4;
        case 0x94:
            r._a = alu_sub(r._h, false);
            return 4;
        case 0x95:
            r._a = alu_sub(r._l, false);
            return 4;
        case 0x96:
            r._a = alu_sub(read(r.hl()), false);
            return 8;
        case 0x97:
            r._a = alu_sub(r._a, false);
            return 4;
        case 0x98:
            sbc(r._b);
            return 4;
        case 0x99:
            sbc(r._c);
            return 4;
        case 0x9A:
            sbc(r._d);
            return 4;
        case 0x9B:
            sbc(r._e);
            return 4;
        case 0x9C:
            sbc(r._h);
            return 4;
        case 0x9D:
            sbc(r._l);
            return 4;
        case 0x9E:
            sbc(read(r.hl()));
            return 8;
        case 0x9F:
            sbc(r._a);
            return 4;

        /// Row 0xA0-0xAF
        case 0xA0:
            a_and(r._b);
            return 4;
        case 0xA1:
            a_and(r._c);
            return 4;
        case 0xA2:
            a_and(r._d);
            return 4;
        case 0xA3:
            a_and(r._e);
            return 4;
        case 0xA4:
            a_and(r._h);
            return 4;
        case 0xA5:
            a_and(r._l);
            return 4;
        case 0xA6:
            a_and(read(r.hl()));
            return 8;
        case 0xA7:
            a_and(r._a);
            return 4;
        case 0xA8:
            a_xor(r._b);
            return 4;
        case 0xA9:
            a_xor(r._c);
            return 4;
        case 0xAA:
            a_xor(r._d);
            return 4;
        case 0xAB:
            a_xor(r._e);
            return 4;
        case 0xAC:
            a_xor(r._h);
            return 4;
        case 0xAD:
            a_xor(r._l);
            return 4;
        case 0xAE:
            a_xor(read(r.hl()));
            return 8;
        case 0xAF:
            a_xor(r._a);
            return 4;

        /// Row 0xB0-0xBF
        case 0xB0:
            a_or(r._b);
            return 4;
        case 0xB1:
            a_or(r._c);
            return 4;
        case 0xB2:
            a_or(r._d);
            return 4;
        case 0xB3:
            a_or(r._e);
            return 4;
        case 0xB4:
            a_or(r._h);
            return 4;
        case 0xB5:
            a_or(r._l);
            return 4;
        case 0xB6:
            a_or(read(r.hl()));
            return 8;
        case 0xB7:
            a_or(r._a);
            return 4;
        case 0xB8:
            a_cp(r._b);
            return 4;
        case 0xB9:
            a_cp(r._c);
            return 4;
        case 0xBA:
            a_cp(r._d);
            return 4;
        case 0xBB:
            a_cp(r._e);
            return 4;
        case 0xBC:
            a_cp(r._h);
            return 4;
        case 0xBD:
            a_cp(r._l);
            return 4;
        case 0xBE:
            a_cp(read(r.hl()));
            return 8;
        case 0xBF:
            a_cp(r._a);
            return 4;

        /// Row 0xC0-0xCF
        case 0xC0:
            if (!r.flag_z()) {
                ret();
                return 20;
            }
            return 8;
        case 0xC1:
            r.bc(pop());
            return 12;
        case 0xC2: {
            uint16_t a16 = word();
            if (!r.flag_z()) {
                jp(a16);
                return 16;
            }
            return 12;
        }
        case 0xC3:
            jp(word());
            return 16;
        case 0xC4: {
            uint16_t v = word();
            if (!r.flag_z()) {
                call(v);
                return 24;
            }
            return 12;
        }
        case 0xC5:
            push(r.bc());
            return 16;
        case 0xC6:
            alu_add(byte());
            return 8;
        case 0xC7:
            rst(0x00);
            return 16;
        case 0xC8:
            if (r.flag_z()) {
                ret();
                return 20;
            }
            return 8;
        case 0xC9:
            ret();
            return 16;
        case 0xCA: {
            uint16_t a16 = word();
            if (r.flag_z()) {
                jp(a16);
                return 16;
            }
            return 12;
        }
        case 0xCB:
            return 4 + opcode_cb(byte());
        case 0xCC: {
            uint16_t v = word();
            if (r.flag_z()) {
                call(v);
                return 24;
            }
            return 12;
        }
        case 0xCD: {
            auto v = word();
            call(v);
            return 24;
        }
        case 0xCE:
            adc(byte());
            return 8;
        case 0xCF:
            rst(0x08);
            return 16;

        /// Row 0xD0-0xDF
        case 0xD0:
            if (!r.flag_c()) {
                ret();
                return 20;
            }
            return 8;
        case 0xD1:
            r.de(pop());
            return 12;
        case 0xD2: {
            uint16_t a16 = word();
            if (!r.flag_c()) {
                jp(a16);
                return 16;
            }
            return 12;
        }
        case 0xD4: {
            uint16_t v = word();
            if (!r.flag_c()) {
                call(v);
                return 24;
            }
            return 12;
        }
        case 0xD5:
            push(r.de());
            return 16;
        case 0xD6:
            r._a = alu_sub(byte(), false);
            return 8;
        case 0xD7:
            rst(0x10);
            return 16;
        case 0xD8:
            if (r.flag_c()) {
                ret();
                return 20;
            }
            return 8;
        case 0xD9:
            set_ime();
            ret();
            return 16;
        case 0xDA: {
            uint16_t a16 = word();
            if (r.flag_c()) {
                jp(a16);
                return 16;
            }
            return 12;
        }
        case 0xDC: {
            uint16_t v = word();
            if (r.flag_c()) {
                call(v);
                return 24;
            }
            return 12;
        }
        case 0xDE:
            sbc(byte());
            return 8;
        case 0xDF:
            rst(0x18);
            return 16;

        /// Row 0xE0-0xEF 
        case 0xE0:
            write(0xFF00 | (uint16_t) byte(), r._a);
            return 12;
        case 0xE1:
            r.hl(pop());
            return 12;
        case 0xE2:
            write(0xFF00 | (uint16_t) r._c, r._a);
            return 8;
        case 0xE5:
            push(r.hl());
            return 16;
        case 0xE6:
            a_and(byte());
            return 8;
        case 0xE7:
            rst(0x20);
            return 16;
        case 0xE8:
            add_16_sp(byte());
            return 16;
        case 0xE9:
            jp(r.hl());
            return 4;
        case 0xEA:
            write(word(), r._a);
            return 16;
        case 0xEE:
            a_xor(byte());
            return 8;
        case 0xEF:
            rst(0x28);
            return 16;

        /// Row 0xF0-0xFF
        case 0xF0: {
            auto b = (uint16_t) byte();
            // std::cout << "REG READ " << std::hex << (int) b << " " << std::dec << (int) read(0xFF00 | b) << std::endl;;
            r._a = read(0xFF00 | b);
            return 12;
        }
        case 0xF1:
            r.af(pop() & 0xFFF0);
            return 12;
        case 0xF2:
            r._a = read(0xFF00 | (uint16_t) r._c);
            return 8;
        case 0xF3:
            unset_ime();
            return 4;
        case 0xF5:
            push(r.af());
            return 16;
        case 0xF6:
            a_or(byte());
            return 8;
        case 0xF7:
            rst(0x30);
            return 16;
        case 0xF8:
            load_16_sp_hl(byte());
            return 12;
        case 0xF9:
            r._sp = r.hl();
            return 8;
        case 0xFA:
            r._a = read(word());
            return 16;
        case 0xFB:
            set_ime();
            return 4;
        case 0xFE:
            a_cp(byte());
            return 8;
        case 0xFF:
            rst(0x38);
            return 16;

        default:
            throw std::invalid_argument("Impossible opcode!");
            return -1;
    }
}


__uint128_t CPU::opcode_cb(uint8_t opcode) {

    switch (opcode) {

        /// Row 0x00-0x0F
        case 0x00:
            r._b = rlc(r._b);
            return 8;
        case 0x01:
            r._c = rlc(r._c);
            return 8;
        case 0x02:
            r._d = rlc(r._d);
            return 8;
        case 0x03:
            r._e = rlc(r._e);
            return 8;
        case 0x04:
            r._h = rlc(r._h);
            return 8;
        case 0x05:
            r._l = rlc(r._l);
            return 8;
        case 0x06:
            write(r.hl(), rlc(read(r.hl())));
            return 16;
        case 0x07:
            r._a = rlc(r._a);
            return 8;
        case 0x08:
            r._b = rrc(r._b);
            return 8;
        case 0x09:
            r._c = rrc(r._c);
            return 8;
        case 0x0A:
            r._d = rrc(r._d);
            return 8;
        case 0x0B:
            r._e = rrc(r._e);
            return 8;
        case 0x0C:
            r._h = rrc(r._h);
            return 8;
        case 0x0D:
            r._l = rrc(r._l);
            return 8;
        case 0x0E:
            write(r.hl(), rrc(read(r.hl())));
            return 16;
        case 0x0F:
            r._a = rrc(r._a);
            return 8;

        /// Row 0x10-0x1F
        case 0x10:
            r._b = rl(r._b);
            return 8;
        case 0x11:
            r._c = rl(r._c);
            return 8;
        case 0x12:
            r._d = rl(r._d);
            return 8;
        case 0x13:
            r._e = rl(r._e);
            return 8;
        case 0x14:
            r._h = rl(r._h);
            return 8;
        case 0x15:
            r._l = rl(r._l);
            return 8;
        case 0x16:
            write(r.hl(), rl(read(r.hl())));
            return 16;
        case 0x17:
            r._a = rl(r._a);
            return 8;
        case 0x18:
            r._b = rr(r._b);
            return 8;
        case 0x19:
            r._c = rr(r._c);
            return 8;
        case 0x1A:
            r._d = rr(r._d);
            return 8;
        case 0x1B:
            r._e = rr(r._e);
            return 8;
        case 0x1C:
            r._h = rr(r._h);
            return 8;
        case 0x1D:
            r._l = rr(r._l);
            return 8;
        case 0x1E:
            write(r.hl(), rr(read(r.hl())));
            return 16;
        case 0x1F:
            r._a = rr(r._a);
            return 8;

        /// Row 0x20-0x2F
        case 0x20:
            r._b = sla(r._b);
            return 8;
        case 0x21:
            r._c = sla(r._c);
            return 8;
        case 0x22:
            r._d = sla(r._d);
            return 8;
        case 0x23:
            r._e = sla(r._e);
            return 8;
        case 0x24:
            r._h = sla(r._h);
            return 8;
        case 0x25:
            r._l = sla(r._l);
            return 8;
        case 0x26:
            write(r.hl(), sla(read(r.hl())));
            return 16;
        case 0x27:
            r._a = sla(r._a);
            return 8;
        case 0x28:
            r._b = sra(r._b);
            return 8;
        case 0x29:
            r._c = sra(r._c);
            return 8;
        case 0x2A:
            r._d = sra(r._d);
            return 8;
        case 0x2B:
            r._e = sra(r._e);
            return 8;
        case 0x2C:
            r._h = sra(r._h);
            return 8;
        case 0x2D:
            r._l = sra(r._l);
            return 8;
        case 0x2E:
            write(r.hl(), sra(read(r.hl())));
            return 16;
        case 0x2F:
            r._a = sra(r._a);
            return 8;

        /// Row 0x30-0x3F
        case 0x30:
            r._b = swap(r._b);
            return 8;
        case 0x31:
            r._c = swap(r._c);
            return 8;
        case 0x32:
            r._d = swap(r._d);
            return 8;
        case 0x33:
            r._e = swap(r._e);
            return 8;
        case 0x34:
            r._h = swap(r._h);
            return 8;
        case 0x35:
            r._l = swap(r._l);
            return 8;
        case 0x36:
            write(r.hl(), swap(read(r.hl())));
            return 16;
        case 0x37:
            r._a = swap(r._a);
            return 8;
        case 0x38:
            r._b = srl(r._b);
            return 8;
        case 0x39:
            r._c = srl(r._c);
            return 8;
        case 0x3A:
            r._d = srl(r._d);
            return 8;
        case 0x3B:
            r._e = srl(r._e);
            return 8;
        case 0x3C:
            r._h = srl(r._h);
            return 8;
        case 0x3D:
            r._l = srl(r._l);
            return 8;
        case 0x3E:
            write(r.hl(), srl(read(r.hl())));
            return 16;
        case 0x3F:
            r._a = srl(r._a);
            return 8;

        /// Row 0x40-0x4F
        case 0x40:
            bit(0, r._b);
            return 8;
        case 0x41:
            bit(0, r._c);
            return 8;
        case 0x42:
            bit(0, r._d);
            return 8;
        case 0x43:
            bit(0, r._e);
            return 8;
        case 0x44:
            bit(0, r._h);
            return 8;
        case 0x45:
            bit(0, r._l);
            return 8;
        case 0x46:
            bit(0, read(r.hl()));
            return 12;
        case 0x47:
            bit(0, r._a);
            return 8;
        case 0x48:
            bit(1, r._b);
            return 8;
        case 0x49:
            bit(1, r._c);
            return 8;
        case 0x4A:
            bit(1, r._d);
            return 8;
        case 0x4B:
            bit(1, r._e);
            return 8;
        case 0x4C:
            bit(1, r._h);
            return 8;
        case 0x4D:
            bit(1, r._l);
            return 8;
        case 0x4E:
            bit(1, read(r.hl()));
            return 12;
        case 0x4F:
            bit(1, r._a);
            return 8;

        /// Row 0x50-0x5F
        case 0x50:
            bit(2, r._b);
            return 8;
        case 0x51:
            bit(2, r._c);
            return 8;
        case 0x52:
            bit(2, r._d);
            return 8;
        case 0x53:
            bit(2, r._e);
            return 8;
        case 0x54:
            bit(2, r._h);
            return 8;
        case 0x55:
            bit(2, r._l);
            return 8;
        case 0x56:
            bit(2, read(r.hl()));
            return 12;
        case 0x57:
            bit(2, r._a);
            return 8;
        case 0x58:
            bit(3, r._b);
            return 8;
        case 0x59:
            bit(3, r._c);
            return 8;
        case 0x5A:
            bit(3, r._d);
            return 8;
        case 0x5B:
            bit(3, r._e);
            return 8;
        case 0x5C:
            bit(3, r._h);
            return 8;
        case 0x5D:
            bit(3, r._l);
            return 8;
        case 0x5E:
            bit(3, read(r.hl()));
            return 12;
        case 0x5F:
            bit(3, r._a);
            return 8;

        /// Row 0x60-0x6F
        case 0x60:
            bit(4, r._b);
            return 8;
        case 0x61:
            bit(4, r._c);
            return 8;
        case 0x62:
            bit(4, r._d);
            return 8;
        case 0x63:
            bit(4, r._e);
            return 8;
        case 0x64:
            bit(4, r._h);
            return 8;
        case 0x65:
            bit(4, r._l);
            return 8;
        case 0x66:
            bit(4, read(r.hl()));
            return 12;
        case 0x67:
            bit(4, r._a);
            return 8;
        case 0x68:
            bit(5, r._b);
            return 8;
        case 0x69:
            bit(5, r._c);
            return 8;
        case 0x6A:
            bit(5, r._d);
            return 8;
        case 0x6B:
            bit(5, r._e);
            return 8;
        case 0x6C:
            bit(5, r._h);
            return 8;
        case 0x6D:
            bit(5, r._l);
            return 8;
        case 0x6E:
            bit(5, read(r.hl()));
            return 12;
        case 0x6F:
            bit(5, r._a);
            return 8;

        /// Row 0x70-0x7F
        case 0x70:
            bit(6, r._b);
            return 8;
        case 0x71:
            bit(6, r._c);
            return 8;
        case 0x72:
            bit(6, r._d);
            return 8;
        case 0x73:
            bit(6, r._e);
            return 8;
        case 0x74:
            bit(6, r._h);
            return 8;
        case 0x75:
            bit(6, r._l);
            return 8;
        case 0x76:
            bit(6, read(r.hl()));
            return 12;
        case 0x77:
            bit(6, r._a);
            return 8;
        case 0x78:
            bit(7, r._b);
            return 8;
        case 0x79:
            bit(7, r._c);
            return 8;
        case 0x7A:
            bit(7, r._d);
            return 8;
        case 0x7B:
            bit(7, r._e);
            return 8;
        case 0x7C:
            bit(7, r._h);
            return 8;
        case 0x7D:
            bit(7, r._l);
            return 8;
        case 0x7E:
            bit(7, read(r.hl()));
            return 12;
        case 0x7F:
            bit(7, r._a);
            return 8;

        /// Row 0x80-0x8F
        case 0x80:
            r._b = res(0, r._b);
            return 8;
        case 0x81:
            r._c = res(0, r._c);
            return 8;
        case 0x82:
            r._d = res(0, r._d);
            return 8;
        case 0x83:
            r._e = res(0, r._e);
            return 8;
        case 0x84:
            r._h = res(0, r._h);
            return 8;
        case 0x85:
            r._l = res(0, r._l);
            return 8;
        case 0x86:
            write(r.hl(), res(0, read(r.hl())));
            return 16;
        case 0x87:
            r._a = res(0, r._a);
            return 8;
        case 0x88:
            r._b = res(1, r._b);
            return 8;
        case 0x89:
            r._c = res(1, r._c);
            return 8;
        case 0x8A:
            r._d = res(1, r._d);
            return 8;
        case 0x8B:
            r._e = res(1, r._e);
            return 8;
        case 0x8C:
            r._h = res(1, r._h);
            return 8;
        case 0x8D:
            r._l = res(1, r._l);
            return 8;
        case 0x8E:
            write(r.hl(), res(1, read(r.hl())));
            return 16;
        case 0x8F:
            r._a = res(1, r._a);
            return 8;

        /// Row 0x90-0x9F
        case 0x90:
            r._b = res(2, r._b);
            return 8;
        case 0x91:
            r._c = res(2, r._c);
            return 8;
        case 0x92:
            r._d = res(2, r._d);
            return 8;
        case 0x93:
            r._e = res(2, r._e);
            return 8;
        case 0x94:
            r._h = res(2, r._h);
            return 8;
        case 0x95:
            r._l = res(2, r._l);
            return 8;
        case 0x96:
            write(r.hl(), res(2, read(r.hl())));
            return 16;
        case 0x97:
            r._a = res(2, r._a);
            return 8;
        case 0x98:
            r._b = res(3, r._b);
            return 8;
        case 0x99:
            r._c = res(3, r._c);
            return 8;
        case 0x9A:
            r._d = res(3, r._d);
            return 8;
        case 0x9B:
            r._e = res(3, r._e);
            return 8;
        case 0x9C:
            r._h = res(3, r._h);
            return 8;
        case 0x9D:
            r._l = res(3, r._l);
            return 8;
        case 0x9E:
            write(r.hl(), res(3, read(r.hl())));
            return 16;
        case 0x9F:
            r._a = res(3, r._a);
            return 8;

        /// Row 0xA0-0xAF
        case 0xA0:
            r._b = res(4, r._b);
            return 8;
        case 0xA1:
            r._c = res(4, r._c);
            return 8;
        case 0xA2:
            r._d = res(4, r._d);
            return 8;
        case 0xA3:
            r._e = res(4, r._e);
            return 8;
        case 0xA4:
            r._h = res(4, r._h);
            return 8;
        case 0xA5:
            r._l = res(4, r._l);
            return 8;
        case 0xA6:
            write(r.hl(), res(4, read(r.hl())));
            return 16;
        case 0xA7:
            r._a = res(4, r._a);
            return 8;
        case 0xA8:
            r._b = res(5, r._b);
            return 8;
        case 0xA9:
            r._c = res(5, r._c);
            return 8;
        case 0xAA:
            r._d = res(5, r._d);
            return 8;
        case 0xAB:
            r._e = res(5, r._e);
            return 8;
        case 0xAC:
            r._h = res(5, r._h);
            return 8;
        case 0xAD:
            r._l = res(5, r._l);
            return 8;
        case 0xAE:
            write(r.hl(), res(5, read(r.hl())));
            return 16;
        case 0xAF:
            r._a = res(5, r._a);
            return 8;

        /// Row 0xB0-0xBF
        case 0xB0:
            r._b = res(6, r._b);
            return 8;
        case 0xB1:
            r._c = res(6, r._b);
            return 8;
        case 0xB2:
            r._d = res(6, r._b);
            return 8;
        case 0xB3:
            r._e = res(6, r._b);
            return 8;
        case 0xB4:
            r._h = res(6, r._b);
            return 8;
        case 0xB5:
            r._l = res(6, r._b);
            return 8;
        case 0xB6:
            write(r.hl(), res(6, read(r.hl())));
            return 16;
        case 0xB7:
            r._a = res(6, r._a);
            return 8;
        case 0xB8:
            r._b = res(7, r._b);
            return 8;
        case 0xB9:
            r._c = res(7, r._c);
            return 8;
        case 0xBA:
            r._d = res(7, r._d);
            return 8;
        case 0xBB:
            r._e = res(7, r._e);
            return 8;
        case 0xBC:
            r._h = res(7, r._h);
            return 8;
        case 0xBD:
            r._l = res(7, r._l);
            return 8;
        case 0xBE:
            write(r.hl(), res(7, read(r.hl())));
            return 16;
        case 0xBF:
            r._a = res(7, r._a);
            return 8;

        /// Row 0xC0-0xCF
        case 0xC0:
            r._b = set(0, r._b);
            return 8;
        case 0xC1:
            r._c = set(0, r._c);
            return 8;
        case 0xC2:
            r._d = set(0, r._d);
            return 8;
        case 0xC3:
            r._e = set(0, r._e);
            return 8;
        case 0xC4:
            r._h = set(0, r._h);
            return 8;
        case 0xC5:
            r._l = set(0, r._l);
            return 8;
        case 0xC6:
            write(r.hl(), set(0, read(r.hl())));
            return 16;
        case 0xC7:
            r._a = set(0, r._a);
            return 8;
        case 0xC8:
            r._b = set(1, r._b);
            return 8;
        case 0xC9:
            r._c = set(1, r._c);
            return 8;
        case 0xCA:
            r._d = set(1, r._d);
            return 8;
        case 0xCB:
            r._e = set(1, r._e);
            return 8;
        case 0xCC:
            r._h = set(1, r._h);
            return 8;
        case 0xCD:
            r._l = set(1, r._l);
            return 8;
        case 0xCE:
            write(r.hl(), set(1, read(r.hl())));
            return 16;
        case 0xCF:
            r._a = set(1, r._a);
            return 8;

        /// Row 0xD0-0xDF
        case 0xD0:
            r._b = set(2, r._b);
            return 8;
        case 0xD1:
            r._c = set(2, r._c);
            return 8;
        case 0xD2:
            r._d = set(2, r._d);
            return 8;
        case 0xD3:
            r._e = set(2, r._e);
            return 8;
        case 0xD4:
            r._h = set(2, r._h);
            return 8;
        case 0xD5:
            r._l = set(2, r._l);
            return 8;
        case 0xD6:
            write(r.hl(), set(2, read(r.hl())));
            return 16;
        case 0xD7:
            r._a = set(2, r._a);
            return 8;
        case 0xD8:
            r._b = set(3, r._b);
            return 8;
        case 0xD9:
            r._c = set(3, r._c);
            return 8;
        case 0xDA:
            r._d = set(3, r._d);
            return 8;
        case 0xDB:
            r._e = set(3, r._e);
            return 8;
        case 0xDC:
            r._h = set(3, r._h);
            return 8;
        case 0xDD:
            r._l = set(3, r._l);
            return 8;
        case 0xDE:
            write(r.hl(), set(3, read(r.hl())));
            return 16;
        case 0xDF:
            r._a = set(3, r._a);
            return 8;

        /// Row 0xE0-0xEF
        case 0xE0:
            r._b = set(4, r._b);
            return 8;
        case 0xE1:
            r._c = set(4, r._c);
            return 8;
        case 0xE2:
            r._d = set(4, r._d);
            return 8;
        case 0xE3:
            r._e = set(4, r._e);
            return 8;
        case 0xE4:
            r._h = set(4, r._h);
            return 8;
        case 0xE5:
            r._l = set(4, r._l);
            return 8;
        case 0xE6:
            write(r.hl(), set(4, read(r.hl())));
            return 16;
        case 0xE7:
            r._a = set(4, r._a);
            return 8;
        case 0xE8:
            r._b = set(5, r._b);
            return 8;
        case 0xE9:
            r._c = set(5, r._c);
            return 8;
        case 0xEA:
            r._d = set(5, r._d);
            return 8;
        case 0xEB:
            r._e = set(5, r._e);
            return 8;
        case 0xEC:
            r._h = set(5, r._h);
            return 8;
        case 0xED:
            r._l = set(5, r._l);
            return 8;
        case 0xEE:
            write(r.hl(), set(5, read(r.hl())));
            return 16;
        case 0xEF:
            r._a = set(5, r._a);
            return 8;

        /// Row 0xF0-0xFF
        case 0xF0:
            r._b = set(6, r._b);
            return 8;
        case 0xF1:
            r._c = set(6, r._b);
            return 8;
        case 0xF2:
            r._d = set(6, r._b);
            return 8;
        case 0xF3:
            r._e = set(6, r._b);
            return 8;
        case 0xF4:
            r._h = set(6, r._b);
            return 8;
        case 0xF5:
            r._l = set(6, r._b);
            return 8;
        case 0xF6:
            write(r.hl(), set(6, read(r.hl())));
            return 16;
        case 0xF7:
            r._a = set(6, r._a);
            return 8;
        case 0xF8:
            r._b = set(7, r._b);
            return 8;
        case 0xF9:
            r._c = set(7, r._c);
            return 8;
        case 0xFA:
            r._d = set(7, r._d);
            return 8;
        case 0xFB:
            r._e = set(7, r._e);
            return 8;
        case 0xFC:
            r._h = set(7, r._h);
            return 8;
        case 0xFD:
            r._l = set(7, r._l);
            return 8;
        case 0xFE:
            write(r.hl(), set(7, read(r.hl())));
            return 16;
        case 0xFF:
            r._a = set(7, r._a);
            return 8;


        default:
            return -1;
    }
}