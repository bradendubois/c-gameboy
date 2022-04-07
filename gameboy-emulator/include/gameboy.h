#ifndef GAMEBOY_H
#define GAMEBOY_H

#include "cartridge.h"
#include "cpu.h"
#include "mmu.h"
#include "include/gui_debug.h"
#include <vector>

#include <QVBoxLayout>
#include <QObject>
#include <QLabel>

class CPU;

class Gameboy: public QVBoxLayout {

    Q_OBJECT

    public:
        Gameboy(QWidget *parent = nullptr);

        CPU *cpu;
        Cartridge *cartridge;

        void initialize(std::string romPath);
        void run();

    signals:
        void ready();

    public slots:
        void advanceCycles(uint64_t cycles);
        void setBreakpointOn(ADDRESS_ACCESS accessType, uint16_t address);
        void removeBreakpointOn(ADDRESS_ACCESS accessType, uint16_t address);

    private:
        QLabel *title;

    private slots:
        void updateLocalGUI();

};

#endif
