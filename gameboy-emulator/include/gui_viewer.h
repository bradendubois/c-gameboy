#ifndef GUI_VIEWER
#define GUI_VIEWER

#include <stdint.h>
#include <iostream>

#include <QAction>
#include <QActionGroup>
#include <QApplication>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLatin1Char>
#include <QMetaObject>
#include <QObject>
#include <QPushButton>
#include <QSpacerItem>
#include <QStatusBar>
#include <QString>
#include <QTabWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>

enum PPU_LAYER {
    L_SPRITE,
    L_WINDOW,
    L_BACKGROUND
};

class PPUViewer: public QTableWidget {

    Q_OBJECT

    public:
        PPUViewer(QTabWidget *parent, uint8_t rows, uint8_t cols);
        void receiveImage(QImage *img, uint8_t n);

    private:
        QVBoxLayout *layout;
        QLabel *l;
        QTableWidget *viewers;
};



class GuiViewer: public QTabWidget {

    Q_OBJECT

    public:
        GuiViewer(QWidget *parent = nullptr);

    public slots:
        void receiveImage(QImage *img, uint8_t n, PPU_LAYER layer);    

    private:
        PPUViewer *sprites;
        PPUViewer *window;
        PPUViewer *background;

};


#endif
