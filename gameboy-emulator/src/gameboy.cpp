#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

class MMU;

#include "include/gameboy.h"
#include "include/cpu.h"
#include "include/gui_debug.h"
#include "include/mmu.h"
#include "include/ppu.h"
#include "include/timer.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QString>
#include <QImage>
#include <QTime>
#include <QCoreApplication>
#include <QPixmap>

#ifndef DEBUG
Gameboy::Gameboy(QWidget *parent): QVBoxLayout(parent), displayLabel(new QLabel), windowLabel(new QLabel), backgroundLabel(new QLabel), checkCycleCount(false), cycleCount(0) {
    addWidget(displayLabel);
    addWidget(backgroundLabel);
    addWidget(windowLabel);
    connect(this, &Gameboy::ready, this, &Gameboy::updateLocalGUI);
}
#endif

Gameboy::Gameboy() { }

void Gameboy::initialize(std::string romPath) {

    // std::cout << "Initialize " << std::endl;
    // TODO Add some cleanup here if swapping games

    std::ifstream instream(std::string(romPath), std::ios::in | std::ios::binary);
    std::vector<uint8_t> *data = new std::vector<uint8_t>((std::istreambuf_iterator<char>(instream)), std::istreambuf_iterator<char>());
    
    // cartridge = new Cartridge(data);
    
    #ifdef DEBUG
    mmu = new MMU(data);
    #else
    mmu = new MMU(this, cartridge);
    cpu = new CPU(mmu);
    ppu = new PPU(mmu, displayLabel, windowLabel, backgroundLabel);
    timer = new Timer(mmu);
    #endif


    // Joypad
    mmu->write(0xFF00, (uint8_t) 0xCF);

    // Timer
    mmu->write(0xFF0F, (uint8_t) 0x18);
    mmu->write(0xFF05, (uint8_t) 0x00);
    mmu->write(0xFF06, (uint8_t) 0x00);
    mmu->write(0xFF07, (uint8_t) 0xF8);

    // Interrupt Flag
    mmu->write(0xFF0F, (uint8_t) 0xE1);

    // PPU Initialization
    // mmu->write(0xFF40, (uint8_t) 0x91);
    mmu->write(0xFF40, (uint8_t) (0x91 | 0x02));
    mmu->write(0xFF41, (uint8_t) 0x81);
    mmu->write(0xFF42, (uint8_t) 0x00);
    mmu->write(0xFF43, (uint8_t) 0x00);
    // mmu->write(0xFF44, (uint8_t) 0x91);
    mmu->write(0xFF44, (uint8_t) 0x00);
    mmu->write(0xFF45, (uint8_t) 0x00);
    mmu->write(0xFF46, (uint8_t) 0xFF);
    mmu->write(0xFF47, (uint8_t) 0xFC);
    mmu->write(0xFF47, (uint8_t) 0x1B);
    mmu->write(0xFF48, (uint8_t) 0x1B);
    mmu->write(0xFF49, (uint8_t) 0x1B);
    mmu->write(0xFF4A, (uint8_t) 0x00);
    mmu->write(0xFF4B, (uint8_t) 0x00);
    mmu->write(0xFF4D, (uint8_t) 0xFF);
    mmu->write(0xFF4F, (uint8_t) 0xFF);

    // std::cout << "initialized " << std::endl;

    // std::vector<uint8_t> a{0xFF, 0x00, 0x7E, 0xFF, 0x85, 0x81, 0x89, 0x83, 0x93, 0x85, 0xA5, 0x8B, 0xC9, 0x97, 0x7E, 0xFF};
    // std::vector<uint8_t> b{0x7C, 0x7C, 0x00, 0xC6, 0xC6, 0x00, 0x00, 0xFE, 0xC6, 0xC6, 0x00, 0xC6, 0xC6, 0x00, 0x00, 0x00};
    // std::vector<uint8_t> *c = &a;

    // bool flip = false;
    // for (int i = 0; i < 256; i++) {
    //     std::cout << std::hex << "Starting write at " << (int) 0x8800 + (i * 16) << std::dec << std::endl;
    //     if (i % 32 == 0) { c = (c == &a ? &b : &a); }
    //     for (int k = 0; k < 16; ++k) {
    //         mmu->write(0x8800 + (i * 16) + k, c->at(k));
    //     }
    //     c = (c == &a ? &b : &a);
    // }


    // for (int i = 0; i < 16; i++) {
    //     if (i % 32 == 0) { c = (c == &a ? &b : &a); }
    //     // std::cout << std::hex << "Starting write at " << (int) 0x8000 + (i * 16) << std::dec << std::endl;
    //     for (int k = 0; k < 16; ++k) {
            
    //         mmu->write(0x8000 + (i * 16) + k, c->at(k));
    //     }
    //     c = (c == &a ? &b : &a);
    // }

    // for (int i = 0; i < 32; i++) {
    //     for (int j = 0; j < 32; j++) {
    //         mmu->write(0x9800 | (i * 32) + j, (uint8_t) ((j % 2 == 0 ? 2 : 1)));
    //         if (mmu->read(0x9800 | (i * 32) + j) != (uint8_t) ((j % 2 == 0 ? 2 : 1))) {
    //             std::cout << "ERR " << std::hex << (0x9800 | (i * 32) + j) << " " << (int) mmu->read(0x9800 | (i * 32) + j) << std::dec << std::endl; 
    //         }
    //     }
    // }

    // for (int i = 0; i < 20; i++) {

    //     mmu->write(0xC000 | (uint16_t) (i * 8), (uint8_t) 45);
    //     mmu->write(0xC001 | (uint16_t) ((i * 8) + 1), (uint8_t) 155);
    //     mmu->write(0xC002 | (uint16_t) ((i * 8) + 2), (uint8_t) 0);
    //     mmu->write(0xC003 | (uint16_t) ((i * 8) + 3), (uint8_t) 0b00010000);


    //     mmu->write(0xC004 | (uint16_t) (i * 8), (uint8_t) 140);
    //     mmu->write(0xC005 | (uint16_t) ((i * 8) + 1), (uint8_t) 80);
    //     mmu->write(0xC006 | (uint16_t) ((i * 8) + 2), (uint8_t) 1);
    //     mmu->write(0xC007 | (uint16_t) ((i * 8) + 3), (uint8_t) 0b01100000);

        // mmu->write(0xC004 + (i * 8) + 4, (uint8_t) 140);
        // mmu->write(0xC005 + (i * 8) + 5, (uint8_t) 80);
        // mmu->write(0xC006 + (i * 8) + 6, (uint8_t) 1);
        // mmu->write(0xC007 + (i * 8) + 7, (uint8_t) 0b01100000); 

    // }

    // ppu->initiateOAMTransfer(0xC0);

    #ifndef DEBUG
    emit ready();
    #endif
}

void Gameboy::run() {
    // while (!cpu->halted && (!checkCycleCount || cycleCount > 0)) {
    while (!mmu->cpu->halted) {
        auto v = mmu->cpu->cycle();
        
        mmu->ppu->cycle(v);
        if (checkCycleCount && (cycleCount > 0)) {
            --cycleCount;
        }

        // if (cpu->cycles % 10000 == 0) {
        //     QTime dieTime= QTime::currentTime().addMSecs(10);
        //     while (QTime::currentTime() < dieTime)
        //     QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        // }
    }
}

std::vector<uint8_t> Gameboy::mooneye() {
    while (!mmu->cpu->halted) {
        auto v = mmu->cpu->cycle();        
        mmu->ppu->cycle(v);
    }
    return {mmu->cpu->r._b, mmu->cpu->r._c, mmu->cpu->r._d, mmu->cpu->r._e, mmu->cpu->r._h, mmu->cpu->r._l};
}


#ifndef DEBUG
void Gameboy::advanceCycles(uint64_t cycles) {
    cycleCount = cycles;
    checkCycleCount = true;
    run();
}

void Gameboy::setBreakpointOn(ADDRESS_ACCESS accessType, uint16_t address) {
    switch (accessType) {
        case ADDRESS_ACCESS::READ:
            cpu->mmu->watchAddress(accessType, address);
            break;
        case ADDRESS_ACCESS::WRITE:
            cpu->mmu->watchAddress(accessType, address);
            break;
        case ADDRESS_ACCESS::PC_AT:
            cpu->watchPC.insert(address);            
            break;
        default:
            break;
    }
}

void Gameboy::removeBreakpointOn(ADDRESS_ACCESS accessType, uint16_t address) {
    std::cout << "Breakpoint on " << (int) address << " Removed!" << std::endl;
}


void Gameboy::updateLocalGUI() {
    connect(cpu, &CPU::accessHaltSignal, this, &Gameboy::accessHalt);
}

void Gameboy::accessHalt(ADDRESS_ACCESS r, uint16_t address) {
    cycleCount = 0;
    std::cout << "Gameboy halted with " << r << " on address " << (int) address << std::endl;
}
#endif
