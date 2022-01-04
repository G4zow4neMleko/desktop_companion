#include "menubutton.h"

MenuButton::MenuButton(): QGraphicsEllipseItem()
{
  circle = new QGraphicsEllipseItem(100,100,20,20);
};

QRectF MenuButton::boundingRect() const
{
    return QRectF(0,0,1000,1000);
};

void MenuButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //painter->drawEllipse(100,100,20,20);
    Q_UNUSED(option);
    Q_UNUSED(widget);
};
