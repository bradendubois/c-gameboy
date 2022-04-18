#include <iostream>
#include <stdint.h>

#include <QAction>
#include <QActionGroup>
#include <QApplication>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLatin1Char>
#include <QMetaObject>
#include <QObject>
#include <QPushButton>
#include <QSpacerItem>
#include <QStatusBar>
#include <QString>
#include <QTabWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>

#include "include/gui_debug.h"
#include "include/gui_history.h"
#include "include/gui_breakpoints.h"

GuiRegisters::GuiRegisters(QWidget *parent): QTableWidget(parent) {

    setRowCount(5);
    setColumnCount(8);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setFocusPolicy(Qt::NoFocus);
    setSelectionMode(QAbstractItemView::NoSelection);
    setFixedWidth(9 * 40 + 245);
    setFixedHeight(9 * 20);
    setItem(0, 1, new QTableWidgetItem(tr("???")));
    
    setHorizontalHeaderLabels({"R", "d", "0x", "0b", "R", "d", "0x", "0b"});
    horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    
    verticalHeader()->hide();

    QTableWidgetItem *item;
    int r = 5, c;
    while (r--) {
        c = 8;
        while (c--) {
            if (c != 0 && c != 4) {
                item = new QTableWidgetItem(tr("???"));
                setItem(r, c, item);
                item->setTextAlignment(Qt::AlignCenter);
            }
        }
    }

    setItem(0, 0, new QTableWidgetItem(tr("A")));
    setItem(0, 4, new QTableWidgetItem(tr("F")));
    setItem(1, 0, new QTableWidgetItem(tr("B")));
    setItem(1, 4, new QTableWidgetItem(tr("C")));
    setItem(2, 0, new QTableWidgetItem(tr("D")));
    setItem(2, 4, new QTableWidgetItem(tr("E")));
    setItem(3, 0, new QTableWidgetItem(tr("H")));
    setItem(3, 4, new QTableWidgetItem(tr("L")));
    setItem(4, 0, new QTableWidgetItem(tr("PC")));
    setItem(4, 4, new QTableWidgetItem(tr("SP")));

    setColumnWidth(0, 40);
    setColumnWidth(1, 80);
    setColumnWidth(2, 60);
    setColumnWidth(3, 120);
    setColumnWidth(4, 40);
    setColumnWidth(5, 80);
    setColumnWidth(6, 60);
    setColumnWidth(7, 120);

}

void GuiRegisters::updateRegister(int row, int col, uint16_t value) {
    item(row, col + 1)->setText(tr("%1").arg(value, 0, 10));
    item(row, col + 2)->setText(tr("%1").arg(value, (row == 4 ? 4 : 2), 16, QLatin1Char('0')));
    item(row, col + 3)->setText(tr("%1").arg(value, 8, 2, QLatin1Char('0')));
}

CycleButton *advanceFactory(uint64_t v) {
    CycleButton *b = new CycleButton(v);
    b->setText(QObject::tr("+%1").arg(v));
    QObject::connect(b, &CycleButton::released, b, &CycleButton::click);
    return b;
}

GuiControls::GuiControls(QWidget *parent): QHBoxLayout(parent),
    b1(advanceFactory(1)), b5(advanceFactory(5)),
    b100(advanceFactory(100)), b1000(advanceFactory(1000)), b1000000(advanceFactory(10000)) {

    connect(b1, &CycleButton::advance, this, &GuiControls::advanceCycles);
    connect(b5, &CycleButton::advance, this, &GuiControls::advanceCycles);
    connect(b100, &CycleButton::advance, this, &GuiControls::advanceCycles);
    connect(b1000, &CycleButton::advance, this, &GuiControls::advanceCycles);
    connect(b1000000, &CycleButton::advance, this, &GuiControls::advanceCycles);

    addWidget(b1);
    addWidget(b5);
    addWidget(b100);
    addWidget(b1000);
    addWidget(b1000000);
}


void GuiDebug::updateRegisters(REGISTER_POSITION r, uint16_t value) {
    switch (r) {
        case R_A:
            mr->updateRegister(0, 0, value);
            break;
        case R_F:
            mr->updateRegister(0, 4, value);
            break;
        case R_B:
            mr->updateRegister(1, 0, value);
            break;
        case R_C:
            mr->updateRegister(1, 4, value);
            break;
        case R_D:
            mr->updateRegister(2, 0, value);
            break;
        case R_E:
            mr->updateRegister(2, 4, value);
            break;
        case R_H:
            mr->updateRegister(3, 0, value);
            break;
        case R_L:
            mr->updateRegister(3, 4, value);
            break;
        case R_PC:
            mr->updateRegister(4, 0, value);
            break;
        case R_SP:
            mr->updateRegister(4, 4, value);
            break;
        
    }
}

GuiDebug::GuiDebug(QWidget *parent): QVBoxLayout(parent), mr(new GuiRegisters), gc(new GuiControls), tabs(new QTabWidget), gh(new GuiHistory), bp(new GuiBreakpoints) {

    addWidget(mr);
    addLayout(gc);
    
    gv = new GuiViewer;

    tabs->addTab(gh, "History");
    tabs->addTab(bp, "Breakpoints");
    addWidget(tabs);

    addWidget(gv);

    addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Fixed, QSizePolicy::Expanding));
}
