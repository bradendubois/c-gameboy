#include <stdint.h>
#include <iostream>

#include <QHBoxLayout>
#include <QLabel>
#include <QTabWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QAbstractButton>
#include <QPushButton>
#include <QLineEdit>

#include "include/gui/gui_history.h"


GuiHistory::GuiHistory(QWidget *parent): QWidget(parent), layout(new QVBoxLayout), l(new QLabel), history(new QTableWidget) {

    l->setText(tr("History"));
    layout->addWidget(l);
    layout->addWidget(history);
 
    setLayout(layout);
}

