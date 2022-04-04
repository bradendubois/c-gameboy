#ifndef MMU_H
#define MMU_H

#include <iostream>
#include <stdint.h>
#include <vector>

#include "joypad.h"
#include "mbc.h"
#include "mbc1.h"
#include "serial.h"
#include "sound.h"
#include "timer.h"

const uint16_t W_RAM_SIZE = 0x2000;

class MMU {

    public:
        MMU(std::vector<uint8_t> *cartridge): 
            w_ram(std::vector<uint8_t>(W_RAM_SIZE, 0)),
            mbc(MBC1(cartridge)),
            joypad(Joypad()),
            serial(Serial()),
            timer(Timer()),
            sound(Sound())
            {

    // Joypad j = Joypad();

    // QObject::connect(&w, &MainWindow::pressed, &j, &Joypad::receivePress);

            };

        uint8_t  byte(uint16_t address);
        uint16_t word(uint16_t address);

        uint8_t read(uint16_t address);
        uint16_t read_word(uint16_t address);

        void write(uint16_t address, uint8_t value);
        void write(uint16_t address, uint16_t value);

    private:
        std::vector<uint8_t> w_ram; 
        MBC1 mbc;
        Joypad joypad;
        Serial serial;
        Timer timer;
        Sound sound;
};

#endif
