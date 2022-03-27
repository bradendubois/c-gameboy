#include <stdint.h>

#include "cpu.h"
#include "alu.h"
#include "registers.h"

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