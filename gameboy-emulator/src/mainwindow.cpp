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

MainWindow::MainWindow() {
    
    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    QHBoxLayout *layout = new QHBoxLayout;

    // createCartridgeGroup();
    // createPlayerGroup();

    // mc = new MetaCartridge;
    // layout->addLayout(mc);


    setWindowTitle(tr("Menus"));
    setMinimumSize(160, 160);
    resize(480, 320);

    createMenuBar();

    createDetailsPanel();
    layout->addLayout(r);

    widget->setLayout(layout);

    // setLayout(layout);

    // QWidget * wdg = new QWidget(this);
    // QVBoxLayout *vlay = new QVBoxLayout(wdg);
    
    // QPushButton *btn1 = new QPushButton("btn1");
    // vlay->addWidget(btn1);

    // QPushButton *btn2 = new QPushButton("btn2");
    // vlay->addWidget(btn2);
    
    // QPushButton *btn3 = new QPushButton("btn3");
    // vlay->addWidget(btn3);
    // wdg->setLayout(vlay);
    
    // setCentralWidget(wdg);
    
    // connect(btn1, SIGNAL(clicked()), this, SLOT(setFile()));
    // QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "/home", tr("Image Files (*.png, *.jpg, *.bmp)"));

    // std::ifstream input(fileName.toStdString(), std::ios::binary );

    // copies all data into buffer
    // std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});
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
    emit setRom(rom.toStdString());
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



void MainWindow::newFile() {

}

void MainWindow::setRom(std::string romName) {

    std::ifstream instream(std::string(romName), std::ios::in | std::ios::binary);
    cartridge = new std::vector<uint8_t>((std::istreambuf_iterator<char>(instream)),       std::istreambuf_iterator<char>());

    gameboy = new Gameboy(cartridge);


}

void MainWindow::createCartridgeGroup() {

    // l = new QVBoxLayout;

    // QWidget *topFiller = new QWidget;
    // topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // QLabel *t = new QLabel(tr("Some text"));
    // t->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    // t->setAlignment(Qt::AlignCenter);

    // QWidget *bottomFiller = new QWidget;
    // bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // l->setContentsMargins(5, 5, 5, 5);
    // l->addWidget(topFiller);
    // l->addWidget(t);
    // l->addWidget(bottomFiller);

}

void MainWindow::createDetailsPanel() {

    r = new QVBoxLayout;
    r->addWidget(new MetaRegisters);
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
