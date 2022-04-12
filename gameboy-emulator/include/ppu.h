#ifndef PPU_H
#define PPU_H

#include <QImage>
#include <QGraphicsScene>
#include <QObject>

#include "include/mmu.h"

constexpr uint8_t DISPLAY_W = 160;
constexpr uint8_t DISPLAY_H = 144;

constexpr uint16_t BACKGROUND_N = 256;

enum TILE_MAP_AREA {
    _9800_9BFF,
    _9C00_9FFF
};

enum BG_WINDOW_TILE_AREA {
    _8800_97FF,
    _8000_8FFF
};

enum PPU_MODE {
    _0_HBLANK = 0,
    _1_VBLANK = 1,
    _2_OAM_SEARCH = 2,
    _3_OAM_TRANSFER = 3
};

enum BG_OR_WINDOW {
    BG,
    WINDOW
};

struct OAM_Entry {
    uint8_t y;
    uint8_t x;
    QImage* img;
    uint8_t flags;
};

class PPU: public QObject {

    Q_OBJECT

    public:
        PPU(MMU *mmu, QLabel *displayLabel, QLabel *windowLabel, QLabel *backgroundLabel);
        uint8_t read(uint16_t address);
        void write(uint16_t address, uint8_t value);
        void cycle(uint64_t cycles);
        void initiateOAMTransfer(uint8_t addr_half);

    private:
        MMU *mmu;
        QPixmap *pix;

        QImage *img;        
        
        std::vector<uint8_t> v_ram;

        uint8_t ff40, ff41,
            ff42,   // SCY (Scroll Y)
            ff43,   // SCX (Scroll X)
            ff44,   // LY (LCD Y Coordinate)
            ff45,   // LYC (LY Compare)
            ff47,   // BGP (BG Pallette Data)
            ff48,   // OBP0 (OBJ Palette 0)
            ff49,   // OBP1 (OBJ Palette 1)
            ff4a,   // WY (Window Y Position)
            ff4b;   // WX (Window X Position)

        // 0xFF40 - LCDC
        bool PPU_ENABLED;                       // bit 7
        TILE_MAP_AREA WINDOW_TMA;               // bit 6
        bool WINDOW_ENABLE;                     // bit 5
        BG_WINDOW_TILE_AREA ADDRESSING_MODE;    // bit 4
        TILE_MAP_AREA BACKGROUND_TMA;           // bit 3
        bool STACKED_OBJ;                       // bit 2
        bool OBJ_ENABLED;                       // bit 1
        bool BG_WINDOW_ENABLE_PRIORITY;         // bit 0

        // 0xFF41 - LCDY
        bool LYC_LY_INTERRUPT;                  // bit 6
        bool MODE_2_OAM_STAT_INTERRUPT;         // bit 5
        bool MODE_1_VBLANK_INTERRUPT;           // bit 4
        bool MODE_0_HBLANK_INTERRUPT;           // bit 3
        // LYC=LY FLAG - not stored, as it      // bit 2
        // will be computed when 0xFF41 is read
        PPU_MODE MODE;                          // bit 1

        // make each window operate separately here

        QImage *composite;
        QImage *backgroundImage;
        QImage *windowImage;

        // ***

        QLabel *displayLabel;
        QLabel *backgroundLabel;
        QLabel *windowLabel;
        uint64_t dots;

        void renderLine(uint8_t ly);

        void renderBackWin(BG_OR_WINDOW o, uint8_t ly);
        void renderSprites(uint8_t ly);
        void renderOpaque();

        void generateBackground();
        void generateWindow();

        QImage* generate8(uint16_t address);

        std::vector<QImage*> oam_cache;
        // std::vector<QImage*> bg_cache;
        
        bool needOAMRevalidation; 
        bool needBackgroundRevalidation;
        bool needWindowRevalidation;

        void computeOAM();
};

#endif
