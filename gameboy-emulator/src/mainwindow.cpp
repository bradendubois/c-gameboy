#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

#include "include/mainwindow.h"

#include <QFileDialog>
#include <vector>
#include <stdint.h>

#include <QMetaObject>
#include <QLabel>
#include <QApplication>
#include <QObject>
#include <QAction>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStatusBar>
#include <QActionGroup>

#include "gui/include/metaRegisters.h"
#include "gui/include/metaGameboy.h"

MainWindow::MainWindow(char *rom) {
    
    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    QHBoxLayout *layout = new QHBoxLayout;

    setWindowTitle(tr("Gameboy Emulator"));
    setMinimumSize(160, 160);
    resize(640, 480);

    mr = new MetaRegisters;
    gb = new MetaGameboy;

    connect(this, &MainWindow::selectedRom, gb, &MetaGameboy::createGameboy);
    connect(gb, &MetaGameboy::ready, this, &MainWindow::gameboyReady);

    createMenuBar();
    createDetailsPanel();


    layout->addLayout(r);
    layout->addLayout(new QVBoxLayout);
    layout->addLayout(gb);

    widget->setLayout(layout);

    if (rom != nullptr) {
        emit selectedRom(std::string(rom));
    }
}


void MainWindow::keyPressEvent(QKeyEvent *e) {
    emit pressed(e);
}

// TODO - What the frick, QT?
void MainWindow::keyReleaseEvent(QKeyEvent *e) {
    emit pressed(e);
}



void MainWindow::setFile() {
    QString rom = QFileDialog::getOpenFileName(this, tr("Open Image"), "~", tr("ROM Files (*.rom *gb"));
    emit selectedRom(rom.toStdString());
}


void MainWindow::createMenuBar() {

    menuBar = new QMenuBar();

    fileMenu = menuBar->addMenu(tr("&File"));

    selectRom = fileMenu->addAction(tr("&Select ROM"));
    connect(selectRom, &QAction::triggered, [=]() {
        setFile();
    });

    exitAction = fileMenu->addAction(tr("Close"));
    connect(exitAction, &QAction::triggered, [=]() {
        // TODO - Revisit once save states are implemented
        exit(0);
    });

    menuBar->addMenu(fileMenu);

    setMenuBar(menuBar);
}




// void MainWindow::setRom(std::string romName) {

//     std::ifstream instream(std::string(romName), std::ios::in | std::ios::binary);
//     cartridge = new std::vector<uint8_t>((std::istreambuf_iterator<char>(instream)),       std::istreambuf_iterator<char>());
//     emit 

// }


void MainWindow::createDetailsPanel() {

    r = new QVBoxLayout;
    r->addWidget(mr);
    r->addWidget(new MetaCartridge);


}


void MainWindow::createPlayerGroup() {

    r = new QVBoxLayout;

    QWidget *topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QLabel *t = new QLabel(tr("Some text"));
    t->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    t->setAlignment(Qt::AlignCenter);

    QWidget *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    r->setContentsMargins(5, 5, 5, 5);
    r->addWidget(topFiller);
    r->addWidget(t);
    r->addWidget(bottomFiller);

}

void MainWindow::gameboyReady() {
    connect(&gb->gameboy->cpu, &CPU::updateRegister, mr, &MetaRegisters::updateRegisters);
    gb->gameboy->cpu.update();
}
