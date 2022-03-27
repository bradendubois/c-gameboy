#ifndef REGISTERS_H
#define REGISTERS_H

#include "cpu.h"

class Registers {

    public:
        Registers() {};

        uint16_t af() { return (((uint16_t) _a) << 8) | ((uint16_t) _f); }
        uint16_t bc() { return (((uint16_t) _b) << 8) | ((uint16_t) _c); }
        uint16_t de() { return (((uint16_t) _d) << 8) | ((uint16_t) _e); }
        uint16_t hl() { return (((uint16_t) _h) << 8) | ((uint16_t) _l); }
        
        void af(uint16_t value) { _a = value >> 8; _f = 0x0F & value; }
        void bc(uint16_t value) { _b = value >> 8; _c = 0x0F & value; }
        void de(uint16_t value) { _d = value >> 8; _e = 0x0F & value; }
        void hl(uint16_t value) { _h = value >> 8; _l = 0x0F & value; }

        bool flag_z(void) {    return _f & 0b10000000; }
        void flag_z(bool set) { _f = (_f & 0b01111111) | (set ? 0b10000000 : 0b00000000); };

        bool flag_n(void) {    return _f & 0b01000000; }
        void flag_n(bool set) { _f = (_f & 0b10111111) | (set ? 0b01000000 : 0b00000000); };

        bool flag_h(void) {    return _f & 0b00100000; }
        void flag_h(bool set) { _f = (_f & 0b11011111) | (set ? 0b00100000 : 0b00000000); };

        bool flag_c(void) {    return _f & 0b00010000; }
        void flag_c(bool set) { _f = (_f & 0b11101111) | (set ? 0b00010000 : 0b00000000); };

        uint8_t _a;
        uint8_t _b;
        uint8_t _c;
        uint8_t _d;
        uint8_t _e;
        uint8_t _f;
        uint8_t _h;
        uint8_t _l;

        uint16_t _sp;
        uint16_t _pc;
};

#endif
