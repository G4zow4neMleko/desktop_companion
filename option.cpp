#include "option.h"

option::option(QGraphicsItem *parent, QString t) : QObject(), QGraphicsItem()
{
    height = 36;
    width = 146;
    setParentItem(parent);
    text = t;
    color = qRgb(255,255,255);
    text_color = Qt::black;
    setAcceptHoverEvents(true);
}

void option::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    color = qRgb(237, 222, 222);
    text_color = Qt::black;
    this->update(boundingRect());
     Q_UNUSED(event);
}

void option::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    color = qRgb(255,255,255);
    text_color = Qt::black;
    this->update(boundingRect());
    Q_UNUSED(event);
}

void option::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void option::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}

QRectF option::boundingRect() const
{
    return QRectF(0,0,width,height);
}

void option::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(color);
    painter->drawRect(0,0,width,height);
    painter->setPen(text_color);
    painter->setFont(QFont("Arial",15));
    painter->drawText(boundingRect(), Qt::AlignCenter, text);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}


