#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#ifndef DEBUG
#include <stdint.h>
#include <vector>

#include <QMetaObject>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>

#include "include/cpu.h"
#include "include/gameboy.h"
#include "include/gui_debug.h"


class Gameboy;

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

        QWidget *widget;
        QHBoxLayout *layout;
        GuiDebug *gd;
        Gameboy *gb;
};
#endif // DEBUG
#endif // MAINWINDOW_H
