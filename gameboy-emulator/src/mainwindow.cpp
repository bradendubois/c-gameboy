#include "include/mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <fstream>
#include <iterator>
#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "/home", tr("Image Files (*.png, *.jpg, *.bmp)"));

    std::ifstream input(fileName.toStdString(), std::ios::binary );

    // copies all data into buffer
    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::testslot(int value)
{
    (void) value;
}
