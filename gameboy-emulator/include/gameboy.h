#ifndef GAMEBOY_H
#define GAMEBOY_H

#include <vector>

#include <QVBoxLayout>
#include <QObject>
#include <QLabel>


#include "include/mmu.h"
#include "include/cartridge.h"
#include "include/cpu.h"
#include "include/gui_debug.h"

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
        void accessHalt(ADDRESS_ACCESS r, uint16_t address);

    private:
        QLabel *title;
        bool checkCycleCount;
        int cycleCount;

    private slots:
        void updateLocalGUI();

};

#endif
