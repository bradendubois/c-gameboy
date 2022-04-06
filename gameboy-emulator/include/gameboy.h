#ifndef GAMEBOY_H
#define GAMEBOY_H

#include "cartridge.h"
#include "cpu.h"
#include "mmu.h"

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

    private:
        QLabel *title;

    private slots:
        void updateLocalGUI();

};

#endif
