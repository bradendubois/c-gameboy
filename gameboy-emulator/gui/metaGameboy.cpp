#include "gui/include/metaGameboy.h"
#include "gui/include/metaRegisters.h"

#include <QVBoxLayout>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QUrl>
#include <QLabel>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

MetaGameboy::MetaGameboy(): QVBoxLayout() {


    label = new QLabel;
    update();

    addWidget(label);
}

void MetaGameboy::createGameboy(std::string rom) {

    std::ifstream instream(std::string(rom), std::ios::in | std::ios::binary);
    data = new std::vector<uint8_t>((std::istreambuf_iterator<char>(instream)),       std::istreambuf_iterator<char>());

    gameboy = new Gameboy(data);

    update();
    emit ready();

}

void MetaGameboy::update() {

    if (!gameboy) {
        label->setText(tr("Gameboy not loaded."));
    }

    if (gameboy) {
        label->setText(tr("Gameboy is loaded!"));
    }
}