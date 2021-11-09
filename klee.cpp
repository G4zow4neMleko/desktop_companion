#include "klee.h"

Klee::Klee()
{
    QGraphicsPixmapItem *klee = new QGraphicsPixmapItem(QPixmap(":/sprites/klee_idle.png"));
    klee->setPos(700,960);
    klee->setPixmap();
    addToGroup(klee);
}
