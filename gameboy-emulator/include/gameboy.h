#ifndef GAMEBOY_H
#define GAMEBOY_H

#include <vector>

#include <QGraphicsView>
#include <QVBoxLayout>
#include <QObject>
#include <QLabel>
#include <QImage>
#include <QGraphicsScene>

class CPU;
class PPU;

#include "include/cpu.h"
#include "include/mmu.h"
#include "include/cartridge.h"
#include "include/ppu.h"
#include "include/gui_debug.h"

class Gameboy: public QVBoxLayout {

    Q_OBJECT

    public:
        Gameboy(QWidget *parent = nullptr);

        MMU *mmu;
        CPU *cpu;
        PPU *ppu;
    
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
        QLabel *displayLabel;
        bool checkCycleCount;
        int cycleCount;

    private slots:
        void updateLocalGUI();

};

#endif
