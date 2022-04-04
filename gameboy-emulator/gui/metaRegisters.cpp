#include <stdint.h>

#include <QTableWidget>
#include <QTableWidgetItem>

#include "gui/include/metaRegisters.h"

MetaRegisters::MetaRegisters(): QTableWidget() {

    setRowCount(5);
    setColumnCount(8);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    setItem(0, 1, new QTableWidgetItem(tr("???")));
    int r = 5, c;
    while (r--) {
        c = 8;
        while (c--) {
            if (c != 0 && c != 3) {
                setItem(r, c, new QTableWidgetItem(tr("???")));
            }
        }
    }

    setItem(0, 0, new QTableWidgetItem(tr("A")));
    setItem(0, 4, new QTableWidgetItem(tr("H")));
    setItem(1, 0, new QTableWidgetItem(tr("B")));
    setItem(1, 4, new QTableWidgetItem(tr("C")));
    setItem(2, 0, new QTableWidgetItem(tr("D")));
    setItem(2, 4, new QTableWidgetItem(tr("E")));
    setItem(3, 0, new QTableWidgetItem(tr("H")));
    setItem(3, 4, new QTableWidgetItem(tr("L")));
    setItem(4, 0, new QTableWidgetItem(tr("PC")));
    setItem(4, 4, new QTableWidgetItem(tr("SP")));

    setHorizontalHeaderLabels({});
    setVerticalHeader(nullptr);

}
