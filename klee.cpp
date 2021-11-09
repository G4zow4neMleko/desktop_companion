#include "klee.h"

Klee::Klee()
{
    QPixmap QPixmap(":/sprites/klee_idle.png");
    class QPixmap scaled = QPixmap.copy(0,0,64,86);

    QGraphicsPixmapItem *klee = new QGraphicsPixmapItem(scaled);
    klee->setPos(700,1080 - 86 - 37);

    addToGroup(klee);
}
