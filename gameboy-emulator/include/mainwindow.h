#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gameboy.h"
#include "gui/include/metaCartridge.h"
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>

#include "include/gameboy.h"

#include <QMetaObject>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <vector>
#include <stdint.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow 
{

    Q_OBJECT

    public:
        MainWindow(char *rom = nullptr);
        ~MainWindow() {};

    public slots:
        void keyPressEvent(QKeyEvent *e);
        void keyReleaseEvent(QKeyEvent *e);
        void gameboyReady();

    private slots:
        void setFile();

    signals:
        void selectedRom(std::string romName);
        void pressed(QKeyEvent *e);

    protected:
        std::vector<uint8_t> *cartridge;

    private:
        Ui::MainWindow *ui;


        void createMenuBar();

        void createDetailsPanel();

        void createPlayerGroup();

        void createActions();


        QMenuBar *menuBar;
        QAction *selectRom;
        QAction *exitAction;

        QMenu *fileMenu;
        QMenu *editMenu;
        QMenu *formatMenu;
        QMenu *helpMenu;
        QActionGroup *alignmentGroup;
        QLabel *infoLabel;

        MetaRegisters *mr;
        MetaCartridge *mc;
        QVBoxLayout *r;
        Gameboy *gb;
};

#endif // MAINWINDOW_H
