#include "include/mainwindow.h"
#include "include/gameboy.h"

#include <vector>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    std::vector<int> cartridge;
    Gameboy gb = Gameboy(cartridge);
    return a.exec();
}
