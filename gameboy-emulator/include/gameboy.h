#ifndef GAMEBOY_H
#define GAMEBOY_H

#include <iostream>
#include <set>
#include <vector>

#include <QGraphicsView>
#include <QVBoxLayout>
#include <QObject>
#include <QLabel>
#include <QImage>
#include <QGraphicsScene>
#include <QThread>

class CPU;
class MMU;
class PPU;
struct Breakpoint;

#ifdef DEBUG
#include "include/other/testing.h"
#else
#include "include/gui/gui_debug.h"
#endif

#include "include/mmu.h"
#include "include/ppu.h"
#include "include/registers.h"

#include "include/other/constants.h"

#ifdef DEBUG
class Gameboy {
#else
class Gameboy: public QVBoxLayout {
    Q_OBJECT
#endif

    public:
        Gameboy(
            #ifndef DEBUG
            QWidget *parent = nullptr
            #endif
        );
        ~Gameboy();

        void initialize(const GAMEBOY_MODEL MODEL, const std::string &romPath);
        void run();

        void addBreakpoint(Breakpoint b);        

        Registers* registers();

        CPU *cpu;
        MMU *mmu;


    #ifndef DEBUG
    signals:
        void ready();

        void signal_updateRegister(REGISTER r, uint16_t value);
        void signal_updateTile(QImage *img, uint8_t n, PPU_LAYER layer);

    public slots:
        void advanceCycles(uint64_t cycles);
        void setBreakpointOn(ADDRESS_ACCESS accessType, uint16_t address);
        void removeBreakpointOn(ADDRESS_ACCESS accessType, uint16_t address);
        void accessHalt(ADDRESS_ACCESS r, uint16_t address);

        void slot_updateRegister(REGISTER r, uint16_t value);
        void slot_updateTile(QImage *img, uint8_t n, PPU_LAYER layer);
    #endif

    private:
        friend class MMU;
        friend class PPU;

        bool checkCycleCount;
        int cycleCount;
        GAMEBOY_MODEL model;

    #ifndef DEBUG
    private slots:
        void updateLocalGUI();
    #endif


};

#endif
