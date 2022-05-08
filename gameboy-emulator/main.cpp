#ifdef DEBUG
#include "include/other/testing.h"
#else
#include "include/mainwindow.h"
#endif

#include "include/gameboy.h"

#include <fstream>
#include <iterator>
#include <iostream>
#include <stdint.h>
#include <tuple>
#include <vector>

#include <QApplication>
#include <QObject>



int main(int argc, char *argv[])
{
    #ifdef DEBUG
        const auto [fails, total] = TEST();
        return fails;
    #else
        char *rom = nullptr;
        if (argc > 1) {
            rom = argv[1];
        }

        QApplication a(argc, argv);
        MainWindow w(rom);

        w.show();

        return a.exec();
    #endif
}
