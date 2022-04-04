#ifndef META_CARTRIDGE
#define META_CARTRIDGE

#include <QVBoxLayout>
#include <QLabel>
#include <QLayout>
#include <QTabWidget>
#include <QListWidget>

class MetaCartridge: public QListWidget {

    Q_OBJECT

    public:
        MetaCartridge();
    
    private:
        QLabel *title;
};

#endif
