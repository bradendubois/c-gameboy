#include "include/other/testing.h"
#include "include/gameboy.h"
#include "include/registers.h"

struct Breakpoint debug;

std::string hexout(int digits, uint16_t value) {
    std::ostringstream ss;
    ss << std::setfill('0') << std::setw(digits) << std::hex << value;
    return "0x" + ss.str();
}

bool _MOONEYE(Gameboy *gameboy)
{
    debug.param = DEBUG_PARAMETER::OPCODE_VALUE;
    debug.value = 0x40;
    debug.time = DEBUG_TIME::BEFORE;
    debug.response = DEBUG_RESPONSE::HALT;

    gameboy->addBreakpoint(debug);
    gameboy->run();

    Registers *r = gameboy->registers();

    return
        r->_b == 3 &&
        r->_c == 5 &&
        r->_d == 8 &&
        r->_e == 13 &&
        r->_h == 21 &&
        r->_l == 34;
}

bool _BLARGG(Gameboy *gameboy)
{
    debug.param = DEBUG_PARAMETER::SERIAL_WRITE;
    debug.time = DEBUG_TIME::BEFORE;
    debug.response = DEBUG_RESPONSE::PRINT;

    gameboy->addBreakpoint(debug);
    gameboy->run();

    return false;
}

bool RUN_SINGLE_TEST(const std::string &rom, const GAMEBOY_MODEL model, const TESTING_FRAMEWORK framework) {
    
    std::cout << rom.substr(rom.rfind("/", rom.rfind("/") - 1)) << " - ";

    Gameboy *gb = new Gameboy();
    gb->initialize(model, rom);    

    bool success;
    
    switch (framework) {
        case TESTING_FRAMEWORK::MOONEYE:
            success = _MOONEYE(gb);
            break;

        case TESTING_FRAMEWORK::BLARGG:
            success = _BLARGG(gb);
            break;

        // __builtin_unreachable();
        default:
            std::cerr << "unknown testing framework for rom " << rom << std::endl;
            return 1;
    }
    
    std::cout << (success ? "success" : "failure") << std::endl;
    return success;
}

std::tuple<int,int> TEST() {
    int fails = 0;
    int totals = 0;
    bool success;

    for (auto [rom, model, framework]: testRoms)
    {
        success = RUN_SINGLE_TEST(rom, model, framework);
        if (!success) {
            fails++;
        }

        totals++;
    }

    return {fails, totals};
}
