#ifndef PPU_H
#define PPU_H

#include <QImage>
#include <QGraphicsScene>
#include <QObject>

#ifndef DEBUG
#include "include/gui/gui_viewer.h"
#endif

#include "include/other/constants.h"

#include "include/mmu.h"

struct OAM_Entry {
    uint8_t y;
    uint8_t x;
    QImage* img;
    uint8_t flags;
};

#ifdef DEBUG
class PPU {
#else
class PPU: public QObject {
    Q_OBJECT
#endif

    public:
        PPU(MMU *mmu);
        ~PPU() = default;

        uint8_t read(uint16_t address);
        void write(uint16_t address, uint8_t value);
        void cycle(uint64_t cycles);
        void initiateOAMTransfer(uint8_t addr_half);

    #ifndef DEBUG
    signals:
        void updateTile(QImage *img, uint8_t n, PPU_LAYER layer);
    #endif

    private:
        MMU *mmu;

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

        // 0xFF41 - LCDS
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
        void renderSprites(uint8_t ly);
        void cacheImage(int bank, QImage *dst, PPU_LAYER layer);

        QImage* generate8(uint16_t address, uint8_t palette, bool useTransparency = false);
        // std::vector<QImage*> bg_cache;

        std::vector<QImage*> oam_cache;

        bool needOAMRevalidation; 
        bool needBackgroundRevalidation;
        bool needWindowRevalidation;

        void computeOAM();
};

#endif
