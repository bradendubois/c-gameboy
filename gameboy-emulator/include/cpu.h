#ifndef CPU_H
#define CPU_H

#include <stdint.h>

#include "mmu.h"
#include "registers.h"

#include <vector>

class CPU {


    public:
        CPU(std::vector<int> & cartridge): mmu(MMU(cartridge)), r(Registers()), cb(false), t(0) {};
        MMU mmu;
        Registers r;

    private:

        bool cb;
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
        void  a_add(uint8_t v);
        void  a_sub(uint8_t v);

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

        uint8_t pop_byte();
        uint16_t pop_word();
        void push(uint8_t v);
        void push(uint16_t v);

        void rst(uint8_t v);
        void ret();

        uint16_t add_16_immediate(uint8_t a, uint8_t b);
        void set_ime();
        void unset_ime();
};

#endif
