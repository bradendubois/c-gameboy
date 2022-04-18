#include <stdint.h>


#include "include/cpu.h"
#include "include/gui_breakpoints.h"
#include "include/mmu.h"

#include "include/mbc0.h"
#include "include/mbc1.h"
#include "include/ppu.h"


MBC* mbcFactory(std::vector<uint8_t> *data) {
    switch (data->at(0x147)) {
        case 0x00:
            // std::cout << "MBC0" << std::endl;
            return new MBC0(data);
        case 0x01 ... 0x03:
            // std::cout << "MBC1" << std::endl;
            return new MBC1(data);
        default:
            std::cerr << "Unknown MBC type " << (int) data->at(0x147) << std::endl;
            exit(1);
    }
}

MMU::~MMU() {
    std::cout << "Deleting MBC" << std::endl;
    delete mbc;
    std::cout << "Deleting CPU" << std::endl;
    delete cpu;
    std::cout << "Deleting PPU" << std::endl;
    delete ppu;
    std::cout << "Deleting Joypad" << std::endl;
    delete joypad;
    std::cout << "Deleting Serial" << std::endl;
    delete serial;
    std::cout << "Deleting Sound" << std::endl;
    delete sound;
    std::cout << "Done MMU Delete" << std::endl;
};

#ifndef DEBUG
MMU::MMU(QObject *parent, std::vector<uint8_t> *data): QObject(parent), w_ram(std::vector<uint8_t>(W_RAM_SIZE, 0)), h_ram(std::vector<uint8_t>(H_RAM_SIZE, 0)), oam(std::vector<uint8_t>(OAM_SIZE, 0)), joypad(Joypad()), serial(Serial()), sound(Sound())
{
    mbc = mbcFactory(data);

    ff0f = 0xE1;
    ffff = 0;

    // Joypad j = Joypad();

    // QObject::connect(&w, &MainWindow::pressed, &j, &Joypad::receivePress);
}
#else
MMU::MMU(std::vector<uint8_t> *data): w_ram(std::vector<uint8_t>(W_RAM_SIZE, 0)), h_ram(std::vector<uint8_t>(H_RAM_SIZE, 0)), oam(std::vector<uint8_t>(OAM_SIZE, 0))
{
    mbc = mbcFactory(data);
    cpu = new CPU(this);
    ppu = new PPU(this);
    timer = new Timer(this);
    joypad = new Joypad(this);
    serial = new Serial(this);
    sound = new Sound(this);

    ff0f = 0xE1;
    ffff = 0;

    // Joypad j = Joypad();

    // QObject::connect(&w, &MainWindow::pressed, &j, &Joypad::receivePress);

}
#endif

uint8_t MMU::read(uint16_t address) {
    if (watchReads.contains(address)) {
        #ifndef DEBUG
        emit accessHalt(ADDRESS_ACCESS::READ, address);
        #endif
    }
    switch (address) {
        case 0x0000 ... 0x7FFF:
            return mbc->read(address);
        case 0x8000 ... 0x9FFF:
            return ppu->read(address);
        case 0xA000 ... 0xBFFF:
            return mbc->read(address);
        case 0xC000 ... 0xDFFF:
            return w_ram[address & (W_RAM_SIZE - 1)];
        case 0xE000 ... 0xFDFF:
            return w_ram[address & 0x1FFF];
        case 0xFE00 ... 0xFE9F:
            return oam[address & 0xFF];
        case 0xFEA0 ... 0xFEFF: // prohibited
            return 0;
        case 0xFF00 ... 0xFF7F: {
            switch (address) {
                case 0xFF00:
                    return joypad->read();
                case 0xFF01 ... 0xFF02:
                    return serial->read(address);
                case 0xFF04 ... 0xFF07:
                    return timer->read(address);
                case 0xFF0F:
                    return ff0f;
                case 0xFF40 ... 0xFF4B:
                    return ppu->read(address);
                default:
                    return 0xFF;
            }
        }
        case 0xFF80 ... 0xFFFE:
            return h_ram[address & 0xFF];
        case 0xFFFF:
            return ffff;

        default:
            std::cerr << "UNAUTH RAM READ " << std::hex << address << std::dec << std::endl;
            exit(0);
    }
}

void MMU::write(uint16_t address, uint8_t value) {
    if (watchWrites.contains(address)) {
        #ifndef DEBUG
        emit accessHalt(ADDRESS_ACCESS::WRITE, address);
        #endif
    }

    switch (address) {
        case 0x0000 ... 0x7FFF:
            mbc->write(address, value);
            break;
        case 0x8000 ... 0x9FFF:
            // std::cout << "PPU WRITE" << std::endl;
            ppu->write(address, value);
            break;
        case 0xA000 ... 0xBFFF:
            mbc->write(address, value);
            break;
        case 0xC000 ... 0xDFFF:
            w_ram[address & (W_RAM_SIZE - 1)] = value;
            break;
        case 0xE000 ... 0xFDFF:
            w_ram[address & 0x1FFF] = value;
            break;
        case 0xFE00 ... 0xFE9F:
            oam[address & 0xFF] = value;
            break;
        case 0xFEA0 ... 0xFEFF: // prohibited
            break;
        case 0xFF00 ... 0xFF7F: {
            switch (address) {
                case 0xFF00:
                    joypad->write(value);
                    break;
                case 0xFF01 ... 0xFF02:
                    serial->write(address, value);
                    break;
                case 0xFF04 ... 0xFF07:
                    timer->write(address, value);
                    break;
                case 0xFF0F:
                    ff0f = value;
                    break;
                case 0xFF10 ... 0xFF3F:
                    // sound->write(address, value);
                    break;
                case 0xFF40 ... 0xFF4F:
                    ppu->write(address, value);
                    break;
                case 0xFF50:
                    break;
                case 0xFF51 ... 0xFF70:
                    break;
                case 0xFFFF:
                    ffff = value;
                    break;
                default:
                    return;
            }
            break;
        }
        case 0xFF80 ... 0xFFFE:
            h_ram[address & 0xFF] = value;
            break;
        case 0xFFFF ... 0xFFFF:
            break;

        default:
            std::cerr << "UNAUTH RAM WRITE " << std::hex << address << std::dec << std::endl;
            exit(0);
            return;
    }
}

void MMU::watchAddress(ADDRESS_ACCESS r, uint16_t address) {
    switch (r) {
        case ADDRESS_ACCESS::READ:
            watchReads.insert(address);
            break;
        case ADDRESS_ACCESS::WRITE:
            watchWrites.insert(address);
            break;
        default:
            break;
    }
}