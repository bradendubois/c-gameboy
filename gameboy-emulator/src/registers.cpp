#include <stdint.h>

#include "include/gameboy.h"
#include "include/registers.h"

const uint8_t REGISTER_VALUES [7][8]{
    {0x01, 0x00, 0xFF, 0x13, 0x00, 0xC1, 0x84, 0x03},   // DMG0
    {0x01, 0x80, 0x00, 0x13, 0x00, 0xD8, 0x01, 0x4D},   // DMG
    {0xFF, 0x80, 0x00, 0x13, 0x00, 0xD8, 0x01, 0x4D},   // MGB
    {0x01, 0x00, 0x00, 0x14, 0x00, 0x00, 0xC0, 0x60},   // SGB
    {0xFF, 0x00, 0x00, 0x14, 0x00, 0x00, 0xC0, 0x60},   // SGB2
    {0x11, 0x80, 0x00, 0x00, 0xFF, 0x56, 0x0D, 0x0D},   // CGB
    {0x11, 0x00, 0x00, 0x00, 0xFF, 0x56, 0x0D, 0x0D}    // AGB
};

void Registers::initialize(GAMEBOY_MODEL MODEL, uint16_t checksum)
{
    const uint8_t* VALUES = REGISTER_VALUES[MODEL];
    _a = VALUES[0];
    _f = VALUES[1];
    _b = VALUES[2];
    _c = VALUES[3];
    _d = VALUES[4];
    _e = VALUES[5];
    _h = VALUES[6];
    _l = VALUES[7];

    _pc = 0x0100;
    _sp = 0xFFFE;

    if ((MODEL == GAMEBOY_MODEL::DMG) || (MODEL == GAMEBOY_MODEL::MGB))
    {
        flag_c(checksum != 0x00);
        flag_h(checksum != 0x00);
    }
}
