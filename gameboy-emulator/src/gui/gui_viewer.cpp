#include "include/gui/gui_viewer.h"

#include <QTableWidget>
#include <stdint.h>

PPUViewer::PPUViewer(QTabWidget *parent, uint8_t rows, uint8_t cols): QTableWidget(parent) {

    setRowCount(rows);
    setColumnCount(cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            setItem(i, j, new QTableWidgetItem(""));
        }
    }

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setFocusPolicy(Qt::NoFocus);
    setSelectionMode(QAbstractItemView::NoSelection);
    // setFixedWidth(300);
    // setFixedHeight(300);
    
    verticalHeader()->hide();
    horizontalHeader()->hide();

    for (int i = 0; i < cols; ++i) {
        setColumnWidth(i, 25);
    }
}

void PPUViewer::receiveImage(QImage *img, uint8_t n) {
    item(n / columnCount(), n % columnCount())->setData(Qt::DecorationRole, QPixmap::fromImage(*img).scaled(20, 20));
}

GuiViewer::GuiViewer(QWidget *parent): QTabWidget(parent) {

    sprites = new PPUViewer(this, 2, 20);
    window = new PPUViewer(this, 16, 16);
    background = new PPUViewer(this, 16, 16);

    addTab(sprites, "Sprites");
    addTab(window, "Window");
    addTab(background, "Background");
    // addWidget(tabs);

}

void GuiViewer::receiveImage(QImage *img, uint8_t n, PPU_LAYER layer) {
    switch (layer) {
        case L_SPRITE:
            sprites->receiveImage(img, n);
            break;
        case L_WINDOW:
            window->receiveImage(img, n);
            break;
        case L_BACKGROUND:
            background->receiveImage(img, n);
            break;
        default:
            std::cerr << "Impossible PPU Layer" << std::endl;
    }
}