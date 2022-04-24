#include <fstream>
#include <iostream>
#include <iterator>
#include <stdint.h>
#include <vector>

#include <QFileDialog>
#include <QMetaObject>
#include <QLabel>
#include <QApplication>
#include <QObject>
#include <QAction>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStatusBar>
#include <QActionGroup>

#include "include/gameboy.h"
#include "include/gui_debug.h"
#include "include/mainwindow.h"
#include "include/gui_viewer.h"
#ifndef DEBUG
MainWindow::MainWindow(char *rom): widget(new QWidget), layout(new QHBoxLayout) {
    
    setCentralWidget(widget);

    gd = new GuiDebug(this);
    gb = new Gameboy(this);

    setWindowTitle(tr("Gameboy Emulator"));
    setMinimumSize(600, 400);
    resize(800, 600);

    connect(this, &MainWindow::selectedRom, gb, &Gameboy::initialize);
    connect(gb, &Gameboy::ready, this, &MainWindow::gameboyReady);

    connect(gd->gc, &GuiControls::advanceCycles, gb, &Gameboy::advanceCycles);
    connect(gd->bp, &GuiBreakpoints::addAccess, gb, &Gameboy::setBreakpointOn);

    createMenuBar();

    layout->addLayout(gd);
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
    QString rom = QFileDialog::getOpenFileName(this, tr("Open Image"), "~", tr("ROM Files (*rom *gb"));
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



void MainWindow::gameboyReady() {
    connect(gb, &Gameboy::signal_updateRegister, gd, &GuiDebug::updateRegisters);
    connect(gb, &Gameboy::signal_updateTile, gd->gv, &GuiViewer::receiveImage);
}

#endif
