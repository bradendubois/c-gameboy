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
    "./roms/mooneye/emulator-only/mbc1/rom_16Mb.gb",
    "./roms/mooneye/emulator-only/mbc2/bits_ramg.gb",
    "./roms/mooneye/emulator-only/mbc2/bits_romb.gb",
    "./roms/mooneye/emulator-only/mbc2/bits_unused.gb",
    "./roms/mooneye/emulator-only/mbc2/ram.gb",
    "./roms/mooneye/emulator-only/mbc2/rom_1Mb.gb",
    "./roms/mooneye/emulator-only/mbc2/rom_2Mb.gb",
    "./roms/mooneye/emulator-only/mbc2/rom_512kb.gb",
    // "./roms/mooneye/emulator-only/mbc5/rom_1Mb.gb",
    // "./roms/mooneye/emulator-only/mbc5/rom_2Mb.gb",
    // "./roms/mooneye/emulator-only/mbc5/rom_4Mb.gb",
    // "./roms/mooneye/emulator-only/mbc5/rom_8Mb.gb",
    // "./roms/mooneye/emulator-only/mbc5/rom_16Mb.gb",
    // "./roms/mooneye/emulator-only/mbc5/rom_32Mb.gb",
    // "./roms/mooneye/emulator-only/mbc5/rom_64Mb.gb",
    // "./roms/mooneye/emulator-only/mbc5/rom_512kb.gb",
    "./roms/mooneye/acceptance/bits/mem_oam.gb",
    "./roms/mooneye/acceptance/bits/reg_f.gb",
    "./roms/mooneye/acceptance/instr/daa.gb",
    "./roms/mooneye/acceptance/interrupts/ie_push.gb",
    "./roms/mooneye/acceptance/add_sp_e_timing.gb",
    "./roms/mooneye/acceptance/boot_div-dmg0.gb",
    "./roms/mooneye/acceptance/boot_hwio-dmg0.gb",
    "./roms/mooneye/acceptance/boot_regs-dmg0.gb",
    "./roms/mooneye/acceptance/call_cc_timing.gb",
    "./roms/mooneye/acceptance/call_cc_timing2.gb",
    "./roms/mooneye/acceptance/call_timing.gb",
    "./roms/mooneye/acceptance/call_timing2.gb",
    "./roms/mooneye/acceptance/div_timing.gb",
    "./roms/mooneye/acceptance/ei_sequence.gb",
    "./roms/mooneye/acceptance/ei_timing.gb",
    "./roms/mooneye/acceptance/if_ie_registers.gb",
};


    
    
// "./roms/mooneye/acceptance/intr_timing.gb",
//     "./roms/mooneye/acceptance/jp_cc_timing.gb",
//     "./roms/mooneye/acceptance/jp_timing.gb",
//     "./roms/mooneye/acceptance/ld_hl_sp_e_timing.gb",
//     "./roms/mooneye/acceptance/pop_timing.gb",
//     "./roms/mooneye/acceptance/push_timing.gb",
//     "./roms/mooneye/acceptance/rapid_di_ei.gb",
//     "./roms/mooneye/acceptance/ret_cc_timing.gb",
//     "./roms/mooneye/acceptance/reti_timing.gb",
//     "./roms/mooneye/acceptance/rst_timing.gb"
    // "./roms/mooneye/acceptance/ret_timing.gb",
    // "./roms/mooneye/acceptance/reti_intr_timing.gb",

int main(int argc, char *argv[])
{
    #ifdef DEBUG
        for (auto rom: roms) {
            std::cout << rom.substr(rom.rfind("/", rom.rfind("/") - 1)) << " - ";
            Gameboy gb;
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
