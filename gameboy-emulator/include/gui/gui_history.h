#ifndef GUI_HISTORY
#define GUI_HISTORY

#include <stdint.h>
#include <iostream>

#include <QLabel>
#include <QTabWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QAbstractButton>
#include <QPushButton>

#include "include/gui/gui_breakpoints.h"

class GuiHistory: public QWidget {

    Q_OBJECT

    public:
        GuiHistory(QWidget *parent = nullptr);

    private:
        QVBoxLayout *layout;
        QLabel *l;
        QTableWidget *history;

};


#endif
