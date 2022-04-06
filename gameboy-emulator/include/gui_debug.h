#ifndef GUI_DEBUG
#define GUI_DEBUG

#include <stdint.h>
#include <iostream>

#include <QLabel>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QAbstractButton>
#include <QPushButton>

enum REGISTER_POSITION {
    R_A,
    R_F,
    R_B,
    R_C,
    R_D,
    R_E,
    R_H,
    R_L,
    R_SP,
    R_PC
};


class CycleButton: public QPushButton {

    Q_OBJECT

    public:
        CycleButton(uint64_t cycles, QWidget *parent = nullptr): QPushButton(parent), v(cycles) {};
    signals:
        void advance(uint64_t v);
    public slots:
        void click() {
            emit advance(v);
        }
    private:
        uint64_t v;
};


class GuiRegisters: public QTableWidget {

    Q_OBJECT;

    public:
        GuiRegisters(QWidget *parent = nullptr);
        ~GuiRegisters() {};
        void updateRegister(int row, int col, uint16_t value);

};


class GuiControls: public QHBoxLayout {

    Q_OBJECT;

    public:
        GuiControls(QWidget *parent = nullptr);
    
    signals:
        void advanceCycles(uint64_t cycles);

    private:
        CycleButton *b1;
        CycleButton *b5;
        CycleButton *b100;
        CycleButton *b1000;
};


class GuiDebug: public QVBoxLayout {

    Q_OBJECT;

    public:
        GuiDebug(QWidget *parent = nullptr);
        GuiRegisters *mr;
        GuiControls *gc;

    // signals:
    //     advanceCycles(uint64_t cycles);

    public slots:
        void updateRegisters(REGISTER_POSITION r, uint16_t value);


};

#endif
