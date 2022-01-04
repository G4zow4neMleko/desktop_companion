#include "option.h"

option::option(QGraphicsItem *parent, QString t) : QObject(), QGraphicsItem()
{
    height = 36;
    width = 146;
    setParentItem(parent);
    text = t;
}

void option::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{

}

void option::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{

}

QRectF option::boundingRect() const
{
    return QRectF(0,0,width,height);
}

void option::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::white);
    painter->drawRect(0,0,width,height);
    painter->setFont(QFont("Arial",15));
    painter->drawText(boundingRect(), Qt::AlignCenter, text);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
