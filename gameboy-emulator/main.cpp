#include "include/mainwindow.h"

#include <fstream>
#include <iterator>
#include <iostream>
#include <vector>
#include <stdint.h>

#include <QApplication>
#include <QObject>

int main(int argc, char *argv[])
{

    char *rom = nullptr;
    if (argc > 1) {
        rom = argv[1];
    }

    QApplication a(argc, argv);
    MainWindow w(rom);

    // Joypad j = Joypad();

    // QObject::connect(&w, &MainWindow::pressed, &j, &Joypad::receivePress);

    w.show();

    // std::vector<int> cartridge;
    // Gameboy gb = Gameboy(cartridge);
    return a.exec();
}
