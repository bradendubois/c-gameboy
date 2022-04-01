#include "include/cartridge.h"
#include "include/gameboy.h"
#include "include/mainwindow.h"

#include <fstream>
#include <iterator>
#include <iostream>
#include <vector>
#include <stdint.h>

#include <QApplication>

int main(int argc, char *argv[])
{

    for (int i = 0; i < argc; i++) {
        std::cout << argv[i] << std::endl;
    }

    if (argc == 1) {
        std::cout << "Missing rom!" << std::endl;
        return 0;
    }
    
    std::ifstream instream(argv[1], std::ios::in | std::ios::binary);
    std::vector<uint8_t> data((std::istreambuf_iterator<char>(instream)), std::istreambuf_iterator<char>());

    std::cout << std::hex << (int) data[0x0104] << std::endl;
    std::cout << std::hex << 0xCE << std::endl;

    std::cout << std::hex;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 16; ++j) {
            std::cout << (int) data[0x0104 + ((i * 16) + j)] << " ";
        } std::cout << std::endl;
    }

    std::cout << std::dec;
    for (int i = 0x0134; i <= 0x0143; ++i) {
        std::cout << data[i] << " ";
    } std::cout << std::endl;

    Cartridge cartridge(data);
    std::cout << cartridge.toString() << std::endl;

    Gameboy gb = Gameboy(data);
    gb.run();

    return 0;

    // QApplication a(argc, argv);
    // MainWindow w;
    // w.show();

    // // std::vector<int> cartridge;
    // // Gameboy gb = Gameboy(cartridge);
    // return a.exec();
}
