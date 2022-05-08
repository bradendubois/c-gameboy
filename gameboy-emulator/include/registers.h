#ifndef REGISTERS_H
#define REGISTERS_H

#include <iomanip>
#include <iostream>
#include <sstream>
#include <QObject>

#include <stdint.h>

#include "include/gameboy.h"

class Registers {

    public:
        Registers() {};
        void initialize(GAMEBOY_MODEL MODEL, uint16_t checksum);

        uint16_t af() { return (((uint16_t) _a) << 8) | ((uint16_t) _f); }
        uint16_t bc() { return (((uint16_t) _b) << 8) | ((uint16_t) _c); }
        uint16_t de() { return (((uint16_t) _d) << 8) | ((uint16_t) _e); }
        uint16_t hl() { return (((uint16_t) _h) << 8) | ((uint16_t) _l); }
        
        // void af(uint16_t value) { _a = value >> 8; _f = 0xFF & value; std::cout << std::hex << (int) af() << std::dec << std::endl; }
        void af(uint16_t value) { _a = value >> 8; _f = 0xFF & value; }
        void bc(uint16_t value) { _b = value >> 8; _c = 0xFF & value; }
        void de(uint16_t value) { _d = value >> 8; _e = 0xFF & value; }
        void hl(uint16_t value) { _h = value >> 8; _l = 0xFF & value; }

        bool flag_z(void) {   return (_f & 0b10000000) != 0; }
        void flag_z(bool set) { _f = (_f & 0b01111111) | (set ? 0b10000000 : 0b00000000); };

        bool flag_n(void) {   return (_f & 0b01000000) != 0; }
        void flag_n(bool set) { _f = (_f & 0b10111111) | (set ? 0b01000000 : 0b00000000); };

        bool flag_h(void) {   return (_f & 0b00100000) != 0; }
        void flag_h(bool set) { _f = (_f & 0b11011111) | (set ? 0b00100000 : 0b00000000); };

        bool flag_c(void) {   return (_f & 0b00010000) != 0; }
        void flag_c(bool set) { _f = (_f & 0b11101111) | (set ? 0b00010000 : 0b00000000); };

        uint8_t _a;
        uint8_t _f;
        uint8_t _b;
        uint8_t _c;
        uint8_t _d;
        uint8_t _e;
        uint8_t _h;
        uint8_t _l;

        uint16_t _pc;
        uint16_t _sp;

        std::string hexout(int digits, uint16_t value) {
            std::ostringstream ss;
            ss << std::setfill('0') << std::setw(digits) << std::hex << value;
            return "0x" + ss.str();
        }

        std::string decout(int digits, uint16_t value) {
            std::ostringstream ss;
            ss << std::setfill('0') << std::setw(digits) << std::dec << value;
            return "d" + ss.str();
        }

        std::string toString() {
            return
                " A:   " + hexout(2, _a)  + " " + decout(2, _a) + " |  F   " + hexout(2, _f) + " " + decout(2, _f) + "\n" +
                " B:   " + hexout(2, _b)  + " " + decout(2, _b) + " |  C   " + hexout(2, _c) + " " + decout(2, _c) + "\n" +
                " D:   " + hexout(2, _d)  + " " + decout(2, _d) + " |  E   " + hexout(2, _e) + " " + decout(2, _e) + "\n" +
                " H:   " + hexout(2, _h)  + " " + decout(2, _h) + " |  L   " + hexout(2, _l) + " " + decout(2, _l) + "\n" +
                "PC: " + hexout(4, _pc) + " " + decout(4, _pc) + " | SP " + hexout(4, _sp) + " " + decout(4, _sp) + "\n";
        }

};

#endif
