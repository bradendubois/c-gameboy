#ifndef GUI_DEBUG
#define GUI_DEBUG

#include <stdint.h>
#include <iostream>

#include <QLabel>
#include <QTabWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QAbstractButton>
#include <QPushButton>

class GuiViewer;

#include "include/gui/gui_breakpoints.h"
#include "include/gui/gui_history.h"
#include "include/gui/gui_viewer.h"

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
        CycleButton *b1000000;
};


class GuiDebug: public QVBoxLayout {

    Q_OBJECT;

    public:
        GuiDebug(QWidget *parent = nullptr);
        GuiRegisters *mr;
        GuiControls *gc;

        QTabWidget *tabs;
        GuiHistory *gh;
        GuiBreakpoints *bp;

        GuiViewer *gv;

    // signals:
    //     advanceCycles(uint64_t cycles);

    public slots:
        void updateRegisters(REGISTER r, uint16_t value);


};

#endif
