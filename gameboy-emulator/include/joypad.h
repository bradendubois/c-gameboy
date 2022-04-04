#ifndef JOYPAD_H
#define JOYPAD_H

#include <QEvent>
#include <QKeyEvent>
#include <QObject>

#include <iostream>
#include <stdint.h>

class Joypad : public QObject {

    Q_OBJECT

    public:
        Joypad(): ff00(0x00) {};
        virtual ~Joypad() {};
        uint8_t read();
        void write(uint8_t v);

    public slots:
        void receivePress(QKeyEvent *e);

    private:
        uint8_t ff00;
};

#endif
