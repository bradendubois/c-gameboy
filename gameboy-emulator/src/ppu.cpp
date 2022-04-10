#include <QGraphicsScene>
#include <QGraphicsView>
#include <QImage>

#include "include/ppu.h"

PPU::PPU(MMU *mmu, QLabel *displayLabel): mmu(mmu), pix(new QPixmap), img(new QImage(160, 144, QImage::Format_RGBA64)), v_ram(std::vector<uint8_t>(0x2000, 0)) {
    mmu->ppu = this;

    QImage *img = new QImage(160, 144, QImage::Format::Format_RGB32);
    
    img->fill(Qt::white);

    displayLabel->setPixmap(QPixmap::fromImage(*img));
    
    img->setPixel(10, 10, qRgb(128, 255, 255));
    img->setPixel(10, 11, qRgb(255, 128, 255));
    img->setPixel(10, 12, qRgb(255, 255, 128));
    img->setPixel(10, 13, qRgb(180, 60, 120));

    displayLabel->setPixmap(QPixmap::fromImage(*img));

    const std::vector<uint8_t> t{0xFF, 0x00, 0x7E, 0xFF, 0x85, 0x81, 0x89, 0x83, 0x93, 0x85, 0xA5, 0x8B, 0xC9, 0x97, 0x7E, 0xFF};

    for (int i = 0; i < t.size(); i += 2) {
        uint8_t low = t[i];
        uint8_t high = t[i+1];
        for (int j = 7; j >= 0; j--) {
            uint8_t h = (j - 1 >= 0 ? (high >> (j-1)) : (high));
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
            std::cerr << "Impossible PPU write address " << (int) address << std::endl;
            break;
    }
}
