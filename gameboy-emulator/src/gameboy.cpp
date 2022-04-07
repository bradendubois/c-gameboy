#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

class MMU;

#include "include/gameboy.h"
#include "include/cpu.h"
#include "include/gui_debug.h"
#include "include/mmu.h"

#include <QVBoxLayout>
#include <QString>

Gameboy::Gameboy(QWidget *parent): QVBoxLayout(parent), checkCycleCount(false), cycleCount(0) {

    title = new QLabel;
    title->setText(tr("Gameboy Stub"));

    addWidget(title);

    connect(this, &Gameboy::ready, this, &Gameboy::updateLocalGUI);

}

void Gameboy::initialize(std::string romPath) {

    std::ifstream instream(std::string(romPath), std::ios::in | std::ios::binary);
    std::vector<uint8_t> *data = new std::vector<uint8_t>((std::istreambuf_iterator<char>(instream)), std::istreambuf_iterator<char>());
    
    cartridge = new Cartridge(data);
    cpu = new CPU(this, cartridge);

    emit ready();
}

void Gameboy::run() {
    while (!checkCycleCount || cycleCount > 0) {
        std::cout << (int) cycleCount << std::endl;
        cpu->cycle();
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

    title->setText(QString::fromStdString("Got a game! " + cartridge->title()));
    connect(cpu, &CPU::accessHaltSignal, this, &Gameboy::accessHalt);

}

void Gameboy::accessHalt(ADDRESS_ACCESS r, uint16_t address) {
    cycleCount = 0;
    std::cout << "Gameboy halted with " << r << " on address " << (int) address << std::endl;
}