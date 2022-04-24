#include "../include/sound.h"

void Sound::write(uint16_t address, uint8_t value) {
    switch (address) {
        case 0xFF10:
            break;
        case 0xFF11:
            break;
        case 0xFF12:
            break;
        case 0xFF13:
            break;
        case 0xFF14:
            break;
        case 0xFF16:
            break;
        case 0xFF17:
            break;
        case 0xFF18:
            break;
        case 0xFF19:
            break;
        case 0xFF1A:
            break;
        case 0xFF1B:
            break;
        case 0xFF1C:
            break;
        case 0xFF1D:
            break;
        case 0xFF1E:
            break;

        case 0xFF20:
            break;
        case 0xFF21:
            break;
        case 0xFF22:
            break;
        case 0xFF23:
            break;
        case 0xFF24:
            break;
        case 0xFF25:
            break;
        case 0xFF26:
            break;
        
        case 0xFF30 ... 0xFF3F:
            break;
        
        default:
            std::cerr << "Impossible Sound address (" << (int) address << ")" << std::endl;
            break;
    }

    (void) value;
}

uint8_t Sound::read(uint16_t address) {
    switch (address) {
        case 0xFF10:
            break;
        case 0xFF11:
            break;
        case 0xFF12:
            break;
        case 0xFF13:
            break;
        case 0xFF14:
            break;
        case 0xFF16:
            break;
        case 0xFF17:
            break;
        case 0xFF18:
            break;
        case 0xFF19:
            break;
        case 0xFF1A:
            break;
        case 0xFF1B:
            break;
        case 0xFF1C:
            break;
        case 0xFF1D:
            break;
        case 0xFF1E:
            break;

        case 0xFF20:
            break;
        case 0xFF21:
            break;
        case 0xFF22:
            break;
        case 0xFF23:
            break;
        case 0xFF24:
            break;
        case 0xFF25:
            break;
        case 0xFF26:
            break;
        
        case 0xFF30 ... 0xFF3F:
            break;
        
        default:
            std::cerr << "Impossible Sound address (" << (int) address << ")" << std::endl;
            break;
    }

    return 0;
}
