#include <QGraphicsScene>
#include <QGraphicsView>
#include <QImage>

#include "include/ppu.h"
#include <math.h>
#include <time.h>

PPU::PPU(MMU *mmu, QLabel *displayLabel, QLabel *windowLabel, QLabel *backgroundLabel): mmu(mmu), pix(new QPixmap), displayLabel(displayLabel), windowLabel(windowLabel), backgroundLabel(backgroundLabel), img(new QImage(160, 144, QImage::Format_RGBA64)), v_ram(std::vector<uint8_t>(0x2000, 0)), ff40(0), ff41(0), ff42(0), ff43(0), ff44(0), ff45(0), ff47(0), ff48(0), ff49(0), ff4a(0), ff4b(0), dots(0), oam_cache(std::vector<QImage*>(40, nullptr)), needOAMRevalidation(true), needBackgroundRevalidation(true), needWindowRevalidation(true) {
    mmu->ppu = this;

    composite = new QImage(160, 144, QImage::Format::Format_ARGB32);
    backgroundImage = new QImage(256, 256, QImage::Format::Format_ARGB32);
    windowImage = new QImage(256, 256, QImage::Format::Format_ARGB32);

    composite->fill(Qt::white);
    backgroundImage->fill(Qt::white);

    // Only drawing background while testing
    displayLabel->setPixmap(QPixmap::fromImage(*composite));
    backgroundLabel->setPixmap(QPixmap::fromImage(*backgroundImage));

    composite->setPixel(10, 10, qRgb(128, 255, 255));
    composite->setPixel(10, 11, qRgb(255, 128, 255));
    composite->setPixel(10, 12, qRgb(255, 255, 128));
    composite->setPixel(10, 13, qRgb(180, 60, 120));

    displayLabel->setPixmap(QPixmap::fromImage(*composite).scaled(displayLabel->size(), Qt::KeepAspectRatio));
    backgroundLabel->setPixmap(QPixmap::fromImage(*backgroundImage).scaled(backgroundLabel->size(), Qt::KeepAspectRatio));

    const std::vector<uint8_t> t{0xFF, 0x00, 0x7E, 0xFF, 0x85, 0x81, 0x89, 0x83, 0x93, 0x85, 0xA5, 0x8B, 0xC9, 0x97, 0x7E, 0xFF};

    for (unsigned char i = 0; i < t.size(); i += 2) {
        uint8_t low = t[i];
        uint8_t high = t[i+1];
        for (int j = 7; j >= 0; j--) {
            std::cout << (int) ((((high >> j) << 1) & 0x02) | ((low >> j) & 0x01));
        } std::cout << std::endl;
    }
}


uint8_t PPU::read(uint16_t address) {
    switch (address) {
        case 0x8000 ... 0x9FFF:
            return v_ram[address - 0x8000];
        default:
            std::cerr << "Impossible PPU read address " << (int) address << std::endl;
            return 0;
    };
}


void PPU::write(uint16_t address, uint8_t value) {
    switch (address) {
        case 0x8000 ... 0x9FFF:
            v_ram[address - 0x8000] = value;
            break;
        default:
            std::cerr << "Impossible PPU write address " << std::hex << (int) address << std::dec << std::endl;
            break;
    }
}



void PPU::cycle(uint64_t cycles) {
    auto x = (int) cycles;
    while (x-- > 0) {
        dots++;
        if (ff44 < DISPLAY_H) {
            switch (dots) {
                case 0 ... 80: {
                    if (MODE != PPU_MODE::_2_OAM_SEARCH) {
                        if (needOAMRevalidation) { computeOAM(); }
                        MODE = PPU_MODE::_2_OAM_SEARCH;
                    }
                    break;
                }
                case 81 ... 252: {
                    if (MODE != PPU_MODE::_3_OAM_TRANSFER) {
                        if (ff44 < DISPLAY_H) {
                            renderLine(ff44);
                        }
                        MODE = PPU_MODE::_3_OAM_TRANSFER;
                    }
                    break;
                }
                case 253 ... 456: {
                    if (MODE != PPU_MODE::_0_HBLANK) {
                        MODE = PPU_MODE::_0_HBLANK;
                    }
                    break;
                }
                default:
                    break;
            }
        } else {
            if (MODE != PPU_MODE::_1_VBLANK) {
                displayLabel->setPixmap(QPixmap::fromImage(*composite));
                MODE = PPU_MODE::_1_VBLANK;
            }
        }

        // end of scanline
        if (dots >= 456) {
            dots %= 456;
            ff44++;
        }

        // reset to top
        if (ff44 >= 154) {
            ff44 %= 154;
        }
    }
} 

void PPU::renderLine(uint8_t ly) {
    // if (WINDOW_ENABLE)
        // renderBackWin(BG_OR_WINDOW::WINDOW, ly);
    // else
    renderBackWin(BG_OR_WINDOW::BG, ly);

    renderSprites(ly);
    
    // displayLabel->setPixmap(QPixmap::fromImage(*composite));
    // displayLabel->setPixmap(QPixmap::fromImage(*composite).scaled(displayLabel->size(), Qt::KeepAspectRatio));
    
}

void PPU::renderBackWin(BG_OR_WINDOW o, uint8_t ly) {

    (void) o;

    if (needBackgroundRevalidation) { std::cout << "Generating window" << std::endl; generateWindow(); }

    uint8_t row = ff42 + ly;
    for (uint8_t c = 0; c < DISPLAY_W; ++c) {
        composite->setPixel(c, ly, backgroundImage->pixel(ff43 + c, row));
    }
    // TILE_MAP_AREA tileMapArea = (o == BG_OR_WINDOW::WINDOW ? WINDOW_TMA : BACKGROUND_TMA);    
    // int base = (ADDRESSING_MODE == BG_WINDOW_TILE_AREA::_8800_97FF ? 0x1000 : 0x0000)
    // bool sign = ADDRESSING_MODE == BG_WINDOW_TILE_AREA::_8800_97FF;

    // for (i = 0; i < SCREEN_W; ++i) {
    //     uint8_t viewportY = (o == BG_OR_WINDOW::WINDOW ? ff4a : ff42) + x;
    //     uint8_t viewportX = (o == BG_OR_WINDOW::WINDOW ? ff4b : ff43) + x;

    //     uint8_t ty = (viewportY >> 3) & 0x1F;
    //     uint8_t tx = (viewportX >> 3) & 0x1F;
    //     int tile = (ty * 32) + tx;
    //     int tile_base = base + ((sign ? (iint8_t) tile : tile) * 32);
    //     std::vector<uint8_t> tileData{v_ram[base], v_ram[base+1], v_ram[base+2], v_ram[base+3]};

    // }
}


void PPU::generateWindow() {

    ADDRESSING_MODE = BG_WINDOW_TILE_AREA::_8800_97FF;

    int tileMapArea = (BACKGROUND_TMA == TILE_MAP_AREA::_9800_9BFF ? 0 : 1);
    int base = (ADDRESSING_MODE == BG_WINDOW_TILE_AREA::_8800_97FF ? 0x1000 : 0x0000);
    bool sign = ADDRESSING_MODE == BG_WINDOW_TILE_AREA::_8800_97FF;

    for (uint8_t row = 0; row < 32; ++row) {
        for (uint8_t col = 0; col < 32; ++col) {
            int tileNumber = (row * 32) + col;
            int tile_base = base + ((sign ? ((int8_t) tileNumber) : tileNumber) * 16);
            // std::cout << "Tile base: " << std::hex << tile_base << std::dec << std::endl;
            QImage *result = generate8(tile_base);

            for (uint8_t i = 0; i < 8; i++) {
                for (uint8_t j = 0; j < 8; j++) {
                    backgroundImage->setPixel(col * 8 + i, row * 8 + j, result->pixel(i, j));
                    backgroundImage->setPixel(i, j, result->pixel(i, j));
                }
            }

            delete result;
        }
    }

    // backgroundLabel->setPixmap(QPixmap::fromImage(*backgroundImage));
    // backgroundLabel->setPixmap(QPixmap::fromImage(*backgroundImage).scaled(backgroundLabel->size(), Qt::KeepAspectRatio));
    needBackgroundRevalidation = false;
}


QImage* PPU::generate8(uint16_t address) {

    QImage *result = new QImage(8, 8, QImage::Format::Format_ARGB32);

    for (int i = 0; i < 8; ++i) {
        uint8_t low = v_ram[address + (i * 2)]; 
        uint8_t high = v_ram[address + (i * 2) + 1];

        for (int j = 7; j >= 0; j--) {
            auto c = (((high >> j) << 1) & 0x02) | ((low >> j) & 0x01);
            switch (c) {
                case 0:
                    result->setPixel(7 - j, i, qRgb(0, 0, 0));
                    break;
                case 1:
                    result->setPixel(7 - j, i, qRgb(80, 80, 80));
                    break;
                case 2:
                    result->setPixel(7 - j, i, qRgb(160, 160, 160));
                    break;
                case 3:
                    result->setPixel(7 - j, i, qRgb(256, 256, 256));
                    break;
                default:
                    std::cerr << "Impossible pixel value" << std::endl;
            }
        }
    }

    return result;

}


void PPU::initiateOAMTransfer(uint8_t addr_half) {
    uint16_t base = ((uint16_t) addr_half) << 8;
    for (auto i = 0; i <= 0x9F; ++i) {
        mmu->write(0xFE00 | i, mmu->read(base | i));
        // std::cout << "Writing " << std::hex << (int) mmu->read(base | i) << " from " << (int) (base | i) <<  " to " << (int) (0xFE00 | i) <<  std::dec << std::endl;
    }

    needOAMRevalidation = true;
}


void PPU::renderSprites(uint8_t ly) {
    if (needOAMRevalidation) computeOAM();

    std::vector<int> show;
    for (int j = 0; j < 40; ++j) {
        int y = mmu->read(0xFE00 | (j * 4));
        if (ly >= y && ly < y + 8) {
            show.push_back(j);
            if (show.size() == 10) {
                break;
            }
        }
    }

    // Move the flipping to the precomputing
    for (auto entry : show) {
        QImage sprite = *oam_cache[entry];
        uint8_t flags = mmu->read(0xFE00 | (entry * 4) + 3);
        if ((flags & 0x40) != 0) { sprite = sprite.mirrored(false, true); }
        if ((flags & 0x20) != 0) { sprite = sprite.mirrored(true, false); }

        uint8_t spritex = mmu->read(0xFE00 | (entry * 4) + 1);
        uint8_t spritey = mmu->read(0xFE00 | (entry * 4));

        for (int j = 0; j < 8; ++j) {
            if (spritex + j >= DISPLAY_W) continue;

            // Make separate sprite overlay
            // std::cout << (int) spritex + j << " " << (int) ly << " " << j << " " << (int) ly - spritey << std::endl;  
            composite->setPixel(spritex + j, ly, sprite.pixel(j, ly - spritey));
        }
    }
}

void PPU::computeOAM() {
    for (int i = 0; i < 40; ++i) {
        if (oam_cache.at(i) != nullptr) {
            delete oam_cache[i]; 
        }
    }

    QImage *cur;
    for (auto i = 0; i < 40; ++i) {
        oam_cache[i] = generate8(mmu->read(0xFE00 | (i * 4) + 2) * 16);
    }

    needOAMRevalidation = false;
}
