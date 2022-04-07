#ifndef GUI_BREAKPOINTS_H
#define GUI_BREAKPOINTS_H

#include <stdint.h>
#include <iostream>

#include <QLabel>
#include <QTabWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QAbstractButton>
#include <QPushButton>
#include <QWidget>
#include <QLineEdit>


enum ADDRESS_ACCESS {
    READ,
    WRITE,
    PC_AT
};


class GuiBreakpoints: public QWidget {

    Q_OBJECT

    public:
        GuiBreakpoints(QWidget *parent = nullptr);

    signals:
        void addAccess(ADDRESS_ACCESS type, uint16_t address);

    private slots:
        void addRead();
        void addWrite();
        void addPCAt();

    private:
        QVBoxLayout *layout;
        QLabel *l;
        QTableWidget *table;
        
        QLineEdit *le;
        QPushButton *readButton;
        QPushButton *writeButton;
        QPushButton *pcButton;

        void addTable(ADDRESS_ACCESS, uint16_t v);
};

#endif
