#ifndef META_REGISTERS_H
#define META_REGISTERS_H

#include <QTableWidget>
#include <QLabel>

#include "../include/registers.h"

class MetaRegisters: public QTableWidget {

    public:
        MetaRegisters();
        ~MetaRegisters() {};

    public slots:
        void updateRegisters(Registers &r);

};

#endif
