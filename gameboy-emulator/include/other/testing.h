#ifndef TESTING_H
#define TESTING_H

#include <stdint.h>
#include <tuple>
#include <vector>

#include <iomanip>
#include <iostream>
#include <sstream>

#include "include/other/constants.h"
#include "include/gameboy.h"

enum TESTING_FRAMEWORK {
    MOONEYE,
    BLARGG
};

struct Breakpoint {
    DEBUG_PARAMETER param;
    DEBUG_RESPONSE response;
    DEBUG_TIME time;
    uint16_t address;
    uint8_t value;
};

const std::tuple<std::string, GAMEBOY_MODEL, TESTING_FRAMEWORK> testRoms[]{
    
    // // mbc1
    // {"./roms/mooneye/emulator-only/mbc1/bits_bank1.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/emulator-only/mbc1/bits_bank2.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/emulator-only/mbc1/bits_mode.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/emulator-only/mbc1/bits_ramg.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/emulator-only/mbc1/ram_64kb.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/emulator-only/mbc1/ram_256kb.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/emulator-only/mbc1/rom_512kb.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/emulator-only/mbc1/rom_1Mb.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/emulator-only/mbc1/rom_2Mb.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/emulator-only/mbc1/rom_4Mb.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/emulator-only/mbc1/rom_8Mb.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/emulator-only/mbc1/rom_16Mb.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    
    // // {"./roms/mooneye/emulator-only/mbc2/bits_ramg.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/emulator-only/mbc2/bits_romb.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/emulator-only/mbc2/bits_unused.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/emulator-only/mbc2/ram.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/emulator-only/mbc2/rom_512kb.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/emulator-only/mbc2/rom_1Mb.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/emulator-only/mbc2/rom_2Mb.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    
    // // mbc5
    // {"./roms/mooneye/emulator-only/mbc5/rom_1Mb.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/emulator-only/mbc5/rom_2Mb.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/emulator-only/mbc5/rom_4Mb.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/emulator-only/mbc5/rom_8Mb.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/emulator-only/mbc5/rom_512kb.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/emulator-only/mbc5/rom_16Mb.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/emulator-only/mbc5/rom_32Mb.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/emulator-only/mbc5/rom_64Mb.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},

    // // acceptance misc
    // {"./roms/mooneye/acceptance/bits/mem_oam.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/acceptance/bits/reg_f.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/acceptance/instr/daa.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/acceptance/interrupts/ie_push.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/acceptance/add_sp_e_timing.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},

    // // boot_div
    // {"./roms/mooneye/acceptance/boot_div-dmg0.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/acceptance/boot_div-dmgABCmgb.gb", GAMEBOY_MODEL::DMG, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/acceptance/boot_div-dmgABCmgb.gb", GAMEBOY_MODEL::MGB, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/acceptance/boot_div-S.gb", GAMEBOY_MODEL::SGB, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/acceptance/boot_div-S.gb", GAMEBOY_MODEL::SGB2, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/acceptance/boot_div2-S.gb", GAMEBOY_MODEL::SGB, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/acceptance/boot_div2-S.gb", GAMEBOY_MODEL::SGB2, TESTING_FRAMEWORK::MOONEYE},

    // // boot_hwio
    // {"./roms/mooneye/acceptance/boot_hwio-dmg0.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/acceptance/boot_hwio-dmgABCmgb.gb", GAMEBOY_MODEL::DMG, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/acceptance/boot_hwio-dmgABCmgb.gb", GAMEBOY_MODEL::AGB, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/acceptance/boot_hwio-S.gb", GAMEBOY_MODEL::SGB, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/acceptance/boot_hwio-S.gb", GAMEBOY_MODEL::SGB2, TESTING_FRAMEWORK::MOONEYE},
    
    // // boot_regs
    // {"./roms/mooneye/acceptance/boot_regs-dmg0.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/acceptance/boot_regs-dmgABC.gb", GAMEBOY_MODEL::DMG, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/acceptance/boot_regs-mgb.gb", GAMEBOY_MODEL::MGB, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/acceptance/boot_regs-sgb.gb", GAMEBOY_MODEL::SGB, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/acceptance/boot_regs-sgb2.gb", GAMEBOY_MODEL::SGB2, TESTING_FRAMEWORK::MOONEYE},
    
    // // timing misc
    // {"./roms/mooneye/acceptance/call_cc_timing.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/acceptance/call_cc_timing2.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/acceptance/call_timing.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/acceptance/call_timing2.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/acceptance/div_timing.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/acceptance/ei_sequence.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/acceptance/ei_timing.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/acceptance/if_ie_registers.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/acceptance/intr_timing.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/acceptance/jp_cc_timing.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/acceptance/jp_timing.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/acceptance/ld_hl_sp_e_timing.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/acceptance/pop_timing.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/acceptance/push_timing.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/acceptance/rapid_di_ei.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/acceptance/ret_cc_timing.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/acceptance/reti_timing.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/acceptance/rst_timing.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE}
    // {"./roms/mooneye/acceptance/ret_timing.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    // {"./roms/mooneye/acceptance/reti_intr_timing.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},

    // timer
    {"./roms/mooneye/acceptance/timer/div_write.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    {"./roms/mooneye/acceptance/timer/rapid_toggle.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    {"./roms/mooneye/acceptance/timer/tim00_div_trigger.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    {"./roms/mooneye/acceptance/timer/tim00.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    {"./roms/mooneye/acceptance/timer/tim01_div_trigger.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    {"./roms/mooneye/acceptance/timer/tim01.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    {"./roms/mooneye/acceptance/timer/tim10_div_trigger.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    {"./roms/mooneye/acceptance/timer/tim11_div_trigger.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    {"./roms/mooneye/acceptance/timer/tim11.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    {"./roms/mooneye/acceptance/timer/tima_reload.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    {"./roms/mooneye/acceptance/timer/tima_write_reloading.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},
    {"./roms/mooneye/acceptance/timer/tma_write_reloading.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::MOONEYE},

    // blargg
    {"./roms/blargg/01-special.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::BLARGG},
    {"./roms/blargg/02-interrupts.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::BLARGG},
    {"./roms/blargg/03-op sp,hl.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::BLARGG},
    {"./roms/blargg/04-op r,imm.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::BLARGG},
    {"./roms/blargg/05-op rp.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::BLARGG},
    {"./roms/blargg/06-ld r,r.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::BLARGG},
    {"./roms/blargg/07-jr,jp,call,ret,rst.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::BLARGG},
    {"./roms/blargg/08-misc instrs.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::BLARGG},
    {"./roms/blargg/09-op r,r.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::BLARGG},
    {"./roms/blargg/10-bit ops.gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::BLARGG},
    {"./roms/blargg/11-op a,(hl).gb", GAMEBOY_MODEL::DMG0, TESTING_FRAMEWORK::BLARGG},
};

std::tuple<int, int> TEST();
std::string hexout(int digits, uint16_t value);

#endif
