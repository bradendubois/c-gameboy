#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

#include "include/gameboy.h"
#include "include/cpu.h"
#include "include/gui_debug.h"

#include <QVBoxLayout>
#include <QString>

Gameboy::Gameboy(QWidget *parent): QVBoxLayout(parent) {

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
    cpu->run();
}


void Gameboy::advanceCycles(uint64_t cycles) {

    std::cout << "Hearing " << (int) cycles << " coming up!" << std::endl;

}

void Gameboy::setBreakpointOn(ADDRESS_ACCESS accessType, uint16_t address) {

    std::cout << "Breakpoint on " << (int) address << " marked!" << std::endl;

}

void Gameboy::removeBreakpointOn(ADDRESS_ACCESS accessType, uint16_t address) {
    std::cout << "Breakpoint on " << (int) address << " Removed!" << std::endl;

}


void Gameboy::updateLocalGUI() {

    title->setText(QString::fromStdString("Got a game! " + cartridge->title()));

}