#include "curtain.h"

Curtain::Curtain(QGraphicsItem *parent)
{
    setParentItem(parent);
    width = 70;
    height = 90;
    pos_x = 0;
    pos_y = 0;
    setPos(pos_x,pos_y);

    curatin_pixmap = QPixmap(":/sprites/curtain/curtain.png");

}

QRectF Curtain::boundingRect() const
{
    return QRectF(0,0,width,height);
}

void Curtain::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
     painter->drawPixmap(0,0, curatin_pixmap);
     Q_UNUSED(option);
     Q_UNUSED(widget);
}
