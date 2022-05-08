
#include <stdint.h>
#include <iostream>

#include <QHeaderView>
#include <QIntValidator>
#include <QLabel>
#include <QTabWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QAbstractButton>
#include <QPushButton>
#include <QWidget>

#include "include/gui/gui_breakpoints.h"

GuiBreakpoints::GuiBreakpoints(QWidget *parent): QWidget(parent), layout(new QVBoxLayout), l(new QLabel), table(new QTableWidget(0, 3, this)), le(new QLineEdit), readButton(new QPushButton(tr("on Read"))), writeButton(new QPushButton(tr("on Write"))), pcButton(new QPushButton(tr("on PC at"))) {

    l->setText(tr("Add breakpoint to halt on address read / write"));
    layout->addWidget(l);
    QHBoxLayout *hb = new QHBoxLayout;
    le->setValidator(new QIntValidator(0, 0xFFFF, this));
    hb->addWidget(le);
    
    connect(readButton, &QPushButton::released, this, &GuiBreakpoints::addRead);
    connect(writeButton, &QPushButton::released, this, &GuiBreakpoints::addWrite);
    connect(pcButton, &QPushButton::released, this, &GuiBreakpoints::addPCAt);

    hb->addWidget(readButton);
    hb->addWidget(writeButton);
    hb->addWidget(pcButton);
    
    layout->addLayout(hb);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    table->verticalHeader()->hide();
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setFocusPolicy(Qt::NoFocus);
    table->setSelectionMode(QAbstractItemView::NoSelection);
    table->setHorizontalHeaderLabels({"Reason", "Address (dec)", "Address (hex)"});
    table->setColumnWidth(0, 200);
    table->setColumnWidth(1, 100);
    table->setColumnWidth(2, 100);
    layout->addWidget(table);

    setLayout(layout);

}

void GuiBreakpoints::addRead() {
    if (le->text().size() > 0) {
        emit addAccess(ADDRESS_ACCESS::READ, le->text().toInt());
        addTable(ADDRESS_ACCESS::READ, le->text().toInt());
        le->setText("");
    }
}

void GuiBreakpoints::addWrite() {
    if (le->text().size() > 0) {
        emit addAccess(ADDRESS_ACCESS::WRITE, le->text().toInt());
        addTable(ADDRESS_ACCESS::WRITE, le->text().toInt());
        le->setText("");
    }
}

void GuiBreakpoints::addPCAt() {
    if (le->text().size() > 0) {
        emit addAccess(ADDRESS_ACCESS::PC_AT, le->text().toInt());
        addTable(ADDRESS_ACCESS::PC_AT, le->text().toInt());
        le->setText("");
    }
}

void GuiBreakpoints::addTable(ADDRESS_ACCESS r, uint16_t v) {
    QTableWidgetItem *newItem = new QTableWidgetItem;
    switch (r) {
        case ADDRESS_ACCESS::READ:
            newItem->setText(tr("Memory Read"));
            break;
        case ADDRESS_ACCESS::WRITE:
            newItem->setText(tr("Memory Write"));
            break;
        case ADDRESS_ACCESS::PC_AT:
            newItem->setText(tr("Program Counter At"));
            break;
        default:
            delete newItem;
            return;
    };
    table->insertRow(table->rowCount());
    int i = table->rowCount() - 1;
    table->setItem(i, 0, newItem);
    table->setItem(i, 1, new QTableWidgetItem(tr("%1").arg(v, 0, 10)));
    table->setItem(i, 2, new QTableWidgetItem(tr("%1").arg(v, 4, 16, QLatin1Char('0'))));
}
