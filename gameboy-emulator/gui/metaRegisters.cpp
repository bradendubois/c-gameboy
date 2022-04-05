#include <stdint.h>
#include <iostream>

#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QLatin1Char>

#include "gui/include/metaRegisters.h"

MetaRegisters::MetaRegisters(): QTableWidget() {

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

void MetaRegisters::updateRegister(int row, int col, uint16_t value) {
    item(row, col + 1)->setText(tr("%1").arg(value, 0, 10));
    item(row, col + 2)->setText(tr("%1").arg(value, (row == 4 ? 4 : 2), 16, QLatin1Char('0')));
    item(row, col + 3)->setText(tr("%1").arg(value, 8, 2, QLatin1Char('0')));
}

void MetaRegisters::updateRegisters(REGISTER_POSITION r, uint16_t value) {
    switch (r) {
        case R_A:
            updateRegister(0, 0, value);
            break;
        case R_F:
            updateRegister(0, 4, value);
            break;
        case R_B:
            updateRegister(1, 0, value);
            break;
        case R_C:
            updateRegister(1, 4, value);
            break;
        case R_D:
            updateRegister(2, 0, value);
            break;
        case R_E:
            updateRegister(2, 4, value);
            break;
        case R_H:
            updateRegister(3, 0, value);
            break;
        case R_L:
            updateRegister(3, 4, value);
            break;
        case R_SP:
            updateRegister(4, 0, value);
            break;
        case R_PC:
            updateRegister(4, 4, value);
            break;
        
    }
}
