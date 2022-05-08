#include "../include/serial.h"

void Serial::write(uint16_t address, uint8_t value) {
    switch (address) {
        case 0xFF01:
            ff01 = value;
            break;
        case 0xFF02:
            if (sWrite == DEBUG_RESPONSE::PRINT) {
                std::cout << (char) (int) ff01 << " " << (int) value << std::endl;
            }
            ff02 = value;
            break;
        __builtin_unreachable();
        default:
            return;
    };
}

uint8_t Serial::read(uint16_t address) {
    switch (address) {
        case 0xFF01:
            return ff01;
        case 0xFF02:
            return ff02;
        __builtin_unreachable();
        default:
            return 0;
    }
}

void Serial::advanceCycles(uint64_t cycles)
{
    counter += cycles;
    while (counter >= 512)
    {
        _cycle();
        counter -= 512;
    }
}

void Serial::_cycle()
{
    rotation++;
    ff01 <<= 1;
    ff01 |= 0x01;

    if (rotation == 8)
    {
        mmu->ff0f |= 0x08;
    }
}

void Serial::debug(Breakpoint b)
{
    switch (b.param) {
        case DEBUG_PARAMETER::SERIAL_WRITE:
            sWrite = b.response;
            break;
    }
}