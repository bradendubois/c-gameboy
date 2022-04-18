#ifndef MMU_H
#define MMU_H

#include <iostream>
#include <set>
#include <stdint.h>
#include <vector>

#include <QObject>

class CPU;
class PPU;
class Timer;
class Serial;
class Joypad;
class Sound;

#include "include/cartridge.h"
#include "include/cpu.h"
#include "include/gameboy.h"
#include "include/gui_breakpoints.h"
#include "include/joypad.h"
#include "include/mbc.h"
#include "include/mbc1.h"
#include "include/ppu.h"
#include "include/serial.h"
#include "include/sound.h"
#include "include/timer.h"

constexpr uint16_t W_RAM_SIZE = 0x2000;
constexpr uint16_t H_RAM_SIZE = 0x7E;
constexpr uint16_t OAM_SIZE = 0xA0;

#ifdef DEBUG
class MMU {
#else
class MMU: public QObject {
    Q_OBJECT
#endif

    public:
        #ifdef DEBUG
        MMU(std::vector<uint8_t> *data);
        #else
        MMU(QObject *parent, std::vector<uint8_t> *data);
        #endif
        ~MMU();

        uint8_t  byte(uint16_t address);
        uint16_t word(uint16_t address);

        uint8_t read(uint16_t address);
        uint16_t read_word(uint16_t address);

        void write(uint16_t address, uint8_t value);
        void write(uint16_t address, uint16_t value);
        void watchAddress(ADDRESS_ACCESS r, uint16_t address);

        std::vector<uint8_t> mooneye();

    #ifndef DEBUG
    signals:
        void accessHalt(ADDRESS_ACCESS r, uint16_t address);
    #endif

    protected:
        friend class CPU;
        friend class PPU;
        friend class Timer;
        friend class Gameboy;

        CPU *cpu;
        PPU *ppu;
        Timer *timer;
        Joypad *joypad;
        Serial *serial;
        Sound *sound;
        MBC *mbc;

    private:

        std::vector<uint8_t> w_ram; 
        std::vector<uint8_t> h_ram;
        std::vector<uint8_t> oam;

        uint8_t ff0f, ffff;

        std::set<uint16_t> watchReads;
        std::set<uint16_t> watchWrites;
};


#include "include/ppu.h"

#endif
