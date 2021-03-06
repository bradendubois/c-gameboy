#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <vector>

#include <QObject>


class MMU;

#ifndef DEBUG
#include "include/gui/gui_debug.h"
#include "include/gui/gui_breakpoints.h"
#include "include/mainwindow.h"
#endif

#include "include/other/testing.h"

#include "include/mmu.h"
#include "include/registers.h"


enum IME { Enabled, Disabled, OneCycleDelay };

enum ACCESS_HALTED {
    TRIGGERED,
    NOT_TRIGGERED
};

enum ISR {
    INACTIVE,
    NOPS,
    PUSH,
    JMP
};

#ifdef DEBUG
class CPU {
#else
class CPU: public QObject {
    Q_OBJECT
#endif

    public:
        CPU();
        ~CPU() = default;
        uint64_t cycle();
        void update();
        uint64_t cycles;

        void initialize(GAMEBOY_MODEL model, uint16_t checksum);
        void debug(Breakpoint b);

    #ifndef DEBUG
    signals:
        void updateRegister(REGISTER r, uint16_t value);
        void accessHaltSignal(ADDRESS_ACCESS r, uint16_t address);

    public slots:
        void accessHaltSlot(ADDRESS_ACCESS r, uint16_t address);
    #endif

    private:
        friend class MainWindow;
        friend class Gameboy;

        bool halted;

        Registers r;
        MMU *mmu;
        __uint128_t t;

        __uint128_t opcode(uint8_t opcode);
        __uint128_t opcode_cb(uint8_t opcode);

        void halt();
        void stop();

        void jr(int8_t v);
        void jp(uint16_t v);
        uint8_t inc(uint8_t v);
        uint16_t inc(uint16_t v);
        uint8_t dec(uint8_t v);
        uint16_t dec(uint16_t v);
        
        void hl_add(uint16_t v);
        uint8_t alu_sub(uint8_t v, bool carry);

        uint8_t rl(uint8_t v);
        uint8_t rr(uint8_t v);

        void adc(uint8_t v);
        void sbc(uint8_t v);
        void a_and(uint8_t v);
        void a_xor(uint8_t v);
        void a_or(uint8_t v);
        void a_cp(uint8_t v);

        void call(uint16_t v);
        void ret();

        uint16_t pop();
        void push(uint16_t v);

        void rst(uint8_t v);

        void set_ime();
        void unset_ime();

        IME ime;

        uint8_t rlc(uint8_t v);
        uint8_t rrc(uint8_t v);

        void alu_add(uint8_t v);
        void alu_add(uint16_t v);
        void add_16_sp(uint8_t v);
        void load_16_sp_hl(uint8_t v);

        uint8_t byte();
        uint16_t word();

        uint8_t read(uint16_t address);
        void write(uint16_t address, uint8_t value);
        void write(uint16_t address, uint16_t value);
    
        uint8_t sla(uint8_t v);
        uint8_t sra(uint8_t v);

        uint8_t swap(uint8_t v);
        uint8_t srl(uint8_t v);

        void bit(uint8_t bit, uint8_t v);
        uint8_t res(uint8_t bit, uint8_t v);
        uint8_t set(uint8_t bit, uint8_t v);

        std::set<uint16_t> watchPC;
        ACCESS_HALTED hit;

        ISR isr;
        uint8_t handler;

        std::set<uint8_t> opcodeWatch;
};

#endif
