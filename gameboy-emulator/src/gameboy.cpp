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

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QString>
#include <QImage>
#include <QPixmap>

Gameboy::Gameboy(QWidget *parent): QVBoxLayout(parent), displayLabel(new QLabel), windowLabel(new QLabel), backgroundLabel(new QLabel), checkCycleCount(false), cycleCount(0) {
    addWidget(displayLabel);
    addWidget(backgroundLabel);
    addWidget(windowLabel);
    connect(this, &Gameboy::ready, this, &Gameboy::updateLocalGUI);
}

void Gameboy::initialize(std::string romPath) {

    // Add some cleanup here if swapping games

    std::ifstream instream(std::string(romPath), std::ios::in | std::ios::binary);
    std::vector<uint8_t> *data = new std::vector<uint8_t>((std::istreambuf_iterator<char>(instream)), std::istreambuf_iterator<char>());
    
    cartridge = new Cartridge(data);
    mmu = new MMU(this, cartridge);
    cpu = new CPU(mmu);
    // display->fill(Qt::GlobalColor::blue);
    ppu = new PPU(mmu, displayLabel, windowLabel, backgroundLabel);

    std::vector<uint8_t> a{0xFF, 0x00, 0x7E, 0xFF, 0x85, 0x81, 0x89, 0x83, 0x93, 0x85, 0xA5, 0x8B, 0xC9, 0x97, 0x7E, 0xFF};
    std::vector<uint8_t> b{0x7C, 0x7C, 0x00, 0xC6, 0xC6, 0x00, 0x00, 0xFE, 0xC6, 0xC6, 0x00, 0xC6, 0xC6, 0x00, 0x00, 0x00};
    std::vector<uint8_t> *c = &a;

    bool flip = false;
    for (int i = 0; i < 256; i++) {
        std::cout << std::hex << "Starting write at " << (int) 0x8800 + (i * 16) << std::dec << std::endl;
        if (i % 32 == 0) { c = (c == &a ? &b : &a); }
        for (int k = 0; k < 16; ++k) {
            mmu->write(0x8800 + (i * 16) + k, c->at(k));
        }
        c = (c == &a ? &b : &a);
    }


    for (int i = 0; i < 16; i++) {
        if (i % 32 == 0) { c = (c == &a ? &b : &a); }
        // std::cout << std::hex << "Starting write at " << (int) 0x8000 + (i * 16) << std::dec << std::endl;
        for (int k = 0; k < 16; ++k) {
            
            mmu->write(0x8000 + (i * 16) + k, c->at(k));
        }
        c = (c == &a ? &b : &a);
    }
    // ppu->updateBackground();

    mmu->write(0xC000, (uint8_t) 45);
    mmu->write(0xC001, (uint8_t) 155);
    mmu->write(0xC002, (uint8_t) 1);
    mmu->write(0xC003, (uint8_t) 0b00000000);

    mmu->write(0xC004, (uint8_t) 140);
    mmu->write(0xC005, (uint8_t) 80);
    mmu->write(0xC006, (uint8_t) 1);
    mmu->write(0xC007, (uint8_t) 0b01100000);

    ppu->initiateOAMTransfer(0xC0);
    // ppu->updateSprites();

    ppu->cycle(70224);
    std::cout << "1" << std::endl;
    ppu->cycle(70224);
    std::cout << "2" << std::endl;

    emit ready();
}

void Gameboy::run() {
    while (!checkCycleCount || cycleCount > 0) {
        std::cout << (int) cycleCount << std::endl;
        auto v = cpu->cycle();
        ppu->cycle(v);   // TODO - conversion to keep things synced
        if (checkCycleCount && (cycleCount > 0)) {
            --cycleCount;
        }
    }
}


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

    // title->setText(QString::fromStdString("Got a game! " + cartridge->title()));
    connect(cpu, &CPU::accessHaltSignal, this, &Gameboy::accessHalt);

}

void Gameboy::accessHalt(ADDRESS_ACCESS r, uint16_t address) {
    cycleCount = 0;
    std::cout << "Gameboy halted with " << r << " on address " << (int) address << std::endl;
}