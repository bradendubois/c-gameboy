#ifndef GAMEBOY_H
#define GAMEBOY_H

#include <vector>
#include <iostream>

#include <QGraphicsView>
#include <QVBoxLayout>
#include <QObject>
#include <QLabel>
#include <QImage>
#include <QGraphicsScene>
#include <QThread>

class CPU;
class PPU;
class Timer;

#include "include/cpu.h"
#include "include/mmu.h"
#include "include/cartridge.h"
#include "include/ppu.h"
#include "include/gui_debug.h"
#include "include/timer.h"

#ifdef DEBUG
class Gameboy {
#else
class Gameboy: public QVBoxLayout {
    Q_OBJECT
#endif

    public:
        #ifndef DEBUG
        Gameboy(QWidget *parent = nullptr);
        #endif
        Gameboy();
        ~Gameboy() { delete mmu; };

        void initialize(std::string romPath);
        std::vector<uint8_t> mooneye();

        MMU *mmu;

    #ifndef DEBUG
    signals:
        void ready();

    public slots:
        void advanceCycles(uint64_t cycles);
        void setBreakpointOn(ADDRESS_ACCESS accessType, uint16_t address);
        void removeBreakpointOn(ADDRESS_ACCESS accessType, uint16_t address);
        void accessHalt(ADDRESS_ACCESS r, uint16_t address);
    #endif

    protected:
        void run();

    private:
        #ifndef DEBUG
        QLabel *displayLabel;
        QLabel *backgroundLabel;
        QLabel *windowLabel;
        #endif

        bool checkCycleCount;
        int cycleCount;

    #ifndef DEBUG
    private slots:
        void updateLocalGUI();
    #endif


};

#endif
