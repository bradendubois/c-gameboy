#include <QGraphicsScene>
#include <QGraphicsView>
#include <QImage>

#ifndef DEBUG
#include "include/gui/gui_viewer.h"
#endif

#include "include/ppu.h"

#include <math.h>
#include <time.h>

#ifdef DEBUG
PPU::PPU(MMU *mmu): mmu(mmu)
#else
PPU::PPU(MMU *mmu): QObject(mmu), mmu(mmu)
#endif
{
    #ifndef DEBUG
    displayLabel = new QLabel;
    backgroundLabel = new QLabel;
    windowLabel = new QLabel;

    Gameboy *gb = static_cast<Gameboy*>(parent()->parent());
    gb->addWidget(displayLabel);
    gb->addWidget(backgroundLabel);
    gb->addWidget(windowLabel);
    #endif

    v_ram = std::vector<uint8_t>(0x2000, 0);
    oam_cache = std::vector<QImage*>(40, nullptr);
    dots = 0;
    
    needOAMRevalidation = true;
    needBackgroundRevalidation = true;
    needWindowRevalidation = true;

    #ifndef DEBUG
    composite = new QImage(160, 144, QImage::Format::Format_ARGB32);
    backgroundImage = new QImage(256, 256, QImage::Format::Format_ARGB32);
    windowImage = new QImage(256, 256, QImage::Format::Format_ARGB32);

    composite->fill(Qt::white);
    backgroundImage->fill(Qt::white);
    windowImage->fill(Qt::white);

    // Only drawing background while testing
    displayLabel->setPixmap(QPixmap::fromImage(*composite));
    backgroundLabel->setPixmap(QPixmap::fromImage(*backgroundImage));
    windowLabel->setPixmap(QPixmap::fromImage(*backgroundImage));

    composite->setPixel(10, 10, qRgb(128, 255, 255));
    composite->setPixel(10, 11, qRgb(255, 128, 255));
    composite->setPixel(10, 12, qRgb(255, 255, 128));
    composite->setPixel(10, 13, qRgb(180, 60, 120));
    #endif

    // displayLabel->setPixmap(QPixmap::fromImage(*composite).scaled(displayLabel->size(), Qt::KeepAspectRatio));
    // backgroundLabel->setPixmap(QPixmap::fromImage(*backgroundImage).scaled(backgroundLabel->size(), Qt::KeepAspectRatio));

    // const std::vector<uint8_t> t{0xFF, 0x00, 0x7E, 0xFF, 0x85, 0x81, 0x89, 0x83, 0x93, 0x85, 0xA5, 0x8B, 0xC9, 0x97, 0x7E, 0xFF};

    // for (unsigned char i = 0; i < t.size(); i += 2) {
    //     uint8_t low = t[i];
    //     uint8_t high = t[i+1];
    //     for (int j = 7; j >= 0; j--) {
    //         std::cout << (int) ((((high >> j) << 1) & 0x02) | ((low >> j) & 0x01));
    //     } std::cout << std::endl;
    // }
}


uint8_t PPU::read(uint16_t address) {
    switch (address) {
        case 0x8000 ... 0x9FFF:
            return v_ram[address - 0x8000];
        case 0xFF40:
            return ff40;
        case 0xFF41: {
            uint8_t r = ff41;
            if (ff44 == ff45) r |= 0x04;
            if (MODE == _3_OAM_TRANSFER) r |= 0x03;
            if (MODE == _2_OAM_SEARCH) r |= 0x02;
            if (MODE == _1_VBLANK) r |= 0x01;
            return r;
        }
        case 0xFF42:
            return ff42;
        case 0xFF43:
            return ff43;
        case 0xFF44:
            return ff44;
        case 0xFF45:
            return ff45;
        case 0xFF46:
            return 0xFF;
        case 0xFF47:
            return ff47;
        case 0xFF48:
            return ff48;
        case 0xFF49:
            return ff49;
        case 0xFF4A:
            return ff4a;
        case 0xFF4B:
            return ff4b;
        case 0xFF4D:
            return 0xFF; // CGB

        default:
            // std::cerr << "Impossible PPU read address " << std::hex << (int) address << std::dec << std::endl;
            return 0;
    };
}


void PPU::write(uint16_t address, uint8_t value) {
    switch (address) {
        case 0x8000 ... 0x9FFF:
            // std::cout << std::hex << (int) (address - 0x8000) << " " << (int) value << std::dec << std::endl;
            v_ram[address - 0x8000] = value;
            break;
        case 0xFF40:
            ff40 = value;
            PPU_ENABLED = (value & 0x80) != 0;
            WINDOW_TMA = ((value & 0x40) == 0 ? _9800_9BFF : _9C00_9FFF);
            WINDOW_ENABLE = (value & 0x20) != 0;
            ADDRESSING_MODE = ((value & 0x10) == 0 ? _8800_97FF : _8000_8FFF);
            BACKGROUND_TMA = ((value & 0x08) == 0 ? _9800_9BFF : _9C00_9FFF);
            STACKED_OBJ = (value & 0x04) != 0;
            OBJ_ENABLED = (value & 0x02) != 0;
            BG_WINDOW_ENABLE_PRIORITY = (value & 0x01) != 0;
            break;
        case 0xFF41:
            ff41 = value & ~0x04;
            LYC_LY_INTERRUPT = (value & 0x40) != 0;
            MODE_2_OAM_STAT_INTERRUPT = (value & 0x20) != 0;
            MODE_1_VBLANK_INTERRUPT = (value & 0x10) != 0;
            MODE_0_HBLANK_INTERRUPT = (value & 0x08) != 0;
            break;
        case 0xFF42:
            ff42 = value;
            break;
        case 0xFF43:
            ff43 = value;
            break;
        case 0xFF44:
            // ff44 = value;
            break;
        case 0xFF45:
            ff45 = value;
            break;
        case 0xFF46:
            initiateOAMTransfer(value);
            break;
        case 0xFF47:
            ff47 = value;
            break;
        case 0xFF48:
            ff48 = value;
            break;
        case 0xFF49:
            ff49 = value;
            break;
        case 0xFF4A:
            ff4a = value;
            break;
        case 0xFF4B:
            ff4b = value;
            break;
        
        // CGB
        case 0xFF4D:
            break;
        case 0xFF4F:
            break;

        default:
            std::cerr << "Impossible PPU write address " << std::hex << (int) address << std::dec << std::endl;
            break;
    }
}



void PPU::cycle(uint64_t cycles) {
    // std::cout << "PPU " << std::dec << (int) ff44 << std::endl;
    

    if (!PPU_ENABLED) {
        return;
    }

    auto x = (int) cycles;
    while (x > 0) {
        
        auto cur = (x > 80 ? 80 : x);
        dots += cur;
        // std::cout << "modeclock " << (int) dots << std::endl;
        x -= cur;

        // end of scanline
        if (dots >= 456) {
            dots %= 456;
            ff44++;

            // reset to top
            if (ff44 >= 154) {
                ff44 %= 154;
            }
            
            if (LYC_LY_INTERRUPT && (ff44 == ff45)) {
                mmu->ff0f |= 0x02;
            }

            if (ff44 >= 144 && MODE != PPU_MODE::_1_VBLANK) {
                if (PPU_ENABLED) {
                    // std::cout << "RENDER" << std::endl;
                    // displayLabel->setPixmap(QPixmap::fromImage(*composite).scaled(displayLabel->size(), Qt::KeepAspectRatio));
                    // backgroundLabel->setPixmap(QPixmap::fromImage(*backgroundImage).scaled(backgroundLabel->size(), Qt::KeepAspectRatio));
                    // windowLabel->setPixmap(QPixmap::fromImage(*windowImage).scaled(windowLabel->size(), Qt::KeepAspectRatio));

                    #ifndef DEBUG
                    displayLabel->setPixmap(QPixmap::fromImage(*composite).scaled(256, 256));
                    backgroundLabel->setPixmap(QPixmap::fromImage(*backgroundImage));
                    windowLabel->setPixmap(QPixmap::fromImage(*windowImage));
                    #endif
                }
                MODE = PPU_MODE::_1_VBLANK;
                mmu->ff0f |= 0x01;
            }
            if (MODE_1_VBLANK_INTERRUPT) {
                mmu->ff0f |= 0x02;       
            }
        }

        if (ff44 < DISPLAY_H) {
            switch (dots) {
                case 0 ... 80: {
                    if (MODE != PPU_MODE::_2_OAM_SEARCH) {
                        #ifndef DEBUG
                        if (needOAMRevalidation) { computeOAM(); }
                        #endif
                        MODE = PPU_MODE::_2_OAM_SEARCH;

                    }
                    if (MODE_2_OAM_STAT_INTERRUPT) {
                        mmu->ff0f |= 0x02;
                    }
                    break;
                }
                case 81 ... 252: {
                    if (MODE != PPU_MODE::_3_OAM_TRANSFER) {
                        if (ff44 < DISPLAY_H) {
                            #ifndef DEBUG
                            renderLine(ff44);
                            #endif
                        }
                        MODE = PPU_MODE::_3_OAM_TRANSFER;
                    }
                    break;
                }
                case 253 ... 456: {
                    if (MODE != PPU_MODE::_0_HBLANK) {
                        MODE = PPU_MODE::_0_HBLANK;
                    }
                    if (MODE_0_HBLANK_INTERRUPT) {
                       mmu->ff0f |= 0x02;       
                    }
                    break;
                }
                default:
                    break;
            }
        } else {
            // if (MODE != PPU_MODE::_1_VBLANK) {
            //     if (PPU_ENABLED) {
            //         // std::cout << "RENDER" << std::endl;
            //         // displayLabel->setPixmap(QPixmap::fromImage(*composite).scaled(displayLabel->size(), Qt::KeepAspectRatio));
            //         // backgroundLabel->setPixmap(QPixmap::fromImage(*backgroundImage).scaled(backgroundLabel->size(), Qt::KeepAspectRatio));
            //         // windowLabel->setPixmap(QPixmap::fromImage(*windowImage).scaled(windowLabel->size(), Qt::KeepAspectRatio));

            //         displayLabel->setPixmap(QPixmap::fromImage(*composite));
            //         backgroundLabel->setPixmap(QPixmap::fromImage(*backgroundImage));
            //         windowLabel->setPixmap(QPixmap::fromImage(*windowImage));
            //     }
            //     MODE = PPU_MODE::_1_VBLANK;
            //     mmu->ff0f |= 0x01;
            // }
            // if (MODE_1_VBLANK_INTERRUPT) {
            //     mmu->ff0f |= 0x02;       
            // }
        }
    }
} 

void PPU::renderLine(uint8_t ly) {

    bool *revalidate;
    uint8_t y, x, x_bias;
    int bank;
    QImage *img;
    PPU_LAYER layer;

    // only perform a scanline for either the window OR background
    if (WINDOW_ENABLE)
    {
        revalidate = &needWindowRevalidation;
        y = ff4a;
        x = ff4b;
        x_bias = 8;
        bank = (WINDOW_TMA == _9800_9BFF ? 0 : 1);
        img = windowImage;
        layer = PPU_LAYER::L_WINDOW;
        uint8_t r = y + ly;
        // for (uint8_t c = 0; c < DISPLAY_W; ++c) {
        //     if (x_bias > c) continue;
        //     windowImage->setPixel(c - x_bias, ly, img->pixel(x + c, r));
        //     // backgroundLabel->setPixmap(QPixmap::fromImage(*backgroundImage));
            // backgroundLabel->setPixmap(QPixmap::fromImage(*backgroundImage).scaled(backgroundLabel->size(), Qt::KeepAspectRatio));
        // }
    }
    else
    {
        revalidate = &needBackgroundRevalidation;
        y = ff42;
        x = ff43;
        x_bias = 0;
        bank = (BACKGROUND_TMA == _9800_9BFF ? 0 : 1);
        img = backgroundImage;
        layer = PPU_LAYER::L_BACKGROUND;

    
        uint8_t r = y + ly;
        for (uint8_t c = 0; c < DISPLAY_W; ++c) {
            backgroundImage->setPixel(c - x_bias, ly, img->pixel(x + c, r));
            // backgroundLabel->setPixmap(QPixmap::fromImage(*backgroundImage));
            // backgroundLabel->setPixmap(QPixmap::fromImage(*backgroundImage).scaled(backgroundLabel->size(), Qt::KeepAspectRatio));
        }
    }

    if (*revalidate) {
        cacheImage(bank, img, layer);
        *revalidate = false;
    }

    uint8_t row = y + ly;
    // for (int c = 0; c < DISPLAY_W; ++c) {
    //     if (c - x_bias < 0) continue;
    //     composite->setPixel(c - x_bias, ly, img->pixel(x + c, row));
    // }

    if (OBJ_ENABLED) {
        renderSprites(ly);
    }
    // } else {
    //     std::cout << "NOT ENABLED?" << std::endl;
    // };

    // displayLabel->setPixmap(QPixmap::fromImage(*composite));
    // displayLabel->setPixmap(QPixmap::fromImage(*composite).scaled(displayLabel->size(), Qt::KeepAspectRatio));

}


void PPU::cacheImage(int bank, QImage *dst, PPU_LAYER layer) {

    int base = (ADDRESSING_MODE == BG_WINDOW_TILE_AREA::_8800_97FF ? 0x1000 : 0x0000);
    bool sign = ADDRESSING_MODE == BG_WINDOW_TILE_AREA::_8800_97FF;

    QImage *result;
    for (uint8_t row = 0; row < 32; ++row) {
        for (uint8_t col = 0; col < 32; ++col) {
            int tileNumber = (int) v_ram[(bank == 0 ? 0x1800 : 0x1C00) + ((row * 32) + col)];
            int tile_base = base + ((sign ? ((int8_t) tileNumber) : tileNumber) * 16);
            
            result = generate8(tile_base, ff47);

            for (uint8_t i = 0; i < 8; i++) {
                for (uint8_t j = 0; j < 8; j++) {
                    dst->setPixel(col * 8 + i, row * 8 + j, result->pixel(i, j));
                }
            }

            #ifndef DEBUG
            emit updateTile(result, (row * 32) + col, layer);
            #endif

            delete result;
        }
    }

    // backgroundLabel->setPixmap(QPixmap::fromImage(*backgroundImage));
    // backgroundLabel->setPixmap(QPixmap::fromImage(*backgroundImage).scaled(backgroundLabel->size(), Qt::KeepAspectRatio));
}


inline constexpr QRgb transparent = qRgba(0, 0, 0, 0);
inline constexpr QRgb white = qRgb(255, 255, 255);
inline constexpr QRgb lightGray = qRgb(192, 192, 192);
inline constexpr QRgb darkGray = qRgb(96, 96, 96);
inline constexpr QRgb black = qRgb(0, 0, 0);

// TODO - Cache these when the palettes change
QRgb rgb(uint8_t v, bool transparency) {
    switch (v) {
        case 0b00:
            return (transparency ? transparent : white);
        case 0b01:
            return lightGray;
        case 0b10:
            return darkGray;
        case 0b11:
            return black;
        default:
            std::cerr << "Impossible pixel value" << std::endl;
    }
}

QImage* PPU::generate8(uint16_t address, uint8_t palette, bool t) {

    QImage *result = new QImage(8, 8, QImage::Format::Format_ARGB32);

    QRgb r[]{rgb(palette & 0x03, t), rgb((palette & 0x0C) >> 2, t), rgb((palette & 0x30) >> 4, t), rgb((palette & 0xC0) >> 6, t)};

    for (int i = 0; i < 8; ++i) {
        uint8_t low = v_ram[address + (i * 2)]; 
        uint8_t high = v_ram[address + (i * 2) + 1];

        for (int j = 7; j >= 0; j--) {
            auto c = (((high >> j) << 1) & 0x02) | ((low >> j) & 0x01);
            result->setPixel(7 - j, i, r[c]);
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
    uint8_t flags;
    for (auto i = 0; i < 40; ++i) {
        flags = mmu->read(0xFE00 | (i * 4) + 3);
        oam_cache[i] = generate8(mmu->read(0xFE00 | (i * 4) + 2) * 16, ((flags & 0x10) == 0 ? ff48 : ff49), true);

        #ifndef DEBUG
        emit updateTile(oam_cache[i], i, PPU_LAYER::L_SPRITE);
        #endif
    }

    needOAMRevalidation = false;
}
