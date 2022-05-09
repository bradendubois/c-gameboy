#ifndef MMU_H
#define MMU_H

#include <iostream>
#include <set>
#include <stdint.h>
#include <vector>

#include <QObject>

#ifdef DEBUG
#include "include/other/testing.h"
#else
#include "include/gui/gui_breakpoints.h"
#endif

#include "include/gameboy.h"
#include "include/other/constants.h"

#include "include/cartridge.h"
#include "include/cpu.h"
#include "include/joypad.h"
#include "include/mbcs/mbc.h"
#include "include/ppu.h"
#include "include/serial.h"
#include "include/sound.h"
#include "include/timer.h"

class CPU;
class PPU;
class Timer;
class Serial;
class Joypad;
class Sound;

#ifdef DEBUG
class MMU {
#else
class MMU: public QObject {
    Q_OBJECT
#endif

    public:
        #ifdef DEBUG
        MMU(CPU *cpu, std::vector<uint8_t> *data);
        #else
        MMU(CPU *cpu, QObject *parent, std::vector<uint8_t> *data, GAMEBOY_MODEL model);
        #endif
        ~MMU();

        uint8_t  byte(uint16_t address);
        uint16_t word(uint16_t address);

        uint8_t read(uint16_t address);
        uint16_t read_word(uint16_t address);

        void write(uint16_t address, uint8_t value);
        void write(uint16_t address, uint16_t value);

        std::vector<uint8_t> mooneye();

        void initialize(GAMEBOY_MODEL model);
        void cycle(uint64_t cycles);
        void debug(Breakpoint b);


    #ifndef DEBUG
    signals:
        void accessHalt(ADDRESS_ACCESS r, uint16_t address);
    #endif

    protected:
        friend class CPU;
        friend class PPU;
        friend class Timer;
        friend class Serial;
        friend class Gameboy;

        CPU *cpu;
        PPU *ppu;
        Timer *timer;
        Joypad *joypad;
        Serial *serial;
        Sound *sound;
        Cartridge *cartridge;

        bool blargg;

    private:

        std::vector<uint8_t> w_ram; 
        std::vector<uint8_t> h_ram;
        std::vector<uint8_t> oam;

        uint8_t ff0f, ffff;

        std::set<uint16_t> watchReads;
        std::set<uint16_t> watchWrites;

        std::set<std::tuple<uint16_t, uint8_t>> watchReadValues;
        std::set<std::tuple<uint16_t, uint8_t>> watchWriteValues;
};



#endif
