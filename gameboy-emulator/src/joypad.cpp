#include "../include/joypad.h"

#include <QKeyEvent>
#include <QObject>

uint8_t Joypad::read() {
    return ff00;
}

void Joypad::write(uint8_t v) {
    ff00 = (v & 0x30) | (ff00 & 0x0F);
}

void Joypad::receivePress(QKeyEvent *e) {
    
    uint8_t b = 255;

    if ((ff00 & 0x20) == 0) {
        switch (e->key()) {
            case Qt::Key_H:     // Start
                b = 3;
                break;
            case Qt::Key_F:     // Select
                b = 2;
                break;
            case Qt::Key_J:     // B
                b = 1;
                break;
            case Qt::Key_I:     // A
                b = 0;
                break;
        }
    }

    if ((ff00 & 0x10) == 0) {
        switch (e->key()) {
            case Qt::Key_S:     // Down
                b = 3;
                break;
            case Qt::Key_W:     // Up
                b = 2;
                break;
            case Qt::Key_A:     // Left
                b = 1;
                break;
            case Qt::Key_D:     // Right
                b = 0;
                break;
        }
    }

    if (b == 255) return;

    switch (e->type()) {
        case QEvent::Type::KeyRelease:
            ff00 |= 1 << b;
            break;
        case QEvent::Type::KeyPress:
            ff00 |= 0b00001111; // TODO This is because the keyreleaseevent doesn't fire
            ff00 &= ~(1 << b);
            break;
        default:
            break;
    };

    std::cout << (int) ff00 << std::endl;
}
