#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gameboy.h"

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>

#include <QMetaObject>
#include <QLabel>

#include <vector>
#include <stdint.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow 
{

    Q_OBJECT

    public:
        MainWindow();
        ~MainWindow();


    public slots:
        void testslot(int value);
        void keyPressEvent(QKeyEvent *e);
        void keyReleaseEvent(QKeyEvent *e);

    private slots:
        void setFile();
        void setRom(std::string romName);
        void newFile();

    signals:
        void pressed(QKeyEvent *e);

    protected:
        std::vector<uint8_t> *cartridge;

    private:
        Ui::MainWindow *ui;

        Gameboy *gameboy;

        void createMenuBar();

        void createActions();


        QMenuBar *menuBar;
        QAction *selectRom;
        QAction *exitAction;

        QMenu *fileMenu;
        QMenu *editMenu;
        QMenu *formatMenu;
        QMenu *helpMenu;
        QActionGroup *alignmentGroup;
        QAction *newAct;
        QAction *openAct;
        QAction *saveAct;
        QAction *printAct;
        QAction *exitAct;
        QAction *undoAct;
        QAction *redoAct;
        QAction *cutAct;
        QAction *copyAct;
        QAction *pasteAct;
        QAction *boldAct;
        QAction *italicAct;
        QAction *leftAlignAct;
        QAction *rightAlignAct;
        QAction *justifyAct;
        QAction *centerAct;
        QAction *setLineSpacingAct;
        QAction *setParagraphSpacingAct;
        QAction *aboutAct;
        QAction *aboutQtAct;
        QLabel *infoLabel;
};

#endif // MAINWINDOW_H
