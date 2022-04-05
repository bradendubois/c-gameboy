#ifndef META_REGISTERS_H
#define META_REGISTERS_H

#include <QTableWidget>
#include <QLabel>

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


class MetaRegisters: public QTableWidget {

    public:
        MetaRegisters();
        ~MetaRegisters() {};

    public slots:
        void updateRegisters(REGISTER_POSITION r, uint16_t value);

    private:
        void updateRegister(int row, int col, uint16_t value);
};

#endif
