#include "gui/include/metaCartridge.h"
#include <QListWidgetItem>

MetaCartridge::MetaCartridge() {

    QWidget *topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    title = new QLabel(tr("<b>Cartridge Title</b>: "));
    title->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    title->setAlignment(Qt::AlignCenter);
    title->setContentsMargins(5, 10, 15, 20);
    title->setWindowFlag(Qt::FramelessWindowHint); // No frame
    title->setAttribute(Qt::WA_NoSystemBackground); // No background

    QWidget *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    setContentsMargins(5, 5, 5, 5);

    // addItem(topFiller);
    addItem(new QListWidgetItem(tr("<b>Cartridge Title</b>: ")));
    // addItem(bottomFiller);

}
