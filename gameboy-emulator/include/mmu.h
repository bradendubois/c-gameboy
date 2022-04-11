#ifndef MMU_H
#define MMU_H

#include <iostream>
#include <set>
#include <stdint.h>
#include <vector>

#include <QObject>

#include "include/gui_breakpoints.h"
#include "joypad.h"
#include "mbc.h"
#include "mbc1.h"
#include "serial.h"
#include "sound.h"
#include "timer.h"
#include "include/cpu.h"
#include "include/ppu.h"
#include "include/cartridge.h"

class CPU;

constexpr uint16_t W_RAM_SIZE = 0x2000;
constexpr uint16_t H_RAM_SIZE = 0x7E;
constexpr uint16_t OAM_SIZE = 0xA0;

class MMU: public QObject {

    Q_OBJECT

    public:
        MMU(QObject *parent, Cartridge *cartridge);

        uint8_t  byte(uint16_t address);
        uint16_t word(uint16_t address);

        uint8_t read(uint16_t address);
        uint16_t read_word(uint16_t address);

        void write(uint16_t address, uint8_t value);
        void write(uint16_t address, uint16_t value);
        void watchAddress(ADDRESS_ACCESS r, uint16_t address);

    signals:
        void accessHalt(ADDRESS_ACCESS r, uint16_t address);

    protected:
        friend class CPU;
        friend class PPU;

        CPU *cpu;
        PPU *ppu;

    private:
        MBC1 mbc;

        std::vector<uint8_t> w_ram; 
        std::vector<uint8_t> h_ram;
        std::vector<uint8_t> oam;

        Joypad joypad;
        Serial serial;
        Timer timer;
        Sound sound;

        std::set<uint16_t> watchReads;
        std::set<uint16_t> watchWrites;
};


#include "include/ppu.h"

#endif
