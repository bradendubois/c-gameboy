#include <stdint.h>

#include "../include/cpu.h"
#include "../include/registers.h"

__uint128_t CPU::opcode(uint8_t opcode) {

    if (cb) { cb = false; return opcode_cb(opcode); }

    switch (opcode) {

        // Row 0x00-0x0F
        case 0x00:
            return 1;
        case 0x01:
            r.bc(mmu.word());
            return 3;
        case 0x02:
            mmu.write(r.bc(), r._a);
            return 2;
        case 0x03:
            r.bc(r.bc() + 1);
            return 2;
        case 0x04:
            r._b += 1;
            return 1;
        case 0x05:
            r._b -= 1;
            return 1;
        case 0x06:
            r._b = mmu.byte();
            return 2;
        case 0x07:
            r.flag_c(r._a & 0x80);
            r._a = (r._a << 1) | (r._a >> 7);
            return 1;
        case 0x08:
            mmu.write(mmu.word(), r._sp);
            return 5;
        case 0x09:
            r.hl(r.bc() + r.hl());
            return 2;
        case 0x0A:
            r._a = mmu.read(r.bc());
            return 2;
        case 0x0B:
            r.bc(r.bc() - 1);
            return 2;
        case 0x0C:
            r._c += 1;
            return 1;
        case 0x0D:
            r._c -= 1;
            return 1;
        case 0x0E:
            r._c = mmu.byte();
            return 2;
        case 0x0F:
            r.flag_c(r._a & 0x01);
            r._a = (r._a >> 1) | (r._a << 7);
            return 1;

        /// Row 0x10-0x1F
        case 0x10:
            stop();
            return 1;
        case 0x11:
            r.de(mmu.word());
            return 3;
        case 0x12:
            mmu.write(r.de(), r._a);
            return 2;
        case 0x13:
            r.de(r.de() + 1);
            return 2;
        case 0x14:
            r._d = inc(r._d);
            return 1;
        case 0x15:
            r._d = dec(r._d);
            return 1;
        case 0x16:
            r._d = mmu.byte();
            return 2;
        case 0x17:
            r._a = rl(r._a);
            r.flag_z(false);
            return 1;
        case 0x18:
            jr((int8_t) mmu.byte());
            return 3;
        case 0x19:
            hl_add(r.de());
            return 2;
        case 0x1A:
            r._a = mmu.read(r.de());
            return 2;
        case 0x1B:
            r.de(r.de() - 1);
            return 2;
        case 0x1C:
            r._e = inc(r._e);
            return 1;
        case 0x1D:
            r._e = dec(r._e);
            return 1;
        case 0x1E:
            r._e = mmu.byte();
            return 2;
        case 0x1F:
            r._a = rr(r._a);
            r.flag_z(false);
            return 1;

        /// Row 0x20-0x2F
        case 0x20:
            int8_t s8 = mmu.byte();
            if (r.flag_z()) {
                jr(s8);
                return 3;
            }
            return 2;
        case 0x21:
            r.hl(mmu.word());
            return 3;
        case 0x22:
            mmu.write(r.hl(), r._a);
            r.hl(r.hl() - 1);
            return 2;
        case 0x23:
            r.hl(r.hl() + 1);
            return 2;
        case 0x24:
            r._h = inc(r._h);
            return 1;
        case 0x25:
            r._h = dec(r._h);
            return 1;
        case 0x26:
            r._h = mmu.byte();
            return 2;
        case 0x27:
            uint8_t adj;
            
            if (r.flag_c()) {
                adj |- 0x60;
            }

            if (r.flag_h()) {
                adj |- 0x06;
            }

            if (!r.flag_n()) {
                if ((r._a & 0x0F) > 0x09) adj |= 0x06;
                if (r._a > 0x99) adj |= 0x60;
            }

            r._a += adj;

            r.flag_c(adj >= 0x80);
            r.flag_h(false);
            r.flag_z(r._a == 0);

            return 1;
        case 0x28:
            int8_t s8 = mmu.byte();
            if (!r.flag_z()) {
                jr(s8);
                return 3;
            }
            return 2;
        case 0x29:
            hl_add(r.hl());
            return 2;
        case 0x2A:
            r._a = mmu.read(r.hl());
            r.hl(r.hl() - 1);
            return 2;
        case 0x2B:
            r.hl(r.hl() - 1);
            return 2;
        case 0x2C:
            r._l = inc(r._l);
            return 1;
        case 0x2D:
            r._l = dec(r._l);
            return 1;
        case 0x2E:
            r._l = mmu.byte();
            return 2;
        case 0x2F:
            r._a = !r._a;
            r.flag_h(true);
            r.flag_n(true);
            return 1;

        /// Row 0x30-0x3F
        case 0x30:
            int8_t s8 = (int8_t) mmu.byte();
            if (!r.flag_c()) {
                jr(s8);
                return 3;
            }
            return 2;
        case 0x31:
            r._sp = mmu.word();
            return 3;
        case 0x32:
            mmu.write(r.hl(), r._a);
            r.hl(r.hl() - 1);
            return 2;
        case 0x33:
            r._pc += 1;
            return 2;
        case 0x34:
            mmu.write(r.hl(), inc(mmu.read(r.hl())));
            return 3;
        case 0x35:
            mmu.write(r.hl(), dec(mmu.read(r.hl())));
            return 3;
        case 0x36:
            mmu.write(r.hl(), mmu.byte());
            return 3;
        case 0x37:
            r.flag_c(true);
            r.flag_h(false);
            r.flag_n(false);
            return 1;
        case 0x38:
            int8_t s8 = (int8_t) mmu.byte();
            if (r.flag_c()) {
                jr(s8);
                return 3;
            }
            return 2;
        case 0x39:
            hl_add(r._sp);
            return 2;
        case 0x3A:
            r._a = mmu.read(r.hl());
            r.hl(r.hl() - 1);
            return 2;
        case 0x3B:
            r._sp -= 1;
            return 2;
        case 0x3C:
            r._a = inc(r._a);
            return 1;
        case 0x3D:
            r._a = dec(r._a);
            return 1;
        case 0x3E:
            r._a = mmu.byte();
            return 2;
        case 0x3F:
            r.flag_c(!r.flag_c());
            r.flag_n(false);
            r.flag_h(false);
            return 1;

        /// Row 0x40-0x4F
        case 0x40:
            r._b = r._b;
            return 1;
        case 0x41:
            r._b = r._c;
            return 1;
        case 0x42:
            r._b = r._d;
            return 1;
        case 0x43:
            r._b = r._e;
            return 1;
        case 0x44:
            r._b = r._h;
            return 1;
        case 0x45:
            r._b = r._l;
            return 1;
        case 0x46:
            r._b = mmu.read(r.hl());
            return 2;
        case 0x47:
            r._b = r._a;
            return 1;
        case 0x48:
            r._c = r._b;
            return 1;
        case 0x49:
            r._c = r._c;
            return 1;
        case 0x4A:
            r._c = r._d;
            return 1;
        case 0x4B:
            r._c = r._e;
            return 1;
        case 0x4C:
            r._c = r._h;
            return 1;
        case 0x4D:
            r._c = r._l;
            return 1;
        case 0x4E:
            r._c = mmu.read(r.hl());
            return 2;
        case 0x4F:
            r._c = r._a;
            return 1;

        /// Row 0x50-0x5F
        case 0x50:
            r._d = r._b;
            return 1;
        case 0x51:
            r._d = r._c;
            return 1;
        case 0x52:
            r._d = r._d;
            return 1;
        case 0x53:
            r._d = r._e;
            return 1;
        case 0x54:
            r._d = r._h;
            return 1;
        case 0x55:
            r._d = r._l;
            return 1;
        case 0x56:
            r._d = mmu.read(r.hl());
            return 2;
        case 0x57:
            r._d = r._a;
            return 1;
        case 0x58:
            r._e = r._b;
            return 1;
        case 0x59:
            r._e = r._c;
            return 1;
        case 0x5A:
            r._e = r._d;
            return 1;
        case 0x5B:
            r._e = r._e;
            return 1;
        case 0x5C:
            r._e = r._h;
            return 1;
        case 0x5D:
            r._e = r._l;
            return 1;
        case 0x5E:
            r._e = mmu.read(r.hl());
            return 2;
        case 0x5F:
            r._e = r._a;
            return 1;

        /// Row 0x60-0x6F
        case 0x60:
            r._h = r._b;
            return 1;
        case 0x61:
            r._h = r._c;
            return 1;
        case 0x62:
            r._h = r._d;
            return 1;
        case 0x63:
            r._h = r._e;
            return 1;
        case 0x64:
            r._h = r._h;
            return 1;
        case 0x65:
            r._h = r._l;
            return 1;
        case 0x66:
            r._h = mmu.read(r.hl());
            return 2;
        case 0x67:
            r._h = r._a;
            return 1;
        case 0x68:
            r._l = r._b;
            return 1;
        case 0x69:
            r._l = r._c;
            return 1;
        case 0x6A:
            r._l = r._d;
            return 1;
        case 0x6B:
            r._l = r._e;
            return 1;
        case 0x6C:
            r._l = r._h;
            return 1;
        case 0x6D:
            r._l = r._l;
            return 1;
        case 0x6E:
            r._l = mmu.read(r.hl());
            return 2;
        case 0x6F:
            r._l = r._a;
            return 1;

        /// Row 0x70-0x7F
        case 0x70:
            mmu.write(r.hl(), r._b);
            return 2;
        case 0x71:
            mmu.write(r.hl(), r._c);
            return 2;
        case 0x72:
            mmu.write(r.hl(), r._d);
            return 2;
        case 0x73:
            mmu.write(r.hl(), r._e);
            return 2;
        case 0x74:
            mmu.write(r.hl(), r._h);
            return 2;
        case 0x75:
            mmu.write(r.hl(), r._l);
            return 2;
        case 0x76:
            halt();
            return 1;
        case 0x77:
            mmu.write(r.hl(), r._a);
            return 2;
        case 0x78:
            r._a = r._b;
            return 1;
        case 0x79:
            r._a = r._c;
            return 1;
        case 0x7A:
            r._a = r._d;
            return 1;
        case 0x7B:
            r._a = r._e;
            return 1;
        case 0x7C:
            r._a = r._h;
            return 1;
        case 0x7D:
            r._a = r._l;
            return 1;
        case 0x7E:
            r._a = mmu.read(r.hl());
            return 2;
        case 0x7F:
            r._a = r._a;
            return 1;
        
        /// Row 0x80-0x8F
        case 0x80:
            a_add(r._b);
            return 1;
        case 0x81:
            a_add(r._c);
            return 1;
        case 0x82:
            a_add(r._d);
            return 1;
        case 0x83:
            a_add(r._e);
            return 1;
        case 0x84:
            a_add(r._h);
            return 1;
        case 0x85:
            a_add(r._l);
            return 1;
        case 0x86:
            a_add(mmu.read(r.hl()));
            return 2;
        case 0x87:
            a_add(r._a);
            return 1;
        case 0x88:
            adc(r._b);
            return 1;
        case 0x89:
            adc(r._c);
            return 1;
        case 0x8A:
            adc(r._d);
            return 1;
        case 0x8B:
            adc(r._e);
            return 1;
        case 0x8C:
            adc(r._h);
            return 1;
        case 0x8D:
            adc(r._l);
            return 1;
        case 0x8E:
            adc(mmu.read(r.hl()));
            return 2;
        case 0x8F:
            adc(r._a);
            return 1;

        /// Row 0x90-0x9F
        case 0x90:
            a_sub(r._b);
            return 1;
        case 0x91:
            a_sub(r._c);
            return 1;
        case 0x92:
            a_sub(r._d);
            return 1;
        case 0x93:
            a_sub(r._e);
            return 1;
        case 0x94:
            a_sub(r._h);
            return 1;
        case 0x95:
            a_sub(r._l);
            return 1;
        case 0x96:
            a_sub(mmu.read(r.hl()));
            return 2;
        case 0x97:
            a_sub(r._a);
            return 1;
        case 0x98:
            sbc(r._b);
            return 1;
        case 0x99:
            sbc(r._c);
            return 1;
        case 0x9A:
            sbc(r._d);
            return 1;
        case 0x9B:
            sbc(r._e);
            return 1;
        case 0x9C:
            sbc(r._h);
            return 1;
        case 0x9D:
            sbc(r._l);
            return 1;
        case 0x9E:
            sbc(mmu.read(r.hl()));
            return 2;
        case 0x9F:
            sbc(r._a);
            return 1;

        /// Row 0xA0-0xAF
        case 0xA0:
            a_and(r._b);
            return 1;
        case 0xA1:
            a_and(r._c);
            return 1;
        case 0xA2:
            a_and(r._d);
            return 1;
        case 0xA3:
            a_and(r._e);
            return 1;
        case 0xA4:
            a_and(r._h);
            return 1;
        case 0xA5:
            a_and(r._l);
            return 1;
        case 0xA6:
            a_and(mmu.read(r.hl()));
            return 2;
        case 0xA7:
            a_and(r._a);
            return 1;
        case 0xA8:
            a_xor(r._b);
            return 1;
        case 0xA9:
            a_xor(r._c);
            return 1;
        case 0xAA:
            a_xor(r._d);
            return 1;
        case 0xAB:
            a_xor(r._e);
            return 1;
        case 0xAC:
            a_xor(r._h);
            return 1;
        case 0xAD:
            a_xor(r._l);
            return 1;
        case 0xAE:
            a_xor(mmu.read(r.hl()));
            return 2;
        case 0xAF:
            a_xor(r._a);
            return 1;

        /// Row 0xB0-0xBF
        case 0xB0:
            a_or(r._b);
            return 1;
        case 0xB1:
            a_or(r._c);
            return 1;
        case 0xB2:
            a_or(r._d);
            return 1;
        case 0xB3:
            a_or(r._e);
            return 1;
        case 0xB4:
            a_or(r._h);
            return 1;
        case 0xB5:
            a_or(r._l);
            return 1;
        case 0xB6:
            a_or(mmu.read(r.hl()));
            return 2;
        case 0xB7:
            a_or(r._a);
            return 1;
        case 0xB8:
            a_cp(r._b);
            return 1;
        case 0xB9:
            a_cp(r._c);
            return 1;
        case 0xBA:
            a_cp(r._d);
            return 1;
        case 0xBB:
            a_cp(r._e);
            return 1;
        case 0xBC:
            a_cp(r._h);
            return 1;
        case 0xBD:
            a_cp(r._l);
            return 1;
        case 0xBE:
            a_cp(mmu.read(r.hl()));
            return 2;
        case 0xBF:
            a_cp(r._a);
            return 1;

        /// Row 0xC0-0xCF
        case 0xC0:
            if (!r.flag_z()) {
                ret();
                return 5;
            }
            return 2;
        case 0xC1:
            r.bc(pop_word());
            return 3;
        case 0xC2:
            uint16_t a16 = mmu.word();
            if (!r.flag_z()) {
                jp(a16);
                return 4;
            }
            return 3;
        case 0xC3:
            jp(mmu.word());
            return 4;
        case 0xC4:
            uint16_t v = mmu.word();
            if (!r.flag_z()) {
                call(v);
                return 6;
            }
            return 3;
        case 0xC5:
            push(r.bc());
            return 4;
        case 0xC6:
            a_add(mmu.byte());
            return 2;
        case 0xC7:
            rst(0x00);
            return 4;
        case 0xC8:
            if (r.flag_z()) {
                ret();
                return 5;
            }
            return 2;
        case 0xC9:
            ret();
            return 4;
        case 0xCA:
            uint16_t a16 = mmu.word();
            if (r.flag_z()) {
                jp(a16);
                return 4;
            }
            return 3;
        case 0xCC:
            uint16_t v = mmu.word();
            if (r.flag_z()) {
                call(v);
                return 6;
            }
            return 3;
        case 0xCD:
            call(mmu.word());
            return 6;
        case 0xCE:
            adc(mmu.byte());
            return 2;
        case 0xCF:
            rst(0x08);
            return 4;

        /// Row 0xD0-0xDF
        case 0xD0:
            if (!r.flag_c()) {
                ret();
                return 5;
            }
            return 2;
        case 0xD1:
            r.de(pop_word());
            return 3;
        case 0xD2:
            uint16_t a16 = mmu.word();
            if (!r.flag_c()) {
                jp(a16);
                return 4;
            }
            return 3;
        case 0xD4:
            uint16_t v = mmu.word();
            if (!r.flag_c()) {
                call(v);
                return 6;
            }
            return 3;
        case 0xD5:
            push(r.de());
            return 4;
        case 0xD6:
            a_sub(mmu.byte());
            return 2;
        case 0xD7:
            rst(0x10);
            return 4;
        case 0xD8:
            if (r.flag_c()) {
                ret();
                return 5;
            }
            return 2;
        case 0xD9:
            set_ime();
            ret();
            return 4;
        case 0xDA:
            uint16_t a16 = mmu.word();
            if (r.flag_c()) {
                jp(a16);
                return 4;
            }
            return 3;
        case 0xDC:
            uint16_t v = mmu.word();
            if (r.flag_c()) {
                call(v);
                return 6;
            }
            return 3;
        case 0xDE:
            sbc(mmu.byte());
            return 2;
        case 0xDF:
            rst(0x18);
            return 4;

        /// Row 0xE0-0xEF 
        case 0xE0:
            mmu.write(0xFF00 | (uint16_t) mmu.byte(), r._a);
            return 3;
        case 0xE1:
            r.hl(pop_word());
            return 3;
        case 0xE2:
            mmu.write(0xFF00 | (uint16_t) r._c, r._a);
            return 2;
        case 0xE5:
            push(r.hl());
            return 4;
        case 0xE6:
            a_and(mmu.byte());
            return 2;
        case 0xE7:
            rst(0x20);
            return 4;
        case 0xE8:
            r._sp = add_16_immediate(r._sp, mmu.byte());
            return 4;
        case 0xE9:
            jp(r.hl());
            return 1;
        case 0xEA:
            mmu.write(mmu.word(), r._a);
            return 4;
        case 0xEE:
            a_xor(mmu.byte());
            return 2;
        case 0xEF:
            rst(0x28);
            return 4;

        /// UNIMPLEMENTED Row 0xF0-0xFF
        case 0xF0:
            r._a = mmu.read(0xFF00 | (uint16_t) mmu.byte());
            return 3;
        case 0xF1:
            r.af(pop_word() & 0xFFF0);
            return 3;
        case 0xF2:
            r._a = mmu.read(0xFF00 | (uint16_t) r._c);
            return 2;
        case 0xF3:
            unset_ime();
            return 1;
        case 0xF5:
            push(r.af());
            return 4;
        case 0xF6:
            a_or(mmu.byte());
            return 2;
        case 0xF7:
            rst(0x30);
            return 4;
        case 0xF8:
            r.hl(add_16_immediate(r._sp, mmu.byte()));
            return 3;
        case 0xF9:
            r._sp = r.hl();
            return 2;
        case 0xFA:
            r._a = mmu.read(mmu.word());
            return 4;
        case 0xFB:
            set_ime();
            return 1;
        case 0xFE:
            a_cp(mmu.byte());
            return 2;
        case 0xFF:
            rst(0x38);
            return 4;

        default:
            return -1;
    }
}


__uint128_t opcode_cb(uint8_t opcode) {

    switch (opcode) {

        /// UNIMPLEMENTED Row 0x00-0x0F
        case 0x00:
            return 0;
            break;
        case 0x01:
            return 0;
            break;
        case 0x02:
            return 0;
            break;
        case 0x03:
            return 0;
            break;
        case 0x04:
            return 0;
            break;
        case 0x05:
            return 0;
            break;
        case 0x06:
            return 0;
            break;
        case 0x07:
            return 0;
            break;
        case 0x08:
            return 0;
            break;
        case 0x09:
            return 0;
            break;
        case 0x0A:
            return 0;
            break;
        case 0x0B:
            return 0;
            break;
        case 0x0C:
            return 0;
            break;
        case 0x0D:
            return 0;
            break;
        case 0x0E:
            return 0;
            break;
        case 0x0F:
            return 0;
            break;

        /// UNIMPLEMENTED Row 0x10-0x1F
        case 0x10:
            return 0;
            break;
        case 0x11:
            return 0;
            break;
        case 0x12:
            return 0;
            break;
        case 0x13:
            return 0;
            break;
        case 0x14:
            return 0;
            break;
        case 0x15:
            return 0;
            break;
        case 0x16:
            return 0;
            break;
        case 0x17:
            return 0;
            break;
        case 0x18:
            return 0;
            break;
        case 0x19:
            return 0;
            break;
        case 0x1A:
            return 0;
            break;
        case 0x1B:
            return 0;
            break;
        case 0x1C:
            return 0;
            break;
        case 0x1D:
            return 0;
            break;
        case 0x1E:
            return 0;
            break;
        case 0x1F:
            return 0;
            break;

        /// UNIMPLEMENTED Row 0x20-0x2F
        case 0x20:
            return 0;
            break;
        case 0x21:
            return 0;
            break;
        case 0x22:
            return 0;
            break;
        case 0x23:
            return 0;
            break;
        case 0x24:
            return 0;
            break;
        case 0x25:
            return 0;
            break;
        case 0x26:
            return 0;
            break;
        case 0x27:
            return 0;
            break;
        case 0x28:
            return 0;
            break;
        case 0x29:
            return 0;
            break;
        case 0x2A:
            return 0;
            break;
        case 0x2B:
            return 0;
            break;
        case 0x2C:
            return 0;
            break;
        case 0x2D:
            return 0;
            break;
        case 0x2E:
            return 0;
            break;
        case 0x2F:
            return 0;
            break;

        /// UNIMPLEMENTED Row 0x30-0x3F
        case 0x30:
            return 0;
            break;
        case 0x31:
            return 0;
            break;
        case 0x32:
            return 0;
            break;
        case 0x33:
            return 0;
            break;
        case 0x34:
            return 0;
            break;
        case 0x35:
            return 0;
            break;
        case 0x36:
            return 0;
            break;
        case 0x37:
            return 0;
            break;
        case 0x38:
            return 0;
            break;
        case 0x39:
            return 0;
            break;
        case 0x3A:
            return 0;
            break;
        case 0x3B:
            return 0;
            break;
        case 0x3C:
            return 0;
            break;
        case 0x3D:
            return 0;
            break;
        case 0x3E:
            return 0;
            break;
        case 0x3F:
            return 0;
            break;

        /// UNIMPLEMENTED Row 0x40-0x4F
        case 0x40:
            return 0;
            break;
        case 0x41:
            return 0;
            break;
        case 0x42:
            return 0;
            break;
        case 0x43:
            return 0;
            break;
        case 0x44:
            return 0;
            break;
        case 0x45:
            return 0;
            break;
        case 0x46:
            return 0;
            break;
        case 0x47:
            return 0;
            break;
        case 0x48:
            return 0;
            break;
        case 0x49:
            return 0;
            break;
        case 0x4A:
            return 0;
            break;
        case 0x4B:
            return 0;
            break;
        case 0x4C:
            return 0;
            break;
        case 0x4D:
            return 0;
            break;
        case 0x4E:
            return 0;
            break;
        case 0x4F:
            return 0;
            break;

        /// UNIMPLEMENTED Row 0x50-0x5F
        case 0x50:
            return 0;
            break;
        case 0x51:
            return 0;
            break;
        case 0x52:
            return 0;
            break;
        case 0x53:
            return 0;
            break;
        case 0x54:
            return 0;
            break;
        case 0x55:
            return 0;
            break;
        case 0x56:
            return 0;
            break;
        case 0x57:
            return 0;
            break;
        case 0x58:
            return 0;
            break;
        case 0x59:
            return 0;
            break;
        case 0x5A:
            return 0;
            break;
        case 0x5B:
            return 0;
            break;
        case 0x5C:
            return 0;
            break;
        case 0x5D:
            return 0;
            break;
        case 0x5E:
            return 0;
            break;
        case 0x5F:
            return 0;
            break;

        /// UNIMPLEMENTED Row 0x60-0x6F
        case 0x60:
            return 0;
            break;
        case 0x61:
            return 0;
            break;
        case 0x62:
            return 0;
            break;
        case 0x63:
            return 0;
            break;
        case 0x64:
            return 0;
            break;
        case 0x65:
            return 0;
            break;
        case 0x66:
            return 0;
            break;
        case 0x67:
            return 0;
            break;
        case 0x68:
            return 0;
            break;
        case 0x69:
            return 0;
            break;
        case 0x6A:
            return 0;
            break;
        case 0x6B:
            return 0;
            break;
        case 0x6C:
            return 0;
            break;
        case 0x6D:
            return 0;
            break;
        case 0x6E:
            return 0;
            break;
        case 0x6F:
            return 0;
            break;

        /// UNIMPLEMENTED Row 0x70-0x7F
        case 0x70:
            return 0;
            break;
        case 0x71:
            return 0;
            break;
        case 0x72:
            return 0;
            break;
        case 0x73:
            return 0;
            break;
        case 0x74:
            return 0;
            break;
        case 0x75:
            return 0;
            break;
        case 0x76:
            return 0;
            break;
        case 0x77:
            return 0;
            break;
        case 0x78:
            return 0;
            break;
        case 0x79:
            return 0;
            break;
        case 0x7A:
            return 0;
            break;
        case 0x7B:
            return 0;
            break;
        case 0x7C:
            return 0;
            break;
        case 0x7D:
            return 0;
            break;
        case 0x7E:
            return 0;
            break;
        case 0x7F:
            return 0;
            break;

        /// UNIMPLEMENTED Row 0x80-0x8F
        case 0x80:
            return 0;
            break;
        case 0x81:
            return 0;
            break;
        case 0x82:
            return 0;
            break;
        case 0x83:
            return 0;
            break;
        case 0x84:
            return 0;
            break;
        case 0x85:
            return 0;
            break;
        case 0x86:
            return 0;
            break;
        case 0x87:
            return 0;
            break;
        case 0x88:
            return 0;
            break;
        case 0x89:
            return 0;
            break;
        case 0x8A:
            return 0;
            break;
        case 0x8B:
            return 0;
            break;
        case 0x8C:
            return 0;
            break;
        case 0x8D:
            return 0;
            break;
        case 0x8E:
            return 0;
            break;
        case 0x8F:
            return 0;
            break;

        /// UNIMPLEMENTED Row 0x90-0x9F
        case 0x90:
            return 0;
            break;
        case 0x91:
            return 0;
            break;
        case 0x92:
            return 0;
            break;
        case 0x93:
            return 0;
            break;
        case 0x94:
            return 0;
            break;
        case 0x95:
            return 0;
            break;
        case 0x96:
            return 0;
            break;
        case 0x97:
            return 0;
            break;
        case 0x98:
            return 0;
            break;
        case 0x99:
            return 0;
            break;
        case 0x9A:
            return 0;
            break;
        case 0x9B:
            return 0;
            break;
        case 0x9C:
            return 0;
            break;
        case 0x9D:
            return 0;
            break;
        case 0x9E:
            return 0;
            break;
        case 0x9F:
            return 0;
            break;

        /// UNIMPLEMENTED Row 0xA0-0xAF
        case 0xA0:
            return 0;
            break;
        case 0xA1:
            return 0;
            break;
        case 0xA2:
            return 0;
            break;
        case 0xA3:
            return 0;
            break;
        case 0xA4:
            return 0;
            break;
        case 0xA5:
            return 0;
            break;
        case 0xA6:
            return 0;
            break;
        case 0xA7:
            return 0;
            break;
        case 0xA8:
            return 0;
            break;
        case 0xA9:
            return 0;
            break;
        case 0xAA:
            return 0;
            break;
        case 0xAB:
            return 0;
            break;
        case 0xAC:
            return 0;
            break;
        case 0xAD:
            return 0;
            break;
        case 0xAE:
            return 0;
            break;
        case 0xAF:
            return 0;
            break;

        /// UNIMPLEMENTED Row 0xB0-0xBF
        case 0xB0:
            return 0;
            break;
        case 0xB1:
            return 0;
            break;
        case 0xB2:
            return 0;
            break;
        case 0xB3:
            return 0;
            break;
        case 0xB4:
            return 0;
            break;
        case 0xB5:
            return 0;
            break;
        case 0xB6:
            return 0;
            break;
        case 0xB7:
            return 0;
            break;
        case 0xB8:
            return 0;
            break;
        case 0xB9:
            return 0;
            break;
        case 0xBA:
            return 0;
            break;
        case 0xBB:
            return 0;
            break;
        case 0xBC:
            return 0;
            break;
        case 0xBD:
            return 0;
            break;
        case 0xBE:
            return 0;
            break;
        case 0xBF:
            return 0;
            break;

        /// UNIMPLEMENTED Row 0xC0-0xCF
        case 0xC0:
            return 0;
            break;
        case 0xC1:
            return 0;
            break;
        case 0xC2:
            return 0;
            break;
        case 0xC3:
            return 0;
            break;
        case 0xC4:
            return 0;
            break;
        case 0xC5:
            return 0;
            break;
        case 0xC6:
            return 0;
            break;
        case 0xC7:
            return 0;
            break;
        case 0xC8:
            return 0;
            break;
        case 0xC9:
            return 0;
            break;
        case 0xCA:
            return 0;
            break;
        case 0xCB:
            return 0;
            break;
        case 0xCC:
            return 0;
            break;
        case 0xCD:
            return 0;
            break;
        case 0xCE:
            return 0;
            break;
        case 0xCF:
            return 0;
            break;

        /// UNIMPLEMENTED Row 0xD0-0xDF
        case 0xD0:
            return 0;
            break;
        case 0xD1:
            return 0;
            break;
        case 0xD2:
            return 0;
            break;
        case 0xD3:
            return 0;
            break;
        case 0xD4:
            return 0;
            break;
        case 0xD5:
            return 0;
            break;
        case 0xD6:
            return 0;
            break;
        case 0xD7:
            return 0;
            break;
        case 0xD8:
            return 0;
            break;
        case 0xD9:
            return 0;
            break;
        case 0xDA:
            return 0;
            break;
        case 0xDB:
            return 0;
            break;
        case 0xDC:
            return 0;
            break;
        case 0xDD:
            return 0;
            break;
        case 0xDE:
            return 0;
            break;
        case 0xDF:
            return 0;
            break;

        /// UNIMPLEMENTED Row 0xE0-0xEF 
        case 0xE0:
            return 0;
            break;
        case 0xE1:
            return 0;
            break;
        case 0xE2:
            return 0;
            break;
        case 0xE3:
            return 0;
            break;
        case 0xE4:
            return 0;
            break;
        case 0xE5:
            return 0;
            break;
        case 0xE6:
            return 0;
            break;
        case 0xE7:
            return 0;
            break;
        case 0xE8:
            return 0;
            break;
        case 0xE9:
            return 0;
            break;
        case 0xEA:
            return 0;
            break;
        case 0xEB:
            return 0;
            break;
        case 0xEC:
            return 0;
            break;
        case 0xED:
            return 0;
            break;
        case 0xEE:
            return 0;
            break;
        case 0xEF:
            return 0;
            break;

        /// UNIMPLEMENTED Row 0xF0-0xFF
        case 0xF0:
            return 0;
            break;
        case 0xF1:
            return 0;
            break;
        case 0xF2:
            return 0;
            break;
        case 0xF3:
            return 0;
            break;
        case 0xF4:
            return 0;
            break;
        case 0xF5:
            return 0;
            break;
        case 0xF6:
            return 0;
            break;
        case 0xF7:
            return 0;
            break;
        case 0xF8:
            return 0;
            break;
        case 0xF9:
            return 0;
            break;
        case 0xFA:
            return 0;
            break;
        case 0xFB:
            return 0;
            break;
        case 0xFC:
            return 0;
            break;
        case 0xFD:
            return 0;
            break;
        case 0xFE:
            return 0;
            break;
        case 0xFF:
            return 0;
            break;

        default:
            break;
    }
}