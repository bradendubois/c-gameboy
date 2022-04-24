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
        ~Gameboy();

        void initialize(std::string romPath);
        std::vector<uint8_t> mooneye();

        MMU *mmu;

    #ifndef DEBUG
    signals:
        void ready();

        void signal_updateRegister(REGISTER_POSITION r, uint16_t value);
        void signal_updateTile(QImage *img, uint8_t n, PPU_LAYER layer);

    public slots:
        void advanceCycles(uint64_t cycles);
        void setBreakpointOn(ADDRESS_ACCESS accessType, uint16_t address);
        void removeBreakpointOn(ADDRESS_ACCESS accessType, uint16_t address);
        void accessHalt(ADDRESS_ACCESS r, uint16_t address);

        void slot_updateRegister(REGISTER_POSITION r, uint16_t value);
        void slot_updateTile(QImage *img, uint8_t n, PPU_LAYER layer);
    #endif

    protected:
        void run();

    private:
        friend class MMU;
        friend class PPU;

        bool checkCycleCount;
        int cycleCount;

    #ifndef DEBUG
    private slots:
        void updateLocalGUI();
    #endif


};

#endif
