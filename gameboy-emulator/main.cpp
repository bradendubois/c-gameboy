#ifndef DEBUG
#include "include/mainwindow.h"
#endif

#include "include/gameboy.h"

#include <fstream>
#include <iterator>
#include <iostream>
#include <vector>
#include <stdint.h>

#include <QApplication>
#include <QObject>


const std::vector<std::string> roms{
    "./roms/mooneye/emulator-only/mbc1/bits_bank1.gb",
    "./roms/mooneye/emulator-only/mbc1/bits_bank2.gb",
    "./roms/mooneye/emulator-only/mbc1/bits_mode.gb",
    "./roms/mooneye/emulator-only/mbc1/bits_ramg.gb",
    "./roms/mooneye/emulator-only/mbc1/ram_64kb.gb",
    "./roms/mooneye/emulator-only/mbc1/ram_256kb.gb",
    "./roms/mooneye/emulator-only/mbc1/rom_512kb.gb",
    "./roms/mooneye/emulator-only/mbc1/rom_1Mb.gb",
    "./roms/mooneye/emulator-only/mbc1/rom_2Mb.gb",
    "./roms/mooneye/emulator-only/mbc1/rom_4Mb.gb",
    "./roms/mooneye/emulator-only/mbc1/rom_8Mb.gb",
    "./roms/mooneye/emulator-only/mbc1/rom_16Mb.gb"
};

int main(int argc, char *argv[])
{
    #ifdef DEBUG
        Gameboy gb;
        for (auto rom: roms) {
            std::cout << rom.substr(rom.rfind("/")) << " - ";
            gb.initialize(rom);
            auto r = gb.mooneye();
            if (r[0] == 3 && r[1] == 5 && r[2] == 8 && r[3] == 13 && r[4] == 21 && r[5] == 34) {
                std::cout << "pass" << std::endl;
            } else {
                std::cout << "fail" << std::endl;
            }
        }

        return 0;
    #endif

    #ifndef DEBUG

        char *rom = nullptr;
        if (argc > 1) {
            rom = argv[1];
        }

        QApplication a(argc, argv);
        MainWindow w(rom);

        w.show();

        return a.exec();

    #endif
}
