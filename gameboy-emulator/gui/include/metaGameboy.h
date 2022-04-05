#ifndef META_GAMEBOY_H
#define META_GAMEBOY_H

#include <QVBoxLayout>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QLabel>

#include "include/gameboy.h"

#include <vector>
#include <stdint.h>

class MetaGameboy: public QVBoxLayout {

    Q_OBJECT

    public:
        MetaGameboy();
        Gameboy *gameboy;

    signals:
        void ready();

    public slots:
        void createGameboy(std::string rom);

    private:
        QLabel *label;
        std::vector<uint8_t> *data; 

        void update();
};

#endif
