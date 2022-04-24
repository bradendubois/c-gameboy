#ifndef JOYPAD_H
#define JOYPAD_H

#include <QEvent>
#include <QKeyEvent>
#include <QObject>

class MMU;

#include <iostream>
#include <stdint.h>

#include "include/mmu.h"


#ifdef DEBUG
class Joypad {
#else
class Joypad : public QObject {
    Q_OBJECT
#endif

    public:
        Joypad(MMU *mmu): ff00(0x00), mmu(mmu) {};
        ~Joypad() = default;
        uint8_t read();
        void write(uint8_t v);

    #ifndef DEBUG
    public slots:
        void receivePress(QKeyEvent *e);
    #endif

    private:
        uint8_t ff00;
        MMU *mmu;
};

#endif
